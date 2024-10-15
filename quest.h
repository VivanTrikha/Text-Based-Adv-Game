#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"

class Quest {
public:
    enum Status { NotStarted, InProgress, Completed };
private:

    std::string title;
    std::string description;
    std::string requiredItem;
    std::string targetRoom;
    Status status;
public:
    Quest(const std::string& title, const std::string& description,
        const std::string& requiredItem, const std::string& targetRoom)
        : title(title), description(description),
        requiredItem(requiredItem), targetRoom(targetRoom), status(NotStarted) {}

    void start() {
        if (status == NotStarted) {
            status = InProgress;
            std::cout << "Quest started: " << title << std::endl;
        }
    }

    void update(const std::vector<Item>& inventory, const std::string& currentRoomName) {
        if (status == InProgress && std::find_if(inventory.begin(), inventory.end(), [&](const Item& item) {
            return item.GetName() == requiredItem;
            }) != inventory.end() && currentRoomName == targetRoom) {
            complete();
        }
    }

    void complete() {
        status = Completed;
        std::cout << "Quest completed: " << title << std::endl;
    }

    void displayStatus() const {
        std::string statusStr;
        switch (status) {
        case NotStarted: statusStr = "Not Started"; break;
        case InProgress: statusStr = "In Progress"; break;
        case Completed: statusStr = "Completed"; break;
        }
        std::cout << "Quest: " << title << " - " << statusStr << std::endl;
    }
    const std::string& GetTitle() const { return title; }
    Status GetStatus() const { return status; }
};
