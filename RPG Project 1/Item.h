#pragma once
#include <string>
#include <iostream>

class Item
{
	friend std::ostream& operator<<(std::ostream& Os, const Item& It);
	
protected:
	
	static constexpr const char* DEFAULT_NAME = "Not defined";
	static constexpr const char* DEFAULT_RARITY = "Not defined";
	static constexpr const char* DEFAULT_DESCRIPTION = "None";
	static constexpr const int DEFAULT_ID = 0;
	static constexpr const int DEFAULT_VALUE = 0;

	static constexpr const char* NAME_LABEL = "Item name";
	static constexpr const char* RARITY_LABEL = "Rarity";
	static constexpr const char* DESCRIPTION_LABEL = "Description";
	static constexpr const char* VALUE_LABEL = "Value";
	static constexpr const char* CURRENCY = "Gold";

	const size_t Id;
	const std::string Name;
	const std::string Rarity;
	const size_t Value;
	const std::string Description;

public:
	Item(size_t Id = DEFAULT_ID, std::string Name = DEFAULT_NAME, std::string Rarity = DEFAULT_RARITY, size_t Value = DEFAULT_VALUE, std::string Description = DEFAULT_DESCRIPTION);
	
	virtual const size_t& GetId() const;
	virtual const std::string& GetName() const;
	virtual const std::string& GetRarity() const;
	virtual const size_t& GetValue() const;
	virtual const std::string& GetDescription() const;
	virtual void Display() const;
	static const char* GetCurrency();
	virtual ~Item()=default;

};

