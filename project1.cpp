#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

//Map function to define keywords in C++ language
map<string, string> keywords = {

    {"double", "keyword"}, {"new", "keyword"}, {"switch", "keyword"}, {"auto", "keyword"}, {"else", "keyword"},
    {"template", "keyword"}, {"break", "keyword"}, {"enum", "keyword"}, {"private", "keyword"}, {"this", "keyword"},
    {"case", "keyword"}, {"throw", "keyword"}, {"catch", "keyword"}, {"float", "keyword"}, {"public", "keyword"},
    {"try", "keyword"}, {"char", "keyword"}, {"for", "keyword"}, {"typedef", "keyword"}, {"class", "keyword"},
    {"return", "keyword"}, {"const", "keyword"}, {"goto", "keyword"}, {"short", "keyword"}, {"unsigned", "keyword"},
    {"continue", "keyword"}, {"if", "keyword"}, {"signed", "keyword"}, {"default", "keyword"}, {"inline", "keyword"},
    {"void", "keyword"}, {"delete", "keyword"}, {"int", "keyword"}, {"static", "keyword"}, {"do", "keyword"},
    {"long", "keyword"}, {"struct", "keyword"}, {"while", "keyword"}, {"main", "keyword"}, {"std::cout", "keyword"},
    {"std::endl", "keyword"}, {"cout", "keyword"}, {"endl", "keyword"},

};

//Map function to define operators in C++ language
map<string, string> operators = {

    {"+", "operator"}, {"-", "operator"}, {"*", "operator"}, {"/", "operator"}, {"%", "operator"},
    {"++", "operator"}, {"--", "operator"}, {"+=", "operator"}, {"-=", "operator"}, {"*=", "operator"},
    {"/=", "operator"}, {"%=", "operator"}, {"!=", "operator"}, {"=", "operator"}, {">", "operator"},
    {"<", "operator"}, {">=", "operator"}, {"<=", "operator"}, {"&&", "operator"}, {"||", "operator"},
    {"!", "operator"}, {"|", "operator"}, {"&", "operator"}, {"^", "operator"}, {"~", "operator"},
    {"<<", "operator"}, {">>", "operator"},
 
};

//Map function to define separators in C++ language
map<char, string> separators = {

    {';', "separator"}, {'(', "separator"}, {')', "separator"}, {'{', "separator"},
    {'}', "separator"}, {'[', "separator"}, {']', "separator"}, 

};

//Boolean type isOperator function to check if the string match values in "operators" map
bool isOperator(const string& opt) {

    //find() and end() functions to search for a match in operators map
    return operators.find(opt) != operators.end();

}

//Boolean type isKeyword function to check if the string match values in "keywords" map
bool isKeyword(const string& word) {

    //find() and end() functions to search for a match in keywords map
    return keywords.find(word) != keywords.end();

}

//Boolean type isSeparator function to check if the character match values in "separators" map
bool isSeparator(char c) {

    //find() and end() functions to search for a match in separators map
    return separators.find(c) != separators.end();

}

//Boolean type isInteger function to check if each character c is a digit
//If all characters are digits, then the token t is an integer.
bool isInteger(const string& integer){

    //Return false if the string is empty
    if (integer.empty()) {
        return false;
    }

    // for loop check each character in the token
    for (char c : integer) {

        // If any character is not a digit, it's not an integer
        if (!isdigit(c)) {
            return false;
        }
    }

    // If all characters are digits, so it's an integer
    return true;
}

// Void function to tokenize the content of the input file
void tokenize(const string& line) {

    stringstream ss(line);  // Using stringstream to extract words

    string token;  // Define a string variable token

    vector<string> tokens;  // Define a string type vector to store tokens

    while (ss >> token) {  // Loop that reads each token in stringstream ss

        string lexeme = "";  // Initialize empty string lexeme

        for (char c : token) {  // Loop each character in tokens to search for separators

            if (isSeparator(c)) {  // Call isSeparator function to check character c

                if (!lexeme.empty()) {  // Avoid empty lexemes being added to the vector

                    lexeme = c;  // assign char c to lexeme

                    tokens.push_back(lexeme); // Add lexemes to tokens if it is not empty

                    lexeme = "";  // Reset the lexeme for the next check

                }
            
            } else {  // Build up the current token until a separator is encountered

                lexeme += c;

            }
        }

        if (!lexeme.empty()) {  // Add the remaining lexemes to vector tokens

            tokens.push_back(lexeme);

        }

    }

    // Use auto to automatically infer the type of the variable based on its initializer
    // For loop to classify each token t in the vector "tokens"
    for (const auto& t : tokens) {

        // Call isKeyword function to check for token t
        if (isKeyword(t)) {

            cout << "\"" << t << "\" = " << keywords[t] << endl;

        } else if (isOperator(t)) {  // Call isOperator function to check for token t

            cout << "\"" << t << "\" = " << operators[t] << endl;

        } else if (isSeparator(t[0])) {  // Call isSeparator function to check for token t

            cout << "\"" << t << "\" = " << separators[t[0]] << endl;

        } else if (isInteger(t)) {  // Call isInteger function to check for token t

            cout << "\"" << t << "\" = integer" << endl;

        } else if (t != " " && t != "\t") {  // t is an identifier if t is not any of the above type

            cout << "\"" << t << "\" = identifier" << endl;

        }

    }

}


int main() {

    // Read the input file
    ifstream inputFile("C:\\Users\\jwinu\\Desktop\\LA1\\program.txt");

    // Generate an error message if the file cannot be opened
    if (!inputFile) {

        cerr << "Error opening input file." << endl;  // Use cerr to send an error message

        return 1;

    }

    // Initialize string "line"
    string line;

    // getline function to read a line from the input file
    // while loop to read all lines in the file
    while (getline(inputFile, line)) {

        // Call tokenize function to tokenize lexemes in each line
        tokenize(line);

    }

    // Close the file
    inputFile.close();

    // Program is terminated
    return 0;

}
