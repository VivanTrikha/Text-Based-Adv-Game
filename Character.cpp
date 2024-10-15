#include "Character.h"
#include <algorithm> 

// Constructor
Character::Character(const std::string& name, int health) : name(name), health(health) {}

// Virtual destructor to allow for inheritance
Character::~Character() {}

// Add an item to the character's inventory
void Character::AddItemToInventory(const Item& item) {
    inventory.push_back(item);
}

// Remove an item from the character's inventory by name
void Character::RemoveItemFromInventory(const std::string& itemName) {
    inventory.erase(
        std::remove_if(inventory.begin(), inventory.end(), [&itemName](const Item& item) {
            return item.GetName() == itemName;
            }),
        inventory.end());
}

// Interact with an item in the character's inventory by name
void Character::InteractWithItem(const std::string& itemName) {
    auto it = std::find_if(inventory.begin(), inventory.end(), [&itemName](const Item& item) {
        return item.GetName() == itemName;
        });

    if (it != inventory.end()) {
        it->Interact();
    }
    else {
        std::cout << name << " does not have an item named " << itemName << std::endl;
    }
}

// Get the character's name
std::string Character::GetName() const {
    return name;
}

// Get the character's health
int Character::GetHealth() const {
    return health;
}

// Set the character's health
void Character::SetHealth(int newHealth) {
    health = newHealth;
}
