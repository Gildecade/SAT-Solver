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
        std::string formulaStr; // store the formula string
        std::string assignmentStr; // store the assignment string
        // your code starts here
        try
        {
            parseLine(line, formulaStr, assignmentStr);
            FormulaParser* formulaParser = new FormulaParser(formulaStr);
            AssignmentParser* assignmentParser = new AssignmentParser(assignmentStr);
            TreeNode* node = formulaParser->getTreeRoot();
            std::map<std::string, bool> map = assignmentParser->parseAssignment();
            if (node == nullptr)
            {
                throw "Error: invalid input";
            }
            if (node->evaluate(map))
            {
                std::cout << "1" << std::endl;
            }
            else
            {
                std::cout << "0" << std::endl;
            }
        }
        catch (const char* e)
        {
            std::cout << e << std::endl;
        }
    }
}
