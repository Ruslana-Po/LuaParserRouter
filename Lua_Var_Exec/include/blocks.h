#ifndef PARSE_BLOCKS_H
#define PARSE_BLOCKS_H

#include <vector>

#include "../LuaWrapper.h"

class Blocks
{
   public:
    Blocks();

    /** 
     * @brief Находит пройденные маркеры
     * @return Вектор с выполненными маркерами
     * @param markers вектор всех блоков кода в которых расставлены маркеры
     * @param luaWrapper объект, содержащий информацию о значениях переменных
     */
    std::vector<std::string> CompletedBlocks(std::vector<std::string>& markers,
                                             RimTir::LuaWrapper luaWrapper);
};


#endif  // PARSE_BLOCKS_H