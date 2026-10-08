#include "piece.h"

bool Piece::is_dead() {
    if (hp <= 0)
        return true;
    return false;
}

Piece::Piece(int own, int x, int y) {
    X = x;
    Y = y;
    owner = own;
}

void Piece::damaged(int damage) {
    if (defended) {
        hp -= damage / 2;
        defended = false;
    } else {
        hp -= damage;
    }
}

void Piece::update_location(int x_next, int y_next) {
    X = x_next;
    Y = y_next;
}

bool Master::check_move(int x_next, int y_next) {
    if (abs(X - x_next) <= 1 && abs(Y - y_next) <= 1)
        return true;
    else
        return false;
}

bool Defender::check_move(int x_next, int y_next) {
    if (abs(X - x_next) <= 1 && abs(Y - y_next) <= 1)
        return true;
    else
        return false;
}

bool Attacker::attack_check(int x_to, int y_to) {
    if ((abs(X - x_to) <= 1 && abs(Y - y_to) <= 1) || (abs(X - x_to) <= 2 && abs(Y - y_to) <= 2 && abs(X - x_to) - abs(Y - y_to) != 1))
        return true;
    else
        return false;
}

int Attacker::damage(int x_to, int y_to) {
    if ((abs(X - x_to) <= 1 && abs(Y - y_to) <= 1)) {
        return ATTACKER_DAMAGE * 2;
    } else {
        return ATTACKER_DAMAGE;
    }
}

bool Attacker::check_move(int x_next, int y_next) {
    if ((abs(X - x_next) <= 1 && abs(Y - y_next) <= 1) || (abs(X - x_next) <= 2 && abs(Y - y_next) <= 2 && abs(X - x_next) - abs(Y - y_next) != 1))
        return true;
    else
        return false;
}

bool Archer::attack_check(int x_to, int y_to) {
    if ((abs(X - x_to) <= 3 && abs(Y - y_to) == 0) || (abs(X - x_to) == 0 && abs(Y - y_to) <= 3))
        return true;
    else
        return false;
}

bool Archer::check_move(int x_next, int y_next) {
    if ((abs(X - x_next) <= 2 && abs(Y - y_next) == 0) || (abs(X - x_next) == 0 && abs(Y - y_next) <= 2))
        return true;
    else
        return false;
}

Board::Board(int width, int height) {
    board.resize(width, vector<Piece*>(height, nullptr));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i == MASTER1_X && j == MASTER1_Y) {
                board[i][j] = new Master(1, MASTER1_X, MASTER1_Y);
            } else if (i == ATTACKER1_X && j == ATTACKER1_Y) {
                board[i][j] = new Attacker(1, ATTACKER1_X, ATTACKER1_Y);
            } else if (i == DEFENDER1_X && j == DEFENDER1_Y) {
                board[i][j] = new Defender(1, DEFENDER1_X, DEFENDER1_Y);
            } else if (i == ARCHER1_X && j == ARCHER1_Y) {
                board[i][j] = new Archer(1, ARCHER1_X, ARCHER1_Y);
            } else if (i == MASTER2_X && j == MASTER2_Y) {
                board[i][j] = new Master(2, MASTER2_X, MASTER2_Y);
            } else if (i == ATTACKER2_X && j == ATTACKER2_Y) {
                board[i][j] = new Attacker(2, ATTACKER2_X, ATTACKER2_Y);
            } else if (i == DEFENDER2_X && j == DEFENDER2_Y) {
                board[i][j] = new Defender(2, DEFENDER2_X, DEFENDER2_Y);
            } else if (i == ARCHER2_X && j == ARCHER2_Y) {
                board[i][j] = new Archer(2, ARCHER2_X, ARCHER2_Y);
            }
        }
    }
}

Board::~Board() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (board[i][j] != nullptr) {
                delete board[i][j];
            }
        }
    }
}

bool Board::is_master_dead(int& round_number) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (board[i][j] != nullptr) {
                if (board[i][j]->get_symbol() == 'M' && round_number % 2 == board[i][j]->get_owner() % 2) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Board::update_defend(char defender, int& round_number) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (board[i][j] != nullptr &&
                board[i][j]->get_symbol() == defender &&
                round_number % 2 == board[i][j]->get_owner() % 2) {
                for (int k = i - 1; k <= i + 1; k++) {
                    for (int z = j - 1; z <= j + 1; z++) {
                        if (k >= 0 && k < WIDTH && z >= 0 && z < HEIGHT &&
                            board[k][z] != nullptr &&
                            board[k][z]->get_owner() == board[i][j]->get_owner()) {
                            board[k][z]->set_Defended(true);
                        }
                    }
                }
                return;
            }
        }
    }
    throw "Defender not found or not your turn!";
}

