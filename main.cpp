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
bool login=false;
string loginRollNo;
void loginStudent();
void registerStudent();

#define f(i, n, m) for (int i = n; i < m; i++)


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

void login_display()
{
	int ch;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t******************************\n";
	cout<<"\t\t\t\t\t 1.  Login\n";
	cout<<"\t\t\t\t\t 2.  Register\n";
	cin>>ch;
	switch (ch){
		case 1: loginStudent();
		break; 
		case 2:registerStudent();
		break;
		default:login_display();
	}

}
void Logout()
{
	login=false;
}
void loginStudent()
{
	string rollno,password,word;
	ifstream fin ("students.txt");
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\t Enter Your Roll Number\t: ";
	cin>>rollno;
	cout<<"\n";
	cout<<"\t\t\t\t\t\t Enter Your Password\t: ";
	cin>>password;
	cout<<"\n";
	while(fin>>word)
	{
		string pass;
		fin>>pass;
		if(word==rollno && pass==password)
		{cout<<"\t\t\t\t\t\t\t ** Login Successfully**    \n";
		loginRollNo=rollno;
		login=true;
		return ;
		}
		else
		{
			cout<<"\n\n\n\t\t\t\t*Incorrect Rollno or password*\n ";
			loginStudent();
			return ;
		}
	}
	login_display();
}
void registerStudent()
{
	Student newstudent;
	string confirmPassword;
	cout<<"\n\n\n\n\t\t\t\t\t\t Enter Your Name\t: ";
	cin>>newstudent.name;
	cout<<"\n";
	cout<<"\t\t\t\t\t\t Enter You  Ldap credentials\t: ";
	cin>>newstudent.ldap;
	cout<<"\n";
	cout<<"\t\t\t\t\t\t Enter Your Roll Number\t: ";
	cin>>newstudent.rollNo;
	cout<<"\n";
	cout<<"\t\t\t\t\t\t Enter Your Password\t: ";
	cin>>newstudent.password;
	cout<<"\n";
	cout<<"\t\t\t\t\t\t Confirm Your Password\t: ";
	cin>>confirmPassword;
	cout<<"\n";
	if(newstudent.password==confirmPassword)
	{
		ofstream fout("students.txt",ios::app);
		fout<<newstudent.rollNo<<" "<<newstudent.password<<"\n";
		cout<<"\t\t\t\t\t** Congratulations Student Registered Succesfully **\n";
		loginRollNo=newstudent.rollNo;
		login=true;
		
	}
	else
	{
		cout<<"\t\t\t\t\t\t\t Password don't matched\n";
		registerStudent();
	}
}



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
		cout << "\n\n\n\n\n\t\t\t\t\t\t**"<<societyName <<"**"<< endl;
		cout<<"\t\t\t\t\t******************************************\n";
		f(i, 0, clubs.size()) cout <<"\t\t\t\t\t\t\t"<< clubs[i] << endl;
		cout<<"\t\t\t\t\t******************************************";
	}
} s;

class Item
{
public:
	int itemId;
	string Name;
	bool status;
	void updateStatus()
	{
        
	}
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
			int n;
			fin1 >> n;
			string s;
			getline(fin1, s);
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
				getline(fin1, s);
				itemsAvailable[j].status=status;
			}
			if (clubName == name)
				break;
		}
		fin1.close();
		
	}
	void display()
	{
		cout<<"\n\n\n\n\n\n";
		
		cout <<"\t\t\t\t\t\t**"<< clubName <<"**"<< endl;

		f(i, 0, members.size()) cout <<"\t\t\t\t\t\t"<< members[i] << endl;
		cout<<"\n\n\t\t\t\t\t\tItems Available\n";
		cout<<"\t\t\t\t\t*****************************\n";
		cout<<"\t\t\t\t\tItemId\tItem Name\tstatus\n";
		f(i, 0, itemsAvailable.size()) 
		cout <<"\t\t\t\t\t" <<itemsAvailable[i].itemId <<"\t"<<itemsAvailable[i].Name<<"\t"<<itemsAvailable[i].status<< endl;
		cout<<"\t\t\t\t\t*****************************\n";
		int Id;
		cout<<"\n\n\\t\t\t\tEnter Item Id To Issue \n";
		cin>>Id;
		if(login)
		{
			;
		}
		else
		{
	        login_display();
		}
		

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
	cout<<"\n\n\n\n\n\t\t\t\t\t\t\t***Societies***\n";
	cout<<"\n\n\n\t\t\t\t\t****************************************************\n";
	f(i, 0, 6) cout << "\t\t\t\t\t\t  "<<i + 1 << "." << societies[i] << endl;
	cout<<"\n\n\t\t\t\t\t****************************************************\n";
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
		cout << "\n\n\n\n\n\n\t\t\t\t\t***************************\n\t\t\t\t\t\t1. Student\n\t\t\t\t\t\t2. Captain\n\t\t\t\t\t\t3: Exit\n\t\t\t\t\t***************************\n";
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