#ifndef GIFLOADER_H
#define GIFLOADER_H

#include <iostream>

class GifLoader
{
public:
    GifLoader();

    static void loadGif(std::string filePath);
};

#endif // GIFLOADER_H
