#pragma once
#include<string>
#include <unordered_map>
#include <tuple>
#include <iostream>
#include "Location.h"
#include "Stats.h"
#include "Player.h"
#include <chrono>
#include <thread>
#include <sstream>
#include <random>
#include "EnemyPNJ.h"
#include "math.h"
#include <iomanip>
#include "Items_Util.h"

//Responsible for : 
//instantiating all the objects (players, locations, ennemis, items..)
//the gameloop
class Game
{
private:
	//Initiate the static list of consumables items
	//Using an ordered map with the item name as key paired with a tuple of : item rarity, item description, item id, and item value.
	static std::unordered_map < std::string, std::tuple<std::string, std::string, size_t, size_t, Stats>> GetConsumablesList();
	//A pointer to an unordered map of consumable items 
	static std::unique_ptr<std::unordered_map<std::string, std::tuple<std::string, std::string, size_t, size_t, Stats>>> ListOfConsumables;

	std::unique_ptr<Player> MainPlayer;
	bool Exit;

	void DisplayBankMenu();
	void DisplayMenu();
	void DisplayTownMenu();
	void DisplayWildMenu();
	void DisplayShopMenu();
	void DisplayInnMenu();
	void DisplayBattleMenu();
	void DisplayFighters(const Player& P, const EnemyPNJ& E);
	void DisplayBuyMenu();
	void DisplaySellMenu();
	const int GetUserInput(const int& max_choice) const;
	const size_t GetUserInput() const;//for deposit and withdraw
	const bool& GetExit();


	void Intro() const;
	void Pause(const int& seconds) const;
	void DisplayItems() const;

	std::unique_ptr<EnemyPNJ> CreateEnemy();
	std::unique_ptr<Stats> GenerateEnemyStats();
	const size_t GenerateLevel() const;
	const size_t CalculateMoneyDropped(const size_t& Level) const;
	void PlayerAttack(EnemyPNJ& E);
	void EnemyAttack(EnemyPNJ& E);
	void PlayerDied();
	void PlayerWon(const EnemyPNJ& E);
	bool UsePotion();
	const size_t CalculateGivenXP(const size_t& EnemyLevel) const;
public:

	Game();
	void Start();
	void ExitGame();//exit to true
	
	//return a const ref to an unordered map of consumable items 
	const static::std::unordered_map<std::string, std::tuple<std::string, std::string, size_t, size_t, Stats>>& GetListOfConsumables();
};

