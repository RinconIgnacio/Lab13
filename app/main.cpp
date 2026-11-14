/// @file main.cpp
/// @brief Starts the arcade and registers its games.

#include "arcade.h"
#include "blackjack_game.h"
#include "dungeon_game.h"
#include "hangman_game.h"
#include "minesweeper_game.h"

int main() {
    Arcade arcade;

    arcade.add(new Hangman());
    arcade.add(new Dungeon());
    arcade.add(new Blackjack());
    arcade.add(new Minesweeper());

    arcade.run();

    return 0;
}
