# Polymorphism notes

Answer in your own words. Use the words **static dispatch** and **dynamic dispatch**.

## 1. The non-virtual destructor

What did the sanitizer report when ~Game was not virtual? Explain which destructor ran and which did not.

A separate AddressSanitizer test reported a new-delete-type-mismatch when a Hangman object was deleted through a Game pointer without a virtual destructor. The allocated object was 408 bytes, while the deallocated type was 8 bytes.

Only the Game destructor executed. The Hangman destructor did not run. This demonstrates why a base class needs a virtual destructor when derived objects are deleted through base pointers.

## 2. Game is abstract

In two sentences, explain why Game g; no longer compiles.

Game contains a pure virtual function, play(), making it an abstract class. Abstract classes cannot be instantiated directly, so an object must be created from a derived class that implements play().

## 3. override

What does override protect you from? Give an example of a mistake it catches.

Override makes the compiler verify that a function actually overrides a virtual function from the base class. It catches mistakes such as incorrect function signatures or attempting to override a function that is not virtual.

## 4. Last week versus this week

Repeat the Week 12 experiment: Game *g = &hangman; g->play();. What printed last week, and what prints now? Name the kind of dispatch that happened each time.

In Week 12, the call to play() through a Game pointer used static dispatch and executed the base class version. In Week 13, the same call uses dynamic dispatch and executes the Hangman version because the function is virtual.

Static dispatch depends on the declared pointer type, while dynamic dispatch uses the actual object type.
