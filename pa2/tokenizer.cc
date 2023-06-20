#include "tokenizer.h"


Tokenizer::Tokenizer(std::string ln) {
	// complete the constructor
	for (size_t i = 0; i < ln.length(); i++)
	{
		Token token;
		if (' ' == ln[i])
		{
			continue;
		}
		if ('+' == ln[i])
		{
			token = {"+", "op"};
		}
		else if ('*' == ln[i])
		{
			token = { "*", "op" };
		}
		else if ('-' == ln[i])
		{
			token = { "-", "op" };
		}
		else if ('1' == ln[i])
		{
			token = { "1", "const" };
		}
		else if ('0' == ln[i])
		{
			token = { "0", "const" };
		}
		else if (isalpha(ln[i]))
		{
			int start = i;
			int length = 0;
			while (isalnum(ln[i]))
			{
				++i;
				++length;
			}
			--i;
			if (length > 10)
			{
				throw "Error: invalid input";
			}
			token = { ln.substr(start, length), "var" };
		}
		else if ('(' == ln[i])
		{
			token = { "(", "par" };
		}
		else if (')' == ln[i])
		{
			token = { ")", "par" };
		}
		else if (':' == ln[i])
		{
			token = { ":", "colon" };
		}
		else if (',' == ln[i])
		{
			token = { ",", "comma" };
		}
		else
		{
			throw "Error: invalid input";
		}

		this->tokenList.push_back(token);
	}
}

bool Tokenizer::advanceToken() {
	// your code starts here
	if (this->hasToken())
	{
		this->tokenList.pop_front();
	}
	return this->hasToken();
}

bool Tokenizer::hasToken() const {
	// your code starts here
	return this->tokenList.size() != 0;
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() {
	Token resultToken;
	// your code starts there
	if (this->hasToken())
	{
		resultToken = this->tokenList.front();
	}
	return resultToken;
}

