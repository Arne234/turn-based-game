#pragma once;

#include <iostream>
#include <string>


class Character {
    protected:
        std::string name;
        int hp;
        int maxHp;
        int attackPower;
        bool defending = false;

        bool poisoned = false;
        int poisonRound = 0;

        bool stunned = false;

    public:
        Character(const std::string& n, int h, int mH, int a) : name(n), hp(h), maxHp(mH), attackPower(a) {};

        virtual void takeTurn(Character& C) = 0;
        virtual void attack(Character& C) = 0;
        virtual void heal() = 0;
        virtual void defend() = 0;
        virtual std::string attackMessage() = 0;
        virtual std::string healMessage() = 0;
        virtual std::string defendMessage() = 0;
        virtual std::string strongAttackMessage() = 0;
        virtual void strongAttack(Character& C, Character& D) {};
        void applyEffect();
        

        void takeDamage(int dmg) {  
            
            if (defending) {
                dmg /= 4;
                defending = false;
            }

            
            hp -= dmg;
            if (hp < 0) hp = 0;
        }

        void getHealed(int heal) {
            hp += heal;
            if (hp > maxHp) hp = maxHp;

            defending = false;
        }

        std::string getName() const {
            return name;
        }
        
        int getHp() const {
            return hp;
        }

        int getMaxHp() const {
            return maxHp;
        }

        bool getIsPoisoned() {
            return poisoned;
        }

        void setPoison(int turns) {
            poisoned = true;
            poisonRound = turns;
        }

        bool getStunnedStatus() {
            return stunned;
        }

        void setStunned() {
            stunned = true;
        }

        void removeStun() {
            stunned = false;
        }

        virtual ~Character() = default;
};

class Player : public Character {  

    public:

        Player() : Character("Player", 100, 100, 25) {};

        void takeTurn(Character& C) override {};
        void attack(Character& C) override;
        void heal() override;
        void strongAttack(Character& C, Character& D) override;
        void defend() override;


        std::string attackMessage() override {
            return "You attacked!\n";
        }
        std::string healMessage() override {
            return "You healed!\n";
        }
        std::string defendMessage() override {
            return "You defended!";
        }
        std::string strongAttackMessage() override {
            return "You hit him very hard!\n";
        }

};

class Enemy : public Character {  

    public:

        Enemy(std::string name, int h, int mH, int a) : Character(name, h, mH, a) {};

        virtual void attack(Character& C) override;
        virtual void heal() override;
        virtual void defend() override;
        virtual void takeTurn(Character& C) override;


        std::string attackMessage() override {
            return " attacked!\n";
        }
        std::string healMessage() override {
            return " healed!\n";
        }
        std::string defendMessage() override {
            return " defended!";
        }
        std::string strongAttackMessage() override {
            return "You got hit very hard!\n";
        }

};

class Goblin : public Enemy {
    public:
        Goblin() : Enemy("Goblin", 80, 80, 30) {};

        void attack(Character& C) override;

};

class Tank : public Enemy {
    public: 
        Tank() : Enemy("Tank", 120, 120, 20) {};

        void takeTurn(Character& C) override;
};

class Mage : public Enemy {
    public: 
        Mage() : Enemy("Mage", 100, 100, 25) {};

        std::string attackMessage() override {
            return " threw a fireball!";
        }
};

class Boss : public Enemy {
    public: 
        Boss() : Enemy("Boss", 120, 120, 30) {};

        void strongAttack(Character& C, Character& D) override;

        void takeTurn(Character& C) override;
};

void Player::attack(Character& C)  {
    int var = rand() % 9 - 4;
    int fullDmg = attackPower + var;

    if (rand() % 10 + 1 == 1) {
        fullDmg *= 2;
        std::cout << "\nCRITICAL HIT!\n";
    }

    std::cout << attackMessage();
    
    C.takeDamage(fullDmg);
}

void Player::heal() {
    getHealed(attackPower/2);

    std::cout << healMessage();

}

void Player::defend() {
    defending = true;

    std::cout << defendMessage();
}

void Player::strongAttack(Character& C, Character& D) {

        C.takeDamage(attackPower * 2);
        D.takeDamage(attackPower/2);

        std::cout << strongAttackMessage();
}

void Enemy::takeTurn(Character& C) {
    int choice = rand() % 3;

    if (hp <= 20) {
        heal();
        return;
    }

    if (choice == 0) {
        attack(C);
    }

    else if (choice == 1) {
        heal();
    }

    else {
        defend();
    }
}


void Enemy::attack(Character& C) {
    int var = rand() % 9 - 4;
    int fullDmg = attackPower + var;

    std::cout << name << attackMessage();
    
    C.takeDamage(fullDmg);
}

void Enemy::heal() {
    getHealed(attackPower/2);

    std::cout << name << healMessage();

}

void Enemy::defend() {
    defending = true;

    std::cout << name << defendMessage();
}

void Boss::strongAttack(Character& C, Character& D) {
    
        C.takeDamage(attackPower * 2);
        D.takeDamage(attackPower/2);

        std::cout << strongAttackMessage();

}

void Goblin::attack(Character& C) {
    Enemy::attack(C);

    if (!C.getIsPoisoned()) {
        if (rand() % 10 + 1 <= 3) {
            C.setPoison(3);
        }
    }
}

void Character::applyEffect() {
    if (poisoned) {
        takeDamage(5);
        poisonRound--;
        std::cout << name << " is poisoned!\n";

        if (poisonRound == 0) {
            poisoned = false;
        }
    }
}

void Tank::takeTurn(Character& C) {
    int choice = rand() % 4;

    if (choice == 0) {
        attack(C);
    }

    else if (choice == 1) {
        heal();
    }

    else if (choice == 2) {
        defend();
    }

    else {

        C.setStunned();

        std::cout << "Player got stunned!\n";
    }
}

void Boss::takeTurn(Character& C) {
    if (rand() % 10 == 0) {

        strongAttack(C, *this);
    }

    else {

        attack(C);
    }
}


