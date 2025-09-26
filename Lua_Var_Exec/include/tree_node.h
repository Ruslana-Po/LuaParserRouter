#ifndef PARSE_TREENODE_H
#define PARSE_TREENODE_H

#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief Типы узлов дерева разбора
 */
enum class NodeType
{
    IF,
    ELSE,
    ELSEIF,
    ROOT
};

/**
 * @brief Данные узла дерева
 */
struct NodeData
{
    std::string content;
    NodeType type;

    /**
     * @brief Конструктор данных узла
     * @param str содержимое узла
     * @param t тип узла
     */
    NodeData(const std::string& str = "", NodeType t = NodeType::ROOT) : content(str), type(t)
    {
    }

    /**
     * @brief Добавление текста к содержимому узла
     * @param additional дополнительный текст
     */
    void AppendContent(const std::string& additional);
};

/**
 * @brief узел дерева
 */
class TreeNode
{
   private:
    NodeData data_;
    std::vector<std::unique_ptr<TreeNode>> children_;

   public:
    /**
     * @brief Лонструктор узла
     * @param nodeData данные для создания узла
     */
    TreeNode(const NodeData& nodeData);

    /**
     * @brief Добавление существующего узла как ребенка (передача владения)
     * @param child unique_ptr на дочерний узел (владение передается)
     * @return Указатель на добавленный дочерний узел
     */
    TreeNode* AddChild(std::unique_ptr<TreeNode> child);

    /**
     * @brief Дополнение строки в данных текущего узла
     * @param additional дополнительный текст
     */
    void AppendToContent(const std::string& additional);

    /**
     * @brief Получение данных узла
     * @return Ссылка на данные узла
     */
    const NodeData& GetData() const;

    /**
     * @brief Получение дочерних узлов
     * @return Ссылка на вектор дочерних узлов
     */
    const std::vector<std::unique_ptr<TreeNode>>& GetChildren() const;

    /**
     * @brief Очистка всех дочерних узлов
     */
    void Clear();
};

#endif  // PARSE_TREENODE_H