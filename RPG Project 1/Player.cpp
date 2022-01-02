#include "Player.h"


Player::Player(std::string Name, bool IsFriendly, std::unique_ptr<Stats> PlayerStats, long long Money, std::shared_ptr<std::map<std::shared_ptr<Item>, int>> Inventory)
	: Character{Name,IsFriendly,false,std::make_unique<Location>()}, PlayerStats{std::move(PlayerStats)}, Money{Money}, Inventory{std::move(Inventory)}, BankMoney{0}
{

}

const std::string& Player::GetName() const
{
	return Character::GetName();
}


const bool& Player::GetIsFriendly() const
{
	return Character::GetIsFriendly();
}

const Location& Player::GetLocation() const
{
	return Character::GetLocation();
}

void Player::SetName(const std::string& Name)
{
	return Character::SetName(Name);
}

void Player::SetIsFriendly(const bool& b)
{
	return Character::SetIsFriendly(b);
}

void Player::SetLocation(std::unique_ptr<Location> NewLocation)
{
	return Character::SetLocation(std::move(NewLocation));
}

const Stats& Player::GetPlayerStats() const 
{
	return *(this->PlayerStats);
}

void Player::DisplayStats() const {
	//std::cout << *(this->PlayerStats).Display() << std::endl;
}
void Player::SetPlayerStats(const std::string& StatName, const size_t& value)
{
	PlayerStats->SetStat(StatName, value);
}
void Player::SetIsFighting(const bool& IsFighting)
{
	return Character::SetIsFighting(IsFighting);
}

void Player::Move(std::unique_ptr<Location> NewLocation)
{
	SetLocation(std::move(NewLocation));
	std::cout << "You moved to " << GetLocation().GetLocationName() << std::endl;
}
const long long& Player::GetMoney() const
{
	return this->Money;
}

const long long& Player::GetBankMoney() const
{
	return this->BankMoney;
}

const std::map<std::shared_ptr<Item>, int> Player::GetInventory() const
{
	return *Inventory;
}

void Player::AddMoney(const size_t& amount)
{
	this->Money += amount;
	std::cout << "+" << amount << " " << Item::GetCurrency() << std::endl;
}

void Player::SetMoney(const long long& amount)
{
	this->Money = amount;
}

void Player::Explore()
{
	size_t ChanceToFindGold = 33;// 33/100
	size_t ChanceToFight = 50;
	const size_t rand = Random::RandomNumber(1, 100);
	
	if (rand <= ChanceToFindGold) {
		size_t GoldFound = Random::RandomNumber(1, 20);
		std::cout << "While looking around, you found a chest containing " << GoldFound << " " << Item::GetCurrency() << "." << std::endl;
		AddMoney(GoldFound);
	}
	else if (rand > ChanceToFindGold && rand <= ChanceToFindGold + ChanceToFight) {
		SetIsFighting(true);
	}
	else
		std::cout << "You found nothing." << std::endl;
}


void Player::AddXP(const size_t& Amount)
{
	SetPlayerStats(Stats::EXPERIENCE, GetPlayerStats().GetStat(Stats::EXPERIENCE) + Amount);
	std::cout << "You gained " << Amount << " XP." << std::endl;
}

void Player::CheckLevelUp()
{
	//TRUNC(LOG10(LEVEL+1)*100)  formula xp needed to reach level
	int ExpNeeded = log10(PlayerStats->GetStat(Stats::LEVEL) + 1) * 100;
	if (PlayerStats->GetStat(Stats::EXPERIENCE) >= ExpNeeded) {
		LevelUp();
		//AddXP(-Difference);//adding the rest of xp
		
	}
}

void Player::LevelUp()
{
	size_t ATK_GROWTH = 2;
	size_t DEF_GROWTH = 2;
	size_t CRIT_GROWTH = 1;

	SetPlayerStats(Stats::LEVEL, GetPlayerStats().GetStat(Stats::LEVEL) + 1);
	SetPlayerStats(Stats::EXPERIENCE, 0);

	SetPlayerStats(Stats::ATTACK, GetPlayerStats().GetStat(Stats::ATTACK) + ATK_GROWTH);
	SetPlayerStats(Stats::DEFENSE, GetPlayerStats().GetStat(Stats::DEFENSE) + DEF_GROWTH);

	//cant get over 20 critical chances
	if (GetPlayerStats().GetStat(Stats::CRITICAL) < 20) {
		SetPlayerStats(Stats::CRITICAL, GetPlayerStats().GetStat(Stats::CRITICAL) + CRIT_GROWTH);
	}
	//TRUNC(LOG(LVL;8)*100)+50
	size_t NewMaxHealth = ((log2(GetPlayerStats().GetStat(Stats::LEVEL)) / log2(8)) * 100) + 50;
	SetPlayerStats(Stats::MAX_HEALTH, NewMaxHealth);
	SetPlayerStats(Stats::CURRENT_HEALTH, NewMaxHealth);

	std::cout << "Level Up ! " << std::endl;
}

