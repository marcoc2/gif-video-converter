#ifndef VIDEOENCODER_H
#define VIDEOENCODER_H

#include <vector>
#include <QImage>

class VideoEncoder
{
public:
    VideoEncoder();

    static bool encodeVideo(std::vector<QImage> frames);
};

#endif // VIDEOENCODER_H
