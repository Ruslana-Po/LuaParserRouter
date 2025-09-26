#ifndef PARSE_STR_H
#define PARSE_STR_H

#include <algorithm>
#include <iostream>
#include <vector>

#include "parse_exception.h"
#include "tree.h"

class StringManipulation
{
   public:
    StringManipulation();

    /**
     * @brief Заменяет /n на пробел, убирает повторяющиеся пробелы, оборачивает строку пробелами
     * @return Обработанная строка
     * @param input исходная строка
     */
    std::string ProcessString(const std::string& input);

    /**
     * @brief Ищет вхождение if then / elseif then, обрезает вхождение если нашел
     * @return Найдено ли вхождение
     * @param str строка для поиска
     * @param conOperator конкретный оператор для поиска
     */
    bool CheckWithThenString(std::string& str, const std::string& conOperator);

    /**
     * @brief Ищет вхождение if then / end / elseif then / else, обрезает вхождение если нашел
     * @return Найдено ли вхождение
     * @param str строка для поиска
     */
    bool CheckIfThenString(std::string& str);
    bool CheckEndString(std::string& str);
    bool CheckElseifThenString(std::string& str);
    bool CheckElseString(std::string& str);

    /**
     * @brief Поиск условного поиск индекса первого вхождения в строке одной из подстрок
     * @return Индекс первого вхождения
     * @param str строка для поиска
     * @param patterns вектор подстрок
     * @param startPos индекс стартовой позиции для поиска
     */
    size_t FindFirstPattern(const std::string& str,
                            const std::vector<std::string>& patterns,
                            size_t startPos);

    /**
     * @brief Поиск условного оператора if then / elseif then / else в строке
     * @return Индекс символа после оператора
     * @param str строка для поиска
     * @param startPos индекс стартовой позиции для поиска
     */
    size_t FindIfThen(const std::string& str, size_t startPos);
    size_t FindElseifThen(const std::string& str, size_t startPos);
    size_t FindElse(const std::string& str, size_t startPos);
};

#endif  // PARSE_STR_H