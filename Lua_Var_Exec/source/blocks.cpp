#include "../include/blocks.h"

Blocks::Blocks()
{
}

std::vector<std::string> Blocks::CompletedBlocks(std::vector<std::string>& markers,
                                                 RimTir::LuaWrapper luaWrapper)
{
    std::vector<std::string> blocks;

    std::lock_guard<std::mutex> lock(RimTir::LuaWrapper::lua_mutex_);
    double value;

    for (size_t i = 0; i < markers.size(); i++)
    {
        std::string var = "MARKER" + std::to_string(i);
        luaWrapper.GetVariableLuaValue(RimTir::DataType::int32, var, value);
        if (static_cast<int>(value) > 0)
        {
            blocks.push_back(markers[i]);
        }
    }

    return blocks;
}