void Player::ReceiveDamage(const size_t& Amount)
{
	if (PlayerStats->GetStat(Stats::CURRENT_HEALTH) - Amount <= 0) {
		PlayerStats->SetStat(Stats::CURRENT_HEALTH, 0);
	}
	else {
		PlayerStats->SetStat(Stats::CURRENT_HEALTH, PlayerStats->GetStat(Stats::CURRENT_HEALTH) - Amount);
	}
}

void Player::AddItem(std::shared_ptr<Item> It)
{
	Inventory->insert(std::make_pair(std::move((It)), 1));
}


void Player::RemoveItem(std::shared_ptr<Item>It)
{
	auto iter = Inventory->find(It);
	if (iter != Inventory->end()) {
		//std::cout << "Item sold!" << std::endl;
		Inventory->erase(iter);
	}

}

void Player::UseItem(std::shared_ptr<Item>It) {
	RemoveItem(It);
}

void Player::Withdraw(const size_t& Amount) {
	if (BankMoney - Amount >= 0 && Amount<=BankMoney) {
		this->BankMoney -= Amount;
		this->Money += Amount;
		std::cout << "You withdrew " << Amount << Item::GetCurrency() << ".";
	}
	else
		std::cout << "You don't have enough " << Item::GetCurrency() <<".";
}

void Player::Deposit(const size_t& Amount) {
	if (Amount > 0 && this->Money >= Amount) {
		this->BankMoney += Amount;
		this->Money -= Amount;
		std::cout << "You deposited " << Amount << Item::GetCurrency() << ".";
	}
	else
		std::cout << "You don't have enough " << Item::GetCurrency() << ".";
}

void Player::BuyItem(std::shared_ptr<Item> It)
{
	if (Money >= It->GetValue()) {
		Money -= It->GetValue();
		std::cout << "You bought " << It->GetName() << "." << std::endl;
		AddItem(std::move(It));	
	}
}

void Player::SellItem(std::shared_ptr<Item> It)
{
	size_t devaluation = 5;
	Money += It->GetValue()- devaluation;
	std::cout << "You sold " << It->GetName() << "." << std::endl;
	RemoveItem(std::move(It));
}

const size_t Player::CountNumberOfItem(std::shared_ptr<Item>It) const{
	std::string NameToLookFor = It->GetName();
	size_t counter{};
	for (const auto& val : GetInventory()) {
		if(val.first->GetName() == NameToLookFor)
			counter++;
	}
	return counter;
}

const size_t Player::CountNumberOfItem(std::string ItemName) const {
	std::string NameToLookFor = ItemName;
	size_t counter{};
	for (const auto& val : GetInventory()) {
		if (val.first->GetName() == NameToLookFor)
			counter++;
	}
	return counter;
}
std::ostream& operator<<(std::ostream& Os, const Player&  P)
{
	Os << "Location" << " : " << P.GetLocation().GetLocationName() << std::endl;
	Os <<"Name : " << P.GetName() << std::endl;
	Os << Stats::LEVEL << " : " << P.GetPlayerStats().GetStat(Stats::LEVEL) <<" " << Stats::EXPERIENCE << " : " << P.GetPlayerStats().GetStat(Stats::EXPERIENCE) << std::endl;
	Os << Item::GetCurrency() << " : " << P.GetMoney() << std::endl;
	Os << Stats::CURRENT_HEALTH << "/" << Stats::MAX_HEALTH << " : " << P.GetPlayerStats().GetStat(Stats::CURRENT_HEALTH) << "/" << P.GetPlayerStats().GetStat(Stats::MAX_HEALTH) << std::endl;
	Os << Stats::ATTACK << " : " << P.GetPlayerStats().GetStat(Stats::ATTACK)<<" " << Stats::DEFENSE << " : " << P.GetPlayerStats().GetStat(Stats::DEFENSE) << " "<< Stats::CRITICAL << " : " << P.GetPlayerStats().GetStat(Stats::CRITICAL) << std::endl;


	return Os;
}



