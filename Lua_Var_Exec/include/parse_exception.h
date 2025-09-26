#ifndef PARSE_EXCEPTION_H
#define PARSE_EXCEPTION_H

#include <exception>
#include <string>

/**
 * @class ParseException
 * @brief класс исключения для обработки ошибок
 * наследуется от std::exception
 */

class ParseException : public std::exception
{
   private:
    std::string message_;

   public:
    /**
     * @brief конструктор с параметром
     * @param msg сообщение об ошибке
     */
    explicit ParseException(const std::string& msg);

    /**
     * @brief возвращает сообщение об ошибке
     * @return указатель на строку с сообщением
     */
    const char* what() const noexcept override;

    /**
     * @brief виртуальный деструктор для корректного наследования
     */
    virtual ~ParseException() noexcept = default;
};

#endif  // PARSE_EXCEPTION_H
