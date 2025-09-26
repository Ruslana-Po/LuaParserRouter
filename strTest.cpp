#include <gtest/gtest.h>
#include "Lua_Var_Exec/include/str.h"
using namespace std;
class StringManipulationTest : public ::testing::Test {
protected:
    StringManipulation str_manip;
};

//ProcessString
TEST_F(StringManipulationTest, CheckElseNull) {
    string input = "";
    string result = str_manip.ProcessString(input);
    EXPECT_EQ(result, " ");

}

TEST_F(StringManipulationTest, CheckOnliLineBreaks) {
    string input = "\n\n\n";
    string result = str_manip.ProcessString(input);
    EXPECT_EQ(result, " ");

}

TEST_F(StringManipulationTest, CheckStringWhithLineBreaks) {
    string input = "Then \n \n if  else \n       i      \n.";
    string result = str_manip.ProcessString(input);
    EXPECT_EQ(result, " Then if else i . ");

}

TEST_F(StringManipulationTest, CheckOnliSpaces) {
    string input = "Then i       elseif    .";
    string result = str_manip.ProcessString(input);
    EXPECT_EQ(result, " Then i elseif . ");

}

TEST_F(StringManipulationTest, CheckNoSpaces) {
    string input = "Then\nIfCheck\n\nYou";
    string result = str_manip.ProcessString(input);
    EXPECT_EQ(result, " Then IfCheck You ");

}


//FindIfThen
TEST_F(StringManipulationTest, CheckNull) {
    string input = "";
    size_t result = str_manip.FindIfThen(input,0);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, CheckNoIndex) {
    string input = "if then";
    size_t result = str_manip.FindIfThen(input,8);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, WrongIndex) {
    string input = "if then";
    size_t result = str_manip.FindIfThen(input,1);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, TheCorrectLine) {
    string input = "Hello if( )then ";
    size_t result = str_manip.FindIfThen(input,3);
    EXPECT_EQ(result, 15);

}

TEST_F(StringManipulationTest, NoIfTnen) {
    string input = "Hello then ";
    size_t result = str_manip.FindIfThen(input,3);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, CheckWhithSpacesBetwin) {
    string input = "if      then";
    size_t result = str_manip.FindIfThen(input,0);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, CheckWhithSpacesAndEnd) {
    string input = " if      then ";
    size_t result = str_manip.FindIfThen(input,0);
    EXPECT_EQ(result, 13);

}

TEST_F(StringManipulationTest, CheckWhithSmarginsAndEndIf) {
    string input = "\nif      then\n";
    size_t result = str_manip.FindIfThen(input,0);
    EXPECT_EQ(result, 13);

}

TEST_F(StringManipulationTest, CheckWhithSmarginsAndSpacesIf) {
    string input = "\nif      then ";
    size_t result = str_manip.FindIfThen(input,0);
    EXPECT_EQ(result, 13);

}

TEST_F(StringManipulationTest, CheckWhithSmarginsAndSpacesIfTwo) {
    string input = " if      then\n";
    size_t result = str_manip.FindIfThen(input,0);
    EXPECT_EQ(result, 13);

}


//FindElseifThen
TEST_F(StringManipulationTest, CheckNullElseIf) {
    string input = "";
    size_t result = str_manip.FindElseifThen(input,0);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, CheckNoIndexElseIf) {
    string input = "elseif then";
    size_t result = str_manip.FindElseifThen(input,15);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, WrongIndexElseIf) {
    string input = "elseif then";
    size_t result = str_manip.FindElseifThen(input,1);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, TheCorrectLineElseif) {
    string input = "Hello elseif( )then ";
    size_t result = str_manip.FindElseifThen(input,3);
    EXPECT_EQ(result, 19);

}

TEST_F(StringManipulationTest, NoElseIfTnen) {
    string input = "Hello then ";
    size_t result = str_manip.FindElseifThen(input,3);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, CheckWhithSpacesBetwinElseIf) {
    string input = "elseif      then";
    size_t result = str_manip.FindElseifThen(input,0);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, CheckWhithSpacesAndEndElseIf) {
    string input = " elseif      then ";
    size_t result = str_manip.FindElseifThen(input,0);
    EXPECT_EQ(result, 17);

}

TEST_F(StringManipulationTest, CheckWhithSmarginsAndEndElseIf) {
    string input = "\nelseif      then\n";
    size_t result = str_manip.FindElseifThen(input,0);
    EXPECT_EQ(result, 17);

}

TEST_F(StringManipulationTest, CheckWhithSmarginsAndSpacesElseIf) {
    string input = "\nelseif      then ";
    size_t result = str_manip.FindElseifThen(input,0);
    EXPECT_EQ(result, 17);

}

