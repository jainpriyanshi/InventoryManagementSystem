#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <iomanip>
#include <time.h>
using namespace std;
// #define clear() cout << "\033[2J\033[15;1H";
#define clear() printf("\033[H\033[J")
#define STUDENT 1
#define CAPTAIN 2
#define f(i, n, m) for (int i = n; i < m; i++)

int level = 0, mode = 0;
struct winsize w;

const std::string currentDateTime()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}

void align_middle(string s, int leftSpacing = 0)
{
	int n = s.size();
	cout << setw((w.ws_col + n) / 2 - leftSpacing) << right << s;
}

void padding(int n = 1)
{
	f(i, 0, n) cout << " ";
}

void spacing(int n = 1)
{
	for (int i = 0; i < n; i++)
		cout << endl;
}

void design(int n = w.ws_col / 2)
{
	string s;
	f(i, 0, n) s.push_back('*');
	spacing(2);
	align_middle(s);
	spacing(2);
	return;
}

void header()
{
	design();
	align_middle("Welcome To Inventory Management System Of IIT Jodhpur");
	design();
	// sleep(1);
}

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
		align_middle(name);
		cout << endl;
		align_middle(rollNo);
		cout << endl;
		align_middle(ldap);
		cout << endl;
	}
	void requestMembership(string club)
	{
		ofstream fout("request_transactions.txt", ios::app);
		fout << rollNo << " REQUEST_MEMBERSHIP " << currentDateTime() << " " << club << endl;
		fout.close();
	}
} stu;

class Society
{
public:
	string societyName;
	vector<string> clubs;
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
		align_middle(societyName + "\n\n");
		f(i, 0, clubs.size())
			align_middle(to_string(i + 1) + ". " + clubs[i] + "\n");
		cout << endl;
	}
} s;

class Item
{
public:
	int itemID;
	string name;
	string status;
	string issuedOn;
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
				getline(fin, issuedOn);
			}
			if (id == itemID)
				return 1;
		}
		fin.close();
		return 0;
	}
	void display()
	{
		align_middle(to_string(itemID) + " " + name);
		cout << endl;
		if (status == "ISSUED")
		{

			align_middle("ISSUED BY:\n");
			issuedBy.display();
			align_middle("ISSUED ON: " + issuedOn);
			cout << endl;
		}
		else
		{
			align_middle(status);
			cout << endl;
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
		align_middle(clubName);
		spacing(2);
		f(i, 0, itemsAvailable.size())
		{
			cout << setw(w.ws_col / 3) << right << to_string(itemsAvailable[i].itemID) + " "
				 << setw(w.ws_col / 3) << left << itemsAvailable[i].name
				 << setw(w.ws_col / 3) << left << (itemsAvailable[i].status == "ISSUED" ? ":NOT AVAILABLE" : ":AVAILABLE") << endl;
		}
		cout << endl;
	}
} c;

ifstream transaction_fin;

class transaction
{
public:
	string studentRollNo;
	Student student;
	string request;
	string time;
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
		transaction_fin >> request >> time;
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
		align_middle(request);
		cout << endl;
		align_middle(time);
		cout << endl;
		student.display();
		cout << endl;
		if (request == "REQUEST_ITEM_RETURN" || request == "REQUEST_ITEM")
		{
			item.display();
		}
		align_middle(signature());
		cout << endl;
	}

	string signature()
	{
		if (itemID)
			return studentRollNo + " " + request + " " + time + " " + to_string(itemID);
		else
			return studentRollNo + " " + request + " " + time + " " + clubName;
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

	bool valid()
	{
		if (itemID)
		{
			if (request == "REQUEST_ITEM")
				return (item.status == "NOT_ISSUED");
			else
				return (item.status == "ISSUED" && item.issuedBy.rollNo == studentRollNo);
		}
		else
			return !find(c.members, studentRollNo);
	}
};

