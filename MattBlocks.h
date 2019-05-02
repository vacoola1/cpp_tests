//
// Created by roman on 01.05.19.
//

#ifndef CPP_TESTS_MATTBLOCKS_H
#define CPP_TESTS_MATTBLOCKS_H

#include <list>
#include <map>

using namespace std;

typedef list<list<int>> Screen;
typedef map<int, map<int, int>> Payout;
typedef map<int, list<map<string, int>>> Positions;
typedef map<int, list<list<map<string, int>>>> Blocks;



class MattBlocks {
public:
    void run();

private:
    int symbol_payout(int symbol, int count, Payout payout);

    void display_screen(const Screen &screen);

    void display_positions(const Positions &positions);

    void display_blocks(const Blocks &blocks);

    Positions find_symbols_positions();
};


#endif //CPP_TESTS_MATTBLOCKS_H
