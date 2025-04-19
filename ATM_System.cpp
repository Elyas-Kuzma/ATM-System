
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>


using namespace std;

const string ClientsFileName = "Clients.txt";

enum enATMSystimOptions
{

	QuickWithdraw = 1,
	NormalWithdraw = 2,

	Deposit = 3,
	CheckBalance = 4,

	ChangePINCode = 5,
	TransferAmount = 6,

	Logout = 7
};


enum enQuickWithdrawAmount
{

	eTwenty = 1,
	eFifty = 2,

	eOneHundred = 3,
	eTowHundred = 4,

	eFourHundred = 5,
	eSixHundred = 6,

	eEigthHundred = 7,
	eOneThusand = 8,

	eExit = 9

};


struct stClient
{

	string AccountNumber;
	string PINCode;
	string ClientName;
	string PhoneNumber;
	double AccountBalance;

};


// Declaration

vector<stClient> LoadClientDataFromFile(string);

void ShowATM_MainMenu();

void ShowNormalWithdrawScreen();

void DisplayQuickWithdrawMenu();

void ShowTransferAmountScreen();

void Login();
///


//Global
vector<stClient> vClients = LoadClientDataFromFile(ClientsFileName);

stClient CurrentClient;

///



string Line(short LineLength, char LineType = '=')
{

	string line = "";
	for (short i = 0; i < LineLength; i++)
		line += LineType;

	return line;

}


string Tab(short TabNumber)
{

	string tab = "";
	for (short i = 0; i < TabNumber; i++)
		tab += "\t";

	return tab;

}


short ReadATMSystimOption()
{

	short Option;
	cout << "Choose Whate do you want to do?[1-7]....";
	cin >> Option;

	while (cin.fail() || Option < 1 || Option > 7)
	{
		cin.clear();
		// numeric_limits<streamsize>::max(), '\n'

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\nInvalide Input Please Enter a valide Option: ";

		cin >> Option;
	}

	return Option;
}


short ReadQuickWithdrawOption()
{
	short Option;
	cout << "Enter option [1 - 9] : ";
	cin >> Option;

	while (cin.fail() || Option < 1 || Option >9)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Option Enter Another One: ";
		cin >> Option;
	}

	return Option;
}


vector<string> SplitString(string Dataline, string Seperetor = "#//#")
{
	vector<string> vClient;
	short Pos = 0;
	string sWord = "";

	while ((Pos = Dataline.find(Seperetor)) != string::npos)
	{
		sWord = Dataline.substr(0, Pos);

		if (sWord != "")
			vClient.push_back(sWord);

		Dataline.erase(0, Pos + Seperetor.length());
	}

	if (Dataline != "")
		vClient.push_back(Dataline);

	return vClient;
}


string ConvertClientRecordToDataLine(stClient Client, string Seperetor = "#//#")
{
	string DataLine;

	DataLine = Client.AccountNumber + Seperetor
		+ Client.PINCode + Seperetor
		+ Client.ClientName + Seperetor
		+ Client.PhoneNumber + Seperetor
		+ to_string(Client.AccountBalance);

	return DataLine;
}


stClient ConvertClientDataLineToRecord(string DataLine)
{
	vector<string> vClients = SplitString(DataLine);

	stClient ClientRecord;

	ClientRecord.AccountNumber = vClients.at(0);
	ClientRecord.PINCode = vClients.at(1);
	ClientRecord.ClientName = vClients.at(2);
	ClientRecord.PhoneNumber = vClients.at(3);
	ClientRecord.AccountBalance = stod(vClients.at(4));

	return ClientRecord;
}


vector<stClient> LoadClientDataFromFile(string FileName)
{

	vector<stClient> vClients;

	fstream FileVariable;

	FileVariable.open(FileName, ios::in);

	if (FileVariable.is_open())
	{
		string Line;

		while (getline(FileVariable, Line))
		{
			vClients.push_back(ConvertClientDataLineToRecord(Line));
		}
		FileVariable.close();
	}

	return vClients;
}


bool SaveClientsVectorDataToFile(string FileName, vector<stClient> vClients)
{

	fstream FileVariable;

	FileVariable.open(FileName, ios::out);

	if (FileVariable.is_open())
	{
		for (stClient Cl : vClients)
			FileVariable << ConvertClientRecordToDataLine(Cl) << endl;

		FileVariable.close();
		return true;
	}

	return false;

}


void DisplayHeader_LoginScreen()
{
	cout << Line(35, '_') << "\n";
	cout << Tab(1) << "Login Screen\n";
	cout << Line(35, '_') << endl;
}


