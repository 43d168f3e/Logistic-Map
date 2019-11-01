#include "dialogForRATE.h"
#include "ui_dialogForRATE.h"
#include <thread>
#include <cmath>
#include <string>
#include "lmap.h"

DialogForRATE::DialogForRATE(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent),
    ui(new Ui::DialogForRATE),
    flags{f}
{
    ui->setupUi(this);
    lineEdit_rate = ui->lineEdit_rate;
    label_rate = ui->label_rate;
//    if (pt2ConstMember == &LMap::playThisRate) label_rate->setText(str_play);
//    if (pt2ConstMember == &LMap::gotoThisRate) label_rate->setText(str_goto);

    QObject::connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    QObject::connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

DialogForRATE::~DialogForRATE()
{
    delete ui;
}
///////////////////////////////////////////////////////////////////////////////
/*
stoul
stoull
stoi
stol
stoll
stof
stod
stold
*/

QString DialogForRATE::rate_qstring() const
{
    //lineEdit_rate = ui->lineEdit_rate;
    //label_rate = ui->label_rate;
    //if (ui->label_rate->count())
        return ui->lineEdit_rate->text();
    return {};
}

static constexpr const double minR{0};
static constexpr const double mmxR{4};
template <typename T>
bool contains(T x) {
    if (static_cast<T>(mmxR) >= x && x >= static_cast<T>(minR)) { return true; }
    return false; }

QString DialogForRATE::getDialogText(QWidget *parent, const QString &text, bool *ok,
                                     Qt::WindowFlags flags, Qt::InputMethodHints inputMethodHints)
{
    setTextValue(text);
    lineEdit_rate->selectAll();
    setInputMethodHints(inputMethodHints);
    const int ret = exec();
    if (ok)
        *ok = !!ret;
    if (ret) {
        QString q = getTextValue();
        {
            std::string s{q.toStdString()};
            std::string t = do_replace(s);
            QString qs{t.c_str()};
            try {double d{-1}; d = std::stod(t); if (contains(d)) return qs;} catch (...) { }
            try {float f{-1}; f = std::stof(t); if (contains(f)) return qs;} catch (...) { }
            try {int i{-1}; i = std::stoi(t); if (contains(i)) return qs;} catch (...) { }
            try {long l{-1}; l = std::stol(t); if (contains(l)) return qs;} catch (...) { }
            try {long long L{-1}; L = std::stoll(t); if (contains(L)) return qs;} catch (...) { }
            try {long double D{-1}; D = std::stold(t); if (contains(D)) return qs;} catch (...) { }
            *ok = false;
        }
        return text;
    } else {
        return text;//QString();
    }
#if 0
    QAutoPointer<DialogForRATE> dialog(new DialogForRATE(parent, flags));
    //dialog->setWindowTitle(title);
    //dialog->setLabelText(label);
    dialog->setTextValue(text);
    //dialog->setTextEchoMode(mode);
    dialog->setInputMethodHints(inputMethodHints);

    const int ret = dialog->exec();
    if (ok)
        *ok = !!ret;
    if (ret) {
        dialog->setTextValue(dialog->getTextValue());
        return dialog->getTextValue();
    } else {
        return QString();
    }
#endif

}
//QString DialogForRATE::getText(QWidget *parent, /*const QString &title, const QString &label,
//                              QLineEdit::EchoMode mode,*/ const QString &text, bool *ok,
//                              Qt::WindowFlags flags, Qt::InputMethodHints inputMethodHints)
