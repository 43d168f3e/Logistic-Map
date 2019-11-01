#include "playRows.h"
#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>
//#include "work.h"
#include "notes.h"
#include "lmap.h"
#include "data.h"
#include "play_music_root.h"

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

//static QWaitCondition t1_condv;

QMutex playRows_Worker::playRows_Worker_mutex;
///////////////////////////////////////////////MPF_Vec_Ptr pv, ////////////////////////////////

playRows_Controller::playRows_Controller(std::size_t index, QRgb _begin, QRgb _end, QRgb _num_notes, int lLength_ms,
                                         std::atomic<int> &spi, LMap* _ptr_LMap, bool b_for_play_RATE, mpf_class rate_t)
    : m_ptr_LMap{_ptr_LMap}
{
    playRows_Worker *worker = new playRows_Worker( m_ptr_LMap->m_selected,
         _begin, _end, _num_notes, lLength_ms, spi, m_ptr_LMap, rate_t, this);

    worker->moveToThread(&workerThread);

    QObject::connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);

    QObject::connect(this, &playRows_Controller::stopProcess, worker, &playRows_Worker::on_StopProcess);
    QObject::connect(m_ptr_LMap->pb_cancel, &QPushButton::clicked, this, &playRows_Controller::on_StopProcess);

//    QObject::connect(m_ptr_LMap, &LMap::sig_playROWS,     this,  &playRows_Controller::on_playROWS );
//    QObject::connect(m_ptr_LMap, &LMap::sig_playThisRate , this,  &playRows_Controller::on_playThisRate  );//emit SUCCEEDS
    //emit FAILS:connect(this, SLOT(sig_playThisRate(std::size_t)), this,  SIGNAL(on_playThisRate(std::size_t)) );
    QObject::connect(this, &playRows_Controller::suicide,   m_ptr_LMap, &LMap::on_Suicide);
    QObject::connect(this, &playRows_Controller::suicide,   m_ptr_LMap, &LMap::on_End);
    QObject::connect(this, &playRows_Controller::sig_begin, m_ptr_LMap, &LMap::on_Begin);

//    QObject::connect(this, &playRows_Controller::qs_rate,      m_ptr_LMap->lineEdit_Rate_Play, &xxxQLineEdit::setText);
//    QObject::connect(this, &playRows_Controller::qs_rate,      m_ptr_LMap->pb_Rate_Goto, &QPushButton::setText);

    QObject::connect(this, &playRows_Controller::qs_rate,      m_ptr_LMap, &LMap::pb_Rate_Goto_setText);

//    QObject::connect(this, &playRows_Controller::selectAll,    m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::selectAll);
//    QObject::connect(this, &playRows_Controller::cut,          m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::cut);
//    QObject::connect(this, &playRows_Controller::clear,        m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::clear);
//    QObject::connect(this, &playRows_Controller::qs_rate,      m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::setPlainText);


    workerThread.start();

    if (b_for_play_RATE) {
        worker->do_playThisRate(index);
    }
    else {
        worker->do_playROWS(index);
    }
}

