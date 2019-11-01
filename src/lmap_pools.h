//lmap_pools.h
#if 0
lmap_pools.h
#include "lmap_pools.h"
#include "src/lmap_pools.h"
#include "../src/lmap_pools.h"
#endif


#if !defined(LMAP_POOLS_H_2449132712a04939b7d4047814fb59d2)
#define LMAP_POOLS_H_2449132712a04939b7d4047814fb59d2


#if 0

0 <=  col_x <= (screenWidth   - 1) ) ;  x_min_t <= x_t <= x_max_t
0 <=  row_y <= (screenHeight  - 1) ) ;  y_min_t <= y_t <= y_max_t


    x_t = x_min_t + ( ( x_max_t - x_min_t )  / (screenWidth   - 1) ) * col_x ;
    y_t = y_min_t + ( ( y_max_t - y_min_t )  / (screenHeight  - 1) ) * row_y ;


    width_t  = x_max_t - x_min_t;
    height_t = y_max_t - y_min_t;

    x_t = x_min_t + ( width_t   / (screenWidth   - 1) ) * col_x ;
    y_t = y_min_t + ( height_t  / (screenHeight  - 1) ) * row_y ;

    normalized_width_t  = width_t  / (screenWidth  - 1);
    normalized_height_t = height_t / (screenHeight - 1);

    x_t = x_min_t + normalized_width_t  * col_x ; col_t = (x_t - x_min_t)/normalized_width_t;
    y_t = y_min_t + normalized_height_t * row_y ; row_t = (y_t - y_min_t)/normalized_height_t;


    rate_t = y_min_t + normalized_height_t * row_y; // ==  y_min_t + (y_max_t - y_min_t) * ( row_y / (screenHeight-1) )
#endif

#if 0
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <functional>
#include <stdexcept>
#include <algorithm>
#endif
#include "global.h"
#include "rect_data.h"
#include <QDebug>
#include <QImage>

//the following succeeds because INCLUDEPATH += $$PWD/include
#include <taskflow/taskflow.hpp>

static constexpr const Q_RGB_t m_num_iterations_for_initialization{2000};


//typedef Q_RGB_t begin_t;
//typedef Q_RGB_t end_t;
using ID_t = Q_RGB_t;
using begin_t = Q_RGB_t;
using end_t = Q_RGB_t;
using area_t = Q_RGB_t;
using tup_idANDbeginANDendANDarea = std::tuple<ID_t, begin_t, end_t, area_t>;

using vec_idANDbeginANDendANDarea = std::vector<tup_idANDbeginANDendANDarea>;

using quotient_t = Q_RGB_t;
using modulo_t = Q_RGB_t;
using quotientANDmodulo_t = std::pair<quotient_t, modulo_t>;

///////////////////////////////////////////////////////////////////////////////
#if 0
#endif
#include <cstddef>
#include <new>

// minimal C++11 allocator with debug output
template <class Tp>
struct NAlloc {
    using value_type = Tp;
    NAlloc() = default;
    template <class T> NAlloc(const NAlloc<T>&) {}
    Tp* allocate(std::size_t n) {
        n *= sizeof(Tp);
        std::cout << "allocating " << n << " bytes\n";
        auto block = static_cast<Tp*>(::operator new(n));
        memset(block, 0, n );
        return block;//static_cast<Tp*>(::operator new(n));
    }
    void deallocate(Tp* p, std::size_t n) {
        std::cout << "deallocating " << n*sizeof*p << " bytes\n";
        ::operator delete(p);
    }
};
template <class T, class U>
bool operator==(const NAlloc<T>&, const NAlloc<U>&) { return true; }
template <class T, class U>
bool operator!=(const NAlloc<T>&, const NAlloc<U>&) { return false; }

using vectorRGB = std::vector< Q_RGB_t, NAlloc<Q_RGB_t> >;

