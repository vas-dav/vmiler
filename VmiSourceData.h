//
// Created by tylen on 28.12.2023.
//

#ifndef VMILER_VMISOURCEDATA_H
#define VMILER_VMISOURCEDATA_H

#include <vector>
#include <string>
#include <fstream>
#include <utility>

#include "Logger.h"

namespace vmiler {
    class VmiSourceData {
    public:
        struct VmiSourceLine {
        public:
            VmiSourceLine();
            explicit VmiSourceLine(std::string line);
            std::string getFullLine() const;
            std::size_t position;
            bool isEnd;
        private:
            std::string m_line;
        };

        explicit VmiSourceData(const std::string &sourceFilePath);
        ~VmiSourceData() = default;
        VmiSourceLine getNextLine();


    private:
        std::ifstream srcFile;
    };
}

#endif //VMILER_VMISOURCEDATA_H
