#pragma once

#include "RenderEngine.h"
#include <vector>
#include <string>
#include "Animal.h"
#include "Product.h"
#include "Prices.h"


class RenderingEngine;
// The class the user will use
class Farmer
{
	std::vector<std::pair<Animal*, Product*>> inventory;

	// The amount of money the player will have
	double money;

public:

	// Initialise the user's class for new game
	// Initialise the animals vector with all the animals which start from 0, then add 1 to the starter animal which is a chicken
	Farmer();
	~Farmer();

	// Saves the data for the user
	// Loops to call every animal's saveData function
	void SaveData(std::ofstream& outSaveFile) const;

	// Load the data for the user
	// Loops to call every animal's saveData function
	void LoadData(std::ifstream& saveFile);


	void PurchaseAnimal(std::string animalToPurchase, int animalsAmount, RenderingEngine* renderEngine);
	void SellProduct(std::string productType, int productAmount, RenderingEngine* renderEngine);

	// Loops through all the animals and calls their corresponding FinishDay()
	void FinishDay(int day);


	// Returns the amount of money the player has
	double GetMoneyAmount() const { return money; }

	void UpdateDailyPrices(std::vector<std::pair<double, double>> newPrices) const;
	void UpdateWeeklyPrices(std::vector<std::pair<double, double>> newPrices) const;
	std::vector<std::pair<double, double>> GetBasePrices() const;
	std::vector<std::pair<double, double>> GetCurrentPrices() const;

	void PrintFarmInfo() const;
	void PrintProducts() const;

	void RandomEventStealMoney(double amountToTake);
	void RandomEventWolfAttack(double percentToTake);
	void RandomEventPlague(double percentToTake);
	void RandomEventNPCrequest(std::string request, int amount, double requestPriceDiff);
	void RandomEventAnimalCapture(std::string animalType, double chancePercent);
	void RandomEventTornado(double damagePricePercentage, double percentMissingAnimals);

	void RandomEventHyperinflation();
	void RandomEventMarketCrash();

};