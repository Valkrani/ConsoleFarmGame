#pragma once
 
#include "RenderEngine.h"
#include "Farmer.h"

// Class used to handle the days, random events, user input and console output
class WorldSystem
{
	int days;
	// Chance for a random event to happen
	// Calculated upon a base percentage
	// Increases every day until an event happens
	double chanceForRandomEvent;

	// Each week the base value increases to spice up long time gameplay
	double basechanceForRandomEvent;

	bool bIsMarketCrash;


public:
	WorldSystem();

	// Moves the day forward, updating the price, calling the rendering engine to display the user's choices
	// Also handles the user input, and calls the corresponding commands for the user's choice
	void ProccessDay(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices, bool& isUserQuiting);

	// For now just saves the day int...
	void SaveData(std::ofstream& outSaveFile) const;
	// For now just loads the day int...
	void LoadData(std::ifstream& saveFile);

	void FinishDay(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices);

	// Handles the user input for purchasing an animal
	void PurchaseScreen(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices) const;

	// Handles the user input for selling products
	void SellScreen(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices) const;

	// Creates a random event from a number of options
	void GenerateRandomEvent(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices);
};