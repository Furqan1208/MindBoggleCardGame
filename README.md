# Mind Boggle: Cards Edition

## Overview
Mind Boggle: Cards Edition is a card game where players compete to achieve the lowest score by strategically discarding and exchanging cards. The game features a human player and three computer-controlled bots, each with unique decision-making abilities and memory mechanisms. The game was developed as a project for an Object-Oriented Programming (OOP) course and showcases various OOP concepts in a practical, engaging way.

## Features
- **Human Player vs. Bots**: Play against three AI-controlled opponents with different strategies and memory capabilities.
- **Strategic Gameplay**: Make strategic decisions to discard or exchange cards, aiming for the lowest score.
- **Special Card Effects**: Utilize cards with special abilities that can shuffle, exchange, or reveal cards, adding complexity to the game.
- **Memory Mechanism**: Bots remember the rank, condition, and position of their own and opponents' cards, making for challenging gameplay.
- **Score Calculation**: At the end of the game, the player with the lowest score wins.

## Challenges Faced
- **Understanding the Flow**: Managing multiple classes, functions, and memory tracking for players and bots.
- **Bot Decision-Making**: Implementing effective algorithms for bot moves based on memory and card conditions.
- **User Interaction**: Handling user inputs, ensuring proper validation, and providing feedback during gameplay.
- **Code Complexity and Debugging**: Managing and debugging complex code with various OOP components.

## Future Expansions
- **Multiplayer Support**: Adding support for multiple human players.
- **Additional Game Modes**: Introducing new game modes or custom rulesets for varied gameplay experiences.
- **Graphical User Interface (GUI)**: Enhancing the user interface with graphical elements for a more immersive experience.

## OOP Concepts Demonstrated
- **Class Inheritance**: Derived classes (e.g., `Human` and `Bot`) inherit properties and methods from a base `Player` class.
- **Polymorphism**: Overriding functions like `printHand()` for specialized behavior in derived classes.
- **Encapsulation**: Controlled access to class data and methods through public and private specifiers.
- **Memory Management**: Dynamic allocation and management of memory for card objects.
- **Game Logic Implementation**: Integrating OOP principles into the core gameplay mechanics.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/Furqan1208/Mind-Boggle.git
2. Compile the code using a C++ compiler.
3. Run the executable to start the game.   

## How to Play
- Start the game and choose your moves by selecting card ranks and suits.
- Discard or exchange cards strategically to lower your score.
- Compete against bots and aim to have the lowest score by the end of the game.
