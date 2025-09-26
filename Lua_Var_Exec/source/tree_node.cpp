#include "../include/tree_node.h"

void NodeData::AppendContent(const std::string& additional)
{
    content += additional;
}

TreeNode::TreeNode(const NodeData& nodeData) : data_(nodeData)
{
}

TreeNode* TreeNode::AddChild(std::unique_ptr<TreeNode> child)
{
    TreeNode* childPtr = child.get();
    children_.push_back(std::move(child));
    return childPtr;
}

void TreeNode::AppendToContent(const std::string& additional)
{
    data_.AppendContent(additional);
}

const NodeData& TreeNode::GetData() const
{
    return data_;
}

const std::vector<std::unique_ptr<TreeNode>>& TreeNode::GetChildren() const
{
    return children_;
}

void TreeNode::Clear()
{
    children_.clear();
}