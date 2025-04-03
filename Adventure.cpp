#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>

using namespace std;


class Room {
    private:
        string name;
        map<string, Room*> exits;
        bool hasMonster;
        bool hasPrincess;
    public:
        Room(string name) : name(name), hasMonster(false), hasPrincess(false) {}

        string getName(){
            return this->name;
        }

        bool ifHasMonster(){
            return this->hasMonster;
        }

        bool ifHasPrincess(){
            return this->hasPrincess;
        }

        map<string, Room*> getExits() {
            return exits;
        }

        void setMonster(){
            this->hasMonster = true;
        }

        void setPrincess(){
            this->hasPrincess = true;
        }

        void setExits(string dir, Room* room){
            this->exits[dir] = room;
        }
};

void displayExitNames(vector<string> exits) {
    if(exits.size() == 0) cout << "No exits.";
    while(exits.size() != 0) {
        if(exits.size() == 1){
            cout << "and " << exits.back() << ".";
            return;
        }
        cout << exits.back() << ", ";
        exits.pop_back();
    }
}

class Game {
    private:
        vector<Room*> rooms;
        Room* current_Room;
        bool hasRescuedPrincess;
        bool hasMetMonster;
        bool gameLose;
        bool gameWin;
        bool gameOver;
    public:
        Game() : hasRescuedPrincess(false), hasMetMonster(false),
                 gameLose(false), gameWin(false), gameOver(false){
                    initializeRooms();
        }
        
        ~Game() {
            for (Room *room: rooms) {
                delete room;
            }
        }

        void gameBegin() {
            gameStart();
        }
    private:
        void initializeRooms() {
            Room* lobby = new Room("Lobby");
            Room* dining = new Room("Dining Room");
            Room* armory = new Room("Armory");
            Room* tower = new Room("Tower");
            Room* kitchen = new Room("Kitchen");
            Room* dungeon = new Room("Dungeon");
            Room* towerTop = new Room("Tower Top");
            Room* pantry = new Room("Pantry");
            Room* secretRoom = new Room("Secret Room");

            lobby->setExits("east", dining);
            lobby->setExits("west", armory);
            lobby->setExits("up", tower);

            dining->setExits("west", lobby);
            dining->setExits("south", kitchen);

            armory->setExits("east", lobby);
            armory->setExits("down", dungeon);

            tower->setExits("down", lobby);
            tower->setExits("up", towerTop);

            kitchen->setExits("north", dining);
            kitchen->setExits("east", pantry);

            pantry->setExits("west", kitchen);

            dungeon->setExits("up", armory);
            dungeon->setExits("south", secretRoom);

            secretRoom->setExits("north", dungeon);

            towerTop->setExits("down", tower);

            rooms.push_back(lobby);
            rooms.push_back(dining);
            rooms.push_back(armory);
            rooms.push_back(tower);
            rooms.push_back(kitchen);
            rooms.push_back(dungeon);
            rooms.push_back(towerTop);
            rooms.push_back(pantry);
            rooms.push_back(secretRoom);

            current_Room = lobby;

            vector<Room*> possibleRooms;
            for (Room* room : rooms) {
                if (room != lobby) {
                    possibleRooms.push_back(room);
                }
            }

            srand(time(0));
            int monsterIndex = rand() % possibleRooms.size();
            int princessIndex = rand() % possibleRooms.size();
            while (princessIndex == monsterIndex) {
                princessIndex = rand() % possibleRooms.size();
            }
            cout << possibleRooms[monsterIndex]->getName() << " Monster\n" << possibleRooms[princessIndex]->getName() << " Princess\n";
            possibleRooms[monsterIndex]->setMonster();
            possibleRooms[princessIndex]->setPrincess();
        }

        void gameStart() {
            while(!gameOver) {
                outputRoomInfo();
                processInput();
                checkRoomEvents();
            }
            displayEnd();
        }
        
        void outputRoomInfo() {
            vector<string> exitNames;
            for (const auto& exit : current_Room->getExits()) {
                exitNames.push_back(exit.first);
            }
            cout << "Welcome to the " << current_Room->getName() << ". There are "<< exitNames.size() << " exits: ";
            displayExitNames(exitNames);
            cout << endl << "Enter your command:\n";
        }

        void processInput() {
            string input, direct;
            bool legalInst = false, rightDir = false;
            getline(cin, input);
            cout << input << endl;
            if(input.find("east") > 0 && input.find("east") < input.length()) {
                legalInst = true;
                direct = input.substr(input.find("east"), 4);
            }
            else if(input.find("west") > 0 && input.find("west") < input.length()) {
                legalInst = true;
                direct = input.substr(input.find("west"), 4);
            }
            else if(input.find("up") > 0 && input.find("up") < input.length()) {
                legalInst = true;
                direct = input.substr(input.find("up"), 2);
            }
            else if(input.find("down") > 0 && input.find("down") < input.length()) {
                legalInst = true;
                direct = input.substr(input.find("down"), 4);
            }
            else if(input.find("south") > 0 && input.find("south") < input.length()) {
                legalInst = true;
                direct = input.substr(input.find("south"), 5);
            }
            else if(input.find("north") > 0 && input.find("north") < input.length()) {
                legalInst = true;
                direct = input.substr(input.find("north"), 5);
            }
            if(input.substr(0,2) != "go" ) legalInst = false;
            // cout << direct << endl;
            if(legalInst == false) { cout << "Wrong Instruction!" << endl; return; }
            if(!findName(direct)) { cout << "There is NO ROOM in this direction!" << endl; return; }
            current_Room = current_Room->getExits()[direct];
            cout << current_Room->getName() << endl;
        }
        
        bool findName(string direct) {
            for (const auto& exit : current_Room->getExits()) {
                if(exit.first == direct) return true;
            }
            return false;
        }

        void checkRoomEvents() {
            if(current_Room->ifHasMonster()) {gameLose = true, gameOver = true; }
            if(current_Room->ifHasPrincess()) gameWin = true, gameOver = true;
        }

        void displayEnd() {
            if(gameLose) cout << "You have met the Monster. YOU LOSE!";
            if(gameWin) cout << "You have rescued the Princess. YOU WIN!";
        }
};

int main(){
    Game game;
    game.gameBegin();
    return 0;
}