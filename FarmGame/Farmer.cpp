#include "Farmer.h"
#include "EnumTypes.h"
#include "Prices.h"

#include <iostream>
#include <fstream>

using namespace std;
Farmer::Farmer()
{
	inventory.push_back(make_pair(new Chicken(1, 12.50), new Eggs(4.40)));
	inventory[0].first->AddAnimal(1);
	inventory.push_back(make_pair(new Cow(3, 23.30), new Milk(7.50)));
	inventory.push_back(make_pair(new Sheep(3, 56.70), new Wool(13.23)));
	inventory.push_back(make_pair(new Crocodile(5, 120.70), new CrocodileSkin(34.60)));

	money = 0;
}

Farmer::~Farmer()
{
	for (int i = 0; i < inventory.size(); i++)
	{
		delete inventory[i].first;
		delete inventory[i].second;
	}
}

void Farmer::SaveData(ofstream& outSaveFile) const
{
	outSaveFile << money << '\n';
	for (pair<Animal*, Product*> curPair : inventory)
	{
		curPair.first->SaveData(outSaveFile);
		curPair.second->SaveData(outSaveFile);
	}
}

void Farmer::LoadData(ifstream& saveFile)
{
	saveFile >> money;
	for (pair<Animal*, Product*> curPair : inventory)
	{
		curPair.first->LoadData(saveFile);
		curPair.second->LoadData(saveFile);
	}
}

void Farmer::FinishDay(int day)
{
	for (pair<Animal*, Product*> curPair : inventory)
	{
		curPair.first->FinishDay(day, curPair.second);
	}
}


void Farmer::PurchaseAnimal(std::string animalToPurchase, int animalsAmount, RenderingEngine* renderEngine)
{

	//  By default its false, but changes to true when the player has enough money to purchase the desired animal
	bool bSuccessfulPurchase = false;

	// Stores the amount of money needed incase the player doesn't have enough
	double moneyNeeded = 0;

	// Iterate through the inventory and check if it has found the querie
	// Calculate the sum needed and check if the user has enough
	for (pair<Animal*, Product*> curPair : inventory)
	{
		if (curPair.first->IsType(animalToPurchase))
		{
			double neededSum = curPair.first->GetPrice() * animalsAmount;
			if (money >= neededSum)
			{
				money -= neededSum;
				curPair.first->AddAnimal(animalsAmount);
				renderEngine->SuccessfulPurchaseMessage(curPair.first->GetType(false), animalsAmount, this);
			}
			else
			{
				moneyNeeded = neededSum - money;
				renderEngine->FailedPurchaseMessage(curPair.first->GetType(false), animalsAmount, moneyNeeded);
			}

			break;
		}
	}
}

void Farmer::SellProduct(std::string productType, int productAmount, RenderingEngine* renderEngine)
{

	// Iterate through the inventory and check if it has found the querie
	// Check if the user has enough of the product in question
	for (pair<Animal*, Product*> curPair : inventory)
	{
		if (curPair.second->IsType(productType))
		{
			if (curPair.second->GetProductAmount() >= productAmount)
			{
				curPair.second->RemoveProduct(productAmount);
				money += curPair.second->GetPrice() * productAmount;
				renderEngine->SuccessfulSellMessage(curPair.second->GetType(false), productAmount, this);
				return;
			}
			else
			{
				renderEngine->FailedSellMessage(curPair.second->GetType(false), productAmount, curPair.second->GetProductAmount(), curPair.second->GetType());
				return;
			}
		}
	}
}

void Farmer::UpdateDailyPrices(std::vector<pair<double, double>> newPrices) const
{
	if (inventory.size() != newPrices.size())
	{
		return;
	}

	for (int i = 0; i < inventory.size(); i++)
	{
		inventory[i].first->UpdateDailyPrice(newPrices[i].first);
		inventory[i].second->UpdateDailyPrice(newPrices[i].second);
	}
}

void Farmer::UpdateWeeklyPrices(std::vector<pair<double, double>> newPrices) const
{
	if (inventory.size() != newPrices.size())
	{
		return;
	}

	for (int i = 0; i < inventory.size(); i++)
	{
		inventory[i].first->UpdateWeeklyPrice(newPrices[i].first);
		inventory[i].second->UpdateWeeklyPrice(newPrices[i].second);
	}
}

std::vector<std::pair<double, double>> Farmer::GetBasePrices() const
{
	std::vector<std::pair<double, double>> output;

	for (pair<Animal*, Product*> curPair : inventory)
	{
		output.push_back(make_pair(curPair.first->GetBasePrice(), curPair.second->GetBasePrice()));
	}

	return output;
}

std::vector<std::pair<double, double>> Farmer::GetCurrentPrices() const
{
	std::vector<std::pair<double, double>> output;

	for (pair<Animal*, Product*> curPair : inventory)
	{
		output.push_back(make_pair(curPair.first->GetPrice(), curPair.second->GetPrice()));
	}

	return output;
}

void Farmer::PrintFarmInfo() const
{
	cout << "Current animals:" << '\n';
	for (pair<Animal*, Product*> curPair : inventory)
	{
		cout << curPair.first->GetAnimalAmount() << " - " << curPair.first->GetType() << '\n';
	}

	cout << '\n';
	cout << "Current products:" << '\n';

	for (pair<Animal*, Product*> curPair : inventory)
	{
		cout << curPair.second->GetProductAmount() << " - " << curPair.second->GetType() << '\n';
	}

	cout << '\n';

	cout << "Your moneys: " << this->money << '\n';
}

