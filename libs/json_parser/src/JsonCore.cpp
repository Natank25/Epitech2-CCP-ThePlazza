/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** DESCRIPTION
*/

#include "Json.hpp"

#include <cctype>
#include <fstream>
#include <iterator>

namespace JSON {
    void JSON::skipWhitespace(std::string_view json, size_t &pos) noexcept
    {
        while (pos < json.size() &&
            std::isspace(static_cast<unsigned char>(json[pos])))
            ++pos;
    }

    bool JSON::consumeChar(std::string_view json, size_t &pos, char c) noexcept
    {
        if (pos >= json.size() || json[pos] != c)
            return false;
        ++pos;
        return true;
    }

    bool JSON::matchLiteral(
        std::string_view json, size_t &pos, std::string_view literal) noexcept
    {
        if (json.substr(pos, literal.size()) != literal)
            return false;
        pos += literal.size();
        return true;
    }

    std::optional<JSON> JSON::parseTrue(std::string_view json, size_t &pos)
    {
        if (!matchLiteral(json, pos, "true"))
            return std::nullopt;
        return JSON(true);
    }

    std::optional<JSON> JSON::parseFalse(std::string_view json, size_t &pos)
    {
        if (!matchLiteral(json, pos, "false"))
            return std::nullopt;
        return JSON(false);
    }

    std::optional<JSON> JSON::parseNull(std::string_view json, size_t &pos)
    {
        if (!matchLiteral(json, pos, "null"))
            return std::nullopt;
        return JSON();
    }

    std::optional<JSON> JSON::parseValue(std::string_view json, size_t &pos)
    {
        skipWhitespace(json, pos);
        if (pos >= json.size())
            return std::nullopt;

        const char c = json[pos];
        if (std::isdigit(static_cast<unsigned char>(c)))
            return parseNumber(json, pos);

        const auto parser = VALUE_PARSERS.find(c);
        if (parser == VALUE_PARSERS.end())
            return std::nullopt;
        return parser->second(json, pos);
    }

    std::optional<JSON> JSON::parse(std::string_view json)
    {
        size_t pos = 0;
        auto value = parseValue(json, pos);

        if (!value)
            return std::nullopt;
        skipWhitespace(json, pos);
        if (pos != json.size())
            return std::nullopt;
        return value;
    }

    std::optional<JSON> JSON::parseStream(std::istream &stream)
    {
        const std::string json((std::istreambuf_iterator<char>(stream)),
            std::istreambuf_iterator<char>());

        if (stream.bad())
            return std::nullopt;
        return parse(json);
    }

    std::optional<JSON> JSON::parseFile(std::string_view path)
    {
        std::ifstream file {std::string(path)};

        if (!file.is_open())
            return std::nullopt;
        return parseStream(file);
    }

    const std::unordered_map<char, JSON::ValueParser> JSON::VALUE_PARSERS = {
        {'{', &JSON::parseObject},
        {'[', &JSON::parseArray},
        {'"', &JSON::parseString},
        {'-', &JSON::parseNumber},
        {'t', &JSON::parseTrue},
        {'f', &JSON::parseFalse},
        {'n', &JSON::parseNull}};
} // namespace JSON
