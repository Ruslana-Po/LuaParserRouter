#include "../include/check_func.h"

Function::Function()
{
    mathFunctions = {
                     {"math.abs", {1}},
                     {"math.acos", {1}},
                     {"math.asin", {1}},
                     {"math.atan", {1, 2}},  // atan может принимать 1 или 2 аргумента
                     {"math.atan2", {2}},
                     {"math.ceil", {1}},
                     {"math.cos", {1}},
                     {"math.cosh", {1}},
                     {"math.deg", {1}},
                     {"math.exp", {1}},
                     {"math.floor", {1}},
                     {"math.fmod", {2}},
                     {"math.frexp", {1}},
                     {"math.huge", {0}},
                     {"math.ldexp", {2}},
                     {"math.log", {1, 2}},  // log может принимать 1 или 2 аргумента
                     {"math.log10", {1}},
                     {"math.max", {2, -1}},  // -1 означает переменное количество аргументов (≥2)
                     {"math.min", {2, -1}},
                     {"math.modf", {1}},
                     {"math.pi", {0}},
                     {"math.pow", {2}},
                     {"math.rad", {1}},
                     {"math.random", {0, 1, 2}},
                     {"math.randomseed", {1}},
                     {"math.sin", {1}},
                     {"math.sinh", {1}},
                     {"math.sqrt", {1}},
                     {"math.tan", {1}},
                     {"math.tanh", {1}},
                     {"math.tointeger", {1}},
                     {"math.type", {1}},
                     {"math.ult", {2}},
                     {"set", {1}},
                     {"self", {0}},
                     {"update", {1}},
                     {"delay", {2}}};
}

void Function::FunctionParse(const std::string &functionName, int argCount)
{
    // Ищем функцию в словаре
    auto it = mathFunctions.find(functionName);
    if (it == mathFunctions.end())
    {
        throw std::invalid_argument(
            "Функция '" + functionName +
            "' не найдена в библиотеке math и библиотеке кастомных функций");
    }

    const std::vector<int> &validArgCounts = it->second;

    // Проверяем количество аргументов
    bool isValid = false;

    for (int validCount : validArgCounts)
    {
        if (validCount == -1)
        {
            // Специальный случай: переменное количество аргументов (≥2)
            if (argCount >= 2)
            {
                isValid = true;
                break;
            }
        }
        else if (argCount == validCount)
        {
            isValid = true;
            break;
        }
    }

    if (!isValid)
    {
        std::string errorMsg =
            "Неверное количество аргументов для функции '" + functionName + "'. Ожидается: ";

        for (size_t i = 0; i < validArgCounts.size(); ++i)
        {
            if (validArgCounts[i] == -1)
            {
                errorMsg += "≥2 аргументов";
            }
            else
            {
                errorMsg +=
                    std::to_string(validArgCounts[i]) + " аргумент" + getSuffix(validArgCounts[i]);
            }

            if (i < validArgCounts.size() - 1)
            {
                errorMsg += " или ";
            }
        }

        throw std::invalid_argument(errorMsg);
    }
}

std::string Function::getSuffix(int count) const
{
    if (count % 10 == 1 && count % 100 != 11)
        return "";
    if (count % 10 >= 2 && count % 10 <= 4 && (count % 100 < 10 || count % 100 >= 20))
        return "а";
    return "ов";
}