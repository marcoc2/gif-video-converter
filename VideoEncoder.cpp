#include "VideoEncoder.h"
#include "ImageUtils.h"
#include <opencv2/imgproc/imgproc.hpp>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavutil/common.h"
#include "libavutil/imgutils.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

// Source: http://www.ffmpeg.org/doxygen/3.0/avpacket_8c_source.html
static AVPacket *av_packet_alloc(void)
{
    AVPacket *pkt = static_cast<AVPacket*>( av_mallocz(sizeof(AVPacket)) );
    if (!pkt)
        return pkt;

    av_packet_unref(pkt);

    return pkt;
}

void av_packet_free(AVPacket **pkt)
{
    if (!pkt || !*pkt)
        return;

    av_packet_unref(*pkt);
    av_freep(pkt);
}

VideoEncoder::VideoEncoder()
{

}

static void encode(AVCodecContext *enc_ctx, AVFrame *frame, AVPacket *pkt,
                   FILE *outfile)
{
    int ret;

    /* send the frame to the encoder */
    if (frame)
        printf("Send frame %3" PRId64 "\n", frame->pts);


    //ret = avcodec_send_frame(enc_ctx, frame); // DEPRECATED
    //if (ret < 0) {
    //    fprintf(stderr, "Error sending a frame for encoding\n");
    //    exit(1);
    //}

    //while (ret >= 0)
    //{
        int got = 0;
        //ret = avcodec_receive_packet(enc_ctx, pkt); //DEPRECATED
        ret = avcodec_encode_video2(enc_ctx, pkt, frame, &got );
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            fprintf(stderr, "Error during encoding\n");
            exit(1);
        }

        printf("Write packet %3" PRId64 " (size=%5d)\n", pkt->pts, pkt->size);
        fwrite(pkt->data, 1, pkt->size, outfile);
        av_packet_unref(pkt);
    //}
}

bool VideoEncoder::encodeVideo(std::vector<QImage> frames)
{
    QImage image = frames[0];

    av_register_all();

    const AVCodec* codec;
    AVCodecContext* context = nullptr;
    int i, ret, x, y;

    FILE* file;
    AVFrame *picture;
    AVPacket *pkt;

    uint8_t endcode[] = { 0, 0, 1, 0xb7 };

    // Find the mpeg1video encoder
    codec = avcodec_find_encoder(AV_CODEC_ID_MPEG4);

    if (!codec)
    {
        fprintf(stderr, "codec not found\n");
        return false;
    }

    context = avcodec_alloc_context3(codec);

    picture = av_frame_alloc();
    pkt = av_packet_alloc();

    if(!pkt)
        return false;

    // Put sample parameters
    context->bit_rate = 400000;

    // Resolution must be a multiple of two
    //context->width = 352;
    //context->height = 288;
    context->width = image.width();
    context->height = image.height();

    // Frames per second
    context->time_base = {1, 25};
    context->framerate = {25, 1};
    context->gop_size = 10; /* emit one intra frame every ten frames */
    context->max_b_frames = 1;
    context->pix_fmt = AV_PIX_FMT_YUV420P;

    // Open
    if(avcodec_open2(context, codec, NULL) < 0)
    {
        fprintf(stderr, "could not open codec\n");
        return false;
    }

    file = fopen("teste.mp4", "wb");
    if(!file)
    {
        fprintf(stderr, "could not open %s\n", "teste.jpg");
        return false;
    }

    picture->format = context->pix_fmt;
    picture->width  = context->width;
    picture->height = context->height;
    ret = av_frame_get_buffer(picture, 32);
    if(ret < 0)
    {
        fprintf(stderr, "could not alloc the frame data\n");
        return false;
    }

    cv::Mat frame = QImageToCvMat(image);
    cv::cvtColor(frame, frame, cv::COLOR_RGB2YCrCb);

    // initialize sample scaler
    SwsContext* swsctx = sws_getCachedContext(nullptr,
                                              image.width(), image.height(),
                                              AV_PIX_FMT_BGR24,
                                              image.width(), image.height(),
                                              context->pix_fmt, SWS_BICUBIC,
                                              nullptr, nullptr, nullptr);
    if (!swsctx) {
        std::cerr << "fail to sws_getCachedContext";
        return 2;
    }

    for(i=0; i<150 ;i++)
    {
        const int stride[] = { static_cast<int>(frame.step[0]) };
        sws_scale(swsctx, &frame.data, stride, 0, frame.rows, picture->data, picture->linesize);
        picture->pts = i;
        /* encode the image */
        encode(context, picture, pkt, file);
    }


    // Encode 1 second of video
    //for(i=0; i<150 ;i++)
    //{
    //    fflush(stdout);
    //    /* make sure the frame data is writable */
    //    ret = av_frame_make_writable(picture);
    //    if(ret < 0)
    //        return false;
    //    /* prepare a dummy image */
    //    /* Y */
    //    for(y=0;y<context->height;y++) {
    //        for(x=0;x<context->width;x++) {
    //            picture->data[0][y * picture->linesize[0] + x] = x + y + i * 3;
    //        }
    //    }
    //    /* Cb and Cr */
    //    for(y=0;y<context->height/2;y++) {
    //        for(x=0;x<context->width/2;x++) {
    //            picture->data[1][y * picture->linesize[1] + x] = 128 + y + i * 2;
    //            picture->data[2][y * picture->linesize[2] + x] = 64 + x + i * 5;
    //        }
    //    }
    //    picture->pts = i;
    //    /* encode the image */
    //    encode(context, picture, pkt, file);
    //}

    /* flush the encoder */
    encode(context, NULL, pkt, file);
    /* add sequence end code to have a real MPEG file */
    fwrite(endcode, 1, sizeof(endcode), file);
    fclose(file);
    avcodec_free_context(&context);
    av_frame_free(&picture);
    av_packet_free(&pkt);
    return 0;

    /**
    int width = 640;
    int height = 480;
    int size = avpicture_get_size(PIX_FMT_YUV420P, width, height);
    uint8_t *pic_dat = (uint8_t *) av_malloc(size);
    RGBtoYUV420P(image.bits(), pic_dat, image.depth()/8, true, width, height);
    avpicture_fill((AVPicture *)frame, pic_dat, PIX_FMT_YUV420P, width, height); // Libav method
    **/
}
