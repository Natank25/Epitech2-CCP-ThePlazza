/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** DESCRIPTION
*/

#include "Json.hpp"

#include <iomanip>
#include <limits>
#include <stdexcept>

namespace JSON {
    void JSON::writeIndent(std::ostream &stream, size_t depth)
    {
        for (size_t i = 0; i < depth * INDENT_SIZE; ++i)
            stream.put(' ');
    }

    void JSON::writeEscapedString(std::ostream &stream, std::string_view value)
    {
        stream.put('"');
        for (unsigned char c : value) {
            auto escaped = ESCAPED_CHARS.find(c);

            if (escaped != ESCAPED_CHARS.end()) {
                stream << escaped->second;
                continue;
            }
            stream.put(static_cast<char>(c));
        }
        stream.put('"');
    }

    void JSON::writeNumber(std::ostream &stream, double number)
    {
        const auto previousPrecision = stream.precision();
        const auto previousFlags = stream.flags();

        stream << std::defaultfloat
               << std::setprecision(std::numeric_limits<double>::max_digits10)
               << number;
        stream.precision(previousPrecision);
        stream.flags(previousFlags);
    }

    void JSON::writeArray(
        std::ostream &stream, const JsonArray &array, size_t depth)
    {
        stream << "[\n";
        for (size_t i = 0; i < array.size(); ++i) {
            writeIndent(stream, depth + 1);
            writeValue(stream, array[i], depth + 1);
            if (i + 1 < array.size())
                stream.put(',');
            stream.put('\n');
        }
        writeIndent(stream, depth);
        stream.put(']');
    }

    void JSON::writeObject(
        std::ostream &stream, const JsonObject &object, size_t depth)
    {
        stream << "{\n";
        for (size_t i = 0; i < object.size(); ++i) {
            const auto &[key, value] = object[i];

            writeIndent(stream, depth + 1);
            writeEscapedString(stream, key);
            stream << ": ";
            writeValue(stream, value, depth + 1);
            if (i + 1 < object.size())
                stream.put(',');
            stream.put('\n');
        }
        writeIndent(stream, depth);
        stream.put('}');
    }

    void JSON::writeArrayCompact(std::ostream &stream, const JsonArray &array)
    {
        stream.put('[');
        for (size_t i = 0; i < array.size(); ++i) {
            array[i].writeValueCompact(stream);
            if (i + 1 < array.size())
                stream.put(',');
        }
        stream.put(']');
    }

    void JSON::writeObjectCompact(
        std::ostream &stream, const JsonObject &object)
    {
        stream.put('{');
        for (size_t i = 0; i < object.size(); ++i) {
            const auto &[key, value] = object[i];

            writeEscapedString(stream, key);
            stream.put(':');
            value.writeValueCompact(stream);
            if (i + 1 < object.size())
                stream.put(',');
        }
        stream.put('}');
    }

    void JSON::writeValue(std::ostream &stream, const JSON &value, size_t depth)
    {
        if (value.is<std::nullptr_t>()) {
            stream << "null";
            return;
        }
        if (value.is<bool>()) {
            stream << (value.as<bool>() ? "true" : "false");
            return;
        }
        if (value.is<double>()) {
            writeNumber(stream, value.as<double>());
            return;
        }
        if (value.is<std::string>()) {
            writeEscapedString(stream, value.as<std::string>());
            return;
        }
        if (value.is<JsonArray>()) {
            writeArray(stream, value.as<JsonArray>(), depth);
            return;
        }
        writeObject(stream, value.as<JsonObject>(), depth);
    }

    void JSON::writeValueCompact(std::ostream &stream) const
    {
        if (this->is<std::nullptr_t>()) {
            stream << "null";
            return;
        }
        if (this->is<bool>()) {
            stream << (this->as<bool>() ? "true" : "false");
            return;
        }
        if (this->is<double>()) {
            writeNumber(stream, this->as<double>());
            return;
        }
        if (this->is<std::string>()) {
            writeEscapedString(stream, this->as<std::string>());
            return;
        }
        if (this->is<JsonArray>()) {
            writeArrayCompact(stream, this->as<JsonArray>());
            return;
        }
        writeObjectCompact(stream, this->as<JsonObject>());
    }

    JSON::JSON() noexcept :
        _value(nullptr)
    {
    }

    JSON::JSON(bool b) noexcept :
        _value(b)
    {
    }

    JSON::JSON(double d) noexcept :
        _value(d)
    {
    }

    JSON::JSON(std::string s) :
        _value(std::move(s))
    {
    }

    JSON::JSON(JsonArray arr) :
        _value(std::move(arr))
    {
    }

