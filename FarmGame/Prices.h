#pragma once

#include <fstream>

// class to hold all the information related to prices and update them from the corresponding functions
class Prices
{
	// current prices which fluctuate around the base prices daily
	// current prices change on a daily basis (called from WorldSystem)

	double inflationRate;

	double eggsPrice;
	double milkLiterPrice;
	double woolPrice;
	double crocSkinPrice;


	double chickenPrice;
	double cowPrice;
	double sheepPrice;
	double crocodilePrice;


	// base prices on which the above prices will fluctuate around daily
	// base prices change on a weekly basis (called from WorldSystem)
	// base prices should not be used

	double baseInflationRate = 1.00;

	double baseEggsPrice	   = 4.40;
	double baseMilkLiterPrice  = 7.50;
	double baseWoolPrice	   = 13.23;
	double baseCrocSkinPrice   = 34.60;


	double baseChickenPrice	   = 12.50  * baseInflationRate;
	double baseCowPrice		   = 23.30  * baseInflationRate;
	double baseSheepPrice	   = 56.70  * baseInflationRate;
	double baseCrocodilePrice  = 120.70 * baseInflationRate;

	double NegativeProtection(double priceToCheck);

public:
	Prices();

	// Saves all the current and base prices
	void SaveData(std::ofstream& outSaveFile) const;

	// Loads all the current and base prices
	void LoadData(std::ifstream& saveFile);

	// Updates the current prices daily around the base price with a randomly generated number with a bit of inflation (called from WorldSystem)
	// Uses NegativeProtection() to make sure the prices dont go into the negatives
	void DailyPriceChange();

	// Updates the base prices weekly based on a randomly generated number with a bit of inflation (called from WorldSystem)
	// Uses NegativeProtection() to make sure the prices dont go into the negatives
	void WeeklyPriceChange();

	double GetEggsPrice() const { return eggsPrice; }
	double GetMilkPrice() const { return milkLiterPrice; }
	double GetWoolPrice() const { return woolPrice; }
	double GetCrocSkinPrice() const { return crocSkinPrice; }

	double GetChickenPrice() const { return chickenPrice; }
	double GetCowPrice() const { return cowPrice; }
	double GetSheepPrice() const { return sheepPrice; }
	double GetCrocodilePrice() const { return crocodilePrice; }
};