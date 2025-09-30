#ifndef CHECK_FUNCTION_H
#define CHECK_FUNCTION_H

#include <algorithm>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class Function
{
   private:
    std::unordered_map<std::string, std::vector<int>> mathFunctions;

    /**
     * @brief Получение правильного окончания для слова "аргумент" в зависимости от числа
     * @param count количество аргументов
     * @return Строка с правильным окончанием ("", "а" или "ов")
     */
    std::string getSuffix(int count) const;

   public:
    /**
     * @brief Конструктор класса Function
     * @details Инициализирует словарь функций с допустимыми количествами аргументов
     */
    Function();

    /**
     * @brief Парсинг и проверка математической функции
     * @param functionName имя функции
     * @param argCount количество переданных аргументов
     * @throw если функция не найдена или неверное количество аргументов
     * @details Проверяет существование функции в библиотеке и корректность количества аргументов
     */
    void FunctionParse(const std::string &functionName, int argCount);
};

#endif  // CHECK_FUNCTION_H