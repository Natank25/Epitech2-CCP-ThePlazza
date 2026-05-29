/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** DESCRIPTION
*/

#ifndef JSON_HPP
    #define JSON_HPP

    #include <concepts>
    #include <functional>
    #include <optional>
    #include <ostream>
    #include <string>
    #include <string_view>
    #include <unordered_map>
    #include <variant>
    #include <vector>

namespace JSON {
    class JSON {
    public:
        using JsonObject = std::vector<std::pair<std::string, JSON>>;
        using JsonArray = std::vector<JSON>;

        using Variant = std::variant<std::nullptr_t, bool, double, std::string,
            JsonArray, JsonObject>;

        JSON() noexcept;

        explicit JSON(bool b) noexcept;

        explicit JSON(double d) noexcept;

        explicit JSON(std::string s);

        explicit JSON(JsonArray arr);

        explicit JSON(JsonObject obj);

        [[nodiscard]] static JSON object();

        [[nodiscard]] static JSON array();

        template<typename Type>
        [[nodiscard]] bool is() const noexcept
        {
            return std::holds_alternative<Type>(_value);
        }

        template<typename Type>
        [[nodiscard]] Type &as() noexcept
        {
            return std::get<Type>(_value);
        }

        template<typename Type>
        [[nodiscard]] const Type &as() const noexcept
        {
            return std::get<Type>(_value);
        }

        template<typename Type>
        [[nodiscard]] std::optional<std::reference_wrapper<Type>>
        getIf() noexcept
        {
            if (!this->is<Type>())
                return std::nullopt;
            return this->as<Type>();
        }

        template<typename Type>
        [[nodiscard]] std::optional<const std::reference_wrapper<Type>>
        getIf() const noexcept
        {
            if (!this->is<Type>())
                return std::nullopt;
            return this->as<Type>();
        }

        std::optional<std::reference_wrapper<JSON>> find(std::string_view key);

        [[nodiscard]] std::optional<std::reference_wrapper<const JSON>> find(
            std::string_view key) const;

        [[nodiscard]] bool contains(std::string_view key) const;

        JSON &set(std::string key, JSON value);

        JSON &set(std::string key, bool value);

        JSON &set(std::string key, double value);

        JSON &set(std::string key, std::string value);

        JSON &set(std::string key, std::nullptr_t value);

        JSON &set(std::string key, JsonArray value);

        JSON &set(std::string key, JsonObject value);

        template<std::integral Type>
            requires(!std::same_as<Type, bool>)
        JSON &set(std::string key, Type value)
        {
            return this->set(std::move(key), static_cast<double>(value));
        }

        template<std::floating_point Type>
        JSON &set(std::string key, Type value)
        {
            return this->set(std::move(key), static_cast<double>(value));
        }

        JSON &push(JSON value);

        JSON &push(bool value);

        JSON &push(double value);

        JSON &push(std::string value);

        JSON &push(JsonArray value);

        JSON &push(JsonObject value);

        template<std::integral Type>
            requires(!std::same_as<Type, bool>)
        JSON &push(Type value)
        {
            return this->push(static_cast<double>(value));
        }

        template<std::floating_point Type>
        JSON &push(Type value)
        {
            return this->push(static_cast<double>(value));
        }

        JSON &setObject(std::string key, JSON value);

        JSON &pushToArray(JSON value);

        JSON &operator[](std::string_view key);
        const JSON &operator[](std::string_view key) const;

        JSON &operator[](size_t index);

        [[nodiscard]] size_t size() const;

        static void writeIndent(std::ostream &stream, size_t depth);

        static void writeEscapedString(
            std::ostream &stream, std::string_view value);

        static void writeNumber(std::ostream &stream, double number);

        static void writeArray(
            std::ostream &stream, const JsonArray &array, size_t depth);

        static void writeObject(
            std::ostream &stream, const JsonObject &object, size_t depth);

        static void writeArrayCompact(
            std::ostream &stream, const JsonArray &array);

        static void writeObjectCompact(
            std::ostream &stream, const JsonObject &object);

        static void writeValue(
            std::ostream &stream, const JSON &value, size_t depth);

        void writeValueCompact(std::ostream &stream) const;

        [[nodiscard]] std::string toCompactString() const;

        static std::optional<JSON> parse(std::string_view json);

        static std::optional<JSON> parseStream(std::istream &stream);

        static std::optional<JSON> parseFile(std::string_view path);

    private:
        using ValueParser = std::optional<JSON> (*)(
            std::string_view json, size_t &pos);

        static void skipWhitespace(std::string_view json, size_t &pos) noexcept;

        static bool consumeChar(
            std::string_view json, size_t &pos, char c) noexcept;

        static bool matchLiteral(std::string_view json, size_t &pos,
            std::string_view literal) noexcept;

        static std::optional<JSON> parseValue(
            std::string_view json, size_t &pos);

        static std::optional<JSON> parseObject(
            std::string_view json, size_t &pos);

        static std::optional<JSON> parseArray(
            std::string_view json, size_t &pos);

        static std::optional<JSON> parseString(
            std::string_view json, size_t &pos);

        static std::optional<JSON> parseTrue(
            std::string_view json, size_t &pos);

        static std::optional<JSON> parseFalse(
            std::string_view json, size_t &pos);

        static std::optional<JSON> parseNull(
            std::string_view json, size_t &pos);

        static std::optional<char> parseEscapedChar(
            std::string_view json, size_t &pos) noexcept;

        static std::optional<bool> parseStringCharacter(
            std::string_view json, size_t &pos, std::string &out);

        static std::optional<JSON> parseNumber(
            std::string_view json, size_t &pos);

        static bool parseIntegerPart(
            std::string_view json, size_t &pos) noexcept;

        static bool parseFractionPart(
            std::string_view json, size_t &pos) noexcept;

        static bool parseExponentPart(
            std::string_view json, size_t &pos) noexcept;

        static std::optional<double> numberToDouble(
            std::string_view json, size_t start, size_t end) noexcept;

        static bool parseArrayElement(
            std::string_view json, size_t &pos, JsonArray &arr);

        static std::optional<bool> parseArrayDelimiter(
            std::string_view json, size_t &pos) noexcept;

        static bool parseObjectMember(
            std::string_view json, size_t &pos, JsonObject &obj);

        static std::optional<bool> parseObjectDelimiter(
            std::string_view json, size_t &pos) noexcept;

        static const std::unordered_map<char, ValueParser> VALUE_PARSERS;
        static const std::unordered_map<char, char> ESCAPE_CHARS;
        static constexpr size_t INDENT_SIZE = 4;
        static const std::unordered_map<unsigned char, const char *>
            ESCAPED_CHARS;

        Variant _value;
    };

    std::ostream &operator<<(std::ostream &stream, const JSON &json);
} // namespace JSON

#endif
