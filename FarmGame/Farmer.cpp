#include "Farmer.h"
#include "EnumTypes.h"
#include "Prices.h"

#include <algorithm> // used for find()
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

	// First loop to check if there are enough products to sell
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
	for (Animal* animal : this->animals)
	{
		cout << animal->GetAnimalAmount() << " " << animal->GetAnimalTypeToString() << " have made: " << animal->GetProductAmount() << " " << animal->GetProductTypeToString() << "." << '\n';
	}
	cout << "Your moneys: " << this->money << "." << '\n';
}
