#include "TokenTree.hpp"

TokenTree::TokenNode::TokenNode(const Token& token, std::initializer_list<const TokenNode *> nodes): m_token{token}, m_nodes {nodes} {
    // Nothing to do
}

bool TokenTree::TokenNode::operator==(const TokenTree::TokenNode &node) const {
    return this->m_token.getId() == node.m_token.getId();
}

bool TokenTree::TokenNode::operator!=(const TokenTree::TokenNode &node) const {
    return this->m_token.getId() != node.m_token.getId();
}

std::vector<TokenTree::TokenNode> TokenTree::tokenizeStringCall(const std::string& str) {
    std::vector<TokenNode> tokens;
    TokenNode currentNode = m_lastTokenNode;
    size_t strPosition = 0;
    /* The currentNode should change on each iteration of the loop. If
     * that does not happen, there is a mismatch and the function should
     * immediately stop and throw an error. */
    while (currentNode != endTokenNode && strPosition < str.size()) {
        bool tokenMatched = false;
        for (const auto* child : currentNode.m_nodes) {
            TokenNode tokenNode = *child;
            std::smatch match;
            if (std::regex_search(str.cbegin() + strPosition,
                                  str.cend(), match,
                                  std::regex(tokenNode.m_token.getRegex()))) {
                if (tokenNode != endTokenNode) {
                    tokens.push_back(tokenNode);
                } else {
                    // Go back to rootNode after an endToken hits a match
                    currentNode = rootTokenNode;
                    tokenMatched = true;
                    break;
                }
                strPosition += match.position() + match.length();
                currentNode = tokenNode;
                tokenMatched = true;
                break;
            }
        }
        if (!tokenMatched) {
            std::string errorInString= str.substr(strPosition, str.size() > 10 ? 10 : str.size() - strPosition);
            vmiler::logger.error("Can't match token at %s. Last token is %s", errorInString.c_str(),
                                                                  currentNode.m_token.getName().c_str());
        }
    }
    m_lastTokenNode = currentNode;
    return tokens;
}

std::vector<Token> TokenTree::tokenizeString(const std::string &str) {
    WIP_WEAK();
    //vmiler::logger.debug("TokenTree::tokenizeString tokenizing: %s", str.c_str());
    auto parsedNodes {tokenizeStringCall(str)};
    std::vector<Token> tokens {};
    tokens.resize(parsedNodes.size());
    std::transform(parsedNodes.begin(),
                   parsedNodes.end(),
                   tokens.begin(), [] (const TokenNode& node) -> const Token& {
        return node.m_token;
    });

    return tokens;
}
