#pragma once
#include "Character.h"
#include "Stats.h"
#include "Item.h"
#include "Location.h"
#include "Random.h"
#include "Item.h"

class Player :
    public Character
{
    friend std::ostream& operator<<(std::ostream& Os, const Player& P);

private:
    std::unique_ptr<Stats> PlayerStats;
    std::shared_ptr<std::map<std::shared_ptr<Item>, int>> Inventory;
    long long BankMoney;
    long long Money;
    
    //Lvl 1 stats for player
    static constexpr long long DEFAULT_MONEY = 100;
    static constexpr size_t       DEFAULT_MAX_HEALTH = 50;
    static constexpr size_t       DEFAULT_CURRENT_HEALTH = DEFAULT_MAX_HEALTH;
    static constexpr size_t       DEFAULT_ENERGY = 10;
    static constexpr size_t       DEFAULT_ATTACK = 5;
    static constexpr size_t       DEFAULT_DEFENSE = 5;
    static constexpr size_t       DEFAULT_CRITICAL = 1;
    static constexpr size_t       DEFAULT_LEVEL = 1;
    static constexpr size_t       DEFAULT_EXPERIENCE = 0;

    //static const std::map<size_t, size_t> MapLevelExp;

    static constexpr const char* DEFAULT_NAME = "Isaac";

    void LevelUp();

public:
    Player(
        std::string Name = DEFAULT_NAME, 
        bool IsFriendly = DEFAULT_ISFRIENDLY,
        std::unique_ptr<Stats> PlayerStats=std::make_unique<Stats>(
            Stats(
                std::map <std::string, size_t>{
                    { Stats::CURRENT_HEALTH, DEFAULT_MAX_HEALTH },
                    { Stats::MAX_HEALTH, DEFAULT_MAX_HEALTH },
                    { Stats::ENERGY, DEFAULT_ENERGY },
                    { Stats::ATTACK, DEFAULT_ATTACK },
                    { Stats::DEFENSE, DEFAULT_DEFENSE },
                    { Stats::CRITICAL, DEFAULT_CRITICAL },
                    { Stats::LEVEL, DEFAULT_LEVEL },
                    { Stats::EXPERIENCE, DEFAULT_EXPERIENCE }
                }
           )
        ),
        long long Money = DEFAULT_MONEY,
        std::shared_ptr<std::map<std::shared_ptr<Item>, int>> Inventory = std::make_unique<std::map<std::shared_ptr<Item>, int>>()
    );

    virtual const std::string& GetName() const override;
    virtual const bool& GetIsFriendly() const override;
    virtual const Location& GetLocation() const override;
    virtual const Stats& GetPlayerStats() const;
    virtual const long long& GetMoney() const;
    virtual const long long& GetBankMoney() const;
    virtual const std::map<std::shared_ptr<Item>, int> GetInventory() const;

    virtual void DisplayStats() const;

    virtual void SetName(const std::string& Name) override;
    virtual void SetIsFriendly(const bool& b) override;
    virtual void SetLocation(std::unique_ptr<Location> NewLocation) override;
    virtual void SetPlayerStats(const std::string& StatName, const size_t& value);
    virtual void SetIsFighting(const bool& IsFighting) override;

    

    virtual void AddMoney(const size_t& amount);
    virtual void SetMoney(const long long& amount);

    virtual void AddItem(std::shared_ptr<Item> It);
    virtual void RemoveItem(std::shared_ptr<Item>It);
    virtual void BuyItem(std::shared_ptr<Item> It);
    virtual void SellItem(std::shared_ptr<Item>It);
    virtual void UseItem(std::shared_ptr<Item>It);
    virtual const size_t CountNumberOfItem(std::shared_ptr<Item>It)const;
    virtual const size_t CountNumberOfItem(std::string ItemName) const;

    virtual void Explore();
    virtual void Move(std::unique_ptr<Location> NewLocation);

    virtual void AddXP(const size_t& Amount);
    void CheckLevelUp();

    virtual void ReceiveDamage(const size_t& Amount);

    void Withdraw(const size_t& Amount);
    void Deposit(const size_t& Amount);

    ~Player() = default;
};

