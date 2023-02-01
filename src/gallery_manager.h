//
// Created by Caleb Moore on 9/10/21.
//

#ifndef INC_21F_PA01_CALEB_S_TEAM_GALLERY_MANAGER_H
#define INC_21F_PA01_CALEB_S_TEAM_GALLERY_MANAGER_H

#include "gallery.h"
#include <string>

using namespace std;

class gallery_manager{
private:
    string s;
    gallery g;
public:
    void make_gallery(string&);
    void make_gallery_output();
};
#endif //INC_21F_PA01_CALEB_S_TEAM_GALLERY_MANAGER_H
