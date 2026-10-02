#include <iostream>
#include <string>

struct ASTNode {
    std::string type;
    std::string value;
};

class SemanticAnalyzer {
public:
    bool analyze(const ASTNode& node) {
        if (node.type != "PrintStatement") {
            std::cerr << "[Semantic Error]: Unknown statement type '" << node.type << "'" << std::endl;
            return false;
        }

        if (node.value.empty()) {
            std::cerr << "[Semantic Warning]: Print statement contains empty string" << std::endl;
            return true;
        }

        std::cout << "[Semantic Analysis]: Passed. String literal is valid." << std::endl;
        return true;
    }
};

int main() {
    ASTNode inputNode = {"PrintStatement", "mostafa"};

    std::cout << "=== Phase 3: Semantic Analysis ===" << std::endl << std::endl;

    SemanticAnalyzer analyzer;
    bool isValid = analyzer.analyze(inputNode);

    if (isValid) {
        std::cout << "[Result]: AST Node is semantically valid and ready for IR Generation." << std::endl;
    }

    return 0;
}
