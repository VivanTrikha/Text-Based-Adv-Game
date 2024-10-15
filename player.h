#pragma once
#include "Room.h"
#include "Item.h" 
#include <vector>
#include "Quest.h"

class Player {
private:
    Room* currentRoom = nullptr;
    std::vector<Item> inventory;
    std::vector<Quest> quests; 

public:
    Player() = default;

    void SetLocation(Room* room); 
    Room* GetLocation() const;
    void AddItemToInventory(const Item& item); 
    void DisplayInventory() const; 
    void AddQuest(const Quest& quest); 
    void UpdateQuests(const std::string& currentRoomName);
    void ListQuests() const;
    void StartQuest(const std::string& questTitle);

    bool HasItem(const std::string& itemName) const;
};
