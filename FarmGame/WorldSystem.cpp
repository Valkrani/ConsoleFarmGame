#include "WorldSystem.h"
#include "EnumTypes.h"
#include "StringToLower.h"

#include "RenderEngine.h"
#include "Farmer.h"

#include <iostream>
#include <string>
#include <fstream>
#include <random> // used for random()
#include <cstdlib>  // for system("CLS")


// Given a range, it returns a random integer
int random(int range_from, int range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>    distr(range_from, range_to);
    return distr(generator);
}

// Overload given a range, it returns a random double
double random(double range_from, double range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_real_distribution<double>    distr(range_from, range_to);
    return distr(generator);
}


using namespace std;

WorldSystem::WorldSystem() 
{
    days = 1;
    basechanceForRandomEvent = 0.1; // a base of 10%
    chanceForRandomEvent = basechanceForRandomEvent;
    bIsMarketCrash = false;
}


void WorldSystem::ProccessDay(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices, bool& isUserQuiting)
{
    if (days != 1)
    {
        todaysPrices->DailyPriceChange(player);
        if (random(0.0, 1.0) <= chanceForRandomEvent)
        {
            GenerateRandomEvent(renderEngine, player);
            chanceForRandomEvent = basechanceForRandomEvent;
        }
        else
        {
            chanceForRandomEvent += 0.05; // increases by 5% every day
        }
    }


    while (true)
    {
        renderEngine->ClearConsole();
        renderEngine->DisplayDailyOptions(days, player);

        string input;
        getline(cin, input);

        StringToLower(input);

        if (input == "1" || input == "sell products")
        {
            this->SellScreen(renderEngine, player);
        }
        else if (input == "2" || input == "buy animals")
        {
            this->PurchaseScreen(renderEngine, player);
        }
        else if (input == "3" || input == "sleep")
        {
            return;
        }
        else if (input == "4" || input == "save and quit" || input == "quit")
        {
            isUserQuiting = true;
            return;
        }
        else
        {
            cout << "Wrong command. Try again." << '\n';
        }
    }
}


void WorldSystem::SaveData(std::ofstream& outSaveFile) const
{
    outSaveFile << days << " " << basechanceForRandomEvent << " " << chanceForRandomEvent << '\n';
}


void WorldSystem::LoadData(std::ifstream& saveFile)
{
    saveFile >> days >> basechanceForRandomEvent >> chanceForRandomEvent;
}

void WorldSystem::FinishDay(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices)
{
    player->FinishDay(days);
    renderEngine->DayEndScreen();

    // Check if the week has ended
    if (days % 7 == 0)
    {
        todaysPrices->WeeklyPriceChange(player);
        basechanceForRandomEvent += 0.05;
    }
    todaysPrices->DailyPriceChange(player);

    days++;

    if (bIsMarketCrash)
    {
        bIsMarketCrash = false;
    }

}


void WorldSystem::SellScreen(RenderingEngine* renderEngine, Farmer* player) const
{
    if (bIsMarketCrash)
    {
        cout << "The market values have crashed!!!" << '\n';
        cout << "Are you sure you want to continue? (yes/no)" << '\n';
        string input;
        cin >> input;

        if (input == "yes")
        {
            cout << "Alright, but I warned you!!!" << '\n';
            cout << '\n';
        }
        else
        {
            return;
        }
    }


    renderEngine->ClearConsole();
    renderEngine->SellProductScreen(player);

    while (true)
    {
        string input;
        int amount;
        getline(cin, input);
        StringToLower(input);

        if (input == "1" || input == "2" || input == "3" || input == "4"
            || (input == "eggs") || input == "milk liters" || input == "wool" || input == "crocodile skin pieces")
        {
            while (true)
            {
                cout << "And how many?" << '\n';
                cin >> amount;
                cin.ignore();

                // for when the user enters something other than int
                if (cin.fail()) {
                    cin.clear(); // Clear the fail state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                    cout << "Invalid Input" << '\n';
                    continue;
                }

                if (amount <= 0)
                {
                    cout << "Invalid amount: " << amount << '\n';
                    continue;
                }
                break;
            }
        }

        if (input == "1" || input == "eggs")
        {
            player->SellProduct("Eggs", amount, renderEngine);
        }
        else if (input == "2" || input == "milk liters")
        {
            player->SellProduct("Milk", amount, renderEngine);
        }
        else if (input == "3" || input == "wool")
        {
            player->SellProduct("Wool", amount, renderEngine);
        }
        else if (input == "4" || input == "crocodile skins")
        {
            player->SellProduct("Crocodile Skin", amount, renderEngine);
        }
        else if (input == "5" || input == "return")
        {
            return;
        }
        else
        {
            cout << "Invalid Input" << '\n';
        }
    }
}

