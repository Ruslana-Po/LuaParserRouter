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
    ROOT,
    BODY,
    CONDITION,
    THEN,
    NUMBER,
    STRING,
    VARIABLE,
    FUNCTION,
    OPERATOR_BINARY,
    OPERATOR_UNARY,
    OPERATOR_ASSIGNMENT,
    OPERATOR_CONDITIONAL,
    PARENTHESIS_OPEN,
    PARENTHESIS_CLOSE,
    EXPRESSION
};

/**
 * @brief Данные узла дерева
 */
struct NodeData
{
    std::string content;
    NodeType type;
    int index;

    /**
     * @brief Конструктор данных узла
     * @param str содержимое узла
     * @param t тип узла
     */
    NodeData(const std::string &str = "", NodeType t = NodeType::ROOT, int i = 0)
        : content(str), type(t), index(i)
    {
    }

    /**
     * @brief Добавление текста к содержимому узла
     * @param additional дополнительный текст
     */
    void AppendContent(const std::string &additional);

    /**
     * @brief Очистка содержимого строки
     */
    void ClearData();

    /**
     * @brief Изменение индекса
     * @param new_index новый индекс
     */
    void NewIndex(int new_index);
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
     * @brief Конструктор узла
     * @param nodeData данные для создания узла
     */
    TreeNode(const NodeData &nodeData);

    /**
     * @brief Добавление существующего узла как ребенка (передача владения)
     * @param child unique_ptr на дочерний узел (владение передается)
     * @return Указатель на добавленный дочерний узел
     */
    TreeNode *AddChild(const std::string &content, NodeType type = NodeType::BODY, int index = 0);

    /**
     * @brief Дополнение строки в данных текущего узла
     * @param additional дополнительный текст
     */
    void AppendToContent(const std::string &additional);

    /**
     * @brief Очистка строки в данных текущего узла
     */
    void ClearContent();

    /**
     * @brief Получение данных узла
     * @return Ссылка на данные узла
     */
    const NodeData &GetData() const;

    /**
     * @brief Изменение индекса
     * @param new_index новый индекс
     */
    void ChangeIndex(int new_index);

    /**
     * @brief Получение дочерних узлов
     * @return Ссылка на вектор дочерних узлов
     */
    const std::vector<std::unique_ptr<TreeNode>> &GetChildren() const;

    /**
     * @brief Очистка всех дочерних узлов
     */
    void Clear();
};

#endif  // PARSE_TREENODE_H