///////////////////////////////////////////////////////////////////////////////
/// \brief The Fill_in_vector class
///
struct data_block {
//    friend class Fill_in_vector;
//public:
    data_block() = default;
    data_block(const data_block& rhs)     = default;
    data_block(data_block&& rhs) noexcept = default;
    ~data_block() noexcept = default;
    auto operator=(const data_block& rhs) &          -> data_block& = default;
    auto operator=(data_block&& rhs)      & noexcept -> data_block& = default;
    data_block(tup_idANDbeginANDendANDarea const &_ibeL)
      : ibeL{_ibeL}  {  }
    void operator()() {
        std::tie(this->id_, this->begin_, this->end_, this->area_) = ibeL;
        v_.reserve(area_);
        memset(&v_[0], 0, area_ * sizeof (Q_RGB_t));
    }
    constexpr data_block& operator()() {return *this;}
    //~data_block(){}

//private:
//protected:
    tup_idANDbeginANDendANDarea const &ibeL;
    vectorRGB v_;
    ID_t id_{static_cast<Q_RGB_t>(-1)};// = static_cast<Q_RGB_t>( (long) arg );//typically this argument is a thread number
    begin_t begin_{0};
    end_t end_{0};
    area_t area_{0};
    //vectorRGB& operator()() {return v_;}
};

#if 0
///////////////////////////////////////////////////////////////////////////////
/// \brief get_mpf_XY
/// \param pos
/// \return
///
using mpf_pair = std::pair<mpf_class,mpf_class>;
using mpf_2_tuple = std::tuple<mpf_class,mpf_class>;

mpf_2_tuple get_mpf_XY( mpf_class const &x_min_t, mpf_class const &y_min_t,
                        mpf_class const &normalized_width_t, mpf_class const &normalized_height_t,
                        QPoint const &pos) ;
{
    mpf_set_default_prec (NS_LogisticMap::prec);
    //	mpf_class width_t  = x_max_t - x_min_t;
    //	mpf_class height_t = y_max_t - y_min_t;
    //	mpf_class normalized_width_t  = width_t  / (screen_width  - 1);
    //	mpf_class normalized_height_t = height_t / (screen_height - 1);
//************  WARNING  ************
// drops to double precision ACCURACY [for some reason]
// if one uses  ... normalized_width_t  * pos.x()
        mpf_class x_t = x_min_t + normalized_width_t  * mpf_class{pos.x()} ;// col_t = (x_t - x_min_t)/normalized_width_t;
        //mpf_class y_t = y_min_t + normalized_height_t *((screen_height - 1) - pos.y() );// row_t = (y_t - y_min_t)/normalized_height_t;
        mpf_class y_t = y_min_t + normalized_height_t * mpf_class{pos.y()} ;// row_t = (y_t - y_min_t)/normalized_height_t;
        return {x_t, y_t};
}
#endif
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/// \brief The Fill_in_vector class
///

class Fill_in_vector {
public:
    Fill_in_vector(data_block& v,
                   std::size_t selected)   : v_{v}, m_selected{selected}
    {
#if 0
        //[this->begin_, this->end_, this->area_] = beL;
        std::tie(this->begin_, this->end_, this->area_) = beL;
        v_.reserve(area_);
        std::vector< Q_RGB_t, NAlloc<Q_RGB_t> > v1;
                v1.reserve(sz);
        _d = std::unique_ptr<Q_RGB_t[]>(new Q_RGB_t[ nrows * screenWidth ]);//, [](Q_RGB_t* x){ delete[] x; });/* * sizeof(Q_RGB_t)*/
        memset(_d.get(), 0, nrows * screenWidth * sizeof (Q_RGB_t));
#endif
    }
#if 10
    ~Fill_in_vector(){}
#endif

