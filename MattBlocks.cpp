//
// Created by mail@vacoola.name on 01.05.19.
//

#include <list>
#include <map>
#include <iostream>

#include "MattBlocks.h"

Screen SCREEN =
        {
                {1, 1, 1, 4, 5, 6, 7},
                {1, 2, 3, 4, 5, 6, 7},
                {1, 2, 3, 4, 5, 6, 6},
                {1, 1, 6, 1, 5, 6, 6},
                {1, 2, 3, 1, 8, 8, 7},
                {1, 2, 3, 4, 8, 8, 7}
        };

int WILD = 2;

Payout PAYOUT =
        {
                {
                        1, {{2, 20}, {3, 30}}
                },
                {
                        2, {{2, 20}, {3, 30}}
                },
                {
                        3, {{2, 20}, {3, 50}}
                },
                {
                        4, {{2, 20}, {3, 30}}
                },
                {
                        5, {{2, 20}, {3, 30}}
                },
                {
                        6, {{2, 20}, {3, 30}}
                },
                {
                        7, {{2, 20}, {3, 30}}
                },
                {
                        8, {{2, 20}, {3, 30}}
                }
        };

void MattBlocks::run() {

    //cout << "3 of 3 = " << symbol_payout(3, 3, PAYOUT) << endl;

    display_screen(SCREEN);

    Positions positions = find_symbols_positions();

    display_positions(positions);
}

int MattBlocks::symbol_payout(int symbol, int count, Payout payout) {
    int pay = 0;

    if (payout.count(symbol)) {
        for (const auto &symbol_payout : payout[symbol]) {
            int s_count = symbol_payout.first;
            int s_pay = symbol_payout.second;
            if (count >= s_count && pay < s_pay) {
                pay = s_pay;
            }
        }
    }
    return pay;
}

void MattBlocks::display_screen(const Screen &screen) {
    cout << "****     Screen     ****";

    for (const auto &row : screen) {
        for (const auto &symbol : row) {
            cout << " " << symbol << " ";
        }
        cout << endl;
    }
}

void MattBlocks::display_positions(const Positions &positions) {
    cout << "****     Positions     ****";

    for (const auto &symbol : positions) {
        cout << " " << symbol.first << " : ";
        for (const auto &symbol_positions : symbol.second) {
            for (const auto &position : symbol_positions) {
                cout << " " << position.first << " : " << position.second;
            }
        }
        cout << endl;
    }

}

Positions MattBlocks::find_symbols_positions() {

    Positions symbols_positions;

    for (const auto &symbol_payout : PAYOUT) {
        const int &symbol = symbol_payout.first;
        list<list<pair<string, int>>> positions;
        for (const auto &row : SCREEN) {
            for (const auto &screen_symbol : row) {
                if (screen_symbol == symbol || screen_symbol == WILD) {
                    positions.push_back(
                            {
                                    {"x", 1},
                                    {"y", 1}
                            }
                    );
                }
            }
        }
    }

    return symbols_positions;

/*    for symbol in payout:
    positions = []
    for x, row in enumerate(screen):
    for y, screen_symbol in enumerate(row):
    if screen_symbol == symbol or screen_symbol == wild:
    positions.append({'x': x, 'y': y})

    if len(positions) > 0:
    symbols_positions[symbol] = positions

    return symbols_positions*/

}

void MattBlocks::display_blocks(const Blocks &blocks) {

}