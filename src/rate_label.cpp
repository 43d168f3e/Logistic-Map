#include "rate_label.h"

Rate_Label::Rate_Label(QWidget *parent) : QLabel(parent)
{

}
///////////////////////////////////////////////////////////////////////////////
Rate_Label::Rate_Label(const QString &text, QWidget *parent) : QLabel(parent)
{
    setText(text);
    QLabel::update();
    updateGeometry();
    repaint();
}

///////////////////////////////////////////////////////////////////////////////
void Rate_Label::onRate(std::shared_ptr<std::string const> a) {
    std::string s = *a.get();
    QString qs{s.c_str()};
    clear();
    setText(qs);
    QVariant n{"\0"};
    QVariant v{qs};
    setProperty("text", n);
    setProperty("text", v);
//    setHidden(false);
//    setVisible(true);
    update();
    updateGeometry();
    repaint();
    std::cout << " Rate_Label::rate " << text().toStdString() << std::endl << std::flush;
}
///////////////////////////////////////////////////////////////////////////////
void Rate_Label::setText2(const QString & s) {
    clear();
    setText(s);
    update();
    QLabel::update();
    updateGeometry();
    repaint();
    std::cout << " Rate_Label::setText2 " << text().toStdString() << std::endl << std::flush;
}
///////////////////////////////////////////////////////////////////////////////
void Rate_Label::setNum2(double const & x){
    clear();
    setNum(x);
    update();
    QLabel::update();
    updateGeometry();
    repaint();
    std::cout << " Rate_Label::setText2 " << text().toStdString() << std::endl << std::flush;
}
