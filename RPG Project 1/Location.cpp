#include "Location.h"

/* Init of List of locations and their type*/
constexpr const char* TYPE_TOWN = "Town";
constexpr const char* TYPE_WILD = "Wild";
constexpr const char* TYPE_SHOP = "Shop";
constexpr const char* TYPE_INN = "Inn";
constexpr const char* TYPE_BANK = "Bank";

const std::map<std::string, std::string>& tmp = {
	std::make_pair("Harujmarr", TYPE_TOWN),
	std::make_pair("The Misty Forest", TYPE_WILD),
	std::make_pair("Desert Ruins", TYPE_WILD),
	std::make_pair("Ice Lands", TYPE_WILD),
	std::make_pair("Shop", TYPE_SHOP),
	std::make_pair("Bank", TYPE_BANK),
	std::make_pair("Inn", TYPE_INN)
};

std::unique_ptr<std::map<std::string, std::string>> Location::LocationAndType = std::make_unique<std::map<std::string, std::string>>(tmp);

Location::Location(std::string Name)
	: Name{Name}
{
	auto it = LocationAndType->find(Name);
	if (it != LocationAndType->end())
		Type = it->second;
	else
		Type = "Unknown";
		//throw err
}

//Location::Location(std::string Name,std::string Type)
//	: Name{Name}, Type{Type}
//{
//}

const std::string& Location::GetLocationName() const
{
	return this->Name;
}

const std::string& Location::GetLocationType() const
{
	return this->Type;
}


//returns an const int& corresponding to the type so it's usable in a switch statement
const int& Location::GetLocationTypeToInt() const
{
	if (this->Type == TYPE_TOWN)
		return 0;
	if (this->Type == TYPE_WILD)
		return 1;
	if (this->Type == TYPE_SHOP)
		return 2;
	if (this->Type == TYPE_INN)
		return 3;
	if (this->Type == TYPE_BANK)
		return 4;

	return 0;
}


void Location::SetLocationName(const std::string& Name)
{
	this->Name = Name;
}

void Location::SetLocationType(const std::string& Type)
{
	this->Type = Type;
}

std::ostream& operator<<(std::ostream& Os, const Location& Loc)
{
	Os << Loc.Name<<std::endl;
	return Os;
}

const char* Location::GetTheMistyForestName() {
	return Location::TheMistyForestName;
}
const char* Location::GetDesertRuinsName() {
	return Location::DesertRuinsName;
}
const char* Location::GetIceLandsName() {
	return Location::IceLandsName;
}
const char* Location::GetShopName() {
	return Location::ShopName;
}
const char* Location::GetInnName() {
	return Location::InnName;
}