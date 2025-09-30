#ifndef PARSE_EXCEPTION_H
#define PARSE_EXCEPTION_H

#include <exception>
#include <string>

/**
 * @class ParseException
 * @brief класс исключения для обработки ошибок с индексом
 * наследуется от std::exception
 */

class ParseException : public std::exception
{
   private:
    std::string message_;
    size_t error_index_;

   public:
    /**
     * @brief конструктор с параметром (только сообщение)
     * @param msg сообщение об ошибке
     */
    explicit ParseException(const std::string &msg);

    /**
     * @brief конструктор с параметрами (сообщение и индекс)
     * @param msg сообщение об ошибке
     * @param index индекс ошибки
     */
    explicit ParseException(const std::string &msg, size_t index);

    /**
     * @brief возвращает сообщение об ошибке
     * @return указатель на строку с сообщением
     */
    const char *what() const noexcept override;

    /**
     * @brief возвращает индекс ошибки
     * @return индекс ошибки
     */
    size_t getErrorIndex() const noexcept;

    /**
     * @brief виртуальный деструктор для корректного наследования
     */
    virtual ~ParseException() noexcept = default;
};

#endif  // PARSE_EXCEPTION_H