void Farmer::PrintProducts() const
{
	int counter = 1;
	for (pair<Animal*, Product*> curPair : inventory)
	{
		cout << counter << ". Amount of " << curPair.second->GetType() << " - " << curPair.second->GetProductAmount() << '\n';
		counter++;
	}

	cout << counter << ". Return." << '\n';

}



void Farmer::RandomEventStealMoney(double amountToTake)
{
	if (money <= 0)
	{
		cout << "You dont have any money to get robbed of." << '\n';
		return;
	}

	money -= amountToTake;
	cout << "You have lost " << amountToTake << "." << '\n';
}

void Farmer::RandomEventWolfAttack(double percentToTake)
{
	for (pair<Animal*, Product*> curPair : inventory)
	{
		if (curPair.first->IsType("Sheep"))
		{
			if (curPair.first->GetAnimalAmount() == 0)
			{
				cout << "Luckily you dont have any sheep." << '\n';
				return;
			}

			int amountToRemove = floor(curPair.first->GetAnimalAmount() * percentToTake);
			if (amountToRemove == 0)
			{
				cout << "Somehow none of the sheep got killed!" << '\n';
				return;
			}

			curPair.first->RemoveAnimal(amountToRemove);
			cout << "Your sheep have been attacked by wolves!!!" << '\n';
			cout << "You have lost " << amountToRemove << " sheep" << '\n';
		}
	}
}

void Farmer::RandomEventPlague(double percentToTake)
{
	for (pair<Animal*, Product*> curPair : inventory)
	{
		if (curPair.first->GetAnimalAmount() == 0)
		{
			cout << "You dont have any " << curPair.first->GetType(false) << "." << '\n';
			continue;
		}
		int amountToRemove = floor(curPair.first->GetAnimalAmount() * percentToTake);
		if (amountToRemove == 0)
		{
			cout << "None of the " << curPair.first->GetType(false) << " have died." << '\n';
			continue;
		}
		curPair.first->RemoveAnimal(amountToRemove);
		cout << amountToRemove << " " << curPair.first->GetType(false) << " have died." << '\n';
	}
}

void Farmer::RandomEventNPCrequest(std::string request, int amount, double requestPriceDiff)
{
	double requestPrice;

	for (pair<Animal*, Product*> curPair : inventory)
	{
		if (curPair.second->IsType(request))
		{
			requestPrice = (curPair.second->GetPrice() * requestPriceDiff) * amount;

			cout << "A villager has appeared at your farm requesting " << amount << " " << curPair.second->GetType(false) << "." << '\n';
			cout << "They offer " << requestPrice << "." << '\n';
			cout << "Do you accept their offer?" << '\n';

			while (true)
			{
				string input;
				cin >> input;

				if (input == "yes")
				{
					if (curPair.second->GetProductAmount() < amount)
					{
						cout << "You dont have enough product." << '\n';
						return;
					}

					curPair.second->RemoveProduct(amount);
					cout << "You have agreed to give them the requested product." << '\n';
					money += requestPrice;
					return;
				}
				else if (input == "no")
				{
					cout << "You have declined to give them the requested product." << '\n';
					return;
				}
				else
				{
					cout << "Invalid input" << '\n';
					continue;
				}
			}
		}
	}

	
}

void Farmer::RandomEventAnimalCapture(std::string animalType, double chancePercent)
{
	cout << "A wild animal has appeared!" << '\n';
	cout << "Will you try to catch it? (yes/no)" << '\n';

	while (true)
	{
		string input;
		cin >> input;

		if (input == "yes")
		{
			break;
		}
		else if (input == "no")
		{
			cout << "You have decided to not test your luck. Maybe next time.." << '\n';
			return;
		}
		else
		{
			cout << "Invalid input." << '\n';
			continue;
		}
	}

	if (chancePercent > 0.6)
	{
		for (pair<Animal*, Product*> curPair : inventory)
		{
			if (curPair.first->IsType(animalType))
			{
				curPair.first->AddAnimal(1);

				cout << "You have successfully caught a " << curPair.first->GetType() << "!" << '\n';
				cout << "Congrats!" << '\n';
			}
		}
	}
	else
	{
		cout << "You tried your best but the animal escaped! Maybe next time.." << '\n';
	}
}

void Farmer::RandomEventTornado(double damagePricePercentage, double percentMissingAnimals)
{
	double moneyToTake = money * damagePricePercentage;
	if (moneyToTake == 0)
	{
		cout << "A tornado has struct nearby but luckily your farm was not affected." << '\n';
		return;
	}

	money -= moneyToTake;

	cout << "A tornado has struct your farm and has caused " << moneyToTake << " money worth of damage!" << '\n';
	cout << "The money has been automatically deducted from your account." << '\n';
	RandomEventPlague(percentMissingAnimals);
}

void Farmer::RandomEventHyperinflation()
{
	for (pair<Animal*, Product*> curPair : inventory)
	{
		curPair.first->SetPrice(curPair.first->GetPrice() * 10);
	}
}

void Farmer::RandomEventMarketCrash()
{
	for (pair<Animal*, Product*> curPair : inventory)
	{
		curPair.first->SetPrice(0.0);
		curPair.second->SetPrice(0.0);
	}
}