#ifndef VMILER_TOKEN_TREE
#define VMILER_TOKEN_TREE

#include <vector>
#include <string>
#include <cassert>
#include <utility>

#include "Token.h"
#include "Logger.h"


class TokenTree {
public:
    struct TokenNode {
    public:
        Token m_token;
        std::vector<const TokenNode*> m_nodes {};

        TokenNode(Token  token, std::initializer_list<const TokenNode*> nodes);
        TokenNode(const TokenNode& node) = default;
    };

    explicit TokenTree(const TokenNode& rootNode);
    static std::vector<Token> tokenizeString(const std::string& str) ;

protected:
    TokenNode m_rootNode;
};


#endif
