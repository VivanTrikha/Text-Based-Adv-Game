#include "room.h"
Room::Room(const std::string& name, const std::string& description)
    : name(name), description(description) {}


void Room::AddExit(const std::string& direction, Room* room) {
    exits[direction] = room;
}

Room* Room::GetExit(const std::string& direction) const {
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    }
    return nullptr;
}

void Room::AddItem(const Item& item) {
    items.push_back(item);
}

const std::map<std::string, Room*>& Room::GetExits() const { return exits; }
const std::vector<Item>& Room::GetItems() const { return items; }

std::string Room::GetDescription() const { return description; }
std::string Room::GetName() const { return name; }

void Room::DisplayExits() const {
    std::cout << "From " << name << ", you can go: ";
    for (const auto& exit : exits) {
        std::cout << exit.first << " ";
    }
    std::cout << std::endl;
}

void Room::Describe() const {
    std::cout << "Current Location: " << GetName() << std::endl;
    std::cout << GetDescription() << std::endl;
    std::cout << "Items in the room:" << std::endl;
    if (GetItems().empty()) {
        std::cout << "- None" << std::endl;
    }
    else {
        for (const auto& item : GetItems()) {
            std::cout << "- " << item.GetName() << ": " << item.GetDescription() << std::endl;
        }
    }
    DisplayExits();
}
Item Room::TakeItem(const std::string& itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->GetName() == itemName) {
            Item takenItem = *it;
            items.erase(it);
            std::cout << itemName << " has been taken." << std::endl;
            return takenItem;
        }
    }
    return Item("", ""); // return an empty item if not found
}
