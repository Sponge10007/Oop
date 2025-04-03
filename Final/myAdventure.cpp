#include "geneRoom.h"
#include "Room.h"
#include<vector>
#include<map>
#include<stack>
#include<string>
#include<iostream>

void displayExitNames(std::vector<std::string> exits) {
    if(exits.size() == 0) std::cout << "No exits.";
    if(exits.size() == 1) {std::cout << exits.back(); return;}
    while(exits.size() != 0) {
        if(exits.size() == 1){
            std::cout << "and " << exits.back() << ".";
            return;
        }
        std::cout << exits.back() << ", ";
        exits.pop_back();
    }
}

class Game {
    private:
        std::vector<Room*> rooms;
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
            int n;
            std::cout << "Please give the number of rooms(AKA the size of the map)\n";
            std::cin >> n;
            mapGenerator generator;
            rooms = generator.generate(n);
            srand(time(0));
            int monsterIndex = rand() % rooms.size();
            int princessIndex = rand() % rooms.size();
            //随机设置公主和怪兽的位置，但是不能为出生点
            while (princessIndex == monsterIndex && monsterIndex != 0 && princessIndex != 0) {
                princessIndex = rand() % rooms.size();
            }
            rooms[monsterIndex]->setMonster();
            rooms[princessIndex]->setPrincess();
            current_Room = rooms[0]; //设置出生点
        }

        void gameStart() {
            std::cout << "-------------------------GAME START!-----------------------\n";
            while(!gameOver) {
                outputRoomInfo();
                processInput();
                checkRoomEvents();
            }
            displayEnd();
        }
        
        void outputRoomInfo() {
            std::vector<std::string> exitNames;
            for (const auto& exit : current_Room->getExits()) {
                exitNames.push_back(exit.first);
            }
            std::cout << "Welcome to the " << current_Room->getName() << ". There are "<< exitNames.size() << " exits: ";
            displayExitNames(exitNames);
            std::cout << std::endl << "Enter your command:\n";
        }

        void processInput() {
            std::string input, direct;
            bool legalInst = false, rightDir = false;
            std::getline(std::cin, input);
            // std::cout << input << std::endl;
            //下面是用来解析命令的if语句
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
            if(legalInst == false) { std::cout << "Wrong Instruction!" << std::endl; return; }
            if(!findName(direct)) { std::cout << "There is NO ROOM in this direction!" << std::endl; return; }
            current_Room = current_Room->getExits()[direct];
            std::cout << current_Room->getName() << std::endl;
        }
        
        bool findName(std::string direct) {
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
            if(gameLose) std::cout << "You have met the Monster. YOU LOSE!";
            if(gameWin) std::cout << "You have rescued the Princess. YOU WIN!";
        }
};

int main(){
    Game game;
    game.gameBegin();
    return 0;
}

