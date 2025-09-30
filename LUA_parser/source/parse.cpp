#include "../include/parse.h"

ParseCode::ParseCode()
{
}

void AddCopyChild(TreeNode &root, int index)
{
    root.AddChild(root.GetData().content, NodeType::BODY, index);
    root.ClearContent();
}

bool ParseCode::ParseTree(TreeNode &root, std::string &work_str)
{
    StringManipulation sm;
    bool status = true;
    std::string condition = "";

    while (work_str != "")
    {
        if (sm.CheckEndString(work_str))
        {  // проверка строки на end
            if (root.GetData().type == NodeType::ROOT)
            {  // если end не в условном операторе - ошибка
                throw ParseException("end без if", work_str.size());
            }
            else
            {  // если всё хорошо возвращаемся к родителю
                AddCopyChild(root, root.GetData().index);
                return true;
            }
        }

        if (sm.CheckIfThenString(work_str, condition))
        {  // если if верный, обрезаем строку и создаем ребенка
            AddCopyChild(root, root.GetData().index);
            TreeNode *childPtr = root.AddChild("", NodeType::IF);
            childPtr->AddChild(
                condition, NodeType::CONDITION, work_str.size() + kThenLength + condition.size());
            TreeNode *childPtrThen = childPtr->AddChild("", NodeType::THEN, work_str.size());
            status = ParseTree(*childPtrThen, work_str);
            continue;
        }

        // Проверяем, начинается ли строка с "elseif " или "else "
        if ((work_str.size() > kElseLength + 1 &&
             work_str.substr(0, kElseLength + 2) == " else ") ||
            (work_str.size() > kElseifLength + 1 &&
             work_str.substr(0, kElseifLength + 2) == " elseif "))
        {
            if (status)
            {  // если на том же уровне, то подняться в родителя
                AddCopyChild(root, work_str.size() + root.GetData().content.size());
                return false;
            }
            else
            {  // если уже в родителе

                if (sm.CheckElseifThenString(work_str, condition))
                {
                    TreeNode *childPtr = root.AddChild("", NodeType::ELSEIF);
                    childPtr->AddChild(condition,
                                       NodeType::CONDITION,
                                       work_str.size() + condition.size() + kThenLength);
                    TreeNode *childPtrThen =
                        childPtr->AddChild("", NodeType::THEN, work_str.size());
                    status = ParseTree(*childPtrThen,
                                       work_str);  // рекурсивно вызываем с корнем в ребенке
                }

                if (sm.CheckElseString(work_str))
                {
                    TreeNode *childPtr = root.AddChild("", NodeType::ELSE, work_str.size());
                    status =
                        ParseTree(*childPtr, work_str);  // рекурсивно вызываем с корнем в ребенке
                }
                continue;
            }
        }

        root.AppendToContent(work_str.substr(0, 1));  // добавляем в блок текущего узла
        work_str = work_str.substr(1);                // обрезаем строку
    }
    AddCopyChild(root, work_str.size() + root.GetData().content.size());

    if (root.GetData().type != NodeType::ROOT)
    {
        throw ParseException("программа не полная");
    }

    return status;
}

void ParseCode::ParseBody(TreeNode *root)
{
    for (const auto &child : root->GetChildren())
    {
        ParseBody(child.get());
    }

    LuaParser parser;

    if (root->GetData().type == NodeType::BODY || root->GetData().type == NodeType::CONDITION)
    {
        parser.ParseStringToNode(root);
    }

    root->ClearContent();
}

void ParseCode::CheckFunc(TreeNode *root)
{
    for (const auto &child : root->GetChildren())
    {
        CheckFunc(child.get());
    }

    Function funcParser;

    if (root->GetData().type == NodeType::FUNCTION)
    {
        auto &children = root->GetChildren();
        try
        {
            funcParser.FunctionParse(root->GetData().content, children.size());
        }
        catch (const std::exception &e)
        {
            throw ParseException(e.what(), root->GetData().index);
        }
    }
}

void ParseCode::Variables(TreeNode *root, std::vector<std::string> &variables)
{
    for (const auto &child : root->GetChildren())
    {
        Variables(child.get(), variables);
    }

    if (root->GetData().type == NodeType::VARIABLE)
    {
        variables.push_back(root->GetData().content);
    }
}

void ParseCode::CodeParse(std::string &input, std::vector<std::string> &variables)
{
    StringManipulation sm;
    std::string result = input;
    std::string work_str = sm.ProcessString(input);  // сменить переносы строк на пробелы

    Tree tree;

    TreeNode *root = tree.Create(NodeData("", NodeType::ROOT, work_str.size()));

    if (!ParseTree(*root, work_str))  // парсим весь код в дерево
    {
        throw ParseException("программа не полная");
    }

    ParseBody(root);

    CheckFunc(root);

    Variables(root, variables);

    // tree.PrintTree(*root);

    tree.Clear();
}