/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** DESCRIPTION
*/

#include "Json.hpp"

#include <cctype>
#include <cstdlib>

namespace JSON {
    std::optional<JSON> JSON::parseNumber(std::string_view json, size_t &pos)
    {
        const size_t start = pos;

        if (pos < json.size() && json[pos] == '-')
            ++pos;
        if (!parseIntegerPart(json, pos) || !parseFractionPart(json, pos) ||
            !parseExponentPart(json, pos))
            return std::nullopt;

        auto value = numberToDouble(json, start, pos);
        if (!value)
            return std::nullopt;
        return JSON(*value);
    }

    bool JSON::parseIntegerPart(std::string_view json, size_t &pos) noexcept
    {
        if (pos >= json.size())
            return false;
        if (json[pos] == '0') {
            ++pos;
            return pos >= json.size() ||
                !std::isdigit(static_cast<unsigned char>(json[pos]));
        }
        if (!std::isdigit(static_cast<unsigned char>(json[pos])))
            return false;
        while (pos < json.size() &&
            std::isdigit(static_cast<unsigned char>(json[pos])))
            ++pos;
        return true;
    }

    bool JSON::parseFractionPart(std::string_view json, size_t &pos) noexcept
    {
        if (pos >= json.size() || json[pos] != '.')
            return true;

        ++pos;
        if (pos >= json.size() ||
            !std::isdigit(static_cast<unsigned char>(json[pos])))
            return false;
        while (pos < json.size() &&
            std::isdigit(static_cast<unsigned char>(json[pos])))
            ++pos;
        return true;
    }

    bool JSON::parseExponentPart(std::string_view json, size_t &pos) noexcept
    {
        if (pos >= json.size() || (json[pos] != 'e' && json[pos] != 'E'))
            return true;

        ++pos;
        if (pos < json.size() && (json[pos] == '+' || json[pos] == '-'))
            ++pos;
        if (pos >= json.size() ||
            !std::isdigit(static_cast<unsigned char>(json[pos])))
            return false;
        while (pos < json.size() &&
            std::isdigit(static_cast<unsigned char>(json[pos])))
            ++pos;
        return true;
    }

    std::optional<double> JSON::numberToDouble(
        std::string_view json, size_t start, size_t end) noexcept
    {
        std::string numberStr(json.substr(start, end - start));
        char *parseEnd = nullptr;
        const double value = std::strtod(numberStr.c_str(), &parseEnd);

        if (parseEnd == nullptr || *parseEnd != '\0')
            return std::nullopt;
        return value;
    }
} // namespace JSON
