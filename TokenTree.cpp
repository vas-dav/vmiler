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

std::vector<TokenTree::TokenNode> TokenTree::tokenizeStringCall(vmiler::VmiSourceData::VmiSourceLine &line) {
    std::vector<TokenNode> tokens;
    TokenNode currentNode = m_lastTokenNode;
    std::string str = line.getFullLine();
    /* The currentNode should change on each iteration of the loop. If
     * that does not happen, there is a mismatch and the function should
     * immediately stop and throw an error. */
    while (currentNode != endTokenNode && line.position < str.size()) {
        bool tokenMatched = false;
        for (const auto* child : currentNode.m_nodes) {
            TokenNode tokenNode = *child;
            std::smatch match;
            if (std::regex_search(str.cbegin() + line.position,
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
                line.position += match.position() + match.length();
                currentNode = tokenNode;
                tokenMatched = true;
                break;
            }
        }
        if (!tokenMatched) {
            auto* expected = currentNode.m_nodes.front();
            line.throwExpectationNotMet(expected->m_token.getName(), currentNode.m_token.getName());
        }
    }
    m_lastTokenNode = currentNode;
    return tokens;
}

std::vector<Token> TokenTree::tokenizeString(vmiler::VmiSourceData::VmiSourceLine& line) {
    WIP_WEAK();
    vmiler::logger.debug("TokenTree::tokenizeString tokenizing: %s", line.getFullLine().c_str());
    auto parsedNodes {tokenizeStringCall(line)};
    std::vector<Token> tokens {};
    tokens.resize(parsedNodes.size());
    std::transform(parsedNodes.begin(),
                   parsedNodes.end(),
                   tokens.begin(), [] (const TokenNode& node) -> const Token& {
        return node.m_token;
    });

    return tokens;
}