class Captain : public Student, public Club
{
private:
	void sign(transaction t)
	{
		if (t.itemID)
		{
			if (t.request == "REQUEST_ITEM")
			{
				ifstream fin("item_details.txt");
				ofstream fout("item_details_new.txt");
				int n;
				fin >> n;
				fout << n << endl;
				string s;
				getline(fin, s);
				Item item;
				f(i, 0, n)
				{
					getline(fin, item.name);
					fout << item.name << endl;
					fin >> item.itemID;
					fout << item.itemID << endl;
					getline(fin, item.status);
					getline(fin, item.status);
					if (t.itemID == item.itemID)
					{
						fout << "ISSUED" << endl
							 << t.studentRollNo << endl
							 << currentDateTime() << endl;
					}
					else
					{
						fout << item.status << endl;
						if (item.status == "ISSUED")
						{
							string issuedByRoll;
							getline(fin, issuedByRoll);
							fout << issuedByRoll << endl;
							item.issuedBy.load(issuedByRoll);
							getline(fin, item.issuedOn);
							fout << item.issuedOn << endl;
						}
					}
				}
				fin.close();
				fout.close();
				rename("item_details_new.txt", "item_details.txt");
			}
			else
			{
				ifstream fin("item_details.txt");
				ofstream fout("item_details_new.txt");
				int n;
				fin >> n;
				fout << n << endl;
				string s;
				getline(fin, s);
				Item item;
				f(i, 0, n)
				{
					getline(fin, item.name);
					fout << item.name << endl;
					fin >> item.itemID;
					fout << item.itemID << endl;
					getline(fin, item.status);
					getline(fin, item.status);
					string issuedByRoll;
					if (item.status == "ISSUED")
					{
						getline(fin, issuedByRoll);
						getline(fin, item.issuedOn);
					}
					if (t.itemID == item.itemID)
					{
						fout << "NOT_ISSUED" << endl;
					}
					else
					{
						fout << item.status << endl;
						if (item.status == "ISSUED")
						{
							fout << issuedByRoll << endl;
							fout << item.issuedOn << endl;
						}
					}
				}
				fin.close();
				fout.close();
				rename("item_details_new.txt", "item_details.txt");
			}
		}
		else
		{
			ifstream fin("club_members.txt");
			ofstream fout("club_members_new.txt");
			int total;
			fin >> total;
			fout << total << endl;
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
				if (t.clubName == name)
					memb.push_back(t.studentRollNo);
				fout << name << endl
					 << cap << endl
					 << memb.size() << endl;
				f(j, 0, memb.size()) fout << memb[j] << endl;
			}
			fin.close();
			fout.close();
			rename("club_members_new.txt", "club_members.txt");
		}
	}
	friend void transactions();
} cap;

class ClubMember : public Student, public Club
{
public:
	void input(string rollNo, string clubName)
	{
		Student::load(rollNo);
		Club::input(clubName);
	}
	void requestItem(int item)
	{
		ofstream fout("request_transactions.txt", ios::app);
		fout << rollNo << " REQUEST_ITEM " << currentDateTime() << " " << item << endl;
		fout.close();
	}
	void requestItemReturn(int item)
	{
		ofstream fout("request_transactions.txt", ios::app);
		fout << rollNo << " REQUEST_ITEM_RETURN " << currentDateTime() << " " << item << endl;
		fout.close();
	}
} clubMember;

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
		clear();
		header();
		align_middle("NO NEW REQUESTS");
		cout << endl;
		align_middle("ENTER 0 TO GO BACK: ");
		cin >> response;
		return;
	}
	if (!t.relative())
	{
		skipped_ts.push_back(t.signature());
		goto label;
	}
	else if (!t.valid())
		goto label;

	clear();
	header();
	t.display();
	spacing(2);
	align_middle("1. ACCEPT");
	cout << endl;
	align_middle("2. DECLINE");
	cout << endl;
	align_middle("3. NEXT REQUEST");
	cout << endl;
	align_middle("ENTER INDEX [ 0 :: EXIT ] : ");
	cin >> response;
	switch (response[0])
	{
	case '0':
		break;
	case '1':
		cap.sign(t);
		confirm_ts.push_back(t.signature());
		c.input(c.clubName);
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
	clear();
	header();
	align_middle("NO NEW REQUESTS");
	cout << endl;
	align_middle("ENTER 0 TO GO BACK: ");
	cin >> response;
	return;
}

int loadStudent()
{
	string ldap, pass;
	align_middle("Enter LDAP: ", 5);
	cin >> ldap;
	getline(cin, pass);
	align_middle("Enter PASS: ", 5);
	pass = getpass("");
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
	align_middle("STUDENT GYMKHANA\n\n");
	f(i, 0, total)
		align_middle(to_string(i + 1) + ". " + societies[i] + "\n");
	cout << endl;
	string response;
	align_middle("Enter Index [ 0 :: BACK ] : ");
	cin >> response;

	if (response.size() > 1)
		return 0;
	int num = response[0] - '0';
	if (num == 0)
		return -1;
	else if (num < 1 || num > 6)
		return 0;
	s.input(societies[num - 1]);
	fin.close();
	return 1;
}

int loadClub()
{
	string response;
	align_middle("Enter Index [ 0 :: BACK ] : ");
	cin >> response;
	if (response.size() > 1)
		return 0;
	int num = response[0] - '0';
	if (num == 0)
		return -1;
	if (num < 1 || num > s.clubs.size())
		return 0;
	c.input(s.clubs[num - 1]);
	return 1;
}

