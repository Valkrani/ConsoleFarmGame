#include "SaveGameSystem.h"
#include <fstream>
#include <iostream>


using namespace std;

SaveGameSystem::SaveGameSystem() : saveGameName("savegame") {}

void SaveGameSystem::SaveGame(Farmer* farmer, WorldSystem* worldSystem, Prices* prices) const
{
	cout << "Saving..." << '\n';

	// Opens the file to write in it, whilst clearing the contents previously
	ofstream saveFile(saveGameName, std::ios::out | std::ios::trunc);

	if (saveFile.is_open())
	{
		farmer->SaveData(saveFile);
		worldSystem->SaveData(saveFile);
		prices->SaveData(saveFile);
		cout << "Save successful..." << '\n';
	}
	else
	{
		cout << "Save failed." << '\n';
	}
}

void SaveGameSystem::LoadGame(Farmer* farmer, WorldSystem* worldSystem, Prices* prices) const
{
	cout << "Loading save..." << '\n';

	ifstream loadFile(saveGameName);
	if (loadFile.is_open())
	{
		farmer->LoadData(loadFile);
		worldSystem->LoadData(loadFile);
		prices->LoadData(loadFile);
		cout << "Load successful..." << '\n';
		loadFile.close();
	}
	else
	{
		cout << "Load failed." << '\n';
	}
}