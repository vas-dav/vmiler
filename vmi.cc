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
#include <fstream>
#include <string>

#include "Logger.h"
#include "TokenTree.hpp"

int main (int argc, char** argv) {
    if (argc < 2) {
        vmiler::logger.usage("No arguments provided");
    }

    std::ifstream srcFile {argv[1]};
    if (!srcFile.is_open()) {
        vmiler::logger.error("Unable to open file: %s", argv[1]);
    }
    vmiler::logger.info("Reading file %s", argv[1]);
    std::string currentLine {};
    TokenTree tokenTree;
    std::vector<Token> tokens;

    while(std::getline(srcFile, currentLine)) {
        auto lineTokens {(tokenTree.tokenizeString(currentLine))};
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