void WorldSystem::PurchaseScreen(RenderingEngine * renderEngine, Farmer * player) const
{
    if (bIsMarketCrash)
    {
        cout << "The market values have crashed!!!" << '\n';
        cout << "I will not allow you to purchase any of them though." << '\n';
        cout << "Are you sure you want to continue? (yes/no)" << '\n';
        string input;
        cin >> input;

        if (input == "yes")
        {
            cout << "Alright, but I warned you!!!" << '\n';
            cout << '\n';
        }
        else
        {
            return;
        }
    }

    renderEngine->ClearConsole();
    renderEngine->BuyAnimalsScreen(player);
    while (true)
    {
        string input;
        int amount;
        getline(cin, input);
        StringToLower(input);

        if (input == "1" || input == "2" || input == "3" || input == "4"
            || input == "chicken" || input == "cow" || input == "sheep" || input == "crocodile")
        {
            while (true)
            {
                cout << "And how many?" << '\n';
                cin >> amount;
                cin.ignore();

                // for when the user enters something other than int
                if (cin.fail()) {
                    cin.clear(); // Clear the fail state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                    cout << "Invalid Input" << '\n';
                    continue;
                }

                if (amount <= 0)
                {
                    cout << "Invalid amount: " << amount << '\n';
                    continue;
                }
                break;
            }
        }

        if (bIsMarketCrash && (input != "5" || input != "return"))
        {
            cout << "nuh uh" << '\n';
            continue;
        }

        if (input == "1" || input == "chicken")
        {
            player->PurchaseAnimal("Chicken", amount, renderEngine);
        }
        else if (input == "2" || input == "cow")
        {
            player->PurchaseAnimal("Cow", amount, renderEngine);
        }
        else if (input == "3" || input == "sheep")
        {
            player->PurchaseAnimal("Sheep", amount, renderEngine);
        }
        else if (input == "4" || input == "crocodile")
        {
            player->PurchaseAnimal("Crocodile", amount, renderEngine);
        }
        else if (input == "5" || input == "return")
        {
            return;
        }
        else
        {
            cout << "Invalid Input" << '\n';
        }
    }
}


void WorldSystem::GenerateRandomEvent(RenderingEngine* renderEngine, Farmer* player)
{
    renderEngine->ClearConsole();
    cout << "A random event has occured!!!" << '\n';

    RandomEvents randomEvent = static_cast<RandomEvents>(random(0, 7));

    
    string requestProduct;
    string randomAnimalType;

    switch (random(1, 4))
    {
    case 1:
        requestProduct = "Eggs";
        randomAnimalType = "Chicken";
        break;

    case 2:
        requestProduct = "Milk liters";
        randomAnimalType = "Cow";
        break;

    case 3:
        requestProduct = "Wool";
        randomAnimalType = "Sheep";
        break;

    case 4:
        requestProduct = "Crocodile skin pieces";
        randomAnimalType = "Crocodile";
        break;
    }

    switch (randomEvent)
    {
    case RandomEvents::Robbery:
        cout << "A robber was spotted near your farm!" << '\n';
        player->RandomEventStealMoney(player->GetMoneyAmount() * random(0.1, 0.9));
        break;

    case RandomEvents::WolfAttack:
        cout << "A pack of wolves were spotted at your farm!" << '\n';
        player->RandomEventWolfAttack(random(0.1, 0.9));
        break;

    case RandomEvents::Hyperinflation:
        cout << "Hyperinflation has occured!" << '\n';
        cout << "All prices have gone up 1000%" << '\n';
        player->RandomEventHyperinflation();
        break;

    case RandomEvents::Plague:
        cout << "A plague has occured!" << '\n';
        player->RandomEventPlague(random(0.3, 0.9));
        break;

    case RandomEvents::NPCrequest:
        player->RandomEventNPCrequest(requestProduct, random(1, 10), random(0.95, 1.05));
        break;

    case RandomEvents::AnimalCapture:
        player->RandomEventAnimalCapture(randomAnimalType, random(0.0, 1.0));
        break;

    case RandomEvents::MarketCrash:
        cout << "A Market Crash has occured!" << '\n';
        cout << "Be adviced to NOT use the market this day!!" << '\n';
        player->RandomEventMarketCrash();
        bIsMarketCrash = true;
        break;

    case RandomEvents::Tornado:
        player->RandomEventTornado(random(0.4, 0.9), random(0.4, 0.9));
        break;
    default:
        break;
    }

    cout << '\n';
    system("pause");
}
