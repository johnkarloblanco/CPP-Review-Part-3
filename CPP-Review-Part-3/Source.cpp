#include <iostream>

using namespace std;

//struct review
//struct students
//{
//	string name;
//	float GPA;
//};
//
//
//int main()
//{
//	students Teacher;
//	Teacher.name = "Dr. Colvin";
//	students firstPeriod[10];
//	firstPeriod[0].name = "Tom";
//	firstPeriod[0].GPA = 4.0;
//
//
//	cout << firstPeriod[0].name << endl;
//	cout << firstPeriod[0].GPA << endl;
//}


////class review
//class BankAccount
//{
//private:
//	float balance;
//
//public:
//	BankAccount();
//	void Deposit(float);
//	void WithDraw(float);
//	float getBalance();
//};
//
//BankAccount::BankAccount()
//{
//	balance = 0;
//}
//
//float BankAccount::getBalance()
//{
//	return balance;
//}
//
//void BankAccount::WithDraw(float withdrawAmount) 
//{
//	balance = balance - withdrawAmount;
//}
//
//void BankAccount::Deposit(float depositAmount)
//{
//	balance = balance + depositAmount;
//}
//
//int main()
//{
//	BankAccount checking;
//	BankAccount savings;
//	cout << "Checking balance is: " << checking.getBalance() << endl;
//	cout << "Savings balance is: " << savings.getBalance() << endl;
//
//	checking.Deposit(100);
//	savings.Deposit(500);
//
//	cout << "Checking balance is: " << checking.getBalance() << endl;
//	cout << "Savings balance is: " << savings.getBalance() << endl;
//
//	checking.WithDraw(50);
//	savings.WithDraw(250);
//
//	cout << "Checking balance is: " << checking.getBalance() << endl;
//	cout << "Savings balance is: " << savings.getBalance() << endl;
//}

//pointers review
//int main()
//{
//	int v1 = 0;
//	int* p1;
//	p1 = &v1;
//	*p1 = 42;
//	
//	cout << "the value of v1 is: " << v1;
//}


////Linked list review
//#include <iostream>
//using namespace std;
//struct Node
//{
//	int data;
//	Node *link;
//};
//
//typedef Node* nodePtr;
//
//void insert(nodePtr& head, int data);
//
//int main()
//{
//	nodePtr head;
//	head = new Node;
//	head->data = 20;
//	head->link = NULL;
//
//	insert(head, 30);
//	nodePtr tmp;
//	tmp = head;
//
//	while (tmp != NULL)
//	{
//		cout << tmp->data << endl;
//		tmp = tmp->link;
//	}
//	return 0;
//}
//
//void insert(nodePtr& head, int data)
//{
//	nodePtr tempPtr;
//	tempPtr = new Node;
//	tempPtr->data = data;
//	tempPtr->link = head;
//	head = tempPtr;
//}

#include <iostream> 
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;


struct player
{
	string name;
	int numWins;
};


string FindPlayerName(player[], bool playerTurn);
int askMove(bool player1Turn, int chipsInPile, player[]);
void getUserNames(player[]);
void addWin(player[], bool);

const float MAX_TURN = .5;
const int MAX_CHIPS = 100;

int main()
{
	bool player1Turn = true;

	bool gameOver = false;
	int moveCounter = 0;
	int chipsInPile = 0;
	int chipsTaken = 0;

	char userChoice;
	player Players[2];


	ofstream outFile;
	outFile.open("Winners.txt", ios::app);


	srand(time(0));

	//ask the player names
	getUserNames(Players);


	//start the game. create random number of chips in the pile
	do
	{
		chipsInPile = (rand() % MAX_CHIPS) + 1;

		cout << "This round will start with " << chipsInPile << " chips in the pile\n";
		gameOver = false;
		moveCounter = 0;
		while (gameOver == false)
		{
			chipsTaken = askMove(player1Turn, chipsInPile, Players);
			chipsInPile = chipsInPile - chipsTaken;
			cout << "There are " << chipsInPile << " left in the pile\n";
			player1Turn = !player1Turn;
			moveCounter++;
			if (chipsInPile == 0)
			{
				gameOver = true;
				cout << FindPlayerName(Players, player1Turn) << ", congratulations you won\n";
				outFile << FindPlayerName(Players, player1Turn) << " won in " << moveCounter << " moves";
				addWin(Players, player1Turn);
			}
		}
		cout << "Do you wish to play again? (Y/N)\n";
		cin >> userChoice;
		userChoice = toupper(userChoice);

	} while (userChoice == 'Y');
	cout << Players[0].name << " had " << Players[0].numWins << " total wins this round " << endl;
	cout << Players[1].name << " had " << Players[1].numWins << " total wins this round " << endl;
	outFile.close();
	return 0;
}


void getUserNames(player Players[])
{
	cout << "Player 1, please enter your name: ";
	cin >> Players[0].name;
	cout << "\nThanks and good luck!" << endl;
	cout << "Player 2, please enter your name \n ";
	cout << "(If you wish to play against the computer, enter AI): ";
	cin >> Players[1].name;
	cout << "\nThanks and good luck! \n";
	Players[0].numWins = 0;
	Players[1].numWins = 0;
}


string FindPlayerName(player Players[], bool playerTurn)
{
	if (playerTurn == true)
		return Players[0].name;
	else
		return Players[1].name;
}


int askMove(bool player1Turn, int chipsInPile, player Players[])
{
	int chipsTaken;
	int maxPerTurn = MAX_TURN * chipsInPile;
	do
	{
		cout << FindPlayerName(Players, player1Turn) << " How many chips would  you like?\n";

		cout << "You can take up to ";
		if ((maxPerTurn) == 0)
		{
			cout << " 1\n";
		}
		else
		{
			cout << maxPerTurn << endl;
		}
		if (FindPlayerName(Players, player1Turn) == "AI")
		{
			if (maxPerTurn == 0)
			{
				chipsTaken = 1;
			}
			else
			{
				chipsTaken = (rand() % maxPerTurn) + 1;
			}
		}
		else
		{
			cin >> chipsTaken;
		}
	} while ((chipsTaken > maxPerTurn) && (chipsInPile > 1));
	return chipsTaken;
}


void addWin(player Players[], bool player1Turn)
{
	if (player1Turn)
	{
		Players[0].numWins++;
	}
	else
	{
		Players[1].numWins++;
	}
}
