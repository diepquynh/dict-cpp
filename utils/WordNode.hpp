#ifndef __WNODE_HDR__
#define __WNODE_HDR__
#include <string>

class WordNode
{
	std::string word;
	std::string meaning;
	WordNode *left;
	WordNode *right;

public:
	WordNode()
	{
		word = "";
		meaning = "";
		left = NULL;
		right = NULL;
	}
	~WordNode()
	{
		delete left;
		delete right;
	}

	std::string getWord()
	{
		return this->word;
	}

	void setWord(std::string word)
	{
		this->word = word;
	}

	std::string getMeaning()
	{
		return this->meaning;
	}

	void setMeaning(std::string meaning)
	{
		this->meaning = meaning;
	}

	WordNode *getLeft()
	{
		return this->left;
	}

	void setLeft(WordNode *left)
	{
		this->left = left;
	}

	WordNode *getRight()
	{
		return this->right;
	}

	void setRight(WordNode *right)
	{
		this->right = right;
	}

	WordNode getData()
	{
		WordNode tmp;
		tmp.setWord(this->getWord());
		tmp.setMeaning(this->getMeaning());

		return tmp;
	}

	void setData(WordNode data)
	{
		this->setWord(data.getWord());
		this->setMeaning(data.getMeaning());
	}

	bool hasLeft()
	{
		return left != NULL;
	}

	bool hasRight()
	{
		return right != NULL;
	}

	bool isExternal()
	{
		return left == NULL && right == NULL;
	}
};

#endif /* __WNODE_HDR__ */