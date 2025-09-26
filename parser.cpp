#include <gtest/gtest.h>
#include <exception>
#include "Lua_Var_Exec/include/parse_exception.h"
using namespace std;

class ParseExceptionTest : public ::testing::Test {
protected:
    void SetUp() override {}
};


TEST_F(ParseExceptionTest, GetExceptionMessage) {
    string message = "Error";
    ParseException exception(message);
    EXPECT_STREQ(message.c_str(), exception.what());
}


TEST_F(ParseExceptionTest, LongExceptionMessage) {
    vector<string> str = {
        "Error",
        "Неверный синтекс",
        "Просто очень очень много разных букв, надеясь, что это все сюда влезет, а так же символы !!!!!!!!!!!!!!!!!!!!!!!!!!№№№№;;%%:;;""№;%:?*",
    };
    
    for (const auto& message : str) {
        ParseException exception(message);
        EXPECT_STREQ(message.c_str(), exception.what());
    }
}


TEST_F(ParseExceptionTest, InheritsFromStdException) {
    ParseException exception("Test");
    try {
        throw exception;
        FAIL() << "Expected exception to be thrown";
    } catch (const std::exception& e) {
        EXPECT_STREQ("Test", e.what());
    } catch (...) {
        FAIL() << "Expected std::exception";
    }
}

TEST_F(ParseExceptionTest, EmptyExceptionMessage) {
    ParseException exception("");
    EXPECT_STREQ("", exception.what());
}
