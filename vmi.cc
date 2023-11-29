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
#include <iostream>
#include <cstdlib>

static void help(void) {
    std::cout << "Usage: vmi <source.vmi>" << std::endl;
    exit(1);
}

int main (int argc, char** argv) {
    if (argc < 2) help();
    return 0;
}

