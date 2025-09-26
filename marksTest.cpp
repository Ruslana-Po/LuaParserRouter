#include <gtest/gtest.h>
#include <vector>
#include "Lua_Var_Exec/include/marks.h"
using namespace std;

class AddMarkersTest : public ::testing::Test {
protected:
    AddMarkers marks_test;
string ProcessAndGetResult(const string& input) {
        AddMarkers marker;
        vector<string> blocks;
        string result = input;
        
        try {
            marker.AddCodeMarkers(result, blocks);
            return result;
        } catch (const ParseException& e) {
            return "ERROR: " + string(e.what());
        }
}
};

//AddCodeMarkers
//!!!
TEST_F(AddMarkersTest, CheckNullString) {
    string input = "";
    vector<string> str;
    ASSERT_THROW(marks_test.AddCodeMarkers(input, str), ParseException);
}

TEST_F(AddMarkersTest, ElseWithoutIf) {
    string input = "end";
    vector<string> str;
    ASSERT_THROW(marks_test.AddCodeMarkers(input, str), ParseException);
}


TEST_F(AddMarkersTest, SimpleIfBlock) {
    string input = " if condition then\n statement\nend";
    vector<string> str;
    ASSERT_NO_THROW(marks_test.AddCodeMarkers(input, str));
}


TEST_F(AddMarkersTest, IfElseBlock) {
    string input = " if condition then\n st1\nelse\n st2\nend";
    vector<string> str;
    ASSERT_NO_THROW(marks_test.AddCodeMarkers(input, str));
}

TEST_F(AddMarkersTest, NestedIfBlocks) {
    string input = " if cond1 then\n if cond2 then\n st1\n end\nend";
    vector<string> str;
    ASSERT_NO_THROW(marks_test.AddCodeMarkers(input, str));
}

TEST_F(AddMarkersTest, LargeCodeBlock) {
    string input = " if cond1 then\n if cond2 then\n elseif ggg then   \n elseif gg then \n\n else st1\n end  else str4\nend";
    vector<string> str;
    ASSERT_NO_THROW(marks_test.AddCodeMarkers(input, str));
}

//Разделить ???
TEST_F(AddMarkersTest, BasicIfTest) {
    string input = " if condition then\n do_something()\nend";
    string result = ProcessAndGetResult(input);
    
    EXPECT_TRUE(result.find("MARKER0 = 0") != std::string::npos);
    EXPECT_TRUE(result.find("MARKER0 = MARKER0 + 1") != std::string::npos);
    EXPECT_TRUE(result.find("do_something()") != std::string::npos);
}

//Разделить ???
TEST_F(AddMarkersTest, BasicElseIfTest) {
    string input = " if condition then\n do_something()\n elseif what then\n tra()\nend";
    string result = ProcessAndGetResult(input);
    
    EXPECT_TRUE(result.find("MARKER0 = 0") != std::string::npos);
    EXPECT_TRUE(result.find("MARKER1 = 0") != std::string::npos);
    EXPECT_TRUE(result.find("MARKER0 = MARKER0 + 1") != std::string::npos);
    EXPECT_TRUE(result.find("MARKER1 = MARKER1 + 1") != std::string::npos);
    EXPECT_TRUE(result.find("do_something()") != std::string::npos);
    EXPECT_TRUE(result.find("tra()") != std::string::npos);
}

TEST_F(AddMarkersTest, BasicElseTest) {
    string input = " if condition then\n do_something()\n else\n tra()\nend";
    string result = ProcessAndGetResult(input);
    
    EXPECT_TRUE(result.find("MARKER0 = 0") != std::string::npos);
    EXPECT_TRUE(result.find("MARKER1 = 0") != std::string::npos);
    EXPECT_TRUE(result.find("MARKER0 = MARKER0 + 1") != std::string::npos);
    EXPECT_TRUE(result.find("MARKER1 = MARKER1 + 1") != std::string::npos);
    EXPECT_TRUE(result.find("do_something()") != std::string::npos);
}

TEST_F(AddMarkersTest, BasicElseNoIfTest) {
    string input = " else\n tra()\nend";
    string result = ProcessAndGetResult(input);
    EXPECT_TRUE(result.find("ERROR") != std::string::npos);
}

TEST_F(AddMarkersTest, BasicEndNoIfTest) {
    string input = "\nend";
    string result = ProcessAndGetResult(input);
    EXPECT_TRUE(result.find("ERROR") != std::string::npos);
}

TEST_F(AddMarkersTest, BasicElseIfNoIfTest) {
    string input = "\n elseif what then\n tra()\nend";
    string result = ProcessAndGetResult(input);
    EXPECT_TRUE(result.find("ERROR") != std::string::npos);
}

//!!!!
TEST_F(AddMarkersTest, OnlyWhitespaceTest) {
    string input = "   \n   \t   \n   ";
    string result = ProcessAndGetResult(input);
    EXPECT_TRUE(result.find("ERROR") != std::string::npos);
}

TEST_F(AddMarkersTest, BasicIfNoThenTest) {
    string input = " if condition\nend";
    string result = ProcessAndGetResult(input);
    EXPECT_TRUE(result.find("ERROR") != std::string::npos);
}

TEST_F(AddMarkersTest, BasicElseIfNoThenTest) {
    string input = " if condition then\n do_something()\n elseif what \nend";
    string result = ProcessAndGetResult(input);
    EXPECT_TRUE(result.find("ERROR") != std::string::npos);
}

//!!!!!
TEST_F(AddMarkersTest, BasicElseWithThenTest) {
    string input = " if condition then\n do_something()\n else then\n tra()\nend";
    string result = ProcessAndGetResult(input);
    EXPECT_TRUE(result.find("ERROR") != std::string::npos);
}
