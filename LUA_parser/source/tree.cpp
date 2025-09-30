#include "../include/tree.h"

Tree::Tree() : root_(nullptr)
{
}

TreeNode *Tree::Create(const NodeData &rootData)
{
    root_ = std::make_unique<TreeNode>(rootData);
    return root_.get();
}

void Tree::Clear()
{
    root_.reset();
}

void Tree::PrintTree(const TreeNode &node, int depth) const
{
    for (int i = 0; i < depth; ++i)
    {
        std::cout << "  ";
    }

    std::string typeStr;
    switch (node.GetData().type)
    {
        case NodeType::BODY:
            typeStr = "BODY";
            break;
        case NodeType::IF:
            typeStr = "IF";
            break;
        case NodeType::ELSE:
            typeStr = "ELSE";
            break;
        case NodeType::ELSEIF:
            typeStr = "ELSEIF";
            break;
        case NodeType::ROOT:
            typeStr = "ROOT";
            break;
        case NodeType::CONDITION:
            typeStr = "CONDITION";
            break;
        case NodeType::THEN:
            typeStr = "THEN";
            break;

        case NodeType::EXPRESSION:
            typeStr = "EXPRESSION";
            break;
        case NodeType::OPERATOR_BINARY:
            typeStr = "OPERATOR_BINARY";
            break;
        case NodeType::OPERATOR_UNARY:
            typeStr = "OPERATOR_UNARY";
            break;
        case NodeType::NUMBER:
            typeStr = "NUMBER";
            break;
        case NodeType::STRING:
            typeStr = "STRING";
            break;
        case NodeType::VARIABLE:
            typeStr = "VARIABLE";
            break;
        case NodeType::FUNCTION:
            typeStr = "FUNCTION";
            break;

        case NodeType::OPERATOR_ASSIGNMENT:
            typeStr = "OPERATOR_ASSIGNMENT";
            break;
        case NodeType::OPERATOR_CONDITIONAL:
            typeStr = "OPERATOR_CONDITIONAL";
            break;
        case NodeType::PARENTHESIS_OPEN:
            typeStr = "PARENTHESIS_OPEN";
            break;
        case NodeType::PARENTHESIS_CLOSE:
            typeStr = "PARENTHESIS_CLOSE";
            break;
    }

    std::cout << "[" << typeStr << "] " << node.GetData().index << " \"" << node.GetData().content
              << "\"" << std::endl;

    for (const auto &child : node.GetChildren())
    {
        PrintTree(*child, depth + 1);
    }
}

const TreeNode *Tree::getRoot() const
{
    return root_.get();
}