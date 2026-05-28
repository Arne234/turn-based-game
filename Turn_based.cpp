#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>

#include "Classes.h"
#include "EnemyFactory.h"


void showStats(const Character& P, const Character& E);
void showHpBar(int hp, int maxHp);
void playerChoice(Character& E, Character& P);


bool gameRunning = false;
bool playerSkipped = false;
int i = 1;
std::string result = "";
char key = '.';


int main() {

    std::string start;
    while (start != "y") {
        std::cout << "Start the game? (y/n) ";
        std::getline(std::cin, start);
    }

    int num;
    std::cout << "\nWhich Enemy do you want?: \n";
    std::cout << "1. Goblin\n";
    std::cout << "2. Tank\n";
    std::cout << "3. Mage\n";
    std::cout << "4. Boss\n";
    std::cin >> num;
    

    gameRunning = true;
    srand(time(NULL));

    Player P;
    auto E = EnemyFactory::createEnemy(num);

    while (gameRunning) {
        showStats(P, *E);

        P.applyEffect();

        playerSkipped = false;

        if (P.getStunnedStatus()) {
            P.removeStun();
            playerSkipped = true;
            std::cout << "Player is stunned and skips a turn!\n";
        }

        if (!playerSkipped) {
            std::cin >> key;
            playerChoice(*E, P);
        }
 
        
        if (E->getHp() > 0) E->takeTurn(P);

        Sleep(1500);

        if (E->getHp() == 0) {
            result = "You won";
            gameRunning = false;
        }

        if (P.getHp() == 0) {
            result = "You lost";
            gameRunning = false;
        }
        
        i++;
    }
    std::cout << result << "\n";
    i = 1;

    return 0;
}

void showStats(const Character& P, const Character& E) {
    system("cls");
    
    std::cout << "\n****************Stats****************\n";
    std::cout << "Round " << i << "\n";
    std::cout << P.getName() << " Hp: " <<  P.getHp() << "\n";
    showHpBar(P.getHp(), P.getMaxHp());
    std::cout << E.getName() << " Hp: " <<  E.getHp() << "\n";
    showHpBar(E.getHp(), E.getMaxHp());
    std::cout << "\n****************Stats****************\n";
    std::cout << "[A] Attack    [H] Heal    [D] Defend\n";
    std::cout << "[S] ~ Strong Attack for double damage, but a chance of missing and gurantied Hp loss\n";
    std::cout << "\n*************************************\n";

}

void showHpBar(int hp, int maxHp) {
    int width = 10;
    
    int filled = hp * width / maxHp;

    if (hp > 0 && filled == 0) filled = 1;

    int rest = width - filled;

    std::cout << "[";

    for (int i = 1; i <= filled; i++) {
        std::cout << "|";
    }

    for (int i = 1; i <= rest; i++) {
        std::cout << "-";
        
    }
    std::cout << "]\n";
}


void playerChoice(Character& E, Character& P) {
    if (key == 'A' || key == 'a') {
        P.attack(E);
    }

    else if (key == 'H' || key == 'h') {
        P.heal();
    }

    else if (key == 'D' || key == 'd') {
        P.defend();
    }

    else if (key == 'S' || key == 's') {
        if (rand() % 10 + 1 <= 3) {
            P.strongAttack(E, P);
        }
        else {
            std::cout << "You missed!\n";
            P.takeDamage(10);
        }
        
    }
    else {
        return;
    }
}