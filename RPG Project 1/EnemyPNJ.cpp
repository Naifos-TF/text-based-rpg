#include "EnemyPNJ.h"
//Player::Player(std::string Name, bool IsFriendly, std::unique_ptr<Stats> PlayerStats, long long Money, std::unique_ptr<std::map<std::unique_ptr<Item>, int>> Inventory)
//	: Character{ Name,IsFriendly,false,std::make_unique<Location>() }, PlayerStats{ std::move(PlayerStats) }, Money{ Money }, Inventory{ std::move(Inventory) }
//{
//
//}

EnemyPNJ::EnemyPNJ(std::string Name, std::unique_ptr<Location> enemyLocation, long MoneyDropped, std::unique_ptr<Stats> EnemyStats)
	: Character{ Name,false,true,std::move(enemyLocation) }, MoneyDropped{ MoneyDropped }, EnemyStats{ std::move(EnemyStats) }
{
}

//void EnemyPNJ::Attack(Player& P)
//{
//	//formula for dmage (ATK * 2 - enemy def) 
//	//if crit *2 multiplier
//	size_t DamageDone = (EnemyStats->GetStat(Stats::ATTACK) * 2) - (P.GetPlayerStats().GetStat(Stats::DEFENSE));
//	//roll for crit
//	bool IsCrit = false;
//	if (Random::RandomNumber(1, 100) <= P.GetPlayerStats().GetStat(Stats::CRITICAL)) {
//		std::cout << "Critical Hit !" << std::endl;
//		DamageDone *= 2;
//	}
//
//	P.ReceiveDamage(DamageDone);
//}

void EnemyPNJ::ReceiveDamage(const size_t& Amount)
{
	if (EnemyStats->GetStat(Stats::CURRENT_HEALTH) - Amount <= 0) {
		EnemyStats->SetStat(Stats::CURRENT_HEALTH, 0);
	}
	else{
		EnemyStats->SetStat(Stats::CURRENT_HEALTH, EnemyStats->GetStat(Stats::CURRENT_HEALTH) - Amount);
	}
}

const std::string& EnemyPNJ::GetDesertName()
{
	return EnemyPNJ::DesertEnemyName;
}

const std::string& EnemyPNJ::GetForestName()
{
	return EnemyPNJ::ForestEnemyName;
}

const std::string& EnemyPNJ::GetFrostEnemyName()
{
	return EnemyPNJ::FrostEnemyName;
}

const Stats& EnemyPNJ::GetEnemyStats() const
{
	return *EnemyStats;
}

const long& EnemyPNJ::GetMoneyDropped() const
{
	return this->MoneyDropped;
}

std::ostream& operator<<(std::ostream& Os, const EnemyPNJ& E)
{
	Os << "Location" << " : " << E.GetLocation().GetLocationName() << std::endl;
	Os << "Name : " << E.GetName() << std::endl;
	Os << Stats::LEVEL << " : " << E.GetEnemyStats().GetStat(Stats::LEVEL) << std::endl;
	Os << Stats::CURRENT_HEALTH << "/" << Stats::MAX_HEALTH << " : " << E.GetEnemyStats().GetStat(Stats::CURRENT_HEALTH) << "/" << E.GetEnemyStats().GetStat(Stats::MAX_HEALTH) << std::endl;
	Os << Stats::ATTACK << " : " << E.GetEnemyStats().GetStat(Stats::ATTACK) << " " << Stats::DEFENSE << " : " << E.GetEnemyStats().GetStat(Stats::DEFENSE) << " " << Stats::CRITICAL << " : " << E.GetEnemyStats().GetStat(Stats::CRITICAL) << std::endl;

	return Os;
}