void Board::update_attack(char attacker, int x_attacker, int y_attacker, char attacked, int x_attacked, int y_attacked, int& round_number) {
    if (x_attacker < 0 || x_attacker >= WIDTH || y_attacker < 0 || y_attacker >= HEIGHT ||
        x_attacked < 0 || x_attacked >= WIDTH || y_attacked < 0 || y_attacked >= HEIGHT) {
        throw "Coordinates out of bounds!";
    }
    if (board[x_attacker][y_attacker] == nullptr || board[x_attacked][y_attacked] == nullptr) {
        throw "Attacker or attacked piece does not exist!";
    }
    if (board[x_attacker][y_attacker]->get_symbol() == attacker &&
        round_number % 2 == board[x_attacker][y_attacker]->get_owner() % 2 &&
        board[x_attacked][y_attacked]->get_symbol() == attacked &&
        (round_number + 1) % 2 == board[x_attacked][y_attacked]->get_owner() % 2) {
        if (board[x_attacker][y_attacker]->attack_check(x_attacked, y_attacked)) {
            int damage = board[x_attacker][y_attacker]->damage(x_attacked, y_attacked);
            board[x_attacked][y_attacked]->damaged(damage);
            if (board[x_attacked][y_attacked]->is_dead()) {
                delete board[x_attacked][y_attacked];
                board[x_attacked][y_attacked] = nullptr;
            }
        } else {
            throw "Attack not possible!";
        }
    } else {
        throw "Invalid attack!";
    }
}

void Board::update_move(char symbol, int x_next, int y_next, int& round_number) {
    if (x_next < 0 || x_next >= WIDTH || y_next < 0 || y_next >= HEIGHT) {
        throw "Destination out of bounds!";
    }
    if (board[x_next][y_next] != nullptr) {
        throw "Destination not empty!";
    }
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (board[i][j] != nullptr &&
                board[i][j]->get_symbol() == symbol &&
                round_number % 2 == board[i][j]->get_owner() % 2) {
                if (board[i][j]->check_move(x_next, y_next)) {
                    board[x_next][y_next] = board[i][j];
                    board[x_next][y_next]->update_location(x_next, y_next);
                    board[i][j] = nullptr;
                    return;
                } else {
                    throw "Movement not possible!";
                }
            }
        }
    }
    throw "Piece not found or not your turn!";
}

void Board::print() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (board[i][j] != nullptr) {
                cout << board[i][j]->get_symbol() << ' ';
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

System::System() {
    board = new Board(WIDTH, HEIGHT);
}

System::~System() {
    delete board;
}

void System::print_history() {
    cout << "Game history so far:" << endl;
    for (const string& action : history) {
        cout << action << endl;
    }
}

bool System::check_end() {
    if (round_number == 61) {
        cout << "Game Over" << endl << "It's a tie!";
        return true;
    }
    if (board->is_master_dead(round_number)) {
        if (round_number % 2 == 0) {
            cout << "Game Over" << endl << "Player 1 is the winner!";
        } else {
            cout << "Game Over" << endl << "Player 2 is the winner!";
        }
        return true;
    }
    return false;
}

void System::run() {
    board->print();
    while (!check_end()) {
        input();
        round_number += 1;
    }
}

void System::input() {
    bool valid = false;
    while (!valid) {
        try {
            string action = " ";
            string order;
            cin >> order;
            if (order == "0") {
                cout << "Exiting the game. Goodbye!" << endl;
                exit(0);
            }
            if (order == MOVE) {
                char symbol;
                string to;
                int x_next, y_next;
                cin >> symbol >> to;
                char comma;
                if (!(cin >> x_next >> comma >> y_next) || (comma != ',')) {
                    throw "Invalid coordinate format!";
                }
                board->update_move(symbol, x_next, y_next, round_number);
                cout << "Move confirmed." << endl << "Updated Board:" << endl;
                board->print();
                string action = "player " + to_string(((round_number-1) % 2)+1) + " : " + order + " " + string(1, symbol) + " " + to + " " + to_string(x_next) + comma + to_string(y_next);
                history.push_back(action);
                valid = true;
            } else if (order == ABILITY) {
                char defender;
                cin >> defender;
                board->update_defend(defender, round_number);
                cout << "Defensive ability used." << endl;
                board->print();
                string action = "player " + to_string(((round_number-1) % 2)+1) + " : " + order + " " + string(1, defender);
                history.push_back(action);
                valid = true;
            } else if (order == ATTACK) {
                char attacker;
                string at;
                char attacked;
                cin >> attacker >> at;
                char comma;
                int x_attacker, y_attacker, x_attacked, y_attacked;
                if (!(cin >> x_attacker >> comma >> y_attacker) || (comma != ',')) {
                    throw "Invalid coordinate format!";
                }
                string to;
                cin >> to;
                cin >> attacked >> at;
                if (!(cin >> x_attacked >> comma >> y_attacked) || (comma != ',')) {
                    throw "Invalid coordinate format!";
                }
                board->update_attack(attacker, x_attacker, y_attacker, attacked, x_attacked, y_attacked, round_number);
                cout << "Attack confirmed." << endl;
                board->print();
                string action = "player " + to_string(((round_number-1) % 2)+1) + " : " + order + " " + string(1, attacker) + " at " + to_string(x_attacker) + comma + to_string(y_attacker) + " -> " + attacked + " at " + to_string(x_attacked) + comma + to_string(y_attacked);
                history.push_back(action);
                valid = true;
            } else if (order == HISTORY) {
                print_history();
            } else {
                throw "Invalid order!";
            }
        } catch (const char* error) {
            cout << error << endl;
            cout << "Please try another input:" << endl;
        }
    }
}
