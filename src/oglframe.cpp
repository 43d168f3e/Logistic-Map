#include "oglframe.h"
#include "mycentralwidget.h"
#include "src/oglwidget.h"
#include <QApplication>

OGLframe::OGLframe(/*QWidget*/ MyCentralWidget*centralWidget):
    QFrame{centralWidget}
{
    centralWidget->frameOGL = this;
//    const QObjectList &cl = children();
//    if (openGLWidget==nullptr) {
//    foreach (QObject *qo, children()) {
//        if (auto q = qobject_cast<OGLWidget *>(qo)) {
//            openGLWidget = q;
//        }
//    }
//    }
//    if (openGLWidget==nullptr) {
//        openGLWidget = findChild<OGLWidget *>("openGLWidget");
//    }

////    foreach (QWidget *widget, QApplication::allWidgets()) {
////        if (auto mainWindow = qobject_cast<OGLWidget *>(widget)) {
////            openGLWidget = mainWindow;
////        }
////    }
//    if (openGLWidget==nullptr) {
//        std::cout << "openGLWidget==nullptr" << std::endl;
//        exit(-7);
//    }
//Mouse move events will occur only when a mouse button is pressed down, unless mouse tracking has been enabled with QWidget::setMouseTracking().
    setMouseTracking(true);

}

void OGLframe::mouseMoveEvent(QMouseEvent *event){
    mouseMoveEventQPoint = ScreenToModel( event->pos()  );
//    mouseMoveEventQPoint.rx() -= 20;
//    mouseMoveEventQPoint.ry() -= 20;
    //    QString rate{rs2.c_str()};
        QString x; x.setNum( mouseMoveEventQPoint.x() );
        QString y; y.setNum( mouseMoveEventQPoint.y() );
        QString qs{"<html><head/><body><p>Screen Mouse:</p><p>x= " + x + "; y = "+  y + "</p><p>R= " /*+ rate*/ + "</p></body></html>"};
        //m_ptr_LMap->onSet_mouse_Text( qs ); employ signal
        qs = "OGLframe Screen Mouse:\nx= " + x + "; y = " +  y;
        emit set_mouse_Text( qs );
}

///////////////////////////////////////////////////////////////////////////////
#if 0
#endif
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void OGLframe::enterEvent(QEvent *event) {
    enterEventQPoint = mouseMoveEventQPoint;
}
///////////////////////////////////////////////////////////////////////////////
void OGLframe::leaveEvent(QEvent *event) {
    leaveEventEventQPoint = mouseMoveEventQPoint;
}
///////////////////////////////////////////////////////////////////////////////

void OGLframe::mousePressEvent(QMouseEvent *event)
{
    openGLWidget->m_mseDn = m_mseDn = ScreenToModel( event->pos()  );
}

void OGLframe::mouseReleaseEvent(QMouseEvent *event)
{
    openGLWidget->m_mseUp = m_mseUp = ScreenToModel( event->pos()  );
}
///////////////////////////////////////////////////////////////////////////////
QPoint OGLframe::ScreenToModel( QPoint const &pos) const {
    QPoint p{ pos.x(), (this->size().height() - 1) - pos.y() };
    p.rx() -= 20;
    p.ry() -= 20;
    return p;
}
///////////////////////////////////////////////////////////////////////////////
