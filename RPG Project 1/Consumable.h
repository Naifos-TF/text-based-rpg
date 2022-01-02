#pragma once
#include "Item.h"
#include "Stats.h"

class Consumable :
    public Item
{
private:
    Stats BoostedStats;
    bool Used;
public:

    Consumable(size_t Id = DEFAULT_ID, std::string Name = DEFAULT_NAME, std::string Rarity = DEFAULT_RARITY, size_t Value = DEFAULT_VALUE, std::string Description = DEFAULT_DESCRIPTION, Stats BoostedStats = Stats());

    virtual void Display() const override;
    virtual const size_t& GetId() const override;
    virtual const std::string& GetName() const override;
    virtual const std::string& GetRarity() const override;
    virtual const size_t& GetValue() const override;
    virtual const std::string& GetDescription() const override;
    void Use();//sets used to true if not already true
    void SetUse(const bool& Used);
    virtual ~Consumable() = default;
};

