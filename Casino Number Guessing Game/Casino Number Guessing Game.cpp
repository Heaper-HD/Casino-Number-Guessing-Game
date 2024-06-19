#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <string>

double playerMoney = 100;
double bid;

int numberRoll()
{
	static std::random_device rng;
	std::uniform_int_distribution<int> dist(1, 10);
	int roll = dist(rng);
	return roll;
}

bool checkForRolled(int playerGuess, int systemRoll)
{
	bool rightGuess = false;
	if (playerGuess == systemRoll)
	{
		rightGuess = true;
	}
	return rightGuess;
}

void printGUI()
{
	std::cout << "Money: " << playerMoney << std::endl;
	std::cout << "Current bid: " << bid << std::endl;
	std::cout << "\nInput: ";
}

void printHelp()
{
	system("cls");
	std::cout << "Commands:\n";
	std::cout << "1| help ~ show commands\n";
	std::cout << "2| bid ~ choses a value to bid\n";
	std::cout << "3| roll ~ roll for number\n";
	system("pause");
}

void setBid()
{
	std::string input;
	while (bid <= 0)
	{
		system("cls");
		std::cout << "What is your current bid?\nBid: ";
		std::cin >> input;
		bool showNegativeNumberError = true;
		try
		{
			bid = std::stod(input);
		}

		catch (const std::exception&)
		{
			system("cls");
			std::cout << "That's not a valid value please use only numbers" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(3));
			showNegativeNumberError = false;
		}

		if (bid <= 0)
		{
			if (showNegativeNumberError == true)
			{
				system("cls");
				std::cout << "Please use only positive values!";
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
		showNegativeNumberError = true;
	}
	
	if (bid > playerMoney)
	{
		system("cls");
		std::cout << "Your bid cannot be more than the ammount of money you have!\nThe bid has been set to the be all your current money becouse of it!" << std::endl;
		bid = playerMoney;
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	system("cls");
}

void gameOver()
{
	playerMoney = 100;
	bid = 0;
	std::cout << "Seems like you money reached 0, that means you lose!" << std::endl;
	std::cout << "Your money has been set back to the default value of 100!" << std::endl;
	system("pause");
	system("cls");
}

void checkForGameOver()
{
	if (playerMoney <= 0)
	{
		gameOver();
	}
}

void userInput(std::string input)
{
	std::transform(input.begin(), input.end(), input.begin(), tolower);

	if (input == "help")
	{
		printHelp();
		system("cls");
	}

	else if (input == "bid")
	{
		setBid();
	}

	else if (input == "roll")
	{
		system("cls");
		if (bid <= 0)
		{
			system("cls");
			std::cout << "You haven't bid anything yet\nPlease bid something before rolling a number!" << std::endl;
			system("pause");
			setBid();
		}
		int playerNumber;
		std::cout << "Please type the number that you guess that will be chosen!" << std::endl;
		std::cout << "(It needs to be between 1 and 10)" << std::endl;
		std::cout << "Number: ";
		playerRollInput:
		std::cin >> input;
		try
		{
			playerNumber = std::stoi(input);
		}
		catch (const std::exception&)
		{
			system("cls");
			std::cout << "That's not a valid input, please use a number between 1 and 10!" << std::endl;
			std::cout << "Number: ";
			goto playerRollInput;
		}
		while (playerNumber > 10 || playerNumber < 1)
		{
			system("cls");
			std::cout << "That's not a valid range of value please write a number between 1 and 10!" << std::endl;
			std::cout << "Number: ";
			std::cin >> playerNumber;
		}
		bool playerWin = false;
		int systemRoll = 1;
		playerWin = checkForRolled(playerNumber, systemRoll);
		system("cls");
		std::cout << "System rolled for: " << systemRoll;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		system("cls");

		if (playerWin == true)
		{
			playerMoney = playerMoney + (bid * 10);
			std::cout << "Congrats you chose the right number!" << std::endl;
			std::cout << "You won: " << bid * 10 << std::endl;
			std::cout << "Your current ammount of money is: " << playerMoney;
			std::this_thread::sleep_for(std::chrono::seconds(5));
			system("cls");
		}

		else
		{
			playerMoney = playerMoney - bid;
			std::cout << "You guessed the number wrong!\nYou lost: " << bid << std::endl;
			std::cout << "Your current ammount of money is: " << playerMoney;
			std::this_thread::sleep_for(std::chrono::seconds(4));
			system("cls");
		}
		bid = 0;
		checkForGameOver();
	}

	else if (input == "exit")
	{
		exit(0);
	}

	else
	{
		system("cls");
		std::cout << "That's not a valid command!\nType 'help' to see avaliable commands\n";
		std::this_thread::sleep_for(std::chrono::seconds(4));
		system("cls");
	}
}

int main()
{
	std::string input;
	std::cout << "Welcome to the cassino number guessing game!\nType help to see what commands you can use\nUse 'exit' as soon as you want to leave the game!\nGood luck!\n";
	system("pause");
	system("cls");
	while (true)
	{
		printGUI();
		std::cin >> input;
		std::cout << std::endl;
		userInput(input);
	}
}