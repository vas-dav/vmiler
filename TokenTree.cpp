#include "TokenTree.hpp"

TokenTree::TokenNode::TokenNode(const Token& token, std::initializer_list<const TokenNode *> nodes): m_token{token}, m_nodes {nodes} {
    // Nothing to do
}

bool TokenTree::TokenNode::operator==(const TokenTree::TokenNode &node) const {
    return this->m_token.getId() == node.m_token.getId();
}


std::vector<TokenTree::TokenNode> TokenTree::tokenizeStringCall(const std::string& str, const TokenNode& currentNode, size_t& position) {
    std::vector<TokenTree::TokenNode> tokens;
    /* TODO:
     * - Throw an error, when token is mismatched
     * */
    for (const auto* child : currentNode.m_nodes) {
        TokenNode tokenNode = *child;
        std::smatch match;
        if (std::regex_search(str.cbegin() + position,
                              str.cend(), match,
                              std::regex(tokenNode.m_token.getRegex()))) {
            tokens.push_back(tokenNode);
            position += match.position() + match.length();

            std::vector<TokenTree::TokenNode> childTokens = tokenizeStringCall(str, tokenNode, position);
            tokens.insert(tokens.end(), childTokens.begin(), childTokens.end());
            break;
        }
    }

    if (!tokens.empty()) {
        m_lastTokenNode = tokens.back();
    }

    if (m_lastTokenNode == endTokenNode && position < str.size()) {
        std::vector<TokenTree::TokenNode> childTokens = tokenizeStringCall(str, rootTokenNode, position);
        tokens.insert(tokens.end(), childTokens.begin(), childTokens.end());
    }
    return tokens;
}

std::vector<Token> TokenTree::tokenizeString(const std::string &str) {
    WIP_WEAK();
    //vmiler::logger.debug("TokenTree::tokenizeString tokenizing: %s", str.c_str());
    size_t strPosition = 0;
    auto parsedNodes {tokenizeStringCall(str, m_lastTokenNode, strPosition)};
    std::vector<Token> tokens {};
    tokens.resize(parsedNodes.size());
    std::transform(parsedNodes.begin(),
                   parsedNodes.end(),
                   tokens.begin(), [] (const TokenNode& node) -> const Token& {
        return node.m_token;
    });

    return tokens;
}
