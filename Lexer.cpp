#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum TokenType {
    TOKEN_KEYWORD,       // pri
    TOKEN_LPAREN_QUOTE,  // ("
    TOKEN_STRING,        // "mostafa" or any string content
    TOKEN_QUOTE_RPAREN,  // ")
    TOKEN_ERROR          // Syntax errors
};

struct Token {
    TokenType type;
    std::string value;
    int line;
};

std::vector<Token> tokenize(const std::string& line, int lineNumber) {
    std::vector<Token> tokens;

    if (line.empty()) {
        return tokens;
    }

    size_t priPos = line.find("pri");
    size_t openPos = line.find("(\"");
    size_t closePos = line.find("\")");

    // Syntax Check 1: Ensure 'pri' and '("' exist in correct sequence
    if (priPos == std::string::npos || openPos == std::string::npos || openPos < priPos) {
        std::cerr << "[Lexer Error] Line " << lineNumber << ": Invalid syntax. Expected 'pri(\"'" << std::endl;
        tokens.push_back({TOKEN_ERROR, "", lineNumber});
        return tokens;
    }

    // Syntax Check 2: Ensure '")' exists and closes properly
    if (closePos == std::string::npos || closePos <= openPos + 1) {
        std::cerr << "[Lexer Error] Line " << lineNumber << ": Missing closing brackets '\")'" << std::endl;
        tokens.push_back({TOKEN_ERROR, "", lineNumber});
        return tokens;
    }

    // Tokenization
    tokens.push_back({TOKEN_KEYWORD, "pri", lineNumber});
    tokens.push_back({TOKEN_LPAREN_QUOTE, "(\"", lineNumber});

    // Extract dynamic text content between (" and ")
    std::string extractedString = line.substr(openPos + 2, closePos - (openPos + 2));
    tokens.push_back({TOKEN_STRING, extractedString, lineNumber});

    tokens.push_back({TOKEN_QUOTE_RPAREN, "\")", lineNumber});

    return tokens;
}

int main() {
    std::ifstream file("script.ml");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open source file 'script.ml'" << std::endl;
        return 1;
    }

    std::string line;
    int lineNumber = 1;

    std::cout << "=== Phase 1: Lexical Analysis (Tokens Output) ===" << std::endl << std::endl;

    while (std::getline(file, line)) {
        std::vector<Token> tokens = tokenize(line, lineNumber);

        for (const auto& token : tokens) {
            switch (token.type) {
                case TOKEN_KEYWORD:
                    std::cout << "[TOKEN_KEYWORD]      -> " << token.value << std::endl;
                    break;
                case TOKEN_LPAREN_QUOTE:
                    std::cout << "[TOKEN_LPAREN_QUOTE] -> " << token.value << std::endl;
                    break;
                case TOKEN_STRING:
                    std::cout << "[TOKEN_STRING]       -> " << token.value << std::endl;
                    break;
                case TOKEN_QUOTE_RPAREN:
                    std::cout << "[TOKEN_QUOTE_RPAREN] -> " << token.value << std::endl;
                    break;
                case TOKEN_ERROR:
                    std::cout << "[TOKEN_ERROR]        -> Tokenization Failed" << std::endl;
                    break;
            }
        }
        lineNumber++;
    }

    file.close();
    return 0;
}