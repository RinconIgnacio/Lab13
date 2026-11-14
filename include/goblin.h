#ifndef ARCADE_GOBLIN_H
#define ARCADE_GOBLIN_H

#include "monster.h"

/// A small monster that deals 3 damage per attack.
class Goblin : public Monster {
public:
    Goblin();

    /// @return the Goblin's attack damage
    int attack_damage() const override;
};

#endif // ARCADE_GOBLIN_H
