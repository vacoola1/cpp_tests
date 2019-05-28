//
// Created by roman on 01.05.19.
//

#ifndef CPP_TESTS_MATTBLOCKS_H
#define CPP_TESTS_MATTBLOCKS_H

#include <list>
#include <map>

using namespace std;


typedef list<list<int>> Screen;
typedef map<int, map<int, int>> SymbolsPayout;
typedef map<std::string, int> Position;
typedef map<int, list<Position>> SymbolsPositions;
typedef list<Position> Block;
typedef map<int, list<Block>> SymbolsBlocks;

class MattBlocks {
public:
    void run();

private:
    int symbol_payout(int symbol, int count, SymbolsPayout payout);

    void display_screen(const Screen &screen);

    void display_positions(const SymbolsPositions &positions);

    void display_blocks(const SymbolsBlocks &blocks);

    void display_blocks_symple(const SymbolsBlocks &blocks);

    SymbolsPositions find_symbols_positions();

    bool stacked(const Position &pos1, const Position &pos2);

    list<Block> group_positions(const list<Position> &positions);

    SymbolsBlocks find_symbols_blocks(const SymbolsPositions &symbolsPositions);
};


#endif //CPP_TESTS_MATTBLOCKS_H
