#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include <iostream>

class VideoDecoder
{
public:
    VideoDecoder();

    static void decodeVideo(std::string filePath);
};

#endif // VIDEODECODER_H