TEST_F(StringManipulationTest, CheckWhithSmarginsAndSpacesElseIfTwo) {
    string input = " elseif      then\n";
    size_t result = str_manip.FindElseifThen(input,0);
    EXPECT_EQ(result, 17);

}

//Else
TEST_F(StringManipulationTest, CheckNullElse) {
    string input = "";
    size_t result = str_manip.FindElse(input,0);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, CheckNoIndexElse) {
    string input = "else then";
    size_t result = str_manip.FindElse(input,8);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, WrongIndexElse) {
    string input = "else then";
    size_t result = str_manip.FindElse(input,1);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, TheCorrectLineElse) {
    string input = "Hello else( )then ";
    size_t result = str_manip.FindElse(input,3);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, TheCorrectLineElseNoStaples) {
    string input = "Hello else then ";
    size_t result = str_manip.FindElse(input,3);
    EXPECT_EQ(result, 10);

}

TEST_F(StringManipulationTest, NoElse) {
    string input = "Hello then ";
    size_t result = str_manip.FindElse(input,3);
    EXPECT_EQ(result, std::string::npos);

}


TEST_F(StringManipulationTest, CheckWhithSpacesBetwinElse) {
    string input = "else";
    size_t result = str_manip.FindElse(input,0);
    EXPECT_EQ(result, std::string::npos);

}

TEST_F(StringManipulationTest, CheckWhithSpacesAndEndElse) {
    string input = " else ";
    size_t result = str_manip.FindElse(input,0);
    EXPECT_EQ(result, 5);

}

TEST_F(StringManipulationTest, CheckWhithSmarginsAndEndElse) {
    string input = "\nelse\n";
    size_t result = str_manip.FindElse(input,0);
    EXPECT_EQ(result, 5);

}

TEST_F(StringManipulationTest, CheckWhithSmarginsAndSpacesElse) {
    string input = "\nelse ";
    size_t result = str_manip.FindElse(input,0);
    EXPECT_EQ(result, 5);

}

TEST_F(StringManipulationTest, CheckWhithSmarginsAndSpacesElseTwo) {
    string input = " else\n";
    size_t result = str_manip.FindElse(input,0);
    EXPECT_EQ(result, 5);

}

//CheckElseString
TEST_F(StringManipulationTest, CheckElseStringNull) {
    string input = "";
    bool result = str_manip.CheckElseString(input);
    EXPECT_FALSE(result);

}

TEST_F(StringManipulationTest, CheckElseNo) {
    string input = "Hello test";
    bool result = str_manip.CheckElseString(input);
    EXPECT_FALSE(result);

}

//!!!!!!!!
TEST_F(StringManipulationTest,  CheckElseOneScape) {
    string input = "Hello test else";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}


TEST_F(StringManipulationTest, CheckElseNoScape) {
    string input = "Hello testelse";
    bool result = str_manip.CheckElseString(input);
    EXPECT_FALSE(result);

}

//!!!!!!!!
TEST_F(StringManipulationTest, CheckElseTwoScape) {
    string input = "Hello else test";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}

TEST_F(StringManipulationTest, CheckElse) {
    string input = " else ";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}
//!!!!!!
TEST_F(StringManipulationTest, NoScapeCheckElse) {
    string input = "else";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}
//!!!!!!
TEST_F(StringManipulationTest, OneLeftScapeCheckElse) {
    string input = " else";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}
//!!!!!!
TEST_F(StringManipulationTest, OneRightScapeCheckElse) {
    string input = "else ";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}

//!!!
TEST_F(StringManipulationTest, LineBreakOneLeftCheckElse) {
    string input = "\nelse ";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}
//!!!!
TEST_F(StringManipulationTest, LineBreakOneRightCheckElse) {
    string input = " else\n";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}
//!!!!!!
TEST_F(StringManipulationTest, LineBreakTwoCheckElse) {
    string input = "\nelse\n";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}

//CheckEndString
TEST_F(StringManipulationTest, CheckEndStringNull) {
    string input = "";
    bool result = str_manip.CheckEndString(input);
    EXPECT_FALSE(result);

}

TEST_F(StringManipulationTest, CheckEndNo) {
    string input = "Hello test";
    bool result = str_manip.CheckEndString(input);
    EXPECT_FALSE(result);

}

TEST_F(StringManipulationTest, CheckEndNoScape) {
    string input = "Hello testend";
    bool result = str_manip.CheckEndString(input);
    EXPECT_FALSE(result);

}

//!!!!!!
TEST_F(StringManipulationTest, CheckEndOneScape) {
    string input = "Hello test end";
    bool result = str_manip.CheckEndString(input);
    EXPECT_TRUE(result);

}

TEST_F(StringManipulationTest, OneLeftScapeCheckEnd) {
    string input = " end";
    bool result = str_manip.CheckEndString(input);
    EXPECT_TRUE(result);

}

