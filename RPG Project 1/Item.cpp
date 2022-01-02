#include "Item.h"

Item::Item(size_t Id, std::string Name, std::string Rarity, size_t Value, std::string Description)
    : Id{ Id }, Name{ Name }, Rarity{Rarity}, Value{Value}, Description{Description}
{
}

const size_t& Item::GetId() const
{
    return this->Id;
}

const std::string& Item::GetName() const
{
    return this->Name;
}

const std::string& Item::GetRarity() const
{
    return this->Rarity;
}

const size_t& Item::GetValue() const
{
    return this->Value;
}

const std::string& Item::GetDescription() const
{
    return this->Description;
}

void Item::Display() const
{
    std::cout << Item::NAME_LABEL<< " : " << this->Name << std::endl;
    std::cout << Item::RARITY_LABEL << " : " << this->Rarity << std::endl;
    std::cout << Item::DESCRIPTION_LABEL << " : " << this->Description << std::endl;
    std::cout << Item::VALUE_LABEL << " : " <<  this->Value <<" " << Item::CURRENCY << std::endl;
}

const char* Item::GetCurrency()
{
    return CURRENCY;
}

std::ostream& operator<<(std::ostream& Os, const Item& It)
{
    Os << Item::NAME_LABEL << " : " <<  It.Name << std::endl;
    Os << Item::RARITY_LABEL << " : " <<  It.Rarity << std::endl;
    Os << Item::DESCRIPTION_LABEL << " : " <<  It.Description << std::endl;
    Os << Item::VALUE_LABEL << " : " <<  It.Value << " " << Item::CURRENCY <<std::endl;
    return Os;
}
