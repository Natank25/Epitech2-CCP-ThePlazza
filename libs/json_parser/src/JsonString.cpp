/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** DESCRIPTION
*/

#include "Json.hpp"

namespace JSON {
    std::optional<JSON> JSON::parseString(std::string_view json, size_t &pos)
    {
        if (!consumeChar(json, pos, '"'))
            return std::nullopt;

        std::string out;

        while (pos < json.size()) {
            auto done = parseStringCharacter(json, pos, out);

            if (!done)
                return std::nullopt;
            if (*done)
                return JSON(std::move(out));
        }
        return std::nullopt;
    }

    std::optional<char> JSON::parseEscapedChar(
        std::string_view json, size_t &pos) noexcept
    {
        if (pos >= json.size())
            return std::nullopt;

        const char escape = json[pos++];
        const auto it = ESCAPE_CHARS.find(escape);

        if (it == ESCAPE_CHARS.end())
            return std::nullopt;
        return it->second;
    }

    std::optional<bool> JSON::parseStringCharacter(
        std::string_view json, size_t &pos, std::string &out)
    {
        const char c = json[pos++];

        if (c == '"')
            return true;
        if (static_cast<unsigned char>(c) < 0x20)
            return std::nullopt;
        if (c != '\\') {
            out.push_back(c);
            return false;
        }

        auto escaped = parseEscapedChar(json, pos);
        if (!escaped)
            return std::nullopt;
        out.push_back(*escaped);
        return false;
    }

    const std::unordered_map<char, char> JSON::ESCAPE_CHARS = {{'"', '"'},
        {'\\', '\\'},
        {'/', '/'},
        {'b', '\b'},
        {'f', '\f'},
        {'n', '\n'},
        {'r', '\r'},
        {'t', '\t'}};
} // namespace JSON
