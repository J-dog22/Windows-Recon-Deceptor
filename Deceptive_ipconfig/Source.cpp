#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {

	ifstream infile;
	string compName;
	string tmp;
	char ch;

	//
	//	Get the computer/host name
	//
	infile.open("..\\..\\..\\Results_files\\computerName.txt");

	if (infile.is_open()) {

		getline(infile, compName);

		infile.close();
	}
	else cout << "Unable to open file";

	//
	//	Get brief Ipconif info
	//
	if (argc == 1) {

		fstream fin("..\\..\\..\\Results_files\\ipconfig_results_files\\ipconfig_all.txt", fstream::in);
		while (fin >> noskipws >> ch) {
			if (ch == '!') {
				fin.ignore(3487, '?');
			}
			else if (ch == '<') {
				fin.ignore(1024, '>');
			}
			else if (ch == '(') {
				fin.ignore(20, ')');
			}
			else cout << ch;
		}
	}

	//
	//   Get ALL ipconfig info
	//
	else if (string(argv[1]) == "/all") {

		fstream fin("..\\..\\..\\Results_files\\ipconfig_results_files\\ipconfig_all.txt", fstream::in);
		while (fin >> noskipws >> ch) {
			if (ch == '!') {
				fin.ignore(3487, '?');
			}
			else if (ch == '<') {
				fin.ignore(0);
			}
			else if (ch == '>') {
				fin.ignore(0);
			}
			else cout << ch;
		}
	}

	//
	//   Get help info
	//
	else if (string(argv[1]) == "/?") {
		infile.open("..\\..\\..\\Results_files\\ipconfig_results_files\\ipconfig_help.txt");

		if (infile.is_open()) {

			while (getline(infile, tmp)) {

				cout << tmp << "\n";
			}
			infile.close();
		}
		else cout << "Unable to open file";
	}
	else {
		infile.open("..\\..\\..\\Results_files\\ipconfig_results_files\\ipconfig_help.txt");

		if (infile.is_open()) {

			while (getline(infile, tmp)) {

				cout << tmp << "\n";
			}
			infile.close();
		}
		else cout << "Unable to open file";
	}

	//
	//	logging
	//
	time_t result = time(NULL);
	char dt[26];
	ctime_s(dt, sizeof dt, &result);
	//cout << "The UTC date and time is:" << dt << endl;

	ofstream outfile;
	outfile.open("..\\..\\..\\Results_files\\logfile.txt", ios::app);

	outfile << string(dt) << "\t" << string(argv[0]) << " " << string(argv[1]) << "\n";
	outfile.close();

	return 0;
}