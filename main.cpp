#include <iostream>

#include <QImageReader>
#include <QDir>

#include "gif.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "USAGE: $ program file.gif" << endl;
        return 0;
    }

    string gifPath = argv[1];

    QImageReader qImageReader( QDir::currentPath() + "/" + QString(gifPath.c_str()) );

    cout << "Input gif have " << qImageReader.imageCount() << " frames" << endl;
    qImageReader.jumpToImage(0);
    cout << "Frame resolution: " <<  qImageReader.read().width() << " x "<< qImageReader.read().height() << endl;

    vector<QImage> animatedGif;

    if( qImageReader.supportsAnimation() && ( qImageReader.imageCount() > 1 ) )
    {
        for( int i = 0; i < qImageReader.imageCount(); i++ )
        {
            qImageReader.jumpToImage( i );
            animatedGif.push_back( qImageReader.read() );
        }
    }

    //GifBegin()

    return 0;
}
