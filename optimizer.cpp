#include <iostream>
#include <string>
#include <vector>

struct IRInstruction {
    std::string opCode;
    std::string operand;
};

class IROptimizer {
public:
    std::vector<IRInstruction> optimize(const std::vector<IRInstruction>& inputIR) {
        std::vector<IRInstruction> optimizedIR;

        for (const auto& instr : inputIR) {
            // Trim empty operands or skip redundant instructions
            if (instr.opCode == "PARAM" && instr.operand.empty()) {
                continue;
            }
            optimizedIR.push_back(instr);
        }

        return optimizedIR;
    }
};

int main() {
    std::vector<IRInstruction> rawIR = {
        {"PARAM", "\"mostafa\""},
        {"CALL_PRINT", "1"}
    };

    std::cout << "=== Phase 5: Code Optimization ===" << std::endl << std::endl;

    IROptimizer optimizer;
    std::vector<IRInstruction> cleanIR = optimizer.optimize(rawIR);

    std::cout << "[Optimized IR Output]:" << std::endl;
    for (const auto& instr : cleanIR) {
        std::cout << "  " << instr.opCode << " " << instr.operand << std::endl;
    }

    return 0;
}
