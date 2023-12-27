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

    explicit TokenTree();
    std::vector<Token> tokenizeString(const std::string& str) ;
private:
    std::vector<Token> tokenizeStringCall(const std::string& str, const TokenNode& currentNode, size_t& position);
protected:
    const Token rootToken {"root", ".*"};
    const Token exitToken {"exit", "\\bexit\\b"};
    const Token charToken {"char", "\\bchar\\b"};
    const Token byteToken {"byte", "\\bbyte\\b"};
    const Token boolToken {"bool", "\\bbool\\b"};
    const Token intToken {"int", "\\bint\\b"};
    const Token stringToken {"string", "\\bstring\\b"};
    const Token identifierToken {"id", "(\\s+)([a-zA-Z_][a-zA-Z0-9_]*)\\b"};
    const Token equalityToken {"equality", "="};
    const Token numericLiteralToken {"num_literal", "\\b[0-9]+\\b"};
    const Token stringLiteralToken {"string_literal", "\"([^\"]*)\""};
    const Token endToken {"end", ";"};

    const TokenTree::TokenNode endTokenNode {endToken, {}};
    const TokenTree::TokenNode stringLiteralTokenNode {stringLiteralToken, {&endTokenNode}};
    const TokenTree::TokenNode numericLiteralTokenNode {numericLiteralToken, {&endTokenNode}};
    const TokenTree::TokenNode equalityTokenNode {equalityToken, {&numericLiteralTokenNode, &stringLiteralTokenNode}};
    const TokenTree::TokenNode identifierTokenNode {identifierToken, {&equalityTokenNode}};
    const TokenTree::TokenNode stringTokenNode {stringToken, {&identifierTokenNode}};
    const TokenTree::TokenNode intTokenNode {intToken, {&identifierTokenNode}};
    const TokenTree::TokenNode boolTokenNode {boolToken, {&identifierTokenNode}};
    const TokenTree::TokenNode byteTokenNode {byteToken, {&identifierTokenNode}};
    const TokenTree::TokenNode charTokenNode {charToken, {&identifierTokenNode}};
    const TokenTree::TokenNode exitTokenNode {exitToken, {&numericLiteralTokenNode, &endTokenNode}};
    const TokenTree::TokenNode rootTokenNode {rootToken, {&exitTokenNode, &charTokenNode, &byteTokenNode, &boolTokenNode, &intTokenNode, &stringTokenNode}};
};

#endif
