#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
	
	ifstream infile;
	string user = "\\User1";
	string tmp;

	if (argc == 1) {

		infile.open("..\\..\\..\\Results_files\\computerName.txt");

		if (infile.is_open()) {

			if (getline(infile, tmp)) {

				cout << tmp << user << "\n";
			}
			infile.close();
		}
		else cout << "Unable to open file";

	}
	else if (string(argv[1]) == "/?") {

		infile.open("..\\..\\..\\Results_files\\whoami_results_files\\whoami_help.txt");

		if (infile.is_open()) {

			while (getline(infile, tmp)) {

				cout << tmp << "\n";
			}
			infile.close();
		}
		else cout << "Unable to open file";
	}
	
	else if (string(argv[1]) == "/user") {

		int count = 0;
		int startLine;
		
		infile.open("..\\..\\..\\Results_files\\whoami_results_files\\whoami_all.txt");

		if (infile.is_open()) {

			while (getline(infile, tmp)) {
				
				if (string(tmp).find("User Name") != std::string::npos) {
					startLine = count;
					//cout << startLine << " is the starting\n";
				}
				count++;
			}
			
			infile.clear();
			infile.seekg(0, infile.beg);
			
			count = 0;

			cout << "\nUSER INFORMATION\n----------------\n\n";

			while (getline(infile, tmp)) {
				if (count >= startLine) {
					if (tmp.empty()) {
						break;
					}
					cout << tmp << "\n";
				}
				count++;
			}
			infile.close();
		}
		else cout << "Unable to open file";
	}

	else if (string(argv[1]) == "/groups") {

		int count = 0;
		int startLine;
		
		infile.open("..\\..\\..\\Results_files\\whoami_results_files\\whoami_all.txt");

		if (infile.is_open()) {

			while (getline(infile, tmp)) {

				if (string(tmp).find("Group Name") != std::string::npos) {
					startLine = count;
					//cout << userStart << " is the starting\n";
				}
				count++;
			}

			infile.clear();
			infile.seekg(0, infile.beg);

			count = 0;

			cout << "\nGROUP INFORMATION\n-----------------\n\n";

			while (getline(infile, tmp)) {
				if (count >= startLine) {
					if (tmp.empty()) {
						break;
					}
					cout << tmp << "\n";
				}
				count++;
			}
			infile.close();
		}
		else cout << "Unable to open file";
	}

	else if (string(argv[1]) == "/priv") {

		int count = 0;
		int startLine;

		infile.open("..\\..\\..\\Results_files\\whoami_results_files\\whoami_all.txt");

		if (infile.is_open()) {

			while (getline(infile, tmp)) {

				if (string(tmp).find("Privilege Name") != std::string::npos) {
					startLine = count;
					//cout << userStart << " is the starting\n";
				}
				count++;
			}

			infile.clear();
			infile.seekg(0, infile.beg);

			count = 0;

			cout << "\nPRIVILEGES INFORMATION\n----------------------\n\n";

			while (getline(infile, tmp)) {
				if (count >= startLine) {
					if (tmp.empty()) {
						break;
					}
					cout << tmp << "\n";
				}
				count++;
			}
			infile.close();
		}
		else cout << "Unable to open file";
	}

	else if (string(argv[1]) == "/all") {

		infile.open("..\\..\\..\\Results_files\\whoami_results_files\\whoami_all.txt");

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
	cout << "The UTC date and time is:" << dt << endl;

	ofstream outfile;
	outfile.open("..\\..\\..\\Results_files\\logfile.txt", ios::app);

	outfile << dt << "\t" << string(argv[0]) << " " << string(argv[1]) << "\n";
	outfile.close();

	return 0;
}
