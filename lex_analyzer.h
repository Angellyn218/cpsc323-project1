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
    // destructor
    ~LexAnalyzer() {
        delete v_untokenized_file_lines;
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
    std::vector<std::string>* v_untokenized_file_lines;
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

        std::smatch search_output;
        std::string replace_str;

        // throughout this portion of the code, <<< and >>> will be used to mark any strings that have already been tokenized
        // the regexes used are specifically made to ignore input that has already been tokenized
        for (std::string& v_str : *v_untokenized_file_lines) {
            
            // remove all comments
            v_str = std::regex_replace(v_str, t_comment, "");

            // identify all literal tokens
            while (std::regex_search(v_str, search_output, t_literal)) {
                // for all identified parts of the found string, append together in order to tokenize into one
                for (auto str : search_output) { replace_str += str; }
                v_str = std::regex_replace(v_str, t_literal, "<<<\"" + replace_str + "\" = literal>>>", std::regex_constants::format_first_only);
                replace_str = ""; // reset replace_str for next loop
            }

            // identify all keyword tokens and replace itself in string
            while (std::regex_search(v_str, search_output, t_keyword)) {
                v_str = std::regex_replace(v_str, t_keyword, "<<<\"" + search_output.str() + "\" = keyword>>>", std::regex_constants::format_first_only);
            }

            // identify all separator tokens and replace itself in string
            while (std::regex_search(v_str, search_output, t_separator)) {
                v_str = std::regex_replace(v_str, t_separator, "<<<\"" + search_output.str() + "\" = separator>>>", std::regex_constants::format_first_only);
            }

            // identify all integer tokens and replace itself in string
            while (std::regex_search(v_str, search_output, t_integer)) {
                v_str = std::regex_replace(v_str, t_integer, "<<<\"" + search_output.str() + "\" = integer>>>", std::regex_constants::format_first_only);
            }

            // identify all identifier tokens and replace itself in string
            while (std::regex_search(v_str, search_output, t_identifer)) {
                v_str = std::regex_replace(v_str, t_identifer, "<<<\"" + search_output.str() + "\" = identifier>>>", std::regex_constants::format_first_only);
            }

            // identify all operator tokens and replace itself in string
            while (std::regex_search(v_str, search_output, t_operator)) { 
                v_str = std::regex_replace(v_str, t_operator, "<<<\"" + search_output.str() + "\" = operator>>>", std::regex_constants::format_first_only);
            }

            // remove all whitespace
            v_str = std::regex_replace(v_str, t_whitespace, "");

            // delete and replace all the uncessary markers with proper formatting
            v_str = std::regex_replace(v_str, std::regex("<<<"), "");
            v_str = std::regex_replace(v_str, std::regex(">>>"), "\n");

            // convert tokenized string to char array to prep for writing
            const char* char_arr = v_str.c_str();
            // write tokenized char array to output file
            output_file->write(char_arr, v_str.length());
        }
    }

    // append all lines of input file to vector for easier handling
    void createInitialVector() {
        std::string line;
        v_untokenized_file_lines = new std::vector<std::string>;
        
        // until unable to get a line from input file, push line from input file onto vector
        while (getline(*input_file, line)) {
            v_untokenized_file_lines->push_back(line);
        }
    }
};

#endif