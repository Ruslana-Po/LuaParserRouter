#include "../include/tree.h"

Tree::Tree() : root_(nullptr)
{
}

TreeNode* Tree::Create(const NodeData& rootData)
{
    root_ = std::make_unique<TreeNode>(rootData);
    return root_.get();
}

void Tree::Clear()
{
    root_.reset();
}

void Tree::PrintTree(const TreeNode& node, int depth) const
{
    for (int i = 0; i < depth; ++i)
    {
        std::cout << "  ";
    }

    std::string typeStr;
    switch (node.GetData().type)
    {
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
    }

    std::cout << "[" << typeStr << "] " << node.GetData().content << std::endl;

    for (const auto& child : node.GetChildren())
    {
        PrintTree(*child, depth + 1);
    }
}