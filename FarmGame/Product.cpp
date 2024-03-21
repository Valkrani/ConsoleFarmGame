#include "Product.h"

Product::Product(double _price) : basePrice(_price), currentPrice(_price)
{
	count = 0;
}

void Product::UpdateDailyPrice(double newPrice)
{
	currentPrice = newPrice;
}

void Product::UpdateWeeklyPrice(double newPrice)
{
	basePrice = newPrice;
}


void Product::AddProduct(int amountToAdd)
{
	count += amountToAdd;
}

void Product::RemoveProduct(int amountToTake)
{
	count -= amountToTake;
}


void Product::SaveData(std::ofstream& outSaveFile) const
{
	outSaveFile << count << " " << currentPrice << " " << basePrice << '\n';
}


void Product::LoadData(std::ifstream& saveFile)
{
	saveFile >> count >> currentPrice >> basePrice;
}


std::string Eggs::GetType(bool checkSingle) const
{ 
	if (GetProductAmount() == 1 && checkSingle)
	{
		return "Egg";
	}

	return "Eggs"; 
}

std::string Milk::GetType(bool checkSingle) const
{
	if (GetProductAmount() == 1 && checkSingle)
	{
		return "Milk liter";
	}

	return "Milk liters";
}

std::string CrocodileSkin::GetType(bool checkSingle) const
{
	if (GetProductAmount() == 1 && checkSingle)
	{
		return "Crocodile skin piece";
	}

	return "Crocodile skin pieces";
}
