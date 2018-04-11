#include <iostream>

#include <QImageReader>

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

    QImageReader qImageReader( gifPath.c_str() );
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

    cout << gifPath << endl;
    return 0;
}
