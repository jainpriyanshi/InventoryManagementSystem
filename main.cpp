#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <unistd.h>

#define clear() printf("\033[H\033[J")
#define STUDENT 1
#define CAPTAIN 2
#define f(i, n, m) for (int i = n; i < m; i++)
using namespace std;

int level = 0, mode = 0;
template <typename T>
bool find(vector<T> v, T elem)
{
	bool flag = 0;
	for (auto e : v)
		flag |= elem == e;
	return flag;
}

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
		cout << endl;
	}
	void requestItem(int item)
	{
		ofstream fout("request_transactions.txt", ios::app);
		fout << rollNo << " REQUEST_ITEM " << item << endl;
		fout.close();
	}
	void requestItemReturn(int item)
	{
		ofstream fout("request_transactions.txt", ios::app);
		fout << rollNo << " REQUEST_ITEM_RETURN " << item << endl;
		fout.close();
	}
	void requestMembership(string club)
	{
		ofstream fout("request_transactions.txt", ios::app);
		fout << rollNo << " REQUEST_MEMBERSHIP " << club << endl;
		fout.close();
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
		cout << endl;
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
		}
		else
		{
			cout << status << endl;
		}
		cout << endl;
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
		cout << endl;
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

ifstream transaction_fin;

class transaction
{
public:
	string studentRollNo;
	Student student;
	string request;
	int itemID;
	Item item;
	string clubName;
	int load()
	{
		itemID = 0;
		if (transaction_fin >> studentRollNo)
			;
		else
			return 1;
		student.load(studentRollNo);
		transaction_fin >> request;
		if (request == "REQUEST_ITEM_RETURN" || request == "REQUEST_ITEM")
		{
			transaction_fin >> itemID;
			item.input(itemID);
		}
		else
		{
			getline(transaction_fin, clubName);
			clubName = clubName.substr(1);
		}
		return 0;
	}
	void display()
	{
		cout << request << endl
			 << endl;
		student.display();
		if (request == "REQUEST_ITEM_RETURN" || request == "REQUEST_ITEM")
		{
			item.display();
		}
		cout << endl
			 << signature() << endl
			 << endl;
	}

	string signature()
	{
		if (itemID)
			return studentRollNo + " " + request + " " + to_string(itemID);
		else
			return studentRollNo + " " + request + " " + clubName;
	}

	bool relative()
	{
		bool flag = 0;
		if (itemID)
			for (auto item : c.itemsAvailable)
				flag |= item.itemID == itemID;
		else
			flag = c.clubName == clubName;
		return flag;
	}
};

void write(vector<string> confirm, vector<string> skipped)
{
	ofstream fout("request_transactions.txt");
	for (auto sig : skipped)
		fout << sig << endl;
	fout.close();
	fout.open("confirm_transactions.txt", ios::app);
	for (auto sig : confirm)
		fout << sig << endl;
	fout.close();
}

void transactions()
{
	string response;
	transaction_fin.open("request_transactions.txt");
	vector<string> confirm_ts, skipped_ts;
	transaction t;
	int exitStatus;
label:
	exitStatus = t.load();
	if (exitStatus)
	{
		transaction_fin.close();
		write(confirm_ts, skipped_ts);
		return;
	}
	if (!t.relative())
	{
		skipped_ts.push_back(t.signature());
		goto label;
	}
	clear();
	t.display();
	cout << "1. ACCEPT\n2. DECLINE\n3. NEXT REQUEST\n";
	cout << "ENTER INDEX (0 FOR EXIT)\n";
	cin >> response;
	switch (response[0])
	{
	case '0':
		break;
	case '1':
		confirm_ts.push_back(t.signature());
		goto label;
	case '2':
		goto label;
	case '3':
		skipped_ts.push_back(t.signature());
		goto label;
	default:
		break;
	}
	while (!exitStatus)
	{
		skipped_ts.push_back(t.signature());
		exitStatus = t.load();
	}
	transaction_fin.close();
	write(confirm_ts, skipped_ts);
	return;
}

int loadStudent()
{
	stu.input("tawatia.1", "pass");
	return 0;
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

	cout << "Student Gymkhana\n\n";
	f(i, 0, total) cout << i + 1 << ". " << societies[i] << endl;
	cout << endl;

	int num;
	cout << "Enter Index: (0 for back)\n";
	cin >> num;
	fflush(stdin);
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
	fflush(stdin);
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
	fflush(stdin);
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
	string response;
	if (it.status == "ISSUED")
	{
		if (stu.rollNo == it.issuedBy.rollNo)
		{
			cout << "RETURN? [y/n] ";
			cin >> response;
			if (response == "n" || response == "y")
				level--;
			if (response == "y")
				stu.requestItemReturn(it.itemID);
			return 0;
		}
		else
		{
			cout << "ENTER 0 TO GO BACK\n";
			cin >> response;
			level--;
			return 0;
		}
	}
	else if (find(c.members, stu.rollNo))
	{
		cout << "REQUEST ISSUE? [y/n] ";
		cin >> response;
		if (response == "n" || response == "y")
			level--;
		if (response == "y")
			stu.requestItem(it.itemID);
		return 0;
	}
	else
	{
		cout << "YOU ARE NOT A MEMBER OF THIS CLUB YET\n";
		cout << "REQUEST MEMBERSHIP? [y/n] ";
		cin >> response;
		if (response == "n" || response == "y")
			level--;
		if (response == "y")
			stu.requestMembership(c.clubName);
		return 0;
	}
}

int loadCaptainActions()
{
	int option;
	string response;

	if (c.captain != stu.rollNo)
	{
		cout << "You are not the captain of " << c.clubName << endl;
		cout << "ENTER 0 TO GO BACK\n";
		cin >> response;
		return 1;
	}
	cout << "1. SHOW TRANSACTION REQUESTS\n2. SHOW MEMBERS\n3. SHOW ITEMS\n";
	cout << "ENTER INDEX (0 for back):\n";

	cin >> option;
	fflush(stdin);
	switch (option)
	{
	case 0:
		return 1;
	case 1:
		transactions();
		return 0;
	case 2:
		clear();
		for (auto member : c.members)
		{
			Student s;
			s.load(member);
			s.display();
		}
		cout << "ENTER 0 TO GO BACK\n";
		cin >> response;
		return 0;
	case 3:
		clear();
		for (auto item : c.itemsAvailable)
		{
			item.display();
		}
		cout << "ENTER 0 TO GO BACK\n";
		cin >> response;
		return 0;
	default:
		return 0;
	}
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
		cout << "1. Student\n2. Captain\n3. Exit\n\n";
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
		if (mode == STUDENT)
		{
			c.display();
			exitStatus = loadItem();
			if (exitStatus)
				EXIT(0);
			level++;
		}
		else
		{
			exitStatus = loadCaptainActions();
			if (exitStatus)
				EXIT(0);
		}
		return;
	case 4:
		it.display();
		exitStatus = loadAction();
		if (exitStatus)
			EXIT(0);
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