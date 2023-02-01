//
// Created by Caleb Moore on 8/25/21.
//

#ifndef INC_21F_PA01_CALEB_S_TEAM_GALLERY_H
#define INC_21F_PA01_CALEB_S_TEAM_GALLERY_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

class gallery{
private:
    unordered_map<int, int> pricePairs; //id, price
    unordered_map<int, pair<int, int>> dimensions;
    multimap<int, int> ordered_price; //price, id
    unordered_map<int, pair<int, int>> coordinateHigh;
    set<int> highest_placed;
    int highInt = 0;
    unordered_map<int, pair<int, int>> coordinateCustom;
    set<int> custom_placed;
    int customInt = 0;
    unordered_map<int, pair<int, int>> coordinateBrute;
    set<int> highest_brute;
    int bruteInt = 0;
    int max_x = 0;
    int max_y = 0;
    int current_y;
    int current_x;
    int pieces;
    bool doBrute = false;
    ofstream output;
public:
    void load_file(string&);
    void val_first();
    void custom();
    bool runBrute();
    void brute();

    //make the files
    void makeBrute(string &);
    void makeHigh(string &);
    void makeCustom(string &);
};

#endif //INC_21F_PA01_CALEB_S_TEAM_GALLERY_H
