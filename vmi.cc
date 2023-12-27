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
    std::string currentLine {};

    do {
        srcFile >> currentLine;
        auto tokens {TokenTree::tokenizeString(currentLine)};
    } while (!currentLine.empty());

    return 0;
}
