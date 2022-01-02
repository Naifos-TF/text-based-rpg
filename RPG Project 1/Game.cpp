#include "Game.h"

std::unique_ptr<std::unordered_map<std::string, std::tuple<std::string, std::string, size_t, size_t, Stats>>> Game::ListOfConsumables = std::make_unique<std::unordered_map<std::string, std::tuple<std::string, std::string, size_t, size_t, Stats>>>(Game::GetConsumablesList());


Game::Game()
	:	MainPlayer{std::make_unique<Player>()}, Exit{false}
{

	
}

void Game::DisplayItems() const
{

	for (const auto& it : *ListOfConsumables) {
		std::cout << it.first << std::endl;
	}
}

void Game::Start()
{
	Intro();
	do {
		std::cout << std::endl;
		std::cout << "------------------------------------------------" << std::endl;
		std::cout <<  std::endl;
		std::cout << *MainPlayer << std::endl;
		std::cout << std::endl;
		std::cout << "------------------------------------------------" << std::endl;
		std::cout << std::endl;
		DisplayMenu();
		std::cout << "------------------------------------------------" << std::endl;
	} while (!GetExit());

}

const bool& Game::GetExit() 
{
	return this->Exit;
}

void Game::DisplayFighters(const Player& P, const EnemyPNJ& E) {

	std::cout << std::setw(20) << std::left << P.GetName() << E.GetName() << std::endl;

	std::cout << std::setw(10) << "LEVEL : ";
	std::cout << std::setw(20) << std::left << P.GetPlayerStats().GetStat(Stats::LEVEL);
	std::cout << E.GetEnemyStats().GetStat(Stats::LEVEL) << std::endl;
	std::cout << std::endl;

	std::cout << std::setw(10) << "Health : ";
	std::cout << std::setw(2) << std::left << P.GetPlayerStats().GetStat(Stats::CURRENT_HEALTH) << "/" << P.GetPlayerStats().GetStat(Stats::MAX_HEALTH);
	std::cout << std::setw(12) << std::right <<  E.GetEnemyStats().GetStat(Stats::CURRENT_HEALTH) << "/" << E.GetEnemyStats().GetStat(Stats::MAX_HEALTH) << std::endl;

	std::cout << std::endl;

	std::cout << std::setw(10)  << std::left << "ATK : ";
	std::cout << std::setw(20) << std::left << P.GetPlayerStats().GetStat(Stats::ATTACK);
	std::cout <<  E.GetEnemyStats().GetStat(Stats::ATTACK) << std::endl;

	std::cout << std::setw(10) << "DEF : ";
	std::cout << std::setw(20) << std::left << P.GetPlayerStats().GetStat(Stats::DEFENSE);
	std::cout << E.GetEnemyStats().GetStat(Stats::DEFENSE) << std::endl;

	std::cout << std::setw(10) << "CRIT : ";
	std::cout << std::setw(20) << std::left << P.GetPlayerStats().GetStat(Stats::CRITICAL);
	std::cout << E.GetEnemyStats().GetStat(Stats::CRITICAL) << std::endl;
}


void Game::DisplayBattleMenu()
{
	std::unique_ptr<EnemyPNJ> e = Game::CreateEnemy();
	std::cout << "You are attacked by "<<e->GetName() <<"." << std::endl;
	std::cout << *e <<std::endl;


	int MaxChoice = 3;
	do {
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "1. Attack" << std::endl;
		std::cout << "2. Drink potion (" << MainPlayer->CountNumberOfItem(Items_Util::HEALTH_POTION) <<")" << std::endl;
		std::cout << "3. Run away" << std::endl;

		int MaxChoice = 3;
		int UserChoice = GetUserInput(MaxChoice);
		

		//Player's turn
		switch (UserChoice) {
		case 1: {
			PlayerAttack(*e);
			if (MainPlayer->GetIsFighting()) {
				//Enemy's turn
				EnemyAttack(*e);
				DisplayFighters(*MainPlayer, *e);
			}
			break;
		}
		case 2: {
			if (UsePotion()) {
				//Enemy's turn
				EnemyAttack(*e);
				DisplayFighters(*MainPlayer, *e);
			}
			break;
		}
		case 3: {
			std::cout << std::endl;
			std::cout << "You fleed like a coward." << std::endl;
			MainPlayer->SetIsFighting(false);
			break;
		}
		default:
			break;
		}

	} while (MainPlayer->GetIsFighting());
}
//try to use a potion and return true if it succeeds
bool Game::UsePotion() {
	size_t PotionPower = 20;
	//check if player has potion in inventory
	for (const auto& item : MainPlayer->GetInventory()) {
		if (item.first->GetName() == Items_Util::HEALTH_POTION) {
			if (MainPlayer->GetPlayerStats().GetStat(Stats::CURRENT_HEALTH) + PotionPower > MainPlayer->GetPlayerStats().GetStat(Stats::MAX_HEALTH)) {
				MainPlayer->SetPlayerStats(Stats::CURRENT_HEALTH, MainPlayer->GetPlayerStats().GetStat(Stats::MAX_HEALTH));//if potion would bring player over maxhp set health to maxhp
			}
			else {
				MainPlayer->SetPlayerStats(Stats::CURRENT_HEALTH, MainPlayer->GetPlayerStats().GetStat(Stats::CURRENT_HEALTH) + PotionPower);//else adds to current health
			}
			//removes item after it has been used
			MainPlayer->UseItem(item.first);
			std::cout << Items_Util::HEALTH_POTION << " has been used ! " << std::endl;
			return true;
		}
	}
	std::cout << "You have no potion !" << std::endl;
	return false;

	
	

	//removes potion
}

