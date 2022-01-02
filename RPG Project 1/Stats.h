#pragma once
#include <string>
#include <set>
#include <map>
#include <vector>
class Stats
{
private :

	 std::map< std::string, size_t>  StatsValue;// mapping a stat name with its value 
	 const bool StatNameIsAllowed(const std::string& StatName) const;
public:

	static constexpr size_t DEFAULT_STAT = 0;
	//default labels
	static constexpr const char* CURRENT_HEALTH = "CURRENT HEALTH";
	static constexpr const char* MAX_HEALTH = "MAX HEALTH";
	static constexpr const char* ENERGY = "ENERGY";
	static constexpr const char* ATTACK = "ATK";
	static constexpr const char* DEFENSE = "DEF";
	static constexpr const char* CRITICAL = "CRIT";
	static constexpr const char* LEVEL = "LVL";
	static constexpr const char* EXPERIENCE = "XP";

	

	static constexpr const char* AllowedStatName[]{CURRENT_HEALTH,MAX_HEALTH,ENERGY,ATTACK,DEFENSE,CRITICAL,LEVEL,EXPERIENCE};

	Stats(std::map <std::string, size_t> StatsValue = {
		{CURRENT_HEALTH, DEFAULT_STAT},
		{MAX_HEALTH, DEFAULT_STAT},
		{ENERGY, DEFAULT_STAT},
		{ATTACK, DEFAULT_STAT},
		{DEFENSE, DEFAULT_STAT},
		{CRITICAL, DEFAULT_STAT},
		{LEVEL, DEFAULT_STAT},
		{EXPERIENCE, DEFAULT_STAT},
	});

	/*Stats(Stats&& source);*/

	const size_t& GetStat(const std::string& StatName) const;
	const std::map<std::string, size_t>& GetAllStats() const;

	void SetStat(const std::string& StatName,const size_t& Value);
	void SetStat(const std::string& StatName,const size_t&& Value);

	void Display() const;//Display all stats
	void DisplayHealth() const;
};

