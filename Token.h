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
    explicit Token(std::string name, const std::string& regex="");
    std::regex getRegex();
    std::string getName();

protected:
    std::string m_name;
    std::regex m_regex;
};


#endif //VMILER_TOKEN_H
