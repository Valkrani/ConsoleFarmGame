#include "Animal.h"
#include <string>
#include <fstream>

using namespace std;
Animal::Animal(AnimalTypes _animalType, int _produceDays) : animalType(_animalType), produceDays(_produceDays)
{
	this->productAmount = 0;
	this->animalCount = 0;
}

void Animal::FinishDay(int day)
{
	if (day % produceDays == 0)
	{
		productAmount += 1 * animalCount;
	}
}

void Animal::SaveData(ofstream& outSaveFile) const
{
	outSaveFile << static_cast<int>(animalType) << " " << productAmount << " " << animalCount << " " << produceDays << '\n';
}

void Animal::LoadData(ifstream& saveFile)
{
	int type;
	saveFile >> type >> productAmount >> animalCount >> produceDays;
	animalType = static_cast<AnimalTypes>(type);
}



void Animal::AddAnimal(int amountToAdd)
{
	this->animalCount += amountToAdd;
}

void Animal::RemoveAnimal(int amountToTake)
{
	this->animalCount -= amountToTake;
}


void Animal::RemoveProducts(int amountToRemove)
{
	if (this->productAmount < amountToRemove)
	{
		return;
	}

	this->productAmount -= amountToRemove;
}

string Animal::GetAnimalTypeToString() const
{
	switch (this->animalType)
	{
	case AnimalTypes::Chicken:
		return "Chicken(s)";
		break;

	case AnimalTypes::Cow:
		return "Cow(s)";
		break;

	case AnimalTypes::Sheep:
		return "Sheep";

		break;

	case AnimalTypes::Crocodile:
		return "Crocodile(s)";
		break;
	default:
		break;
	}

	return "error";
}

std::string Animal::GetProductTypeToString() const
{
	switch (this->animalType)
	{
	case AnimalTypes::Chicken:
		return "Egg(s)";
		break;

	case AnimalTypes::Cow:
		return "Milk Liter(s)";
		break;

	case AnimalTypes::Sheep:
		return "Wool";
		break;

	case AnimalTypes::Crocodile:
		return "Crocodile Skin(s)";
		break;

	default:
		break;
	}

	return "error";
}
