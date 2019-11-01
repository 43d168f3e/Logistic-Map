#include "mycentralwidget.h"
#include "src/oglframe.h"

MyCentralWidget::MyCentralWidget(QWidget *parent) : QWidget(parent)
{

}
///////////////////////////////////////////////////////////////////////////////
void MyCentralWidget::mouseMoveEvent(QMouseEvent *event)
{
    frameOGL->enterEventQPoint = frameOGL->mouseMoveEventQPoint = ScreenToModel( event->pos()  );
}
///////////////////////////////////////////////////////////////////////////////
QPoint MyCentralWidget::ScreenToModel( QPoint const &pos) const {
    QPoint p{ pos.x(), (this->size().height() - 1) - pos.y() };
    p.rx() -= 20;
    p.ry() -= 20;
    return p;
}
///////////////////////////////////////////////////////////////////////////////
