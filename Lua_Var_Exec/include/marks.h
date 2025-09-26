#ifndef PARSE_MARKS_H
#define PARSE_MARKS_H

#include <string>
#include <vector>

#include "str.h"

class AddMarkers
{
   private:
    /**
     * @brief Парсит строку с кодом в дерево
     * @return Успешность парсинга
     * @param root корневой узел дерева
     * @param work_str строка с кодом
     */
    bool ParseTree(TreeNode& root, std::string& work_str);

    /**
     * @brief Создает вектор с блоками кода и вставляет в код маркеры
     * @param root корневой узел дерева
     * @param result_str строка с исходным кодом
     * @param start_str стартовый индекс для поиска условных операторов (изначально 0)
     * @param marker_num номер маркера для вставки (изначально 0)
     * @param blocks вектор для блоков кода
     */
    void Travers(TreeNode* root,
                 std::string& result_str,
                 size_t& start_str,
                 int& marker_num,
                 std::vector<std::string>& blocks);

    /**
     * @brief Проверяет правильность парных параметров в блоке кода
     * @return Правильность парных параметров
     * @param root корневой узел дерева
     * @param first_param открывающий параметр
     * @param second_param закрывающий параметр
     */
    bool FindParam(TreeNode* root, const std::string& first_param, const std::string& second_param);

   public:
    AddMarkers();

    /**
     * @brief Добавляет в код маркеры, создает вектор блоков
     * @return Код с маркерами
     * @param input исходная строка с кодом
     * @param blocks вектор для блоков
     */
    void AddCodeMarkers(std::string& input, std::vector<std::string>& blocks);
};


#endif  // PARSE_MARKS_H