#include<fstream.h>
#include<ctype.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>

class account
{
	int acno;
	char name[50];
	long deposit;
	char type;
      public:
	void create_account();
	void show_account();
	void modify();
	void dep(int);
	void draw(int);
	void report();
	int retacno();
	int retdeposit();
	char rettype();
};

void account::create_account()
{
	cout<<"\nEnter the account no. : ";
	cin>>acno;
	cout<<"\nEnter the name of the account holder : ";
	gets(name);
	cout<<"\nEnter type of the account (Current-c/Saving-s) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter the initial amount";
	cout<<"\n(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nACCOUNTCREATED!..";
}

void account::show_account()
{
	cout<<"\nAccountno. : "<<acno;
	cout<<"\nAccount holder's name : "<<name;
	cout<<"\nType of account : "<<type;
	cout<<"\nBalanceamount : "<<deposit;
}


void account::modify()
{
	cout<<"\nAccount no."<<acno;
	cout<<"\n\nEnter new name of the account holder : ";
	gets(name);
	cout<<"\nEnter new type (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter the changed amount : ";
	cin>>deposit;
}


void account::dep(int x)
{
	deposit+=x;
}


void account::draw(int x)
{
	deposit-=x;
}

void account::report()
{
	cout<<acno<<setw(10)<<" "<<name<<setw(9)<<" "<<type<<setw(11)<<deposit<<endl;
}

int account::retacno()
{
	return acno;
}

int account::retdeposit()
{
	return deposit;
}

char account::rettype()
{
	return type;
}

//FUNCTION DECLARATIONS

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit(int);
void withdraw(int);
void intro();


//    	THE MAIN FUNCTION OF THE PROGRAM

void main()
{
	char ch;
	int num;
	clrscr();
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\t***MAIN MENU***";
		cout<<"\n\n\t1. NEW ACCOUNT";
		cout<<"\n\n\t2. DEPOSIT AMOUNT";
		cout<<"\n\n\t3. WITHDRAW AMOUNT";
		cout<<"\n\n\t4. BALANCE ENQUIRY";
		cout<<"\n\n\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t6. CLOSE AN ACCOUNT";
		cout<<"\n\n\t7. MODIFY AN ACCOUNT";
		cout<<"\n\n\t8. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) : ";
		cin>>ch;
		clrscr();

	   switch(ch)
		{
		 case '1':write_account();
				 break;
		 case '2':cout<<"\n\nEnter the account no. : ";
				cin>>num;
			      deposit(num);
				 break;
		 case '3':cout<<"\n\nEnter the account no. : ";
				cin>>num;
				withdraw(num);
				break;
		 case '4':cout<<"\n\nEnter the account no. : ";
				cin>>num;
				display_sp(num);
				break;
		 case '5':display_all();
				break;
		 case '6':cout<<"\n\nEnter the account no. : ";
				cin>>num;
				delete_account(num);
				break;
		 case '7':cout<<"\n\nEnter the account no. : ";
				cin>>num;
				modify_account(num);
				break;
		 case '8':cout<<"\n\n\tThanks for using bank managemnt system";
				break;
		default :cout<<"\Enter correctly";
	      }

	}while(ch!='8');
	getch();
}


//      FUNCTION TO WRITE IN FILE

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("acc.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write((char *) &ac, sizeof(account));
	outFile.close();
}




//    	FUNCTION TO READ SPECIFIC RECORD FROM FILE

void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
	inFile.open("acc.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be opened !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist";
	}



//    	FUNCTION TO MODIFY RECORD OF FILE

void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
	File.open("acc.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be opened !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter the new details of account"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
		File.write((char *) &ac, sizeof(account));
		cout<<"\n\n\t Record Updated!";
		 found=1;
		  }
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}


//    	FUNCTION TO DELETE RECORD OF FILE

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("acc.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write((char *) &ac, sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("acc.dat");
	rename("Temp.dat","acc.dat");
	cout<<"\n\n\tRecord Deleted ..";
}


//    	FUNCTION TO DISPLAY ALL ACCOUNT DEPOSIT LIST

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("acc.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	else
       { cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type     Balance\n";
	cout<<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
      }
	inFile.close();
}


//    	FUNCTION TO DEPOSIT AMOUNTS

void deposit (int n)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
	File.open("acc.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			{
				cout<<"\n\n\tTO DEPOSIT AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited : ";
				cin>>amt;
				ac.dep(amt);
			}
		int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	}
	 }
File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}

//       FUNCTION TO WITHDRAW AMOUNTS

void  withdraw(int n)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
File.open("acc.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdrawn : ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 &&ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficient balance";
				else
					ac.draw(amt);
		}
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	}
	 }
File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}


//    INTRODUCTION FUNCTION
void intro()
{
	int pas;
	cout<<"\t\t ********************************";
	cout<<endl;
	cout<<"\t\t     BANK MANAGEMENT SYSTEM     ";
	cout<<endl;
	cout<<"\t\t   COMPLETE BANKING SOLUTIONS!!!   ";
	cout<<endl;
	cout<<"\t\t ********************************";
cout<<endl;
	cout<<endl;
	cout<<endl;
for(int i=0;i<3;i++)
	{
	cout<<"\nEnter the password : ";
	cin>>pas;
	   if(pas==1234)
	    break;
	   if(i==2)
	   {
	cout<<"\nWrong password ";
	cout<<"\nExiting ";
	getch();
	exit(0);
	   }
	   else
	   if(pas!=1234)
	   {
	cout<<"\nWrong password ";
	cout<<"\nEnter again";
	   }
	}

getch();
}



