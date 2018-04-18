#include "GifLoader.h"

#include <QImageReader>
#include <QDir>

GifLoader::GifLoader()
{

}

std::vector<QImage> GifLoader::loadGif(std::string filePath)
{
    QImageReader qImageReader( QDir::currentPath() + "/" + QString(filePath.c_str()) );

    std::cout << "Input gif have " << qImageReader.imageCount() << " frames" << std::endl;
    qImageReader.jumpToImage(0);
    std::cout << "Frame resolution: " <<  qImageReader.read().width() << " x "<< qImageReader.read().height() << std::endl;

    std::vector<QImage> animatedGif;

    if( qImageReader.supportsAnimation() && ( qImageReader.imageCount() > 1 ) )
    {
        for( int i = 0; i < qImageReader.imageCount(); i++ )
        {
            qImageReader.jumpToImage( i );
            animatedGif.push_back( qImageReader.read() );
        }
    }

    return animatedGif;
}
