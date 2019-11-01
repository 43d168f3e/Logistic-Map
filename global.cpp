// global.cpp

#include "global.h"
#if 0
global.h
#include "global.h"
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/include
#endif


#if 0

0 <=  col_x <= (g_default___screen_width   - 1) ) ;  x_min_mpf <= x_t <= x_max_mpf
0 <=  row_y <= (g_default___screen_height  - 1) ) ;  y_min_mpf <= y_t <= y_max_mpf


	x_t = x_min_mpf + ( ( x_max_mpf - x_min_mpf )  / (g_default___screen_width   - 1) ) * col_x ;
	y_t = y_min_mpf + ( ( y_max_mpf - y_min_mpf )  / (g_default___screen_height  - 1) ) * row_y ;


	width_t  = x_max_mpf - x_min_mpf;
	height_t = y_max_mpf - y_min_mpf;

	x_t = x_min_mpf + ( width_t   / (g_default___screen_width   - 1) ) * col_x ;
	y_t = y_min_mpf + ( height_t  / (g_default___screen_height  - 1) ) * row_y ;

	normalized_width_t  = width_t  / (g_default___screen_width  - 1);
	normalized_height_t = height_t / (g_default___screen_height - 1);

	x_t = x_min_mpf + normalized_width_t  * col_x ; col_t = (x_t - x_min_mpf)/normalized_width_t;
	y_t = y_min_mpf + normalized_height_t * row_y ; row_t = (y_t - y_min_mpf)/normalized_height_t;


	rate_t = y_min_mpf + normalized_height_t * row_y; // ==  y_min_mpf + (y_max_mpf - y_min_mpf) * ( row_y / (g_default___screen_height-1) )
#endif
#if 0
#endif

map_buffer_t map_buffer::g_logisticMaps;

quotientANDmodulo_t quotientANDmodulo(QRgb numTHREADS)//, QRgb screen_height)
{
    quotient_t quotient    = g_default___screen_height / numTHREADS;//static_cast<std::uint32_t> ( g_default___screen_height/numTHREADS );
    modulo_t modulo      = g_default___screen_height % numTHREADS;
    assert(g_default___screen_height == quotient * numTHREADS + modulo);
    Q_ASSERT(g_default___screen_height == quotient * numTHREADS + modulo);
    return /*quotientANDmodulo*/{ /*nrows =*/ quotient, /*remainder =*/ modulo};
}

void calculate_area_begin_end_id(vec_idANDbeginANDendANDarea &vibeA, QRgb numTHREADS)//, QRgb screen_width, QRgb screen_height)
{
    vibeA.clear();
    vibeA.reserve(numTHREADS);
    begin_t begin{0};
    end_t end{0};
    area_t area{0};
    auto [nrows, remainder] = quotientANDmodulo(numTHREADS);

    auto indices = ranges::view::iota(0u, numTHREADS);
//PLN: for (const auto& b : indices) is replaced by
//RANGES_FOR(auto i, indices) {  const auto& b=i; }
    RANGES_FOR(auto i, ranges::view::iota(0u, numTHREADS)) {
        const auto& id=i;
        begin = static_cast<begin_t>(id*nrows);
    if (id == (numTHREADS - 1)) {
        end    = static_cast<end_t>(g_default___screen_height - 1);
        area = static_cast<area_t>( (nrows + remainder) * g_default___screen_width );
    }
    else {
        end    = static_cast<end_t>( (id+1)*nrows - 1);
        area = static_cast<area_t>( nrows * g_default___screen_width );
    }
    assert(area == static_cast<area_t>( (end - begin + 1) * g_default___screen_width ));
    vibeA.emplace_back(static_cast<ID_t>(id), begin, end, area);
   }
}
///////////////////////////////////////////////////////////////////////////////
vec_idANDbeginANDendANDarea
calculate_area_begin_end_id(QRgb numTHREADS/*, QRgb screen_width, QRgb screen_height*/) {
    vec_idANDbeginANDendANDarea vibeA;
    //extern vec_idANDbeginANDendANDarea vibeA;
    vibeA.reserve(numTHREADS);
    begin_t begin{0};
    end_t end{0};
    area_t area{0};
    auto [nrows, remainder] = quotientANDmodulo(numTHREADS);

    auto indices = ranges::view::iota(0u, numTHREADS);
//PLN: for (const auto& b : indices) is replaced by
//RANGES_FOR(auto i, indices) {  const auto& b=i; }
    RANGES_FOR(auto i, ranges::view::iota(0u, numTHREADS)) {
        const auto& id=i;
        begin = static_cast<begin_t>(id*nrows);
    if (id == (numTHREADS - 1)) {
        end    = static_cast<end_t>(g_default___screen_height - 1);
        area = static_cast<area_t>( (nrows + remainder) * g_default___screen_width );
    }
    else {
        end    = static_cast<end_t>( (id+1)*nrows - 1);
        area = static_cast<area_t>( nrows * g_default___screen_width );
    }
    assert(area == static_cast<area_t>( (end - begin + 1) * g_default___screen_width ));
    //data_t mem;
    vibeA.emplace_back(static_cast<ID_t>(id), begin, end, area/*, mem*/);
   }
#if 0
//for (auto id : boost::irange<std::uint32_t>(0, numTHREADS-1) ) {
//for (auto id : boost::irange<ID_t>(0, numTHREADS-1) ) {
// // counting_range() returns a range of numbers from the half-open interval
    for ( auto id : boost::counting_range(0, static_cast<int>(numTHREADS) )  ) {
//    begin_t begin = id*nrows;ID_t
//    end_t end   = (id+1)*nrows - 1;
//    if (id == (numTHREADS - 1)) {
//        end = g_default___screen_height - 1;
//    }
    begin = static_cast<begin_t>(id*nrows);
    if (id == (numTHREADS - 1)) {
        end    = static_cast<end_t>(g_default___screen_height - 1);
        area = static_cast<area_t>( (nrows + remainder) * g_default___screen_width );
        //memset(_d.get(), 0, (nrows + remainder) * g_default___screen_width * sizeof (QRgb));
    }
    else {
        end    = static_cast<end_t>( (id+1)*nrows - 1);
        area = static_cast<area_t>( nrows * g_default___screen_width );
        //memset(_d.get(), 0, nrows * g_default___screen_width * sizeof (QRgb));
    }
    vibeA.emplace_back(static_cast<ID_t>(id), begin, end, area);
}
#endif
    return vibeA;
}