void DisplayHeader_QuickWithdrawScreen()
{

	cout << Line(40) << "\n";
	cout << Tab(1) << "Quick Withdraw Screen\n";
	cout << Line(40) << "\n";

}


void DisplayHeader_NormalWithdrawScreen()
{

	cout << Line(40, '_') << endl;
	cout << Tab(1) << "Normal Withdraw Screen\n";
	cout << Line(40, '_') << "\n";

	cout << "Your balance is : " << CurrentClient.AccountBalance << "\n";

}


void DisplayHeader_DepositScreen()
{
	cout << Line(40, '_') << "\n";
	cout << Tab(1) << "Deposite Screen\n";
	cout << Line(40, '_') << "\n";

	cout << "Your balance is : " << CurrentClient.AccountBalance << "\n";

}


void DisplayHeader_CheckBalanceScreen()
{
	cout << Line(40, '_') << "\n";
	cout << Tab(1) << "Account Balance Screen\n";
	cout << Line(40, '_') << "\n";
}


void DisplayHeader_TransferAmountScreen()
{
	cout << Line(40, '_') << "\n";
	cout << Tab(1) << "Trensfer Amount Screen\n";
	cout << Line(40, '_') << "\n";

	cout << "Your balance is : " << CurrentClient.AccountBalance << "\n";

}


void DisplayHeader_ChangePINCodeScreen()
{
	
	cout << Line(40, '_') << "\n";
	cout << Tab(1) << "Change PIN Code Screen\n";
	cout << Line(40, '_') << "\n";

}


void GoBackTo_MainMenuScreen()
{
	cout << "\nEnter Any key to go back to Main Menu...";

	system("pause>0");
	 ShowATM_MainMenu();
		

}


void GoBackTo_QuickWithdrawMinue()
{
	system("pause");
	DisplayQuickWithdrawMenu();
}


///////////////////////////////////////////////////////////



bool FindClientByAccountNumberAndPINCode(string AccountNumber, string PINCode, stClient& Client)
{
	for(stClient Cl : vClients)
		if (Cl.AccountNumber == AccountNumber && Cl.PINCode == PINCode)
		{
			Client = Cl;
			return true;
		}
	return false;
}


bool FindClientByAccountNumber(string AccountNumber)
{

	for (stClient& Cl : vClients)
		if (Cl.AccountNumber == AccountNumber)
			return true;
	
	return false;
}


bool FindClientByAccountNumber(string AccountNumber,stClient &Client)
{

	for (stClient& Cl : vClients)
		if (Cl.AccountNumber == AccountNumber)
		{
			Client = Cl;
			return true;
		}

	return false;
}


bool LoadClientInfo(string Accountnumber, string PINCode,stClient &Client)
{
	return FindClientByAccountNumberAndPINCode(Accountnumber, PINCode, Client);
}


short GetQuickWithdrawAmount(enQuickWithdrawAmount Amount)
{
	short arrAmount[] = { 0,20,50,100,200,400,600,800,1000 };
	return arrAmount[Amount];
}


bool DepositAmountToClientBalanceByAccountNumber(string AccountNumber, int Amount)
{
	for(stClient &Cl : vClients)
		if (Cl.AccountNumber == AccountNumber)
		{
			Cl.AccountBalance += Amount;
			SaveClientsVectorDataToFile(ClientsFileName,vClients);
			return true;
		}
	return false;

}


void PerformQuickWithdrawMenuOption(enQuickWithdrawAmount Option)
{

	if (Option == enQuickWithdrawAmount::eExit)
		ShowATM_MainMenu();

	short WithdrawBalance = GetQuickWithdrawAmount(Option);

	if (WithdrawBalance > CurrentClient.AccountBalance)
	{
		cout << "\nThe Amount exceeds your balance, make another choice.\n\n";
		system("pause");
		DisplayQuickWithdrawMenu();
		return;
	}

	char WithdrawAccept;

	cout << "\nAre you sure you want to wihtdraw " << WithdrawBalance << " amount?[N/Y]...";
	cin >> WithdrawAccept;

	if (toupper(WithdrawAccept) == 'Y')
	{
		DepositAmountToClientBalanceByAccountNumber(CurrentClient.AccountNumber, WithdrawBalance * -1);
		CurrentClient.AccountBalance -= WithdrawBalance;

		cout << "\nDone Successfully, the New Balance is : " << CurrentClient.AccountBalance << "\n";
	}
	else
		cout << "\nThe request has been canceld.\n";

}


