#ifndef MYCENTRALWIDGET_H
#define MYCENTRALWIDGET_H

#include <QObject>
#include <QWidget>
class OGLframe;
class MyCentralWidget : public QWidget
{
    Q_OBJECT
    friend OGLframe;
public:
    explicit MyCentralWidget(QWidget *parent = nullptr);
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    QPoint ScreenToModel( QPoint const &pos) const;
    OGLframe*frameOGL=nullptr;

signals:

public slots:
};

#endif // MYCENTRALWIDGET_H
