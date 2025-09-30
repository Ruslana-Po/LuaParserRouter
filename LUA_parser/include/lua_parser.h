#ifndef LUA_PARSER_H
#define LUA_PARSER_H

#include <string>
#include <unordered_set>

#include "parse_exception.h"
#include "tree.h"
#include "tree_node.h"

/**
 * @brief Простой парсер для разбора выражений
 */
class LuaParser
{
   private:
    std::string input_;
    size_t pos_;
    size_t global_offset_;

    const std::unordered_set<std::string> binary_operators_;
    const std::unordered_set<std::string> unary_operators_;
    const std::unordered_set<std::string> assignment_operators_;
    const std::unordered_set<std::string> conditional_operators_;

   public:
    /**
     * @brief Конструктор парсера
     */
    LuaParser();

    /**
     * @brief Парсинг строки и добавление детей к указанному узлу
     * @param parent узел, к которому добавляются дети
     * @throws ParseException в случае ошибки парсинга
     */
    void ParseStringToNode(TreeNode *parent);

   private:
    /**
     * @brief Генерация исключения с указанием индекса ошибки
     * @param message сообщение об ошибке
     * @throws ParseException исключение с сообщением и индексом
     */
    void ThrowError(const std::string &message);

    /**
     * @brief Пропуск пробельных символов
     */
    void SkipWhitespace();

    /**
     * @brief Получение текущего индекса с учетом глобального смещения
     * @return Текущий индекс в исходной строке
     */
    size_t GetCurrentIndex() const;

    /**
     * @brief Проверка на два оператора подряд
     * @param parent родительский узел для проверки детей
     * @throws ParseException если обнаружены два оператора подряд
     */
    void CheckConsecutiveOperators(TreeNode *parent);

    /**
     * @brief Парсинг выражения и добавление детей к родительскому узлу
     * @param parent родительский узел для добавления детей
     */
    void ParseExpression(TreeNode *parent);

    /**
     * @brief Парсинг аргументов функции (разделенных запятыми)
     * @param func_node узел функции для добавления аргументов
     */
    void ParseFunctionArguments(TreeNode *func_node);

    /**
     * @brief Парсинг числа и добавление как ребенка
     * @param parent родительский узел
     * @param start_index начальный индекс числа
     */
    void ParseNumber(TreeNode *parent, size_t start_index);

    /**
     * @brief Парсинг строки и добавление как ребенка
     * @param parent родительский узел
     * @param start_index начальный индекс строки
     */
    void ParseString(TreeNode *parent, size_t start_index);

    /**
     * @brief Парсинг идентификатора (переменная или функция)
     * @param parent родительский узел
     * @param start_index начальный индекс идентификатора
     */
    void ParseIdentifier(TreeNode *parent, size_t start_index);

    /**
     * @brief Парсинг скобок и создание дочернего выражения
     * @param parent родительский узел
     * @param start_index начальный индекс скобки
     */
    void ParseParenthesis(TreeNode *parent, size_t start_index);

    /**
     * @brief Парсинг оператора и добавление как ребенка
     * @param parent родительский узел
     * @param start_index начальный индекс оператора
     */
    void ParseOperator(TreeNode *parent, size_t start_index);

    /**
     * @brief Проверка, является ли символ оператором
     * @param c символ для проверки
     * @return true если символ может быть частью оператора
     */
    bool IsOperatorChar(char c) const;

    /**
     * @brief Проверка, является ли текущая позиция оператором
     * @param c символ для проверки
     * @return true если это оператор
     */
    bool IsOperator(char c) const;
};

#endif  // LUA_PARSER_H