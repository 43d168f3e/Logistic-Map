//fill_in_vector.h
#if 0
fill_in_vector.h
#include "fill_in_vector.h"
#include "src/fill_in_vector.h"
#include "../src/fill_in_vector.h"
#endif

#if !defined(FILL_IN_VECTOR_Hdf675692345dfgC132712a04939b7d4047814fb59d2)
#define FILL_IN_VECTOR_Hdf675692345dfgC132712a04939b7d4047814fb59d2


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

//the following succeeds because INCLUDEPATH += $$PWD
#include "global.h"
#include "data.h"//#include "rect_data.h"

/*
With C++17, shared_ptr can be used to manage a dynamically allocated array.
The shared_ptr template argument in this case must be T[N] or T[]. So you may write

shared_ptr<int[]> sp(new int[10]);

Prior to C++17, shared_ptr could not be used to manage dynamically allocated arrays.
By default,  shared_ptr will call delete on the managed object when no more references remain to it.
However, when you allocate using new[] you need to call delete[], and not delete, to free the resource.

In order to correctly use shared_ptr with an array, you must supply a custom deleter.

template< typename T >
struct array_deleter
{
  void operator ()( T const * p)
  {
    delete[] p;
  }
};
Create the shared_ptr as follows:

std::shared_ptr<int> sp(new int[10], array_deleter<int>());
*/

template< typename T >
struct array_deleter
{
  void operator ()( T const * p)
  {
    delete[] p;
  }
};

///////////////////////////////////////////////////////////////////////////////
#include <mutex>
#include <condition_variable>
#include <QDebug>
#include <QImage>

