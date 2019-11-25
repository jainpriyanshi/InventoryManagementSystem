#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>

#define clear() printf("\033[H\033[J")

#include <stdlib.h>
#include <ios>
#include <limits>

#include <termios.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;
int level = 0, mode = 0, valid_action_available = 1;
#define STUDENT 1
#define CAPTAIN 2
#define f(i, n, m) for (int i = n; i < m; i++)

class Student
{
private:
	string password;

public:
	string name, ldap, rollNo;
	int input(string LDAP, string PASS)
	{
		ifstream fin("students.txt");
		int n;
		fin >> n;
		string s;
		getline(fin, s);
		f(i, 0, n)
		{
			getline(fin, rollNo);
			getline(fin, name);
			getline(fin, ldap);
			getline(fin, password);
			if (ldap == LDAP && password == PASS)
				return 0;
		}
		fin.close();
		return 1;
	}
	int load(string roll)
	{
		ifstream fin("students.txt");
		int n;
		fin >> n;
		string s;
		getline(fin, s);
		f(i, 0, n)
		{
			getline(fin, rollNo);
			getline(fin, name);
			getline(fin, ldap);
			getline(fin, s);
			if (rollNo == roll)
				return 0;
		}
		fin.close();
		return 1;
	}
	void display()
	{
		cout << name << endl
			 << rollNo << endl
			 << ldap << endl;
	}
} stu;
class Captain : public Student
{
	string password;

public:
	bool verifymember();
	void searchItem();
	void issueItem();
	void returnItem();
	void createReceipt();
};

class ClubMember : public Student
{
	string Password;

public:
	vector<string> itemsIssued;
	void updateItemsIssued();
};

class Society
{
private:
	int budgetAlloted;
	int budgetUsed;

public:
	string societyName;
	string secretaryName;
	vector<string> clubs;
	string facultyAdvisor;
	bool approveRequest();
	void input(string name)
	{
		ifstream fin("society_clubs.txt");
		int total;
		fin >> total;
		string s;
		getline(fin, s);
		f(i, 0, total)
		{
			getline(fin, societyName);
			int n;
			fin >> n;
			string s;
			getline(fin, s);
			clubs.resize(n);
			f(j, 0, n) getline(fin, clubs[j]);
			if (societyName == name)
				break;
		}
		fin.close();
	}
	void display()
	{
		cout << societyName << endl;
		f(i, 0, clubs.size()) cout << i + 1 << ". " << clubs[i] << endl;
	}
} s;

class Item
{
public:
	int itemID;
	string name;
	string status;
	Student issuedBy;
	int input(int id)
	{
		ifstream fin("item_details.txt");
		int n;
		fin >> n;
		string s;
		getline(fin, s);
		f(i, 0, n)
		{
			getline(fin, name);
			fin >> itemID;
			getline(fin, status);
			getline(fin, status);
			if (status == "ISSUED")
			{
				string issuedByRoll;
				getline(fin, issuedByRoll);
				issuedBy.load(issuedByRoll);
			}
			if (id == itemID)
				return 0;
		}
		fin.close();
		return 1;
	}
	void display()
	{
		cout << itemID << " " << name << endl;
		if (status == "ISSUED")
		{
			cout << "ISSUED BY:\n";
			issuedBy.display();
			if (stu.rollNo == issuedBy.rollNo)
				cout << "RETURN? [y/n] ";
			else
				valid_action_available = 0;
		}
		else
		{
			cout << "REQUEST ISSUE? [y/n] ";
		}
	}
} it;

