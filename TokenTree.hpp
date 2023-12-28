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
        Token m_token {};
        std::vector<const TokenNode*> m_nodes {};

        TokenNode(const Token& token, std::initializer_list<const TokenNode*> nodes);
        TokenNode(const TokenNode& node) = default;

        bool operator==(const TokenNode& node) const;
        bool operator!=(const TokenNode& node) const;
    };

    TokenTree() = default;
    std::vector<Token> tokenizeString(const std::string& str);

protected:
    const Token rootToken {"root", ".*", Token::TokenId::ROOT_TOKEN};
    const Token exitToken {"exit", "^\\s*\\bexit\\b", Token::TokenId::EXIT_TOKEN};
    const Token charToken {"char", "^\\s*\\bchar\\b", Token::TokenId::CHAR_TOKEN};
    const Token byteToken {"byte", "^\\s*\\bbyte\\b", Token::TokenId::BYTE_TOKEN};
    const Token boolToken {"bool", "^\\s*\\bbool\\b", Token::TokenId::BOOL_TOKEN};
    const Token intToken {"int", "^\\s*\\bint\\b", Token::TokenId::INT_TOKEN};
    const Token stringToken {"string", "^\\s*\\bstring\\b", Token::TokenId::STRING_TOKEN};
    const Token identifierToken {"id", "(\\s+)([a-zA-Z_][a-zA-Z0-9_]*)\\b", Token::TokenId::IDENTIFIER_TOKEN};
    const Token equalityToken {"equality", "^\\s*=", Token::TokenId::EQUALITY_TOKEN};
    const Token numericLiteralToken {"num_literal", "^\\s*\\b[0-9]+\\b", Token::TokenId::NUMERIC_LITERAL_TOKEN};
    const Token stringLiteralToken {"string_literal", "^\\s*\"([^\"]*)\"", Token::TokenId::STRING_LITERAL_TOKEN};
    const Token semicolonToken {"semicolon", "^\\s*;", Token::TokenId::SEMICOLON_TOKEN};
    const Token endToken {"end", "", Token::TokenId::END_TOKEN};

    const TokenTree::TokenNode endTokenNode {endToken, {}};
    const TokenTree::TokenNode semicolonTokenNode {semicolonToken, {&endTokenNode}};
    const TokenTree::TokenNode stringLiteralTokenNode {stringLiteralToken, {&semicolonTokenNode}};
    const TokenTree::TokenNode numericLiteralTokenNode {numericLiteralToken, {&semicolonTokenNode}};
    const TokenTree::TokenNode equalityTokenNode {equalityToken, {&numericLiteralTokenNode,
                                                                               &stringLiteralTokenNode}};
    const TokenTree::TokenNode identifierTokenNode {identifierToken, {&equalityTokenNode}};
    const TokenTree::TokenNode stringTokenNode {stringToken, {&identifierTokenNode}};
    const TokenTree::TokenNode intTokenNode {intToken, {&identifierTokenNode}};
    const TokenTree::TokenNode boolTokenNode {boolToken, {&identifierTokenNode}};
    const TokenTree::TokenNode byteTokenNode {byteToken, {&identifierTokenNode}};
    const TokenTree::TokenNode charTokenNode {charToken, {&identifierTokenNode}};
    const TokenTree::TokenNode exitTokenNode {exitToken, {&numericLiteralTokenNode, &semicolonTokenNode}};
    const TokenTree::TokenNode rootTokenNode {rootToken, {&exitTokenNode, &charTokenNode, &byteTokenNode,
                                                                       &boolTokenNode, &intTokenNode, &stringTokenNode,
                                                                       &semicolonTokenNode}};

    std::vector<TokenNode> tokenizeStringCall(const std::string& str);
    TokenTree::TokenNode m_lastTokenNode {rootTokenNode};
};

#endif
