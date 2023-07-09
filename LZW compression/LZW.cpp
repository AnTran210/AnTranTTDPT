#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct dictionary {
	string s;
	short index;
};

void encode() {
	string str; //String for compressing
	vector<short> output; //array store output codes
	vector<dictionary> dict; //Dictionary init
	cout << "Input string: ";
	cin.ignore();
	getline(cin, str);
	short code = 256;
	short prefix;
	string cur = "";
	for (int i = 0; i < str.size(); i++) {
		cur += str.substr(i, 1);
		if (cur.size() == 1) {
			prefix = short(cur[0]);
			continue;
		}
		else {
			short flag = -1;
			for (int j = 0; j < dict.size(); j++) { //dictionary search
				if (cur == dict[j].s) {
					flag = dict[j].index;
					break;
				}
			}
			if (flag != -1) { //found in dictionary
				prefix = flag;
				if (i == str.size() - 1) {
					output.push_back(prefix);
				}
				continue;
			} 
			else {
				dictionary temp;
				temp.s = cur;
				temp.index = code++;
				dict.push_back(temp);
				output.push_back(prefix);
				cur = cur.substr(cur.size() - 1, 1);
				prefix = short(cur[0]);
				if (i == str.size() - 1) {
					output.push_back(prefix);
				}
			}
		}
	}
	cout << "Output: ";
	for (int i = 0; i < output.size(); i++) {
		cout << output[i] << ' ';
	}
	cout << endl;
}

void decode() {
	vector<short> input;
	string output = "";
	string preout = "";
	vector<dictionary> dict;
	short code = 0;
	cout << "Input codes, end the code by -1: ";
	while (code != -1) {
		cin >> code;
		input.push_back(code);
	}
	code = 256;
	output.push_back(char(input[0]));
	preout.push_back(char(input[0]));
	for (int i = 1; i < input.size(); i++) {
		if (input[i] < 256) {
			output.push_back(char(input[i]));
			dictionary temp;
			temp.s = preout; temp.s.push_back(char(input[i]));
			temp.index = code++;
			dict.push_back(temp);
			preout.clear(); preout.push_back(char(input[i]));
		}
		else {
			short flag = -1;
			for (int j = 0; j < dict.size(); j++) {
				if (input[i] == dict[j].index) {
					flag = j;
					break;
				}
			}
			if (flag != -1) {
				dictionary temp;
				temp.s = preout; temp.s.push_back(dict[flag].s[0]);
				temp.index = code++;
				dict.push_back(temp);
				preout = dict[flag].s;
				output += preout;
			}
			else {
				dictionary temp;
				temp.s = preout; temp.s.push_back(preout[0]);
				temp.index = code++;
				dict.push_back(temp);
				preout = temp.s;
				output += preout;
			}
		}
	}
	cout << "Output: " << output << endl;
}

int main() {
	int choice;
	while (1) {
		cout << "Press 1 to encode, 2 to decode, 0 to end program: ";
		cin >> choice;
		if (choice == 1) {
			encode();
		}
		else if (choice == 2) {
			decode();
		}
		else if (choice == 0) return 0;
	}
}