# Alien vs. Zombie

This is a assignment project inspired by a mobile game app called Alien Path. It is an adventurous game which the Alien (the player)
must go through challenges and obstacles to defeat the Zombies in the Battlefield.

YouTube link to our video demo Part 1 : [TCP1101 | Assignment Part 1: Video Demo](https://youtu.be/rTWrMOoeHlA).

Youtube link to our video demo Part 2 : [TCP1101 | Assignment Part 2: Video Demo](https://youtu.be/lopQ84WmDPk).

## Compilation Instructions

```
g++ pf\*.cpp main2.cpp -o game
```


## User Manual

*Welcome to ALIEN VS ZOMBIE!*

Hello my alien friends! Before we begin our adventure in destroying ~THE MENACING ZOMBIES~, we must know the "tactics" and find the most strategic way in killing those zombies.


*How to customize size of the board*
1. User must prompt the number of rows and columns.
2. Once done, the board will be appeared as it prompted before and the Alien will automatically
   positioned at the centre of the board.
   
*How to play*
1. User will be provided with the life, attack and range of alien and zombies.
2. To move Alien up,down,left and right ,user must prompt "up","down","left" and "right".
3. All objects in the game have its own functions:
   - h or Health will add 20 life to Alien.
   - p or Pod will instantly inflicts 10 damage to Zombie when hit by Alien.
   - r or Rock will hides a game object (either h or p) and will reveal it when hit by Alien and it will stop the Alien from moving.
   
*How to get any tutorial for the game*

Prompt "help". It will show the user the list and description of the commands that user can use in the game.

*How to save, load and quit the game*
1. To save the game, simply prompt "save". It will save the current game and user need to enter the name of the file to save to.
2. To load user previous game, prompt "load" and it will bring to the previous saved game.
3. To quit the game, propmt "quit" and type 'y' to confirm or type 'n' to cancel.
   
## Progress Log

- [Part 1](PART1.md)
- [Part 2](PART2.md)

## Contributors

- Syed Danial Imtiaz Bin Syed Abdul Rahim
- Hilman Danish Bin Hamka
- Adam Bin Azmanhazim

