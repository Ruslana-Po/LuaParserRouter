#include <gtest/gtest.h>
#include "LUA_parser/include/tree_node.h"
using namespace std;

class TreeNodeTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_data = NodeData("test", NodeType::VARIABLE, 10);
    }
    NodeData test_data;
};

TEST_F(TreeNodeTest, ConstructorInitializesDataOne) {
    TreeNode node(test_data);
    const NodeData& data = node.GetData();
    EXPECT_EQ("test", data.content);
}

TEST_F(TreeNodeTest, ConstructorInitializesDataTwo) {
    TreeNode node(test_data);
    const NodeData& data = node.GetData();
    EXPECT_EQ(NodeType::VARIABLE, data.type);
}

TEST_F(TreeNodeTest, ConstructorInitializesDataThree) {
    TreeNode node(test_data);
    const NodeData& data = node.GetData();
    EXPECT_EQ(10, data.index);
}

TEST_F(TreeNodeTest, AddChildCreatesNewChildNoNull) {
    TreeNode parent(test_data);
    TreeNode* child = parent.AddChild("child", NodeType::NUMBER, 5);
    ASSERT_NE(nullptr, child);
}

TEST_F(TreeNodeTest, AddChildCreatesNewChildOne) {
    TreeNode parent(test_data);
    TreeNode* child = parent.AddChild("child", NodeType::NUMBER, 7);
    const NodeData& child_data = child->GetData();
    EXPECT_EQ("child", child_data.content);
}

TEST_F(TreeNodeTest, AddChildCreatesNewChildTwo) {
    TreeNode parent(test_data);
    TreeNode* child = parent.AddChild("child", NodeType::NUMBER, 7);
    const NodeData& child_data = child->GetData();
    EXPECT_EQ(NodeType::NUMBER, child_data.type);
}

TEST_F(TreeNodeTest, AddChildCreatesNewChildThree) {
   TreeNode parent(test_data);
    TreeNode* child = parent.AddChild("child", NodeType::NUMBER, 7);
    const NodeData& child_data = child->GetData();
    EXPECT_EQ(7, child_data.index);
}

TEST_F(TreeNodeTest, AddChildStoresChildInVectorOne) {
    TreeNode parent(test_data);
    TreeNode* child1 = parent.AddChild("child1");
    TreeNode* child2 = parent.AddChild("child2", NodeType::STRING);
    const auto& children = parent.GetChildren();
    EXPECT_EQ(2, children.size());
}

TEST_F(TreeNodeTest, AddChildStoresChildInVectorTwo) {
    TreeNode parent(test_data);
    TreeNode* child1 = parent.AddChild("child1");
    TreeNode* child2 = parent.AddChild("child2", NodeType::STRING);
    const auto& children = parent.GetChildren();
    EXPECT_EQ("child2", children[1]->GetData().content);
}

TEST_F(TreeNodeTest, AppendToContentModifiesData) {
    TreeNode node(test_data);
    node.AppendToContent("_tree");
    EXPECT_EQ("test_tree", node.GetData().content);
}

TEST_F(TreeNodeTest, ClearContentEmptiesContent) {
    TreeNode node(test_data);
    node.ClearContent();
    EXPECT_TRUE(node.GetData().content.empty());
}

TEST_F(TreeNodeTest, ChangeIndexModifiesIndex) {
    TreeNode node(test_data);
    node.ChangeIndex(999);
    EXPECT_EQ(999, node.GetData().index);
}


TEST_F(TreeNodeTest, ClearRemovesAllChildrenKol) {
    TreeNode parent(test_data);
    parent.AddChild("child1");
    parent.AddChild("child2");
    EXPECT_EQ(2, parent.GetChildren().size());
}

TEST_F(TreeNodeTest, ClearRemovesAllChildrenEmpty) {
    TreeNode parent(test_data);
    parent.AddChild("child1");
    parent.AddChild("child2");
    parent.Clear();
    EXPECT_TRUE(parent.GetChildren().empty());
}

//NodeData
TEST(NodeDataTest, ConstructorWithParametersContent) {
    NodeData data("content", NodeType::FUNCTION, 15);
    EXPECT_EQ("content", data.content);
}

TEST(NodeDataTest, ConstructorWithParametersType) {
    NodeData data("content", NodeType::FUNCTION, 15);
    EXPECT_EQ(NodeType::FUNCTION, data.type);
}

TEST(NodeDataTest, ConstructorWithParametersIndex) {
    NodeData data("content", NodeType::FUNCTION, 15);
    EXPECT_EQ(15, data.index);
}

//ТОЖЕ САМОЕ С ПУСТОТОЙ

TEST(NodeDataTest, DefaultConstructorComtent) {
    NodeData data;
    EXPECT_TRUE(data.content.empty());
}

TEST(NodeDataTest, DefaultConstructorType) {
    NodeData data;
    EXPECT_EQ(NodeType::ROOT, data.type);
}

TEST(NodeDataTest, DefaultConstructorIndex) {
    NodeData data;
    EXPECT_EQ(0, data.index);
}


