/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   one_day_game.cpp
 * Author: roman.subik
 *
 * Created on 5 listopada 2017, 06:31
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "one_day_game.hpp"

using namespace std;

int getRandomInt(int upperBand) {
    return getRandomIntFromRange(0, upperBand);
}

int getRandomIntFromRange(int lowerBand, int upperBand) {
    if (upperBand < lowerBand) {
        upperBand = lowerBand;
    }

    int range = upperBand - lowerBand;
    std::srand(std::time(0));
    int randomValue = std::rand() % range;

    return lowerBand + randomValue;
}

string Weapon::toString() {
    return name + ": " + to_string(minDamage) + "-" + to_string(maxDamage);
}

void Character::hit(Character opponent) {
    int weaponDamage = getRandomIntFromRange(weapon->getMinDamage(),
            weapon->getMaxDamage());

    int totalDamage = -(damage + weaponDamage);
    opponent.modifyHp(totalDamage);
}

string Character::toString() {
    return name + " has " + to_string(hp) + " hp and " + to_string(damage) 
            + " base damage\nWields:" + weapon->toString();
}

Weapon GameWorld::generateWeapon() {
    int minDamage = round * 2 + getRandomInt(round * 2);
    int maxDamage = round * 4 + 1;

    return Weapon(weaponNames[round], minDamage, maxDamage);
}

Character GameWorld::generateOpponent() {
    int hp = round * 100 + getRandomInt(round - 1)*10;
    int damage = round * 2;
    Weapon *weapon = currentItem;

    Character opponent = Character(hp, damage, weaponNames[round]);
    opponent.setWeapon(currentItem);

    return opponent;
}

string getInput() {
    string input;
    cin >> input;
    return input;
}

void redrawScreen(GameWorld world, Character player) {
    if (world.getGameState() != fight) {
        system("clear");
    }

    string description;
    string options = "\n\nPress 's' to see yours and opponent's stats.\n"
            "Press 'a' to enter the duel.\n";

    switch (world.getGameState()) {
        case start_game:
            description = "Welcome on the arena.\nYou will be facing various oponents.\n"
                    "Only one can win!";
            break;
        case stats_screen:
            description = "Your stats.\n\n" + player.toString() 
                    + "\n\nOpponent stats" + world.getOponent()->toString();
            break;
        default:
            break;
    }

    cout << description << options;
}

void runGameLogic(GameWorld world, Character player, string playerInput) {
    if (playerInput == "s") {
        world.setGameState(stats_screen);
    }
}

int main(int argc, char** argv) {
    GameWorld world = GameWorld();
    Character player = Character(100, 10);

    do {
        redrawScreen(world, player);
        string input = getInput();
        runGameLogic(world, player, input);
    } while (world.getGameState() != game_over);

    return 0;
}

