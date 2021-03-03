#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
#include"bprinter/table_printer.h"
using namespace std;

typedef struct indi {
    string ID;
    string name;
    string gender;
    string birth;
    int age;
    string alive;
    string death;
    string child[1000];
    string spouse[1000];
} INDI;

typedef struct fam {
    string ID;
    string married;
    string divorced;
    string husband_id;
    string husband_name;
    string wife_id;
    string wife_name;
    string children[1000];
} FAM;

void checkTag(string& text, char num, int m);
INDI collectINDIData(string *store, int i, INDI i1);
FAM collectFAMData(string *store, int i, FAM i1);
int calAge(string date, string old);
string transOldFormat(string cd);
int getCurrentDate(string d);
string getHusbandName(vector<INDI> v1, string ID);
string getWifeName(vector<INDI> v1, string ID);

int main(int argc, char** argv) {
	int count = 0;
	int temp = 0;
	int mid = 0;
    int c1 = 0;
    string store[6000];
    vector<INDI> v1;
    vector<FAM> v2;
	string text;
	ifstream f;
	f.open("GEDCOM.ged");
	if (f.is_open()) {
		while (!f.eof()) {
			getline(f, text);
			int length = text.size();
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
                store[c1] = text;
                c1++;
			}
			count = 0;
			mid = 0;
		}
        for (int i = 0; i < c1; i++) {
            if ((store[i][0] == '0') && (store[i].substr(2, 4) == "INDI")) {
                INDI i1;
                i1.ID = store[i].substr(9, store[i].size() - 9);
                i1.alive = "True";
                INDI i2 = collectINDIData(store, i, i1);
                time_t current = time(0);
                string date = ctime(&current);
                i2.age = calAge(date, i2.birth);
                if (i2.death == "")
                    i2.death = "NA";
                //if (i2.child[0] == "")
                    //i2.child = "{}";
                v1.push_back(i2);
            }
            else if ((store[i][0] == '0') && (store[i].substr(2, 3) == "FAM")) {
                FAM i1;
                i1.ID = store[i].substr(8, store[i].size() - 8);
                i1.divorced = "NA";
                FAM i2 = collectFAMData(store, i, i1);
                i2.husband_name = getHusbandName(v1, i2.husband_id);
                i2.wife_name = getWifeName(v1, i2.wife_id);
                v2.push_back(i2);
            }
        }

        vector<FAM>::iterator it;
        for (it = v2.begin(); it != v2.end(); it++) {
            cout << (*it).ID << endl;
            cout << (*it).husband_name << endl;
            cout << (*it).wife_name << endl;
            cout << endl;
        }

        // vector<INDI>::iterator it;
        // for (it = v1.begin(); it != v1.end(); it++) {
        //     cout << (*it).ID << endl;
        //     cout << (*it).name << endl;
        //     cout << (*it).birth << endl;
        //     if ((*it).gender != "")
        //         cout << (*it).gender << endl;
        //     else
        //         cout << "NA" << endl;
        //     cout << (*it).alive << endl;
        //     cout << (*it).death << endl;
        //     cout << (*it).age << endl;
        // }
	}
	f.close();
}

string getHusbandName(vector<INDI> v1, string ID) {
    vector<INDI>::iterator it;
    for (it = v1.begin(); it != v1.end(); it++) {
        if ((*it).ID == ID)
            return (*it).name;
    }
}

string getWifeName(vector<INDI> v1, string ID) {
    vector<INDI>::iterator it;
    for (it = v1.begin(); it != v1.end(); it++) {
        if ((*it).ID == ID)
            return (*it).name;
    }
}

int getCurrentDate(string d) {
    if (d == "Jan")
        return 1;
    else if (d == "Feb")
        return 2;
    else if (d == "Mar")
        return 3;
    else if (d == "Apr")
        return 4;
    else if (d == "May")
        return 5;
    else if (d == "Jun")
        return 6;
    else if (d == "Jul")
        return 7;
    else if (d == "Aug")
        return 8;
    else if (d == "Sep")
        return 9;
    else if (d == "Oct")
        return 10;
    else if (d == "Nov")
        return 11;
    else if (d == "Dec")
        return 12;
}

