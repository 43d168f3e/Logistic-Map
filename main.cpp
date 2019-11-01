
#include "lmap.h"

#include "QJsonModel/qjsontreeview.h"

#include <QApplication>
#include <QtWidgets>
#include <QDebug>
//#include <QThread>
//#include <QWidget>
//#include <QtWidgets>
#include <QVBoxLayout>
//https://github.com/coozoo/qtjsondiff.git>
//https://github.com/coozoo/qtjsondiff

//using OGLWidget = QWidget;
//using Rate_Label = QLabel;

//#include "declarations.h"


//using namespace std::chrono;
//#include "setupUi.h"

#include <rxqt.hpp>
#include <rxcpp/operators/rx-subscribe_on.hpp>
#include <rxcpp/operators/rx-observe_on.hpp>

namespace Rx {
    using namespace rxcpp;
    using namespace rxcpp::sources;
    using namespace rxcpp::operators;
    using namespace rxcpp::util;
}

QString threadId(const QString& name)
{
    return name + QString(": %1\n").arg(reinterpret_cast<uintptr_t>(QThread::currentThreadId()));
}

#include <iostream>
#include <type_traits>

template <typename T, typename U>
struct decay_equiv :
    std::is_same<typename std::decay<T>::type, U>::type
{};

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

//typedef QRgb
//An ARGB quadruplet on the format #AARRGGBB, equivalent to an unsigned int.
//QT += gui

//#include <QColor>
//std::unique_ptr<QRgb[]> mem_global{std::make_unique<QRgb[]>(g_default___screen_width*g_default___screen_height)};

int main(int argc, char *argv[])
{
    mpf_set_default_prec (NS_LogisticMap::prec);

    std::cout << std::boolalpha << "std::is_same<QRgb, std::uint32_t>::value = "  << std::is_same<QRgb, std::uint32_t>::value << '\n';

    std::cout<<"NS_LogisticMap::COORD::X_MIN_T=" << as_integer(NS_LogisticMap::COORD::X_MIN_T) << std::endl;
    std::cout<<"NS_LogisticMap::COORD::POINT_DENSITY_EXPONENT_T=" << as_integer(NS_LogisticMap::COORD::POINT_DENSITY_EXPONENT_T) << std::endl;
    std::cout<<"NS_LogisticMap::COORD::ID_BASE=" << as_integer(NS_LogisticMap::COORD::ID_BASE) << std::endl;

    QApplication a(argc, argv);
    a.setDoubleClickInterval(400);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setColorSpace(QSurfaceFormat::sRGBColorSpace);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    //rxqt::run_loop rxqt_run_loop;
    char* argv1{nullptr};
    if (argc==2) { argv1 = argv[1]; }

/*
  QJsonTreeView view WILL NOT TERMINATE WITHOUT
      void LMap::closeEvent (QCloseEvent *event)
protected:
    void closeEvent(QCloseEvent *event) override;
*/
    QJsonTreeView view{};
//    QJsonModel model{};
//    view.setModel(&model);
//    QTreeView * view   = new QTreeView;
//    QJsonModel * model = new QJsonModel;
//    view->setModel(model);
//    QString fileName{"/home/nsh/Documents/Qt/Logistic_Map/test.json"};
//    bool ret =  model->load(fileName);
//    view->show();

    LMap w{argv1};
    LMap *windowLogisticMap = &w;//new LogisticMap{argv1};

// type parameter must be one of QEvent::MouseButtonPress, QEvent::MouseButtonRelease, QEvent::MouseButtonDblClick, or QEvent::MouseMove.
#if 0
    rxqt::from_signal(openGLWidget, &QPushButton::clicked)
            .map([=](const auto&){ return (*count) += 1; })
            .debounce(milliseconds(QApplication::doubleClickInterval()))
            .tap([=](int){ (*count) = 0; })
            .subscribe([label](int x){ label->setText(QString("%1-ple click.").arg(x)); });

    rxqt::from_signal(openGLWidget, &QPushButton::pressed)
            .subscribe([=](const auto&){ label->setText(QString()); });
#endif

#if 0
    rxqt::from_event(w.openGLWidget, QEvent::MouseButtonPress)
            .subscribe([](const QEvent* e){
                auto ke = static_cast<const QMouseEvent*>(e);
                qDebug() << ke->globalX() << " " << ke->globalY() ;
            });
    rxqt::from_event(w.openGLWidget, QEvent::MouseButtonRelease)
            .subscribe([](const QEvent* e){
                auto ke = static_cast<const QMouseEvent*>(e);
                qDebug() << ke->globalX() << " " << ke->globalY() ;
            });
#endif

#if 0
    rxqt::from_event(w.openGLWidget, QEvent::MouseMove)
            .subscribe([](const QEvent* e){
                auto ke = static_cast<const QMouseEvent*>(e);
                qDebug() << ke->globalX() << " " << ke->globalY() ;
                std::cout << ke->globalX() << " " << ke->globalY() << std::endl;
            });
#endif

    auto _layout = std::make_unique<QVBoxLayout>();
    auto layout = _layout.get();
    w.centralWidget->setLayout(layout);
        if (argv1==nullptr || std::strlen(argv1) == 0){
            QSize sz{w.openGLWidget->size()};
            //mem_global = std::make_unique<QRgb[]>(sz.width()*sz.height());//,    ui(new Ui::LMap)
//call BEFORE openGLWidget creationw.InitializeMpfRect(sz);//call BEFORE openGLWidget creation
        }

    if (!QGuiApplication::styleHints()->showIsFullScreen() && !QGuiApplication::styleHints()->showIsMaximized()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(windowLogisticMap);
        //window->resize(availableGeometry.width() / 3, availableGeometry.height() * 2 / 3);
//        window->move((availableGeometry.width() - window->width()) / 2,
//                    (availableGeometry.height() - window->height()) / 2);
        windowLogisticMap->move(20, 20);
        view.move(20+windowLogisticMap->width()+40, 0);
        view.resize(g_default___screen_height,g_default___screen_height);
    }
    view.show();
    //windowLogisticMap->show();
    w.show();

    return a.exec();
}

