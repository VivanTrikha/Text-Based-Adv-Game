#include "Player.h"
#include <iostream>
#include <algorithm>

void Player::SetLocation(Room* room) {
    currentRoom = room;
}

Room* Player::GetLocation() const {
    return currentRoom;
}

void Player::AddItemToInventory(const Item& item) {
    if (!item.GetName().empty()) { 
        inventory.push_back(item); 
        std::cout << item.GetName() << " added to your inventory." << std::endl;
    }
}


void Player::DisplayInventory() const {
    std::cout << "Your inventory contains:" << std::endl;
    if (inventory.empty()) {
        std::cout << "Nothing" << std::endl;
    }
    else {
        for (const auto& item : inventory) {
            std::cout << "- " << item.GetName() << ": " << item.GetDescription() << std::endl;
        }
    }
}

void Player::AddQuest(const Quest& quest) {
    quests.push_back(quest);
}

void Player::UpdateQuests(const std::string& currentRoomName) {
    for (auto& quest : quests) {
        quest.update(inventory, currentRoomName);
    }
}

void Player::ListQuests() const {
    for (const auto& quest : quests) {
        quest.displayStatus();
    }
}

bool Player::HasItem(const std::string& itemName) const {
    return std::any_of(inventory.begin(), inventory.end(), [&](const Item& item) {
        return item.GetName() == itemName;
        });
}
void Player::StartQuest(const std::string& questTitle) {
    auto it = std::find_if(quests.begin(), quests.end(), [&questTitle](const Quest& quest) {
        return quest.GetTitle() == questTitle;
        });

    if (it != quests.end() && it->GetStatus() == Quest::NotStarted) {
        it->start();
    }
}
