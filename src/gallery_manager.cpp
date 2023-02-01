//
// Created by Caleb Moore on 9/10/21.
//

#include "gallery_manager.h"

void gallery_manager::make_gallery(string & S) {
    s = S;
    g.load_file(s);
    g.val_first();
    g.custom();
    if(g.runBrute()) {
        g.brute();
    }
}

void gallery_manager::make_gallery_output() {
    s = s.substr(0, (s.length() - 4));
    string s1 = s + "-bruteforce.txt";
    string s2 = s + "-highvalue.txt";
    string s3 = s + "-custom.txt";

    g.makeBrute(s1);
    g.makeHigh(s2);
    g.makeCustom(s3);
}
