#include "goblin.h"

Goblin::Goblin() : Monster("Goblin", 12) {}

int Goblin::attack_damage() const {
    return 3;
}
