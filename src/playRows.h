#ifndef PLAYROWS_H
#define PLAYROWS_H
//-> -> -> -> "emit XXX()"  RETURNS to the calling proc !!! NOT async !!!
#if 0
-> -> -> -> "emit XXX()"  RETURNS to the calling proc !!!
-> -> -> -> "emit XXX()"  RETURNS to the calling proc !!!
//emit is just syntactic sugar. If you look at the pre-processed output of function that emits a signal,
//you'll see emit is just gone.
->
/*
 * http://doc.qt.io/qt-5/qthread.html#details
 * new slots should *** NOT *** be implemented directly into a subclassed QThread.
 * new slots should *** NOT *** be implemented directly into a subclassed QThread.
 * new slots should *** NOT *** be implemented directly into a subclassed QThread.
 * new slots should *** NOT *** be implemented directly into a subclassed QThread.
*/

//    Qt signals CAN return a value!!!!!!!!!!!!!!!!!

//    Qt signals CAN return a value!!!!!!!!!!!!!!!!!

//    Qt signals CAN return a value!!!!!!!!!!!!!!!!!

//    Qt signals CAN return a value!!!!!!!!!!!!!!!!!

class Thread  : public QThread{
    Q_OBJECT
  using QThread::run; // make it final
public:
  Thread(QObject * parent = nullptr) : QThread(parent) {}
  ~Thread() override { requestInterruption(); quit(); wait(); }
};

///////////////////////////////////////////////////////////////////////////////
class Worker : public QObject
{
    Q_OBJECT

public slots:
    void do_playROWS(const QString &parameter) {
        QString result;
        /* ... here is the expensive or blocking operation ... */
        emit resultReady(result);
    }

signals:
    void resultReady(const QString &result);
};
///////////////////////////////////////////////////////////////////////////////
class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    Controller() {
        Worker *worker = new Worker;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::sig_playROWS, worker, &Worker::do_playROWS);
        connect(worker, &Worker::resultReady, this, &Controller::handleResults);
        workerThread.start();
//By default, run() starts the event loop by calling exec() and runs a Qt event loop inside the thread.
    }
    ~Controller() {
        workerThread.quit();
        workerThread.wait();
    }
public slots:
    void handleResults(const QString &);
signals:
    void sig_playROWS(const QString &);
};
///////////////////////////////////////////////////////////////////////////////
class Task : public QObject
{
Q_OBJECT
public:
    Task();
    ~Task();
public slots:
    // doWork must emit workFinished when it is done.
    void doWork();
signals:
    void workFinished();
};
///////////////////////////////////////////////////////////////////////////////
QThread* thread = new QThread( );
Task* task = new Task();

// move the task object to the thread BEFORE connecting any signal/slots
task->moveToThread(thread);

connect(thread, SIGNAL(started()), task, SLOT(doWork()));
connect(task, SIGNAL(workFinished()), thread, SLOT(quit()));

// automatically delete thread and task object when work is done:
connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
connect(task, SIGNAL(workFinished()), task, SLOT(deleteLater()));?
connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));??

thread->start();
#endif
///////////////////////////////////////////////////////////////////////////////
#include <QSharedPointer>
#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>
//#include <QObject>
#include <QtWidgets>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <ctime>
#include <cassert>

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
//#include "mpfRect.h"
#include "data.h"//#include "rect_data.h"

