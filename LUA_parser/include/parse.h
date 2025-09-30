#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <vector>

#include "check_func.h"
#include "lua_parser.h"
#include "str.h"

class ParseCode
{
   private:
    static const int kElseifLength = 6;
    static const int kElseLength = 4;
    static const int kThenLength = 4;
    static const int kIfLength = 4;

    /**
     * @brief Парсит строку с кодом в дерево
     * @return Успешность парсинга
     * @param root корневой узел дерева
     * @param work_str строка с кодом
     */
    bool ParseTree(TreeNode &root, std::string &work_str);

   public:
    ParseCode();

    /**
     * @brief Парсинг кода и получение списка всех переменных кода
     * @param input исходная строка с кодом
     * @param variables все переменные, которые есть в коде
     */
    void CodeParse(std::string &input, std::vector<std::string> &variables);

    /**
     * @brief Парсинг строк кода без условных конструкций
     * @param root корень дерева кода
     */
    void ParseBody(TreeNode *root);

    /**
     * @brief Проверка правильного количества аргументов функции и существования
     * функции
     * @param root корень дерева кода
     */
    void CheckFunc(TreeNode *root);

    /**
     * @brief Получение переменных из кода
     * @param root корень дерева кода
     * @param variables все переменные, которые есть в коде
     */
    void Variables(TreeNode *root, std::vector<std::string> &variables);
};

#endif  // PARSE_H