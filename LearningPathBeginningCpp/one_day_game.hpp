/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   one_day_game.hpp
 * Author: roman.subik
 *
 * Created on 5 listopada 2017, 06:32
 */

#ifndef ONE_DAY_GAME_HPP
#define ONE_DAY_GAME_HPP

#include <string>

using namespace std;

class Weapon {
private:
    int minDamage;
    int maxDamage;
    string name;
    
public:
    Weapon(string n, int min, int max) {
        name = n;
        minDamage = min;
        maxDamage = max;
    }
    
    string getName() { return name; };
    int getMinDamage() { return minDamage; };
    int getMaxDamage() { return maxDamage; };
    string toString();
};

class Character {
private:
    int hp;
    int damage;
    string name;
    Weapon *weapon;
    
public:
    Character(int h, int d, string n="You") {
        hp = h;
        damage = d;
        weapon = nullptr;
        name = n;
    }
    
    int getHp() { return hp; };
    void modifyHp(int hpDifference) { hp += hpDifference; };
    int getDamage() { return damage; };
    Weapon* getWeapon() { return weapon; };
    void setWeapon(Weapon *w) { weapon = w; };
    void hit(Character oponent);
    string toString();
};

enum GameState { start_game, stats_screen, fight, round_won, game_over, game_won };

class GameWorld{
private:
    Weapon *currentItem;
    Character *currentOponent;
    int round;
    GameState gameState;
    
    Character generateOpponent();
    Weapon generateWeapon();
    
public:
    GameWorld(){
        currentItem = nullptr;
        currentOponent = nullptr;
        round = 1;
        gameState = start_game;
    };
    void nextRound();
    GameState getGameState() { return gameState; };
    void setGameState(GameState s) { gameState = s; };
    Character* getOponent() { return currentOponent; };
    Weapon* getWeapon() { return currentItem; };
    const static int TOTAL_ROUNDS = 3;
    const string oponentNames[TOTAL_ROUNDS] = {"Old dog", "Weak murlock", "Warrior"};
    const string weaponNames[TOTAL_ROUNDS] = {"Dog's claw", "Old sword", "Battle axe"};
    
};

extern int getRandomInt(int max);
extern int getRandomIntFromRange(int min, int max);

extern string getInput();
extern void redrawScreen(GameWorld world, Character player);
extern void runGameLogic(GameWorld world, Character player, string playerInput);

#endif /* ONE_DAY_GAME_HPP */