const std::unordered_map<std::string, std::tuple<std::string, std::string, size_t, size_t, Stats>>& Game::GetListOfConsumables()
{
	return *Game::ListOfConsumables;
}





//populating the consumable list so it can be used in items_util.cpp
//params are : Item name, { rarity, description, id, value, stats }
std::unordered_map<std::string, std::tuple<std::string, std::string, size_t, size_t, Stats>> Game::GetConsumablesList() {
	static constexpr const char* Rarity1 = "Common";
	static constexpr const char* Rarity2 = "Uncommon";
	static constexpr const char* Rarity3 = "Rare";
	static constexpr const char* Rarity4 = "Epic";
	static constexpr const char* Rarity5 = "Legendary";

	std::unordered_map<std::string, std::tuple<std::string, std::string, size_t, size_t,Stats>> items{
		//name,			{rarity, description, id, value, stats}
		{"Health Potion", {Rarity1,"'Regenerates 20 health.'",1,20, Stats() }}
	};

	return items;
}






void Game::DisplayMenu() 
{
	

	if (MainPlayer->GetIsFighting()) {
		DisplayBattleMenu();
	}
	else
	{
		switch (MainPlayer->GetLocation().GetLocationTypeToInt()) {
			case 0://town
				DisplayTownMenu();
				break;
			case 1://wild zones
				DisplayWildMenu();
				break;
			case 2://shop
				DisplayShopMenu();
				break;
			case 3://inn
				DisplayInnMenu();
				break;
			case 4://bank
				DisplayBankMenu();
			default:
				break;
		}
	}

}