    JSON::JSON(JsonObject obj) :
        _value(std::move(obj))
    {
    }

    JSON JSON::object()
    {
        return JSON(JsonObject {});
    }

    JSON JSON::array()
    {
        return JSON(JsonArray {});
    }

    std::optional<std::reference_wrapper<JSON>> JSON::find(std::string_view key)
    {
        auto object = this->getIf<JsonObject>();
        if (!object)
            return std::nullopt;
        auto &obj = object.value().get();
        for (auto &[k, v] : obj) {
            if (k == key)
                return v;
        }
        return std::nullopt;
    }

    std::optional<std::reference_wrapper<const JSON>> JSON::find(
        std::string_view key) const
    {
        if (!this->is<JsonObject>())
            return std::nullopt;
        const auto &obj = this->as<JsonObject>();

        for (const auto &[k, v] : obj) {
            if (k == key)
                return v;
        }
        return std::nullopt;
    }

    bool JSON::contains(std::string_view key) const
    {
        return this->find(key).has_value();
    }

    JSON &JSON::set(std::string key, JSON value)
    {
        return this->setObject(std::move(key), std::move(value));
    }

    JSON &JSON::set(std::string key, bool value)
    {
        return this->setObject(std::move(key), JSON(value));
    }

    JSON &JSON::set(std::string key, double value)
    {
        return this->setObject(std::move(key), JSON(value));
    }

    JSON &JSON::set(std::string key, std::string value)
    {
        return this->setObject(std::move(key), JSON(std::move(value)));
    }

    JSON &JSON::set(std::string key, std::nullptr_t)
    {
        return this->setObject(std::move(key), JSON());
    }

    JSON &JSON::set(std::string key, JsonArray value)
    {
        return this->setObject(std::move(key), JSON(std::move(value)));
    }

    JSON &JSON::set(std::string key, JsonObject value)
    {
        return this->setObject(std::move(key), JSON(std::move(value)));
    }

    JSON &JSON::push(JSON value)
    {
        return this->pushToArray(std::move(value));
    }

    JSON &JSON::push(bool value)
    {
        return this->pushToArray(JSON(value));
    }

    JSON &JSON::push(double value)
    {
        return this->pushToArray(JSON(value));
    }

    JSON &JSON::push(std::string value)
    {
        return this->pushToArray(JSON(std::move(value)));
    }

    JSON &JSON::push(JsonArray value)
    {
        return this->pushToArray(JSON(std::move(value)));
    }

    JSON &JSON::push(JsonObject value)
    {
        return this->pushToArray(JSON(std::move(value)));
    }

    JSON &JSON::setObject(std::string key, JSON value)
    {
        if (!this->is<JsonObject>())
            throw std::runtime_error("json: value is not an object");
        auto &obj = this->as<JsonObject>();

        for (auto &[currentKey, currentValue] : obj) {
            if (currentKey == key) {
                currentValue = std::move(value);
                return *this;
            }
        }
        obj.emplace_back(std::move(key), std::move(value));
        return *this;
    }

    JSON &JSON::pushToArray(JSON value)
    {
        if (!this->is<JsonArray>())
            throw std::runtime_error("json: value is not an array");
        this->as<JsonArray>().push_back(std::move(value));
        return *this;
    }

    JSON &JSON::operator[](std::string_view key)
    {
        auto v = find(key);
        if (!v)
            throw std::runtime_error("json: key not found");
        return *v;
    }

    const JSON &JSON::operator[](std::string_view key) const
    {
        auto v = find(key);
        if (!v)
            throw std::runtime_error("json: key not found");
        return *v;
    }

    JSON &JSON::operator[](size_t index)
    {
        return this->as<JsonArray>().at(index);
    }

    size_t JSON::size() const
    {
        if (this->is<JsonArray>())
            return this->as<JsonArray>().size();
        if (this->is<JsonObject>())
            return this->as<JsonObject>().size();
        return 0;
    }

    std::string JSON::toCompactString() const
    {
        std::ostringstream stream;

        this->writeValueCompact(stream);
        return stream.str();
    }

    std::ostream &operator<<(std::ostream &stream, const JSON &json)
    {
        JSON::writeValue(stream, json, 0);
        return stream;
    }

    const std::unordered_map<unsigned char, const char *> JSON::ESCAPED_CHARS =
        {{'"', "\\\""},
            {'\\', "\\\\"},
            {'\b', "\\b"},
            {'\f', "\\f"},
            {'\n', "\\n"},
            {'\r', "\\r"},
            {'\t', "\\t"}};
} // namespace JSON
