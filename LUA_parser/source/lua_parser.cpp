#include "../include/lua_parser.h"

#include <cctype>
#include <sstream>

LuaParser::LuaParser()
    : pos_(0),
      global_offset_(0),
      binary_operators_({"+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">=", "&&", "||"}),
      unary_operators_({"!", "~", "-", "+"}),
      assignment_operators_({"=", "+=", "-=", "*=", "/=", "%="}),
      conditional_operators_({"?", ":"})
{
}

void LuaParser::ParseStringToNode(TreeNode *parent)
{
    input_ = parent->GetData().content;
    pos_ = 0;
    global_offset_ = parent->GetData().index;

    try
    {
        ParseExpression(parent);

        SkipWhitespace();
        if (pos_ < input_.size())
        {
            ThrowError("Неожиданные символы в конце выражения");
        }
    }
    catch (const ParseException &)
    {
        throw;
    }
    catch (const std::exception &e)
    {
        ThrowError(std::string("Внутренняя ошибка парсера: ") + e.what());
    }
}

void LuaParser::ThrowError(const std::string &message)
{
    throw ParseException(message, GetCurrentIndex());
}

void LuaParser::SkipWhitespace()
{
    while (pos_ < input_.size() && std::isspace(input_[pos_]))
    {
        pos_++;
    }
}

size_t LuaParser::GetCurrentIndex() const
{
    return global_offset_ - pos_;
}

void LuaParser::CheckConsecutiveOperators(TreeNode *parent)
{
    if (!parent->GetChildren().empty())
    {
        const auto &last_child = parent->GetChildren().back();
        NodeType last_type = last_child->GetData().type;

        if (last_type == NodeType::OPERATOR_BINARY || last_type == NodeType::OPERATOR_UNARY ||
            last_type == NodeType::OPERATOR_ASSIGNMENT ||
            last_type == NodeType::OPERATOR_CONDITIONAL)
        {
            ThrowError("Два оператора подряд недопустимы");
        }
    }
}

void LuaParser::ParseExpression(TreeNode *parent)
{
    SkipWhitespace();

    while (pos_ < input_.size() && input_[pos_] != ')' && input_[pos_] != ',')
    {
        size_t relative_index = pos_;
        char current = input_[pos_];

        if (std::isdigit(current))
        {
            ParseNumber(parent, relative_index);
        }
        else if (current == '"' || current == '\'')
        {
            ParseString(parent, relative_index);
        }
        else if (std::isalpha(current) || current == '_' || current == '.')
        {
            ParseIdentifier(parent, relative_index);
        }
        else if (current == '(')
        {
            ParseParenthesis(parent, relative_index);
        }
        else if (IsOperator(current))
        {
            CheckConsecutiveOperators(parent);
            ParseOperator(parent, relative_index);
        }
        else if (current == ',')
        {
            pos_++;
            return;
        }
        else
        {
            ThrowError("Неожиданный символ");
        }

        SkipWhitespace();
    }
}

void LuaParser::ParseFunctionArguments(TreeNode *func_node)
{
    SkipWhitespace();

    if (pos_ < input_.size() && input_[pos_] == ')')
    {
        return;
    }

    while (pos_ < input_.size() && input_[pos_] != ')')
    {
        TreeNode *arg_node = func_node->AddChild("ARG", NodeType::EXPRESSION, GetCurrentIndex());

        ParseExpression(arg_node);

        SkipWhitespace();

        if (pos_ < input_.size() && input_[pos_] == ',')
        {
            pos_++;
            SkipWhitespace();

            if (pos_ >= input_.size() || input_[pos_] == ')')
            {
                ThrowError("Ожидается аргумент после запятой");
            }
        }
        else if (pos_ < input_.size() && input_[pos_] != ')')
        {
            ThrowError("Оживается запятая или закрывающая скобка");
        }
    }
}

void LuaParser::ParseNumber(TreeNode *parent, size_t start_index)
{
    size_t start = pos_;

    while (pos_ < input_.size() && (std::isdigit(input_[pos_]) || input_[pos_] == '.'))
    {
        pos_++;
    }

    std::string number = input_.substr(start, pos_ - start);

    if (number.find('.') != number.find_last_of('.'))
    {
        ThrowError("Неверный формат числа - несколько десятичных точек");
    }

    parent->AddChild(number, NodeType::NUMBER, GetCurrentIndex());
}

void LuaParser::ParseString(TreeNode *parent, size_t start_index)
{
    char quote_char = input_[pos_];
    pos_++;

    size_t start = pos_;
    bool escaped = false;

    while (pos_ < input_.size())
    {
        if (escaped)
        {
            escaped = false;
            pos_++;
            continue;
        }

        if (input_[pos_] == '\\')
        {
            escaped = true;
            pos_++;
        }
        else if (input_[pos_] == quote_char)
        {
            break;
        }
        else
        {
            pos_++;
        }
    }

    if (pos_ >= input_.size())
    {
        ThrowError("Незакрытая строковая константа");
    }

    std::string str_content = input_.substr(start, pos_ - start);
    pos_++;

    parent->AddChild(str_content, NodeType::STRING, GetCurrentIndex());
}

void LuaParser::ParseIdentifier(TreeNode *parent, size_t relative_index)
{
    size_t start = pos_;

    while (pos_ < input_.size() &&
           (std::isalnum(input_[pos_]) || input_[pos_] == '_' || input_[pos_] == '.'))
    {
        pos_++;
    }

    std::string identifier = input_.substr(start, pos_ - start);

    if (!identifier.empty() && identifier.back() == '.')
    {
        ThrowError("Идентификатор не может заканчиваться точкой");
    }

    if (identifier.find("..") != std::string::npos)
    {
        ThrowError("Нельзя использовать две точки подряд в идентификаторе");
    }

    SkipWhitespace();
    if (pos_ < input_.size() && input_[pos_] == '(')
    {
        TreeNode *func_node = parent->AddChild(identifier, NodeType::FUNCTION, GetCurrentIndex());
        pos_++;

        ParseFunctionArguments(func_node);

        if (pos_ >= input_.size() || input_[pos_] != ')')
        {
            ThrowError("Незакрытые скобки функции");
        }
        pos_++;
    }
    else
    {
        parent->AddChild(identifier, NodeType::VARIABLE, GetCurrentIndex());
    }
}

void LuaParser::ParseParenthesis(TreeNode *parent, size_t start_index)
{
    pos_++;

    TreeNode *expr_node = parent->AddChild("EXPR", NodeType::EXPRESSION, GetCurrentIndex());

    ParseExpression(expr_node);

    if (pos_ >= input_.size() || input_[pos_] != ')')
    {
        ThrowError("Незакрытые скобки");
    }
    pos_++;
}

void LuaParser::ParseOperator(TreeNode *parent, size_t start_index)
{
    size_t start = pos_;

    while (pos_ < input_.size() && IsOperatorChar(input_[pos_]))
    {
        pos_++;
    }

    std::string op = input_.substr(start, pos_ - start);

    NodeType op_type = NodeType::OPERATOR_BINARY;

    if (assignment_operators_.find(op) != assignment_operators_.end())
    {
        op_type = NodeType::OPERATOR_ASSIGNMENT;
    }
    else if (unary_operators_.find(op) != unary_operators_.end())
    {
        op_type = NodeType::OPERATOR_UNARY;
    }
    else if (conditional_operators_.find(op) != conditional_operators_.end())
    {
        op_type = NodeType::OPERATOR_CONDITIONAL;
    }

    parent->AddChild(op, op_type, GetCurrentIndex());
}

bool LuaParser::IsOperatorChar(char c) const
{
    return std::string("+-*/%=!<>&|?:~").find(c) != std::string::npos;
}

bool LuaParser::IsOperator(char c) const
{
    return IsOperatorChar(c) && !std::isalnum(c) && c != '_' && c != ',';
}