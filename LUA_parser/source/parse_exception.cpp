#include "../include/parse_exception.h"

ParseException::ParseException(const std::string &msg) : message_(msg), error_index_(0)
{
}

ParseException::ParseException(const std::string &msg, size_t index)
    : message_(msg), error_index_(index)
{
}

const char *ParseException::what() const noexcept
{
    return message_.c_str();
}

size_t ParseException::getErrorIndex() const noexcept
{
    return error_index_;
}