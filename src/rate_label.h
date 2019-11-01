#ifndef RATE_LABEL_H
#define RATE_LABEL_H

#include <QLabel>
#include <QtWidgets>
#include <iostream>
#include <memory>
#include <iomanip>
#include <string>
#include <cstring>

class Rate_Label : public QLabel
{
    Q_OBJECT
    friend class LMap;
public:
    //explicit Rate_Label(QWidget *parent = nullptr);
    ~Rate_Label() override {}// {wait();}
    Rate_Label(QWidget *parent = nullptr);
    Rate_Label(const QString &text, QWidget *parent = nullptr);
signals:

public slots:
    void onRate(std::shared_ptr<std::string const> s);
    void setText2(QString const & s);
    void setNum2(double const & x);
};

#endif // RATE_LABEL_H
