#include "tseitinTransformer.h"
#include <string>
#include <iostream>

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
	if (subRoot == nullptr)
	{
		return 0;
	}
	std::string content = subRoot->getContent();
	int leftID = transSubformula(subRoot->getLeftChild());
	int rightID = transSubformula(subRoot->getRightChild());
	std::string left;
	if (content[0] == '+')
	{
		left = std::to_string(leftID);
		std::string right = std::to_string(rightID);
		left.append(content);
		left.append(right);

	}
	else if (content[0] == '*')
	{
		left = std::to_string(leftID);
		std::string right = std::to_string(rightID);
		left.append(content);
		left.append(right);
	}
	else if (content[0] == '-')
	{
		left = "-";
		left.append(std::to_string(leftID));
	}
	else
	{
		left = content;
	}
	int curID = 0;
	if (this->varIdTable.count(left) == 0)
	{
		curID = this->varIdCounter++;
		this->varIdTable.insert(std::pair<std::string, int>(left, curID));
	}
	else
	{
		curID = this->varIdTable[left];
	}
	if (content[0] == '+')
	{
		addOrEq(curID, leftID, rightID);

	}
	else if (content[0] == '*')
	{
		addAndEq(curID, leftID, rightID);
	}
	else if (content[0] == '-')
	{
		addNegEq(curID, leftID);
	}
	return curID;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
	std::vector<int> clauseOne;
	clauseOne.push_back(-curID);
	clauseOne.push_back(-childID);
	std::vector<int> clauseTwo;
	clauseTwo.push_back(curID);
	clauseTwo.push_back(childID);
	this->cnf.push_back(clauseOne);
	this->cnf.push_back(clauseTwo);
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
	std::vector<int> clauseOne;
	clauseOne.push_back(-curID);
	clauseOne.push_back(leftID);
	clauseOne.push_back(rightID);
	this->cnf.push_back(clauseOne);
	std::vector<int> clauseTwo;
	clauseTwo.push_back(-leftID);
	clauseTwo.push_back(curID);
	this->cnf.push_back(clauseTwo);
	std::vector<int> clauseThree;
	clauseThree.push_back(-rightID);
	clauseThree.push_back(curID);
	this->cnf.push_back(clauseThree);
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
	std::vector<int> clauseOne;
	clauseOne.push_back(-curID);
	clauseOne.push_back(leftID);
	this->cnf.push_back(clauseOne);
	std::vector<int> clauseTwo;
	clauseTwo.push_back(-curID);
	clauseTwo.push_back(rightID);
	this->cnf.push_back(clauseTwo);
	std::vector<int> clauseThree;
	clauseThree.push_back(-leftID);
	clauseThree.push_back(-rightID);
	clauseThree.push_back(curID);
	this->cnf.push_back(clauseThree);
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
	this->transSubformula(this->formulaRoot);
	std::vector<int> wholeFormula;
	wholeFormula.push_back(this->getVarNum());
	this->cnf.push_back(wholeFormula);
	return this->cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  // your code starts here
  for (std::vector<std::vector<int>>::const_iterator it = this->cnf.begin(); it != cnf.end(); ++it)
  {
	  result.append("[");
	  std::vector<int> clause = *it;
	  for (std::vector<int>::iterator itt = clause.begin(); itt != clause.end(); ++itt)
	  {
		  if (itt != clause.begin())
		  {
			  result.append(", ");
		  }
		  result.append(std::to_string(*itt));
	  }
	  result.append("]");
  }
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
	return this->varIdCounter - 1;
}
