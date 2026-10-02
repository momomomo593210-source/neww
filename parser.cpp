#include <iostream>
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

class Parser {
private:
    std::vector<Token> tokens;

public:
    Parser(const std::vector<Token>& t) : tokens(t) {}

    ASTNode parse() {
        if (tokens.size() == 4 &&
            tokens[0].type == TOKEN_KEYWORD &&
            tokens[1].type == TOKEN_LPAREN_QUOTE &&
            tokens[2].type == TOKEN_STRING &&
            tokens[3].type == TOKEN_QUOTE_RPAREN) {

            return ASTNode{"PrintStatement", tokens[2].value};
        }

        std::cerr << "[Parser Error]: Invalid statement structure" << std::endl;
        return ASTNode{"ERROR", ""};
    }
};

int main() {
    std::vector<Token> inputTokens = {
        {TOKEN_KEYWORD, "pri"},
        {TOKEN_LPAREN_QUOTE, "(\""},
        {TOKEN_STRING, "mostafa"},
        {TOKEN_QUOTE_RPAREN, "\")"}
    };

    std::cout << "=== Phase 2: Syntax Analysis (Parser & AST) ===" << std::endl << std::endl;

    Parser parser(inputTokens);
    ASTNode ast = parser.parse();

    if (ast.type != "ERROR") {
        std::cout << "[AST Node Created Successfully]" << std::endl;
        std::cout << "  |- Node Type  : " << ast.type << std::endl;
        std::cout << "  |- Print Value: \"" << ast.value << "\"" << std::endl;
    }

    return 0;
}
