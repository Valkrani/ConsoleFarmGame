#pragma once

#include "EnumTypes.h"
#include <string>

class Animal
{
	AnimalTypes animalType;
	int productAmount;
	int animalCount;
	int produceDays;

public:
	Animal(AnimalTypes _animalType, int _produceDays);

	// Saves all the data related to the animal
	void SaveData(std::ofstream& outSaveFile) const;
	// Loads all the data related to the animal
	void LoadData(std::ifstream& saveFile);

	// Returns the animal type using AnimalTypes
	AnimalTypes GetAnimalType() const { return animalType; }

	// Returns the animal type in string
	std::string GetAnimalTypeToString() const;
	// Returns the product type in string using AnimalType
	std::string GetProductTypeToString() const;

	// Returns the amount of products the animal currently has
	int GetProductAmount() const { return productAmount; }

	// Returns the amount of animals
	int GetAnimalAmount() const { return animalCount; }

	void FinishDay(int day);

	void AddAnimal(int amountToAdd);
	void RemoveProducts(int amountToRemove);

};

