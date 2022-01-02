#include "Character.h"



Character::Character(std::string Name, bool IsFriendly, bool IsFighting, std::unique_ptr<Location> Loc)
	: Name{ Name }, IsFriendly{ IsFriendly }, IsFighting{ IsFighting }, CharacterLocation{std::move(Loc)}
{

}

const std::string& Character::GetName() const
{
	return this->Name;
}

const bool& Character::GetIsFriendly() const
{
	return this->IsFriendly;
}

const Location& Character::GetLocation() const
{
	return *CharacterLocation;
}


const bool& Character::GetIsFighting() const
{
	return this->IsFighting;
}

void Character::SetIsFighting(const bool& IsFighting)
{
	this->IsFighting = IsFighting;
}

void Character::SetLocation(std::unique_ptr<Location> NewLocation)
{
	this->CharacterLocation = std::move(NewLocation);
}

void Character::SetName(const std::string& Name)
{
	this->Name = Name;
}

void Character::SetIsFriendly(const bool& b)
{
	IsFriendly = b;
}
