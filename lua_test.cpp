#include <gtest/gtest.h>
#include "LUA_parser/include/lua_parser.h"
#include "LUA_parser/include/tree_node.h"
#include "LUA_parser/include/tree.h"
#include "LUA_parser/include/parse_exception.h"
using namespace std;

class LuaTest : public ::testing::Test {
protected:
    unique_ptr<LuaParser> parser = std::make_unique<LuaParser>();

    TreeNode* CreateRootNode(const std::string& expression) {
        NodeData data(expression, NodeType::EXPRESSION, 0);
        TreeNode* root = new TreeNode(data);
        return root;
    }
};


// числа
#pragma region kek

TEST_F(LuaTest, ParseNumbersThrow) {
    TreeNode* root = CreateRootNode("3");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, ParseNumbersChildrenEmpty) {
    TreeNode* root = CreateRootNode("3");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    ASSERT_FALSE(children.empty());
}

TEST_F(LuaTest, ParseNumbersType) {
    TreeNode* root = CreateRootNode("3");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    EXPECT_EQ(children[0]->GetData().type, NodeType::NUMBER);
}

TEST_F(LuaTest, ParseNumbersContent) {
    TreeNode* root = CreateRootNode("3");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    EXPECT_EQ(children[0]->GetData().content, "3");
}
#pragma endregion

//строки
#pragma region kek
TEST_F(LuaTest, ParseStringThrow) {
    TreeNode* root = CreateRootNode("\"test\"");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, ParseStringChildren) {
    TreeNode* root = CreateRootNode("\"test\"");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    ASSERT_FALSE(children.empty());
}

TEST_F(LuaTest, ParseStringType) {
    TreeNode* root = CreateRootNode("\"test\"");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    EXPECT_EQ(children[0]->GetData().type, NodeType::STRING);
}

TEST_F(LuaTest, ParseStringContent) {
    TreeNode* root = CreateRootNode("\"test\"");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    EXPECT_EQ(children[0]->GetData().content, "test");
}
#pragma endregion

//variable
#pragma region kek
TEST_F(LuaTest, ParseVariableThrow) {
    TreeNode* root = CreateRootNode("variable");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, ParseVariableChildren) {
    TreeNode* root = CreateRootNode("variable");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    ASSERT_FALSE(children.empty());
}

TEST_F(LuaTest, ParseVariableType) {
    TreeNode* root = CreateRootNode("variable");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    EXPECT_EQ(children[0]->GetData().type, NodeType::VARIABLE);
}

TEST_F(LuaTest, ParseVariableContent) {
    TreeNode* root = CreateRootNode("variable");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    EXPECT_EQ(children[0]->GetData().content, "variable");
}
#pragma endregion
//для биарных операторов
#pragma region kek
TEST_F(LuaTest, ParseBinaryOperatorNoThrow) {
    TreeNode* root = CreateRootNode("a + b");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, ParseBinaryOperatorChildren) {
    TreeNode* root = CreateRootNode("a + b");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    ASSERT_EQ(children.size(), 3);
}

//Окак очень странно что на true не меняется 
// Разобралась
// Ошибка потому что он принимает + не за бинарный, а за унарный оператор, но в данном случае это не так
// Заменив на это || child->GetData().type == NodeType::OPERATOR_UNARY тест зараюотает 
TEST_F(LuaTest, ParseBinaryOperator) {
    TreeNode* root = CreateRootNode("a + b");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    bool foundOperator = false;
    for (const auto& child : children) {
        if (child->GetData().type == NodeType::OPERATOR_BINARY ) {
            foundOperator = true;
            EXPECT_EQ(child->GetData().content, "+");
            break;
        }
    }
    EXPECT_TRUE(foundOperator);
}
#pragma endregion

// функции
#pragma region kek
TEST_F(LuaTest, ParseFuncNoThrow) {
    TreeNode* root = CreateRootNode("func()");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, ParseFuncChildren) {
    TreeNode* root = CreateRootNode("func()");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    ASSERT_FALSE(children.empty());
}

TEST_F(LuaTest, ParseFuncType) {
    TreeNode* root = CreateRootNode("func()");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    EXPECT_EQ(children[0]->GetData().type, NodeType::FUNCTION);
}

TEST_F(LuaTest, ParseFuncContent) {
    TreeNode* root = CreateRootNode("func()");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    EXPECT_EQ(children[0]->GetData().content, "func");
}
#pragma endregion

