
//
// Created by Caleb Moore on 8/25/21.
//

#include "gallery.h"

//function to load gallery file
void gallery::load_file(string & fileName) {
    ifstream in;

    //open the file for the gallery pieces
    in.open(fileName);

    //check if the file has opened
    if(!in.is_open()){
        std::cout << "gallery file failed to open" << std::endl;
    }
    else{
        //file opened, so load data
        in >> max_x;
        in >> max_y;
        in >> pieces;

        //check if brute will be run
        if (pieces < 11){
            doBrute = true;
        }
        int tempID;
        int tempX;
        int tempY;
        int tempVal;
        //loop through pieces
        for(int i = 0; i < pieces; i++){
            in >> tempID;
            in >> tempVal;
            in >> tempX;
            in >> tempY;

            pricePairs.emplace(tempID, tempVal);
            ordered_price.emplace(tempVal, tempID);
            dimensions.emplace(tempID, make_pair(tempX, tempY));

        }
    }
}

void gallery::val_first() {
    //using a shelf next fit algo discussed in the text "a thousand ways to back the bin" by Jukka Jylanki
    map<int, int>::reverse_iterator rit;
    current_x = 0;
    current_y = 0;
    //dont change actual max x and y
    int totalX = max_x;
    int totalY = max_y;
    for(rit = ordered_price.rbegin(); rit != ordered_price.rend(); rit++){
        //note: seconds are y firsts are x

        //see if it fits current shelf
        if(dimensions[rit->second].second < current_y && dimensions[rit->second].first < current_x){
            coordinateHigh.emplace(rit->second, make_pair(max_x - current_x, max_y - totalY - current_y));
            current_x -= dimensions[rit->second].first;
            highest_placed.emplace(rit->second);
            highInt += pricePairs[rit->second];
        }
        //see if it would fit in a new shelf
        else if(dimensions[rit->second].second < totalY && dimensions[rit->second].first < totalX){
            current_y = dimensions[rit->second].second;
            coordinateHigh.emplace(rit->second, make_pair(0, (max_y - totalY)));
            totalY -= dimensions[rit->second].second;
            current_x = totalX - dimensions[rit->second].first;
            highest_placed.emplace(rit->second);
            highInt += pricePairs[rit->second];
        }
        //ignores if it can't fit into current or new shelf
    }
}

//place in order of most expensive square unit
void gallery::custom() {
    current_x = 0;
    current_y = 0;
    //dont change actual max x and y
    int totalX = max_x;
    int totalY = max_y;

    //make a map of the price per square unit values as sorted keys
    double temp;
    multimap<double, int> customMap;
    for(auto o : ordered_price){
        temp = double(o.first) / double(dimensions[o.second].first * dimensions[o.second].second);
        customMap.emplace(temp, o.second);
    }

    //now use the new map to place the paintings with the same next fit shelf algorithm
    map<double, int>::reverse_iterator rit;

    for(rit = customMap.rbegin(); rit != customMap.rend(); rit++){
        //note: seconds are y firsts are x

        //see if it fits current shelf
        if(dimensions[rit->second].second < current_y && dimensions[rit->second].first < current_x){
            coordinateCustom.emplace(rit->second, make_pair(max_x - current_x, max_y - totalY - current_y));
            current_x -= dimensions[rit->second].first;
            custom_placed.emplace(rit->second);
            customInt += pricePairs[rit->second];
        }
            //see if it would fit in a new shelf
        else if(dimensions[rit->second].second < totalY && dimensions[rit->second].first < totalX){
            coordinateCustom.emplace(rit->second, make_pair(0, (max_y - totalY)));
            current_y = dimensions[rit->second].second;
            totalY -= dimensions[rit->second].second;
            current_x = totalX - dimensions[rit->second].first;
            custom_placed.emplace(rit->second);
            customInt += pricePairs[rit->second];
        }
        //ignores if it can't fit into current or new shelf
    }
}

void gallery::brute() {
    //use a 'shelf next fit' that makes use of previous shelves so all elements get a chance and use every painting as a starting piece
    //I realize this is not the most efficient but im not too concerned since it's only running on < 11 elements
    set<int> currBrute;
    int bestVal = 0;
    int currVal;
    vector<int> orders;
    set<pair<int, int>> shelves;
    bool fit;
    unordered_map<int, pair<int, int>> tempCoordinateBrute;

    //make vector to shift starting order
    for(auto o : ordered_price){
        orders.push_back(o.second);
    }

    //go through the vector starting with each painting once
    int start = orders[0];
    int temp;
    do {
        //make temp variables
        int totalX = max_x;
        int totalY = max_y;
        currVal = 0;
        currBrute.clear();
        tempCoordinateBrute.clear();

        //start with element one and try and place them all afterwards
        for(int & order : orders){
            //check already open shelves
            fit = false;
            int currY = 0;
            for(auto s : shelves){
                if(dimensions[order].first < s.first && dimensions[order].second < s.second){
                    currBrute.emplace(order);
                    currVal += pricePairs[order];
                    tempCoordinateBrute.emplace(order, make_pair(max_x - s.first, currY));
                    s.first -= dimensions[order].first;
                    fit = true;
                    break;
                }
                currY += s.second;
            }

            //see if it did not fit in a current shelf see if there is room for a new one
            if(!fit){
                if(dimensions[order].second < totalY && dimensions[order].first < totalX) {
                    shelves.emplace(make_pair((totalX - dimensions[order].first), dimensions[order].second));
                    tempCoordinateBrute.emplace(order, make_pair(0, (max_y - totalY)));
                    totalY -= dimensions[order].second;
                    currBrute.emplace(order);
                    currVal += pricePairs[order];
                }
            }
        }

        //evaluate how good that one was
        if (currVal > bestVal){
            bestVal = currVal;
            bruteInt = currVal;
            coordinateBrute = tempCoordinateBrute;
            highest_brute = currBrute;
        }

        //rotate elements;
        temp = orders[0];
        for(int i = 1; i < orders.size(); i++){
            orders[i - 1] = orders[i];
        }
        orders[orders.size() - 1] = temp;
    } while(orders[0] != start);
}

void gallery::makeBrute(string & s) {
    output.open(s);
    //see which output to give
    if(!doBrute){
        output << "data set size exceeds maximum" << "\n";
        output.close();
        return;
    }
    output << bruteInt << '\n';
    for(auto p : highest_brute){
        output << p << " " <<
            pricePairs[p] << " " <<
            dimensions[p].first << " " <<
            dimensions[p].second << " " <<
            coordinateBrute[p].first << " " <<
            coordinateBrute[p].second << '\n';
    }
    output.close();
}

void gallery::makeHigh(string & s) {
    output.open(s);
    output << highInt << '\n';
    for(auto p : highest_placed){
        output << p << " " <<
               pricePairs[p] << " " <<
               dimensions[p].first << " " <<
               dimensions[p].second << " " <<
               coordinateHigh[p].first << " " <<
               coordinateHigh[p].second << '\n';
    }
    output.close();
}

void gallery::makeCustom(string & s) {
    output.open(s);
    output << customInt << '\n';
    for(auto p : custom_placed){
        output << p << " " <<
               pricePairs[p] << " " <<
               dimensions[p].first << " " <<
               dimensions[p].second << " " <<
               coordinateCustom[p].first << " " <<
               coordinateCustom[p].second << '\n';
    }
    output.close();
}

bool gallery::runBrute() {
    if(doBrute){
        return true;
    }
    return false;
}
