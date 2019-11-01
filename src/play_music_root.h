// play_music_root.h

#if 0
#include "play_music_root.h"
#include "src/play_music_root.h"
#include "../src/play_music_root.h"
#endif



#if !defined(PLAY_MUSIC_ROOT_H_7413546gfhjnbc550b53c48ab80a4232466ea81af)
#define	  PLAY_MUSIC_ROOT_H_7413546gfhjnbc550b53c48ab80a4232466ea81af



#include "global.h"
#include <QString>

class LMap;
class playRows_Controller;
class playRows_Worker;
//class QJsonTreeView;
///////////////////////////////////////////////////////////////////////////////


#include <QObject>

class Play_Music_ROOT : public QObject
{
    Q_OBJECT
    friend LMap;
    friend playRows_Worker;
    friend playRows_Controller;
public:
    explicit Play_Music_ROOT(LMap * ptr_LMap, QObject *parent = nullptr);
//    void set_LMap_ptr(LMap * ptr_LMap);

protected:
    LMap *m_ptr_LMap{nullptr};
    std::shared_ptr<playRows_Controller> spR;
    std::atomic<int> &spi;//{0};
    void initialize_play_connections(bool b_for_play_RATE);
    void updateMilliSeconds(int);

signals:

public slots:
    void on_Suicide(void);
};

#endif // PLAY_MUSIC_ROOT_H_7413546gfhjnbc550b53c48ab80a4232466ea81af
