#include <iostream>

#include "Farmer.h"
#include "RenderEngine.h"
#include "Prices.h"
#include "WorldSystem.h"
#include "SaveGameSystem.h"


using namespace std;
int main()
{
    WorldSystem* worldSystem = new WorldSystem();
    Prices* todaysPrices = new Prices();
    Farmer* player = new Farmer();
    RenderingEngine* renderEngine = new RenderingEngine();
    SaveGameSystem* saveGameSystem = new SaveGameSystem();

    bool isPlayerLoadingSave;
    renderEngine->StartupScreen(isPlayerLoadingSave);

    // If the user is loading a save, it loads the data, its creating fresh instances of all the classes anyways
    if (isPlayerLoadingSave)
    {
        saveGameSystem->LoadGame(player, worldSystem, todaysPrices);
    }

    bool isUserQuiting = false;
    while (true)
    {    
        worldSystem->ProccessDay(renderEngine, player, todaysPrices, isUserQuiting);
        if (isUserQuiting)
        {
            saveGameSystem->SaveGame(player, worldSystem, todaysPrices);
            break;
        }
        worldSystem->FinishDay(renderEngine, player, todaysPrices);
    }

    // future idea:
    // colors to the console text
    // https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text


    delete worldSystem;
    delete todaysPrices;
    delete renderEngine;
    delete player;
    delete saveGameSystem;
}
