
#if 0
colorize_map.h
#include "colorize_map.h"
#include "src/colorize_map.h"
#include "../src/colorize_map.h"
#endif


#if !defined(COLORIZE_MAP_H_A27b4567fghj53898441d9383f44ee6159a9f)
#define COLORIZE_MAP_H_A27b4567fghj53898441d9383f44ee6159a9f




#include "global.h"
//#include <QColor>
#include "colormap.h"


// data_t  Assemble_block::output;
#include <QSize>
#include <QImage>
///////////////////////////////////////////////////////////////////////////////
/// \brief The Assemble_block class
///
class Colorize_map {

public:
    Colorize_map() {}
///////////////////////////////////////////////////////////////////////////////
static void colorize(std::uint32_t * buffer, QRgb const g_default___screen_width, QRgb const g_default___screen_height, bool useColor) {
        std::uint32_t imin{1};
        std::uint32_t imax{1};
        std::uint32_t iwidth{1};
        auto cmap = [&imin,&iwidth](std::uint32_t a)->std::uint32_t{return (static_cast<std::uint32_t>( ( (g_control.ColormapSize-1)*(a-imin) )/iwidth) );};
        for ( QRgb row_y = 0; row_y < g_default___screen_height; ++row_y ) {
                std::uint32_t const * const x = &buffer[row_y*g_default___screen_width];
    /*auto*/ std::pair<std::uint32_t const * const, std::uint32_t const * const>  result = std::minmax_element(&x[0], &x[g_default___screen_width-1]);
                imin = *result.first;
                imax = *result.second;
                iwidth = imax - imin;
                if (iwidth == 0) iwidth = 1;
//auto map = [imin,iwidth](std::uint32_t a)->std::uint32_t{return ((g_control.ColormapSize*(a-imin))/iwidth) % g_control.ColormapSize ;};
                for ( QRgb col_x = 0; col_x < g_default___screen_width; ++col_x) {
                    QRgb &p         = buffer[row_y*g_default___screen_width+col_x];
    //QRgb qRgb(int r, int g, int b)
    //Returns the ARGB quadruplet (255, r, g, b).
                    if (useColor) {
                        p = p > 0 ? g_control.colormap[ /*q % g_control.ColormapSize*/ cmap(/*x[col_x]*/ p ) ] : qRgb(255, 255, 255);
                    }
                    else {
                        p = p > 0 ? qRgb(0, 0, 0) : qRgb(255, 255, 255);
                    }
                }
            }

//QImage img( QSize(g_default___screen_width, g_default___screen_height), QImage::Format_RGB32 );
//std::memcpy(img.bits(), buffer, g_default___screen_height * g_default___screen_width * sizeof(QRgb)  );
        //emit renderedImage( img.mirrored(false,true)  );
        //emit updateAfterRenderedImage();

    }
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
    static data_t Colorize(/*std::uint32_t * buffer, */
                          QRgb const g_default___screen_width, QRgb const g_default___screen_height, bool useColor, std::uint32_t * buffer) {
//using data_t = std::vector<QRgb>;
        data_t mem_( g_default___screen_width*g_default___screen_height /* *sizeof (QRgb) */ , 0);
        std::uint32_t * buffer_out = &mem_[0];
        std::uint32_t imin{1};
        std::uint32_t imax{1};
        std::uint32_t iwidth{1};
        auto cmap = [&imin,&iwidth](std::uint32_t a)->std::uint32_t{return (static_cast<std::uint32_t>( ( (g_control.ColormapSize-1)*(a-imin) )/iwidth) );};
        for ( QRgb row_y = 0; row_y < g_default___screen_height; ++row_y ) {
                std::uint32_t const * const x = &buffer[row_y*g_default___screen_width];
    /*auto*/ std::pair<std::uint32_t const * const, std::uint32_t const * const>  result = std::minmax_element(&x[0], &x[g_default___screen_width-1]);
                imin = *result.first;
                imax = *result.second;
                iwidth = imax - imin;
                if (iwidth == 0) iwidth = 1;
//auto map = [imin,iwidth](std::uint32_t a)->std::uint32_t{return ((g_control.ColormapSize*(a-imin))/iwidth) % g_control.ColormapSize ;};
                for ( QRgb col_x = 0; col_x < g_default___screen_width; ++col_x) {
                  //QRgb &p         = buffer[row_y*g_default___screen_width+col_x];
                    QRgb &p         = buffer_out[row_y*g_default___screen_width+col_x];
    //QRgb qRgb(int r, int g, int b)
    //Returns the ARGB quadruplet (255, r, g, b).
                    if (useColor) {
                        p = p > 0 ? g_control.colormap[ /*q % g_control.ColormapSize*/ cmap(/*x[col_x]*/ p ) ] : qRgb(255, 255, 255);
                    }
                    else {
                        p = p > 0 ? qRgb(0, 0, 0) : qRgb(255, 255, 255);
                    }
                }
            }

//QImage img( QSize(g_default___screen_width, g_default___screen_height), QImage::Format_RGB32 );
//std::memcpy(img.bits(), buffer, g_default___screen_height * g_default___screen_width * sizeof(QRgb)  );
        //emit renderedImage( img.mirrored(false,true)  );
        //emit updateAfterRenderedImage();
return mem_;
    }
///////////////////////////////////////////////////////////////////////////////

};
//////////////////////////////////////////////////////////////////////////////////////////
#endif // COLORIZE_MAP_H_A27b4567fghj53898441d9383f44ee6159a9f
