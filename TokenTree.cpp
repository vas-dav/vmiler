#include "TokenTree.hpp"

TokenTree::TokenNode::TokenNode(Token token, std::initializer_list<const TokenNode *> nodes): m_token{std::move(token)}, m_nodes {nodes} {
    // Nothing to do
}


TokenTree::TokenTree(){
    // Nothing to do
}


std::vector<Token> TokenTree::tokenizeStringCall(const std::string& str, const TokenNode& currentNode, size_t& position) {
    std::vector<Token> tokens;
    /* TODO:
     * - Go back to rootNode after an endToken hits a match
     * - Throw an error, when token is mismatched
     * */
    for (const auto* child : currentNode.m_nodes) {
        const TokenNode& tokenNode = *child;
        Token token = tokenNode.m_token;

        std::smatch match;
        if (std::regex_search(str.cbegin() + position, str.cend(), match, std::regex(token.getRegex()))) {
            tokens.push_back(token);
            position += match.position() + match.length();

            std::vector<Token> childTokens = tokenizeStringCall(str, tokenNode, position);
            tokens.insert(tokens.end(), childTokens.begin(), childTokens.end());

            break;
        }
    }

    return tokens;
}

std::vector<Token> TokenTree::tokenizeString(const std::string &str) {
    WIP_WEAK();
    vmiler::logger.debug("TokenTree::tokenizeString tokenizing: %s", str.c_str());
    size_t strPosition = 0;
    return tokenizeStringCall(str, rootTokenNode, strPosition);
}
