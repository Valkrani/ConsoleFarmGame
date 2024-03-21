#pragma once

#include <fstream>

class Farmer;
// class to hold all the information related to prices and update them from the corresponding functions
class Prices
{
	double inflationRate;

	double baseInflationRate = 1.00;

	double NegativeProtection(double priceToCheck);

public:
	Prices();

	// Saves all the current and base prices
	void SaveData(std::ofstream& outSaveFile) const;

	// Loads all the current and base prices
	void LoadData(std::ifstream& saveFile);

	// Updates the current prices daily around the base price with a randomly generated number with a bit of inflation (called from WorldSystem)
	// Uses NegativeProtection() to make sure the prices dont go into the negatives
	void DailyPriceChange(Farmer* player);

	// Updates the base prices weekly based on a randomly generated number with a bit of inflation (called from WorldSystem)
	// Uses NegativeProtection() to make sure the prices dont go into the negatives
	void WeeklyPriceChange(Farmer* player);
};