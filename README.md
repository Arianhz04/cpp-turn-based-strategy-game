# Turn-Based Strategy Board Game in C++

A command-line, two-player strategy board game developed as a university C++ project. The game models an 8×8 board with multiple piece types, turn-based actions, movement rules, combat, defensive abilities, win/lose conditions, and an action history.

## Project Highlights

- Object-oriented design using inheritance and virtual functions
- Four piece types: Master, Defender, Attacker, and Archer
- Two-player alternating turns
- Board-state management using a 2D structure of `Piece*`
- Combat and damage handling, including defensive damage reduction
- Input validation and error handling for invalid moves and actions
- Game-ending logic and a turn limit
- Action history for reviewing previous moves

## Technologies

- C++17
- Object-Oriented Programming
- Inheritance and polymorphism
- STL `vector` and `string`
- Dynamic memory management
- Command-line interface

## Architecture

```text
Piece (abstract base class)
├── Master
├── Defender
├── Attacker
└── Archer

Board
└── Owns and updates pieces, movement, attacks, defense, and board state

System
└── Controls the game loop, user input, turns, history, and end conditions
```

## Gameplay

Each player controls one Master, Defender, Attacker, and Archer on an 8×8 board.

Commands supported by the game include:

- `move` — move a piece to a legal destination
- `ability` — use the Defender's defensive ability
- `attack` — attack an opponent's piece
- `history` — view previously recorded actions
- `0` — exit the game

The exact command arguments depend on the action. For example, a move is entered in a form such as `move A to 1,4`.

## Build and Run

### Requirements

A C++ compiler that supports C++17 or later.

### Compile

```bash
g++ -std=c++17 -Wall -Wextra -pedantic project.cpp implementation.cpp -o game
```

### Run

On macOS/Linux:

```bash
./game
```

On Windows, run `game.exe` from a terminal after compiling.

## Files

| File | Purpose |
|---|---|
| `piece.h` | Class definitions, constants, and board/game interfaces |
| `implementation.cpp` | Piece rules, board operations, combat, game logic, and input handling |
| `project.cpp` | Program entry point |

## Learning Outcomes

This project provided practical experience with object-oriented program design, modelling entities with inheritance and polymorphism, maintaining state across multiple classes, validating user input, and managing dynamically allocated objects.

## Possible Future Improvements

- Replace raw owning pointers with smart pointers such as `std::unique_ptr`
- Separate class declarations and implementations into more focused files
- Add automated unit tests for movement and attack rules
- Introduce a cleaner command parser
- Add save/load functionality
- Improve the terminal interface and display player/health information

## Author

**Arian Hasanzadeh**  
B.Sc. Computer Science — University of Tehran
