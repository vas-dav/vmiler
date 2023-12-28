/*
 * =====================================================================================
 *
 *       Filename:  vmi.cpp
 *
 *    Description: A main source file of vmiler project 
 *
 *        Version:  1.0
 *        Created:  29.11.2023 22.40.02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  tylen, mishanya
 *
 * =====================================================================================
 */

#include <string>

#include "Logger.h"
#include "TokenTree.hpp"
#include "VmiSourceData.h"

int main (int argc, char** argv) {
    if (argc < 2) {
        vmiler::logger.usage("No arguments provided");
    }
    vmiler::VmiSourceData vmiMainSrc(argv[1]);
    std::vector<Token> tokens;
    TokenTree tokenTree;
    for(auto line {(vmiMainSrc.getNextLine())}; !line.isEnd; line = vmiMainSrc.getNextLine()) {
        auto lineTokens {(tokenTree.tokenizeString(line))};
        tokens.insert(tokens.end(), lineTokens.begin(), lineTokens.end());
    }

    std::stringstream ss;
    ss << "Tokenized: ";
    for (Token token : tokens) {
        ss << token.getName() << " ";
    }
    vmiler::logger.info(ss.str());
    return 0;
}
