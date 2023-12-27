//
// Created by tylen on 26.12.2023.
//

#include "Token.h"


Token::Token(std::string name, const std::string& regex): m_name(std::move(name)),
                                                          m_regex((regex)) {}

std::regex Token::getRegex() {
    return std::__cxx11::regex{m_regex};
}

std::string Token::getName() {
    return std::string{m_name};
}
