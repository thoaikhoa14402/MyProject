#include<iostream>
#include"Mylib.h"
#include<map>
#include<string>
#include<fstream>
#include<iterator>
using namespace std;

int count_1 = 0, count_2 = 0;
map<string, bool> check;
map<string, string> quiz;

void Read_File(ifstream& filein, map<string, string>& a) {
	string str1, str2;
	while (!filein.eof()) {
		getline(filein, str1, '-');
		filein.seekg(1, 1);
		getline(filein, str2);
		a.insert(pair<string, string>{str1, str2});
	}
}

// Hàm xuất để test
void output(map<string, string> a) {
	for (auto e : a) {
		cout << e.first << " : " << e.second;
		cout << endl;
	}
}

// Hàm check cú pháp
bool checkSyntax(string s1, string s2) {
	while (s1.find(" ") < s1.size()) {
		s1.replace(s1.find(" "), 1, "");
	}
	while (s2.find(" ") < s2.size()) {
		s2.replace(s2.find(" "), 1, "");
	}
	return (_stricmp(s1.c_str(), s2.c_str()) == 0);
}

// Hàm xử lý chính
void QuizGame() {
	int choice = -1;
	string answer;
	// dùng map check để đánh dấu những câu đã random ra để tránh ra lại những câu đó
	for (auto e : quiz) {
		check.insert(pair<string, bool>{e.first, false}); // khởi tạo các key mặc định là false
	}
	do {
		system("cls");
		map<string, string>::iterator item = quiz.begin();
		advance(item, rand() % quiz.size());
		if (check[item->first] == false) {
			SetColor(4);
			cout << "------------------- QUIZ GAME -------------------";
			SetColor(11);
			cout << "\nLET'S PREDICT THE CAPITAL OF GIVEN COUNTRY";
			SetColor(6);
			cout << "\n\nName of country: ";
			cout << item->first;
			SetColor(7);
			cout << "\n\n\tYour answer: ";
			getline(cin, answer);
			cout << "\n\tComputer's answer: ";
			cout << item->second << endl;
			if (checkSyntax(answer, item->second)) {
				SetColor(12);
				cout << "\nYES, YOU ARE RIGHT !!! \n\n";
				SetColor(10);
				cout << "The correct answers: " << ++count_1 << "\n\n";   
				cout << "The incorrect answers: " << count_2 << "\n\n";
			}
			else {
				SetColor(12);
				cout << "\nOOPS! YOU ARE WRONG :( \n\n";
				SetColor(10);
				cout << "The correct answers: " << count_1 << "\n\n";
				cout << "The incorrect answers: " << ++count_2 << "\n\n";
			}
			SetColor(9);
			cout << "------------------- OPTION -------------------\n";
			cout << "1 - Continue playing\n";
			cout << "0 - End game !!!\n\n";
			SetColor(7);
			cout << "Your choice: "; cin >> choice;
			cin.ignore();
			check[item->first] = true;
		}
	} while (choice != 0);
	if (choice == 0) {
		SetColor(6);
		cout << "\n\n------------------ STATISTICS ------------------\n\n";
		SetColor(10);
		cout << "The correct answers: " << count_1;
		cout << "\nThe incorrect answers: " << count_2;
		SetColor(4);
		cout << "\n\nBYE BYE !!!";
		cout << "\n\n";
		SetColor(0);
		ShowCur(0);
	}
}
int main() {
	srand(time(NULL)); // random name of states
	ifstream filein;
	filein.open("INPUT.txt");
	Read_File(filein, quiz);
	QuizGame();
	filein.close();
	return 0;
}