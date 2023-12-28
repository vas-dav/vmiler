//
// Created by tylen on 26.12.2023.
//

#ifndef VMILER_TOKEN_H
#define VMILER_TOKEN_H

#include <string>
#include <utility>
#include <regex>


class Token {
public:
    enum TokenId {
        ROOT_TOKEN,
        EXIT_TOKEN,
        CHAR_TOKEN,
        BYTE_TOKEN,
        BOOL_TOKEN,
        INT_TOKEN,
        STRING_TOKEN,
        IDENTIFIER_TOKEN,
        EQUALITY_TOKEN,
        NUMERIC_LITERAL_TOKEN,
        STRING_LITERAL_TOKEN,
        SEMICOLON_TOKEN,
        END_TOKEN
    };

    Token() = default;
    Token(const Token& token) = default;
    explicit Token(std::string name, const std::string& regex="", TokenId id = ROOT_TOKEN);
    std::regex getRegex() const;
    std::string getName() const;
    TokenId getId() const;

    bool operator==(const Token& token);
    bool operator!=(const Token& token);

protected:
    std::string m_name {};
    std::regex m_regex {};
    TokenId m_id {ROOT_TOKEN};
};


#endif //VMILER_TOKEN_H
