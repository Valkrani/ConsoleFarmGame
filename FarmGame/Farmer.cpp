#include "Farmer.h"
#include "EnumTypes.h"
#include "Prices.h"

#include <iostream>
#include <fstream>

using namespace std;
Farmer::Farmer()
{
	this->animals.push_back(new Animal(AnimalTypes::Chicken, ChickenProduceDays));
	this->animals[0]->AddAnimal(1);
	this->animals.push_back(new Animal(AnimalTypes::Cow, CowProduceDays));
	this->animals.push_back(new Animal(AnimalTypes::Sheep, SheepProduceDays));
	this->animals.push_back(new Animal(AnimalTypes::Crocodile, CrocodileProduceDays));
	this->money = 0;
}

void Farmer::SaveData(ofstream& outSaveFile) const
{
	outSaveFile << money << '\n';
	for (Animal* animal : animals)
	{
		animal->SaveData(outSaveFile);
	}
}

void Farmer::LoadData(ifstream& saveFile)
{
	saveFile >> money;
	for (Animal* animal : animals)
	{
		animal->LoadData(saveFile);
	}
}

void Farmer::FinishDay(int day)
{
	for (Animal* animal : animals)
	{
		animal->FinishDay(day);
	}
}


Farmer::~Farmer()
{
	for (int i = 0; i < animals.size(); i++)
	{
		delete animals[i];
	}
}

void Farmer::PurchaseAnimal(AnimalTypes animalToPurchase, int animalsAmount, RenderingEngine* renderEngine, Prices* currentPrices)
{

	//  By default its false, but changes to true when the player has enough money to purchase the desired animal
	bool bSuccessfulPurchase = false;

	// Stores the amount of money needed incase the player doesn't have enough
	double moneyNeeded = 0;

	switch (animalToPurchase)
	{
	case AnimalTypes::Chicken:
		if (this->money >= currentPrices->GetChickenPrice() * animalsAmount)
		{
			this->money -= currentPrices->GetChickenPrice() * animalsAmount;
			bSuccessfulPurchase = true;
		}
		else
		{
			moneyNeeded = currentPrices->GetChickenPrice() * animalsAmount - this->money;
		}
		break;

	case AnimalTypes::Cow:
		if (this->money >= currentPrices->GetCowPrice() * animalsAmount)
		{
			this->money -= currentPrices->GetCowPrice() * animalsAmount;
			bSuccessfulPurchase = true;
		}
		else
		{
			moneyNeeded = currentPrices->GetCowPrice() * animalsAmount - this->money;
		}
		break;

	case AnimalTypes::Sheep:
		if (this->money >= currentPrices->GetSheepPrice() * animalsAmount)
		{
			this->money -= currentPrices->GetSheepPrice() * animalsAmount;
			bSuccessfulPurchase = true;
		}
		else
		{
			moneyNeeded = currentPrices->GetSheepPrice() * animalsAmount - this->money;
		}
		break;

	case AnimalTypes::Crocodile:
		if (this->money >= currentPrices->GetCrocodilePrice() * animalsAmount)
		{
			this->money -= currentPrices->GetCrocodilePrice() * animalsAmount;
			bSuccessfulPurchase = true;
		}
		else
		{
			moneyNeeded = currentPrices->GetCrocodilePrice() * animalsAmount - this->money;
		}
		break;

	default:
		break;
	}

	// Loop to find the desired animal and check if the player had enough money to purchase
	// then output with the correct answer
	for (Animal* animal : this->animals)
	{
		if (animal->GetAnimalType() == animalToPurchase)
		{
			if (bSuccessfulPurchase)
			{
				animal->AddAnimal(animalsAmount);
				renderEngine->SuccessfulPurchaseMessage(animal->GetAnimalTypeToString(), animalsAmount, this);
				break;
			}
			else
			{
				renderEngine->FailedPurchaseMessage(animal->GetAnimalTypeToString(), animalsAmount, moneyNeeded);
			}
		}
	}
}

