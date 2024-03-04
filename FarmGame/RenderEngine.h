#pragma once


#include <string>
#include "Farmer.h"
#include "Prices.h"


class Farmer;
// This class manages the console
class RenderingEngine
{
public:
	RenderingEngine();

	// Shows the welcomeing text and gives the user the choice to load the game or start new
	// Returns true if the user is loading a save and false if hes starting a new game
	void StartupScreen(bool& outLoadingSave) const;

	void SuccessfulPurchaseMessage(std::string purchaseType, int amount, Farmer* player) const;
	void SuccessfulSellMessage(std::string purchaseType, int amount, Farmer* player) const;

	void FailedPurchaseMessage(std::string sellType, int amount, double moneyNeeded) const;
	void FailedSellMessage(std::string sellType, int amount, int productAmount, std::string productType) const;

	void DisplayDailyOptions(int currentDay, Farmer* player) const;
	void SellProductScreen(Farmer* player, Prices* todaysPrices) const;
	void BuyAnimalsScreen(Farmer* player, Prices* todaysPrices) const;
	void DayEndScreen() const;
};