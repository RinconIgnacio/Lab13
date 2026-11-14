# GDB log

One dated section per week. Paste the commands you used and the output you saw, then explain what it means in your own words. Pasted output with no explanation earns partial credit at most.

## Week 12 (Lab 12) - November 7, 2026

### Constructor Chain

Commands used:

    break Hangman::Hangman
    run
    bt
    step
    bt
    break Game::Game
    continue
    bt
    finish
    bt

Output:

    #0 Hangman::Hangman (this=0x7fffffffe1a0)
       at src/hangman_game.cpp:4
    #1 main () at app/main.cpp:50

    #0 Game::Game (this=0x7fffffffe1a0, title="Hangman")
       at src/game.cpp:8
    #1 Hangman::Hangman (this=0x7fffffffe1a0)
       at src/hangman_game.cpp:4
    #2 main () at app/main.cpp:50

    #0 Hangman::Hangman (this=0x7fffffffe1a0)
       at src/hangman_game.cpp:4
    #1 main () at app/main.cpp:50

I first tried using step, but it took me into the string allocator. After setting a breakpoint in Game, I could see that the base constructor was called from Hangman. Using finish brought me back to Hangman, which helped me understand the order.

### Destructor Chain

Commands used:

    break Hangman::~Hangman
    break Game::~Game
    continue
    bt
    continue
    bt
    continue
    bt

Output:

    #0 Game::~Game (this=0x7fffffffe1d0)
       at src/game.cpp:10
    #1 Minesweeper::~Minesweeper (this=0x7fffffffe1d0)
       at include/minesweeper_game.h:6
    #2 main () at app/main.cpp:87

    #0 Hangman::~Hangman (this=0x7fffffffe1a0)
       at include/hangman_game.h:6
    #1 main () at app/main.cpp:87

    #0 Game::~Game (this=0x7fffffffe1a0)
       at src/game.cpp:10
    #1 Hangman::~Hangman (this=0x7fffffffe1a0)
       at include/hangman_game.h:6
    #2 main () at app/main.cpp:87

Minesweeper was destroyed first because it was created last. I also noticed that Hangman's destructor ran before Game's destructor. So construction starts with the base class, while destruction happens in the opposite order.

### Inspecting Inheritance (Task 8)

I added `Game *g = &hangman;` in main and used GDB to compare the object and the pointer.

Commands:

    break app/main.cpp:54
    run
    print hangman
    print *g
    ptype Hangman
    ptype g
    whatis g

Output:

    (gdb) print hangman
    $1 = {<Game> = {m_title = "Hangman", m_last_score = 0},
      m_times_played = 0}

    (gdb) print *g
    $2 = {m_title = "Hangman", m_last_score = 0}

    (gdb) ptype Hangman
    type = class Hangman : public Game {
        int m_times_played;
      public:
        Hangman(void);
        void play(void);
        int times_played(void) const;
    }

    (gdb) ptype g
    type = class Game {
        std::string m_title;
        int m_last_score;
      public:
        Game(std::string);
        ~Game(void);
        const std::string & title(void) const;
        int last_score(void) const;
        void play(void);
      protected:
        void set_score(int);
        bool ask_play_again(void) const;
    } *

    (gdb) whatis g
    type = Game *

I noticed that printing Hangman showed both its own variable and the ones inherited from Game. But printing through g only showed the Game part. This helped me see how the type of a pointer affects what GDB displays.

## Week 13 (Lab 13)

Name: Ignacio Rincon

### A Game pointer with a virtual play()

Commands:
- break src/arcade.cpp:49
- run
- set print object off
- print *m_games[i]
- ptype m_games[i]
- set print object on
- print *m_games[i]
- info vtbl *m_games[i]
- step

With object printing off, GDB showed the Game portion:
m_title = "Hangman" and m_last_score = 0.

With object printing on, GDB showed the real Hangman object,
including m_times_played = 0.

ptype showed Game*, which is the declared pointer type.

The virtual table contained:
- Hangman::~Hangman()
- Hangman::~Hangman()
- Hangman::play()

The step command entered Hangman::play() in hangman_game.cpp.

This is dynamic dispatch because the function is selected
using the actual object's type.

### A Monster pointer

The fight function uses Monster& instead of Monster*.

Commands:
- break src/dungeon.cpp:104
- run
- set print object on
- print monster
- ptype monster
- info vtbl monster
- step

For Goblin, GDB showed:
- Real object: Goblin
- Name: Goblin
- Health: 8 after the first attack
- Declared type: Monster&
- Real type: Goblin&

Goblin virtual table:
- Goblin::~Goblin()
- Goblin::~Goblin()
- Goblin::attack_damage() const
- Monster::describe() const

The step command entered Goblin::attack_damage()
in goblin.cpp, returning 3.

For Troll, GDB showed:
- Real object: Troll
- Name: Troll
- Health: 16 after the first attack
- Declared type: Monster&
- Real type: Troll&

Troll virtual table:
- Troll::~Troll()
- Troll::~Troll()
- Troll::attack_damage() const
- Troll::describe() const

The step command entered Troll::attack_damage()
in troll.cpp, returning 6.

Both monsters use dynamic dispatch for attack_damage().
Goblin inherits Monster::describe(), while Troll overrides it.
