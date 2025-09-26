#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include "../include/tree_node.h"

/**
 * @brief Дерево
 */
class Tree
{
   private:
    std::unique_ptr<TreeNode> root_;

   public:
    /**
     * @brief Конструктор дерева
     */
    Tree();

    /**
     * @brief Создание дерева с корневым узлом
     * @param rootData данные корневого узла
     * @return Указатель на корневой узел
     */
    TreeNode* Create(const NodeData& rootData);

    /**
     * @brief Очистка дерева
     */
    void Clear();

    /**
     * @brief Рекурсивный вывод дерева в консоль
     * @param node узел для вывода
     * @param depth глубина вложенности (для отступов)
     */
    void PrintTree(const TreeNode& node, int depth = 0) const;
};

#endif  // PARSE_TREE_H