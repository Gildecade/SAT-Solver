#include "treeNode.h"

TreeNode::TreeNode(std::string cntt) : content{ cntt } {}

std::string TreeNode::getContent() const {
	// your code starts here
	return this->content;
}

TreeNode* TreeNode::getLeftChild() const {
	// your code starts here
	return this->leftChild;
}
TreeNode* TreeNode::getRightChild() const {
	// your code starts here
	return this->rightChild;
}

void TreeNode::updateLeftChild(TreeNode* lChild) {
	// your code starts here
	this->leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode* lChild, TreeNode* rChild) {
	// your code starts here
	this->leftChild = lChild;
	this->rightChild = rChild;
}

OperatorNode::OperatorNode(std::string cntt) : TreeNode{ cntt } {}

bool OperatorNode::evaluate(const std::map<std::string, bool>& assignment) const {
	// your code starts here
	if (this->getContent() == "-")
	{
		return !(this->getLeftChild()->evaluate(assignment));
	}
	else if (this->getContent() == "+")
	{
		bool left = this->getLeftChild()->evaluate(assignment);
		bool right = this->getRightChild()->evaluate(assignment);
		return (left or right);
	}
	else  // "*" means and
	{
		bool left = this->getLeftChild()->evaluate(assignment);
		bool right = this->getRightChild()->evaluate(assignment);
		return (left and right);
	}
}

ConstantNode::ConstantNode(std::string cntt) : TreeNode{ cntt } {}

bool ConstantNode::evaluate(const std::map<std::string, bool>& assignment) const {
	// your code starts here
	if (this->getContent() == "1")
	{
		return true;
	}
	return false;
}

VariableNode::VariableNode(std::string cntt) : TreeNode{ cntt } {}

bool VariableNode::evaluate(const std::map<std::string, bool>& assignment) const {
	// your code starts here
	std::string str = this->getContent();
	if (0 == assignment.count(str))
	{
		throw "Error: incomplete assignment";
	}
	return assignment.find(str)->second;
}

TreeNode::~TreeNode() {
	// your code starts here
	if (this->getLeftChild())
	{
		delete this->getLeftChild();
	}
	if (this->getRightChild())
	{
		delete this->getRightChild();
	}
	delete this;
}
