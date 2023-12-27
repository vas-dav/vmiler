#include "TokenTree.hpp"

const Token rootToken {"root"};
const Token exitToken {"exit"};
const Token charToken {"char"};
const Token byteToken {"byte"};
const Token boolToken {"bool"};
const Token intToken {"int"};
const Token stringToken {"string"};
const Token identifierToken {"id"};
const Token equalityToken {"equality"};
const Token numericLiteralToken {"num_literal"};
const Token stringLiteralToken {"string_literal"};
const Token endToken {"end"};

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


TokenTree tokenTree {rootTokenNode};


TokenTree::TokenNode::TokenNode(Token token, std::initializer_list<const TokenNode *> nodes): m_token{std::move(token)}, m_nodes {nodes} {
    // Nothing to do
}


TokenTree::TokenTree(const TokenNode& rootNode): m_rootNode {rootNode} {
    // Nothing to do
}

std::vector<Token> TokenTree::tokenizeString(const std::string &str) {
    WIP();
    return std::vector<Token>();
}
