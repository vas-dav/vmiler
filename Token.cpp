//
// Created by tylen on 26.12.2023.
//

#include "Token.h"


Token::Token(std::string name, const std::string& regex, TokenId id):
                               m_name(std::move(name)),
                               m_regex((regex)),
                               m_id(id) {
    // Nothing to do
}

bool Token::operator==(const Token &token) {
    return this->m_id == token.m_id;
}

bool Token::operator!=(const Token &token) {
    return this->m_id != token.m_id;
}

std::regex Token::getRegex() const {
    return std::__cxx11::regex{m_regex};
}

std::string Token::getName() const {
    return std::string{m_name};
}

Token::TokenId Token::getId() const {
    return m_id;
}