    void operator()() {
//        Q_RGB_t screenWidth  = LogisticMap_data_structure::get_JSON_Data(static_cast<long>(m_selected))->screen_width;
//        Q_RGB_t screenHeight = LogisticMap_data_structure::get_JSON_Data(static_cast<long>(m_selected))->screen_height;
//        mpf_class x_min_t    = LogisticMap_data_structure::get_JSON_Data(static_cast<long>(m_selected))->x_min_t;
//        mpf_class y_min_t    = LogisticMap_data_structure::get_JSON_Data(static_cast<long>(m_selected))->y_min_t;
//        mpf_class x_max_t    = LogisticMap_data_structure::get_JSON_Data(static_cast<long>(m_selected))->x_max_t;
//        mpf_class y_max_t    = LogisticMap_data_structure::get_JSON_Data(static_cast<long>(m_selected))->y_max_t;
//        mpf_class width_t    = LogisticMap_data_structure::get_JSON_Data(static_cast<long>(m_selected))->width_t; //width_t  = x_max_t - x_min_t;
//        mpf_class height_t   = LogisticMap_data_structure::get_JSON_Data(static_cast<long>(m_selected))->height_t;//height_t = y_max_t - y_min_t;
//        mpf_class normalized_width_t = LogisticMap_data_structure::get_JSON_Data(static_cast<long>(m_selected))->normalized_width_t; //= width_t  / (mpf_class{screenWidth  - 1});
//        mpf_class normalized_height_t = LogisticMap_data_structure::get_JSON_Data(static_cast<long>(m_selected))->normalized_height_t;//= height_t / (mpf_class{screenHeight - 1});


    //x_t = x_min_t + ( width_t   / (screenWidth   - 1) ) * col_x ;
    //y_t = y_min_t + ( height_t  / (screenHeight  - 1) ) * row_y ;
        {
            std::lock_guard<std::mutex> lock(worker_mutex);
        auto jd = LogisticMap_data_structure::get_JSON_Data(static_cast<long>(m_selected));
        screenWidth  = jd->screen_width;
        screenHeight = jd->screen_height;
        x_min_t    = jd->x_min_t;
        y_min_t    = jd->y_min_t;
        x_max_t    = jd->x_max_t;
        y_max_t    = jd->y_max_t;
        width_t    = jd->width_t; //width_t  = x_max_t - x_min_t;
        height_t   = jd->height_t;//height_t = y_max_t - y_min_t;
        normalized_width_t = jd->normalized_width_t; //= width_t  / (mpf_class{screenWidth  - 1});
        normalized_height_t = jd->normalized_height_t;//= height_t / (mpf_class{screenHeight - 1});

        num_iterations_base    = LogisticMap_data_structure::num_iterations_base    (static_cast<long>(m_selected));
        increase_sample_size_by = LogisticMap_data_structure::increase_sample_size_by(static_cast<long>(m_selected));
        }
//        num_THREADS = this->m_num_THREADS;
//        bcolor = this->m_color;

#if 10
        Q_RGB_t m_num_iterations = static_cast<Q_RGB_t>( num_iterations_base*increase_sample_size_by );
        Q_RGB_t col_x{0};
        Q_RGB_t row_y{0};

        mpf_class rate_t;
        mpf_class x_t;
        mpf_class col_t;
        Q_RGB_t col{0};


        double rate=0, x=0, x_min=0, x_max=0;
        double normalized_width =  mpf_get_d(normalized_width_t.get_mpf_t());
        for (row_y = v_.begin_; row_y <= v_.end_; ++row_y) {

            //Q_RGB_t *scanLinE = reinterpret_cast<Q_RGB_t *>( ((Q_RGB_t*)_d.get()) + (row_y - id_*nrows) * screenWidth/* * sizeof(Q_RGB_t)*/);
            //Q_RGB_t *scanLine = reinterpret_cast<Q_RGB_t *>( ((Q_RGB_t*)&_d[0]) + (row_y - id_*nrows) * screenWidth/* * sizeof(Q_RGB_t)*/);
            Q_RGB_t *scanLinE = reinterpret_cast<Q_RGB_t *>( ((Q_RGB_t*)&v_.v_.front()) + (row_y - v_.begin_) * screenWidth/* * sizeof(Q_RGB_t)*/);
            Q_RGB_t *scanLine = reinterpret_cast<Q_RGB_t *>( ((Q_RGB_t*)&v_.v_[0])      + (row_y - v_.begin_) * screenWidth/* * sizeof(Q_RGB_t)*/);
            assert( scanLinE == scanLine );

            //double	rate_t = g_y_min_t + ( ( g_y_max_t - g_y_min_t )  / (screenHeight  - 1) ) * row_y ;
            rate_t = y_min_t + normalized_height_t * row_y; // ==  y_min_t + (y_max_t - y_min_t) * ( row_y / (screen_height-1) )
            rate   = mpf_get_d( rate_t.get_mpf_t());
            int count = 0;
            std::uint32_t j = 0;

            x_min = mpf_get_d(x_min_t.get_mpf_t());
            x_max = mpf_get_d(x_max_t.get_mpf_t());

            //x   = NS_LogisticMap::uniform_real_distribution(NS_LogisticMap::MERSENNE_TWISTER_RNG);
            x   = NS_LogisticMap::urd();
            // for fun, start inside the chosen interval
            x_t = x_min + x*( x_max - x_min );
            //increase_sample_size_by
            auto scale_initialization = [this/*, screenHeight,increase_sample_size_by*/](auto row_y)->Q_RGB_t{return
                        static_cast<Q_RGB_t> (/*std::sqrt*/(increase_sample_size_by)*(1+8*static_cast<double>(row_y)/ static_cast<double>(screenHeight - 1)) );};

            if (m_num_iterations_for_initialization > 0) {
                for (j = 0; j < m_num_iterations_for_initialization*scale_initialization(row_y); ++j) {
                    x_t = rate_t * x_t * (1 - x_t);// in general, x_t is NOT inside the chosen interval
                    x   = rate   * x   * (1 - x);
                }
            }
            if (count > 0)
                std::cout << "row_y " << row_y << std::endl;
            for (j = 0; j < m_num_iterations; ++j) {

                x_t = rate_t * x_t * (1 - x_t);
                x   = rate   * x   * (1 - x);
                col   = static_cast<Q_RGB_t>((x - x_min) / normalized_width);
                col_t = (x_t - x_min_t) / normalized_width_t;
                col_x = mpf_get_ui(col_t.get_mpf_t());//mpf_get_si(col_t.get_mpf_t());
                Q_RGB_t COL   = mpf_get_si(col_t.get_mpf_t());

                auto crap = static_cast<int64_t>(col - col_x);
                crap=crap;
                //assert( std::abs( crap ) < 8 );
                //        if ( ( rate >= R_at_ChaosOnset )  && ( std::abs( crap ) >= 8  ) ) {
                //            //crap;//assert( std::abs( crap ) < 8 );// for debugging at an interesting value of rate
                //        }

                if ( static_cast<int32_t>(COL) >= 0 &&  COL < screenWidth) {
                    ++scanLine[COL];
                    if(--count > 0) std::cout<< COL <<"[" << scanLine[COL] <<"]%";
                }

            }//m_num_iterations
        }//for ( row_y = id_*nrows; row_y <= end; ++row_y )


#endif

/**/
#if 0
{
        auto rng = init_mersenne_twister();
        std::uniform_int_distribution<Q_RGB_t> percentile_die(1, 100);

        //the taskflow is used only once, so we can mess up with area_ value
        while (area_ > 0) {
            --area_;
            v_.push_back( percentile_die(rng) );
        }
}
#endif
    }
private:
    data_block& v_;
    std::size_t m_selected{0};
    static std::mutex worker_mutex;
//    Q_RGB_t id_{static_cast<Q_RGB_t>(-1)};// = static_cast<Q_RGB_t>( (long) arg );//typically this argument is a thread number

//    /*std::vector< Q_RGB_t, NAlloc<Q_RGB_t> >*/ vectorRGB& v_;
//    begin_t begin_{0};
//    end_t end_{0};
//    area_t area_{0};
#if 10
    //std::unique_ptr<Q_RGB_t[]> _d;//(new Q_RGB_t[nrows * screenWidth /* * sizeof(Q_RGB_t)*/], [](Q_RGB_t* x){ delete[] x; });
//if (id_ == nthreads - 1) _d = std::unique_ptr<Q_RGB_t[]>(new Q_RGB_t[ (nrows + remainder) * screenWidth ]);
//    Q_RGB_t nrows{9} ;//= dotstr.nrows;
//    Q_RGB_t remainder{9} ;//= dotstr.remainder;
    Q_RGB_t screenWidth{960}  ;//= dotstr.screenWidth;
    Q_RGB_t screenHeight{600} ;//= dotstr.screenHeight;
    mpf_class x_min_t ;//= dotstr.x_min_t;
    mpf_class y_min_t ;//= dotstr.y_min_t;
    mpf_class x_max_t ;//= dotstr.x_max_t;
    mpf_class y_max_t ;//= dotstr.y_max_t;
    mpf_class height_t ;//= dotstr.height_t;
    mpf_class width_t ;//= dotstr.width_t;
    mpf_class normalized_height_t ;//= dotstr.normalized_height_t;
    mpf_class normalized_width_t ;//= dotstr.normalized_width_t;
    Q_RGB_t num_iterations_base{1000};
    double increase_sample_size_by{1} ;
#endif

};

