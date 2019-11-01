#ifndef OGLFRAME_H
#define OGLFRAME_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QtWidgets/QFrame>
#include <QPoint>
#include <QSize>
#include <QMouseEvent>
#include <QRubberBand>

class MyCentralWidget;
class OGLWidget;

class OGLframe : public QFrame
{
    Q_OBJECT
    friend MyCentralWidget;
    friend OGLWidget;
public:
    OGLframe(/*QWidget*/ MyCentralWidget*centralWidget = nullptr);
protected:
    QPoint  m_mseDn;
    QPoint  m_mseUp;
    QPoint mouseMoveEventQPoint;
    QPoint enterEventQPoint, leaveEventEventQPoint;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
//    void keyPressEvent(QKeyEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    QPoint ScreenToModel( QPoint const &pos) const;
    OGLWidget*openGLWidget = nullptr;
    void clear_mousePressEvent_and_QPoints(void){
        mouseMoveEventQPoint=m_mseDn=m_mseUp=enterEventQPoint=leaveEventEventQPoint = QPoint();
    }
signals:
    void set_mouse_Text( QString const &qs);
};

#endif // OGLFRAME_H
