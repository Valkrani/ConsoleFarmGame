#pragma once

#include <fstream>
#include <string>

#include "Farmer.h"
#include "WorldSystem.h"
#include "Prices.h"

class SaveGameSystem
{
	const std::string saveGameName;

public:
	SaveGameSystem();

	// Calls all the classes' individual saveData functions
	void SaveGame(Farmer* farmer, WorldSystem* worldSystem, Prices* prices) const;

	// Calls all the classes' individual loadData functions
	void LoadGame(Farmer* farmer, WorldSystem* worldSystem, Prices* prices) const;
};