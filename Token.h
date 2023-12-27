//
// Created by tylen on 26.12.2023.
//

#ifndef VMILER_TOKEN_H
#define VMILER_TOKEN_H

#include <string>
#include <utility>


class Token {
public:
    Token(std::string name);

protected:
    std::string _name;
};


#endif //VMILER_TOKEN_H
