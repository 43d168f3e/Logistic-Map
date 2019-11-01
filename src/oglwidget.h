#ifndef OGLWIDGET_H
#define OGLWIDGET_H


#include "global.h"
#include <QOpenGLWidget>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPoint>
#include <QSize>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QMouseEvent>
#include <QRubberBand>
#include "oglframe.h"


class LMap;
class playRows_Worker;
class OGLWidget;
typedef void (*SignalHandler)(OGLWidget * ptr);



class OGLWidget : public QOpenGLWidget
{
    Q_OBJECT
    friend LMap;
    friend OGLframe;
    friend class playRows_Worker;
public:
    OGLWidget(LMap*pmap, /*QWidget*/ OGLframe *parent = nullptr);
    ~OGLWidget() override;
    static constexpr const double aspectRatio{ static_cast<double>( g_default___screen_width ) / static_cast<double>( g_default___screen_height )};
    //void requestRedraw(QPoint const &m_mseDn, QPoint const &m_mseUp, QSize const & size, double const &aspectRatio);

    void UPDATE(void) {update();}
    void func(uint32_t v) /*const*/
    {
        update();
        printf("instance member callback: %u\n", v);
        //this->update();
    }

protected:
    void DisplayMap(void);
    void paintEvent(QPaintEvent *event) override;//choice between using QPainter and standard OpenGL rendering commands
    void draw(QPoint const &p);
    void draw(QPoint const &prev, QPoint const &p);
//widget's OpenGL rendering context is made current when paintGL(), resizeGL(), or initializeGL() is called.
    //widget's OpenGL rendering context is made current when paintGL(), resizeGL(), or initializeGL() is called.
    void mouseDoubleClickEvent(QMouseEvent *event)  override { event->accept();}
    // NEVER CALLED:void closeEvent(QCloseEvent *event) override;
<<<<<<< HEAD
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
//    void keyPressEvent(QKeyEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
=======
//  void mousePressEvent(QMouseEvent *event) override;
//  void mouseReleaseEvent(QMouseEvent *event) override;
//  void mouseMoveEvent(QMouseEvent *event) override;
//    void keyPressEvent(QKeyEvent *event) override;
>>>>>>> a05e49d729fc6aaee688a84d33145411faae9dda
    QPoint ScreenToModel( QPoint const &pos) const;
    void set_ptr_LM(LMap *_ptr_LM) {
        m_ptr_LMap = _ptr_LM;
    }


    struct HACK {
        QPoint prev{QPoint{}};
        QPoint p{QPoint{}};
        bool goldenHACK{false};
        SignalHandler fn;
    } m_hack;


    std::unique_ptr<QRubberBand> m_rubberBand;
    bool dragging_QRubberBand{false};
    QPoint origin_QRubberBand{};// = event->pos();
    QPoint enterEventQPoint, leaveEventEventQPoint;

private:
    bool b_mousePress{false};
    QPoint  m_mseDn;
    QPoint  m_mseUp;
    QPoint mouseMoveEventQPoint;
    int elapsed;
    uint rgbFromWaveLength(double wave);

    enum { ColormapSize = 512 };
    uint colormap[ColormapSize];
    LMap* m_ptr_LMap{nullptr};
private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
    QPixmap pixmap;
//    void paint(QPainter *painter, QPaintEvent *event, int elapsed);
    std::unique_ptr<QPainter> painter{nullptr};//circles for playMap
    OGLframe*frameOGL = nullptr;
    void clear_mousePressEvent_and_QPoints(void)/*{
        b_mousePress = false;
        frameOGL->mouseMoveEventQPoint=m_mseDn=m_mseUp=enterEventQPoint=leaveEventEventQPoint = QPoint();
        m_rubberBand.release();
        m_rubberBand = nullptr;
        dragging_QRubberBand = false;
        origin_QRubberBand = QPoint{};
    }*/;

public slots:
//void newPixmapFromThreadDraw(void);//, double scaleFactor);
    void newPixmapFromThreadDraw(QImage const &image);//, double scaleFactor);

signals:
void map(QImage const &image);//std::size_t const n, QRgb *buffer);
void set_mouse_Text( QString const &qs);
};

#endif // OGLWIDGET_H
