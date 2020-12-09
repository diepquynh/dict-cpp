#include <iostream>
#include <fstream>
#include <sstream>
#include "utils/DictionaryTree.hpp"

//#define ABSOLUTE_PATH "E:\\Study\\OOP\\C++\\btl\\dictionary\\"

using namespace std;

void waitForEnter()
{
	cout << "Nhan enter de tiep tuc...";
	cin.get();
}

int importFromFile(string filename, DictionaryTree &dt)
{
#ifdef ABSOLUTE_PATH
	filename = ABSOLUTE_PATH + filename;
#endif
	ifstream ifs(filename);
	string str;

	if (ifs.fail()) {
		cout << "Loi mo file!" << endl;
		return -1;
	}

	while (getline(ifs, str)) {
		string word, meaning;

		istringstream iss(str);
		getline(iss, word, ';');
		getline(iss, meaning);
		dt.insert(word, meaning);
	}

	ifs.close();
	return 0;
}

void traverse(WordNode *root, ostream &os)
{
	if (root->hasLeft())
		traverse(root->getLeft(), os);

	os << root->getWord() << ";";
	os << root->getMeaning() << std::endl;

	if (root->hasRight())
		traverse(root->getRight(), os);
}

int exportToFile(string filename, DictionaryTree &dt)
{
#ifdef ABSOLUTE_PATH
	filename = ABSOLUTE_PATH + filename;
#endif
	ofstream ofs(filename);
	string str;

	if (ofs.fail()) {
		cout << "Loi mo file!" << endl;
		return -1;
	}

	traverse(dt.getRoot(), ofs);
	ofs.close();
	return 0;
}

int main()
{
	DictionaryTree dt;
	int choice;

	do {
		string word, meaning;
		WordNode *wn;

		cout << "Tu dien C++" << endl;
		cout << "*. Thoat khoi chuong trinh" << endl;
		cout << "1. Nhap du lieu tu dien tu file" << endl;
		cout << "2. Tim kiem 1 tu" << endl;
		cout << "3. Thay doi nghia 1 tu" << endl;
		cout << "4. Xoa 1 tu trong tu dien" << endl;
		cout << "5. Xuat cac tu da co trong tu dien ra man hinh" << endl;
		cout << "6. Xuat cac tu da co trong tu dien ra file" << endl;
		cout << "Moi nhap lua chon: ";
		cin >> choice;
		cin.ignore();

		if (choice > 1 && choice < 7) {
			if (dt.getRoot() == NULL) {
				cout << "Chua nhap du lieu tu dien! Dang tien hanh nhap du lieu..." << endl;
				choice = 1;
			}
		}

		cout << endl << endl;
		switch (choice) {
		case 1:
			if (!importFromFile("dict.txt", dt))
				cout << "Nhap du lieu thanh cong! ";
			waitForEnter();
			break;
		case 2:
			cout << "Nhap tu can tim kiem: ";
			getline(cin, word);

			wn = dt.search(word);
			if (!wn) {
				cout << word << " khong ton tai!" << endl;
				waitForEnter();
				break;
			}

			cout << "Tu: " << wn->getWord() << endl;
			cout << "Nghia: " << wn->getMeaning() << endl;
			waitForEnter();
			break;
		case 3:
			cout << "Nhap tu can tim kiem: ";
			getline(cin, word);

			wn = dt.search(word);
			if (!wn) {
				cout << word << " khong ton tai!" << endl;
				waitForEnter();
				break;
			}

			cout << "Tu: " << wn->getWord() << endl;
			cout << "Nghia cu: " << wn->getMeaning() << endl;
			cout << "Nhap nghia moi (enter de bo qua): ";
			getline(cin, meaning);

			if (meaning.length() != 0) {
				dt.modify(word, meaning);
				cout << "Thay doi thanh cong! ";
				waitForEnter();
			}
			break;
		case 4:
			cout << "Nhap tu can xoa: ";
			getline(cin, word);
			dt.remove(word);
			cout << "Xoa thanh cong! ";
			waitForEnter();
			break;
		case 5:
			dt.print();
			waitForEnter();
			break;
		case 6:
			if (!exportToFile("out.txt", dt))
				cout << "Xuat du lieu ra file thanh cong! ";
			waitForEnter();
			break;
		default:
			cout << "Thank you for using our software!" << endl;
			cout << "From IT1 with love <3" << endl;
			break;
		}
		cout << endl << endl;
	} while (choice > 0 && choice < 7);

	return 0;
}