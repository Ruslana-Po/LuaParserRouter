#include <gtest/gtest.h>
#include "LUA_parser/include/parse.h"
#include "LUA_parser/include/tree_node.h"
using namespace std;

class ParseCodeTest : public ::testing::Test {
protected:
    void SetUp() override {
        parse_code = make_unique<ParseCode>();
    }
    
    unique_ptr<ParseCode> parse_code;
};

TEST_F(ParseCodeTest, EmptyInput) {
    string input = "";
    vector<string> variables;
    EXPECT_THROW(parse_code->CodeParse(input, variables), ParseException);
}

TEST_F(ParseCodeTest, CodeParseWithSimpleVariable) {
    string input = "x = 5";
    vector<string> variables;
    EXPECT_NO_THROW(parse_code->CodeParse(input, variables));
}

TEST_F(ParseCodeTest, ParseBodyWithValidRoot) {
    NodeData root_data("root", NodeType::ROOT, 0);
    TreeNode root(root_data);
    EXPECT_NO_THROW(parse_code->ParseBody(&root));
}


TEST_F(ParseCodeTest, CheckFuncWithValidRoot) {
    NodeData root_data("root", NodeType::ROOT, 0);
    TreeNode root(root_data);
    EXPECT_NO_THROW(parse_code->CheckFunc(&root));
}


TEST_F(ParseCodeTest, CodeParseThrowsParse) {
    string input = "if x == 5 then y = 10";
    vector<string> variables;
    EXPECT_THROW(parse_code->CodeParse(input, variables), ParseException);
}

TEST_F(ParseCodeTest, CodeParseThrowsWithCorrectErrorMessage) {
    string input = "if condition then x = 1"; 
    vector<string> variables;
    try {
        parse_code->CodeParse(input, variables);
        FAIL() << "Expected ParseException for incomplete code";
    } catch (const ParseException& e) {
        EXPECT_STREQ("программа не полная", e.what());
    }
}

TEST_F(ParseCodeTest, CodeParseThrowsOnEndWithoutIf) {
    string input = "end"; 
    vector<string> variables;
    EXPECT_THROW(parse_code->CodeParse(input, variables), ParseException);
}

// 5 не должна сохрантся
TEST_F(ParseCodeTest, VariablesExtractsVariableNodesTwo) {
    NodeData root_data("root", NodeType::ROOT, 0);
    TreeNode root(root_data);
    root.AddChild("x", NodeType::VARIABLE, 1);
    root.AddChild("y", NodeType::VARIABLE, 2);
    root.AddChild("5", NodeType::NUMBER, 3); 
    vector<string> variables;
    parse_code->Variables(&root, variables);
    EXPECT_EQ(2, variables.size());
}

TEST_F(ParseCodeTest, VariablesExtractsVariableNodesX) {
    NodeData root_data("root", NodeType::ROOT, 0);
    TreeNode root(root_data);
    root.AddChild("x", NodeType::VARIABLE, 1);
    root.AddChild("y", NodeType::VARIABLE, 2);
    root.AddChild("5", NodeType::NUMBER, 3); 
    vector<string> variables;
    parse_code->Variables(&root, variables);
    EXPECT_EQ("x", variables[0]);
}

TEST_F(ParseCodeTest, VariablesExtractsVariableNodesY) {
    NodeData root_data("root", NodeType::ROOT, 0);
    TreeNode root(root_data);
    root.AddChild("x", NodeType::VARIABLE, 1);
    root.AddChild("y", NodeType::VARIABLE, 2);
    root.AddChild("5", NodeType::NUMBER, 3); 
    vector<string> variables;
    parse_code->Variables(&root, variables);
    EXPECT_EQ("y", variables[1]);
}

