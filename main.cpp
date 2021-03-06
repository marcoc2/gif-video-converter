#include <iostream>
#include <vector>
#include <QImage>
#include <boost/program_options.hpp>

#include "GifLoader.h"
#include "VideoDecoder.h"
#include "VideoEncoder.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        cout << "USAGE: $ program [OPTIONS] file.gif" << endl;
        return 0;
    }

    string direction = argv[1];
    string filePath = argv[2];

    int isG2V = direction.compare("g2v");
    int isGIF2VID = direction.compare("gif2vid");
    int isV2G = direction.compare("v2g");
    int isVID2GIF = direction.compare("vid2gif");

    if(isG2V == 0 || isGIF2VID == 0)
    {
        auto frames = GifLoader::loadGif(filePath);
        if(!VideoEncoder::encodeVideo(frames))
            return 1;
    }
    else if(isV2G == 0 || isVID2GIF)
        VideoDecoder::decodeVideo(filePath);
    else
        return 1;

    return 0;
}
