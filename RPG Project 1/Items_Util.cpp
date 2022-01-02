#include "Items_Util.h"
#include "Game.h"

std::shared_ptr<Consumable> Items_Util::CreateConsumable(std::string ItemName)
{
    auto it = Game::GetListOfConsumables().find(ItemName);
    if (it != Game::GetListOfConsumables().end()) {
        auto it2 = it->second;
        std::string Rarity = std::get<0>(it2);
        std::string Description = std::get<1>(it2);
        size_t Id = std::get<2>(it2);
        size_t Value = std::get<3>(it2);
        Stats St = std::get<4>(it2);
        //std::cout <<it->first<<" " << Rarity << " " << Description << " " << Id << " " << Value << " " << std::endl;
        //St.Display();
        return std::make_shared<Consumable>(Id,ItemName,Rarity,Value,Description,St);
        //throw ConsumableCreationFailedException
    }
    else {
        std::cerr << "Creation of Consumable '" << ItemName << "'failed. No such Object." << std::endl;
        return nullptr;
        //throw ConsumableNameNotFoundException
    }
}

//std::unique_ptr<Weapon> Items_Util::CreateWeapon(std::string ItemName)
//{
//    return std::unique_ptr<Weapon>();
//}

