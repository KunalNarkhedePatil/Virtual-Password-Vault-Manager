#include "logins.h"

Logins::Logins(UserLoginInfo *UsersArr)
{
	this->UsersArr = UsersArr;
}
bool Logins::searchByLoginName(const string &SearchLoginName)
{
	bool bFlag = 0;
	if (SearchLoginName.empty())
	{
		return false;
	}
	StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;

	while (temp != NULL)
	{
		if (temp->loginName == SearchLoginName)
		{
			bFlag = 1;
			cout << "Title Name: " << temp->titleName << endl;
			cout << "Login Name: " << temp->loginName << endl;
			cout << "Password: " << temp->password << endl;
			cout << "Site Name: " << temp->URL << endl;
			cout << "-------------------------------------" << endl;
		}
		temp = temp->next;
	}
	if (temp == NULL && bFlag == 0)
	{
		return false;
	}
}

void Logins::resetLoginNo()
{
	int iCnt = 1;
	StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;
	while (temp != NULL)
	{
		temp->LoginNo = iCnt;
		temp = temp->next;
		iCnt++;
	}
}
void Logins::viewAllUserLoginInfo()
{
	if (UsersArr == NULL)
	{
		return;
	}

	StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;
	cout << "=============================================" << endl;
	while (temp != NULL)
	{
		cout << "LoginNo:" << temp->LoginNo << endl;
		cout << "Title Name: " << temp->titleName << endl;
		cout << "Login Name: " << temp->loginName << endl;
		cout << "Password: " << temp->password << endl;
		cout << "Site Name: " << temp->URL << endl;
		cout << "=============================================" << endl;
		temp = temp->next;
	}
}
bool Logins::deleteByLoginNo(int loginNo)
{
	StoreLoginInfo *first = UsersArr->ptrUserFunc->ptrStoreLoginInfo;
	StoreLoginInfo *current = first;
	StoreLoginInfo *prev = NULL;

	while (first != NULL && first->LoginNo == loginNo)
	{
		StoreLoginInfo *temp = first;
		first = first->next;
		delete temp;
	}
	UsersArr->ptrUserFunc->ptrStoreLoginInfo = first;

	current = first;

	while (current != NULL)
	{
		if (current->LoginNo == loginNo)
		{
			prev->next = current->next;
			delete current;
			resetLoginNo();
			return true;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return false;
}

bool Logins::addLoginRecord(string titleName, string loginName, string password, string URL)
{
	if (UsersArr == NULL)
		return false;

	StoreLoginInfo *newRecord = new StoreLoginInfo(titleName, loginName, password, URL);
	if (!newRecord)
		return false;
	StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;

	if (temp == NULL)
	{
		UsersArr->ptrUserFunc->ptrStoreLoginInfo = newRecord;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newRecord;
	}
	resetLoginNo();
	return true;
}

void Logins::updateLoginRecord(int loginNo)
{
	StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;

	while (temp != NULL)
	{
		if (temp->LoginNo == loginNo)
		{
			int choice = 0;
			do
			{
				cout << "Enter what you want to update" << endl;
				cout << "\n1. Title Name\n2. Login Name\n3. Password\n4. Site Name or URL\n5. Exit\n"
					 << endl;
				cout << "Enter choice: ";
				cin >> choice;
				cin.ignore();
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Invalid option. Please enter a number." << endl;
					continue;
				}
				if (choice < 1 || choice > 5)
				{
					cout << "Number out of range. Please enter a number between 1 and 5." << endl;
					continue;
				}
				switch (choice)
				{
				case 1:
				{
					string newTitleName;
					cout << "Enter New Title Name: ";
					cin >> newTitleName;
					temp->titleName = newTitleName;
					break;
				}
				case 2:
				{
					string newLoginName;
					cout << "Enter New Login Name: ";
					cin >> newLoginName;
					temp->loginName = newLoginName;
					break;
				}
				case 3:
				{
					string newPassword;
					cout << "Enter New Password: ";
					cin >> newPassword;

					temp->password = newPassword;
					break;
				}
				case 4:
				{
					string newURL;
					cout << "Enter New URL: ";
					cin >> newURL;
					temp->URL = newURL;
					break;
				}
				case 5:
				{
					return;
				}
				default:
					cout << "Invalid choice. Please try again." << endl;
					strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
					break;
				}
			} while (choice != 5);
		}
		temp = temp->next;
	}
}

void Logins::showLog()
{
	cout << "==============================================" << endl;
	cout << UsersArr->ptrUserFunc->Logs << endl;
	cout << "==============================================" << endl;
}

void Logins::loginInfoOptions(char *Log)
{
	strcat(UsersArr->ptrUserFunc->Logs, Log);
	Log[0] = '\0';
	int choice = 0;

	do
	{
		cout << "Enter the Functionality\n";
		cout << "1. Add Info\n2. View All User Login Info\n3. Search By Login Name\n4. Delete By Login No\n5. Update By Login No\n6. Show Logs\n7. Exit\n";
		cout << "Enter choice: ";

		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid option. Please enter a number." << endl;
			continue;
		}

		if (choice < 1 || choice > 7)
		{
			cout << "Number out of range. Please enter a number between 1 and 7." << endl;
			continue;
		}

		switch (choice)
		{
		case 1:
		{
			cin.ignore();
			string titleName, loginName, password, URL;

			cout << "Enter the title Name: ";
			getline(cin, titleName);

			cout << "Enter the login Name: ";
			getline(cin, loginName);

			cout << "Enter password: ";
			getline(cin, password);

			cout << "Enter the site Name or URL: ";
			getline(cin, URL);

			if (addLoginRecord(titleName, loginName, password, URL))
			{
				cout << "New record inserted successfully into Login Info." << endl;
				char logMessage[100];
				sprintf(logMessage, "New record inserted successfully into Login Info with %s\n", loginName.c_str());
				strcat(UsersArr->ptrUserFunc->Logs, logMessage);
			}
			else
			{
				cout << "Failed to insert record." << endl;
				strcat(UsersArr->ptrUserFunc->Logs, "Failed to insert record.\n");
			}
			break;
		}
		case 2:
		{
			strcat(UsersArr->ptrUserFunc->Logs, "View All User Login Info.\n");
			viewAllUserLoginInfo();
			break;
		}
		case 3:
		{
			strcat(UsersArr->ptrUserFunc->Logs, "Search By Login Name.\n");
			string searchLoginName;
			cin.ignore();
			cout << "Enter the login name to search: ";
			getline(cin, searchLoginName);

			bool found = Logins::searchByLoginName(searchLoginName);

			if (!found)
			{
				cout << "There is no such Login present." << endl;
				strcat(UsersArr->ptrUserFunc->Logs, "There is no such Login present.\n");
			}
			else
			{
				char logMessage[100];
				sprintf(logMessage, "Search By Login Name with %s\n", searchLoginName.c_str());
				strcat(UsersArr->ptrUserFunc->Logs, logMessage);
			}
			break;
		}
		case 4:
		{
			viewAllUserLoginInfo();
			int loginNo = 0;
			cin.ignore();
			cout << "Enter the Login No to delete: ";
			cin >> loginNo;

			bool deleted = deleteByLoginNo(loginNo);

			if (deleted)
			{
				cout << "Deleted the login with No " << loginNo << endl;
				char logMessage[50];
				sprintf(logMessage, "Deleted the login with No %d\n", loginNo);
				strcat(UsersArr->ptrUserFunc->Logs, logMessage);
			}
			break;
		}
		case 5:
		{
			viewAllUserLoginInfo();
			int loginNo = 0;

			cout << "Enter the Login No to update: ";
			cin >> loginNo;

			updateLoginRecord(loginNo);

			char logMessage[50];
			sprintf(logMessage, "Updated the login with No %d\n", loginNo);
			strcat(UsersArr->ptrUserFunc->Logs, logMessage);
			break;
		}
		case 6:
		{
			showLog();
			break;
		}
		case 7:
			strcat(UsersArr->ptrUserFunc->Logs, "Exit\n");
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
			strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 7);
}

PasswordManager::PasswordManager()
{
	for (int i = 0; i < MAX_USER; i++)
	{
		UsersArr[i] = NULL;
	}
}
PasswordManager::~PasswordManager()
{
	for (int i = 0; i < MAX_USER; i++)
	{
		delete UsersArr[i];
	}
}
UserLoginInfo *PasswordManager::getUser(int userIndex)
{
	return this->UsersArr[userIndex];
}
bool PasswordManager::registerUser(const string &userName, const string &password)
{
	if (userName.empty() || password.empty())
	{
		return false;
	}

	for (int i = 0; i < MAX_USER; i++)
	{
		if (UsersArr[i] == NULL)
		{
			UsersArr[i] = new UserLoginInfo();
			if (!UsersArr[i])
				return false; // Check for allocation failure
			UsersArr[i]->userName = userName;
			UsersArr[i]->password = password;
			UsersArr[i]->ptrUserFunc = new UserFunc;
			superBlock.freeInode--;
			return true;
		}
	}
	return false;
}
bool PasswordManager::loginUser(const string &userName, const string &password)
{
	if (userName.empty() || password.empty())
	{
		return false;
	}

	for (int i = 0; i < MAX_USER; i++)
	{
		if (UsersArr[i] != NULL &&
			UsersArr[i]->userName == userName &&
			UsersArr[i]->password == password)
		{

			return true;
		}
	}
	return false;
}
int PasswordManager::findUserByUserName(const string &userName, const string &password)
{
	bool bFlag = false;
	for (int i = 0; i < MAX_USER; i++)
	{
		if (UsersArr[i] != NULL && UsersArr[i]->userName == userName && UsersArr[i]->password == password)
		{
			bFlag = true;
			return i;
		}
	}
	if (bFlag == false)
	{
		return -1;
	}
}

void PasswordManager::waitFor20Seconds()
{
	cout << "Waiting for 20 seconds..." << endl;
	Sleep(20000);
	return;
}
bool PasswordManager::changeMasterPassword(const int userIndex)
{
	string oldPassword, newPassword, confirmPassword;
	cin.ignore();

	cout << "Enter your current password: ";
	getline(cin, oldPassword);

	cout << "Enter your new password: ";
	getline(cin, newPassword);

	cout << "Re-enter your new password to confirm: ";
	getline(cin, confirmPassword);

	if (newPassword != confirmPassword)
	{
		cout << "Passwords don't match. Try again." << endl;
		return false;
	}

	UsersArr[userIndex]->password = newPassword;
	cout << "Password changed successfully!" << endl;
	return true;
}
bool PasswordManager::deleteAccount(const int userIndex)
{
	delete UsersArr[userIndex];
	UsersArr[userIndex] = NULL;
	return true;
}
int PasswordManager::Settings(const int userIndex)
{
	int choice = 0;
	cout << "Select an option:" << endl;

	do
	{
		cout << "\n1. Change Master Password\n2. Delete Account\n3. Exit\n4. Logout\n";
		cout << "Enter your choice: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid input. Please enter a number." << endl;
			strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "Invalid input. Please enter a number.\n");
			continue;
		}

		if (choice < 1 || choice > 4)
		{
			cout << "Please enter a number between 1 and 4." << endl;
			continue;
		}

		switch (choice)
		{
		case 1:
		{
			bool success = changeMasterPassword(userIndex);
			if (success)
			{
				cout << "Master password updated successfully." << endl;
				strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "Master password updated successfully.\n");
			}
			break;
		}
		case 2:
		{
			bool success = deleteAccount(userIndex);
			if (success)
			{
				cout << "Account deleted successfully." << endl;
				strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "Account deleted successfully.\n");
			}
			break;
		}
		case 3:
			return 1;

		case 4:
			return 2;

		default:
			cout << "An error occurred. Try again." << endl;
			strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "Invalid choice. Try again.\n");
			break;
		}
	} while (choice != 4);
}
void PasswordManager::Functionality(const int userIndex, char *Log)
{
	int choice = 0;
	cout << "-------------------------------------" << endl;
	cout << "Enter the Functionality" << endl;

	do
	{
		cout << "1. Logins\n2. Credit Card\n3. Bank Details\n4. Settings\n5. Logout\n";
		cout << "Enter choice: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid option. Please enter a number." << endl;
			continue;
		}

		if (choice < 1 || choice > 5)
		{
			cout << "Number out of range. Please enter a number between 1 and 5." << endl;
			continue;
		}

		switch (choice)
		{
		case 1:
		{
			strcat(Log, "Login Functionality\n");
			Logins logins(UsersArr[userIndex]);
			logins.loginInfoOptions(Log);
			break;
		}
		case 2:
		{
			// Credit Card functionality placeholder
			break;
		}
		case 3:
		{
			// Bank Details functionality placeholder
			break;
		}
		case 4:
		{
			int iRet = Settings(userIndex);
			if (iRet == 1)
			{
				break;
			}
			if (iRet == 2)
			{
				return;
			}
			break;
		}
		case 5:
		{
			return;
		}
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	} while (choice != 5);
}
int main()
{

	cout << "\n";
	cout << "                                +--------------------------------------------------+" << endl;
	cout << "                                |                                                  |" << endl;
	cout << "                                |      >>> Virtual Password Vault Manager <<<      |" << endl;
	cout << "                                |                                                  |" << endl;
	cout << "                                +--------------------------------------------------+" << endl;
	cout << "                                |           Secure your passwords safely!          |" << endl;
	cout << "                                +--------------------------------------------------+" << endl;

	PasswordManager pm;
	int choice = 0;
	int MaxAttempt = 0;
	char Log[LOG_SIZE] = ""; // Log buffer

	do
	{
		cout << "\n--- Virtual Password Manager ---\n";
		cout << "1. Register\n2. Login\n3. Exit\n";
		cout << "----------------------------------\n";
		cout << "Enter choice: ";
		cin >> choice;
		cin.ignore();

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid option. Please enter a number." << endl;
			continue;
		}
		if (choice < 1 || choice > 3)
		{
			cout << "Number out of range. Please enter a number between 1 and 3." << endl;
			continue;
		}

		string username, password;

		switch (choice)
		{
		case 1: // Register
		{
			cout << "Enter username: ";
			getline(cin, username);
			cout << "Enter password: ";
			getline(cin, password);
			int userIndex = 0;
			userIndex = pm.findUserByUserName(username, password);
			if (userIndex >= 0)
			{
				cout << "User Already Exists\n"
					 << endl;
				char logMessage[100];
				sprintf(logMessage, "User Already Exists: %s\n", username.c_str());
				strcat(Log, logMessage);
				break;
			}

			if (pm.registerUser(username, password))
			{
				cout << "User  registered successfully." << endl;

				char logMessage[100];
				sprintf(logMessage, "User  registered successfully: %s\n", username.c_str());
				strcat(Log, logMessage);
				MaxAttempt = 0;
			}
			else
			{
				cout << "Registration failed. Maximum users reached or input error." << endl;
				strcat(Log, "Registration failed. Maximum users reached or input error.\n");
			}
			break;
		}

		case 2: // Login
			if (MaxAttempt >= 3)
			{
				cout << "You have reached the maximum attempts. Please wait 20 seconds." << endl;
				pm.waitFor20Seconds();
				MaxAttempt = 0;
				break;
			}

			cout << "Enter username: ";
			getline(cin, username);
			cout << "Enter password: ";
			getline(cin, password);

			if (pm.loginUser(username, password))
			{

				cout << "User  logged in successfully." << endl;
				strcat(Log, "User  logged in successfully.\n");
				int userIndex = pm.findUserByUserName(username, password);
				// UserLoginInfo* User=pm.getUser(userIndex);
				// Logins logins(User);
				// logins.loginInfoOptions(Log);

				pm.Functionality(userIndex, Log);
				MaxAttempt = 0;
			}
			else
			{
				MaxAttempt++;
				cout << "Login failed. Incorrect username or password." << endl;

				if (MaxAttempt == 3)
				{
					strcat(Log, "You have reached the maximum attempts. Please wait 20 seconds.\n");
				}
				strcat(Log, "Login failed. Incorrect username or password.\n");
			}
			break;

		case 3: // Exit
			cout << "Exiting the application." << endl;
			exit(0);
			break;

		default:
			cout << "Invalid choice. Please try again." << endl;
			strcat(Log, "Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 3);

	return 0;
}