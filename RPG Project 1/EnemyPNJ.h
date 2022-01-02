#pragma once
#include "Character.h"
#include "Stats.h"
#include <string>

class EnemyPNJ :
    public Character
{
    friend std::ostream& operator<<(std::ostream& Os, const EnemyPNJ& E);
private:
        std::unique_ptr<Stats> EnemyStats;
        long MoneyDropped;
public:
    EnemyPNJ(
        std::string Name, 
        std::unique_ptr<Location> EnemyLocation, 
        long MoneyDropped, 
        std::unique_ptr<Stats> EnemyStats
      );

    static constexpr const char* DesertEnemyName = "Desert Bandit";
    static constexpr const char* ForestEnemyName = "Forest Bandit";
    static constexpr const char* FrostEnemyName = "Frost Bandit";

    //void Attack(Player& P);
    void ReceiveDamage(const size_t& Amount);

    static const std::string& GetDesertName();
    static const std::string& GetForestName();
    static const std::string& GetFrostEnemyName();

    const Stats& GetEnemyStats() const;
    const long& GetMoneyDropped() const;
    ~EnemyPNJ() = default;
};

