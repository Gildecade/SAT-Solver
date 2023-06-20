#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"
#include <iostream>

FormulaParser::FormulaParser(std::string ln) : tknzr{ new Tokenizer{ln} } {}

TreeNode* FormulaParser::parseConjTerm() {
	// your code starts here
	TreeNode *term = parseTerm();
	while (this->tknzr->hasToken())
	{
		Token curr = this->tknzr->getToken();
		if (curr.type == "op" and curr.content == "*")
		{
			this->tknzr->advanceToken();
			OperatorNode *node = new OperatorNode(curr.content);
			TreeNode* term2 = parseTerm();
			node->updateChildren(term, term2);
			term = node;
		}
		else
		{
			break;
		}
	}
	return term;
}

TreeNode* FormulaParser::parseTerm() {
	// your code starts here
	TreeNode *node = nullptr;
	if (this->tknzr->hasToken())
	{
		Token curr = this->tknzr->getToken();
		if (curr.type == "par" and curr.content == "(")
		{
			this->tknzr->advanceToken();
			node = parseFormula();
			if (this->tknzr->getToken().content != ")")
			{
				throw "Error: invalid input";
			}
		}
		else if (curr.type == "const")
		{
			node = new ConstantNode(curr.content);
		}
		else if (curr.type == "op" and curr.content == "-")
		{
			this->tknzr->advanceToken();
			node = new OperatorNode(curr.content);
			TreeNode* succ = parseTerm();
			node->updateLeftChild(succ);
			return node;
		}
		else if (curr.type == "var")
		{
			node = new VariableNode(curr.content);
		}
		this->tknzr->advanceToken();
	}
	return node;
}

TreeNode* FormulaParser::parseFormula() {
	// your code starts here
	TreeNode *conjTerm =  parseConjTerm();
	while (this->tknzr->hasToken())
	{
		Token curr = this->tknzr->getToken();
		if (curr.type == "op" and curr.content == "+")
		{
			this->tknzr->advanceToken();
			OperatorNode* node = new OperatorNode(curr.content);
			TreeNode* conjTerm2 = parseConjTerm();
			node->updateChildren(conjTerm, conjTerm2);
			conjTerm = node;
		}
		else
		{
			break;
		}
	}
	return conjTerm;
}

TreeNode* FormulaParser::getTreeRoot() {
	// your code starts here
	TreeNode* root = parseFormula();
	if (this->tknzr->hasToken())
	{
		throw "Error: invalid input";
	}
	return root;
}

FormulaParser::~FormulaParser() {
	// your code starts here
	delete this->tknzr;
	this->getTreeRoot()->~TreeNode();
}

AssignmentParser::AssignmentParser(std::string ln) : tknzr{ new Tokenizer{ln} } {}

std::map<std::string, bool> AssignmentParser::parseAssignment() {
	std::map<std::string, bool> results;
	// your code starts here
	while (this->tknzr->hasToken())
	{
		Token curr = this->tknzr->getToken();
		if (curr.type == "var")
		{
			this->tknzr->advanceToken();
			Token succ = this->tknzr->getToken();
			if (succ.type == "colon")
			{
				this->tknzr->advanceToken();
				succ = this->tknzr->getToken();
				if (succ.type == "const")
				{
					this->tknzr->advanceToken();
					bool flag = false;
					if (succ.content == "1")
					{
						flag = true;
					}
					if (0 == results.count(curr.content))
					{
						results.insert(std::pair<std::string, bool>(curr.content, flag));
					}
					else if (results[curr.content] != flag)
					{
						throw "Error: contradicting assignment";
					}
				}
				else if (succ.type == "")
				{
					throw "Error: incomplete assignment";
				}
				else
				{
					throw "Error: invalid input";
				}
			}
			else
			{
				throw "Error: invalid input";
			}
			succ = this->tknzr->getToken();
			if (succ.type == "comma")
			{
				if (!this->tknzr->advanceToken())
				{
					throw "Error: invalid input";
				}
			}
			else if (succ.type == "")
			{
				break;
			}
			else
			{
				throw "Error: invalid input";
			}
		}
		else
		{
			throw "Error: invalid input";
		}
	}
	return results;
}

AssignmentParser::~AssignmentParser() {
	// your code starts here
	delete this->tknzr;
}
