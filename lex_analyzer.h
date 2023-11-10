#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#ifndef LEX_ANALYZER_H
#define LEX_ANALYZER_H

#define regex_literal "\"[^\"]+\"|\'[^\']+\'"
#define regex_keyword ""
#define regex_operator ""

class LexAnalyzer {
public:
    int analyze(const std::string& path, const std::string& fileName) {
        input_file = new std::ifstream(path + fileName);
        
        if (!input_file) {
            std::cerr << "Error opening input file." << std::endl;  // Use cerr to send an error message
            return 1;
        }

        actualanalyze();

        return 0;
    }
private:
    std::vector<std::string>* v_tokens;
    std::ifstream* input_file;

    const std::regex t_literal{regex_literal};
    const std::regex t_keyword{regex_keyword};
    const std::regex t_operator{regex_operator};

    void actualanalyze() {

    }

    // append all lines of input file to vector
    void createInitialVector() {
        std::string line;

        v_tokens = new std::vector<std::string>;
        
        while (getline(*input_file, line)) {
            v_tokens->push_back(line);
        }
    }
};

#endif