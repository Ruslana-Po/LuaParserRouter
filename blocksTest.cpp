#include <gtest/gtest.h>
#include "Lua_Var_Exec/include/blocks.h"
using namespace std;

class BlocksIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Инициализируем Lua состояние
        luaWrapper.InitializeLuaState();
    }
    
    void SetCustomMarkerValues(const vector<int>& values) {
        lock_guard<mutex> lock(RimTir::LuaWrapper::lua_mutex_);
        
        for (size_t i = 0; i < values.size(); i++) {
            string markerName = "MARKER" + to_string(i);
            string valueStr = to_string(values[i]);
            luaWrapper.ExecLua(markerName, valueStr);
        }
    }
    
    RimTir::LuaWrapper luaWrapper;
    Blocks blocks;
};

TEST_F(BlocksIntegrationTest, AllBlocksCompleted) {
    SetCustomMarkerValues({1, 2, 3, 4});
    // Используем те же имена, что устанавливались в SetCustomMarkerValues
    vector<string> markers = {"MARKER0", "MARKER1", "MARKER2", "MARKER3"};
    EXPECT_EQ(blocks.CompletedBlocks(markers, luaWrapper).size(), 4);
}

TEST_F(BlocksIntegrationTest, MixedValues) {
    SetCustomMarkerValues({0, 1, 0, 1, 0, 1});
    vector<string> markers = {"MARKER0", "MARKER1", "MARKER2", "MARKER3", "MARKER4", "MARKER5"};
    // Ожидаем только те маркеры, у которых значение 1 (ненулевое)
    EXPECT_EQ(blocks.CompletedBlocks(markers, luaWrapper).size(), 3);
}

TEST_F(BlocksIntegrationTest, EmptyMarkersList) {
    vector<string> markers = {};
    EXPECT_TRUE(blocks.CompletedBlocks(markers, luaWrapper).empty());
}

TEST_F(BlocksIntegrationTest, NegativeValuesIgnored) {
    SetCustomMarkerValues({-1, -5, -10});
    vector<string> markers = {"MARKER0", "MARKER1", "MARKER2"};
    // Ожидаем, что отрицательные значения будут проигнорированы
    EXPECT_TRUE(blocks.CompletedBlocks(markers, luaWrapper).empty());
}

TEST_F(BlocksIntegrationTest, FractionalMarkerValues) {
    SetCustomMarkerValues({10000000, 9999999});
    vector<string> markers = {"MARKER0", "MARKER1"};
    EXPECT_EQ(blocks.CompletedBlocks(markers, luaWrapper).size(), 2);
}

TEST_F(BlocksIntegrationTest, NonExistentLuaVariables) {
    // Не устанавливаем никаких значений - переменные не существуют
    vector<string> markers = {"MARKER0", "MARKER1"};
    EXPECT_TRUE(blocks.CompletedBlocks(markers, luaWrapper).empty());
}
