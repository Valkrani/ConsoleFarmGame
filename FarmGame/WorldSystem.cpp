#include "WorldSystem.h"
#include <iostream>
#include <fstream>
#include <random> // used for random()
#include "EnumTypes.h"


// Given a range, it returns a random integer
int random(int range_from, int range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>    distr(range_from, range_to);
    return distr(generator);
}

// Given a range, it returns a random double
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
    basechanceForRandomEvent = 1.0; // a base of 10%
    chanceForRandomEvent = basechanceForRandomEvent;
    bIsMarketCrash = false;
}


void WorldSystem::ProccessDay(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices, bool& isUserQuiting)
{
    if (days != 1)
    {
        todaysPrices->DailyPriceChange();
        if (random(0.0, 1.0) <= chanceForRandomEvent)
        {
            GenerateRandomEvent(player, todaysPrices);
            chanceForRandomEvent = basechanceForRandomEvent;
        }
        else
        {
            chanceForRandomEvent += 0.05; // increases by 5% every day
        }
    }


    while (true)
    {
        cout << "\033[2J\033[1;1H"; // clears screen and sets cursor to 1,1
        renderEngine->DisplayDailyOptions(days, player);

        int input;
        cin >> input;

        switch (input)
        {
        // Sell Products
        case 1:
            this->SellScreen(renderEngine, player, todaysPrices);
            break;

        // Buy Animals
        case 2:
            this->PurchaseScreen(renderEngine, player, todaysPrices);
            break;

        // Sleep
        case 3:
            return;
            break;

        // Save and Quit
        case 4:
            isUserQuiting = true;
            return;
            break;

        default:
            cout << "Wrong command. Try again." << '\n';
            break;
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
        todaysPrices->WeeklyPriceChange();
        basechanceForRandomEvent += 0.05;
    }
    todaysPrices->DailyPriceChange();

    days++;

    if (bIsMarketCrash)
    {
        bIsMarketCrash = false;
    }

}


void WorldSystem::SellScreen(RenderingEngine* renderEngine, Farmer* player, Prices* todaysPrices) const
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


    cout << "\033[2J\033[1;1H"; // clears screen and sets cursor to 1,1
    renderEngine->SellProductScreen(player, todaysPrices);

    while (true)
    {
        int input;
        int amount;
        cin >> input;

        // for when the user enters something other than int
        if (cin.fail()) {
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid Input" << '\n';
            continue; // Restart the loop
        }


        if (input >= 1 && input <= 4)
        {
            while (true)
            {
                cout << "And how many?" << '\n';
                cin >> amount;
                if (amount <= 0)
                {
                    cout << "Invalid amount: " << amount << '\n';
                    continue;
                }
                break;
            }
        }

        switch (input)
        {
        case 1:
            player->SellProduct(Product::Eggs, amount, renderEngine, todaysPrices);
            break;
        case 2:
            player->SellProduct(Product::Milk, amount, renderEngine, todaysPrices);
            break;
        case 3:
            player->SellProduct(Product::Wool, amount, renderEngine, todaysPrices);
            break;
        case 4:
            player->SellProduct(Product::CrocSkin, amount, renderEngine, todaysPrices);
            break;
        case 5:
            return;
            break;
        default:
            cout << "Invalid Input" << '\n';
            break;
        }
    }
}

void WorldSystem::PurchaseScreen(RenderingEngine * renderEngine, Farmer * player, Prices * todaysPrices) const
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

    cout << "\033[2J\033[1;1H"; // clears screen and sets cursor to 1,1
    renderEngine->BuyAnimalsScreen(player, todaysPrices);
    while (true)
    {
        int input;
        int amount;
        cin >> input;

        // for when the user enters something other than int
        if (cin.fail()) {
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid Input" << '\n';
            continue;
        }

        if (input >= 1 && input <= 4)
        {
            while (true)
            {
                cout << "And how many?" << '\n';
                cin >> amount;
                if (amount <= 0)
                {
                    cout << "Invalid amount: " << amount << '\n';
                    continue;
                }
                break;
            }
        }


        if (bIsMarketCrash && input != 5)
        {
            cout << "nuh uh" << '\n';
            continue;
        }

        switch (input)
        {
        case 1:
            player->PurchaseAnimal(AnimalTypes::Chicken, amount, renderEngine, todaysPrices);
            break;
        case 2:
            player->PurchaseAnimal(AnimalTypes::Cow, amount, renderEngine, todaysPrices);
            break;
        case 3:
            player->PurchaseAnimal(AnimalTypes::Sheep, amount, renderEngine, todaysPrices);
            break;
        case 4:
            player->PurchaseAnimal(AnimalTypes::Crocodile, amount, renderEngine, todaysPrices);
            break;
        case 5:
            return;
            break;
        default:
            cout << "Invalid Input" << '\n';
            break;
        }
    }
}


void WorldSystem::GenerateRandomEvent(Farmer* player, Prices* todaysPrices)
{
    cout << "\033[2J\033[1;1H"; // clears screen and sets cursor to 1,1
    cout << "A random event has occured!!!" << '\n';


    RandomEvents randomEvent = static_cast<RandomEvents>(random(0, 8));

    // Created for when in use in the switch
    // as I cannot create them inside
    Product requestProduct;
    AnimalTypes randomAnimalType;

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
        todaysPrices->RandomEventHyperinflation();
        break;

    case RandomEvents::Plague:
        cout << "A plague has occured!" << '\n';
        player->RandomEventPlague(random(0.3, 0.9));
        break;

    case RandomEvents::NPCrequest:
        requestProduct = static_cast<Product>(random(0, 3));
        player->RandomEventNPCrequest(requestProduct, random(1, 10), random(0.95, 1.05), todaysPrices);
        break;

    case RandomEvents::AnimalCapture:
        randomAnimalType = static_cast<AnimalTypes>(random(0, 3));
        player->RandomEventAnimalCapture(randomAnimalType, random(0.0, 1.0));
        break;

    case RandomEvents::MarketCrash:
        cout << "A Market Crash has occured!" << '\n';
        cout << "Be adviced to NOT use the market this day!!" << '\n';
        todaysPrices->RandomEventMarketCrash();
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