void DisplayQuickWithdrawMenu()
{
	system("cls");

	cout << "\t[1] 20\t\t[2] 50\n";
	cout << "\t[3] 100\t\t[4] 200\n";
	cout << "\t[5] 400\t\t[6] 600\n";
	cout << "\t[7] 800\t\t[8] 1000\n";
	cout << "\t[9] Exit\n";

	cout << Line(40, '_') << endl;
	cout << "Your Balance : " << CurrentClient.AccountBalance << "\n";


	PerformQuickWithdrawMenuOption((enQuickWithdrawAmount)ReadQuickWithdrawOption());
}


void ShowQuickWithdrawScreen()
{

	DisplayHeader_QuickWithdrawScreen();
	DisplayQuickWithdrawMenu();

}


int ReadWithdrawAmount()
{
	int Amount;

	do
	{
	
		cout << "\nEnter an Amount multiple of 5's : ";
		cin >> Amount;

	} while (!(Amount % 5 == 0));
	//Amount % 5 != 0

	return Amount;
}


void PerformNormalWithdrawOption()
{
	int WithdrawAmount = ReadWithdrawAmount();

	if (WithdrawAmount > CurrentClient.AccountBalance)
	{
		cout << "\nThe Amount Exceeds your balance, Enter another Amount.\n";
		system("pause");
		ShowNormalWithdrawScreen();
		return;
	}

	char Answer;

	cout << "\nAre you sure you want to withdraw " << WithdrawAmount << " From your balance?[N/Y]...";
	cin >> Answer;


	if (toupper(Answer) == 'Y')
	{
		DepositAmountToClientBalanceByAccountNumber(CurrentClient.AccountNumber, WithdrawAmount * -1);
		CurrentClient.AccountBalance -= WithdrawAmount;

		cout << "\nDone Successfully,the new balance is : " << CurrentClient.AccountBalance << "\n";
	}
	else
		cout << "\nThe request has been camceld.\n";
}


void ShowNormalWithdrawScreen()
{
	system("cls");
	DisplayHeader_NormalWithdrawScreen();
	PerformNormalWithdrawOption();
}


double ReadDepositeAmount()
{
	double Amount;

	do
	{

		cout << "\nEnter a Deposite Amount : ";
		cin >> Amount;


	} while (Amount <= 0);

	return Amount;
}


void PerformDepositeOption()
{

	double DepositAmount = ReadDepositeAmount();
	char DepositAcception;


	cout << "\nAre you sure you want to Deposit " << DepositAmount << " In your Balance?[N/Y]...";
	cin >> DepositAcception;

	if (toupper(DepositAcception) == 'Y')
	{
		DepositAmountToClientBalanceByAccountNumber(CurrentClient.AccountNumber, DepositAmount);
		CurrentClient.AccountBalance += DepositAmount;

		cout << "\nDone Successfully,the new balance is : " << CurrentClient.AccountBalance << "\n";
	}
	else
		cout << "\nThe request has been canceld.\n";

}


void ShowDepositScreen()
{
	DisplayHeader_DepositScreen();
	PerformDepositeOption();
}


void ShowCheckBalanceScreen()
{
	DisplayHeader_CheckBalanceScreen();
	cout << "\n\tYour Balance is : " << CurrentClient.AccountBalance << "\n";
}


bool ChangeClientPINCodeByAccountNumber(string AccountNumber, string NewPINCode)
{
	for(stClient &Cl : vClients)
		if (Cl.AccountNumber == AccountNumber)
		{
			Cl.PINCode = NewPINCode;
			SaveClientsVectorDataToFile(ClientsFileName, vClients);
			return true;
		}
	return false;

}


void PerformChangePINCodeOption()
{
	string NewPINCode;
	char ChangePINCodeAcception;

	cout << "Your Last PIN Code : " << CurrentClient.PINCode << "\n";
	cout << "\nEnter New PIN Code : ";
	getline(cin >> ws, NewPINCode);


	cout << "\nAre you Sure you want to change PIN Code from (" << CurrentClient.PINCode << ") To (" << NewPINCode << ") ?[N/Y]...";
	cin >> ChangePINCodeAcception;

	if (toupper(ChangePINCodeAcception) == 'Y')
	{
		ChangeClientPINCodeByAccountNumber(CurrentClient.AccountNumber, NewPINCode);
		CurrentClient.PINCode = NewPINCode;
		cout << "\nThe PIN Code Changed Successfully.\n";
	}
	else
		cout << "\nThe Request has been canceld.\n";


}


void ShowChangePINCodeScreen()
{
	DisplayHeader_ChangePINCodeScreen();
	PerformChangePINCodeOption();

}


