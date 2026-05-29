/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** DESCRIPTION
*/

#include "Json.hpp"

namespace JSON {
    bool JSON::parseArrayElement(
        std::string_view json, size_t &pos, JsonArray &arr)
    {
        auto value = parseValue(json, pos);
        if (!value)
            return false;
        arr.push_back(std::move(*value));
        return true;
    }

    std::optional<bool> JSON::parseArrayDelimiter(
        std::string_view json, size_t &pos) noexcept
    {
        skipWhitespace(json, pos);
        if (consumeChar(json, pos, ']'))
            return true;
        if (consumeChar(json, pos, ',')) {
            skipWhitespace(json, pos);
            return false;
        }
        return std::nullopt;
    }

    std::optional<JSON> JSON::parseArray(std::string_view json, size_t &pos)
    {
        if (!consumeChar(json, pos, '['))
            return std::nullopt;

        JsonArray arr;
        skipWhitespace(json, pos);
        if (consumeChar(json, pos, ']'))
            return JSON(std::move(arr));

        bool done = false;
        while (!done) {
            if (!parseArrayElement(json, pos, arr))
                return std::nullopt;

            auto delimiter = parseArrayDelimiter(json, pos);
            if (!delimiter)
                return std::nullopt;
            if (*delimiter)
                done = true;
        }
        return JSON(std::move(arr));
    }
} // namespace JSON
