#pragma once

#include <string>
#include <iostream>

class Item {
private:
    std::string name;
    std::string description;

public:
    Item(const std::string& name, const std::string& description) : name(name), description(description) {}

    void Interact() const {
        std::cout << "You interact with the " << name << ": " << description << std::endl;
    }

    std::string GetName() const { return name; }
    std::string GetDescription() const { return description; }
};
