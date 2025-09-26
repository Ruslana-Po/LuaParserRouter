#include <gtest/gtest.h>
#include <memory>
#include "Lua_Var_Exec/include/tree_node.h"
using namespace std;

class TreeNodeTest : public ::testing::Test {
protected:
};

TEST_F(TreeNodeTest, NodeDataConstructor) {
    NodeData data("test content", NodeType::IF);
    
    EXPECT_EQ(data.content, "test content");
    EXPECT_EQ(data.type, NodeType::IF);
}

TEST_F(TreeNodeTest, NodeDataDefaultConstructor) {
    NodeData data;
    
    EXPECT_TRUE(data.content.empty());
    EXPECT_EQ(data.type, NodeType::ROOT);
}

TEST_F(TreeNodeTest, AppendToContent) {
    TreeNode node(NodeData("initial", NodeType::IF));
    node.AppendToContent(" more");
    node.AppendToContent(" content");
    EXPECT_EQ(node.GetData().content, "initial more content");
}

TEST_F(TreeNodeTest, GetData) {
    NodeData expectedData("test data", NodeType::ELSE);
    TreeNode node(expectedData);
    
    const NodeData& actualData = node.GetData();
    
    EXPECT_EQ(actualData.content, "test data");
    EXPECT_EQ(actualData.type, NodeType::ELSE);
}


TEST_F(TreeNodeTest, NodeDataAppendEmptyContent) {
    NodeData data("initial", NodeType::ELSEIF);
    data.AppendContent("");
    
    EXPECT_EQ(data.content, "initial");
}

TEST_F(TreeNodeTest, TreeNodeConstructor) {
    NodeData nodeData("node content", NodeType::IF);
    TreeNode node(nodeData);
    
    EXPECT_EQ(node.GetData().content, "node content");
    EXPECT_EQ(node.GetData().type, NodeType::IF);
    EXPECT_TRUE(node.GetChildren().empty());
}

TEST_F(TreeNodeTest, AddChild) {
    TreeNode parent(NodeData("parent", NodeType::ROOT));
    
    auto child = std::make_unique<TreeNode>(NodeData("child", NodeType::IF));
    TreeNode* childPtr = parent.AddChild(std::move(child));
    
    ASSERT_NE(childPtr, nullptr);
    EXPECT_EQ(childPtr->GetData().content, "child");
    EXPECT_EQ(childPtr->GetData().type, NodeType::IF);
    EXPECT_EQ(parent.GetChildren().size(), 1);
}

TEST_F(TreeNodeTest, ClearEmptyNode) {
    TreeNode node(NodeData("test", NodeType::IF));
    
    EXPECT_TRUE(node.GetChildren().empty());
    node.Clear();
    EXPECT_TRUE(node.GetChildren().empty());
}
