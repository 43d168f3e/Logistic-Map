
#if 0
global.h
#include "global.h"
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/include
#endif


#if !defined(GLOBAL_H_27b82c95yD3898441d9383f44ee6159a9f)
#define GLOBAL_H_27b82c95yD3898441d9383f44ee6159a9f


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

#include <memory>
#include <vector>
#include <cstdint>

#include <iterator>
#include <numeric>
#include <typeinfo>
#include <stdexcept>
#include <iostream>
#include <tuple>

#include <gmpxx.h>
#include <mpfr.h>

//FYI: the following succeeds because INCLUDEPATH += $$PWD/include
#include <range/v3/all.hpp>

#include <nlohmann/json.hpp>
// for convenience
//using json = nlohmann::json;

///////////////////////////////////////////////////////////////////////////////
/// std::mt19937 mersenne_twister_engine
#include "src/logisticMapBoundaryPostOnsetOfChaos.h"
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
using datum_t = std::uint32_t;
using data_t  = std::vector< datum_t >;
using map_buffer_t = std::vector< data_t >;
using matrix_row_t = std::unique_ptr< datum_t[] >;
using matrix_t     = std::unique_ptr< matrix_row_t[] >;


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// typedef unsigned int QRgb;                        // RGB triplet
// unsigned int
// C++ standard	LP32	ILP32	LLP64	LP64
// at least 16  16      32      32      32
// std::uint32_t
#include <QColor>
//using QRgb = QRgb;
//using Q_RGB_t = std::uint32_t;
#include <QRect>
///////////////////////////////////////////////////////////////////////////////
static constexpr std::uint32_t g_default___screen_height{600};
static constexpr std::uint32_t g_default___screen_width {960};
///////////////////////////////////////////////////////////////////////////////
static constexpr std::uint32_t g_default___screen_row_max{600-1};
static constexpr std::uint32_t g_default___screen_col_max{960-1};
static constexpr std::uint32_t g_default___screen_row_min{0};
static constexpr std::uint32_t g_default___screen_col_min{0};
///////////////////////////////////////////////////////////////////////////////
static constexpr double g_default___min__relativeDensity_exponent{-4};
static constexpr double g_default___max__relativeDensity_exponent{6};
static constexpr double g_default___point_density_exponent_d{0.0125};
///////////////////////////////////////////////////////////////////////////////
static constexpr double g_default___x_min_dble{0.0};
static constexpr double g_default___y_min_dble{2.9};
static constexpr double g_default___x_max_dble{1.0};
static constexpr double g_default___y_max_dble{4.0};
static constexpr double g_default___point_density_dble{1.0};


static const mpf_class g_default___x_min_mpf{mpf_class{g_default___x_min_dble}};
static const mpf_class g_default___y_min_mpf{mpf_class{g_default___y_min_dble}};
static const mpf_class g_default___x_max_mpf{mpf_class{g_default___x_max_dble}};
static const mpf_class g_default___y_max_mpf{mpf_class{g_default___y_max_dble}};
static const mpf_class g_default___point_density_mpf{mpf_class{g_default___point_density_dble}};

///////////////////////////////////////////////////////////////////////////////
static constexpr std::uint32_t g_default___num_iterationsBASE_i{1000};
static constexpr const QRgb g_num_iterations_for_initialization{2000};
//("0.0","2.9","1.0","4.0","1.0", 0.0125, 1000);std::to_string(x);
///////////////////////////////////////////////////////////////////////////////
static std::string gs_default___x_min_mpf{std::to_string( g_default___x_min_dble )};
static std::string gs_default___y_min_mpf{std::to_string( g_default___y_min_dble )};
static std::string gs_default___x_max_mpf{std::to_string( g_default___x_max_dble )};
static std::string gs_default___y_max_mpf{std::to_string( g_default___y_max_dble )};
static std::string gs_default___point_density_mpf{std::to_string( g_default___point_density_dble )};
static std::string gs_default___point_density_exponent_d{std::to_string( g_default___point_density_exponent_d )};
static std::string gs_default___num_iterationsBASE_i{std::to_string( g_default___num_iterationsBASE_i )};