const int Game::GetUserInput(const int& MaxChoice) const {
	std::cout << "Enter your choice : ";

	int value{};
	std::string entry{};
	bool done = false;
	do {
		std::cin >> entry;
		std::istringstream validator{ entry };
		if (validator >> value && (value>0 && value <= MaxChoice) )
			done = true;
		else
			std::cout << "Please enter a correct value" << std::endl;

		// discards the input buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (!done);

	return value;
}

const size_t Game::GetUserInput() const {
	std::cout << "Enter the amount : ";

	size_t value{};
	std::string entry{};
	bool done = false;
	do {
		std::cin >> entry;
		std::istringstream validator{ entry };
		if (validator >> value)
			done = true;
		else
			std::cout << "Please enter a correct value" << std::endl;

		// discards the input buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (!done);

	return value;
}

void Game::DisplayTownMenu()  
{
	std::cout << "1. Go to the Shop." << std::endl;
	std::cout << "2. Go to the Inn." << std::endl;
	std::cout << "3. Go to the Bank." << std::endl;
	std::cout << "4. Leave town and go to the Ice Lands." << std::endl;
	std::cout << "5. Leave town and go to the Misty Forest." << std::endl;
	std::cout << "6. Leave town and go to the Desert Ruins." << std::endl;
	std::cout << "7. Exit the game" << std::endl;

	int MaxChoice = 7;

	int UserChoice = GetUserInput(MaxChoice);

	switch (UserChoice) {
		case 1: {
			MainPlayer->SetLocation(std::move(std::make_unique<Location>("Shop")));
			break;
		}
		case 2: {
			MainPlayer->SetLocation(std::move(std::make_unique<Location>("Inn")));
			break;
		}
		case 3: {
			MainPlayer->SetLocation(std::move(std::make_unique<Location>("Bank")));
			break;
		}
		case 4: {
			MainPlayer->SetLocation(std::move(std::make_unique<Location>("Ice Lands")));
			break;
		}
		case 5: {
			MainPlayer->SetLocation(std::move(std::make_unique<Location>("The Misty Forest")));
			break;
		}
		case 6: {
			MainPlayer->SetLocation(std::move(std::make_unique<Location>("Desert Ruins")));
			break;
		}
		case 7:
		{
			ExitGame();
			break;
		}
		default:
			break;
	}
}

void Game::ExitGame() {
	this->Exit = true;
}

void Game::DisplayBankMenu()
{
	std::cout << "1. Deposit (MAX : "<< MainPlayer->GetMoney() <<")" << std::endl;
	std::cout << "2. Withdraw (MAX : " <<MainPlayer->GetBankMoney() <<")"<< std::endl;
	std::cout << "3. Exit" << std::endl;

	int MaxChoice = 3;

	int UserChoice = GetUserInput(MaxChoice);

	switch (UserChoice) {
	case 1: {
		size_t Amount  = GetUserInput();
		if (Amount > 0 )
			MainPlayer->Deposit(Amount);
		break;
	}
	case 2: {
		size_t Amount = GetUserInput();
		if (Amount > 0)
			MainPlayer->Withdraw(Amount);
		break;
	}
	case 3:
	{
		MainPlayer->SetLocation(std::move(std::make_unique<Location>("Harujmarr")));
		break;
	}
	default:
		break;
	}

}

//logic for player attacks
void Game::PlayerAttack(EnemyPNJ& E) {
	//formula for dmage (ATK * 2 - enemy def) 
	//if crit *2 multiplier
	size_t DamageDone = (MainPlayer->GetPlayerStats().GetStat(Stats::ATTACK) * 2) - (E.GetEnemyStats().GetStat(Stats::DEFENSE));
	size_t DamageRoll = Random::RandomNumber(1, 12);
	DamageDone += DamageRoll;
	std::cout << std::endl;
	std::cout << "You rolled " << DamageRoll << " as bonus damage." << std::endl;
	//roll for crit
	bool IsCrit = false;
	if (Random::RandomNumber(1, 100) <= MainPlayer->GetPlayerStats().GetStat(Stats::CRITICAL)) {
		std::cout << "Critical Hit !" << std::endl;
		DamageDone *= 2;
	}

	std::cout << "You did " << DamageDone << " damage." << std::endl;
	if (DamageDone >= E.GetEnemyStats().GetStat(Stats::CURRENT_HEALTH)) {
		PlayerWon(E);
		return;
	}

	E.ReceiveDamage(DamageDone);

}

void Game::PlayerDied() {
	std::cout << "You died and lost all your money ! " << std::endl;
	MainPlayer->Move(std::make_unique<Location>());
	MainPlayer->SetMoney(0);
	MainPlayer->SetIsFighting(false);
	MainPlayer->SetPlayerStats(Stats::CURRENT_HEALTH, MainPlayer->GetPlayerStats().GetStat(Stats::MAX_HEALTH));// Setting current health to max health
}

void Game::PlayerWon(const EnemyPNJ& E) {
	std::cout << "You won the fight ! " << std::endl;
	//=TRUNC(((LOG(A2+10)*100))/10) = xp given by mob per level
	MainPlayer->AddXP(CalculateGivenXP(E.GetEnemyStats().GetStat(Stats::LEVEL)));
	//MainPlayer->AddXP(100);
	MainPlayer->CheckLevelUp();
	MainPlayer->AddMoney(E.GetMoneyDropped());
	MainPlayer->SetIsFighting(false);
}

//logic for enemy attacks
void Game::EnemyAttack(EnemyPNJ& E) {
	//formula for dmage (ATK * 2 - enemy def) 
	//if crit *2 multiplier
	size_t DamageDone = (E.GetEnemyStats().GetStat(Stats::ATTACK) * 2) - (E.GetEnemyStats().GetStat(Stats::DEFENSE));
	//roll for crit
	bool IsCrit = false;
	if (Random::RandomNumber(1, 100) <= E.GetEnemyStats().GetStat(Stats::CRITICAL)) {
		std::cout << "Critical Hit !" << std::endl;
		DamageDone *= 2;
	}
	std::cout << "Ennemy did " << DamageDone << " damage to you." << std::endl;
	std::cout << std::endl;

	if (DamageDone >= MainPlayer->GetPlayerStats().GetStat(Stats::CURRENT_HEALTH)) {
		PlayerDied();
		return;
	}
	MainPlayer->ReceiveDamage(DamageDone);
}

const size_t Game::CalculateGivenXP(const size_t& EnemyLevel) const {
	//=TRUNC(((LOG(A2+10)*100))/10) = xp given by mob per level
	return trunc(((log10(EnemyLevel + 10) * 100)) / 10);
}
std::unique_ptr<EnemyPNJ> Game::CreateEnemy()
{

	
	std::unique_ptr<Location> EnemyLocation = std::make_unique<Location>(MainPlayer->GetLocation().GetLocationName());
	std::string EnemyName;
	std::unique_ptr<Stats> EnemyStats = std::move(GenerateEnemyStats());
	const size_t MoneyDropped =  CalculateMoneyDropped(EnemyStats->GetStat(Stats::LEVEL));


	if (EnemyLocation->GetLocationName() == Location::TheMistyForestName) {
		EnemyName = EnemyPNJ::ForestEnemyName;
	}
	else if (EnemyLocation->GetLocationName() == Location::IceLandsName) {
		EnemyName = EnemyPNJ::FrostEnemyName;
	}
	else if (EnemyLocation->GetLocationName() == Location::DesertRuinsName) {
		EnemyName = EnemyPNJ::DesertEnemyName;
	}
	else {
		EnemyName = "Unknown Bandit";
	}

	return std::make_unique<EnemyPNJ>(EnemyName,std::move(EnemyLocation),MoneyDropped,std::move(EnemyStats));
}

const size_t Game::CalculateMoneyDropped(const size_t& Level) const {
	return (Level*2) + 10 + Random::RandomNumber(0, 30);
};

const size_t Game::GenerateLevel() const{
	size_t LevelVariation = 2;
	//generated level can be down from -LevelVariation under player Level
	size_t FirstValue {};
	//generated level can be up to +LevelVariation above player Level
	size_t SecondValue{ MainPlayer->GetPlayerStats().GetStat(Stats::LEVEL) + LevelVariation };

	//checking if it could theoratically generate a lvl lower than 1
	int LowestLevel = MainPlayer->GetPlayerStats().GetStat(Stats::LEVEL)- LevelVariation;
	//if so we make the min level to 1
	if (LowestLevel <= 0) {
		FirstValue = 1;
		return Random::RandomNumber(FirstValue, SecondValue);
	}
	else
		return Random::RandomNumber(FirstValue, SecondValue);
};

std::unique_ptr<Stats> Game::GenerateEnemyStats()
{
	size_t Level = GenerateLevel();

	size_t Attack{(Level*2)+2};
	size_t Def {(Level * 2) - 1 };
	size_t Critical{1};
	size_t Xp{};

	//logb(x) = loge(x) / loge(b)
	size_t MaxHealth = ((log2(Level)/log2(8))*100)+20;
	size_t CurrentHealth = MaxHealth;
	size_t Energy = 0;

	std::map<std::string, size_t>tmp{
		{Stats::CURRENT_HEALTH, CurrentHealth},
		{Stats::MAX_HEALTH, MaxHealth},
		{Stats::ENERGY, 0},
		{Stats::ATTACK, Attack},
		{Stats::DEFENSE, Def},
		{Stats::CRITICAL, Critical},
		{Stats::LEVEL, Level},
		{Stats::EXPERIENCE, 0},
	};
	return std::make_unique<Stats>(tmp);
}

void Game::DisplayWildMenu() 
{
	std::cout << "1. Explore" << std::endl;
	std::cout << "2. Go back to Harujmarr" << std::endl;

	int MaxChoice = 2;

	int UserChoice = GetUserInput(MaxChoice);

	switch (UserChoice) {
	case 1: {
		MainPlayer->Explore();
		break;
	}
	case 2: {
		MainPlayer->SetLocation(std::move(std::make_unique<Location>("Harujmarr")));
		break;
	}
	case 3:
	{
		this->ExitGame();
		break;
	}
	default:
		break;
	}

}

void Game::DisplayBuyMenu() {
	size_t AtkScrollPrice = 100;
	size_t DefScrollPrice = 100;
	std::cout << "1. Buy potion "<< std::get<3>(GetListOfConsumables().find(Items_Util::HEALTH_POTION)->second) <<" " << Item::GetCurrency() << ". " << std::get<1>(GetListOfConsumables().find(Items_Util::HEALTH_POTION)->second) << std::endl;//getting the value of item out of the list of the map<string, tuple> consumable
	std::cout << "2. Buy ATK scroll (+2 ATK) " << AtkScrollPrice << Item::GetCurrency() << "." << std::endl;
	std::cout << "3. Buy DEF scroll (+2 DEF) " << DefScrollPrice<<  Item::GetCurrency() << "." << std::endl;
	std::cout << "4. Leave the shop." << std::endl;

	int MaxChoice = 4;

	int UserChoice = GetUserInput(MaxChoice);

	switch (UserChoice) {
	case 1: {
		MainPlayer->BuyItem(Items_Util::CreateConsumable(Items_Util::HEALTH_POTION));
		break;
	}
	case 2: {
		if (MainPlayer->GetMoney() >= AtkScrollPrice) {
			MainPlayer->SetPlayerStats(Stats::ATTACK, MainPlayer->GetPlayerStats().GetStat(Stats::ATTACK) + 2);//Adding 2 atk
			MainPlayer->SetMoney(MainPlayer->GetMoney() - AtkScrollPrice);//substracting scroll price from money
			std::cout << "You bought an ATK scroll." << std::endl;
		}
		break;
	}
	case 3: {
		if (MainPlayer->GetMoney() >= AtkScrollPrice) {
			MainPlayer->SetPlayerStats(Stats::DEFENSE, MainPlayer->GetPlayerStats().GetStat(Stats::DEFENSE) + 2);//adding 2 def
			MainPlayer->SetMoney(MainPlayer->GetMoney() - DefScrollPrice);//substracting scroll price from money
			std::cout << "You bought a DEF scroll." << std::endl;
		}
		break;
	}
	case 4:
	{
		MainPlayer->SetLocation(std::move(std::make_unique<Location>("Harujmarr")));
		break;
	}
	default:
		break;
	}
}

void Game::DisplaySellMenu() {
	size_t i{};
	std::vector<std::shared_ptr<Item>> tmpVector;


	for (const auto& item : MainPlayer->GetInventory()) {
		i++;
		std::cout << i << ". Sell " << (*(item.first)).GetName() << " (" << item.first->GetValue()-5<<")" << std::endl;//-5 also in player.cpp sell item
		tmpVector.push_back(item.first);//push all the items into a vector 
	}
	std::cout << i + 1 << ". Leave" << std::endl;

	int MaxChoice = i+1;
	int UserChoice = GetUserInput(MaxChoice);
	//(tmpVector.at(UserChoice - 1)
	if (UserChoice != MaxChoice) {// max choice = exit choice
		MainPlayer->SellItem(tmpVector.at(UserChoice - 1));//sell the item choosen by the user
		
	} 

}


void Game::DisplayShopMenu() 
{
	std::cout << "1. Buy items." << std::endl;
	std::cout << "2. Sell items." << std::endl;
	std::cout << "3. Leave the shop." << std::endl;

	int MaxChoice = 3;

	int UserChoice = GetUserInput(MaxChoice);

	switch (UserChoice) {
	case 1: {
		//std::cout << "Buying stuff" << std::endl;
		DisplayBuyMenu();
		break;
	}
	case 2: {
		//std::cout << "Selling stuff" << std::endl;
		DisplaySellMenu();
		break;
	}
	case 3: {
		MainPlayer->SetLocation(std::move(std::make_unique<Location>("Harujmarr")));
		break;
	}
	case 4:
	{
		this->ExitGame();
		break;
	}
	default:
		break;
	}

}


void Game::DisplayInnMenu()
{
	std::cout << "1. Sleep." << std::endl;
	std::cout << "2. Leave the inn." << std::endl;

	int MaxChoice = 2;

	int UserChoice = GetUserInput(MaxChoice);

	switch (UserChoice) {
	case 1: {
		std::cout << "After a good night of sleep, you are back to full health." << std::endl;
		MainPlayer->SetPlayerStats(Stats::CURRENT_HEALTH, MainPlayer->GetPlayerStats().GetStat(Stats::MAX_HEALTH));
		break;
	}
	case 2: {
		MainPlayer->SetLocation(std::move(std::make_unique<Location>("Harujmarr")));
		break;
	}
	case 3:
	{
		this->ExitGame();
		break;
	}
	default:
		break;
	}

}



void Game::Intro() const
{
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "|         Welcome to Hero Of Aitnelav !        |" << std::endl;
	std::cout << "|Hero Of Aitnelav is a command invite RPG game.|" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	//Pause(2);
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "After a long travel, you finally arrived in the great city of Harujmarr."<<std::endl;
	//Pause(2);
	std::cout << "The city is strangely silent and you hear people whispering as you walk in."<<std::endl;
	//Pause(2);
}


void Game::Pause(const int& seconds) const
{
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
