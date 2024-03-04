#pragma once

/*
 TO LOOK INTO:

	WITHOUT THOSE INCLUDE IT DOESNT COMPILE

*/
#include "RenderEngine.h"
#include "Farmer.h"

// Class used to handle the days, random events (TODO), user input and console output
class WorldSystem
{
	int days;

public:
	WorldSystem();

	// Moves the day forward, updating the price, calling the rendering engine to display the user's choices
	// Also handles the user input, and calls the corresponding commands for the user's choice
	void ProccessDay(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices, bool& isUserQuiting) const;

	// For now just saves the day int...
	void SaveData(std::ofstream& outSaveFile) const;
	// For now just loads the day int...
	void LoadData(std::ifstream& saveFile);

	void FinishDay(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices);

	// Handles the user input for purchasing an animal
	void PurchaseScreen(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices) const;

	// Handles the user input for selling products
	void SellScreen(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices) const;
};