class LMap;
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////LogisticMap_Data_Structure_Ptr pv, //////////////////////////////
class playRows_Worker : public QObject
{
    Q_OBJECT
    friend LMap;
    constexpr static const int nrows{600};
    constexpr static const int ncols{960};
public:
    mpf_class x_max_mpf;
    mpf_class x_min_mpf;
    mpf_class y_max_mpf;
    mpf_class y_min_mpf;
    mpf_class height_t;
    mpf_class width_t;
    mpf_class normalized_height_t;
    mpf_class normalized_width_t;
    //QRgb g_default___screen_width{ncols};
    //QRgb g_default___screen_height{nrows};
    QRgb num_iterations_base{1000};
    double increase_sample_size_by{1};
    QRgb begin{0};//m_FROM;
    QRgb end{599};//this->m_TO;
    QRgb num_notes{24};//this->m_TO;
    float lFrequency{440.f} ;// toot -f 440. -l 300
    int lLength_ms{116} ;
    //playRows_Worker(QObject *parent ) : QObject{parent}{}
    playRows_Worker(std::size_t index,
             QRgb _begin, QRgb _end, QRgb _num_notes, int lLength_ms,
             std::atomic<int> &spi, class LMap *ptrLMap, mpf_class rate_t, QObject *parent = nullptr);
private:
    //std::shared_ptr<int> spi;
    std::atomic<int> &spi;
    LMap *m_ptr_LMap{nullptr};
    //Play_Music_ROOT *m_ptrPlay_Music_ROOT{nullptr};
protected:
//    void run() override;
    void broadcast_first();
/*
 * http://doc.qt.io/qt-5/qthread.html#details
 * new slots should *** NOT *** be implemented directly into a subclassed QThread.
 * new slots should *** NOT *** be implemented directly into a subclassed QThread.
 * new slots should *** NOT *** be implemented directly into a subclassed QThread.
 * new slots should *** NOT *** be implemented directly into a subclassed QThread.
*/
//protected Q_SLOTS:

public slots:
    void do_playROWS(std::size_t index);
    void do_playThisRate(std::size_t index );
    void on_StopProcess(void);
    void on_UpdateMilliSeconds(int n) {
        if (n>=50&&n<=500) {
            QMutexLocker locker(&playRows_Worker_mutex);
            if (n != lLength_ms) lLength_ms =n;
        }
    }

signals:
    void resultReady(const QString &result);
    void s_rate(std::string const &);
    void qs_rate(const QString &);
    void d_rate(double);
    void sp_rate(std::shared_ptr<std::string const> s);
    void clear(void);
    void cut(void);
    void selectAll(void);
    void sig_begin(void);
    void suicide(void);
private:
    bool m_abort{false};
    mpf_class rate_t;
public:
    static QMutex playRows_Worker_mutex;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////LogisticMap_Data_Structure_Ptr pv, ////////////////////////

class playRows_Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
    friend LMap;
    constexpr static const int nrows{600};
    constexpr static const int ncols{960};
public:
    playRows_Controller(std::size_t index,
                         QRgb _begin, QRgb _end, QRgb _num_notes, int lLength_ms,
                        std::atomic<int> &spi,  LMap* _ptrLMap, bool b_for_play_RATE, mpf_class rate_t);
    playRows_Controller() {}
    ~playRows_Controller() {
        workerThread.quit();
        workerThread.wait();
    }
    //playRows_Worker *worker{nullptr};
    LMap* m_ptr_LMap{nullptr};
public slots:
    void handleResults(const QString &){}
    void on_playROWS(std::size_t index) {
        emit sig_playROWS(index);
    }
    void on_playThisRate(std::size_t index) {
        emit sig_playThisRate(index);
        //worker->do_playThisRate(index); 'cancel' button NOT active
    }
    void on_StopProcess(void);
    void on_Suicide(void) {emit suicide();}
    void on_Begin(void) {emit sig_begin();}


    void on_resultReady(const QString &result) {emit resultReady(result);}
    void on_s_rate(std::string const &s) {emit s_rate(s);}
    void on_qs_rate(const QString &s) {emit qs_rate(s);}
    void on_d_rate(double r) {emit d_rate(r);}
    void on_sp_rate(std::shared_ptr<std::string const> s) {emit sp_rate(s);}
    void on_clear(void) {emit clear();}
    void on_cut(void) {emit cut();}
    void on_selectAll(void) {emit selectAll();}
    void on_UpdateMilliSeconds(int n) {emit updateMilliSeconds(n);}

signals:
    void sig_playROWS(std::size_t);//const QString &);
    void sig_playThisRate(std::size_t);
    void sig_begin(void);
    void stopProcess(void);
    void suicide(void);
    void resultReady(const QString &result);
    void s_rate(std::string const &);
    void qs_rate(const QString &);
    void d_rate(double);
    void sp_rate(std::shared_ptr<std::string const> s);
    void clear(void);
    void cut(void);
    void selectAll(void);
    void updateMilliSeconds(int);
};

#endif // PLAYROWS_H