string transOldFormat(string cd) {
    int start, end;
    int c = 0;
    string d;
    for (int i = 0; i < cd.size(); i++) {
        if ((cd[i] == ' ') && (c == 0)) {
            start = i;
            c++;
        }
        else if ((cd[i] == ' ') && (c == 1)) {
            end = i;
            c++;
        }
    }
    if (cd.substr(start+1, end-start-1) == "JAN") {
        string temp = "";
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "01-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "01-" + cd.substr(0, start));
    }
    else if (cd.substr(start+1, end-start-1) == "FEB") {
        string temp;
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "02-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "02-" + cd.substr(0, start));
    }
    else if (cd.substr(start+1, end-start-1) == "MAR") {
        string temp;
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "03-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "03-" + cd.substr(0, start));
    }
    else if (cd.substr(start+1, end-start-1) == "APR") {
        string temp;
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "04-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "04-" + cd.substr(0, start));
    }
    else if (cd.substr(start+1, end-start-1) == "MAY") {
        string temp;
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "05-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "05-" + cd.substr(0, start));
    }
    else if (cd.substr(start+1, end-start-1) == "JUN") {
        string temp;
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "06-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "06-" + cd.substr(0, start));
    }
    else if (cd.substr(start+1, end-start-1) == "JUL") {
        string temp;
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "07-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "07-" + cd.substr(0, start));
    }
    else if (cd.substr(start+1, end-start-1) == "AUG") {
        string temp;
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "08-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "08-" + cd.substr(0, start));
    }
    else if (cd.substr(start+1, end-start-1) == "SEP") {
        string temp;
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "09-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "09-" + cd.substr(0, start));
    }
    else if (cd.substr(start+1, end-start-1) == "OCT") {
        string temp;
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "10-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "10-" + cd.substr(0, start));
    }
    else if (cd.substr(start+1, end-start-1) == "NOV") {
        string temp;
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "11-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "11-" + cd.substr(0, start));
    }
    else if (cd.substr(start+1, end-start-1) == "DEC") {
        string temp;
        if (start == 1)
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "12-0" + cd.substr(0, start));
        else
            d = temp.append(cd.substr(end+1, cd.size()-end-1) + '-' + "12-" + cd.substr(0, start));
    }
    else {
        d = cd;
    }
    return d;
}

int calAge(string date, string old) {
    if (stoi(old.substr(0, 4)) < stoi(date.substr(20, 4))) {
        if (old.size() == 4)
            return (stoi(date.substr(20, 4)) - stoi(old.substr(0, 4)));
        if (stoi(old.substr(5, 2)) < getCurrentDate(date.substr(4, 3))) {   
            return (stoi(date.substr(20, 4)) - stoi(old.substr(0, 4)));
        }
        else if (stoi(old.substr(5, 2)) == getCurrentDate(date.substr(4, 3))) {
            if (stoi(old.substr(8, 2)) <= stoi(date.substr(8, 2)))
                return (stoi(date.substr(20, 4)) - stoi(old.substr(0, 4)));
            else
                return (stoi(date.substr(20, 4)) - stoi(old.substr(0, 4)) - 1);
        }
        else {
            return (stoi(date.substr(20, 4)) - stoi(old.substr(0, 4)) - 1);
        }
    }
    else {
        return 0;
    }
}

FAM collectFAMData(string *store, int i, FAM i1) {
    i++;
    int c = 0;
    while (store[i][0] != '0') {
        if (store[i].substr(2, 4) == "MARR") {
            string temp = store[i+1].substr(9, store[i+1].size() - 9);
            i1.married = transOldFormat(temp);
        }
        else if (store[i].substr(2, 3) == "DIV") {
            string temp = store[i+1].substr(9, store[i+1].size() - 9);
            i1.divorced = transOldFormat(temp);
        }
        else if (store[i].substr(2, 4) == "HUSB") {
            i1.husband_id = store[i].substr(9, store[i].size() - 9);
        }
        else if (store[i].substr(2, 4) == "WIFE") {
            i1.wife_id = store[i].substr(9, store[i].size() - 9);
        }
        else if (store[i].substr(2, 4) == "CHIL") {
            i1.children[c] = store[i].substr(9, store[i].size() - 9);
            c++;
        }
        i++;
    }
    return i1;
}

INDI collectINDIData(string *store, int i, INDI i1) {
    i++;
    int c = 0;
    int s = 0;
    while (store[i][0] != '0') {
        if (store[i].substr(2, 4) == "NAME") {
            i1.name = store[i].substr(9, store[i].size() - 9);
        }
        else if (store[i].substr(2, 3) == "SEX") {
            i1.gender = store[i].substr(8, 1);
        }
        else if (store[i].substr(2, 4) == "BIRT") {
            string temp = store[i+1].substr(9, store[i+1].size() - 9);
            i1.birth = transOldFormat(temp);
        }
        else if (store[i].substr(2, 4) == "DEAT") {
            string temp = store[i+1].substr(9, store[i+1].size() - 9);
            i1.death = transOldFormat(temp);
            i1.alive = "False";
        }
        else if (store[i].substr(2, 4) == "FAMC") {
            i1.child[c] = store[i].substr(9, store[i].size() - 9);
            c++;
        }
        else if (store[i].substr(2, 4) == "FAMS") {
            i1.spouse[s] = store[i].substr(9, store[i].size() - 9);
            s++;
        }
        i++;
    }
    return i1;
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
