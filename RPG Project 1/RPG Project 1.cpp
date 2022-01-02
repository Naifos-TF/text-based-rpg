// RPG Project 1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Stats.h"
#include "Item.h"
#include "Consumable.h"
#include "Player.h"
#include "Game.h"
#include "Items_Util.h"
void TestLigne(const std::string& name);
void Test();

int main()
{
   //Test();
    Game G = Game();
    G.Start();

}

void Test() {
    ////Test classe Stat
    //TestLigne("Stat");
    //Stats Empty = Stats();
    //Empty.SetStat(Stats::ATTACK, 100);
    //Empty.Display();
    //Empty.SetStat("Random", 200);
    //Empty.Display();
    //Empty.SetStat(Stats::CRITICAL, 2);
    //Empty.Display();
    //TestLigne("End Stat");



    ////Test class Item
    //TestLigne("Item");
    //Item i = Item();
    //std::cout << i;
    //std::cout << std::endl;
    //Item i2 = Item(1, "SWORD OF ARTHAS", "LEGENDARY", 4999, "'Very cold.'");
    //i2.Display();
    //TestLigne("End Item");

    ////Test class Consumable
    //TestLigne("Consumable");
    //Consumable cons = Consumable();
    //cons.Display();
    //std::cout << std::endl;
    //Stats HealthPotionStats = Stats(std::map< std::string, size_t> {
    //    {Stats::MAX_HEALTH, static_cast<size_t>(20)}
    //});
    //Consumable HealthPotion = Consumable(2, "Health Potion", "Common", 10, "'Add 20 Health'", HealthPotionStats);
    //HealthPotion.Display();
    //HealthPotion.Use();
    //HealthPotion.Use();
    //TestLigne("End Consumable");

    //TestLigne("Player");

    //std::unique_ptr<Stats> s1 = std::make_unique<Stats>(Empty);
    //std::unique_ptr<Item> it1 = std::make_unique<Item>(i2);

    //std::map<std::unique_ptr<Item>, int > m1;
    //m1.insert(std::make_pair(std::move(it1), 1));



    //std::unique_ptr<std::map<std::unique_ptr<Item>, int>> inv = std::make_unique<std::map<std::unique_ptr<Item>, int >>(std::move(m1));

    //std::unique_ptr<Player> p1 = std::make_unique<Player>();
    //std::cout << p1 << std::endl;
    //std::unique_ptr<Player> p2 = std::make_unique<Player>("Sofian", true, std::move(s1), 1000, std::move(inv));
    //std::cout << p2 << std::endl;
    ////std::cout << p2->GetPlayerStats().GetStat(Stats::CRITICAL) << std::endl;
    //p2->SetPlayerStats(Stats::CRITICAL, 50);
    //std::cout << p2 << std::endl;
    //TestLigne("End Player");

    //TestLigne("Game");
    //Game g = Game();
    ////g.DisplayItems();
    //TestLigne("End Game");

    //TestLigne("Items util");
    //std::shared_ptr<Consumable> c = Items_Util::CreateConsumable("Health Potion");
    //std::shared_ptr<Consumable> c2 = Items_Util::CreateConsumable("Greater Health Potion");
    //Items_Util::CreateConsumable("Z");
    //Items_Util::CreateConsumable("Town Scroll");
    //TestLigne("End Items util");
    //TestLigne("Game");
    //Game G1 = Game();
    //G1.Start();
    //std::unique_ptr<Player> p3 = std::make_unique<Player>();
    //std::cout << *p3 <<std::endl;
    //p3->Move(std::make_unique<Location>("Shop"));
    //std::cout << *p3 << std::endl;
    //TestLigne("End game");

}
void TestLigne(const std::string& name) {
    std::cout << " ------------------------------------- " << name << " ------------------------------------- " << std::endl;
    std::cout << std::endl;
}
