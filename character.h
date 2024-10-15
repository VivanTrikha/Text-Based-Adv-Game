#pragma once

#include <string>
#include <vector>
#include "Item.h" 

class Character {
protected:
    std::string name;
    int health;
    std::vector<Item> inventory;

public:
    Character(const std::string& name, int health);
    virtual ~Character();

    void AddItemToInventory(const Item& item);
    void RemoveItemFromInventory(const std::string& itemName);
    void InteractWithItem(const std::string& itemName);
    std::string GetName() const;
    int GetHealth() const;
    void SetHealth(int newHealth);
};


