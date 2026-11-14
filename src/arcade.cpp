#include "arcade.h"
#include "input.h"

#include <iostream>
#include <string>

Arcade::Arcade() : m_games{}, m_count(0) {
}

Arcade::~Arcade() {
    for (int i = 0; i < m_count; i++) {
        delete m_games[i];
    }
}

void Arcade::add(Game *game) {
    if (m_count < max_games) {
        m_games[m_count] = game;
        m_count++;
    } else {
        delete game;
    }
}

void Arcade::run() {
    std::string line;

    while (true) {
        std::cout << "\n=== ARCADE ===\n";

        for (int i = 0; i < m_count; i++) {
            std::cout << i + 1 << ". " << m_games[i]->title() << '\n';
        }

        std::cout << "0. Quit\n";

        if (!prompt_line("Choose: ", line)) {
            break;
        }

        if (line == "0") {
            break;
        }

        bool valid = false;

        for (int i = 0; i < m_count; i++) {
            if (line == std::to_string(i + 1)) {
                m_games[i]->play();
                std::cout << m_games[i]->title()
                          << " score: "
                          << m_games[i]->last_score() << '\n';
                valid = true;
                break;
            }
        }

        if (!valid) {
            std::cout << "Invalid choice.\n";
        }
    }

    std::cout << "Goodbye.\n";
}
