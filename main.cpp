#include <iostream>
#include <cctype> 
#include <string>
#include "Area.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include <algorithm> 


int main() {
    Area gameWorld;
    gameWorld.LoadMapFromFile("game_map1.txt");

    Player player;
    player.SetLocation(gameWorld.GetRoom("Start Room")); 
    player.AddQuest(Quest("Find the Treasure Room", "Enter the Treasure Room with the Key.", "Key", "Treasure Room"));
    player.AddQuest(Quest("Light the Dining Room Candle", "Enter the Secret Room with the Torch", "Torch", "Dining Room"));
    player.StartQuest("Find the Treasure Room");
    player.StartQuest("Light the Dining Room Candle");
    

    
    std::string input;

    while (true) {
        Room* currentRoom = player.GetLocation();
        if (currentRoom) { 
            currentRoom->Describe(); // calls describe to print room name, description, items, and exits
        }
        else {
            std::cout << "Error: Current room is not set correctly." << std::endl;
        }

        std::cout << "\nOptions:\n1. Look around\n2. Interact with an item\n3. Move to another room\n4. Pick up an item\n5. View Inventory\n6. View Quest\n7. Quit\nEnter your choice: ";

        std::getline(std::cin, input);

        int choice = 0;
        if (!input.empty() && std::all_of(input.begin(), input.end(), [](unsigned char c) { return std::isdigit(c); })) {
            choice = std::stoi(input);
        }

        switch (choice) {
        case 1:
            // Describe
            break;
        case 2: {
            std::cout << "Enter the name of the item you want to interact with: ";
            std::getline(std::cin, input);
            const auto& items = currentRoom->GetItems();

            // Iterate through items to find the one matching the input
            auto it = std::find_if(items.begin(), items.end(), [&input](const Item& item) {
                return item.GetName() == input;
                });

            
            if (it != items.end()) {
                
                it->Interact();
            }
            else {
                
                std::cout << "Item not found." << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "Enter the direction (e.g., north, south): ";
            std::getline(std::cin, input);
            Room* nextRoom = currentRoom->GetExit(input);
            if (nextRoom && nextRoom->GetName() == "Treasure Room" && !player.HasItem("Key")) {
                std::cout << "The door is locked. You need a key to enter the Treasure Room." << std::endl;
            }
            else if (nextRoom) {
                player.SetLocation(nextRoom);
                std::cout << "Moving to " << nextRoom->GetName() << std::endl;
                player.UpdateQuests(nextRoom->GetName());
            }
            else {
                std::cout << "You can't go that way." << std::endl;
            }
            break;
        }
        
        case 4: { 
            std::cout << "Enter the name of the item you wish to pick up: ";
            std::getline(std::cin, input);
            Item item = currentRoom->TakeItem(input);
            if (!item.GetName().empty()) {
                player.AddItemToInventory(item);
                player.UpdateQuests(currentRoom->GetName());
            }
            else {
                std::cout << "Item not found in this room." << std::endl;
            }
            break;
        }
        
        case 5: 
            player.DisplayInventory();
            break;
        case 6:
            player.ListQuests();
            break;
        case 7:
            std::cout << "Exiting game..." << std::endl;
            return 0;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    
	}

    return 0;
}
