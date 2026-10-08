#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
using namespace std;

const int WIDTH = 8, HEIGHT = 8, HP = 100;
const int ATTACKER1_X = 0, ATTACKER1_Y = 4;
const int ATTACKER2_X = 7, ATTACKER2_Y = 3;
const int MASTER1_X = 0, MASTER1_Y = 0;
const int MASTER2_X = 7, MASTER2_Y = 7;
const int DEFENDER1_X = 0, DEFENDER1_Y = 2;
const int DEFENDER2_X = 7, DEFENDER2_Y = 5;
const int ARCHER1_X = 0, ARCHER1_Y = 6;
const int ARCHER2_X = 7, ARCHER2_Y = 1;
const int ATTACKER_DAMAGE = 10, ARCHER_DAMAGE = 12;
const string MOVE = "move", ABILITY = "ability", ATTACK = "attack", HISTORY = "history";

class Piece {
protected:
    bool defended = false;
    int owner;
    int hp = HP;
    char symbol;
    int X;
    int Y;
public:
    virtual int damage(int x_to, int y_to) { return 0; }
    void damaged(int damage);
    char get_symbol() { return symbol; }
    int get_owner() { return owner; }
    virtual bool attack_check(int x_to, int y_to) { return false; }
    Piece(int own, int x, int y);
    virtual ~Piece() {}
    virtual bool check_move(int x_next, int y_next) = 0;
    void update_location(int x_next, int y_next);
    bool is_dead();
    void set_Defended(bool boolean) { defended = boolean; }
};

class Master : public Piece {
public:
    Master(int own, int x, int y) : Piece(own, x, y) { symbol = 'M'; }
    bool check_move(int x_next, int y_next);
};

class Defender : public Piece {
public:
    Defender(int own, int x, int y) : Piece(own, x, y) { symbol = 'D'; }
    bool check_move(int x_next, int y_next);
};

class Attacker : public Piece {
public:
    Attacker(int own, int x, int y) : Piece(own, x, y) { symbol = 'A'; }
    bool check_move(int x_next, int y_next);
    int damage(int x_to, int y_to);
    bool attack_check(int x_to, int y_to);
};

class Archer : public Piece {
public:
    Archer(int own, int x, int y) : Piece(own, x, y) { symbol = 'R'; }
    bool check_move(int x_next, int y_next);
    int damage() { return ARCHER_DAMAGE; }
    bool attack_check(int x_to, int y_to);
};

class Board {
private:
    vector<vector<Piece*>> board;
public:
    Board(int width, int height);
    ~Board();
    void update_move(char symbol, int x_next, int y_next, int& round_number);
    void print();
    void update_attack(char attacker, int x_attacker, int y_attacker, char attacked, int x_attacked, int y_attacked, int& round_number);
    void update_defend(char defender, int& round_number);
    bool is_master_dead(int& round_number);
};

class System {
private:
    int round_number = 1;
    Board* board;
    vector<string> history;
public:
    void input();
    bool check_end();
    System();
    ~System();
    void run();
    void print_history();
};

#endif
