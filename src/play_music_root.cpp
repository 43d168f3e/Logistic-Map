#include "play_music_root.h"
#include "playRows.h"
#include "work.h"
#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>
#include "lmap.h"
#include "data.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Play_Music_ROOT::Play_Music_ROOT
/// \param ptr_LMap
/// \param parent
///
Play_Music_ROOT::Play_Music_ROOT(LMap * ptr_LMap, QObject *parent) :
    QObject(parent),
    m_ptr_LMap{ptr_LMap},
    spi{m_ptr_LMap->spi}
{
//    auto x = m_ptr_LMap;
    initialize_play_connections(m_ptr_LMap->b_Rate_Play);
}
///////////////////////////////////////////////////////////////////////////////
/// \brief Play_Music_ROOT::set_LMap_ptr
/// \param ptr_LMap
///
//void Play_Music_ROOT::set_LMap_ptr(LMap * ptr_LMap) {
//    auto x = m_ptr_LMap;
//    m_ptr_LMap = ptr_LMap;
//}
///////////////////////////////////////////////////////////////////////////////
/// \brief LMap::initialize_play_connections
/// Thus, a developer who wishes to invoke slots in the new thread must use the worker-object approach;
/// new slots should not be implemented directly into a subclassed QThread
///
void Play_Music_ROOT::initialize_play_connections(bool b_for_play_RATE)
{
    m_ptr_LMap->ReleaseMouse();
    spR.reset();
    //spi.reset();
    spR = nullptr;
    spi = 0;//nullptr;

#if 0
    for (auto &n : f_notes) {
        std::cout << n.f << " ";
        toot( n.f , 100 ) ;
    }
    std::cout << std::endl;
#endif

//    QString qs = pb_Rate_Goto->text();
//    std::string s{qs.toStdString()};
//    std::string t = do_replace(s);
//    mpf_class r(t.c_str(), NS_LogisticMap::prec, 10);
    mpf_class rate{};//(t.c_str(), NS_LogisticMap::prec, 10);
    //... but not used in the on_playROWS fn call

    if (b_for_play_RATE) {
        try {
            rate = m_ptr_LMap->get_dialog_Play_Rate_mpf();
        } catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            //return r;
        }
    }
    else {
            //rate = r;
    }

    //spi = std::make_shared<int>();
    spR = std::make_shared<playRows_Controller>(m_ptr_LMap->m_selected, m_ptr_LMap->m_FROM, m_ptr_LMap->m_TO, m_ptr_LMap->m_NUM_NOTES,
                                            m_ptr_LMap->lLength_ms, spi, this, b_for_play_RATE, rate);

auto q= spR;
    //QObject::connect(m_ptr_LMap->pb_cancel, &QPushButton::clicked, spR.get(), &playRows_Controller::on_StopProcess);
#if 0
QObject::connect(this, &LMap::sig_playROWS,     spR.get(),  &playRows_Controller::on_playROWS );
QObject::connect(this, &LMap::sig_playThisRate , spR.get(),  &playRows_Controller::on_playThisRate  );//emit SUCCEEDS
//emit FAILS:connect(this, SLOT(sig_playThisRate(std::size_t)), spR.get(),  SIGNAL(on_playThisRate(std::size_t)) );
QObject::connect(spR.get(), &playRows_Controller::suicide,  this, &LMap::on_Suicide);
QObject::connect(pb_cancel, &QPushButton::clicked, spR.get(), &playRows_Controller::on_StopProcess);

QObject::connect(spR.get(), &playRows_Controller::qs_rate,      pb_Rate_Play, &QPushButton::setText);

QObject::connect(spR.get(), &playRows_Controller::selectAll,    plainTextEdit_rate, &QPlainTextEdit::selectAll);
QObject::connect(spR.get(), &playRows_Controller::cut,          plainTextEdit_rate, &QPlainTextEdit::cut);
QObject::connect(spR.get(), &playRows_Controller::clear,        plainTextEdit_rate, &QPlainTextEdit::clear);
QObject::connect(spR.get(), &playRows_Controller::qs_rate,      plainTextEdit_rate, &QPlainTextEdit::setPlainText);

//QObject::connect(spR.get(), &playRows_Controller::selectAll,    lbl_rate, &Rate_Label::selectAll);
//QObject::connect(spR.get(), &playRows_Controller::cut,          lbl_rate, &Rate_Label::cut);
QObject::connect(spR.get(), &playRows_Controller::clear,        lbl_rate, &Rate_Label::clear);
QObject::connect(spR.get(), &playRows_Controller::qs_rate,      lbl_rate, &Rate_Label::setText2);
QObject::connect(spR.get(), &playRows_Controller::d_rate,       lbl_rate, &Rate_Label::setNum2);
QObject::connect(spR.get(), &playRows_Controller::sp_rate,      lbl_rate, &Rate_Label::onRate);
#endif

