#ifndef DIALOGFORRATE_H
#define DIALOGFORRATE_H


#include <QtWidgets/qtwidgetsglobal.h>
#include <QtCore/qstring.h>
#include <QtWidgets/qlineedit.h>

#include <QtWidgets/qdialog.h>

QT_REQUIRE_CONFIG(inputdialog);

#include <QPointer>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
//#include <QAutoPointer>


#include <regex>
#include <iostream>
#include <iterator>
#include <functional>

static std::string do_replace( std::string const & in )
{
//  std::regex vowel_re("&|=|R| ");
//  std::regex vowel_re("&|=|,|>|<|-|[A-Z]|[a-z]| ");
    std::regex vowel_re("&|=|,|>|<|-|[A-Z]|[a-z]| ");
  std::ostringstream ss;
  std::regex_replace( std::ostreambuf_iterator<char>(ss), in.begin(), in.end(), vowel_re, "");
  std::string out = ss.str();
  return out;
}

#if 0
std::regex vowel_re("a|e|i|o|u");

// write the results to an output iterator
std::regex_replace(std::ostreambuf_iterator<char>(std::cout),
                   text.begin(), text.end(), vowel_re, "*");

// construct a string holding the results
std::cout << '\n' << std::regex_replace(text, vowel_re, "[$&]") << '\n';

static std::string do_replace( std::string const & in, std::string const & from, std::string const & to )
{
  return std::regex_replace( in, std::regex(from), to );
}
#endif


template <typename T>
class QAutoPointer {
    QPointer<T> o;
    struct internal { void func() {} };
    typedef void (internal::*RestrictedBool)();
public:
    explicit QAutoPointer(T *t) Q_DECL_NOTHROW : o(t) {}
    ~QAutoPointer() { delete o; }

    T *operator->() const Q_DECL_NOTHROW { return get(); }
    T *get() const Q_DECL_NOTHROW { return o; }
    T &operator*() const { return *get(); }
    operator RestrictedBool() const Q_DECL_NOTHROW { return o ? &internal::func : nullptr; }
    bool operator!() const Q_DECL_NOTHROW { return !o; }
private:
    Q_DISABLE_COPY(QAutoPointer)
};


namespace Ui {
class DialogForRATE;
}


static constexpr const char str_play[]=R"(Rate to 'play:')";
static constexpr const char str_goto[]=R"(Rate to goto:)";

class LMap;
using lm_v_v_t = std::function<void(LMap::*)(void)>;
//static lm_v_v_t pt2ConstMember = nullptr;

//static void (LMap::*pt2ConstMember)(void) = nullptr;

class DialogForRATE : public QDialog
{
    Q_OBJECT

public:
    explicit DialogForRATE(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~DialogForRATE();
    QString getDialogText(QWidget *parent, /*const QString &title, const QString &label,
                    QLineEdit::EchoMode mode,*/ const QString &text, bool *ok,
                    Qt::WindowFlags flags=Qt::Dialog, Qt::InputMethodHints inputMethodHints = Qt::ImhFormattedNumbersOnly);
    void setTextValue(QString const &text) {
        lineEdit_rate->setText(text);
        lineEdit_rate->setCursorPosition(0);
        lineEdit_rate->update();
        lineEdit_rate->show();
    }

    QString getTextValue(void) {
        return lineEdit_rate->text();
    }

    QString rate_qstring() const;
    quint16 remotePort() const
    {
        return 0;//quint16(ui->portSelector->text().toUInt());
    }

private:
    Ui::DialogForRATE *ui;
    Qt::WindowFlags flags;
    QLineEdit *lineEdit_rate{nullptr};
    QLabel *label_rate{nullptr};
};

#endif // DIALOGFORRATE_H





























