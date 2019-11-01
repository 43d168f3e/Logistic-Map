#if 0
assemble_block.h
#include "assemble_block.h"
#include "src/assemble_block.h"
#include "../src/assemble_block.h"
#endif

#if !defined(ASSEMBLE_BLOCK_H_A27b82c953898441d9383f44ee6159a9f)
#define ASSEMBLE_BLOCK_H_A27b82c953898441d9383f44ee6159a9f

#include "fill_in_vector.h"
#include "colormap.h"
#include "colorize_map.h"
#include <QSize>
#include <QImage>
///////////////////////////////////////////////////////////////////////////////
/// \brief The Assemble_block class
///
class Assemble_block : public QObject {

Q_OBJECT
public:
    Assemble_block() : QObject{}{}
///////////////////////////////////////////////////////////////////////////////
    std::size_t assemble(bool useColor){
/*
The classes listed below automatically detach from common data if an object is about to be changed.
"The programmer will not even notice that the objects are shared."
Thus you should treat separate instances of them as separate objects.
They will always behave as separate objects
... QByteArray ... QImage

*/
        data_t data(g_uint32_t_size,0);
        std::uint8_t* buffer = reinterpret_cast<std::uint8_t*>( &data[0] );

        using namespace NS_LogisticMap;

        std::cout << " ID_T= " << static_cast<int> (TUPL::ID_T)
                  << "; BEGIN_T= " << static_cast<int> (TUPL::BEGIN_T)
                  << "; END_T= " << static_cast<int> (TUPL::END_T)
                  << "; AREA_T= " << static_cast<int> (TUPL::AREA_T)
                  << std::endl << std::flush;


        for (auto &e : Fill_in_vector::g_vec_mem_tup_ibeA_t) {
            ID_t id_      {std::get< static_cast<int> (TUPL::ID_T)    >(e.second)};
            begin_t begin_{std::get< static_cast<int> (TUPL::BEGIN_T) >(e.second)};
            end_t   end_  {std::get< static_cast<int> (TUPL::END_T)   >(e.second)};
            area_t area_  {std::get< static_cast<int> (TUPL::AREA_T)  >(e.second)};
            data_t mem_ = e.first;
#if 0
template <typename T, std::size_t N>
using iadp = T[][N] ;
template <typename T, std::size_t N>
using aTN = T (&)[][N] ;

auto const lambda = [](int const (&arr)[size]) -> void
auto const lambda = [](auto& arr) -> void

tws |ranges::view::transform([](Tweet tw){
auto& tweet = tw.data->tweet;
return tweettext(tweet);
});
using _Ax = QRgb[end_-begin_+1][g_default___screen_width];

data_t out = Colorize(g_default___screen_width, g_default___screen_height, true, reinterpret_cast<std::uint32_t*>(buffer)); /*buffer | ranges::view::transform([g_default___screen_width, g_default___screen_height, this](auto tw){
        return Colorize(g_default___screen_width, g_default___screen_height, true, tw);
        });*/

static_cast<const QRgb>()
#endif

auto dest = const_cast<void*>( (const void *) (   ( (const char *)buffer ) + begin_ * g_default___screen_width * sizeof(data_t::value_type) ) );

data_t::const_pointer const src  =  reinterpret_cast<const QRgb*>( &mem_[0] );
std::memcpy(dest, src, ( end_  - begin_ + 1 ) * g_default___screen_width * sizeof(data_t::value_type)  );

        std::cout << "ID[" << id_ << "]: " << std::hex   << static_cast<std::size_t>( (long)dest ) << std::dec  ;//<< std::endl;

        printf("; Thread %d did %d to %d;",id_ ,begin_ ,end_ );//bugged =>
        std::cout << std::endl;

    }

        QImage image( QSize{ g_default___screen_width , g_default___screen_height }, QImage::Format_RGB32 );//QSize(g_default___screen_width, g_default___screen_height)
        unsigned char* buuffer = image.bits();
        memset(buuffer, 0, g_default___screen_width * g_default___screen_height * sizeof (QRgb));

        std::memcpy(buuffer, buffer, g_default___screen_width * g_default___screen_height * sizeof (QRgb));
        Colorize_map::colorize( reinterpret_cast<std::uint32_t*>(buuffer), static_cast<const QRgb>(g_default___screen_width), static_cast<const QRgb>(g_default___screen_height), useColor);
        std::size_t ret = g_Logistic_Map_HISTORY_database.load( std::move( data ) );
        emit map( image.mirrored(false,true)  );
        return ret;
    }

signals:
void map(QImage const &image);//std::size_t const n, QRgb *buffer);
};
//////////////////////////////////////////////////////////////////////////////////////////
#endif // ASSEMBLE_BLOCK_H_A27b82c953898441d9383f44ee6159a9f