//std::mutex Fill_in_vector::worker_mutex;
///////////////////////////////////////////////////////////////////////////////
/// \brief The Assemble_block class
///
class Assemble_block : public QObject {
    Q_OBJECT
public:
    Assemble_block(data_block const& _db,//std::vector<data_block>&_data_block_list,
                   vectorRGB &_output)
        :db{_db}, output{_output} {}
     // : in1_{in1}, in2_{in2}, out_{out}
    void operator()(Q_RGB_t screenWidth, Q_RGB_t screenHeight, std::vector<data_block> data_block_list, vectorRGB& out) {
            //std::lock_guard<std::mutex> lock(worker_mutex);
#if 0
http://doc.qt.io/qt-5/implicit-sharing.html

The classes listed below automatically detach from common data if an object is about to be changed.
"The programmer will not even notice that the objects are shared."
Thus you should treat separate instances of them as separate objects.
They will always behave as separate objects
... QByteArray ... QImage

auto dest = const_cast<void*>( (const void *) ( ( (const char *)dotstr.buffer ) + m_id * nrows * screenWidth * sizeof(vectorRGB::value_type) ) );

if ( m_id == (nthreads - 1) ) {
    std::memcpy(dest, src, (screenHeight - m_id * nrows ) * screenWidth * sizeof(vectorRGB::value_type)  );//screenWidth * sizeof(vectorRGB::value_type));
}
            else {
    std::memcpy(dest, src, nrows * screenWidth * sizeof(vectorRGB::value_type)  );// * screenWidth * sizeof(vectorRGB::value_type));
}

#endif

            //std::shared_ptr<Q_RGB_t>  bbuffer { new Q_RGB_t[screenHeight * screenWidth] };
            Q_RGB_t* buffer = &output[0];//bbuffer.get();//new Q_RGB_t[screenHeight * screenWidth];
            memset(buffer, 0, screenHeight * screenWidth * sizeof (Q_RGB_t));
    //for (auto &e : data_block_list) {
            auto &e = db;
            ////auto dest = const_cast<void*>( (const void *) (dotstr.qimage.scanLine(m_id*nrows) ) );
            ////auto dest = const_cast<void*>( (const void *) (dotstr.qimageqptr.get()->scanLine(m_id*nrows) ) );
            //auto dest = const_cast<void*>( (const void *) (dotstr.qimageptr.get()->scanLine(m_id*nrows) ) );
            //auto dest = const_cast<void*>( (const void *) (&buffer[ m_id * nrows * screenWidth * sizeof(vectorRGB::value_type) ]) );
auto dest = const_cast<void*>( (const void *) (   ( (const char *)buffer ) + e.begin_ * screenWidth * sizeof(vectorRGB::value_type) ) );

vectorRGB::const_pointer const src  =  reinterpret_cast<const Q_RGB_t*>( &e.v_[0] );
//if ( e.id_ == (nthreads - 1) ) {
//std::memcpy(dest, src, (screenHeight - e.begin_ ) * screenWidth * sizeof(vectorRGB::value_type)  );//screenWidth * sizeof(vectorRGB::value_type));
//}
//else {
std::memcpy(dest, src, ( e.end_  - e.begin_ + 1 ) * screenWidth * sizeof(vectorRGB::value_type)  );// * screenWidth * sizeof(vectorRGB::value_type));
//}

            std::cout << "ID[" << e.id_ << "]: " << std::hex   << static_cast<std::size_t>( (long)dest ) << std::dec  ;//<< std::endl;

            printf("; Thread %d did %d to %d;",e.id_ ,e.begin_ ,e.end_ );//bugged =>
            std::cout << std::endl;
            //pthread_mutex_unlock(&mutexD);
            //pthread_mutex_unlock (&mutexsum);
        //}

#if 0
    QImage ret( QSize(960, 600), QImage::Format_RGB32 );
//    mutex.lock();
    std::memcpy(ret.bits(), buffer, screenHeight * screenWidth * sizeof(QRgb)  );
    emit map(ret);//960*600, buffer );
#endif
#if 0
    Assemble_block ab;
    protected slots:
        void map(QImage const &image);//std::size_t const n, QRgb *buffer);
    connect(&ab, SIGNAL(map(QImage)), this, SLOT(map(QImage)));

?QObject::connect(&ab, &Assemble_block::map, cpu_ptr, &CPU::map);
    connect(this, SIGNAL(renderedImage(QImage)), ptr_LM->openGLWidget, SLOT(newPixmapFromThreadDraw(QImage)));
    connect(this, SIGNAL(updateAfterRenderedImage(void)), ptr_LM, SLOT(updateAfterRenderedImage(void)));
///////////////////////////////////////////////////////////////////////////////
#include "../png/PngWriter.hpp"
void CPU::map(QImage const &ret)//std::size_t const n, QRgb *buffer)
{
    ptr_LM->pb_abort->setVisible(false);
    ptr_LM->pb_abort->setHidden(true);
    QSize sz = ret.size();
    std::size_t n = static_cast<std::size_t>(sz.width()*sz.height());
    {
    std::lock_guard<std::mutex> lock(mem_mutex);
    auto dest = const_cast<void*>(  reinterpret_cast<const void *>(  reinterpret_cast<const char *>(mem_.get()) ));
    std::memcpy(dest, ret.bits(), n * sizeof(QRgb)  );//screenWidth * sizeof(vector_type::value_type));
    }
    /*thread.*/redraw( ptr_LM->openGLWidget->size(), m_color==LogisticMap::COLOR::RedGreenBlue_FromWaveLength);

// mem_mutex is automatically released when lock goes out of scope
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void GLWidget::newPixmapFromThreadDraw(const QImage &image)
{
    this->setCursor(Qt::CrossCursor);
    this->ptr_LM->setCursor(Qt::CrossCursor);
//b_threadRunning = false;
b_mousePress = false;
if (!pixmap.isNull()) {
pixmap.fill(Qt::white);
//pixmap.fill(Qt::black);
pixmap.detach();
}
//pixmap.sharedPainter() = nullptr;
//mutexL.lock();
pixmap = QPixmap::fromImage(image);
//mutexL.unlock();
//    if (!lastDragPos.isNull()) return;//if mousePressEvent OR mouseMoveEvent is active
//    pixmap = nullptr;
//    //pixmap = std::make_unique<QPixmap>(QPixmap::fromImage(image));
//    pixmap = QSharedPointer<QPixmap>(new QPixmap( QPixmap::fromImage(image) ) );
//    //pixmap = QPixmap::fromImage(image);//dup);//image.mirrored(false,true));
    update();
//    if (workerThread != nullptr) {
//        delete workerThread;
//        workerThread = nullptr;
//    }
//disconnect(&thread, SIGNAL(renderedImage(QImage)), nullptr, nullptr);

//disconnect(&thread, SIGNAL(renderedImage(QImage)), this, SLOT(newPixmapFromThreadDraw(QImage)));
}
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief CPU::redraw
/// \param size
/// \param useColor
///
void CPU::redraw(QSize size, bool useColor) {
	std::uint32_t imin{1};
	std::uint32_t imax{1};
	std::uint32_t iwidth{1};
        auto cmap = [&imin,&iwidth](std::uint32_t a)->std::uint32_t{return (static_cast<std::uint32_t>( ( (g_control.ColormapSize-1)*(a-imin) )/iwidth) );};
    uintBuffer_t screenWidth = static_cast<uintBuffer_t>(size.width());
    uintBuffer_t screenHeight = static_cast<uintBuffer_t>(size.height());
    std::shared_ptr<QRgb>  bbuffer { new QRgb[screenHeight * screenWidth] };
    QRgb* buffer = bbuffer.get();//new QRgb[screenHeight * screenWidth];
    memset(buffer, 0, screenHeight * screenWidth * sizeof (QRgb));
    {
        std::lock_guard<std::mutex> lock(mem_mutex);
        auto src = const_cast<void*>( (const void *) (  (const char *)mem_.get() ));
        std::memcpy(buffer, src, screenHeight * screenWidth * sizeof(QRgb)  );//screenWidth * sizeof(vector_type::value_type));
    // mem_mutex is automatically released when lock goes out of scope
    }
        //std::lock_guard<std::mutex> lock(ptr_CPU->mem_mutex);
        for ( uintBuffer_t row_y = 0; row_y < screenHeight; ++row_y ) {
            std::uint32_t const * const x = &buffer[row_y*screenWidth];

//-O0 (do no optimization, the default if no optimization level is specified)
//-O == -O1 (optimize minimally) // FAIL: /*auto*/ unless -Og -Og (Optimize debugging experience.
/*auto*/ std::pair<std::uint32_t const * const, std::uint32_t const * const>  result = std::minmax_element(&x[0], &x[screenWidth-1]);
            imin = *result.first;
            imax = *result.second;
            iwidth = imax - imin;
            if (iwidth == 0) iwidth = 1;
            //auto map = [imin,iwidth](std::uint32_t a)->std::uint32_t{return ((g_control.ColormapSize*(a-imin))/iwidth) % g_control.ColormapSize ;};
            for ( uintBuffer_t col_x = 0; col_x < screenWidth; ++col_x) {
                QRgb &p         = buffer[row_y*screenWidth+col_x];
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

        QImage img( QSize(size.width(), size.height()), QImage::Format_RGB32 );
        std::memcpy(img.bits(), buffer, screenHeight * screenWidth * sizeof(QRgb)  );

    emit renderedImage( img.mirrored(false,true)  );
    emit updateAfterRenderedImage();

    if (ptr_LM->checkBox_auto_save->checkState() == Qt::Checked) save_png(size);
    if ( ptr_LM->checkBox_auto_save->QAbstractButton::isChecked() ) {}
}
#if 0
#endif

#endif

//        for (vectorRGB::size_type i{}, e = in1_.size(); i < e; ++i) {
//            in1_[i] = std::max(in1_[i], in2_[i]);
//        }
//        // the taskflow is executed once, so we avoid one allocation
//        out_.swap(in1_);
    }
signals:
    void map(QImage const &image);//std::size_t const n, QRgb *buffer);
signals:
    void renderedImage(QImage const &image);
    void updateAfterRenderedImage(void);
private:
    //std::vector<data_block> &data_block_list;
    data_block const& db;
    vectorRGB &output;
//    vectorRGB& in1_;
//    vectorRGB& in2_;
//    vectorRGB& out_;
};
//////////////////////////////////////////////////////////////////////////////////////////

class Print {
public:
    Print(vectorRGB const& v)
      : v_{v} {}

    void operator()() {
        bool first{ true };
        for (auto i : v_) {
            if (!first)  {
                //std::cout << ", ";
            }
            //std::cout << i;
            first = false;
        }
        std::cout << "\n";
    }
private:
    vectorRGB const& v_;
};

///////////////////////////////////////////////////////////////////////////////
#include <set>
#include <string>
#include <iomanip>
#include <iostream>
//#include <boost/range/irange.hpp>
#include <boost/range/counting_range.hpp>


quotientANDmodulo_t quotientANDmodulo(Q_RGB_t numTHREADS, Q_RGB_t screenHeight);

vec_idANDbeginANDendANDarea calculate_area_begin_end_id(Q_RGB_t numTHREADS, Q_RGB_t screenWidth, Q_RGB_t screenHeight);
#if  0
    ranges::v3::for_each( ranges::v3::view::iota(1, people.size()),  [&people](int j) { move_selected_to(people.begin(), people.end(), people.begin() + j);
    std::cout << j << '\n';
    for (const auto& person: people) {
        std::cout << title(person) << '\n';
    }
    } );
//#else
//#include <boost/range/irange.hpp>
    for (auto j : boost::irange<std::uint64_t>(1, people.size()) ) {
    //for (auto j : ranges::v3::view::iota(1, people.size()) ) {
        std::cout << j << '\n';
        move_selected_to(people.begin(), people.end(), people.begin() + j);

    for (const auto& person: people) {
        std::cout << title(person) << '\n';
    }
    }
#endif



///////////////////////////////////////////////////////////////////////////////
#if 0
std::unique_ptr<Q_RGB_t[]> _d;//(new Q_RGB_t[nrows * screenWidth /* * sizeof(Q_RGB_t)*/], [](Q_RGB_t* x){ delete[] x; });
if (id_ == nthreads - 1) {
    _d = std::unique_ptr<Q_RGB_t[]>(new Q_RGB_t[ (nrows + remainder) * screenWidth ]);
    //_d = std::unique_ptr<Q_RGB_t[]>(new Q_RGB_t[(screenHeight - (nthreads - 1)*nrows ) * screenWidth ]);//, [](Q_RGB_t* x){ delete[] x; });/* * sizeof(Q_RGB_t)*/
    memset(_d.get(), 0, (nrows + remainder) * screenWidth * sizeof (Q_RGB_t));
}
else {
    _d = std::unique_ptr<Q_RGB_t[]>(new Q_RGB_t[ nrows * screenWidth ]);//, [](Q_RGB_t* x){ delete[] x; });/* * sizeof(Q_RGB_t)*/
    memset(_d.get(), 0, nrows * screenWidth * sizeof (Q_RGB_t));
}

for (row_y = id_*nrows; row_y <= end; ++row_y)

/home/nsh/dev/fcpp-code-examples/3rd-party/catchorg/Catch2/misc/coverage-helper.cpp:
// argv should be:
// [0]: our path
// [1]: "--log-file=<path>"
// [2]: "--sep--"
// [3]+: the actual command


const std::string separator = "--sep--";
const std::string logfile_prefix = "--log-file=";

int main(int argc, char** argv) {
    std::vector<std::string> args(argv, argv + argc);
    auto sep = std::find(begin(args), end(args), separator);
    assert(sep - begin(args) == 2 && "Structure differs from expected!");

    auto num = parse_log_file_arg(args[1]);

    auto cmdline = std::accumulate(++sep, end(args), std::string{}, [] (const std::string& lhs, const std::string& rhs) {
        return lhs + ' ' + rhs;
    });

    try {
        return exec_cmd(cmdline, num, windowsify_path(catch_path(args[0])));
    } catch (std::exception const& ex) {
        std::cerr << "Helper failed with: '" << ex.what() << "'\n";
        return 12;
    }
}

///////////////////////////////////////////////////////////////////////////////
int smain(Q_RGB_t numTHREADS, Q_RGB_t screenWidth, Q_RGB_t screenHeight) {
    vec_idANDbeginANDendANDarea vbeL = calculate_area_begin_end_id( numTHREADS, screenWidth, screenHeight);
    //vectorRGB in1{}, in2{}, out{};
    // Set up the memory for the arcs
    //Q_RGB_t id{0};
//    auto data_block_list = std::accumulate(vbeL.cbegin(), vbeL.cend(), data_block{}, [/*&id*/] (tup_idANDbeginANDendANDarea const & ibeL) {
//        return data_block{/*id++, */ibeL}();
//    });
//    std::vector<data_block> data_block_list4 = {std::accumulate(vbeL.cbegin(), vbeL.cend(), data_block{}, [/*&id*/] (tup_idANDbeginANDendANDarea const & ibeL) {
//        return data_block{/*id++, */ibeL}();
//    })};
//    Q_RGB_t area{20};
//    std::size_t sz = sizeof(Q_RGB_t) * area;
//in1.reserve(sz);
//in2.reserve(sz);
//out.reserve(sz);
    std::vector<data_block> data_block_list;
    for (auto &e : vbeL) {
        data_block_list.emplace_back(e);
        data_block_list.emplace_back(data_block{e});
    }
    std::vector<Fill_in_vector> Fill_in_vector_list;
for (auto &e : data_block_list) {
    Fill_in_vector_list.emplace_back(e,0);
    Fill_in_vector_list.emplace_back(Fill_in_vector{e,0});
}

    // Prepare the functors for taskflow
//    id = 0;
//    id = 0;
    tf::Taskflow tf;
#if 0
    auto [
        fill_in_vector1,
        fill_in_vector2,
        pick_up_max,
        print
    ] = tf.emplace(
        Fill_in_vector(id++, in1, vbeL[0]),
        Fill_in_vector(id++, in2, vbeL[1]),
        Assemble_block(in1, in2, out),
        Print(out)
    );

    // Set up the dependencies
    fill_in_vector1.precede(pick_up_max);
    fill_in_vector2.precede(pick_up_max);
    pick_up_max.precede(print);

    // Execution
    tf.wait_for_all();
        #endif

    return 0;
}


#endif



/*
from dice_pools.cpp
2019/02/25 - contributed by Paolo Bolzoni

cpp-taskflow works on directed acyclic graphs.
And here we want to pass information between the flow elements.

To do so, we see the cpp-taskflow arcs as objects where the functions on the
nodes read from or write to.

The function on every node will *read from* the objects on the incoming arcs
and *write to* the objects on the outcoming arcs.

The cpp-taskflow semantics ensures the synchronization.


Nodes without incoming arcs will require the input from somewhere else; instead
nodes without outcoming arcs have to execute some side effects to be useful.


In this example we fill up (in parallel) two vectors of the same size with the
results of a fair percentile die, once done we pick up the maximum values from
each cell. Finally we output the result.

.----------------.
| fill in vector |----|
'----------------'    |->.-------------.     .-----------------.
                         | pick up max |---->| print in stdout |
.----------------.    |->'-------------'     '-----------------'
| fill in vector |----|
'----------------'

The output will be twenty random integer between 1 and 100, that are clearly
not uniform distributed as they favor larger numbers.

The code assumes the taskflow is executed once, when using the Framework
feature the programmer needs care to keep the invariants.

It is then suggested to use const references (eg., vector<int> const&) for the
objects related to the incoming arcs and non-cost references for outcoming
ones.

*/
#endif //LMAP_POOLS_H_2449132712a04939b7d4047814fb59d2