struct Fill_in_vector
{
    static std::atomic<bool>m_abort;//{false};
    static std::atomic<std::uint32_t> whose_turn;//{static_cast<std::uint32_t>(-1)};
    static std::atomic<std::uint32_t> num_THREADS;

//public:
    QRgb index{0};
    Fill_in_vector(QRgb j=0)   : index{j}{}
    //data_block db_{};
//    Fill_in_vector(data_block& v)   : db_{v}{ }
    //Fill_in_vector(data_block&& v)   : db_{std::move(v)}{v_._M_allocate( area_ * sizeof (QRgb)); }
    //Fill_in_vector(size_t&& j)   : index{std::move(j)}{}
    //Fill_in_vector(Fill_in_vector& rhs)  = default;
    //Fill_in_vector(Fill_in_vector&& rhs) noexcept = default;
//    Fill_in_vector(Fill_in_vector&& o) : db_{o.db_} {}
//    Fill_in_vector(Fill_in_vector& o) : db_{o.db_} {}
    //Fill_in_vector(){};//: db_{} {}
    //auto operator=(const Fill_in_vector& rhs) &          -> Fill_in_vector& = default;
    //auto operator=(Fill_in_vector&& rhs)      & noexcept -> Fill_in_vector& = default;
//    Fill_in_vector& operator=(const Fill_in_vector& o){
//        this->db_= o.db_;
//        return *this;
//    }
//    Fill_in_vector&  operator=(Fill_in_vector&& o) noexcept{
//        this->db_= o.db_;
//        return *this;
//    }
#if 10
    ~Fill_in_vector(){}
#endif
///////////////////////////////////////////////////////////////////////////////
    std::pair< data_t, tup_idANDbeginANDendANDarea>  operator()() {
        auto j = index;//
        auto ibeA = vibeA[index];
        ID_t id_{std::get<0>(ibeA)};//static_cast<QRgb>(-1)
        begin_t begin_{std::get<1>(ibeA)};
        end_t end_{std::get<2>(ibeA)};
        area_t area_{std::get<3>(ibeA)};
        assert(id_ == static_cast<ID_t>(index));

//using data_t = std::vector<QRgb>;
        data_t mem_( area_  , 0);

//        std::shared_ptr<int> sp(new int[10], array_deleter<int>()); < c++17
//        shared_ptr<int[]> sp(new int[10]); c++17

#if 10
QRgb m_num_iterations = static_cast<QRgb>( _num_iterations_base*_increase_sample_size_by );

QRgb col_x{0};
QRgb row_y{0};

mpf_class rate_t;
mpf_class x_t;
mpf_class col_t;
QRgb col{0};


double rate=0, x=0, x_min=0, x_max=0;
double normalized_width =  mpf_get_d(_normalized_width_t.get_mpf_t());
for (row_y = begin_; row_y <= end_; ++row_y) {

    QRgb *scanLine = reinterpret_cast<QRgb *>( &mem_[0] + (row_y - begin_) * _screenWidth);

    rate_t = _y_min_t + _normalized_height_t * row_y; // ==  y_min_mpf + [(y_max_mpf - y_min_mpf) / (g_default___screen_height-1) ] * row_y ;
    rate   = mpf_get_d( rate_t.get_mpf_t());
    int count = 0;
    std::uint32_t j = 0;

    x_min = mpf_get_d(_x_min_t.get_mpf_t());
    x_max = mpf_get_d(_x_max_t.get_mpf_t());

    x   = NS_LogisticMap::urd();//uniform_real_distributionn(NS_LogisticMap::MERSENNE_TWISTER_RNG);
// for fun, start inside the chosen interval
    x_t = x_min + x*( x_max - x_min );
//increase_sample_size_by
    auto scale_initialization = [this](auto row_y)->QRgb{return static_cast<QRgb> ( (_increase_sample_size_by)*(1+8*static_cast<double>(row_y)/ static_cast<double>(_screenHeight - 1)) );};

    if (g_num_iterations_for_initialization > 0) {
for (j = 0; j < g_num_iterations_for_initialization*scale_initialization(row_y); ++j) {

    if( Fill_in_vector::m_abort ) {
        mem_.clear();
        pthread_exit(nullptr);
#if 0
    if( /*Fill_in_vector::num_THREADS > Fill_in_vector::whose_turn &&*/ Fill_in_vector::whose_turn ==  id_) {
        ++Fill_in_vector::whose_turn;
        mem_.clear();
/*
ID[ID[ID[ID[2] std::thread return <- pthread_exit
0] std::thread return <- pthread_exit
3] std::thread return <- pthread_exit
1] std::thread return <- pthread_exit
terminate called after throwing an instance of 'std::invalid_argument'
terminate called recursively
  what():  Invalid std::pair.
terminate called recursively
amdgpu: Failed to allocate a buffer:
amdgpu:    size      : 4907008 bytes
amdgpu:    alignment : 4096 bytes
amdgpu:    domains   : 2
amdgpu: Failed to allocate a buffer:
amdgpu:    size      : 4907008 bytes
amdgpu:    alignment : 4096 bytes
amdgpu:    domains   : 2
EE ../src/gallium/drivers/radeonsi/si_texture.c:1777 si_texture_transfer_map - failed to create temporary texture to hold untiled copy
amdgpu: The CS has been rejected, see dmesg for more information (-9).
*/
        std::cout << "ID[" << id_ << "] std::thread return <- pthread_exit" << std::endl << std::flush;

        if( Fill_in_vector::num_THREADS == Fill_in_vector::whose_turn ) {
            throw std::invalid_argument("Invalid std::pair.");
        }
        else {
            pthread_exit((void*) 0);
        }
        //return  {mem_, ibeA};
    }
#endif
    }

    x_t = rate_t * x_t * (1 - x_t);// in general, x_t is NOT inside the chosen interval
    x   = rate   * x   * (1 - x);
}
    }
    if (count > 0)
std::cout << "row_y " << row_y << std::endl;

    for (j = 0; j < m_num_iterations; ++j) {

        if( Fill_in_vector::m_abort ) {
            mem_.clear();
            pthread_exit(nullptr);
#if 0
        if( Fill_in_vector::num_THREADS > Fill_in_vector::whose_turn && id_ == Fill_in_vector::whose_turn ) {
            ++Fill_in_vector::whose_turn;
            mem_.clear();
//            assert (_d.get() == nullptr);
//            delete[] fp;
//            _d.reset();
//            _d = nullptr;
            std::cout << "ID[" << id_ << "] std::thread return <- pthread_exit" << std::endl;
            //pthread_exit((void*) 0);
            return  {mem_, ibeA};
        }
#endif
        }

//            {
//                std::lock_guard<std::mutex> lock(worker_mutex);
//                if (dotstr.m_abort) {
//                    QRgb* fp = _d.release();
//                    assert (_d.get() == nullptr);
//                    delete[] fp;
//                    _d.reset();
//                    _d = nullptr;
//                    std::cout << "ID[" << m_id << "] pthread_exit" << std::endl;
//                    pthread_exit((void*) 0);
//                    return arg;
//                };
//            }


x_t = rate_t * x_t * (1 - x_t);
x   = rate   * x   * (1 - x);
col   = static_cast<QRgb>((x - x_min) / normalized_width);
col_t = (x_t - _x_min_t) / _normalized_width_t;
col_x = mpf_get_ui(col_t.get_mpf_t());//mpf_get_si(col_t.get_mpf_t());
QRgb COL   = mpf_get_si(col_t.get_mpf_t());

//auto crap = static_cast<int64_t>(col - col_x);
//crap=crap;
//assert( std::abs( crap ) < 8 );
//if ( ( rate >= R_at_ChaosOnset )  && ( std::abs( crap ) >= 8  ) ) {
//    //crap;//assert( std::abs( crap ) < 8 );// for debugging at an interesting value of rate
//}

if ( static_cast<int32_t>(COL) >= 0 &&  COL < _screenWidth) {
    ++scanLine[COL];
    if(--count > 0) std::cout<< COL <<"[" << scanLine[COL] <<"]%";
}

    }//m_num_iterations
}//for ( row_y = id_*nrows; row_y <= end; ++row_y )
#endif
        //Fill_in_vector::g_vec_mem_tup_ibeA_t.push_back( {mem_, ibeA} );
        return  {mem_, ibeA};
    }
///////////////////////////////////////////////////////////////////////////////
    void initialize(std::mutex &files_lock) {
        std::lock_guard<std::mutex> lk(files_lock);

        _screenWidth = g_default___screen_width;
        _screenHeight = g_default___screen_height;
        _x_min_t = x_min_mpf;
        _y_min_t = y_min_mpf;
        _x_max_t = x_max_mpf;
        _y_max_t = y_max_mpf;
        _height_t = height_t;
        _width_t = width_t;
        _normalized_height_t = normalized_height_t;
        _normalized_width_t = normalized_width_t;
        _num_iterations_base = num_iterations_base;
        _increase_sample_size_by = increase_sample_size_by;
    }
///////////////////////////////////////////////////////////////////////////////
QRgb _screenWidth;//{g_default___screen_width}  ;//= dotstr.g_default___screen_width;
QRgb _screenHeight;//{g_default___screen_height} ;//= dotstr.g_default___screen_height;
mpf_class _x_min_t ;//= dotstr.x_min_mpf;
mpf_class _y_min_t ;//= dotstr.y_min_mpf;
mpf_class _x_max_t ;//= dotstr.x_max_mpf;
mpf_class _y_max_t ;//= dotstr.y_max_mpf;
mpf_class _height_t ;//= dotstr.height_t;
mpf_class _width_t ;//= dotstr.width_t;
mpf_class _normalized_height_t ;//= dotstr.normalized_height_t;
mpf_class _normalized_width_t ;//= dotstr.normalized_width_t;
QRgb _num_iterations_base;//{1000};
double _increase_sample_size_by;//{1} ;
#if 10
//    public:
static vec_idANDbeginANDendANDarea vibeA;
static vec_mem_tup_ibeA_t g_vec_mem_tup_ibeA_t;
static std::size_t m_selected;//{0};
static mpf_class x_min_mpf ;//= dotstr.x_min_mpf;
static mpf_class y_min_mpf ;//= dotstr.y_min_mpf;
static mpf_class x_max_mpf ;//= dotstr.x_max_mpf;
static mpf_class y_max_mpf ;//= dotstr.y_max_mpf;
static mpf_class height_t ;//= dotstr.height_t;
static mpf_class width_t ;//= dotstr.width_t;
static mpf_class normalized_height_t ;//= dotstr.normalized_height_t;
static mpf_class normalized_width_t ;//= dotstr.normalized_width_t;
static QRgb num_iterations_base;//{1000};
static double increase_sample_size_by;//{1} ;
#endif

};

//std::mutex Fill_in_vector::worker_mutex;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#endif // FILL_IN_VECTOR_Hdf675692345dfgC132712a04939b7d4047814fb59d2

#if 0
//[this->begin_, this->end_, this->area_] = beL;
std::tie(this->begin_, this->end_, this->area_) = beL;
v_.reserve(area_);
std::vector< QRgb, NAlloc<QRgb> > v1;
v1.reserve(sz);
_d = std::unique_ptr<QRgb[]>(new QRgb[ nrows * g_default___screen_width ]);//, [](QRgb* x){ delete[] x; });/* * sizeof(QRgb)*/
memset(_d.get(), 0, nrows * g_default___screen_width * sizeof (QRgb));
#endif