//!!!!
TEST_F(StringManipulationTest, OneRightScapeCheckEnd) {
    string input = "end ";
    bool result = str_manip.CheckEndString(input);
    EXPECT_TRUE(result);

}

TEST_F(StringManipulationTest, TwoScapeCheckEnd) {
    string input = " end ";
    bool result = str_manip.CheckEndString(input);
    EXPECT_TRUE(result);

}

//!!!
TEST_F(StringManipulationTest, LineBreakOneLeftCheckEnd) {
    string input = "\nend";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}
//!!!!
TEST_F(StringManipulationTest, LineBreakOneRightCheckEnd) {
    string input = " end\n";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}
//!!!!!!
TEST_F(StringManipulationTest, LineBreakTwoCheckEnd) {
    string input = "\nend\n";
    bool result = str_manip.CheckElseString(input);
    EXPECT_TRUE(result);

}

//CheckElseifThenString
TEST_F(StringManipulationTest, CheckElseIfStringNull) {
    string input = "";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_FALSE(result);

}

TEST_F(StringManipulationTest, CheckElseIfNo) {
    string input = "Hello test";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_FALSE(result);

}

//!!!!
TEST_F(StringManipulationTest, CheckNoThen) {
    string input = " elseif ";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_FALSE(result);

}

TEST_F(StringManipulationTest, CheckYesThenNoElseIf) {
    string input = " then ";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_FALSE(result);

}

TEST_F(StringManipulationTest, IncorrectConstruction) {
    string input = " then elseif ";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_FALSE(result);

}

TEST_F(StringManipulationTest, CorrectDesignElseIf) {
    string input = " elseif then ";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_TRUE(result);

}
//!!!!!
TEST_F(StringManipulationTest, DesignElseIfNoScape) {
    string input = "elseif then";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_TRUE(result);

}
//!!!
TEST_F(StringManipulationTest, DesignElseIfOneLeftScape) {
    string input = " elseif then";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_TRUE(result);

}
//!!!
TEST_F(StringManipulationTest, DesignElseIfOneRightScape) {
    string input = "elseif then ";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_TRUE(result);

}
//!!!!
TEST_F(StringManipulationTest, DesignElseIfAndWord) {
    string input = "ggg elseif then ggg";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_TRUE(result);

}

//!!!
TEST_F(StringManipulationTest, LineBreakOneLeftCheckElseIf) {
    string input = "\nelseif then ";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_TRUE(result);

}
//!!!!
TEST_F(StringManipulationTest, LineBreakOneRightChecklseIf) {
    string input = " elseif then\n";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_TRUE(result);

}
//!!!!!!
TEST_F(StringManipulationTest, LineBreakTwoCheckElseIf) {
    string input = "\nelseif then\n";
    bool result = str_manip.CheckElseifThenString(input);
    EXPECT_TRUE(result);

}

//CheckIfThenString

TEST_F(StringManipulationTest, CheckIfStringNull) {
    string input = "";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_FALSE(result);

}

TEST_F(StringManipulationTest, CheckIfNo) {
    string input = "Hello test";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_FALSE(result);

}

//!!!!
TEST_F(StringManipulationTest, CheckNoThenYesIf) {
    string input = " if ";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_FALSE(result);

}

TEST_F(StringManipulationTest, CheckYesThenNoIf) {
    string input = " then ";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_FALSE(result);

}

TEST_F(StringManipulationTest, IncorrectConstructionThenIf) {
    string input = " then if ";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_FALSE(result);

}

TEST_F(StringManipulationTest, CorrectDesignIf) {
    string input = " if then ";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_TRUE(result);

}
//!!!!!
TEST_F(StringManipulationTest, DesignIfNoScape) {
    string input = "if then";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_TRUE(result);

}
//!!!
TEST_F(StringManipulationTest, DesignIfOneLeftScape) {
    string input = " if then";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_TRUE(result);

}
//!!!
TEST_F(StringManipulationTest, DesignIfOneRightScape) {
    string input = "if then ";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_TRUE(result);

}
//!!!!
TEST_F(StringManipulationTest, DesignIfAndWord) {
    string input = "ggg if then ggg";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_TRUE(result);

}

//!!!
TEST_F(StringManipulationTest, LineBreakOneLeftCheckIf) {
    string input = "\nif then ";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_TRUE(result);

}
//!!!!
TEST_F(StringManipulationTest, LineBreakOneRightCheckIf) {
    string input = " if then\n";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_TRUE(result);

}
//!!!!!!
TEST_F(StringManipulationTest, LineBreakTwoCheckIf) {
    string input = "\nif then\n";
    bool result = str_manip.CheckIfThenString(input);
    EXPECT_TRUE(result);

}



