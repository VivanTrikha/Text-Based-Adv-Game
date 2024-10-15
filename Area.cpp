#include "Area.h"
#include <fstream>
#include <sstream>

Area::~Area() {
    for (auto& pair : rooms) {
        delete pair.second;
    }
}

void Area::AddRoom(const std::string& name, Room* room) {
    rooms[name] = room;
}

Room* Area::GetRoom(const std::string& name) const {
    auto it = rooms.find(name);
    if (it != rooms.end()) return it->second;
    return nullptr;
}

void Area::LoadMapFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string roomName, description, attributes;
        std::getline(iss, roomName, '|');
        std::getline(iss, description, '|');

        // creating the room with its name and description
        Room* room = new Room(roomName, description);
        AddRoom(roomName, room);

        
        while (std::getline(iss, attributes, '|')) {
            std::istringstream attrStream(attributes);
            std::string key, value;
            std::getline(attrStream, key, '=');
            std::getline(attrStream, value);

            if (key == "item") {
                
                std::istringstream itemStream(value);
                std::string itemName, itemDescription;
                std::getline(itemStream, itemName, ':');
                std::getline(itemStream, itemDescription);
                room->AddItem(Item(itemName, itemDescription));
            }
            else {
                
                exitInfos.push_back({ roomName, value, key });
            }
        }
    }
    file.close();

    // connect rooms based on stored exit information
    for (const auto& exitInfo : exitInfos) {
        Room* fromRoom = GetRoom(exitInfo.fromRoom);
        Room* toRoom = GetRoom(exitInfo.toRoom);
        if (fromRoom && toRoom) {
            fromRoom->AddExit(exitInfo.direction, toRoom);
        }
    }
}
