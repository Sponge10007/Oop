#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <ctime>
#include <cstdlib>
#include "geneRoom.h"
#include "Room.h"

std::vector<Room*> mapGenerator::generate(int min_rooms) {
    srand(time(0));
    // 生成初始大厅
    Room* lobby = new Room("Main-Lobby");
    rooms.push_back(lobby);
    std::stack<Room*> room_stack;
    room_stack.push(lobby);
    
    // 深度优先生成基础结构
    while(rooms.size() < min_rooms && !room_stack.empty()) {
        Room* current = room_stack.top();
        room_stack.pop();
        // 为当前房间随机添加1-3个新出口
        int new_exits = rand()%3 + 1;
        for(int i=0; i<new_exits && rooms.size()<min_rooms; i++) {
            
            // 获取可用方向（使用类成员directions）
            std::vector<std::string> available_dirs;
            for(auto& d : dirs) {  // 使用类成员变量directions
                if(current->getExits()[d] == 0) { //map查找时如果查不到会返回0,查找还没有被连接的方向
                    available_dirs.push_back(d);
                }
            }
            
            if(available_dirs.empty()) continue;
            // 随机选择方向并创建房间
            std::string dir = available_dirs[rand()%available_dirs.size()];
            Room* new_room = new Room(geneUniqueName());
            current->setExits(dir, new_room);  // 使用Room类的setExit方法
            new_room->setExits(reverse[dir], current); // 每当连接一个房间，实施一次反向连接
            rooms.push_back(new_room);
            room_stack.push(new_room);
        }
    }

    // 添加随机循环路径
    for(int i=0; i<rooms.size()*2; i++) {
        Room* a = rooms[rand()%rooms.size()];
        Room* b = rooms[rand()%rooms.size()];
        
        std::vector<std::string> available_dirs;
        for(auto& d : dirs) {  // 使用类成员directions
            if(a->getExits()[d] == 0) {
                available_dirs.push_back(d);
            }
        }
        
        if(!available_dirs.empty() && a != b) {
            std::string dir = available_dirs[rand()%available_dirs.size()];
            a->setExits(dir, b);  // 使用Room类的setExit方法
            b->setExits(reverse[dir], a);
        }
    }
    
    printMap();
    return rooms;
}

bool mapGenerator::isNameUnique(std::string name) {
    for(auto& r : rooms) 
        if(r->getName() == name) return false;
    return true;
}

std::string mapGenerator::geneUniqueName() {
    int counter = 0;
    std::string name;
    do {
        name = room_types[rand()%room_types.size()] + "-" + std::to_string(++counter);
    } while(!isNameUnique(name));
    return name;
}

void mapGenerator::printMap() {
    for(auto& room : rooms) {
        std::cout << "[" << room->getName() << "]\nExits: ";
        for(auto& exit : room->getExits())
            std::cout << exit.first << "->" << exit.second->getName() << "  ";
        std::cout << "\n\n";
    }
}