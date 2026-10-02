#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

enum TokenType {
    TOKEN_KEYWORD,
    TOKEN_LPAREN_QUOTE,
    TOKEN_STRING,
    TOKEN_QUOTE_RPAREN
};

struct Token {
    TokenType type;
    std::string value;
};

struct ASTNode {
    std::string type;
    std::string value;
};

// 1. Lexer Phase
std::vector<Token> runLexer(const std::string& code) {
    std::vector<Token> tokens;
    size_t pos = 0;

    if (code.find("pri(") == 0) {
        tokens.push_back({TOKEN_KEYWORD, "pri"});
        pos += 4;
        
        size_t endQuote = code.find("\")", pos);
        if (endQuote != std::string::npos) {
            tokens.push_back({TOKEN_LPAREN_QUOTE, "(\""});
            tokens.push_back({TOKEN_STRING, code.substr(pos, endQuote - pos)});
            tokens.push_back({TOKEN_QUOTE_RPAREN, "\")"});
        }
    }
    return tokens;
}

// 2. Parser Phase
ASTNode runParser(const std::vector<Token>& tokens) {
    if (tokens.size() == 4 && tokens[0].type == TOKEN_KEYWORD && tokens[2].type == TOKEN_STRING) {
        return ASTNode{"PrintStatement", tokens[2].value};
    }
    return ASTNode{"ERROR", ""};
}

// 3. Execution Phase (Code Generation & Output)
void execute(const ASTNode& node) {
    if (node.type == "PrintStatement") {
        std::cout << node.value << std::endl;
    } else {
        std::cerr << "Execution Error: Invalid AST node." << std::endl;
    }
}

int main() {
    std::ifstream file("script.ml");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open script.ml" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code = buffer.str();
    file.close();

    // Pipeline Execution
    std::vector<Token> tokens = runLexer(code);
    ASTNode ast = runParser(tokens);
    
    // Output
    execute(ast);

    return 0;
}