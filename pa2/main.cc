#include "tseitinTransformer.h"
#include "satSolver.h"
#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string& line, std::string& formulaStr, std::string& assignmentStr) {
    // your code starts here
    size_t index = line.find(";");
    if (index > line.length())
    {
        throw "Error: invalid input";
    }
    formulaStr = line.substr(0, index);
    assignmentStr = line.substr(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(index) + 1);
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
    std::string line; // store each input line
    while (std::getline(std::cin, line)) // continuously asking for new inputs from standard input
    {
        // your code starts here
        try
        {
            FormulaParser* formulaParser = new FormulaParser(line);
            TreeNode* node = formulaParser->getTreeRoot();
            TseitinTransformer tsTransformer(node);
            if (node == nullptr)
            {
                throw "Error: invalid input";
            }
            std::vector<std::vector<int>> cnf = tsTransformer.transform();
            // std::cout << tsTransformer.cnfString() << std::endl;
            if (satCallingMiniSat(tsTransformer.getVarNum(), cnf))
            {
                std::cout << "sat" << std::endl;
            }
            else
            {
                std::cout << "unsat" << std::endl;
            }
        }
        catch (const char* e)
        {
            std::cout << e << std::endl;
        }
    }
}
