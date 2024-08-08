Mind Boggle: Cards Edition
  
Mind Boggle: Cards Edition is a strategic card game where players compete against each other and computer-controlled opponents (bots) to achieve the lowest score. The game involves strategic decision-making and memory skills.

Table of Contents
1)Introduction
2)Features
3)Game Rules
4)Installation
5)How to Play
6)Future Expansion
7)OOP Concepts

1)Introduction
Mind Boggle: Cards Edition is a unique card game designed to be intuitive and engaging for human players. The game challenges players to strategically discard and exchange cards to achieve the lowest score. Special card effects and different bot personalities add complexity and excitement to the gameplay.

2)Features
Human Player and Bots: Play against three computer-controlled bots.
Strategic Decision-Making: Use your memory skills to track cards and make the best decisions.
Special Card Effects: Certain cards can shuffle opponents' cards, allow card exchanges, or reveal cards.
Dynamic Bot Personalities: Bots have varying levels of difficulty and personality traits, such as being aggressive, cautious, or unpredictable.

3)Game Rules
Each player is dealt a hand of three cards from a deck of 52 cards.
The objective is to achieve the lowest score by the end of the game.
Players can discard cards with or without replacement.
Scores are calculated based on the ranks of the cards in players' hands.
The player with the lowest score is declared the winner.

4)Installation
To run the game, you need to have a C++ compiler installed. Follow these steps to compile and run the game:
  4.1)Clone the repository:
    git clone https://github.com/Furqan1208/MindBoggleCardGame.git
  4.2)Navigate to the project directory:
    cd MindBoggleCardGame
  4.3)Compile the source code:
    g++ -o MindBoggle main.cpp
    
5)How to Play
Start the Game: Launch the game from the command line.
Player Moves: Choose to discard or exchange cards to improve your hand.
Bot Moves: Bots will play according to their personalities and memory of the game state.
Special Cards: Use special cards to gain strategic advantages.
Winning: The player with the lowest score at the end of the game wins.  

6)Future Expansion
Multiplayer Support: Implement support for multiple human players.
Additional Game Modes: Introduce new card games or custom rulesets.
User Interface Enhancements: Develop a graphical user interface (GUI) for a more interactive experience.

7)OOP Concepts
Mind Boggle: Cards Edition utilizes several object-oriented programming (OOP) concepts:

Class Inheritance: The game uses inheritance to create Human and Bot classes from a base Player class.
Polymorphism: Function overriding is used to customize behavior for different player types.
Class Composition: The Game class uses objects of Human and Bot to manage players.
Encapsulation: Data and behavior are encapsulated within classes.
Memory Management: Dynamic memory allocation is used for card objects and memory tracking.
Random Number Generation: Used for card shuffling and distribution.
Game Logic: Implements the complete game mechanics using OOP principles.
