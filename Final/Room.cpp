#include "Room.h"

Room::Room(std::string name) : name(name), hasMonster(false), hasPrincess(false) {}

std::string Room::getName(){
    return this->name;
}

bool Room::ifHasMonster(){
    return this->hasMonster;
}

bool Room::ifHasPrincess(){
    return this->hasPrincess;
}

std::map<std::string, Room*> Room::getExits() {
    return exits;
}

void Room::setMonster(){
    this->hasMonster = true;
}

void Room::setPrincess(){
    this->hasPrincess = true;
}

void Room::setExits(std::string dir, Room* room){
    this->exits[dir] = room;
}