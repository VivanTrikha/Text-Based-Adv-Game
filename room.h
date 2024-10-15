#pragma once
#include <string>
#include <vector>
#include <map>
#include "Item.h" 

class Room {
private:
    std::string name;
    std::string description;
    std::map<std::string, Room*> exits;
    std::vector<Item> items;

public:
    Room(const std::string& name, const std::string& description);
    void AddExit(const std::string& direction, Room* room);
    Room* GetExit(const std::string& direction) const;
    void AddItem(const Item& item);
    void Describe() const;
    void DisplayExits() const;
    std::string GetName() const;
    std::string GetDescription() const;
    const std::map<std::string, Room*>& GetExits() const;
    const std::vector<Item>& GetItems() const;
    Item TakeItem(const std::string& itemName);

};
