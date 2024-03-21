#include "RenderEngine.h"

#include <windows.h> // used for Sleep() and system("CLS")

#include <iostream>
#include <vector>
#include "Prices.h"

#include "StringToLower.h"

using namespace std;

RenderingEngine::RenderingEngine() {}

void RenderingEngine::ClearConsole() const
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

void RenderingEngine::StartupScreen(bool& outLoadingSave) const
{
	ClearConsole();
	cout << "*------------------------------------*" << '\n';
	cout << "|                                    |" << '\n';
	cout << "|      * Welcome to FarmGame *       |" << '\n';    // WIP title (hopefully)
	cout << "|                                    |" << '\n';
	cout << "*------------------------------------*" << '\n';
	cout << '\n';

	cout << "New Game / Load Game   (new/load)" << '\n';

	while (true)
	{
		string input;
		getline(cin, input);

		StringToLower(input);
		
		if (input == "new" || input == "new game")
		{
			cout << "Starting new game..." << '\n';
			Sleep(2000);
			ClearConsole();
			outLoadingSave = false;
			return;
		}
		else if (input == "load" || input == "load game")
		{
			cout << "Loading game..." << '\n';
			Sleep(2000);
			ClearConsole();
			outLoadingSave = true;
			return;
		}
		else
		{
			cout << "Unrecognized command" << '\n';
		}
	}
}

void RenderingEngine::SuccessfulPurchaseMessage(string purchaseType, int amount, Farmer* player) const
{
	cout << "You have successfully purchased " << amount << " " << purchaseType << "." << '\n';
	cout << "Your new balance is: " << player->GetMoneyAmount() << "." << '\n';
}
void RenderingEngine::SuccessfulSellMessage(string sellType, int amount, Farmer* player) const
{
	cout << "You have successfully sold " << amount << " " << sellType << "." << '\n';
	cout << "Your new balance is: " << player->GetMoneyAmount() << "." << '\n';
}

void RenderingEngine::FailedPurchaseMessage(string purchaseType, int amount, double moneyNeeded) const
{
	cout << "Unable to purchase " << amount << " " << purchaseType << "." << '\n';
	cout << "You need " << moneyNeeded << " money more." << '\n';
}
void RenderingEngine::FailedSellMessage(string sellType, int amount, int productAmount, std::string productType) const
{
	cout << "Unable to sell " << amount << " " << productType << "." << '\n';
	cout << "Your " << sellType << " have " << productAmount << " " << productType << "." << '\n';
}

void RenderingEngine::DisplayDailyOptions(int currentDay, Farmer* player) const
{
	ClearConsole();
	cout << "Today is day: " << currentDay << '\n';
	player->PrintFarmInfo();
	cout << '\n';
	cout << "What would you like to do today:" << '\n';
	cout << "1. Sell Products" << '\n';
	cout << "2. Buy Animals" << '\n';
	cout << "3. Sleep" << '\n';
	cout << "4. Save and Quit" << '\n';
}

void RenderingEngine::SellProductScreen(Farmer* player) const
{
	std::vector<std::pair<double, double>> currentPrices = player->GetCurrentPrices();
	ClearConsole();
	cout << "Today's prices are: " << '\n';
	cout << "Eggs: " << currentPrices[0].second << '\n';
	cout << "Milk per liter: " << currentPrices[1].second << '\n';
	cout << "Wool: " << currentPrices[2].second << '\n';
	cout << "Crocodile Skin: " << currentPrices[3].second << '\n';
	cout << '\n';
	cout << "What would you like to sell: " << '\n';

	player->PrintProducts();
}
void RenderingEngine::BuyAnimalsScreen(Farmer* player) const
{
	std::vector<std::pair<double, double>> currentPrices = player->GetCurrentPrices();
	ClearConsole();
	cout << "Your moneys: " << player->GetMoneyAmount()<< '\n';
	cout << "What would you like to buy:" << '\n';
	cout << "1. Chicken: " << currentPrices[0].first << " per chicken" << '\n';
	cout << "2. Cow: " << currentPrices[1].first << " per cow" << '\n';
	cout << "3. Sheep: " << currentPrices[2].first << " per sheep" << '\n';
	cout << "4. Crocodile: " << currentPrices[3].first << " per crocodile" << '\n';
	cout << "5. Return" << '\n';
}

void RenderingEngine::DayEndScreen() const
{
	ClearConsole();
	for (int i = 0; i < 1; i++)
	{
		ClearConsole();
		cout << "Sleeping";
		for (int i = 0; i < 3; i++)
		{
			cout << ".";
			Sleep(1000);
		}
	}
	cout << '\n';
}