#include <iostream>
#include "gallery_manager.h"

int main(int argc, char** fileName) {
    gallery_manager greg;
    string file = fileName[1];
    greg.make_gallery(file);
    greg.make_gallery_output();
}
