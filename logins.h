#include "passwordmanager.h"
class Logins
{
public:
	    UserLoginInfo* UsersArr;
	    Logins(UserLoginInfo* UsersArr);
		bool searchByLoginName(const string &SearchLoginName);
		void resetLoginNo();
		void viewAllUserLoginInfo();
		bool deleteByLoginNo(int loginNo);
		bool addLoginRecord(string titleName,string loginName,string password,string URL);
		void updateLoginRecord(int loginNo);
		void showLog();
		void loginInfoOptions(char * Log);
};
