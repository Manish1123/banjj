#include<bits/stdc++.h>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

class Account {
private:
int accountNumber;
int deposit;
char name[50];
char type;
public:
void createAccount();
void showAccount();
void modify();
void dep(int);
void draw(int);
void report() const;
int getAccountNumber() const;
int getBalance() const;
char getType() const;
};

void Account :: createAccount() {
cout << "Enter the account number : \n";
cin >> accountNumber;
cout << "Enter the account holder full name : \n";
cin.ignore();
cin.getline(name , 50);
cout << "Enter type of the account : click => C for Current , S for Saving \n";

cin >> type;
type = toupper(type);
cout << "Deposit an initial amount : (>= 500 for saving account and >= 1000 for current account) \n";
cin >> deposit;
cout << "Account has been created successfully \n";
}

void Account :: showAccount() {
cout << "Account No. : " << accountNumber  << "\n";
cout << "Name : " << name << "\n";
cout << "Account type : " << type << "\n";
cout << "Total amount : " << deposit << "\n";
}

void Account :: modify() {
cout << "Account No. : " << accountNumber  << "\n";
cout << "Modify account holder name : \n";
cin.ignore();
cin.getline(name , 50);

cout << "Modify account type : \n";
cin >> type;
type = toupper(type);
cout << "Total amount : " << deposit << "\n";
}

void Account :: dep(int x) {
deposit += x;
}

void Account :: draw(int x) {
deposit -= x;
}

void Account :: report() const {
cout << accountNumber << setw(10) << " " << name << setw(10) << " " << type << setw(6) << " " << deposit << endl;

}

int Account :: getAccountNumber() const {
return accountNumber;
}
int Account :: getBalance() const {
return deposit;
}

char Account :: getType() const {
return type;
}


// function to write record in binary file
void write_account();
// function to display account details given by user
void display_sp(int);
// function to modify record of file
void modify_account(int);
// function to delete record of file
void delete_account(int);
// function to display all account details
void display_all();
// function to deposit or withdraw amount for given account
void deposit_withdraw(int , int);
// introduction screen function
void intro_menu();




int main()
{
char ch; int num;
intro_menu();
do {
system("cls");
cout << "\n\n\n\tMain Menu";
cout << "\n\n\t1) New Account";
cout << "\n\n\t2) Deposit Amount";
cout << "\n\n\t3) Withdraw Amount";
cout << "\n\n\t4) Balance Enquiry";
cout << "\n\n\t5) All Account Holder List";
cout << "\n\n\t6) Close An Account";
cout << "\n\n\t7) Modify Account Details";
cout << "\n\n\t8) Exit";
cout << "\n\n\tSelect an option (1-8) => ";

        cin >> ch;
system("cls");
switch (ch) {
case '1':
write_account();
break;
case '2':
cout << "\n\n\tEnter the account number : ";
cin >> num;
deposit_withdraw(num , 1);
break;
case '3':
cout << "\n\n\tEnter the account number : ";
cin >> num;
deposit_withdraw(num , 2);
break;
case '4':
cout << "\n\n\tEnter the account number : ";
cin >> num;
display_sp(num);
break;
case '5':
display_all();
break;
case '6':
cout << "\n\n\tEnter the account number : ";
cin >> num;
delete_account(num);
break;
case '7':
cout << "\n\n\tEnter the account number : ";
cin >> num;
modify_account(num);
break;
case '8':
cout << "\n\n\tThanks for using our bank management system.";
break;
default :
cout << "\a";
}
cin.ignore();
cin.get();
} while (ch != '8');

return 0;
}

void write_account() {
Account ac;
ofstream outFile;
outFile.open("account.dat" , ios::binary | ios::app);
ac.createAccount();
outFile.write(reinterpret_cast<char*> (&ac) , sizeof(Account));
outFile.close();
}


