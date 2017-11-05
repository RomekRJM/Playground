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
#include <thread>
#include <chrono>
#include <unistd.h>
#include <term.h>
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
    srand(std::time(0));
    int randomValue = rand() % range;

    return lowerBand + randomValue;
}

string Weapon::toString() {
    return name + ": " + to_string(minDamage) + "-" + to_string(maxDamage);
}

int Character::hit(Character* opponent) {
    int weaponDamage = getRandomIntFromRange(weapon->getMinDamage(),
            weapon->getMaxDamage());

    int totalDamage = damage + weaponDamage;
    opponent->modifyHp(-totalDamage);

    return totalDamage;
}

int Character::getHp() {
    return hp;
}

string Character::toString() {
    return name + ": " + to_string(hp) + " hp and " + to_string(damage)
            + " base damage\n"
            + ((weapon == nullptr) ? "" : " Wields:" + weapon->toString());
}

Weapon* GameWorld::generateWeapon() {
    int minDamage = round * 2 + getRandomInt(round * 2);
    int maxDamage = round * 4 + 1;
    currentItem = new Weapon(weaponNames[round], minDamage, maxDamage);

    return currentItem;
}

Character* GameWorld::generateOpponent() {
    int hp = round * 100 + getRandomInt(round)*10;
    int damage = round * 2;
    Weapon *weapon = currentItem;

    currentOponent = new Character(hp, damage, oponentNames[round]);
    currentOponent->setWeapon(currentItem);

    return currentOponent;
}

string getInput(GameWorld* world, Character* player) {
    string input = "";

    if (world->getGameState() == stats_screen) {
        getchar();
    } else {
        cin >> input;
    }

    return input;
}

void redrawScreen(GameWorld* world, Character* player) {
    cout << "\033[2J\033[1;1H";

    if (world->getWeapon() == nullptr) {
        world->generateWeapon();
    }

    if (world->getOponent() == nullptr) {
        world->generateOpponent();
    }

    string description;
    string options = "\n\nPress 's' to see yours and opponent's stats.\n"
            "Press 'a' to enter the duel.\n";

    switch (world->getGameState()) {
        case start_game:
            description = "Welcome on the arena.\nYou will be facing various oponents.\n"
                    "Only one can win!";
            break;
        case stats_screen:
            description = "Your stats.\n\n" + player->toString()
                    + "\n\nOpponent stats\n\n" + world->getOponent()->toString();
            break;
        case round_won:
            description = "You won!!!\n\nYou can pick his weapon and replace yours."
                    "\n\nHis weapon \n\n" + world->getOponent()->getWeapon()->toString()
                    + "\n\nYour weapon \n\n" + player->getWeapon()->toString();

            options = "\n\nPress 'y' replace your current weapon.\n"
                    "Press 'n' to keep it.\n";
            break;
        case game_over:
            description = "You lie dead on the cold floor...";

            options = "\n\nPress 'q' quit the game.\n";
            break;
        case game_won:
            description = "Congrats, you have defeted the last oponent!";

            options = "\n\nPress 'q' to leave the game in fame.\n";
            break;
        case fight:
            simulateFight(player, world->getOponent());
            description = "Press any key to continue...";
            
            options = "";
            break;
        default:
            break;
    }

    cout << description << options;
}

void simulateFight(Character* player, Character* oponent) {
    while (player->getHp() > 0 && oponent->getHp() > 0) {
        int oponentDamage = player->hit(oponent);
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout << player->getName() << " deals " << oponentDamage << " to "
                << oponent->getName() << "." << endl;
        int playerDamage = oponent->hit(player);
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout << oponent->getName() << " deals " << playerDamage << " to "
                << player->getName() << "." << endl;
    }
}

void runGameLogic(GameWorld *world, Character* player, const string playerInput) {
    if (player->getHp() <= 0) {
        world->setGameState(game_over);
    } else if (player->getHp() > 0 and world->getGameState() == fight) {
        world->setGameState(round_won);
        int round = world->nextRound();
        if (round >= GameWorld::TOTAL_ROUNDS) {
            world->setGameState(game_won);
        }
    } else if (world->getGameState() == round_won) {
        if (playerInput == "y") {
            player->setWeapon(world->getOponent()->getWeapon());
        }
        world->purgeWeapon();
        world->purgeOponent();
        world->setGameState(start_game);
        player->fullyHeal();
    } else if (playerInput == "s") {
        world->setGameState(stats_screen);
    } else if (playerInput == "a") {
        world->setGameState(fight);
    } 

}

int main(int argc, char** argv) {
    GameWorld* world = new GameWorld();
    Character* player = new Character(100, 10);
    player->setWeapon(new Weapon("Bare hands", 1, 5));

    do {
        redrawScreen(world, player);
        string input = getInput(world, player);
        runGameLogic(world, player, input);
    } while (world->getGameState() != game_over);

    return 0;
}

