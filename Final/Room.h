#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>

class Room {
    private:
        std::string name;
        std::map<std::string, Room*> exits;
        bool hasMonster;
        bool hasPrincess;
    public:
        Room(std::string name);
        std::string getName();
        bool ifHasMonster();
        bool ifHasPrincess();
        std::map<std::string, Room*> getExits();
        void setMonster();
        void setPrincess();
        void setExits(std::string dir, Room* room);
};

#endif