void display_sp(int num) {
Account ac;
ifstream inFile;
bool flag = false;
inFile.open("account.dat" , ios::binary);
if (!inFile) {
cout << "File count not be open , press any key..\n";
return;
}
cout << "\nBank Details\n";
while (inFile.read(reinterpret_cast<char*> (&ac) , sizeof(Account)) and !flag) {
if (ac.getAccountNumber() == num) {
ac.showAccount();
flag = true;
}
}
inFile.close();
if (!flag) {
cout << "\n\nNo user found with this account details\n";
}
}

void modify_account(int num) {
bool  found = false;
Account ac;
fstream File;
File.open("account.dat" , ios::binary | ios::in | ios::out);
if (!File) {
cout << "File count not be open , press any key..\n";
return;
}
while (!File.eof() and !found) {
File.read(reinterpret_cast<char*> (&ac) , sizeof(Account));
if (ac.getAccountNumber() == num) {
ac.showAccount();
cout << "\n\nEnter the new account details : \n";
ac.modify();
int pos = (-1) * static_cast<int>(sizeof(Account));
File.seekp(pos, ios::cur);
File.write(reinterpret_cast<char*> (&ac) , sizeof(Account));
cout << "\n\n\t Record updated..\n";
found = true;
}
}
File.close();
if (!found) {
cout << "\n\nRecord not found..\n";
}
}


void delete_account(int num) {
Account ac;
ifstream inFile;
ofstream outFile;
inFile.open("account.dat" , ios::binary);
if (!inFile) {
cout << "File count not be open , press any key..\n";
return;
}
outFile.open("Temp.dat" , ios::binary);
inFile.seekg(0 , ios::beg);
while (inFile.read(reinterpret_cast<char*>(&ac) , sizeof(Account))) {
if (ac.getAccountNumber() != num) {
outFile.write(reinterpret_cast<char*> (&ac) , sizeof(Account));
}
}
inFile.close();
outFile.close();
remove("account.dat");
rename("Temp.dat" , "account.dat");
cout << "\n\n\t Account deleted..\n";

}



void display_all() {
ifstream inFile;
Account ac;
inFile.open("account.dat" , ios::binary);
if (!inFile) {
cout << "File count not be open , press any key..\n";
return;
}
cout << "\n\n\t Account holder list\n";
cout << "----------------------------------------------------\n";
cout << "A/C no.             Name             Type    Balance\n";
cout << "----------------------------------------------------\n";
while (inFile.read(reinterpret_cast<char*> (&ac) , sizeof(Account))) {
ac.report();
}
inFile.close();
}



void deposit_withdraw(int num , int depordraw) {
bool found = false;
int amount;
Account ac;
fstream File;
File.open("account.dat" , ios::binary | ios::in | ios::out);
if (!File) {
cout << "File count not be open , press any key..\n";
return;
}
bool ok = true;
while (!File.eof() and !found) {
File.read(reinterpret_cast<char*> (&ac) , sizeof(Account));
if (ac.getAccountNumber() == num) {
ac.showAccount();
if (depordraw == 1) {
cout << "\n\n\tEnter the amount to be deposited\n";
cin >> amount;
ac.dep(amount);
}
if (depordraw == 2) {
cout << "\n\n\tEnter the amount to be withdraw\n";
cin >> amount;
int curr_bal = ac.getBalance() - amount;
if ((curr_bal < 500 and ac.getType() == 'S') or (curr_bal < 1000 and ac.getType() == 'C')) {
cout << "Insufficient Balance...\n";
ok = false;
}
else {
ac.draw(amount);
}
}
int pos = (-1) * static_cast<int>(sizeof(ac));
File.seekp(pos , ios::cur);
File.write(reinterpret_cast<char*> (&ac) , sizeof(Account));
if (ok)
cout << "\n\n\t Transaction completed...\n";
found = true;
}
}
File.close();
if (!found) {
cout << "\n\n\t Record not found..\n";
}
}


void intro_menu() {
cout << "\n\n\t Welcome to Compiler Based - Bank Banagement System\n";
cout << "\n\n\t Hope you'll love our service...\n";
}