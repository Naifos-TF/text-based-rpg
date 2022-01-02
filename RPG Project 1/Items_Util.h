#pragma once
#include <array>
#include <set>
#include "Consumable.h"
#include "Weapon.h"
#include <unordered_map>
class Items_Util
{
private:
public:
	static std::shared_ptr<Consumable> CreateConsumable(std::string ItemName);
	//static std::shared_ptr<Weapon> CreateWeapon(std::string ItemName);
	static constexpr const char* HEALTH_POTION = "Health Potion";
};

