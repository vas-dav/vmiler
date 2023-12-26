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

int main (int argc, char** argv) {
    vmiler::Logger logger;
    if (argc < 2) {
        logger.usage();
    }

    std::ifstream srcFilePath(argv[1]);
    std::stringstream ss;
    ss << "Source file: " << argv[1];
    logger.debug(ss.str());
    std::string currentLine;
    while(std::getline(srcFilePath, currentLine)) {

    }


    return 0;
}