///////////////////////////////////////////////////////////////////////////////
void playRows_Controller::on_StopProcess(void) {
    m_ptr_LMap->pb_cancel->blockSignals(true);
    emit stopProcess();
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//extern QMutex t1_cond_playRows_Worker_mutex;
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void playRows_Worker::do_playThisRate(std::size_t index) {
    emit sig_begin();
    try {
        Datum const& dum = Data::datum(index);
        assert(dum.ID_v() == index);
    float lFrequency{440.f} ;// toot -f 440. -l 300
    //int lLength_ms{300} ;
    //QPoint prev{QPoint{}};
    mpf_class x_t = dist(rng);
    QRgb row_y = dum.get_screen_Row_y(rate_t);

    auto map = [](mpf_class const &a){
        mpf_class b = 1000*a;
        return (static_cast<QRgb>(mpf_get_si(b.get_mpf_t())));};

    for (QRgb j = 0; j <= dum.num_iterationsBASE_v()*2; ++j) {
        x_t = rate_t * x_t * (1 - x_t);
    }
    for (QRgb j = 0; j <= num_notes; ++j) {
        if (spi/*.use_count()*/ == 0) {
            m_ptr_LMap->openGLWidget->setCursor(Qt::CrossCursor);
            m_ptr_LMap->setCursor(Qt::CrossCursor);
            //set_abort_play_rows(false);
            LMap::t1_condv.wakeAll();
            return;
        }
        QCoreApplication::sendPostedEvents();
        //QRgb col_x_prev{999};// = m_ptr_LMap->m_mpfRect->get_screen_Col_x( x_t );
        x_t = rate_t * x_t * (1 - x_t);
        QRgb col_x = dum.get_screen_Col_x( x_t );
        QPoint p{static_cast<int>(col_x),static_cast<int>(row_y)};
        /*if (prev != QPoint{}) {
            m_ptr_LMap->openGLWidget->draw(prev, p);
        }
        else*/ //repaint();
        //prev = p;
        lFrequency = static_cast<float>( f_notes[map(x_t)].f );
        //lLength_ms = 166;
        m_ptr_LMap->openGLWidget->draw(p);
        m_ptr_LMap->openGLWidget->update();
        {
            QMutexLocker locker(&playRows_Worker_mutex);
            toot( lFrequency , lLength_ms , m_ptr_LMap->openGLWidget->m_hack.fn, m_ptr_LMap->openGLWidget) ;
        }
        //m_ptr_LMap->openGLWidget->update();
        //std::this_thread::sleep_for(std::chrono::microseconds(1000*lLength_ms));
    }

    this->moveToThread(static_cast<QThread *>(nullptr));// stop all event processing for this object and its children
    emit suicide();
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
///////////////////////////////////////////////////////////////////////////////
void playRows_Worker::on_StopProcess()
{
    spi = 0;
    playRows_Worker_mutex.lock();
    m_abort = true;
    playRows_Worker_mutex.unlock();
    emit suicide();
}
///////////////////////////////////////////////////////////////////////////////
playRows_Worker::playRows_Worker(std::size_t index,
                   QRgb _begin, QRgb _end, QRgb _num_notes, int _lLength_ms,
                   std::atomic<int> &_spi, LMap *ptr_LMap, mpf_class _rate_t, QObject *parent) :
    QObject{parent},
    spi{_spi},
//    num_iterations_base{_m_num_iterationsBASE},
//    increase_sample_size_by{_increase_sample_size_by},
    begin{_begin},
    end{_end},
    num_notes{_num_notes},
    lLength_ms{_lLength_ms},
    m_ptr_LMap{ptr_LMap},
    m_abort{false}
{
//    auto cnt = _spi.use_count();
//    spi = _spi;
//    auto cnt2 = _spi.use_count();
    ++spi;
    rate_t = _rate_t;
    connect(parent, SIGNAL(sig_playThisRate(std::size_t)), this, SLOT(do_playThisRate(std::size_t)));
    connect(parent, SIGNAL(sig_playROWS(std::size_t)), this, SLOT(do_playROWS(std::size_t)));
    connect(parent, SIGNAL(stopProcess()), this, SLOT(on_StopProcess()));
    connect(parent, SIGNAL(updateMilliSeconds(int)), this, SLOT(on_UpdateMilliSeconds(int)));


    connect(this, SIGNAL(resultReady()),            parent, SLOT(handleResults()));
    connect(this, SIGNAL(sig_begin()),              parent, SLOT(on_Begin()));
    connect(this, SIGNAL(suicide()),                parent, SLOT(on_Suicide()));
    connect(this, SIGNAL(selectAll(void)),          parent, SLOT(selectAll(void)));
    connect(this, SIGNAL(cut(void)),                parent, SLOT(cut(void)));
    connect(this, SIGNAL(clear(void)),              parent, SLOT(clear(void)));
    //connect(this, SIGNAL(s_rate(std::string const &)), parent, SLOT(on_s_rate(std::string const &)));
    connect(this, SIGNAL(qs_rate(const QString &)), parent, SLOT(on_qs_rate(const QString &)));
    //connect(this, SIGNAL(d_rate(double)),           parent, SLOT(on_d_rate(double)));
    //connect(this, SIGNAL(sp_rate(std::shared_ptr<std::string const>)), parent, SLOT(on_sp_rate(std::shared_ptr<std::string const>)));


    try {
        Datum const& dum = Data::datum(index);
        assert(dum.ID_v() == index);
//    RenderThread::mutex.lock();
    x_min_mpf = dum.x_min_v();
    y_min_mpf = dum.y_min_v();
    x_max_mpf = dum.x_max_v();
    y_max_mpf = dum.y_max_v();
    num_iterations_base = dum.num_iterationsBASE_v();
    increase_sample_size_by = dum.get_increase_sample_size_by();
//    RenderThread::mutex.unlock();

    width_t  = x_max_mpf - x_min_mpf;
    height_t = y_max_mpf - y_min_mpf;

    normalized_width_t  = width_t  / mpf_class{(g_default___screen_width -1)};
    normalized_height_t = height_t / mpf_class{(g_default___screen_height-1)};
} catch(const std::exception& e) {
    std::cout << e.what() << '\n';
}
}
///////////////////////////////////////////////////////////////////////////////
//void playRows_Worker::broadcast_first() {
////        emit selectAll();
////        emit clear();
////        emit selectAll();
////        emit cut();
//        mpf_class rate_t = y_min_mpf + normalized_height_t * begin;
//        std::stringstream ss;
//    ss.flush();
//    ss.clear();
//    ss /*<< "R="*/<< std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << rate_t  << std::flush;
////QString qs{"<html><head/><body><p>Screen Mouse</p><p>x= " + x + "; y = "+  y + "</p><p>R= " + rate + "</p></body></html>"};

////        ss << "<html><head/><body><p>R="<< std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << rate_t << "</p></body></html>" << std::flush;
//    std::string rs{ss.str()};
//    std::string rs2{remove_ws(rs)};
//    QString qs{rs2.c_str()};
////    emit sp_rate(std::make_shared<std::string const>(rs2));
////    emit qs_rate(qs);
//    std::string rate_s = as_string<decltype(rate_t)>( rate_t );
//    emit s_rate(rate_s);
//}
///////////////////////////////////////////////////////////////////////////////
void playRows_Worker::do_playROWS(std::size_t index) {
    emit sig_begin();
//    auto cnt = spi.use_count();
#if 0
    for (auto &n : g_notes) {
        std::cout << n.f << " ";
        toot( n.f , 100 ) ;
    }
    std::cout << std::endl;
#endif
    //std::stringstream ss;
    mpf_class rate_t, x_t;
    float lFrequency{440.f} ;// toot -f 440. -l 300
    double ratef{0};
    double x   = dist(rng);
    x_t = x;

    std::thread::id this_id = std::this_thread::get_id();

    auto map = [](mpf_class const &a){
        mpf_class b = 1000*a;
        return (static_cast<QRgb>(mpf_get_si(b.get_mpf_t())));};


//    auto map2 = [](mpf_class const &a){
//        mpf_class b = 88*a;
//        return (static_cast<QRgb>(mpf_get_si(b.get_mpf_t())));};

//QRgb Data::vec_LogisticMap_Data::num_iterations_base(){1000};
    double increaseSample_size_by = increase_sample_size_by;
    QRgb screen_height = g_default___screen_height;

    auto scale_initialization = [screen_height,increaseSample_size_by](auto row_y)->QRgb{return
        static_cast<QRgb> (/*std::sqrt*/(increaseSample_size_by)*(1+8*static_cast<double>(row_y)/ static_cast<double>(screen_height - 1)) );};

    for (QRgb row_y = begin; row_y <= end; ++row_y) {
        rate_t = y_min_mpf + normalized_height_t * row_y;
        ratef   = mpf_get_d( rate_t.get_mpf_t());
//        emit selectAll();
//        emit clear();
//        emit selectAll();
//        emit cut();
#if 10
        std::cout << "play_rows\n";
        gmp_printf("playRows_Worker::run() rate_t=%.10Ff, ", rate_t.get_mpf_t());
        std::cout << std::endl << std::flush;
#endif
#if 10
        {
            std::stringstream ss;
        ss.flush();
        ss.clear();
        ss << "R="<< std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << rate_t  << std::flush;
//QString qs{"<html><head/><body><p>Screen Mouse</p><p>x= " + x + "; y = "+  y + "</p><p>R= " + rate + "</p></body></html>"};

//        ss << "<html><head/><body><p>R="<< std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << rate_t << "</p></body></html>" << std::flush;
        std::string rs{ss.str()};
        std::string rs2{remove_ws(rs)};
        //QString qs{rs2.c_str()};
        //emit sp_rate(std::make_shared<std::string const>(rs2));
        //emit qs_rate(qs);
        std::string rate_s = as_string<decltype(rate_t)>( rate_t );
        std::string rate_s1 = as_string< std::decay<decltype(rate_t)>::type >( rate_t );
//as_string( rate_t );
//        emit s_rate(rate_s);
        //auto xxx = rate_s.c_str();
        QString qs{rate_s.c_str()};
        emit qs_rate(QString{rate_s.c_str()});
//        emit sp_rate(std::make_shared<std::string const>(rate_s));
//        emit d_rate(ratef);

        mpf_set_default_prec (NS_LogisticMap::prec);
        std::ostringstream oss;
        oss.precision(NS_LogisticMap::prec+2);
        oss  << std::fixed << rate_t ;//<< std::ends;
    //ERRORS: oss  << std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec+2) << x ;//<< std::ends;
        //std::ostream&      oss_ref = oss;
        //auto prev = oss_ref.rdbuf (std::cout.rdbuf ());
        std::string s0= oss.str();
        std::string s1 = remove_ws(s0);
        std::string s2 = r0trim_copy(s1);
        std::string s3 = "\"" + s2 + "\"";
        std::string s4 = "R=" + s2;
        std::string hack = "hack";

        }
#endif
        try {
            Datum const& dum = Data::datum(index);
            assert(dum.ID_v() == index);
        for (QRgb j = 0; j <= dum.num_iterationsBASE_v()*scale_initialization(row_y); ++j) {
//            {
//                //QMutexLocker locker(&playRows_Worker_mutex);
//            if (m_abort)
//                return;
//            }
//            //QThread::msleep(1);
// An interruption can be requested by QThread::requestInterruption().

#if 0
#endif
            if (spi/*.use_count()*/ == 0) {
                m_ptr_LMap->openGLWidget->setCursor(Qt::CrossCursor);
                m_ptr_LMap->setCursor(Qt::CrossCursor);
                //set_abort_play_rows(false);
                LMap::t1_condv.wakeAll();
                return;
            }
// An interruption can be requested by QThread::requestInterruption().

            x_t = rate_t * x_t * (1 - x_t);
        }
        for (QRgb j = 0; j <= num_notes; ++j) {
#if 0
#endif
            if (spi/*.use_count()*/ == 0) {
                m_ptr_LMap->openGLWidget->setCursor(Qt::CrossCursor);
                m_ptr_LMap->setCursor(Qt::CrossCursor);
                //set_abort_play_rows(false);
                LMap::t1_condv.wakeAll();
                return;
            }
            x_t = rate_t * x_t * (1 - x_t);
#if 0
            gmp_printf(" %.10Ff, ", x_t.get_mpf_t());
            std::cout << map(x_t) << " " << g_notes[map(x_t)].f  << std::endl << std::flush;
#endif



            QRgb col_x = dum.get_screen_Col_x( x_t );
            QPoint p{static_cast<int>(col_x),static_cast<int>(row_y)};
            m_ptr_LMap->openGLWidget->draw(p);






            lFrequency = static_cast<float>( f_notes[map(x_t)].f );
            //lLength_ms = 166;
            {
                QMutexLocker locker(&playRows_Worker_mutex);
                //toot( lFrequency , lLength_ms ) ;
            toot( lFrequency , lLength_ms , m_ptr_LMap->openGLWidget->m_hack.fn, m_ptr_LMap->openGLWidget) ;
            }
            //std::this_thread::sleep_for(std::chrono::microseconds(1000*lLength_ms));
        }
        } catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
    }
    m_ptr_LMap->openGLWidget->setCursor(Qt::CrossCursor);
    m_ptr_LMap->setCursor(Qt::CrossCursor);
    //set_abort_play_rows(false);
    LMap::t1_condv.wakeAll();
    //this->moveToThread(reinterpret_cast<QThread *>(nullptr));
    this->moveToThread(static_cast<QThread *>(nullptr));// stop all event processing for this object and its children
    emit suicide();
}
#if 0
///////////////////////////////////////////////////////////////////////////////
void playRows_Worker::on_Sig_playRows(MPF_Vec_Ptr pv, QRgb _num_iterationsBASE, double _increase_sample_size_by,
              QRgb _begin, QRgb _end, QRgb _num_notes, std::shared_ptr<int> ppr)
{
    /*std::shared_ptr<int>*/ spi = ppr;
    //processEvents(QEventLoop::ExcludeUserInputEvents);
    Data::vec_LogisticMap_Data::num_iterations_base()=_num_iterationsBASE;
    increase_sample_size_by=_increase_sample_size_by;
    begin=_begin;
    end=_end;
    num_notes=_num_notes;

    MPF_Vec newBound = *pv.get();
    x_min_mpf = *((newBound[static_cast<std::size_t>(mpfRect::COORD::X_MIN_T)]).get()); //std::get<0>(chosen_range);
    y_min_mpf = *((newBound[static_cast<std::size_t>(mpfRect::COORD::Y_MIN_T)]).get()); //std::get<1>(chosen_range);
    x_max_mpf = *((newBound[2+static_cast<std::size_t>(mpfRect::COORD::X_MIN_T)]).get()); //std::get<2>(chosen_range);
    y_max_mpf = *((newBound[2+static_cast<std::size_t>(mpfRect::COORD::Y_MIN_T)]).get()); //std::get<3>(chosen_range);
    width_t  = x_max_mpf - x_min_mpf;
    height_t = y_max_mpf - y_min_mpf;

    normalized_width_t  = width_t  / (g_default___screen_width -1);
    normalized_height_t = height_t / (g_default___screen_height-1);
//    std::thread worker(&playRows_Worker::worker_thread);

//    data = "Example data";
//    // send data to the worker thread
//    {
//        std::lock_guard<std::playRows_Worker_mutex> lk(t1_cond_playRows_Worker_mutex);
//        ready = true;
//        std::cout << "main() signals data ready for processing\n";
//    }
//    LMap::t1_condv.notify_one();

//    // wait for the worker
//    {
//        std::unique_lock<std::playRows_Worker_mutex> lk(t1_cond_playRows_Worker_mutex);
//        LMap::t1_condv.wait(lk, []{return processed;});
//    }
//    std::cout << "Back in main(), data = " << data << '\n';

//    worker.join();
    run();
//    playRows_Worker::ready = false;
//    playRows_Worker::processed = false;
}
#endif
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////


