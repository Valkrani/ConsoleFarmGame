#include "Prices.h"
#include "Farmer.h"
#include <random> // used for random()
#include <fstream>

// Taken from stackoverflow
// Given a range, it returns a random number
template<typename T>
T random(T range_from, T range_to) {
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_real_distribution<T>    distr(range_from, range_to);
	return distr(generator);
}

Prices::Prices()
{
	this->inflationRate  = this->baseInflationRate;
}


// This looks retarded lmao but it works

void Prices::SaveData(std::ofstream& outSaveFile) const
{
	outSaveFile << inflationRate << " " << baseInflationRate << '\n';
}

void Prices::LoadData(std::ifstream& saveFile)
{
	saveFile >> inflationRate >> baseInflationRate;
}

// Gets all the current base prices and iterates through a new list creating new prices
void Prices::DailyPriceChange(Farmer* player)
{
	inflationRate	 = NegativeProtection(baseInflationRate + random(-0.2, 0.20));

	std::vector<std::pair<double, double>> inventory = player->GetBasePrices();
	std::vector<std::pair<double, double>> newPrices;
	for (std::pair<double, double> curPair : inventory)
	{
		double newAnimalPrice = NegativeProtection((curPair.first + random(-2.00, 2.00)) * inflationRate);
		double newProductPrice = NegativeProtection(curPair.second + random(-2.00, 2.00));

		newPrices.push_back(std::make_pair(newAnimalPrice, newProductPrice));
	}

	player->UpdateDailyPrices(newPrices);
}

double Prices::NegativeProtection(double priceToCheck)
{
	if (priceToCheck < 0.00)
	{
		return 0.00;
	}
	return priceToCheck;
}

// Every week the base price changes 
void Prices::WeeklyPriceChange(Farmer* player)
{
	this->baseInflationRate  = NegativeProtection(this->baseInflationRate + random(-0.2, 0.20));

	std::vector<std::pair<double, double>> inventory = player->GetBasePrices();
	std::vector<std::pair<double, double>> newPrices;
	for (std::pair<double, double> curPair : inventory)
	{
		double newAnimalPrice = NegativeProtection((curPair.first + random(-2.00, 2.00)) * inflationRate);
		double newProductPrice = NegativeProtection(curPair.second + random(-2.00, 2.00));

		newPrices.push_back(std::make_pair(newAnimalPrice, newProductPrice));
	}

	player->UpdateWeeklyPrices(newPrices);
}