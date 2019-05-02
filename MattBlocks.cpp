//
// Created by mail@vacoola.name on 01.05.19.
//

#include <list>
#include <map>
#include <iostream>
#include <strings.h>

#include "MattBlocks.h"

const Screen SCREEN =
        {
                {1, 1, 1, 4, 5, 6, 7},
                {1, 2, 3, 4, 5, 6, 7},
                {1, 2, 3, 4, 5, 6, 6},
                {1, 1, 6, 1, 5, 6, 6},
                {1, 2, 3, 1, 8, 8, 7},
                {1, 2, 3, 4, 8, 8, 7}
        };

const int WILD = 2;

const Payout PAYOUT =
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
    cout << "****     Positions     ****" << endl;

    for (const auto &symbol : positions) {
        cout << " " << symbol.first << " : ";
        for (const auto &symbol_positions : symbol.second) {
            cout << " { ";
            for (const auto &position : symbol_positions) {
                cout << " " << position.first << ":" << position.second << " ";
            }
            cout << " } ";
        }
        cout << endl;
    }

}

Positions MattBlocks::find_symbols_positions() {

    Positions symbols_positions;

    for (const auto &symbol_payout : PAYOUT) {
        const int &symbol = symbol_payout.first;
        list<map<string, int>> positions;

        for (auto row = SCREEN.begin(); row != SCREEN.end(); ++row) {
            int x = distance(SCREEN.begin(), row);
            for (auto screen_symbol = row->begin(); screen_symbol != row->end(); ++screen_symbol) {
                int y = distance(row->begin(), screen_symbol);
                if ((*screen_symbol) == symbol) {
                    positions.push_back(
                            {
                                    {"x", x},
                                    {"y", y}
                            }
                    );
                }
            }
        }

        symbols_positions.insert({symbol, positions});
    }

    return symbols_positions;
}

void MattBlocks::display_blocks(const Blocks &blocks) {

}