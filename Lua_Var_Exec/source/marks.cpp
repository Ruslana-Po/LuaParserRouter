#include "../include/marks.h"

const int kElseifLength = 6;
const int kElseLength = 4;

AddMarkers::AddMarkers()
{
}

// сначала проверка на end, потом на if, elseif, else, потом добавление в ноду
bool AddMarkers::ParseTree(TreeNode& root, std::string& work_str)
{
    StringManipulation sm;
    bool status = true;

    while (work_str != "")
    {
        if (sm.CheckEndString(work_str))
        {  // проверка строки на end
            if (root.GetData().type == NodeType::ROOT)
            {  // если end не в условном операторе - ошибка
                throw ParseException("end без if");
            }
            else
            {  // если всё хорошо возвращаемся к родителю
                return true;
            }
        }

        if (sm.CheckIfThenString(work_str))
        {  // если if верный, обрезаем строку и создаем ребенка
            auto child = std::make_unique<TreeNode>(NodeData("", NodeType::IF));
            TreeNode* childPtr = root.AddChild(std::move(child));
            status = ParseTree(*childPtr, work_str);
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
                return false;
            }
            else
            {  // если уже в родителе

                if (sm.CheckElseifThenString(work_str))
                {  // если elseif верный, обрезаем строку и создаем ребенка
                    auto child = std::make_unique<TreeNode>(NodeData("", NodeType::ELSEIF));
                    TreeNode* childPtr = root.AddChild(std::move(child));
                    status =
                        ParseTree(*childPtr, work_str);  // рекурсивно вызываем с корнем в ребенке
                }

                if (sm.CheckElseString(work_str))
                {  // если else верный, обрезаем строку и создаем ребенка
                    auto child = std::make_unique<TreeNode>(NodeData("", NodeType::ELSE));
                    TreeNode* childPtr = root.AddChild(std::move(child));
                    status =
                        ParseTree(*childPtr, work_str);  // рекурсивно вызываем с корнем в ребенке
                }
                continue;
            }
        }

        root.AppendToContent(work_str.substr(0, 1));  // добавляем в блок текущего узла
        work_str = work_str.substr(1);                // обрезаем строку
    }

    if (root.GetData().type != NodeType::ROOT)
    {
        throw ParseException("программа не полная");
    }

    return status;
}

void AddMarkers::Travers(TreeNode* root,
                         std::string& result_str,
                         size_t& start_str,
                         int& marker_num,
                         std::vector<std::string>& blocks)
{
    StringManipulation sm;

    switch (root->GetData().type)
    {  // вставка маркеров в lua код
        case NodeType::ROOT:
            start_str = 0;
            break;
        case NodeType::IF:
            start_str = sm.FindIfThen(result_str, start_str);
            break;
        case NodeType::ELSE:
            start_str = sm.FindElse(result_str, start_str);
            break;
        case NodeType::ELSEIF:
            start_str = sm.FindElseifThen(result_str, start_str);
            break;
    }

    std::string block = sm.ProcessString(root->GetData().content);

    if (block != "" && block != " ")
    {
        blocks.push_back(block);  // кладем в вектор блоки

        result_str.insert(start_str,
                          "\nMARKER" + std::to_string(marker_num) + " = " + "MARKER" +
                              std::to_string(marker_num) + " + 1 ");
        marker_num++;
    }


    for (const auto& child : root->GetChildren())
    {
        Travers(child.get(), result_str, start_str, marker_num, blocks);
    }
}

bool AddMarkers::FindParam(TreeNode* root,
                           const std::string& first_param,
                           const std::string& second_param)
{
    StringManipulation sm;
    std::string block = sm.ProcessString(root->GetData().content);
    int count_open = 0;

    while (!block.empty())
    {
        size_t pos_first = block.find(first_param);
        size_t pos_second = block.find(second_param);

        if (pos_first != std::string::npos && pos_second != std::string::npos)
        {
            if (pos_first < pos_second)
            {
                count_open++;
                block = block.substr(pos_first + first_param.length());
            }
            else
            {
                count_open--;
                block = block.substr(pos_second + second_param.length());
            }
        }
        else if (pos_first != std::string::npos)
        {
            count_open++;
            block = block.substr(pos_first + first_param.length());
        }
        else if (pos_second != std::string::npos)
        {
            count_open--;
            block = block.substr(pos_second + second_param.length());
        }
        else
        {
            break;
        }

        if (count_open < 0)
        {
            return false;
        }
    }
    if (count_open != 0)
    {
        return false;
    }

    for (const auto& child : root->GetChildren())
    {
        if (!FindParam(child.get(), first_param, second_param))
        {
            return false;
        }
    }
    return true;
}

void AddMarkers::AddCodeMarkers(std::string& input, std::vector<std::string>& blocks)
{
    StringManipulation sm;
    std::string result = input;
    std::string work_str =
        sm.ProcessString(input);  // сменить переносы строк на пробелы, убрать лишние пробелы

    Tree tree;

    TreeNode* root = tree.Create(NodeData("", NodeType::ROOT));

    if (!ParseTree(*root, work_str))  // парсим весь код в дерево
    {
        throw ParseException("программа не полная");
    }
    /*
        if (!findParam(root, "{", "}")) {
            throw ParseException("ошибочные закрывающие/открывающие конструкции");
        }
    */
    // tree.printTree(*root);

    int marker_num = 0;
    size_t start_str = 0;
    Travers(root, result, start_str, marker_num, blocks);

    for (int i = 0; i < marker_num; i++)
    {
        result.insert(0, "MARKER" + std::to_string(i) + " = 0\n");
    }

    tree.Clear();

    input = result;
}