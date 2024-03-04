#pragma once

#include "RenderEngine.h"
#include <vector>
#include <string>
#include "Animal.h"
#include "Prices.h"


const int ChickenProduceDays = 1;
const int CowProduceDays = 3;
const int SheepProduceDays = 3;
const int CrocodileProduceDays = 5;

class RenderingEngine;
// The class the user will use
class Farmer
{
	// Container of the animals with their type and how much products it has currently
	std::vector<Animal*> animals;

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

	// Using AnimalTypes enum it looks for which type it is, removes the amount of money, and then finds the type in the container to add to the counter.
	// RenderingEngine is used to inform the user if they have succeeded or not.
	void PurchaseAnimal(AnimalTypes animalToPurchase, int animalsAmount, RenderingEngine* renderEngine, Prices* currentPrices);

	// Using Product enum it looks for the corresponding price and adds the money, then looks for the AnimalTypes corresponding to the Product.
	// Product enum has the same values as AnimaTypes so it works without any issues.
	// RenderingEngine is used to inform the user if they have succeeded or not.
	void SellProduct(Product productType, int productAmount, RenderingEngine* renderEngine, Prices* currentPrices);

	// Loops through all the animals and calls their corresponding FinishDay()
	void FinishDay(int day);


	// Returns the amount of money the player has
	double GetMoneyAmount() const { return money; }

	std::vector<Animal*> GetProductsInfo() const { return animals; }

	void PrintFarmInfo() const;

};