#pragma once
#include "Item.h"
class Weapon :
    public Item
{
private:

public:
	enum class WeaponItems {
		RustySword,
		FineSword,
		GreatSword,
		DarkSword,
		ForgottenSword
	};
};

