#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <cstring>
#include <vector>

#ifndef LEX_ANALYZER_H
#define LEX_ANALYZER_H

#define regex_literal "(?![^<<<]*>>>)\"[^\"]+\"|\'[^\']+\'"
#define regex_keyword "(?![^<<<]*>>>)(cout|auto|break|case|catch|class|const|continue|default|delete|do|double|else|enum|explicit|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|operator|private|protected|public|register|reinterpret_cast|return|short|signed|sizeof|static|static_cast|struct|switch|template|this|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while)"
#define regex_separator "(?![^<<<]*>>>)[;:,.\\(\\)\\{\\}\\[\\]]"
#define regex_integer "(?![^<<<]*>>>)[0-9]+"
#define regex_comment "(?![^<<<]*>>>)//[^\n]*"
#define regex_identifier "(?![^<<<]*>>>)\\b[a-zA-Z_]\\w*\\b"
#define regex_whitespace "(?![^<<<]*>>>)\\s"
#define regex_operator "(?![^<<<]*>>>)[-+*/%&|^=!]=?|&&|\\|\\|[~?:-]"

class LexAnalyzer {
public:
    ~LexAnalyzer() {
        delete v_tokens;
        delete input_file;
        delete output_file;
    }

    int analyze(const std::string& path, const std::string& fileName) {
        input_file = new std::ifstream(path + fileName);
        output_file = new std::ofstream(path + "output.txt");
        
        // if input file cannot be opened then output an error and end program
        if (!input_file) {
            std::cerr << "Error opening input file." << std::endl;  // Use cerr to send an error message
            return 1;
        }

        tokenize();

        // close input and output files
        input_file->close();
        output_file->close();

        return 0;
    }
private:
    std::vector<std::string>* v_tokens;
    std::ifstream* input_file;
    std::ofstream* output_file;

    // define all regex for token identifying
    std::regex t_literal{regex_literal};
    std::regex t_keyword{regex_keyword};
    std::regex t_operator{regex_operator};
    std::regex t_separator{regex_separator};
    std::regex t_integer{regex_integer};
    std::regex t_comment{regex_comment};
    std::regex t_identifer{regex_identifier};
    std::regex t_whitespace{regex_whitespace};

    // idenfity and tokenize the input file to an output file
    void tokenize() {
        createInitialVector();

        std::smatch m;
        std::string replace_str;

        // throughout this portion of the code, <<< and >>> will be used to mark any strings that have already been tokenized
        for (std::string& s : *v_tokens) {
            
            // remove all comments
            s = std::regex_replace(s, t_comment, "");

            // identify all literal tokens
            while (std::regex_search(s, m, t_literal)) {
                for (auto str : m) { replace_str += str; }
                s = std::regex_replace(s, t_literal, "<<<\"" + replace_str + "\" = literal>>>", std::regex_constants::format_first_only);
                replace_str = "";
            }

            // identify all keyword tokens
            while (std::regex_search(s, m, t_keyword)) {
                s = std::regex_replace(s, t_keyword, "<<<\"" + m.str() + "\" = keyword>>>", std::regex_constants::format_first_only);
            }

            // identify all separator tokens
            while (std::regex_search(s, m, t_separator)) {
                s = std::regex_replace(s, t_separator, "<<<\"" + m.str() + "\" = separator>>>", std::regex_constants::format_first_only);
            }

            // identify all integer tokens
            while (std::regex_search(s, m, t_integer)) {
                s = std::regex_replace(s, t_integer, "<<<\"" + m.str() + "\" = integer>>>", std::regex_constants::format_first_only);
            }

            // identify all identifier tokens
            while (std::regex_search(s, m, t_identifer)) {
                s = std::regex_replace(s, t_identifer, "<<<\"" + m.str() + "\" = identifier>>>", std::regex_constants::format_first_only);
            }

            // identify all operator tokens
            while (std::regex_search(s, m, t_operator)) { 
                s = std::regex_replace(s, t_operator, "<<<\"" + m.str() + "\" = operator>>>", std::regex_constants::format_first_only);
            }

            // remove all whitespace
            s = std::regex_replace(s, t_whitespace, "");

            // delete and replace all the uncessary markers with proper formatting
            s = std::regex_replace(s, std::regex("<<<"), "");
            s = std::regex_replace(s, std::regex(">>>"), "\n");

            // append tokenized line to output file
            const char* str = s.c_str();
            output_file->write(str, s.length());
        }
    }

    // append all lines of input file to vector for easier handling
    void createInitialVector() {
        std::string line;

        v_tokens = new std::vector<std::string>;
        
        while (getline(*input_file, line)) {
            v_tokens->push_back(line);
        }
    }
};

#endif