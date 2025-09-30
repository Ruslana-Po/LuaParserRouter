#include <gtest/gtest.h>
#include "LUA_parser/include/check_func.h"
using namespace std;

class FunctionTest : public ::testing::Test {
protected:
    Function test;
};

//FunctionParse
TEST_F(FunctionTest, EmptyString) {
    string func="";
    int arg =1;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, EmptyArg) {
    string func="math.abs";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, NonExistentStr) {
    string func="math.ab";
    int arg =1;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArguments) {
    string func="math.abs";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, FunctionWithOneArgument) {
    string func="math.abs";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

TEST_F(FunctionTest, AtanWithTwoArgument) {
    string func="math.atan";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

TEST_F(FunctionTest, AtanWithOneArgument) {
    string func="math.atan";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

TEST_F(FunctionTest, LogWithTwoArgument) {
    string func="math.log";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

TEST_F(FunctionTest, LogWithOneArgument) {
    string func="math.log";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

TEST_F(FunctionTest, RandomWithTwoArgument) {
    string func="math.random";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

TEST_F(FunctionTest, RandomWithOneArgument) {
    string func="math.random";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

TEST_F(FunctionTest, RandomNoArgument) {
    string func="math.random";
    int arg =0;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//Проверка каждой функции на пустое значение и разные аргументы
//match.acos уже проверен, поэтому с функцие принимающих разное значение и которые я начинала проверять
// atan
TEST_F(FunctionTest, AtanWithNoArgument) {
    string func="math.atan";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, AtanWithThreeArgument) {
    string func="math.atan";
    int arg =3;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}
//Log
TEST_F(FunctionTest, LogWithNoArgument) {
    string func="math.log";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LogWithThreeArgument) {
    string func="math.log";
    int arg =3;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}
//Random
TEST_F(FunctionTest, RandomWithThreeArgument) {
    string func="math.random";
    int arg =3;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

//acos
TEST_F(FunctionTest, EmptyArgAcos) {
    string func="math.acos";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsAcos) {
    string func="math.acos";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, AcosWithOneArgument) {
    string func="math.acos";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//asin
TEST_F(FunctionTest, EmptyArgAsin) {
    string func="math.asin";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsAsin) {
    string func="math.asin";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, AsinWithOneArgument) {
    string func="math.asin";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//atan2
TEST_F(FunctionTest, EmptyArgAtan2) {
    string func="math.atan2";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsAtan2) {
    string func="math.atan2";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

TEST_F(FunctionTest, Atan2WithThreeArgument) {
    string func="math.atan2";
    int arg =3;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

//ceil
TEST_F(FunctionTest, EmptyArgCeil) {
    string func="math.ceil";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsCeil) {
    string func="math.ceil";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, CeilWithOneArgument) {
    string func="math.ceil";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//cos
TEST_F(FunctionTest, EmptyArgCos) {
    string func="math.cos";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsCos) {
    string func="math.cos";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, CosWithOneArgument) {
    string func="math.cos";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//cosh
TEST_F(FunctionTest, EmptyArgCosh) {
    string func="math.cosh";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsCosh) {
    string func="math.cosh";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, CoshWithOneArgument) {
    string func="math.cosh";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//deg
TEST_F(FunctionTest, EmptyArgDeg) {
    string func="math.deg";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsDeg) {
    string func="math.deg";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, DegWithOneArgument) {
    string func="math.deg";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//exp
TEST_F(FunctionTest, EmptyArgExp) {
    string func="math.exp";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsExp) {
    string func="math.exp";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, ExpWithOneArgument) {
    string func="math.exp";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//floor
TEST_F(FunctionTest, EmptyArgFloor) {
    string func="math.floor";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsFloor) {
    string func="math.floor";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, FloorWithOneArgument) {
    string func="math.floor";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//fmod
TEST_F(FunctionTest, EmptyArgFmod) {
    string func="math.fmod";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsFmod) {
    string func="math.fmod";
    int arg =3;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, FmodWithTwoArgument) {
    string func="math.fmod";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//frexp
TEST_F(FunctionTest, EmptyArgFrexp) {
    string func="math.frexp";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsFrexp) {
    string func="math.frexp";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, FrexpWithOneArgument) {
    string func="math.frexp";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//huge
TEST_F(FunctionTest, LotOfArgumentsHuge) {
    string func="math.huge";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, HugeWithNullArgument) {
    string func="math.huge";
    int arg =0;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//ldexp
TEST_F(FunctionTest, EmptyArgLdexp) {
    string func="math.ldexp";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsLdexp) {
    string func="math.ldexp";
    int arg =3;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LdexpWithTwoArgument) {
    string func="math.ldexp";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//Log10
TEST_F(FunctionTest, EmptyArgLog10) {
    string func="math.log10";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsLog10) {
    string func="math.log10";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, Log10WithOneArgument) {
    string func="math.log10";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//max
TEST_F(FunctionTest, EmptyArgMax) {
    string func="math.max";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, MaxWithOneArgument) {
    string func="math.max";
    int arg =1;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, MaxWithTwoArgument) {
    string func="math.max";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

TEST_F(FunctionTest, MaxWithManyArgument) {
    string func="math.max";
    int arg =5;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//min
TEST_F(FunctionTest, EmptyArgMin) {
    string func="math.min";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, MinWithOneArgument) {
    string func="math.min";
    int arg =1;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, MinWithTwoArgument) {
    string func="math.min";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

TEST_F(FunctionTest, MinWithManyArgument) {
    string func="math.min";
    int arg =5;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//modf
TEST_F(FunctionTest, EmptyArgModf) {
    string func="math.modf";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsModf) {
    string func="math.modf";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, ModfWithOneArgument) {
    string func="math.modf";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//pi
TEST_F(FunctionTest, LotOfArgumentsPi) {
    string func="math.pi";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, PiWithNullArgument) {
    string func="math.pi";
    int arg =0;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//pow
TEST_F(FunctionTest, EmptyArgPow) {
    string func="math.pow";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsPow) {
    string func="math.pow";
    int arg =3;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, PowWithTwoArgument) {
    string func="math.pow";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//rad
TEST_F(FunctionTest, EmptyArgRad) {
    string func="math.rad";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsRad) {
    string func="math.rad";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, RadWithOneArgument) {
    string func="math.rad";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//randomseed
TEST_F(FunctionTest, EmptyArgRandomseed) {
    string func="math.randomseed";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsRandomseed) {
    string func="math.randomseed";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, RandomseedWithOneArgument) {
    string func="math.randomseed";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//sin
TEST_F(FunctionTest, EmptyArgSin) {
    string func="math.sin";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsSin) {
    string func="math.sin";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, SinWithOneArgument) {
    string func="math.sin";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//sinh
TEST_F(FunctionTest, EmptyArgSinh) {
    string func="math.sinh";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsSinh) {
    string func="math.sinh";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, SinhWithOneArgument) {
    string func="math.sinh";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//sqrt
TEST_F(FunctionTest, EmptyArgSqrt) {
    string func="math.sqrt";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsSqrt) {
    string func="math.sqrt";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, SqrtWithOneArgument) {
    string func="math.sqrt";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//tan
TEST_F(FunctionTest, EmptyArgTan) {
    string func="math.tan";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsTan) {
    string func="math.tan";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, TanWithOneArgument) {
    string func="math.tan";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//tanh
TEST_F(FunctionTest, EmptyArgTanh) {
    string func="math.tanh";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsTanh) {
    string func="math.tanh";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, TanhWithOneArgument) {
    string func="math.tanh";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//tointeger
TEST_F(FunctionTest, EmptyArgTointeger) {
    string func="math.tointeger";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsTointeger) {
    string func="math.tointeger";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, TointegerWithOneArgument) {
    string func="math.tointeger";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//type
TEST_F(FunctionTest, EmptyArgType) {
    string func="math.type";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsType) {
    string func="math.type";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, TypeWithOneArgument) {
    string func="math.type";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//ult
TEST_F(FunctionTest, EmptyArgUlt) {
    string func="math.ult";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsUlt) {
    string func="math.ult";
    int arg =3;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, UltWithTwoArgument) {
    string func="math.ult";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}

//set
TEST_F(FunctionTest, EmptyArgSet) {
    string func="set";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsSet) {
    string func="set";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, SetWithOneArgument) {
    string func="set";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//self
TEST_F(FunctionTest, LotOfArgumentsSelf) {
    string func="self";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, SelfWithNullArgument) {
    string func="self";
    int arg =0;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//update
TEST_F(FunctionTest, EmptyArgUpdate) {
    string func="update";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsUpdate) {
    string func="update";
    int arg =2;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, UpdateWithOneArgument) {
    string func="update";
    int arg =1;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//delay
TEST_F(FunctionTest, EmptyArgDelay) {
    string func="delay";
    int arg =0;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, LotOfArgumentsDelay) {
    string func="delay";
    int arg =3;
    ASSERT_THROW(test.FunctionParse(func,arg), std::invalid_argument);
}

TEST_F(FunctionTest, DelayWithTwoArgument) {
    string func="delay";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//Проверить еще на какие-то ошибки 
//пусть будет не только функция
//??
TEST_F(FunctionTest, NoOneFunc) {
    string func="delay   if";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
// Две функции с одинаковым кол аргументов
TEST_F(FunctionTest, TwoFunc) {
    string func="delay  math.pow";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
//С разным кол аргументов
TEST_F(FunctionTest, TwoFuncDefArg) {
    string func="delay  update";
    int arg =2;
    ASSERT_NO_THROW(test.FunctionParse(func,arg));
}
