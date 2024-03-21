#pragma once


// Random events could be:
	// 1. Robbery (steals a percentage of the player's money)
	// 2. Wolf Attack (a percentage of the player's sheep die) (or maybe the welsh stole them)
	// 3. Quick Hyperinflation (all prices go up by 1000%, but the next day everything is down 1000%)
	// 4. Plague (a percentage of all animals die)
	// 5. Human encounter (a person appears to request some products for a price slightly different than the market price (like in hayday))
	// 6. Animal encounter (an animal appears near the farm, giving the player the option to attempt to capture (maybe 40 : 60 win lose ratio))
	// 7. Market crash (all prices are 0, the user cannot sell nor purchase)
	// 8. Tornado (the player will need to spend money to repair the damages (percentage of money) and possibly lose some animals (percentage of all animals))
	// All events take into consideration the amount of money and animals the player has
enum RandomEvents
{
	// Steals a percentage of the player's money
	Robbery = 0,

	// A percentage of the player's sheep die
	WolfAttack = 1,

	// All prices go up by 1000%
	Hyperinflation = 2,

	// A percentage of all animals die
	Plague = 3,

	// A person appears to request some products
	NPCrequest = 4,

	// An animal appears, the player could attempt to capture it
	AnimalCapture = 5,

	// All prices drop to 0 and the user cannot purchase or sell anything
	MarketCrash = 6,

	// The player needs to pay to repair the buildings and might have lost a few animals
	Tornado = 7
};