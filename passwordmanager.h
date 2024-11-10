#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include <string.h>
#include <cstdio>
#include <windows.h> 

#define MAX_USER 50
#define LOG_SIZE 1024
using namespace std;
char Log[1024];
//Log[0]='\0';
class StoreLoginInfo 
{
public:
	int LoginNo;
    string titleName;
    string loginName;
    string password;
    string URL;
    StoreLoginInfo* next;

   StoreLoginInfo(string titleName,string loginName,string password,string URL)
   {
	   this->LoginNo=0;
	   this->titleName=titleName;
	   this->loginName=loginName;
	   this->password=password;
	   this->URL=URL;
	   this->next=NULL;
   }
};

class UserFunc
{
public:
    StoreLoginInfo* ptrStoreLoginInfo;
    char Logs[2000];
	int countLoginInfo;

	UserFunc()
	{
		ptrStoreLoginInfo=NULL;
		this->Logs[0]='\0';
		countLoginInfo=0;
	}
};

class UserLoginInfo 
{
public:
    string userName;
    string password;
    UserFunc* ptrUserFunc;
    UserLoginInfo()
	{
		this->ptrUserFunc=NULL;
	}
   
};

class SuperBlock 
{
public:
    int totalInodes;
    int freeInode;

	SuperBlock()
	{
	    this->totalInodes=MAX_USER;
	   this->freeInode=MAX_USER;
	}

};

class PasswordManager 
{
private:
    UserLoginInfo* UsersArr[MAX_USER];
    SuperBlock superBlock;

public:
    PasswordManager();
    ~PasswordManager();
	UserLoginInfo* getUser(int userIndex);
	bool registerUser (const string& userName, const string& password);
	bool loginUser (const string& userName, const string& password);
	int findUserByUserName(const string& userName, const string& password);
	void waitFor20Seconds();
	void Functionality(const int userIndex,char *Log);
	int Settings(const int userIndex);
	bool changeMasterPassword(const int userIndex);
	bool deleteAccount(const int userIndex);
};