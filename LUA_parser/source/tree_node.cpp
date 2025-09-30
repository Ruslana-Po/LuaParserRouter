#include "../include/tree_node.h"

void NodeData::AppendContent(const std::string &additional)
{
    content += additional;
}

void NodeData::ClearData()
{
    content = "";
    index = 0;
}

void NodeData::NewIndex(int new_index)
{
    index = new_index;
}

TreeNode::TreeNode(const NodeData &nodeData) : data_(nodeData)
{
}

TreeNode *TreeNode::AddChild(const std::string &content, NodeType type, int index)
{
    auto child = std::make_unique<TreeNode>(NodeData(content, type, index));
    TreeNode *childPtr = child.get();
    children_.push_back(std::move(child));
    return childPtr;
}

void TreeNode::AppendToContent(const std::string &additional)
{
    data_.AppendContent(additional);
}

void TreeNode::ClearContent()
{
    data_.ClearData();
}

void TreeNode::ChangeIndex(int new_index)
{
    data_.NewIndex(new_index);
}

const NodeData &TreeNode::GetData() const
{
    return data_;
}

const std::vector<std::unique_ptr<TreeNode>> &TreeNode::GetChildren() const
{
    return children_;
}

void TreeNode::Clear()
{
    children_.clear();
}