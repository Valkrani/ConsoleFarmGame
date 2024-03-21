#pragma once

#include "Product.h"
#include <string>

class Animal
{
	int count;

	double currentPrice;
	double basePrice;

	int produceDays;

public:
	Animal(int _produceDays, double _price);

	void FinishDay(int day, Product* product) const;

	// Saves all the data related to the animal
	void SaveData(std::ofstream& outSaveFile) const;
	// Loads all the data related to the animal
	void LoadData(std::ifstream& saveFile);

	int GetAnimalAmount() const { return count; }
	double GetPrice() const { return currentPrice; }
	double GetBasePrice() const { return basePrice; }

	void SetPrice(double newPrice) { currentPrice = newPrice; }

	void UpdateDailyPrice(double newPrice);
	void UpdateWeeklyPrice(double newPrice);

	virtual bool IsType(std::string compare) const { return "Animal" == compare; }

	virtual std::string GetType(bool checkSingle = true) const { return "Animal"; }

	void AddAnimal(int amountToAdd);
	void RemoveAnimal(int amountToTake);
};

class Chicken : public Animal
{
public:
	Chicken(int _produceDays, double _price) : Animal(_produceDays, _price) {}

	bool IsType(std::string compare) const override { return "Chicken" == compare; }

	std::string GetType(bool checkSingle) const override;
};

class Cow : public Animal
{
public:
	Cow(int _produceDays, double _price) : Animal(_produceDays, _price) {}

	bool IsType(std::string compare) const override { return "Cow" == compare; }

	std::string GetType(bool checkSingle) const override;
};

class Sheep : public Animal
{
public:
	Sheep(int _produceDays, double _price) : Animal(_produceDays, _price) {}

	bool IsType(std::string compare) const override { return "Sheep" == compare; }

	std::string GetType(bool checkSingle) const override { return "Sheep"; }
};

class Crocodile : public Animal
{
public:
	Crocodile(int _produceDays, double _price) : Animal(_produceDays, _price) {}

	bool IsType(std::string compare) const override { return "Crocodile" == compare; }

	std::string GetType(bool checkSingle) const override;
};