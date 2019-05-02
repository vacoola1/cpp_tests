//
// Created by mail@vacoola.name on 01.05.19.
//

#include <list>
#include <map>
#include <iostream>
#include <strings.h>

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

int WILD = 99;

SymbolsPayout PAYOUT =
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

    SymbolsPositions positions = find_symbols_positions();

    display_positions(positions);

    SymbolsBlocks blocks = find_symbols_blocks(positions);

    display_blocks(blocks);

}

int MattBlocks::symbol_payout(int symbol, int count, SymbolsPayout payout) {
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

SymbolsPositions MattBlocks::find_symbols_positions() {

    SymbolsPositions symbols_positions;

    for (const auto &symbol_payout : PAYOUT) {
        const int &symbol = symbol_payout.first;
        list<map<string, int>> positions;

        for (auto row = SCREEN.begin(); row != SCREEN.end(); ++row) {
            int x = distance(SCREEN.begin(), row);
            for (auto screen_symbol = row->begin(); screen_symbol != row->end(); ++screen_symbol) {
                int y = distance(row->begin(), screen_symbol);
                if ((*screen_symbol) == symbol || (*screen_symbol) == WILD) {
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

bool MattBlocks::stacked(const Position &pos1, const Position &pos2) {
    int x1 = pos1.at("x");
    int y1 = pos1.at("y");
    int x2 = pos2.at("x");
    int y2 = pos2.at("y");

    return (x1 == x2 + 1 && y1 == y2) ||
           (x1 + 1 == x2 && y1 == y2) ||
           (x1 == x2 && y1 == y2 + 1) ||
           (x1 == x2 && y1 + 1 == y2);
}

list<Block> MattBlocks::group_positions(const list<Position> &positions) {
    list<Block> blocks;
    if (positions.empty()) {
        return blocks;
    }

    list<Position> positions_copy = list<Position>(positions);

    while (!positions_copy.empty()) {

        list<Position> new_block;
        new_block.push_back((*positions_copy.begin()));
        positions_copy.remove((*positions_copy.begin()));

        bool has_stack = true;
        while (has_stack) {
            has_stack = false;
            for (const auto &pos_in_block : list<Position>(new_block)) {
                for (const auto &pos : list<Position>(positions_copy)) {
                    if (stacked(pos_in_block, pos)) {
                        new_block.push_back(pos);
                        positions_copy.remove(pos);
                        has_stack = true;
                    }
                }
            }
        }

        blocks.push_back(new_block);
    }

    return blocks;
}

SymbolsBlocks MattBlocks::find_symbols_blocks(const SymbolsPositions &symbolsPositions) {
    SymbolsBlocks symbolsBlocks;
    for (const auto &symbolPositions : symbolsPositions) {
        int symbol = symbolPositions.first;
        list<Block> blocks = group_positions(symbolPositions.second);
        symbolsBlocks.insert({symbol, blocks});
    }
    return symbolsBlocks;
}

void MattBlocks::display_screen(const Screen &screen) {
    cout << "****     Screen     ****" << endl;

    for (const auto &row : screen) {
        for (const auto &symbol : row) {
            cout << " " << symbol << " ";
        }
        cout << endl;
    }
}

void MattBlocks::display_positions(const SymbolsPositions &positions) {
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

void MattBlocks::display_blocks(const SymbolsBlocks &blocks) {
    cout << "****     Blocks     ****" << endl;

    for (const auto &block : blocks) {
        cout << " " << block.first << " : " << endl;
        for (const auto &symbol_blocks : block.second) {
            cout << "       [ ";
            for (const auto &block_positions : symbol_blocks) {
                cout << " { ";
                for (const auto &position : block_positions) {
                    cout << " " << position.first << ":" << position.second << " ";
                }
                cout << " } ";
            }
            cout << " ]" << endl;
        }
        cout << endl;
    }
}