void Farmer::SellProduct(Product productType, int productAmount, RenderingEngine* renderEngine, Prices* currentPrices)
{

	string animalTypeString;

	// First, loop to check if there are enough products to sell
	// If there are, remove them and continue on to get the money and prepare the animal type string
	// Else, early return with a failed message
	for (Animal* animal : this->animals)
	{
		// Because Product::Eggs is 0 and AnimalTypes::Chicken is 0, it works without any extra work
		if (animal->GetAnimalType() == productType)
		{
			if (productAmount <= animal->GetProductAmount())
			{
				animal->RemoveProducts(productAmount);
				animalTypeString = animal->GetAnimalTypeToString();
				break;
			}
			else
			{
				renderEngine->FailedSellMessage(animal->GetAnimalTypeToString(), productAmount, animal->GetProductAmount(), animal->GetProductTypeToString());
				return;
			}
		}
	}

	switch (productType)
	{
	case Product::Eggs:
		money += currentPrices->GetEggsPrice() * productAmount;
		break;

	case Product::Milk:
		money += currentPrices->GetMilkPrice() * productAmount;
		break;

	case Product::Wool:
		money += currentPrices->GetWoolPrice() * productAmount;
		break;

	case Product::CrocSkin:
		money += currentPrices->GetCrocSkinPrice() * productAmount;
		break;

	default:
		break;
	}

	renderEngine->SuccessfulSellMessage(animalTypeString, productAmount, this);
}

void Farmer::PrintFarmInfo() const
{
	cout << "Current animals:" << '\n';
	for (Animal* animal : this->animals)
	{
		cout << animal->GetAnimalAmount() << " - " << animal->GetAnimalTypeToString() << '\n';
	}

	cout << '\n';
	cout << "Current products:" << '\n';

	for (Animal* animal : this->animals)
	{
		cout << animal->GetProductAmount() << " - " << animal->GetProductTypeToString() << '\n';
	}

	cout << '\n';

	cout << "Your moneys: " << this->money << '\n';
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
	for (Animal* animal : animals)
	{
		if (animal->GetAnimalType() == AnimalTypes::Sheep)
		{
			if (animal->GetAnimalAmount() == 0)
			{
				cout << "Luckily you dont have any sheep." << '\n';
				return;
			}

			int amountToRemove = floor(animal->GetAnimalAmount() * percentToTake);
			if (amountToRemove == 0)
			{
				cout << "Somehow none of the sheep got killed!" << '\n';
				return;
			}

			animal->RemoveAnimal(amountToRemove);
			cout << "Your sheep have been attacked by wolves!!!" << '\n';
			cout << "You have lost " << amountToRemove << " sheep" << '\n';
		}
	}
}

void Farmer::RandomEventPlague(double percentToTake)
{
	for (Animal* animal : animals)
	{
		if (animal->GetAnimalAmount() == 0)
		{
			cout << "You dont have any " << animal->GetAnimalTypeToString() << "." << '\n';
			continue;
		}
		int amountToRemove = floor(animal->GetAnimalAmount() * percentToTake);
		if (amountToRemove == 0)
		{
			cout << "None of the " << animal->GetAnimalTypeToString() << " have died." << '\n';
			continue;
		}
		animal->RemoveAnimal(amountToRemove);
		cout << amountToRemove << " " << animal->GetAnimalTypeToString() << " have died." << '\n';
	}
}

void Farmer::RandomEventNPCrequest(Product request, int amount, double requestPriceDiff, Prices* todaysPrices)
{
	double requestPrice;
	string productInString;
	switch (request)
	{
	case Product::Eggs:
		requestPrice = (todaysPrices->GetEggsPrice() * requestPriceDiff) * amount;
		productInString = "Egg(s)";
		break;

	case Product::Milk:		
		requestPrice = (todaysPrices->GetMilkPrice() * requestPriceDiff) * amount;
		productInString = "Milk liter(s)";
		break;

	case Product::Wool:
		requestPrice = (todaysPrices->GetWoolPrice() * requestPriceDiff) * amount;
		productInString = "Wool";
		break;

	case Product::CrocSkin:
		requestPrice = (todaysPrices->GetCrocSkinPrice() * requestPriceDiff) * amount;
		productInString = "Crocodile skin";
		break;
	default:
		break;
	}

	cout << "A villager has appeared at your farm requesting " << amount << " " << productInString << "." << '\n';
	cout << "They offer " << requestPrice << "." << '\n';
	cout << "Do you accept their offer?" << '\n';

	while (true)
	{
		string input;
		cin >> input;

		if (input == "yes")
		{
			for (Animal* animal : this->animals)
			{
				// Because Product::Eggs is 0 and AnimalTypes::Chicken is 0, it works without any extra work
				if (animal->GetAnimalType() == request)
				{
					if (amount <= animal->GetProductAmount())
					{
						animal->RemoveProducts(amount);
						break;
					}
					else
					{
						cout << "You dont have enough product." << '\n';
						return;
					}
				}
			}

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

void Farmer::RandomEventAnimalCapture(AnimalTypes animalType, double chancePercent)
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
		for (Animal* animal : animals)
		{
			if (animal->GetAnimalType() == animalType)
			{
				animal->AddAnimal(1);

				cout << "You have successfully caught a " << animal->GetAnimalTypeToString() << "!" << '\n';
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
