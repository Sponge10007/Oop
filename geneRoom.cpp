#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Room {
    string name;
    map<string, Room*> exits;
    
    Room(const string& name) : name(name) {}
};

class CastleGenerator {
private:
    vector<string> directions = {"north", "south", "east", "west", "up", "down"};
    vector<string> room_types = {"Lobby", "Hall", "Chamber", "Dungeon", "Tower", 
                               "Kitchen", "Armory", "Library", "Cellar", "Gallery"};
    
    string generateUniqueName() {
        static int counter = 0;
        string name;
        do {
            name = room_types[rand()%room_types.size()] + "-" + to_string(++counter);
        } while(!isNameUnique(name));
        return name;
    }

    bool isNameUnique(const string& name) {
        for(auto& r : rooms) 
            if(r->name == name) return false;
        return true;
    }

    vector<Room*> rooms;

public:
    vector<Room*> generate(int min_rooms) {
        srand(time(0));
        
        // 生成初始大厅
        Room* lobby = new Room("Main-Lobby");
        rooms.push_back(lobby);
        stack<Room*> room_stack;
        room_stack.push(lobby);

        // 深度优先生成基础树结构
        while(rooms.size() < min_rooms && !room_stack.empty()) {
            Room* current = room_stack.top();
            room_stack.pop();

            // 为当前房间随机添加1-3个新出口
            int new_exits = rand()%3 + 1;
            for(int i=0; i<new_exits && rooms.size()<min_rooms; i++) {
                
                // 随机选择可用方向
                vector<string> available_dirs;
                for(auto& d : directions)
                    if(current->exits.find(d) == current->exits.end())
                        available_dirs.push_back(d);
                
                if(available_dirs.empty()) continue;
                
                string dir = available_dirs[rand()%available_dirs.size()];
                
                // 创建新房间
                Room* new_room = new Room(generateUniqueName());
                current->exits[dir] = new_room;
                rooms.push_back(new_room);
                room_stack.push(new_room);
            }
        }

        // 添加随机循环路径
        for(int i=0; i<rooms.size()*2; i++) {
            Room* a = rooms[rand()%rooms.size()];
            Room* b = rooms[rand()%rooms.size()];
            
            vector<string> available_dirs;
            for(auto& d : directions)
                if(a->exits.find(d) == a->exits.end())
                    available_dirs.push_back(d);
            
            if(!available_dirs.empty() && a != b) {
                string dir = available_dirs[rand()%available_dirs.size()];
                a->exits[dir] = b;
            }
        }

        return rooms;
    }

    void printMap() {
        for(auto& room : rooms) {
            cout << "[" << room->name << "]\nExits: ";
            for(auto& exit : room->exits)
                cout << exit.first << "->" << exit.second->name << "  ";
            cout << "\n\n";
        }
    }
};

int main() {
    CastleGenerator generator;
    vector<Room*> castle = generator.generate(8); // 生成至少8个房间
    
    cout << "======= Random Castle Layout =======\n";
    generator.printMap();

    // 清理内存
    for(auto& r : castle) delete r;
    return 0;
}