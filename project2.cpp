// Xietong Wei       The input test file needs to be named "test.ged".
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void checkTag(string& text, char num, int m);

int main() {
	int count = 0;
	int temp = 0;
	int mid = 0;
	int c = 0;
	string text;
	ifstream f;
	f.open("test.ged");
	if (f.is_open()) {
		while (!f.eof()) {
			if (c != 0) {
				cout << endl;
			}
			getline(f, text);
			int length = text.size();
			cout << "--> " << text << endl;
			cout << "<-- ";
			for (int i = 0; i < length; i++) {
				if (text[i] == ' ') {
					count++;
					temp = count;
				}
				if (temp == 1) {
					temp = 0;
					text[i] = '|';
				}
				if (temp == 2) {
					temp = 0;
					mid = i;
				}
			}
			if (text[0]) {
				checkTag(text, text[0], mid);
				cout << text;
			}
			count = 0;
			mid = 0;
			c++;
		}
	}
	f.close();
}

void checkTag(string& text, char num, int m) {
	if (num == '0') {
		int length = text.size();
		if (m > 0) {
			string s1;
			string ss = text.substr(m + 1, length - 1 - m);
			if ((ss == "INDI") || (ss == "FAM")) { 
				s1.append("0|" + ss + "|Y|" + text.substr(2, m - 2));
				text = s1;
			}
			else {
				s1.append("0|" + text.substr(2, m - 2) + "|Y|" + ss);
				text = s1;
			}
		}
		else {
			string s1;
			string ss = text.substr(2, length - 2);
			string temp = text;
			if ((ss == "HEAD") || (ss == "TRLR") || (ss == "NOTE")) { 
				s1.append(temp + "|Y");
				text = s1;
			}
			else {
				s1.append(temp + "|N");;
				text = s1;
			}
		}
	}
	else if (num == '1') {
		int length = text.size();
		string s1, ss;
		if (m > 0)
			ss = text.substr(2, m - 2);
		else
			ss = text.substr(2, length - 2);
		if ((ss == "NAME") || (ss == "SEX") || (ss == "BIRT") || (ss == "DEAT") || (ss == "FAMC") || (ss == "FAMS")
		|| (ss == "MARR") || (ss == "HUSB") || (ss == "WIFE") || (ss == "CHILL") || (ss == "DIV")) {
			if (m > 0) {
				s1.append("1|" + ss + "|Y|" + text.substr(m + 1, length - 1 - m));
				text = s1;
			}
			else {
				text.append("|Y");
			}
		}
		else {
			if (m > 0) {
				s1.append("1|" + ss + "|N|" + text.substr(m + 1, length - 1 - m));
				text = s1;
			}
			else {
				text.append("|N");
			}
		}
	}
	else {
		int length = text.size();
		string s1, ss;
		if (m > 0)
			ss = text.substr(2, m - 2);
		else
			ss = text.substr(2, length - 2);
		if (ss == "DATE") {
			if (m > 0) {
				s1.append("2|" + ss + "|Y|" + text.substr(m + 1, length - 1 - m));
				text = s1;
			}
			else {
				text.append("|Y");
			}
		}
		else {
			if (m > 0) {
				s1.append("2|" + ss + "|N|" + text.substr(m + 1, length - 1 - m));
				text = s1;
			}
			else {
				text.append("|N");
			}
		}
	}
}