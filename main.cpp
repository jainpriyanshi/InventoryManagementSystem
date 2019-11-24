#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include<ios>      
#include<limits>

using namespace std;
int level = 0, mode = 0;
#define STUDENT 1
#define CAPTAIN 2

#define f(i, n, m) for (int i = n; i < m; i++)

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
		ifstream fin("clublist.txt");
		f(i, 0, 6)
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
		f(i, 0, clubs.size()) cout << clubs[i] << endl;
	}
} s;

class Student
{
private:
	string password;

public:
	string name, ldap, rollNo;
	friend void registerStudent();
	friend void loginStudent();
	friend void Logout();
};
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
class Item
{
public:
	int itemId;
	string Name;
	bool status;
	void updateStatus();
	void displayDetails();
};
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
		ifstream fin("clubmembers.txt");
		f(i, 0, 36)
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
		ifstream fin1("itemslist.txt");
		f(i, 0, 36)
		{
			
			getline(fin1, clubName);
			//cout<<clubName<<"\n";
			int n;
			fin1 >> n;
			string s;
			getline(fin, s);
			//cout<<n<<"\n";
			itemsAvailable.resize(n);
			f(j,0,n)
			{
				
				int id;
				fin1>>id;
				itemsAvailable[j].itemId=id;
				string tmpname;
				fin1>>tmpname;
				itemsAvailable[j].Name=name;
				int status;
				fin1>>status;
				itemsAvailable[j].status=status;
			}
			if (clubName == name)
				break;
		}
		fin1.close();
		
	}
	void display()
	{
		cout << clubName << endl;
		f(i, 0, members.size()) cout << members[i] << endl;
		f(i, 0, itemsAvailable.size()) 
		cout << itemsAvailable[i].itemId <<" "<<itemsAvailable[i].Name<<" "<<itemsAvailable[i].status<< endl;
	}
	void newmember(string roll)
	{
		ifstream fin("clubmembers.txt");
		ofstream fout("clubmembersnew.txt");
		f(i, 0, 36)
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
		rename("clubmembersnew.txt", "clubmembers.txt");
	}
} c;


class Receipt
{
public:
	static int receiptNo;
	string studentRollNo;
	int itemId;
	string dateIssued;
	string dueDate;
	void createReceipt();
	void deleteReceipt();
	void retrieveReceipt();
};

int loadSociety()
{
	ifstream fin("societylist.txt");
	vector<string> societies(6);
	f(i, 0, 6) getline(fin, societies[i]);
	f(i, 0, 6) cout << i + 1 << "." << societies[i] << endl;
	int num;
	cin >> num;
	if (num < 1 || num > 6)
		return 1;
	s.input(societies[num - 1]);
	fin.close();
	return 0;
}

int loadClub()
{
	int num;
	cin >> num;
	if (num < 1 || num > s.clubs.size())
		return 1;
	c.input(s.clubs[num - 1]);
	return 0;
}

void display()
{
	int exitStatus;
	switch (level)
	{
	case 0:
		cout << "1. Student\n2. Captain\n3: Exit\n";
		cin >> mode;
		if (mode == 1 || mode == 2)
		{
			level++;
			return;
		}
		if (mode == 3)
			exit(0);
		break;
	case 1:
		if (mode == STUDENT)
		{
			exitStatus = loadSociety();
			if (exitStatus)
				exit(0);
			level++;
			return;
		}
		else
		{
			exit(0);
		}
		break;
	case 2:
		s.display();
		exitStatus = loadClub();
		if (exitStatus)
			exit(0);
		level++;
		return;
	case 3:
		c.display();
	default:
		exit(0);
	}
}
int main()
{
	while (1)
	{
		display();
	}
}