#include "../include/str.h"

const int kThenLength = 4;
const int kIfLength = 2;
const int kElseifLength = 6;
const int kElseLength = 4;
const int kEndLength = 3;

/* преобразование строки, убрать переносы, убрать лишние пробелы */

StringManipulation::StringManipulation()
{
}

std::string StringManipulation::ProcessString(const std::string &input)
{
    std::string result = input;

    // переносы строк на пробелы
    replace(result.begin(), result.end(), '\n', ' ');

    result = result + " ";

    return result;
}

/* проверка правильности условных операторов и их обрезка */

bool StringManipulation::CheckWithThenString(std::string &str,
                                             const std::string &conOperator,
                                             std::string &condition)
{
    if (str.size() < conOperator.size() + 2 ||
        (str.substr(0, conOperator.size() + 2) != " " + conOperator + " " &&
         str.substr(0, conOperator.size() + 2) != " " + conOperator + "("))
    {
        return false;
    }

    size_t thenPos = str.find("then ");
    if (thenPos == std::string::npos)
    {
        throw ParseException("then не найдено", str.size());
    }
    // Проверяем, что "then" стоит как отдельное слово
    while (thenPos > 0 && str[thenPos - 1] != ' ' && str[thenPos - 1] != ')')
    {
        thenPos += kThenLength;
        thenPos = str.find("then ", thenPos);
        if (thenPos == std::string::npos)
        {
            throw ParseException("then не найдено", str.size());
        }
    }

    condition = str.substr(conOperator.size() + 1, thenPos - (conOperator.size() + 1));

    std::vector<std::string> forbidden = {
        " if ", " else ", " elseif ", " end ", " if(", " elseif("};

    for (const auto &word : forbidden)
    {
        if (condition.find(word) != std::string::npos)
        {
            throw ParseException("ошибка в конструкции " + conOperator + " then", str.size() - 1);
        }
    }

    size_t afterThenPos = thenPos + kThenLength + 1;
    std::string str_without_then =
        (afterThenPos < str.length()) ? str.substr(afterThenPos - 1) : "";

    str = str_without_then;

    return true;
}

bool StringManipulation::CheckIfThenString(std::string &str, std::string &condition)
{
    return CheckWithThenString(str, "if", condition);
}

bool StringManipulation::CheckElseifThenString(std::string &str, std::string &condition)
{
    return CheckWithThenString(str, "elseif", condition);
}

bool StringManipulation::CheckEndString(std::string &str)
{
    if (str.find(" end") != 0)
    {
        return false;
    }

    if (str == " end")
    {
        str.clear();
        return true;
    }

    if (str.size() >= kEndLength + 2 && str[kEndLength + 1] == ' ')
    {
        std::string str_without_end = str.substr(kEndLength + 1);  // Обрезаем " end"
        str = str_without_end;
        return true;
    }

    // Если после "end" нет пробела, но есть другие символы
    return false;
}

bool StringManipulation::CheckElseString(std::string &str)
{
    if (str.size() < kElseLength + 2)
    {
        return false;
    }

    if (str.substr(0, kElseLength + 2) != " else ")
    {
        return false;
    }

    std::string str_without_else = str.substr(kElseLength + 1);
    str = str_without_else;

    return true;
}

/* поиск условного оператора в строке и возврат индекса */

size_t StringManipulation::FindFirstPattern(const std::string &str,
                                            const std::vector<std::string> &patterns,
                                            size_t startPos)
{
    size_t patternPos = std::string::npos;
    for (const auto &pattern : patterns)
    {
        size_t pos = str.find(pattern, startPos);
        if (pos != std::string::npos && (patternPos == std::string::npos || pos < patternPos))
        {
            patternPos = pos;
        }
    }
    return patternPos;
}

size_t StringManipulation::FindIfThen(const std::string &str, size_t startPos)
{
    std::vector<std::string> patterns = {"\nif ", "\nif(", " if ", " if("};
    size_t ifPos = FindFirstPattern(str, patterns, startPos);
    if (ifPos == std::string::npos)
    {
        return std::string::npos;
    }

    patterns = {")then\n", " then\n", ")then ", " then "};
    size_t thenPos = FindFirstPattern(str, patterns, ifPos + kIfLength);
    if (thenPos == std::string::npos)
    {
        return std::string::npos;
    }

    return thenPos + kThenLength + 1;
}

size_t StringManipulation::FindElseifThen(const std::string &str, size_t startPos)
{
    std::vector<std::string> patterns = {"\nelseif ", "\nelseif(", " elseif ", " elseif("};
    size_t elseifPos = FindFirstPattern(str, patterns, startPos);
    if (elseifPos == std::string::npos)
    {
        return std::string::npos;
    }

    patterns = {")then\n", " then\n", ")then ", " then "};
    size_t thenPos = FindFirstPattern(str, patterns, elseifPos + kElseifLength);
    if (thenPos == std::string::npos)
    {
        return std::string::npos;
    }

    return thenPos + kThenLength + 1;
}

size_t StringManipulation::FindElse(const std::string &str, size_t startPos)
{
    std::vector<std::string> patterns = {"\nelse\n", "\nelse ", " else\n", " else "};
    size_t elsePos = FindFirstPattern(str, patterns, startPos);
    if (elsePos == std::string::npos)
    {
        return std::string::npos;
    }

    return elsePos + kElseLength + 1;
}
