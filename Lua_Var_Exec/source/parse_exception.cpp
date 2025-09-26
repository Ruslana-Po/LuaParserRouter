#include "../include/parse_exception.h"

ParseException::ParseException(const std::string& msg) : message_(msg)
{
}

const char* ParseException::what() const noexcept
{
    return message_.c_str();
}