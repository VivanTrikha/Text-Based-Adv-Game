#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>  
#include <sstream>  
#include "Room.h"   

// Struct for holding exit information
struct ExitInfo {
    std::string fromRoom;
    std::string toRoom;
    std::string direction;
};

class Area {
private:
    std::map<std::string, Room*> rooms;
    std::vector<ExitInfo> exitInfos;

public:
    ~Area();
    void AddRoom(const std::string& name, Room* room);
    Room* GetRoom(const std::string& name) const;
    void LoadMapFromFile(const std::string& filename);
};
