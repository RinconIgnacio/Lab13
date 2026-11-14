#ifndef ARCADE_TROLL_H
#define ARCADE_TROLL_H

#include "monster.h"

/// A stronger monster that deals 6 damage per attack.
class Troll : public Monster {
public:
    Troll();

    /// @return the Troll's attack damage
    int attack_damage() const override;

    /// @return a description specific to the Troll
    std::string describe() const override;
};

#endif // ARCADE_TROLL_H
