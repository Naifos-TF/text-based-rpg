#include "Consumable.h"

Consumable::Consumable(size_t Id, std::string Name, std::string Rarity, size_t Value, std::string Description, Stats BoostedStats)
	: Item{ Id,Name,Rarity,Value,Description }, BoostedStats{ BoostedStats }, Used{false}
{
}

void Consumable::Display() const
{
	return Item::Display();
}

const size_t& Consumable::GetId() const
{
	return Item::GetId();
}

const std::string& Consumable::GetName() const
{
	return Item::GetName();
}

const std::string& Consumable::GetRarity() const
{
	return Item::GetRarity();
}

const size_t& Consumable::GetValue() const
{
	return Item::GetValue();
}

const std::string& Consumable::GetDescription() const
{
	return Item::GetDescription();
}

void Consumable::Use()
{
	std::cout << std::endl;
	if(this->Used == false){
		this->SetUse(true);
	}
	else
		std::cout << "You can't use " << this->Name << ". It has already been used ! " << std::endl;
	std::cout << std::endl;
}

void Consumable::SetUse(const bool& Used)
{
	this->Used = Used;
}