class Club
{
public:
	string clubName;
	string captain;
	vector<Item> itemsAvailable;
	vector<string> members;
	void requestToBuyNewItems();
	void input(string name)
	{
		ifstream fin("club_members.txt");
		int total;
		fin >> total;
		string dump;
		getline(fin, dump);
		f(i, 0, total)
		{
			getline(fin, clubName);
			getline(fin, captain);
			int n;
			fin >> n;
			string s;
			getline(fin, s);
			members.resize(n);
			f(j, 0, n) getline(fin, members[j]);
			if (clubName == name)
				break;
		}
		fin.close();
		fin.open("club_items.txt");
		fin >> total;
		getline(fin, dump);
		f(i, 0, total)
		{
			getline(fin, clubName);
			int n;
			fin >> n;
			string s;
			getline(fin, s);
			itemsAvailable.resize(n);
			f(j, 0, n)
			{
				fin >> itemsAvailable[j].itemID;
				getline(fin, itemsAvailable[j].name);
				itemsAvailable[j].input(itemsAvailable[j].itemID);
			}
			if (clubName == name)
				break;
		}
		fin.close();
	}
	void display()
	{
		cout << clubName << endl;
		f(i, 0, itemsAvailable.size())
		{
			cout << itemsAvailable[i].itemID << " " << itemsAvailable[i].name << " " << (itemsAvailable[i].status == "ISSUED" ? ":NOT AVAILABLE" : ":AVAILABLE") << endl;
		}
	}
	void newmember(string roll)
	{
		ifstream fin("club_members.txt");
		ofstream fout("club_membersnew.txt");
		int total;
		fin >> total;
		string dump;
		getline(fin, dump);
		f(i, 0, total)
		{
			string name, cap;
			getline(fin, name);
			getline(fin, cap);
			int n;
			fin >> n;
			string s;
			getline(fin, s);
			vector<string> memb(n);
			f(j, 0, n) getline(fin, memb[j]);
			if (clubName == name)
				memb.push_back(roll);
			break;
			fout << name << endl
				 << cap << n + 1 << endl;
			f(j, 0, n + 1) fout << memb[j] << endl;
		}
		fin.close();
		fout.close();
		rename("club_membersnew.txt", "club_members.txt");
	}
} c;

class Receipt
{
public:
	static int receiptNo;
	string studentRollNo;
	int itemID;
	string dateIssued;
	string dueDate;
	void createReceipt();
	void deleteReceipt();
	void retrieveReceipt();
};

int loadStudent()
{
	string ldap, pass;
	cout << "Enter LDAP:";
	cin >> ldap;
	getline(cin, pass);
	pass = getpass("Enter Password:");
	int exitStatus = stu.input(ldap, pass);
	if (exitStatus)
		return 1;
	return 0;
}

int loadSociety()
{
	ifstream fin("societylist.txt");
	int total;
	fin >> total;
	string dump;
	getline(fin, dump);
	vector<string> societies(total);
	f(i, 0, total) getline(fin, societies[i]);
	f(i, 0, total) cout << i + 1 << ". " << societies[i] << endl;

	int num;
	cout << "Enter Index: (0 for back)\n";
	cin >> num;
	if (num == 0)
	{
		level -= 2;
		return 0;
	}
	if (num < 1 || num > 6)
		return 1;
	s.input(societies[num - 1]);
	fin.close();
	return 0;
}

int loadClub()
{
	int num;
	cout << "Enter Index: (0 for back)\n";
	cin >> num;
	if (num == 0)
	{
		level -= 2;
		return 0;
	}
	if (num < 1 || num > s.clubs.size())
		return 1;
	c.input(s.clubs[num - 1]);
	return 0;
}

int loadItem()
{
	int num;
	cout << "Enter Index: (0 for back)\n";
	cin >> num;
	if (num == 0)
	{
		level -= 2;
		return 0;
	}
	int flag = 0;
	f(i, 0, c.itemsAvailable.size())
		flag |= (num == c.itemsAvailable[i].itemID);
	if (!flag)
		return 1;
	int exitStatus = it.input(num);
	return exitStatus;
}

int loadAction()
{
	if (valid_action_available == 0)
	{
		level -= 2;
		return 0;
	}
	char num;
	cin >> num;
	if (num != 'y')
	{
		level -= 2;
		return 0;
	}
	return 1;
}

void EXIT(int input)
{
	if (level)
		level--;
	else
		exit(0);
}

void display()
{
	int exitStatus;
	switch (level)
	{
	case 0:
		cout << "1. Student\n2. Captain\n3. Exit\n";
		cin >> mode;
		if (!(mode == 1 || mode == 2))
			EXIT(0);
		exitStatus = loadStudent();
		if (exitStatus)
			EXIT(0);
		level++;
		break;
	case 1:
		exitStatus = loadSociety();
		if (exitStatus)
			EXIT(0);
		level++;
		return;
		break;
	case 2:
		s.display();
		exitStatus = loadClub();
		if (exitStatus)
			EXIT(0);
		level++;
		return;
	case 3:
		c.display();
		exitStatus = loadItem();
		if (exitStatus)
			EXIT(0);
		level++;
		return;
	case 4:
		it.display();
		exitStatus = loadAction();
		if (exitStatus)
			EXIT(0);
		level++;
		return;
	default:
		EXIT(0);
	}
}
int main()
{
	while (1)
	{
		clear();
		display();
	}
}