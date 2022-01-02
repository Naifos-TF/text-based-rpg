#include<iostream>
#include "Stats.h"

Stats::Stats(std::map <std::string, size_t> StatsValue)
	: StatsValue{StatsValue}
{
}

//Stats::Stats(Stats&& source)
//	:	StatsValue{source.StatsValue}
//{
//}



//Stats::Stats(std::string StatName, int StatValue)
//	: StatsValue{std::map<std::string, int> {
//						{StatName,StatValue}
//					}
//				}
//{
//}

const size_t& Stats::GetStat(const std::string& StatName) const
{

	auto it = StatsValue.find(StatName);

	if (it != StatsValue.end()) {
		//std::cout << it->first << " : " << it->second << std::endl;
		return it->second;
	}
	//change to throw excep
	else {
		std::cerr << "Stat not found!" << std::endl;
		return 0;
	}
}

const std::map<std::string, size_t>& Stats::GetAllStats() const
{
	return this->StatsValue;
}



void Stats::SetStat(const std::string& StatName,const size_t& Value)
{
	
	if (StatNameIsAllowed(StatName)) {
		auto it = StatsValue.find(StatName);

		if (it != StatsValue.end())
			this->StatsValue[StatName] = Value;
		else
			StatsValue.insert(std::make_pair(StatName, Value));
	}
	else
		std::cerr << "Stat name not allowed" << std::endl;
}

void Stats::SetStat(const std::string& StatName,const size_t&& Value)
{
	if (StatNameIsAllowed(StatName)) {
		auto it = StatsValue.find(StatName);

		if (it != StatsValue.end())
			this->StatsValue[StatName] = Value;
		else
			StatsValue.insert(std::make_pair(StatName, Value));
	}
	else
		std::cerr << "'" << StatName << "' as a stat name is not allowed" << std::endl;
}

void Stats::Display() const
{
	for (const auto& stat : StatsValue) {
		std::cout << stat.first << " : " << stat.second << std::endl;
	}

}

const bool Stats::StatNameIsAllowed(const std::string& StatName) const {
	for (const auto& val : Stats::AllowedStatName) {
		if (StatName == val)
			return true;
	}
	return false;
}
