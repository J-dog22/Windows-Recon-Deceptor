#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <time.h>
#include <dirent.h>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
	//
	//	Print out help and command list
	//
	if (argc == 1 || string(argv[1]) == "/?") {
		ifstream infile;
		string tmp;
		
		infile.open("..\\..\\..\\Results_files\\Net_results_files\\help\\net_help.txt");

		if (infile.is_open()) {

			while (getline(infile, tmp))
				cout << tmp << "\n";
			infile.close();
		}
	}

	//
	//	Function for use
	//
	else if (string(argv[1]) == "use") {
		cout << "This is fuction for use" << endl;
	}

	//
	//	Net user
	//
	else if (string(argv[1]) == "user") {
		string path = "..\\..\\..\\Results_files\\Net_results_files\\user";
		
		//
		//	Net user - display user accounts
		//
		if (argc == 2) {
			struct dirent* entry;
			ifstream infile;
			string compName;
			
			DIR* dir = opendir("..\\..\\..\\Results_files\\Net_results_files\\user");
			infile.open("..\\..\\..\\Results_files\\computerName.txt");

			if (infile.is_open()) {

				getline(infile, compName);
				infile.close();
			}

			transform(compName.begin(), compName.end(), compName.begin(), ::toupper);
			cout << "\nUser accounts for \\" << compName << "\n\n-------------------------------------------------------------------------------\n";

			int count = 0;
			int count2 = 1;
			int count3 = 1;
			while ((entry = readdir(dir)) != NULL) {

				if (count >= 2) {
					cout << entry->d_name << "\t\t";
					
					if (count2 == 3) {
						cout << "\n";
						count2 = 0;
					}
					if (count3 == 4) {
						cout << "\t";
					}
					count2++;
					count3++;
				}
				count++;
			}
			closedir(dir);

			cout << "\nThe command completed successfully." << endl;
		}

		//
		//	Print help for net user
		//
		if (string(argv[2]) == "/?") {
			ifstream infile;
			string tmp;

			infile.open("..\\..\\..\\Results_files\\Net_results_files\\help\\net_user_help.txt");

			if (infile.is_open()) {

				while (getline(infile, tmp))
					cout << tmp << "\n";
				infile.close();
			}
		}

		//
		//	Net user <username> - display info about specific user
		//
		if (argc == 3 && string(argv[2]) != "/?") {
			ifstream infile;
			string tmp;
			string user = string(argv[2]);
			string filename = string(argv[2]) + "_info.txt";
			string fullpath = path + "\\" + user + "\\" + filename;

			infile.open(fullpath);

			if (infile.is_open()) {

				while (getline(infile, tmp)) {
					cout << tmp << "\n";
				}
				infile.close();

				cout << "This command completed successfully.\n\n";
			}
			else cout << "The user name could not be found.\n\nMore help is available by typing NET HELPMSG 2221.\n\n";
		}

		//
		//	Net User <username> /delete - deleting user
		//
		if (string(argv[3]) == "/delete") {
			string user = string(argv[2]);
			string dirpath = path + "\\" + user;
			struct dirent* entry;
			DIR* dir = opendir("..\\..\\..\\Results_files\\Net_results_files\\localgroup");

			int count = 0;
			while ((entry = readdir(dir)) != NULL) {

				if (count >= 2) {
		
					string lgpath = "..\\..\\..\\Results_files\\Net_results_files\\localgroup\\" + string(entry->d_name);
					char newLGpath[1024];
					strcpy_s(newLGpath, 1024, lgpath.c_str());
					DIR* dir2 = opendir(newLGpath);

					while ((entry = readdir(dir2)) != NULL) {
						if (user == string(entry->d_name)) {
							string finalLGpath = lgpath + "\\" + string(entry->d_name);
							fs::remove_all(finalLGpath);
						}
					}
					closedir(dir2);
				}
				count++;
			}
			closedir(dir);
			
			DIR* dir3 = opendir("..\\..\\..\\Results_files\\Net_results_files\\group");

			int count2 = 0;
			while ((entry = readdir(dir3)) != NULL) {

				if (count >= 2) {
			
					string gpath = "..\\..\\..\\Results_files\\Net_results_files\\group\\" + string(entry->d_name);
					char newGpath[1024];
					strcpy_s(newGpath, 1024, gpath.c_str());
					DIR* dir4 = opendir(newGpath);

					while ((entry = readdir(dir4)) != NULL) {
						if (user == string(entry->d_name)) {
							string finalLGpath = gpath + "\\" + string(entry->d_name);
							fs::remove_all(finalLGpath);
						}
					}
					closedir(dir4);
				}
				count2++;
			}
			closedir(dir3);

			fs::remove_all(dirpath);

			cout << "The command completed successfully.\n";
		}

		//
		//	Net user <username> /add - adding a user
		//
		if (string(argv[3]) == "/add" || string(argv[4]) == "/add") {
			
			string user = string(argv[2]);
			string password = string(argv[3]);
			string filename = string(argv[2]) + "_info.txt";
			string dirpath = path + "\\" + user;
			string fullpath = path + "\\" + user + "\\" + filename;

			time_t t = time(NULL);
			time_t rawtime;
			struct tm now;
			localtime_s(&now, &rawtime);

			ifstream infile;
			infile.open(fullpath);

			if (infile.is_open())
				cout << "The account already exists.\n\nMore help is available by typing NET HELPMSG 2224.\n\n";
			else {
				fs::create_directory(dirpath);

				ofstream outfile;
				outfile.open(fullpath);
				outfile << "User name                    " << user << "\n";
				outfile << "Full Name\nComment\nUser's comment\n";
				outfile << "Country / region code        000 (System Default)\n";
				outfile << "Account active               Yes\n";
				outfile << "Account expires              Never\n\n";
				outfile << "Password last set            5/6/2021 8:21:32 PM\n";
				outfile << "Password expires             Never\n";
				outfile << "Password changeable          5/6/2021 8:21:32 PM\n";
				outfile << "Password required            Yes\n";
				outfile << "User may change password     Yes\n\n";
				outfile << "Workstations allowed         All\n";
				outfile << "Logon script\nUser profile\nHome directory\n";
				outfile << "Last logon                   Never\n\n";
				outfile << "Logon hours allowed          All\n\n";
				outfile << "Local Group Memberships      *Users\n";
				outfile << "Global Group memberships     *None\n";
				outfile.close();

				string grouppath = "..\\..\\..\\Results_files\\Net_results_files\\localgroup\\Users\\" + user;
				fs::copy(dirpath, grouppath, fs::copy_options::recursive);

				cout << "The command completed successfuy.\n";
			}
		}
	}

	//
	//	Function for localgroup
	//
	else if (string(argv[1]) == "localgroup") {
		
		//
		//	Net localgroup - list local groups
		//
		if (argc == 2) {
			
			ifstream infile;
			string compName;

			infile.open("..\\..\\..\\Results_files\\computerName.txt");

			if (infile.is_open()) {

				getline(infile, compName);
				infile.close();
			}

			else cout << "Unable to open file";
			transform(compName.begin(), compName.end(), compName.begin(), ::toupper);
			cout << "\nAliases for \\" << compName << "\n\n-------------------------------------------------------------------------------\n";
			
			struct dirent* entry;
			DIR* dir = opendir("..\\..\\..\\Results_files\\Net_results_files\\localgroup");

			int count = 0;
			while ((entry = readdir(dir)) != NULL) {

				if (count >= 2)
					cout << "*" << entry->d_name << endl;
				count++;
			}
			closedir(dir);
			cout << "The command completed successfully.\n";
		}

		//
		//	Print help for net localgroup
		//
		if (string(argv[2]) == "/?") {
			ifstream infile;
			string tmp;

			infile.open("..\\..\\..\\Results_files\\Net_results_files\\help\\net_localgroup_help.txt");

			if (infile.is_open()) {

				while (getline(infile, tmp))
					cout << tmp << "\n";
				infile.close();
			}
		}


		//
		//	net localgroup <localgroup name> - list uers in local group
		//
		if (argc == 3 && string(argv[2]) != "/?") {

			string alias = string(argv[2]);
			cout << "Alias name\t" << alias << "\n";
			if (alias == "Administrators")
				cout << "Comment\t\tAdministrators have complete and unrestricted access to the computer/domain\n\n";
			else if (alias == "CFRS780")
				cout << "Comment\t\tMembers have acces to course materials\n\n";
			else if (alias == "Guests")
				cout << "Comment\t\tGuests have the same access as members of the Users group by default, except for the Guest account which is further restricted\n\n";
			else if (alias == "Users")
				cout << "Comment\t\tUsers are prevented from making accidental or intentional system - wide changes and can run most applications\n\n";
			else
				cout << "Comment\n\n";
		
			cout << "Members\n\n---------------------------------------------------------------------------------\n";

			struct dirent* entry;
			string lgpath = "..\\..\\..\\Results_files\\Net_results_files\\localgroup\\" + string(alias);
			char newLGpath[1024];
			strcpy_s(newLGpath, 1024, lgpath.c_str());
			DIR* dir = opendir(newLGpath);

			int count = 0;
			while ((entry = readdir(dir)) != NULL) {

				if (count >= 2) {
					cout << entry->d_name << endl;
				}
				count++;
			}
			closedir(dir);
			cout << "The commmand completed successfully.\n";
		}

		//
		//	net localgroup <localgroup name> /add - adding a new local group
		//
		if (string(argv[3]) == "/add") {
			string localGroupName = string(argv[2]);
			string lgpath = "..\\..\\..\\Results_files\\Net_results_files\\localgroup\\";
			string dirpath = lgpath + localGroupName;

			fs::create_directory(dirpath);

			cout << "The command completed successfully.\n";
		}

		if (string(argv[3]) == "/delete") {
			
			string localGroupName = string(argv[2]);
			string lgpath = "..\\..\\..\\Results_files\\Net_results_files\\localgroup\\";
			string dirpath = lgpath + localGroupName;

			fs::remove_all(dirpath);

			cout << "The command completed successfully.\n";
		}

		//
		//	adding existing user to local group
		//
		if (string(argv[4]) == "/add") {
			string localGroupName = string(argv[2]);
			string user = string(argv[3]);
			string localGroupPath = "..\\..\\..\\Results_files\\Net_results_files\\localgroup\\" + localGroupName + "\\" + user;
			string userPath = "..\\..\\..\\Results_files\\Net_results_files\\user\\" + user;
			string usercheck = "..\\..\\..\\Results_files\\Net_results_files\\user\\" + user + "\\" + user + "_info.txt";
			ifstream infile;

			infile.open(usercheck);

			if (infile.is_open()) {

				fs::copy(userPath, localGroupPath, fs::copy_options::recursive);
				cout << "The command completed successfully.\n";
				infile.close();
			}
			else cout << "There is no such global user or group: " << user << "\n\nMore help is available by typing NET HELPMSG 3783.\n";
		}

		//
		//	deleting user from local group
		//
		if (string(argv[4]) == "/delete") {
			string localGroupName = string(argv[2]);
			string user = string(argv[3]);
			string localGroupPath = "..\\..\\..\\Results_files\\Net_results_files\\localgroup\\" + localGroupName + "\\" + user;
			string usercheck = localGroupPath + "\\" + user + "_info.txt";
			int check = 0;
			ifstream infile;

			infile.open(usercheck);

			if (infile.is_open()) {
				check = 1;
				infile.close();
			}
			
			if (check == 1) {
				fs::remove_all(localGroupPath);
				cout << "The command completed successfully.\n";
			}
			else 
				cout << "There is no such global user or group: " << user << "\n\nMore help is available by typing NET HELPMSG 3783.\n";	
		}
	}

	//
	//	Function for group
	//
	else if (string(argv[1]) == "group") {

		//
		//	list all global groups
		//
		if (argc == 2) {

			ifstream infile;
			string compName;

			infile.open("..\\..\\..\\Results_files\\computerName.txt");

			if (infile.is_open()) {

				getline(infile, compName);
				infile.close();
			}
			else cout << "Unable to open file";
			transform(compName.begin(), compName.end(), compName.begin(), ::toupper);
			cout << "\nAliases for \\" << compName << "\n\n-------------------------------------------------------------------------------\n";

			struct dirent* entry;
			DIR* dir = opendir("..\\..\\..\\Results_files\\Net_results_files\\group");

			int count = 0;
			while ((entry = readdir(dir)) != NULL) {

				if (count >= 2)
					cout << "*" << entry->d_name << endl;
				count++;
			}
			closedir(dir);
			cout << "The command completed succesfully.\n";
		}

		//
		//	Print help for net group
		//
		if (string(argv[2]) == "/?") {
			ifstream infile;
			string tmp;

			infile.open("..\\..\\..\\Results_files\\Net_results_files\\help\\net_group_help.txt");

			if (infile.is_open()) {

				while (getline(infile, tmp))
					cout << tmp << "\n";
				infile.close();
			}
		}
		
		//
		//	listing members in group
		//
		if (argc == 3 && string(argv[2]) != "/?") {

			string alias = string(argv[2]);
			cout << "Alias name\t" << alias << "\n";
			cout << "Comment\n\n";
			cout << "Members\n\n---------------------------------------------------------------------------------\n";

			struct dirent* entry;
			string gpath = "..\\..\\..\\Results_files\\Net_results_files\\group\\" + string(alias);
			char newGpath[1024];
			strcpy_s(newGpath, 1024, gpath.c_str());
			DIR* dir = opendir(newGpath);

			int count = 0;
			while ((entry = readdir(dir)) != NULL) {

				if (count >= 2) {
					cout << entry->d_name << endl;
				}
				count++;
			}
			closedir(dir);
			cout << "The command completed sucessfully.\n";
		}

		//
		//	adding group
		//
		if (string(argv[3]) == "/add") {
			string groupName = string(argv[2]);
			string gpath = "..\\..\\..\\Results_files\\Net_results_files\\group\\";
			string dirpath = gpath + groupName;

			fs::create_directory(dirpath);

			cout << "The command completed successfully.\n";
		}

		//
		//	deleting group
		//
		if (string(argv[3]) == "/delete") {

			string groupName = string(argv[2]);
			string gpath = "..\\..\\..\\Results_files\\Net_results_files\\group\\";
			string dirpath = gpath + groupName;

			fs::remove_all(dirpath);

			cout << "The command completed successfully.\n";
		}

		//
		//	adding existing user to group
		//
		if (string(argv[4]) == "/add") {
			string groupName = string(argv[2]);
			string user = string(argv[3]);
			string groupPath = "..\\..\\..\\Results_files\\Net_results_files\\group\\" + groupName + "\\" + user;
			string userPath = "..\\..\\..\\Results_files\\Net_results_files\\user\\" + user;
			string usercheck = "..\\..\\..\\Results_files\\Net_results_files\\user\\" + user + "\\" + user + "_info.txt";
			ifstream infile;

			infile.open(usercheck);

			if (infile.is_open()) {

				fs::copy(userPath, groupPath, fs::copy_options::recursive);
				cout << "The command completed successfully.\n";
				infile.close();
			}
			else cout << "There is no such global user or group: " << user << "\n\nMore help is available by typing NET HELPMSG 3783.\n";
		}

		//
		//	deleting user from group
		//
		if (string(argv[4]) == "/delete") {
			string groupName = string(argv[2]);
			string user = string(argv[3]);
			string groupPath = "..\\..\\..\\Results_files\\Net_results_files\\group\\" + groupName + "\\" + user;
			string usercheck = groupPath + "\\" + user + "_info.txt";
			int check = 0;
			ifstream infile;

			infile.open(usercheck);

			if (infile.is_open()) {
				check = 1;
				infile.close();
			}

			if (check == 1) {
				fs::remove_all(groupPath);
				cout << "The command completed successfully.\n";
			}
			else
				cout << "There is no such global user or group: " << user << "\n\nMore help is available by typing NET HELPMSG 3783.\n";
		}
	}

	//
	//	Function for share
	//
	else if (string(argv[1]) == "share") {

		//
		//	list network shares
		//
		if (argc == 2) {
			struct dirent* entry;
			DIR* dir = opendir("..\\..\\..\\Results_files\\Net_results_files\\share");

			cout << "Share name\tResource                        Remark\n\n-------------------------------------------------------------------------------\n";

			int count = 0;
			while ((entry = readdir(dir)) != NULL) {

				if (count >= 2) {
					cout << entry->d_name << "\t\t";
					string share = string(entry->d_name);
					string path = "..\\..\\..\\Results_files\\Net_results_files\\share\\" + share + "\\" + share + "_share.txt";

					ifstream infile;
					string tmp;
					int linenum = 1;

					infile.open(path);

					if (infile.is_open()) {

						while (getline(infile, tmp)) {
							if (linenum >= 13 && linenum <= 14) {
								cout << tmp << "\t\t\t";
							}
							linenum++;
						}
						infile.close();
						cout << "\n";
					}
					else cout << "Unable to open file";
				}
				count++;
			}
			closedir(dir);
			cout << "The command completed successfully.\n";
		}

		//
		//	Print help for net share
		//
		if (string(argv[2]) == "/?") {
			ifstream infile;
			string tmp;

			infile.open("..\\..\\..\\Results_files\\Net_results_files\\help\\net_share_help.txt");

			if (infile.is_open()) {

				while (getline(infile, tmp))
					cout << tmp << "\n";
				infile.close();
			}
		}

		//
		//	list info about netowrk share
		//
		if (argc == 3 && string(argv[2]) != "/?") {
			string share = string(argv[2]);

			string path = "..\\..\\..\\Results_files\\Net_results_files\\share\\" + share + "\\" + share + "_share.txt";

			ifstream infile;
			string tmp;
			string buf[7];
			int linenum = 0;
			int i = 0;
			infile.open(path);

			if (infile.is_open()) {

				while (getline(infile, tmp)) {
					if (linenum >= 11 && linenum <= 17) {
						buf[i] = tmp;
						i++;
					}
					linenum++;
				}
				infile.close();
			}
			cout << "Share name\t" << buf[0] << "\n";
			cout << "Path\t\t" << buf[1] << "\n";
			cout << "Remark\t\t" << buf[2] << "\n";
			cout << "Maximum users\t" << buf[3] << "\n";
			cout << "Users\t\t" << buf[4] << "\n";
			cout << "Caching\t\t" << buf[5] << "\n";
			cout << "Permission\t" << buf[6] << "\n\n";
			cout << "The command completed successfully.\n\n\n";
		}

		//
		//	deleting shared resource
		//
		if (string(argv[3]) == "/delete") {
			string share = string(argv[2]);
			string path = "..\\..\\..\\Results_files\\Net_results_files\\share\\" + share + "\\" + share + "_share.txt";
			string dirpath = "..\\..\\..\\Results_files\\Net_results_files\\share\\" + share;
			int check = 0;
			ifstream infile;
			infile.open(path);

			if (infile.is_open()) {
				check = 1;
				infile.close();
			}

			if (check == 1) {
				fs::remove_all(dirpath);
				cout << "The command completed successfully.\n";
			}
			else {
				cout << "Share does not exist\n"; //tempory error handling
			}
		}

		//
		//	adding a netowrk share
		//
		if (argc == 4 && string(argv[3]) != "/delete") {
			string share = string(argv[2]);
			string resource = string(argv[3]);
			string dirpath = "..\\..\\..\\Results_files\\Net_results_files\\share\\" + share;
			string filepath = "..\\..\\..\\Results_files\\Net_results_files\\share\\" + share + "\\" + share + "_share.txt";

			ifstream infile;
			infile.open(filepath);
			if (infile.is_open())
				cout << "Network resource already exist.\n";
			else {

				fs::create_directory(dirpath);
				ofstream outfile;
				outfile.open(filepath);
				outfile << "Share name\t" << share << "\n";
				outfile << "Path\t\t" << resource << "\n";
				outfile << "Remark\t\t" << "\n";
				outfile << "Maximum users\tNo limit\n";
				outfile << "Users\t\t\n";
				outfile << "Caching\t\tManual caching of documents\n";
				outfile << "Permission\tEveryone, FULL\n\n";
				outfile.close();

				cout << "The command completed successfully.\n";
			}
		}
	}

	//
	// displau help is anything else is inputed
	//
	else {
		ifstream infile;
		string tmp;

		infile.open("..\\..\\..\\Results_files\\Net_results_files\\help\\net_help.txt");

		if (infile.is_open()) {

			while (getline(infile, tmp))
				cout << tmp << "\n";
			infile.close();
		}
	}
	
	//logging here
	
	time_t result = time(NULL);
	char dt[26];
	ctime_s(dt, sizeof dt, &result);
	cout << "The UTC date and time is:" << dt << endl;

	ofstream outfile;
	outfile.open("..\\..\\..\\Results_files\\logfile.txt", ios::app);

	outfile << dt << "\t" << string(argv[0]) << " " << string(argv[1]) << " " << string(argv[2]) << " " << string(argv[3]) << " " << string(argv[4]) << endl;
	outfile.close();

	return 0;
}