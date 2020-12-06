#ifndef __DICT_HDR__
#define __DICT_HDR__
#include <iostream>
#include "Hash.hpp"
#include "WordNode.hpp"

class DictionaryTree
{
	WordNode *root;

	WordNode *insert(WordNode data, WordNode *root);
	WordNode *remove(std::string word, WordNode *root);
	WordNode *search(std::string word, WordNode *root);
	void print(WordNode *root);

public:
	DictionaryTree()
	{
		root = NULL;
	}

	~DictionaryTree()
	{
		delete root;
	}

	WordNode *getRoot()
	{
		return root;
	}

	void setRoot(WordNode *root)
	{
		this->root = root;
	}

	void insert(std::string word, std::string meaning);
	void remove(std::string word);
	WordNode *search(std::string word);
	void modify(std::string word, std::string new_word, std::string new_meaning);
	void print();
};

// Phuong thuc chen du lieu tu moi
WordNode *DictionaryTree::insert(WordNode data, WordNode *root)
{
	// Kiem tra root va tao moi
	if (!root) {
		root = new WordNode;
		root->setData(data);
		return root;
	}

	/*
	 * Su dung hash de them tu vao cay, dong thoi kiem tra tinh
	 * ton tai cua tu
	 */
	unsigned int dHash = DJBHash(data.getWord());
	unsigned int rHash = DJBHash(root->getWord());
	if (rHash > dHash)
		root->setLeft(this->insert(data, root->getLeft()));
	else if (rHash < dHash)
		root->setRight(this->insert(data, root->getRight()));

	// Them tu moi thanh cong hoac tu can them da ton tai
	return root;
}

void DictionaryTree::insert(std::string word, std::string meaning)
{
	WordNode data;
	data.setWord(word);
	data.setMeaning(meaning);

	this->setRoot(this->insert(data, this->getRoot()));
}

// Phuong thuc tim kiem
WordNode *DictionaryTree::search(std::string word, WordNode *root)
{
	// Tu do khong con tai hoac cay chua duoc khoi tao
	if (!root)
		return root;

	unsigned int wHash = DJBHash(word);
	unsigned int rHash = DJBHash(root->getWord());
	//Da tim thay nut cua tu can tim
	if (rHash == wHash)
		return root;

	if (rHash > wHash)
		return this->search(word, root->getLeft());

	return this->search(word, root->getRight());
}

WordNode *DictionaryTree::search(std::string word)
{
	return this->search(word, this->getRoot());
}

// Phuong thuc xoa
WordNode *DictionaryTree::remove(std::string word, WordNode *root)
{
	if (root == NULL)
		return root;

	// Su dung hash de kiem tra tinh ton tai cua tu
	unsigned int wHash = DJBHash(word);
	unsigned int rHash = DJBHash(root->getWord());
	if (rHash > wHash)
		root->setLeft(this->remove(word, root->getLeft()));
	else if (rHash < wHash)
		root->setRight(this->remove(word, root->getRight()));
	else {
		// TH 1: Nut chi co 1 la hoac khong co la / khong co nut con
		if (!root->hasLeft()) {
			WordNode *tmp = root->getRight();

			if (tmp)
				root->setRight(NULL);

			delete root;
			return tmp;
		} else if (!root->hasRight()) {
			WordNode *tmp = root->getLeft();

			if (tmp)
				root->setLeft(NULL);

			delete root;
			return tmp;
		}

		// TH 2: Nut co 2 nut con / 2 la
		WordNode *tmp = root->getRight();
		while (tmp && tmp->hasLeft())
			tmp = tmp->getLeft();

		root->setData(tmp->getData());
		root->setRight(remove(tmp->getWord(), root->getRight()));
	}

	return root;
}

void DictionaryTree::remove(std::string word)
{
	this->setRoot(this->remove(word, this->getRoot()));
}

// Phuong thuc sua
void DictionaryTree::modify(std::string word, std::string new_word, std::string new_meaning)
{
	WordNode *wn = this->search(word);

	wn->setWord(new_word);
	wn->setMeaning(new_meaning);
}

// Phuong thuc in ra man hinh
void DictionaryTree::print(WordNode *root)
{
	if (root->hasLeft())
		this->print(root->getLeft());

	std::cout << "Tu: " << root->getWord() << std::endl;
	std::cout << "Nghia: " << root->getMeaning() << std::endl;

	if (root->hasRight())
		this->print(root->getRight());
}

void DictionaryTree::print()
{
	this->print(this->getRoot());
}
#endif /* __DICT_HDR__ */