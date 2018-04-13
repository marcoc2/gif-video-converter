#include <iostream>

#include "GifLoader.h"
#include "VideoDecoder.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "USAGE: $ program file.gif" << endl;
        return 0;
    }

    string filePath = argv[1];

    // Load animated GIF
    GifLoader::loadGif(filePath);

    // Decode video
    VideoDecoder::decodeVideo(filePath);

    return 0;
}
