#include "Animal.h"
#include "Product.h"
#include <fstream>

using namespace std;
Animal::Animal(int _produceDays, double _price) : produceDays(_produceDays), basePrice(_price), currentPrice(_price)
{
	count = 0;
}

void Animal::FinishDay(int day, Product* product) const
{
	if (day % produceDays == 0)
	{
		product->AddProduct(count); // one product per animal
	}
}

void Animal::SaveData(ofstream& outSaveFile) const
{
	outSaveFile << count << " " << produceDays << " " << currentPrice << " " << basePrice << '\n';
}

void Animal::LoadData(ifstream& saveFile)
{
	saveFile >> count >> produceDays >> currentPrice >> basePrice;
}

void Animal::UpdateDailyPrice(double newPrice)
{
	currentPrice = newPrice;
}

void Animal::UpdateWeeklyPrice(double newPrice)
{
	basePrice = newPrice;
}


void Animal::AddAnimal(int amountToAdd)
{
	count += amountToAdd;
}

void Animal::RemoveAnimal(int amountToTake)
{
	count -= amountToTake;
}



std::string Chicken::GetType(bool checkSingle) const
{
	if (GetAnimalAmount() == 1 && checkSingle)
	{
		return "Chicken";
	}

	return "Chickens";
}

std::string Cow::GetType(bool checkSingle) const
{
	if (GetAnimalAmount() == 1 && checkSingle)
	{
		return "Cow";
	}

	return "Cows";
}

std::string Crocodile::GetType(bool checkSingle) const
{
	if (GetAnimalAmount() == 1 && checkSingle)
	{
		return "Crocodile";
	}

	return "Crocodiles";
}