///////////////////////////////////////////////////////////////////////////////

#if 0
Read it backwards (as driven by Clockwise/Spiral Rule)...

int* - pointer to int
int const * - pointer to const int
int * const - const pointer to int
int const * const - const pointer to const int
Now the first const can be on either side of the type so:

const int * == int const *
const int * const == int const * const
If you want to go really crazy you can do things like this:

int ** - pointer to pointer to int
int ** const - a const pointer to a pointer to an int
int * const * - a pointer to a const pointer to an int
int const ** - a pointer to a pointer to a const int
int * const * const - a const pointer to a const pointer to an int
...
And to make sure we are clear on the meaning of const

const int* foo;
int *const bar; //note, you actually need to set the pointer
    //here because you can't change it later ;)
foo is a variable pointer to a constant int. This lets you change what you point
to but not the value that you point to. Most often this is seen with cstrings
where you have a pointer to a const char. You may change which string you point
to but you cannot change the content of these strings. This is important when the
string itself is in the data segment of a program and should not be changed.

bar is a const or fixed pointer to a value that can be changed. This is like a
reference without the extra syntactic sugar. Because of this fact, usually you
would use a reference where you would use a T* const pointer unless you need to allow null pointers.

===============================================================================
    A connection can only be used from within the thread that created it. Moving connections between threads or creating queries from a different thread is not supported.

    So you do indeed need one connection per thread. I solved this by generating dynamic names based on the thread:

    auto name = "my_db_" + QString::number((quint64)QThread::currentThread(), 16);
    if(QSqlDatabase::contains(name))
return QSqlDatabase::database(name);
    else {
auto db = QSqlDatabase::addDatabase( "QSQLITE", name);
// open the database, setup tables, etc.
return db;
    }
    In case you use threads not managed by Qt make use of QThreadStorage to generate names per thread:

    // must be static, to be the same for all threads
    static QThreadStorage<QString> storage;

    QString name;
    if(storage.hasLocalData())
name = storage.localData();
    else {
//simple way to get a random name
name = "my_db_" + QUuid::createUuid().toString();
storage.setLocalData(name);
    }

===============================================================================

//
===============================================================================




#endif
