#include "VideoEncoder.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavutil/common.h"
#include "libavutil/imgutils.h"
}

VideoEncoder::VideoEncoder()
{

}

void VideoEncoder::encodeVideo(std::vector<QImage> frames)
{
    QImage image = frames[0];

    int width = 640;
    int height = 480;
    int size = avpicture_get_size(PIX_FMT_YUV420P, width, height);
    uint8_t *pic_dat = (uint8_t *) av_malloc(size);
    RGBtoYUV420P(image.bits(), pic_dat, image.depth()/8, true, width, height);
    avpicture_fill((AVPicture *)frame, pic_dat, PIX_FMT_YUV420P, width, height); // Libav method
}
