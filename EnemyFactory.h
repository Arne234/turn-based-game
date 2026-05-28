#pragma once
#include "Classes.h"
#include <memory>

class EnemyFactory {
    public:
        static std::unique_ptr<Character> createEnemy(const int num)

        {

        if (num == 2) {
            return std::make_unique<Tank>();
        }

        if (num == 3) {
            return std::make_unique<Mage>();
        }

        if (num == 4) {
            return std::make_unique<Boss>();
        }

        return std::make_unique<Goblin>();
        };
};