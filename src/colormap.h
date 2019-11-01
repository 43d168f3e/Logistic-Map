// colormap.h
/*
#include "colormap.h"
#include "src/colormap.h"
*/

#if !defined(COLORMAP_H_as5435741bc550b53c48ab80a4232466ea81af)
#define	  COLORMAP_H_as5435741bc550b53c48ab80a4232466ea81af



struct SCREENDATA
{
//typedef unsigned int QRgb;                        // RGB triplet
    using QRgb = std::uint32_t ;                        // RGB triplet
// non-namespaced Qt global variable
const  QRgb  RGB_MASK    = 0x00ffffff;     // masks RGB values
inline Q_DECL_CONSTEXPR QRgb qRed(QRgb rgb)                // get red part of RGB
{ return ((rgb >> 16) & 0xff); }
inline Q_DECL_CONSTEXPR QRgb qGreen(QRgb rgb)                // get green part of RGB
{ return ((rgb >> 8) & 0xff); }
inline Q_DECL_CONSTEXPR QRgb qBlue(QRgb rgb)                // get blue part of RGB
{ return (rgb & 0xff); }
inline Q_DECL_CONSTEXPR QRgb qAlpha(QRgb rgb)                // get alpha part of RGBA
{ return rgb >> 24; }
inline Q_DECL_CONSTEXPR QRgb qRgb(int r, int g, int b)// set RGB value
{ return (0xffu << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu); }
std::uint32_t rgbFromWaveLength(double wave)
{
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;

    if (wave >= 380.0 && wave <= 440.0) {
        r = -1.0 * (wave - 440.0) / (440.0 - 380.0);
        b = 1.0;
    } else if (wave >= 440.0 && wave <= 490.0) {
        g = (wave - 440.0) / (490.0 - 440.0);
        b = 1.0;
    } else if (wave >= 490.0 && wave <= 510.0) {
        g = 1.0;
        b = -1.0 * (wave - 510.0) / (510.0 - 490.0);
    } else if (wave >= 510.0 && wave <= 580.0) {
        r = (wave - 510.0) / (580.0 - 510.0);
        g = 1.0;
    } else if (wave >= 580.0 && wave <= 645.0) {
        r = 1.0;
        g = -1.0 * (wave - 645.0) / (645.0 - 580.0);
    } else if (wave >= 645.0 && wave <= 780.0) {
        r = 1.0;
    }

    double s = 1.0;
    if (wave > 700.0)
        s = 0.3 + 0.7 * (780.0 - wave) / (780.0 - 700.0);
    else if (wave <  420.0)
        s = 0.3 + 0.7 * (wave - 380.0) / (420.0 - 380.0);

    r = std::pow(r * s, 0.8);
    g = std::pow(g * s, 0.8);
    b = std::pow(b * s, 0.8);
    return qRgb(int(r * 255), int(g * 255), int(b * 255));
}

   int      g_default___screen_width;
   int      g_default___screen_height;
   int      row_y;
    enum { ColormapSize = 512 };
    uint colormap[ColormapSize];
    SCREENDATA(){
    for (int i = 0; i < ColormapSize; ++i)
        colormap[i] = rgbFromWaveLength(380.0 + (i * 400.0 / ColormapSize));
    }
} static g_control;


#endif // COLORMAP_H_as5435741bc550b53c48ab80a4232466ea81af
