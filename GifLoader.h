#ifndef GIFLOADER_H
#define GIFLOADER_H

#include <iostream>
#include <vector>
#include <QImage>

class GifLoader
{
public:
    GifLoader();

    static std::vector<QImage> loadGif(std::string filePath);
};

#endif // GIFLOADER_H