//emit sig_playROWS();

#if 0
//emit is just syntactic sugar. If you look at the pre-processed output of function that emits a signal, you'll see emit is just gone.
    std::shared_ptr<int> spi = std::make_shared<int>();
    emit sig_cpr(spi);
    openGLWidget->setCursor(Qt::CrossCursor);
    setCursor(Qt::CrossCursor);
    set_abort_play_rows(false);
    emit sig_playRows(pv, LogisticMap_data_structure::num_iterations_base(), increase_sample_size_by, m_FROM, m_TO, m_NUM_NOTES, spi);
    //spi.reset();
#endif
    //return rate;
}
///////////////////////////////////////////////////////////////////////////////
void Play_Music_ROOT::updateMilliSeconds(int n) {
    if (spi==1&&spR && spR != nullptr && spR.use_count()>0) emit spR->updateMilliSeconds(n);
}

///////////////////////////////////////////////////////////////////////////////
void Play_Music_ROOT::on_Suicide(void) {
//    m_ptr_LMap->ReleaseMouse();
//    m_ptr_LMap->playROWS_ON();
//    m_ptr_LMap->b_playingMusic = false;
//    m_ptr_LMap->openGLWidget->setCursor(Qt::CrossCursor);
//    m_ptr_LMap->setCursor(Qt::CrossCursor);
//    QObject::disconnect(this, &LMap::sig_playROWS,     spR.get(),  &playRows_Controller::on_playROWS );
//    QObject::disconnect(this, &LMap::sig_playThisRate, spR.get(),  &playRows_Controller::on_playThisRate );
    QObject::disconnect(spR.get(), &playRows_Controller::suicide,   this, &Play_Music_ROOT::on_Suicide);
    QObject::disconnect(spR.get(), &playRows_Controller::suicide,   m_ptr_LMap, &LMap::on_End);
    QObject::disconnect(spR.get(), &playRows_Controller::sig_begin, m_ptr_LMap, &LMap::on_Begin);
    QObject::disconnect(m_ptr_LMap->pb_cancel, &QPushButton::clicked, spR.get(), &playRows_Controller::on_StopProcess);

//    QObject::disconnect(spR.get(), &playRows_Controller::qs_rate,      m_ptr_LMap->pb_Rate_Play, &QPushButton::setText);
//    QObject::disconnect(spR.get(), &playRows_Controller::qs_rate,      m_ptr_LMap->pb_Rate_Goto, &QPushButton::setText);

    QObject::disconnect(spR.get(), &playRows_Controller::qs_rate,      m_ptr_LMap->pb_Rate_Play, &QPushButton::setText);
    QObject::disconnect(spR.get(), &playRows_Controller::qs_rate,      m_ptr_LMap->pb_Rate_Goto, &QPushButton::setText);

//    QObject::disconnect(spR.get(), &playRows_Controller::selectAll,    m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::selectAll);
//    QObject::disconnect(spR.get(), &playRows_Controller::cut,          m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::cut);
//    QObject::disconnect(spR.get(), &playRows_Controller::clear,        m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::clear);
//    QObject::disconnect(spR.get(), &playRows_Controller::qs_rate,      m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::setPlainText);

//    //QObject::disconnect(spR.get(), &playRows_Controller::selectAll,    lbl_rate, &Rate_Label::selectAll);
//    //QObject::disconnect(spR.get(), &playRows_Controller::cut,          lbl_rate, &Rate_Label::cut);
//    QObject::disconnect(spR.get(), &playRows_Controller::clear,        m_ptr_LMap->lbl_rate, &Rate_Label::clear);
//    QObject::disconnect(spR.get(), &playRows_Controller::qs_rate,      m_ptr_LMap->lbl_rate, &Rate_Label::setText2);
//    QObject::disconnect(spR.get(), &playRows_Controller::d_rate,       m_ptr_LMap->lbl_rate, &Rate_Label::setNum2);
//    QObject::disconnect(spR.get(), &playRows_Controller::sp_rate,      m_ptr_LMap->lbl_rate, &Rate_Label::onRate);
    spR.reset();
    //spi.reset();
    spR = nullptr;
    spi = 0;//nullptr;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
