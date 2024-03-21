#pragma once
#include <fstream>
#include <string>

class Product
{
	int count;

	double currentPrice;
	double basePrice;

public:
	Product(double _price);

	// Saves all the data related to the animal
	void SaveData(std::ofstream& outSaveFile) const;
	// Loads all the data related to the animal
	void LoadData(std::ifstream& saveFile);


	int GetProductAmount() const { return count; }
	double GetPrice() const { return currentPrice; }
	double GetBasePrice() const { return basePrice; }

	void SetPrice(double newPrice) { currentPrice = newPrice; }

	void UpdateDailyPrice(double newPrice);
	void UpdateWeeklyPrice(double newPrice);

	virtual bool IsType(std::string compare) const { return "Product" == compare; }

	virtual std::string GetType(bool checkSingle = true) const { return "Product"; }

	void AddProduct(int amountToAdd);
	void RemoveProduct(int amountToTake);
};

class Eggs : public Product
{
public:
	Eggs(double _price) : Product(_price) {}

	bool IsType(std::string compare) const override { return "Eggs" == compare; }

	std::string GetType(bool checkSingle) const override;
};

class Milk : public Product
{
public:
	Milk(double _price) : Product(_price) {}

	bool IsType(std::string compare) const override { return "Milk" == compare; }

	std::string GetType(bool checkSingle) const override;
};

class Wool : public Product
{
public:
	Wool(double _price) : Product(_price) {}

	bool IsType(std::string compare) const override { return "Wool" == compare; }

	std::string GetType(bool checkSingle) const override { return "Wool"; }
};

class CrocodileSkin : public Product
{
public:
	CrocodileSkin(double _price) : Product(_price) {}

	bool IsType(std::string compare) const override { return "Crocodile skin" == compare; }

	std::string GetType(bool checkSingle) const override;
};