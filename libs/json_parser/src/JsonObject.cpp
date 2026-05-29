/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** DESCRIPTION
*/

#include "Json.hpp"

namespace JSON {
    bool JSON::parseObjectMember(
        std::string_view json, size_t &pos, JsonObject &obj)
    {
        auto keyJson = parseString(json, pos);
        if (!keyJson || !keyJson->is<std::string>())
            return false;
        std::string key = std::move(keyJson->as<std::string>());

        skipWhitespace(json, pos);
        if (!consumeChar(json, pos, ':'))
            return false;
        skipWhitespace(json, pos);

        auto value = parseValue(json, pos);
        if (!value)
            return false;
        obj.emplace_back(std::move(key), std::move(*value));
        return true;
    }

    std::optional<bool> JSON::parseObjectDelimiter(
        std::string_view json, size_t &pos) noexcept
    {
        skipWhitespace(json, pos);
        if (consumeChar(json, pos, '}'))
            return true;
        if (consumeChar(json, pos, ',')) {
            skipWhitespace(json, pos);
            return false;
        }
        return std::nullopt;
    }

    std::optional<JSON> JSON::parseObject(std::string_view json, size_t &pos)
    {
        if (!consumeChar(json, pos, '{'))
            return std::nullopt;

        JsonObject obj;
        skipWhitespace(json, pos);
        if (consumeChar(json, pos, '}'))
            return JSON(std::move(obj));

        bool done = false;
        while (!done) {
            if (!parseObjectMember(json, pos, obj))
                return std::nullopt;

            auto delimiter = parseObjectDelimiter(json, pos);
            if (!delimiter)
                return std::nullopt;
            if (*delimiter)
                done = true;
        }
        return JSON(std::move(obj));
    }
} // namespace JSON