static constexpr double g_default___aspectRatio{static_cast<double>(g_default___screen_width)/g_default___screen_height};
static constexpr double g_demo_Rate{3.59254};
//3.594580701168614357262103505843071786310517529215358931552587646076794657762938230383973288814691151919866444073455759599332220367278797
//3.59254
//3.6816506177
//3.6830110851
static constexpr auto g_demo_Rate_s{"3.6830110851"};


static constexpr std::uint32_t g_uint32_t_size{g_default___screen_width*g_default___screen_height};
static constexpr std::uint32_t g_uint8_t_size{g_uint32_t_size*sizeof(QRgb)};
typedef std::uint8_t chunk_t[g_uint8_t_size];
//using data_t = std::vector< std::uint8_t/*[]*/ >;
///////////////////////////////////////////////////////////////////////////////

template<typename T, std::size_t n>
using Chunk_t =  T[n];
///////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t n>
std::size_t array_size(const T (&)[n]) {
    return n;
}
///////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t Height, std::size_t Width>
constexpr void Kopy() {
    Chunk_t<T, Width> rowData;
    std::vector< Chunk_t<T, Width> > rectData(Height);
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
struct map_buffer{
    map_buffer() { }
//     map_buffer_t m_logisticMaps;
    static map_buffer_t g_logisticMaps;
    ~map_buffer(){
        //m_logisticMaps.clear();
        g_logisticMaps.clear();
    }
//    std::size_t load(chunk_t const& _datum) {
//        data_t datum(g_size, 0);
//        std::memcpy(&datum[0], &_datum[0], g_size);
//        m_logisticMaps.emplace_back( std::move( datum ) );
//        return m_logisticMaps.size();
//    }
//    std::size_t load(data_t const& datum) {
//        data_t q(g_size, 0);// = datum;
//        //std::iota(q.begin(), q.end(), 0);
//        //std::copy (datum.begin(), datum.end(), q.begin());
//        std::copy(datum.begin(), datum.end(),
//                  std::back_inserter(q));
//        g_logisticMaps.emplace_back( std::move( q ) );
//        //m_logisticMaps.push_back( datum );
//        return m_logisticMaps.size();
//    }
    std::size_t load(data_t&& datum) {
        g_logisticMaps.emplace_back( std::move( datum ) );
        return g_logisticMaps.size();
    }
    data_t &operator()(std::size_t index) const {
        if ( index < g_logisticMaps.size() ){
            return g_logisticMaps[index];
        }
        throw std::out_of_range("index " + std::to_string(index) + " is out of range");
    }

    QRect m_play_rect{};// bottom() > top()
//set of left, top, width and height integers
//right() = left() + width() - 1
//bottom()= top() + height() - 1.
//std::uint8_t* buffer = reinterpret_cast<std::uint8_t*>( &data[0] );
//auto dest = const_cast<void*>( (const void *) (   ( (const char *)buffer ) + begin_ * g_default___screen_width * sizeof(data_t::value_type) ) );
//static_cast<datum_t>(m_play_rect.left()) + row * (g_default___screen_height - m_play_rect.bottom() -1) * g_default___screen_width
    datum_t begin(datum_t row){ return static_cast<datum_t>(m_play_rect.left()) + row * g_default___screen_width ;}
    datum_t   end(datum_t row){ return begin(row) + static_cast<datum_t>(m_play_rect.width()) ;}
    datum_t selectedValue(std::size_t index, datum_t row, datum_t col) {
        if ( auto offset = begin(row) + col; index < g_logisticMaps.size() && offset < g_default___screen_width){
            return g_logisticMaps[index][offset];
        }
        throw std::out_of_range("index " + std::to_string(index) + " offset " + std::to_string(begin(row) + col) + " is out of range");
    }
///////////////////////////////////////////////////////////////////////////////
// return by value!
matrix_t Copy(data_t d)//, std::size_t Height, std::size_t Width)
{
    auto h = m_play_rect.height();
    auto w = m_play_rect.width();
    auto t = m_play_rect.top();
    auto b = m_play_rect.bottom();
    auto l = m_play_rect.left();
    auto r = m_play_rect.right();
    std::size_t sz{d.size()};
    matrix_t m           =    std::make_unique<matrix_row_t[]>( static_cast<std::size_t>(m_play_rect.height()) );
    matrix_row_t mat_row;// = std::make_unique<     datum_t[]>( static_cast<std::size_t>(m_play_rect.width() );
    
    std::size_t offset{(g_default___screen_height - static_cast<datum_t>(m_play_rect.bottom()) -1) * g_default___screen_width};
    datum_t* base{&d[0] + offset};
    for (datum_t row=0; row < static_cast<datum_t>(m_play_rect.height()) ; ++row) {
        /*mat_row = */m[row] = std::make_unique< datum_t[] >( static_cast<std::size_t>(m_play_rect.width()) );
        for (datum_t col=0; col< static_cast<datum_t>( m_play_rect.width() ) ; ++col) {
            auto index = begin(row)+col;
            index < sz? m[row][col] = base[index] : throw std::out_of_range("index " + std::to_string(index) + " is out of range in Copy");
        }
        //m[row](std::move(mat_row));
//        m[row] = mat_row;
//        mat_row.reset();
//        mat_row = nullptr;
    }
    return m;
//    namespace rng = ranges::v3;
//using xxx= std::vector<datum_t>  (/*Width*/);
//auto a = ranges::take_view()
//    ranges::take_view a{d[0],end(0)};
//    auto tv1 = ranges::take_view{d[0],end(0)};
//    auto tv = ranges::take_view{tv1, -m_play_rect.width()};
//std::vector< std::vector<datum_t>/*(Width)*/ > rectData(Height);
}
///////////////////////////////////////////////////////////////////////////////
//std::unique_ptr<datum_t[]>
//std::vector<datum_t[]>
//copy() {
//    auto h = std::max(datum_t{1}, static_cast<datum_t>(m_play_rect.height()));
//    auto w = std::max(datum_t{1}, static_cast<datum_t>(m_play_rect.width()));
////  std::size_t w = std::max(std::uint64_t{1}, m_play_rect.width());
//  //auto a = std::make_unique<datum_t[w]>(h);
//  //std::unique_ptr<datum_t[]> b  = std::make_unique<datum_t[]>(h);
//  std::vector<datum_t[/*w*/]> b(h);
//  //Copy< datum_t, static_cast<std::size_t>(m_play_rect.height()), static_cast<std::size_t>(m_play_rect.width()) > ();
//  return b;
//}
    void copy() {
//        Copy< int, 1,2 > ();
//        Copy< int, static_cast<std::size_t>(m_play_rect.height()), static_cast<std::size_t>(m_play_rect.width()) > ();
        //Copy< datum_t, static_cast<std::size_t>(m_play_rect.height()), static_cast<std::size_t>(m_play_rect.width()) > ();
    }

///////////////////////////////////////////////////////////////////////////////
};
///////////////////////////////////////////////////////////////////////////////
static map_buffer g_Logistic_Map_HISTORY_database;
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//typedef QRgb begin_t;
//typedef QRgb end_t;
using ID_t = QRgb;
using begin_t = QRgb;
using end_t = QRgb;
using area_t = QRgb;


//std::shared_ptr<int> sp(new int[10], array_deleter<int>()); < c++17
//shared_ptr<int[]> sp(new int[10]); c++17
using tup_idANDbeginANDendANDarea = std::tuple<ID_t, begin_t, end_t, area_t/*, data_t*/>;

using vec_idANDbeginANDendANDarea = std::vector<tup_idANDbeginANDendANDarea>;

using pair_mem_tup_ibeA_t = std::pair< data_t, tup_idANDbeginANDendANDarea>;
using vec_mem_tup_ibeA_t = std::vector< pair_mem_tup_ibeA_t >;

//using vec_mem_tup_ibeA_t = std::vector< std::pair< data_t, tup_idANDbeginANDendANDarea> >;

using quotient_t = QRgb;
using modulo_t = QRgb;
using quotientANDmodulo_t = std::pair<quotient_t, modulo_t>;

#if 0
Always pass your shared_ptr by const reference:

void f(const shared_ptr<Dataset const>& pds) {...}
void g(const shared_ptr<Dataset const>& pds) {...}
Edit: Regarding the safety issues mentioned by others:

When using shared_ptr heavily throughout an application, passing by value will take up a tremendous amount of time (I've seen it go 50+%).
Use const T& instead of const shared_ptr<T const>& when the argument shall not be null.
Using const shared_ptr<T const>& is safer than const T* when performance is an issue.
#endif
///////////////////////////////////////////////////////////////////////////////
//using vectorRGB = std::vector< QRgb >;//, NAlloc<QRgb> >;
///////////////////////////////////////////////////////////////////////////////
quotientANDmodulo_t quotientANDmodulo(QRgb numTHREADS);//, QRgb screen_height);
/*void*/ vec_idANDbeginANDendANDarea calculate_area_begin_end_id(QRgb numTHREADS);//, QRgb screen_width, QRgb screen_height);
void calculate_area_begin_end_id(vec_idANDbeginANDendANDarea &vibeA, QRgb numTHREADS);//, QRgb screen_width, QRgb screen_height);

//typedef QRgb
//An ARGB quadruplet on the format #AARRGGBB, equivalent to an unsigned int.
//QT += gui

//static std::unique_ptr<QRgb[]> mem_global{std::make_unique<QRgb[]>(g_default___screen_width*g_default___screen_height)};


#endif // GLOBAL_H_27b82c95yD3898441d9383f44ee6159a9f


/*
auto testData = std::unique_ptr<unsigned char[]>{ new unsigned char[16000] };
Or with c++14, a better form ( VS2013 already have it ):
            auto testData = std::make_unique<unsigned char[]>( 16000 );

std::unique_ptr<D[]> p{new D[3]};
auto testData = std::make_unique<unsigned char[]>(16000);

std::unique_ptr<T> does not allow copy construction, instead it supports move semantics. Yet, I can return a unique_ptr<T> from a function and assign the returned value to a variable.

see 12.8 §34 and §35    clauses in the c++ language specification
std::unique_ptr<T[], std::default_delete<T[]>> v = make_unique<T[], std::default_delete>(42));
std::unique_ptr<char[], std::default_delete<char[]>> v(new char[42], std::default_delete<char[]>());

std::make_unique function template. See this excellent GOTW for more details. The syntax is:
auto testData = std::make_unique<unsigned char[]>(16000);

#include <iostream>
#include <memory>

std::unique_ptr<int> foo() {
  std::unique_ptr<int> p( new int(10) );
  return p;                   // 1
  //return move( p );         // 2
}

int main() {
  unique_ptr<int> p = foo();
  cout << *p << endl;
  return 0;
}

returning by value should be the default choice here because a named value in the return statement in the worst case, i.e. without elisions in C++11, C++14 and C++17 is treated as an rvalue. So for example the following function compiles with the -fno-elide-constructors flag

std::unique_ptr<int> get_unique() {
  auto ptr = std::unique_ptr<int>{new int{2}}; // <- 1
  return ptr; // <- 2, moved into the to be returned unique_ptr
}

...

auto int_uptr = get_unique(); // <- 3

With the flag set on compilation there are two moves (1 and 2) happening in this function and then one move later on (3). 
///////////////////////////////////////////////////////////////////////////////////////
void bar(std::unique_ptr<int> p) {
// ...
}

int main() {
    unique_ptr<int> p = foo();
    bar(p); // error, can't implicitly invoke move constructor on lvalue
    bar(std::move(p)); // OK but don't use p afterwards
    return 0;
}


*/