bool TransferAmountFromClientToAnother(stClient &ClientFrom, stClient &ClientTo, int Amount)
{

	for(stClient &ClFrom : vClients)
		if(ClFrom.AccountNumber == ClientFrom.AccountNumber)
			for(stClient &ClTo : vClients)
				if (ClTo.AccountNumber == ClientTo.AccountNumber)
				{
					ClFrom.AccountBalance -= Amount;
					ClTo.AccountBalance += Amount;
						SaveClientsVectorDataToFile(ClientsFileName, vClients);
					return true;
				}

	return false;



}


void PerformTransferAmountToAnotherClient()
{

	string TransferToAccount;
	stClient ClientTranferFor;
	char Acception;

	cout << "\nEnter Account Number that you want transfer Amount for : ";
	cin >> TransferToAccount;


	if(FindClientByAccountNumber(TransferToAccount,ClientTranferFor))
	{

		int TransferAmount = ReadDepositeAmount();
		while (!(CurrentClient.AccountBalance > TransferAmount))
		{

			cout << "\nThe Amount is exceeds your balance, Enter another one :\n\n";
			TransferAmount = ReadDepositeAmount();

		}

		cout << "\nAre you sure you want to transfer (" << TransferAmount << ") From your Account,\n to Client with name (" << ClientTranferFor.ClientName
			<< ") and Account Number (" << ClientTranferFor.AccountNumber << ")?[N/Y]...";
		
		cin >> Acception;

		if(toupper(Acception) == 'Y')
		{
			
			TransferAmountFromClientToAnother(CurrentClient, ClientTranferFor, TransferAmount);
			CurrentClient.AccountBalance -= TransferAmount;

			cout << "\nThe Transfer Transaction Done Successfully.\n";
		}

		else
			cout << "\nThe request has been canceld.";

	}
	else
	{
		cout << "\nClient Not Found Do you want to enter another Client?[N/Y]...";
		cin >> Acception;

		if (toupper(Acception) == 'Y')
		{
			ShowTransferAmountScreen();
		}
		else
			cout << "\nThe request has been canceld.";
	}


}


void ShowTransferAmountScreen()
{
	system("cls");
	DisplayHeader_TransferAmountScreen();
	PerformTransferAmountToAnotherClient();

}


void Perform_ATMMenuoption(enATMSystimOptions Option)
{
	system("cls");
	switch (Option)
	{
	case enATMSystimOptions::QuickWithdraw:
		ShowQuickWithdrawScreen();
		GoBackTo_MainMenuScreen();
		
	case enATMSystimOptions::NormalWithdraw:
		ShowNormalWithdrawScreen();
		GoBackTo_MainMenuScreen();

	case enATMSystimOptions::Deposit:
		ShowDepositScreen();
		GoBackTo_MainMenuScreen();

	case enATMSystimOptions::CheckBalance:
		ShowCheckBalanceScreen();
		GoBackTo_MainMenuScreen();

	case enATMSystimOptions::ChangePINCode:
		ShowChangePINCodeScreen();
		GoBackTo_MainMenuScreen();

	case enATMSystimOptions::TransferAmount:
		ShowTransferAmountScreen();
		GoBackTo_MainMenuScreen();

	case enATMSystimOptions::Logout:
		Login();
	}

}


void ShowATM_MainMenu()
{
	system("cls");

	cout << Line(40) << "\n";
	cout << Tab(1) << "ATM Main Menu Screen\n";
	cout << Line(40) << "\n";

	cout << Tab(1) << "[1] Quick Withdraw.\n";
	cout << Tab(1) << "[2] Normal Withdraw.\n";
	cout << Tab(1) << "[3] Deposit.\n";
	cout << Tab(1) << "[4] Check Balance.\n";
	cout << Tab(1) << "[5] Change PIN Code.\n";
	cout << Tab(1) << "[6] Tranfer Amount.\n";
	cout << Tab(1) << "[7] Logout.\n";


	cout << Line(40) << "\n";

	Perform_ATMMenuoption((enATMSystimOptions)ReadATMSystimOption());
}



void Login()
{
	string AccountNumber, PINCode;

	bool LoginFaild = false;

	do
	{
		system("cls");
		DisplayHeader_LoginScreen();


			if (LoginFaild)
			{
				cout << "\nInvalid AcountNumber/Password\n";
			}

			cout << "Enter AcountNumber: ";
			cin >> AccountNumber;

			cout << "Enter PIN Cod: ";
			cin >> PINCode;


			LoginFaild = !LoadClientInfo(AccountNumber, PINCode,CurrentClient);


	} while (LoginFaild);


	ShowATM_MainMenu();

}


int main()
{

	Login();

	return 0;
}
