#pragma once
#include <string>
#include <iostream>
#include "Location.h"
#include <map>

class Character
{
private:

protected:
	std::string Name;
	bool IsFriendly;
	bool IsFighting;
	std::unique_ptr<Location> CharacterLocation;

	static constexpr const char* DEFAULT_NAME = "Unknown";
	static constexpr const bool DEFAULT_ISFRIENDLY = true;
	static constexpr const bool DEFAULT_ISFIGHTING = false;

	static constexpr const char* Locations[] = {
		"Virmilos",
		"Beruk",
		"Harujmarr",
		"Spagha",
		"The misty forest",
		"Desert ruins",
		"Ice road",
		"Shop",
		"Inn"
	};

	//static std::map<std::string, std::string> LocationAndType;

public:
	Character(
		std::string Name = DEFAULT_NAME,
		bool IsFriendly = DEFAULT_ISFRIENDLY,
		bool IsFighting = DEFAULT_ISFIGHTING,
		std::unique_ptr<Location> CharacterLocation = std::make_unique<Location>()
	);

	virtual const std::string& GetName() const;
	virtual const bool& GetIsFriendly() const;
	virtual const Location& GetLocation() const;
	virtual const bool& GetIsFighting() const;
	virtual void SetIsFighting(const bool& IsFighting);
	virtual void SetLocation(std::unique_ptr<Location> NewLocation);
	virtual void SetName(const std::string& Name);
	virtual void SetIsFriendly(const bool& b);
	virtual ~Character() = default;
};

