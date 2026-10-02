#include <iostream>
#include <string>
#include <vector>

struct ASTNode {
    std::string type;
    std::string value;
};

struct IRInstruction {
    std::string opCode;
    std::string operand;
};

class IRGenerator {
public:
    std::vector<IRInstruction> generate(const ASTNode& node) {
        std::vector<IRInstruction> ir;

        if (node.type == "PrintStatement") {
            ir.push_back({"PARAM", "\"" + node.value + "\""});
            ir.push_back({"CALL_PRINT", "1"});
        }

        return ir;
    }
};

int main() {
    ASTNode inputNode = {"PrintStatement", "mostafa"};

    std::cout << "=== Phase 4: Intermediate Representation (IR) Generation ===" << std::endl << std::endl;

    IRGenerator irGen;
    std::vector<IRInstruction> irInstructions = irGen.generate(inputNode);

    std::cout << "[Generated IR Code]:" << std::endl;
    for (const auto& instr : irInstructions) {
        std::cout << "  " << instr.opCode << " " << instr.operand << std::endl;
    }

    return 0;
}
