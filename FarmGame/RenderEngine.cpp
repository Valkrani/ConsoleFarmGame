#include "RenderEngine.h"

#include <windows.h> // used for Sleep()

#include <iostream>
#include <vector>
#include "Prices.h"

using namespace std;

RenderingEngine::RenderingEngine() {}

void RenderingEngine::StartupScreen(bool& outLoadingSave) const
{
	system("CLS");
	cout << "*------------------------------------*" << '\n';
	cout << "|                                    |" << '\n';
	cout << "|      * Welcome to FarmGame *       |" << '\n';    // WIP title (hopefully)
	cout << "|                                    |" << '\n';
	cout << "*------------------------------------*" << '\n';
	cout << "WARNING: There is no autosave, make sure to quit using the Quit option at the start of each day!!!" << '\n';
	cout << '\n';

	cout << "New Game / Load Game   (new/load)" << '\n';

	while (true)
	{
		string input;
		cin >> input;

		if (input == "new")
		{
			cout << "Starting new game..." << '\n';
			Sleep(2000);
			system("CLS");
			outLoadingSave = false;
			return;
		}
		else if (input == "load")
		{
			cout << "Loading game..." << '\n';
			Sleep(2000);
			system("CLS");
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
	system("CLS");
	cout << "Today is day: " << currentDay << "." << '\n';
	cout << "Current farm stats:" << '\n';
	player->PrintFarmInfo();
	cout << '\n';
	cout << "What would you like to do today:" << '\n';
	cout << "1. Sell Products" << '\n';
	cout << "2. Buy Animal(s)" << '\n';
	cout << "3. Sleep" << '\n';
	cout << "4. Save and Quit" << '\n';
}

void RenderingEngine::SellProductScreen(Farmer* player, Prices* todaysPrices) const
{
	system("CLS");
	cout << "Today's prices are: " << '\n';
	cout << "Eggs: " << todaysPrices->GetEggsPrice() << '\n';
	cout << "Milk per liter: " << todaysPrices->GetMilkPrice() << '\n';
	cout << "Wool: " << todaysPrices->GetWoolPrice() << '\n';
	cout << "Crocodile Skin: " << todaysPrices->GetCrocSkinPrice() << '\n';
	cout << '\n';
	cout << "What would you like to sell: " << '\n';

	vector<Animal*> animals = player->GetProductsInfo();
	for (int i = 0; i < animals.size(); i++)
	{
		cout << i + 1 << ". Amount of " << animals[i]->GetProductTypeToString() << ": " << animals[i]->GetProductAmount() << '\n';
	}
	
	cout << animals.size() + 1 <<". Return." << '\n';
}
void RenderingEngine::BuyAnimalsScreen(Farmer* player, Prices* todaysPrices) const
{
	system("CLS");
	cout << "Your moneys: " << player->GetMoneyAmount() << "." << '\n';
	cout << "What would you like to buy:" << '\n';
	cout << "1. Chicken: " << todaysPrices->GetChickenPrice() << " per chicken." << '\n';
	cout << "2. Cow: " << todaysPrices->GetCowPrice() << " per cow." << '\n';
	cout << "3. Sheep: " << todaysPrices->GetSheepPrice() << " per sheep." << '\n';
	cout << "4. Crocodile: " << todaysPrices->GetCrocodilePrice() << " per crocodile." << '\n';
	cout << "5. Return." << '\n';
}

void RenderingEngine::DayEndScreen() const
{
	system("CLS");
	for (int i = 0; i < 2; i++)
	{
		system("CLS");
		cout << "Sleeping";
		for (int i = 0; i < 3; i++)
		{
			cout << ".";
			Sleep(1000);
		}
	}
}