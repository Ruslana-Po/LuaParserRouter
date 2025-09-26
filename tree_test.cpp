#include <gtest/gtest.h>
#include <memory>
#include "Lua_Var_Exec/include/tree.h"
using namespace std;

class TreeTest : public ::testing::Test {
protected:
    Tree test;
};


TEST_F(TreeTest, TreeCreation) {
    TreeNode* root = test.Create(NodeData("root", NodeType::ROOT));
    
    ASSERT_NE(root, nullptr);
}

TEST_F(TreeTest, TreeCreationTwoTest) {
    TreeNode* root1 = test.Create(NodeData("root", NodeType::ROOT));
    EXPECT_EQ(root1->GetData().content, "root");
   
}
TEST_F(TreeTest, TreeCreationThreeTest) {
    TreeNode* root1 = test.Create(NodeData("root", NodeType::ROOT));
    EXPECT_EQ(root1->GetData().type, NodeType::ROOT);
}

TEST_F(TreeTest, TreeCreationFourTest) {
    TreeNode* root1 = test.Create(NodeData("root", NodeType::ROOT));
    EXPECT_TRUE(root1->GetChildren().empty());
}
//&&&&
TEST_F(TreeTest, PrintTreeNull) {
    TreeNode* root1= nullptr;
    ASSERT_DEATH(test.PrintTree(*root1), ".*");
}


TEST_F(TreeTest, ClearTree) {
   
    test.Clear();
    
    ASSERT_NO_THROW({
        TreeNode* newRoot = test.Create(NodeData("new_root", NodeType::ROOT));
    });
}

TEST_F(TreeTest, PrintTreeOutput) {
    TreeNode* root = test.Create(NodeData("test", NodeType::ROOT));
    // Перенаправляем вывод
    testing::internal::CaptureStdout();
    test.PrintTree(*root);
    string output = testing::internal::GetCapturedStdout();
    
    string expected = "[ROOT] test\n";
    ASSERT_EQ(expected, output);
}


