#include "Prices.h"
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
	this->eggsPrice      = this->baseEggsPrice;
	this->milkLiterPrice = this->baseMilkLiterPrice;
	this->woolPrice      = this->baseWoolPrice;
	this->crocSkinPrice  = this->baseCrocSkinPrice;

	this->chickenPrice   = this->baseChickenPrice;
	this->cowPrice       = this->baseCowPrice;
	this->sheepPrice     = this->baseSheepPrice;
	this->crocodilePrice = this->baseCrocodilePrice;
}


// This looks retarded lmao but it works

void Prices::SaveData(std::ofstream& outSaveFile) const
{
	outSaveFile << inflationRate << " "
				<< eggsPrice << " "
				<< milkLiterPrice << " "
				<< woolPrice << " "
				<< crocSkinPrice << " "
				<< chickenPrice << " "
				<< cowPrice << " "
				<< sheepPrice << " "
				<< crocodilePrice << " "

				<< baseInflationRate << " "
				<< baseEggsPrice << " "
				<< baseMilkLiterPrice << " "
				<< baseWoolPrice << " "
				<< baseCrocSkinPrice << " "
				<< baseChickenPrice << " "
				<< baseCowPrice << " "
				<< baseSheepPrice << " "
				<< baseCrocodilePrice << '\n';
}

void Prices::LoadData(std::ifstream& saveFile)
{
	saveFile >> inflationRate
		>> eggsPrice
		>> milkLiterPrice
		>> woolPrice
		>> crocSkinPrice
		>> chickenPrice
		>> cowPrice
		>> sheepPrice
		>> crocodilePrice

		>> baseInflationRate
		>> baseEggsPrice
		>> baseMilkLiterPrice
		>> baseWoolPrice
		>> baseCrocSkinPrice
		>> baseChickenPrice
		>> baseCowPrice
		>> baseSheepPrice
		>> baseCrocodilePrice;
}

// Every day the price changes around the base price
void Prices::DailyPriceChange()
{
	this->inflationRate	 = NegativeProtection(this->baseInflationRate + random(-0.2, 0.20));

	this->eggsPrice		 = NegativeProtection(this->baseEggsPrice      + random(-2.00, 2.00));
	this->milkLiterPrice = NegativeProtection(this->baseMilkLiterPrice + random(-2.00, 2.00));
	this->woolPrice		 = NegativeProtection(this->baseWoolPrice      + random(-2.00, 2.00));
	this->crocSkinPrice	 = NegativeProtection(this->baseCrocSkinPrice  + random(-2.00, 2.00));


	this->chickenPrice	 = NegativeProtection((this->baseChickenPrice   + random(-2.00, 2.00)) * inflationRate);
	this->cowPrice		 = NegativeProtection((this->baseCowPrice       + random(-2.00, 2.00)) * inflationRate);
	this->sheepPrice	 = NegativeProtection((this->baseSheepPrice     + random(-2.00, 2.00)) * inflationRate);
	this->crocodilePrice = NegativeProtection((this->baseCrocodilePrice + random(-2.00, 2.00)) * inflationRate);
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
void Prices::WeeklyPriceChange()
{
	this->baseInflationRate  = NegativeProtection(this->baseInflationRate + random(-0.2, 0.20));

	this->baseEggsPrice		 = NegativeProtection(this->baseEggsPrice	   + random(-2.00, 2.00));
	this->baseMilkLiterPrice = NegativeProtection(this->baseMilkLiterPrice + random(-2.00, 2.00));
	this->baseWoolPrice		 = NegativeProtection(this->baseWoolPrice	   + random(-2.00, 2.00));
	this->baseCrocSkinPrice  = NegativeProtection(this->baseCrocSkinPrice  + random(-2.00, 2.00));


	this->baseChickenPrice	 = NegativeProtection((this->baseChickenPrice   + random(-2.00, 2.00)) * inflationRate);
	this->baseCowPrice		 = NegativeProtection((this->baseCowPrice	    + random(-2.00, 2.00)) * inflationRate);
	this->baseSheepPrice	 = NegativeProtection((this->baseSheepPrice	    + random(-2.00, 2.00)) * inflationRate);
	this->baseCrocodilePrice = NegativeProtection((this->baseCrocodilePrice + random(-2.00, 2.00)) * inflationRate);
}

void Prices::RandomEventHyperinflation()
{
	this->inflationRate  *= 10;
							  
	this->chickenPrice   *= 10;
	this->cowPrice       *= 10;
	this->sheepPrice     *=	10;
	this->crocodilePrice *= 10;
}

void Prices::RandomEventMarketCrash()
{
	this->inflationRate   = 0;

	this->eggsPrice       = 0;
	this->milkLiterPrice  = 0;
	this->woolPrice       = 0;
	this->crocSkinPrice   = 0;

	this->chickenPrice    = 0;
	this->cowPrice        = 0;
	this->sheepPrice      = 0;
	this->crocodilePrice  = 0;
}