int loadItem()
{
	string response;
	align_middle("Enter Index [ 0 :: BACK ] : ");
	cin >> response;
	if (response[0] - '0' < 0 || response[0] - '0' > 9 || response.size() > 6)
		return 0;
	int num = stoi(response);
	if (num == 0)
		return -1;
	int flag = 0;
	f(i, 0, c.itemsAvailable.size())
		flag |= (num == c.itemsAvailable[i].itemID);
	if (!flag)
		return 0;
	int levelChange = it.input(num);
	return levelChange;
}

int loadAction()
{
	string response;
	if (!find(c.members, stu.rollNo))
	{
		align_middle("YOU ARE NOT A MEMBER OF THIS CLUB YET\n");
		align_middle("REQUEST MEMBERSHIP? [y/n] ");
		cin >> response;
		if (response == "y")
		{
			stu.requestMembership(c.clubName);
			align_middle("REQUEST FILED\n");
			align_middle("ENTER 0 TO GO BACK: ");
			cin >> response;
			return -1;
		}
		else if (response == "n")
			return -1;
		else
			return 0;
	}
	else
	{
		clubMember.input(stu.rollNo, c.clubName);
		if (it.status == "ISSUED")
		{
			if (clubMember.rollNo == it.issuedBy.rollNo)
			{
				align_middle("RETURN? [y/n] ");
				cin >> response;
				if (response == "y")
				{
					clubMember.requestItemReturn(it.itemID);
					align_middle("REQUEST FILED\n");
					align_middle("ENTER 0 TO GO BACK: ");
					cin >> response;
					return -1;
				}
				else if (response == "n")
					return -1;
				else
					return 0;
			}
			else
			{
				align_middle("ENTER 0 TO GO BACK: ");
				cin >> response;
				return -1;
			}
		}
		else
		{
			align_middle("REQUEST ISSUE? [y/n] ");
			cin >> response;
			if (response == "y")
			{
				clubMember.requestItem(it.itemID);
				align_middle("REQUEST FILED\n");
				align_middle("ENTER 0 TO GO BACK: ");
				cin >> response;
				return -1;
			}
			else if (response == "n")
				return -1;
			else
				return 0;
		}
	}
}

int loadCaptainActions()
{
	int option;
	string response;
	if (c.captain != stu.rollNo)
	{
		align_middle("You are not the captain of " + c.clubName);
		align_middle("ENTER 0 TO GO BACK: ");
		cin >> response;
		return 1;
	}
	else
		cap.load(stu.rollNo);
	align_middle("1. SHOW TRANSACTION REQUESTS\n");
	align_middle("2. SHOW MEMBERS\n");
	align_middle("3. SHOW ITEMS\n");
	cout << endl;
	align_middle("ENTER INDEX [ 0 :: BACK ] : ");
	cin >> response;
	if (response.size() > 1)
		return 0;
	option = response[0] - '0';
	switch (option)
	{
	case 0:
		return 1;
	case 1:
		transactions();
		return 0;
	case 2:
		clear();
		header();
		for (auto member : c.members)
		{
			Student s;
			s.load(member);
			s.display();
		}
		align_middle("ENTER 0 TO GO BACK: ");
		cin >> response;
		return 0;
	case 3:
		clear();
		header();
		for (auto item : c.itemsAvailable)
		{
			item.display();
		}
		align_middle("ENTER 0 TO GO BACK: ");
		cin >> response;
		return 0;
	default:
		return 0;
	}
}

void EXIT(int input)
{
	level -= input;
}

void display()
{
	int exitStatus, levelChange;
	string response;
	switch (level)
	{
	case 0:
		exitStatus = loadStudent();
		if (!exitStatus)
			level++;
		break;
	case 1:
		align_middle("LOGIN AS:\n\n");
		align_middle("1. Student\n", 5);
		align_middle("2. Captain\n", 5);
		align_middle("3. Logout\n\n", 5);
		align_middle("Enter Index: ");
		cin >> response;
		if (response.size() > 1)
			return;
		mode = response[0] - '0';
		if (mode == 3)
			EXIT(1);
		else if (mode == 1 || mode == 2)
			level++;
		break;
	case 2:
		levelChange = loadSociety();
		level += levelChange;
		break;
	case 3:
		s.display();
		levelChange = loadClub();
		level += levelChange;
		break;
	case 4:
		if (mode == STUDENT)
		{
			c.display();
			levelChange = loadItem();
			level += levelChange;
			break;
		}
		else
		{
			exitStatus = loadCaptainActions();
			if (exitStatus)
				EXIT(1);
		}
		return;
	case 5:
		it.display();
		levelChange = loadAction();
		level += levelChange;
		break;
		return;
	default:
		EXIT(1);
	}
}
int main()
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	while (1)
	{
		clear();
		header();
		display();
	}
}