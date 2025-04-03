#ifndef GENEROOM_H
#define GENEROOM_H

#include "Room.h"
#include <vector>

class mapGenerator {
    private:
        std::vector<std::string> dirs = {"north", "south", "west", "east", "up", "down"};
        std::vector<std::string> room_types = {"Lobby", "Hall", "Chamber", "Dungeon", "Tower",
                                                "Kitchen", "Armory", "Library", "Cellar", "Gallery"};
        std::vector<Room*>rooms;
        std::map<std::string, std::string> reverse = {{"west", "east"}, {"east", "west"}, {"south", "north"}, 
                                                        {"north", "south"}, {"up", "down"}, {"down", "up"}};
        std::string geneUniqueName();
        bool isNameUnique(std::string name);
    public:
        std::vector<Room*> generate(int min_nums);
        void printMap();
};

#endif