//скобочки
#pragma region kek
TEST_F(LuaTest, ParseParenthesesNoThrow) {
    TreeNode* root = CreateRootNode("(a + b)");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, ParseParenthesesChildren) {
    TreeNode* root = CreateRootNode("(a + b)");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    ASSERT_FALSE(children.empty());
}

TEST_F(LuaTest, ParseParenthesesType) {
    TreeNode* root = CreateRootNode("(a + b)");
    parser->ParseStringToNode(root);
    const auto& children = root->GetChildren();
    EXPECT_EQ(children[0]->GetData().type, NodeType::EXPRESSION);
}
//не закрывающиеся скобочки

TEST_F(LuaTest, UnclosedParentheses) {
    TreeNode* root = CreateRootNode("(a + b");
    EXPECT_THROW(parser->ParseStringToNode(root), ParseException);
}

TEST_F(LuaTest, UnclosedParenthesesTwo) {
    TreeNode* root = CreateRootNode("(a + b))");
    EXPECT_THROW(parser->ParseStringToNode(root), ParseException);
}
#pragma endregion

//Пропуск слогаемых для бинарных
#pragma region kek
TEST_F(LuaTest, ConsecutiveOperators) {
    TreeNode* root = CreateRootNode("a + * b");
    EXPECT_THROW(parser->ParseStringToNode(root), ParseException);
}

//???
TEST_F(LuaTest, ConsecutiveOperatorsTwo) {
    TreeNode* root = CreateRootNode("a == ");
    EXPECT_THROW(parser->ParseStringToNode(root), ParseException);
}
#pragma endregion

// неправильный ввод данных
#pragma region kek
TEST_F(LuaTest, InvalidNumberFormat) {
    TreeNode* root = CreateRootNode("3.2.1.0");
    EXPECT_THROW(parser->ParseStringToNode(root), ParseException);

}

TEST_F(LuaTest, InvalidNumberFormatTwo) {
    TreeNode* root = CreateRootNode("* == /");
    EXPECT_THROW(parser->ParseStringToNode(root), ParseException);

}

//дублированные элементы без пары
TEST_F(LuaTest, UnclosedString) {
    TreeNode* root = CreateRootNode("\"test");
    EXPECT_THROW(parser->ParseStringToNode(root), ParseException);
}

//проверка на строках со множетвом операторов

TEST_F(LuaTest, ComplexExpression) {
    TreeNode* root = CreateRootNode("func(0 + b, \"test\")");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));

}

TEST_F(LuaTest, EmptyStringChildren) {
    TreeNode* root = CreateRootNode("");
    EXPECT_TRUE(root->GetChildren().empty());

}

TEST_F(LuaTest, OnlyWhitespace) {
    TreeNode* root = CreateRootNode("   \t\n  ");
    EXPECT_TRUE(root->GetChildren().empty());
    ASSERT_NO_THROW(parser->ParseStringToNode(root));

}
#pragma endregion

//Обнаруженные ошибки
// По синтексу Lua не должно быть ошибок
#pragma region kek
TEST_F(LuaTest, Exponentiation) {
    TreeNode* root = CreateRootNode("a ^= 9");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, NotEqualTo) {
    TreeNode* root = CreateRootNode("a ~= 9");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, OrWhithNumber) {
    TreeNode* root = CreateRootNode("a == 9 or a == 6");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, AndWhithNumber) {
    TreeNode* root = CreateRootNode("a == 9 and b == 6");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, NoWhithNumber) {
    TreeNode* root = CreateRootNode("result = not a");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, Inversion) {
    TreeNode* root = CreateRootNode(" ~b ");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}

TEST_F(LuaTest, ExponentiationTwo) {
    TreeNode* root = CreateRootNode("a ^ 9");
    ASSERT_NO_THROW(parser->ParseStringToNode(root));
}
#pragma endregion

// Должны выдать ошибки
#pragma region kek
TEST_F(LuaTest, ExclamationPoint) {
    TreeNode* root = CreateRootNode("a != 9");
    EXPECT_THROW(parser->ParseStringToNode(root), ParseException);
}

TEST_F(LuaTest, ExclamationPointTwo) {
    TreeNode* root = CreateRootNode(" !b ");
    EXPECT_THROW(parser->ParseStringToNode(root), ParseException);
}

TEST_F(LuaTest, OnlyMark) {
    TreeNode* root = CreateRootNode(" = ");
    EXPECT_THROW(parser->ParseStringToNode(root), ParseException);
}

TEST_F(LuaTest, UnclosedParenthesesThree) {
    TreeNode* root = CreateRootNode("( )");
    EXPECT_THROW(parser->ParseStringToNode(root), ParseException);
}
#pragma endregion
