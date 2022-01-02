#pragma once
#include <string>
#include <iostream>
#include <map>
#include <memory>

class Location
{
	friend std::ostream& operator<<(std::ostream& Os, const Location& Loc);

private:
	std::string Name;
	std::string Type;//town, road..

	static constexpr const char* TYPE_TOWN = "Town";
	static constexpr const char* DEFAULT_LOCATION = "Harujmarr";
	static std::unique_ptr<std::map<std::string, std::string> > LocationAndType;
public:
	//Location(std::string Name=DEFAULT_LOCATION, std::string Type= TYPE_TOWN);
	static constexpr const char* TheMistyForestName = "The Misty Forest";
	static constexpr const char* DesertRuinsName = "Desert Ruins";
	static constexpr const char* IceLandsName = "Ice Lands";
	static constexpr const char* ShopName = "Shop";
	static constexpr const char* InnName = "Inn";
	static constexpr const char* BankName = "Bank";

	Location(std::string Name = DEFAULT_LOCATION);
	virtual const std::string& GetLocationName() const;
	virtual const std::string& GetLocationType() const;
	virtual const int& GetLocationTypeToInt() const;
	virtual void SetLocationName(const std::string& Name);
	virtual void SetLocationType(const std::string& Type);
	static const char* GetTheMistyForestName();
	static const char* GetDesertRuinsName();
	static const char* GetIceLandsName();
	static const char* GetShopName();
	static const char* GetInnName();

	~Location() = default;
};

