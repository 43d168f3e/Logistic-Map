#include "oglwidget.h"
#include "lmap.h"
#include "assemble_block.h"
//#include "ver42.h"

#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QInputDialog>
#include <QLineEdit>


#if 0
#include <rxqt.hpp>
#include <rxcpp/operators/rx-subscribe_on.hpp>
#include <rxcpp/operators/rx-observe_on.hpp>

namespace Rx {
using namespace rxcpp;
using namespace rxcpp::sources;
using namespace rxcpp::operators;
using namespace rxcpp::util;
}
#endif


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>

/*
/home/nsh/opt/hide-qt5.12.3/include/QtCore/qcoreevent.h
        MouseButtonPress = 2,                   // mouse button pressed
        MouseButtonRelease = 3,                 // mouse button released
        MouseButtonDblClick = 4,                // mouse button double click
        MouseMove = 5,                          // mouse move
        KeyPress = 6,                           // key pressed
        KeyRelease = 7,                         // key released
        FocusIn = 8,                            // keyboard focus received
        FocusOut = 9,                           // keyboard focus lost
        FocusAboutToChange = 23,                // keyboard focus is about to be lost
        Enter = 10,                             // mouse enters widget
        Leave = 11,                             // mouse leaves widget
*/

//void cb(char* const ptr) {qobject_cast<OGLWidget const *>(ptr)->update();}
void cb(OGLWidget * ptr){ptr->UPDATE();}

//#include <boost/numeric/interval.hpp>
//#include <boost/multiprecision/cpp_dec_float.hpp>

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/detail/default_ops.hpp>
#include <boost/numeric/interval.hpp>
#include <boost/numeric/interval/io.hpp>

//using namespace boost::numeric;
//using namespace boost::numeric::interval_lib;
//using namespace boost::multiprecision;

namespace bn  = boost::numeric;
namespace bni = bn::interval_lib;
namespace bmp = boost::multiprecision;

template <typename T>
using Interval = bn::interval<T, bni::policies<bni::save_state<bni::rounded_transc_exact<T>>, bni::checking_base<T>>>;

//using BigFloat = bmp::cpp_dec_float_100; // bmp::number<bmp::backends::cpp_dec_float<100>, bmp::et_off>;

//static BigFloat bf_pi() { return bmp::default_ops::get_constant_pi<BigFloat::backend_type>(); }

//namespace boost { namespace numeric { namespace interval_lib { namespace constants {
//    template<> inline BigFloat pi_lower<BigFloat>()       { return bf_pi(); }
//    template<> inline BigFloat pi_upper<BigFloat>()       { return bf_pi(); }
//    template<> inline BigFloat pi_twice_lower<BigFloat>() { return bf_pi() * 2; }
//    template<> inline BigFloat pi_twice_upper<BigFloat>() { return bf_pi() * 2; }
//    template<> inline BigFloat pi_half_lower<BigFloat>()  { return bf_pi() / 2; }
//    template<> inline BigFloat pi_half_upper<BigFloat>()  { return bf_pi() / 2; }
//} } } }

///////////////////////////////////////////////////////////////////////////////
OGLWidget::OGLWidget(LMap *ptr_LMap, /*QWidget*/ OGLframe *parent)
    : QOpenGLWidget(parent),
      m_ptr_LMap{ptr_LMap},
      frameOGL(parent),
      painter{std::make_unique<QPainter>()}
{
    painter->setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    setFixedSize(g_default___screen_width, g_default___screen_height);
    setAutoFillBackground(false);
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));
//m_rubberBand =  std::make_unique<QRubberBand>(QRubberBand::Rectangle, this);
//m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    background = QBrush(Qt::white);
    QColor gold("#ffd700");
    Qt::BrushStyle style = Qt::SolidPattern;
    QBrush brush(gold, style);
    circleBrush = brush;//QBrush(QColor(255, 195, 16), Qt::SolidPattern);//QBrush(gradient);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
    m_hack.fn = cb;

    auto ptrLMap_0 =  static_cast<LMap *>(parent->parent());
    auto ptrLMap_1 = qobject_cast<LMap *>(parent->parent());
    if (m_ptr_LMap == nullptr) {
        foreach (QWidget *widget, QApplication::allWidgets()) {
            if (auto p = qobject_cast<LMap *>(widget)) {
                assert(m_ptr_LMap == p);
                break;
            }
        }}
    bool a0{m_ptr_LMap == ptrLMap_0};
    bool a1{m_ptr_LMap == ptrLMap_1};
    if (m_ptr_LMap==nullptr) {
        std::cout << "m_ptr_LMap==nullptr" << std::endl;
        exit(-9);
    }
//Mouse move events will occur only when a mouse button is pressed down,
//unless mouse tracking has been enabled with QWidget::setMouseTracking().
    setMouseTracking(false);
    clear_mousePressEvent_and_QPoints();
}
#if 0
#endif
///////////////////////////////////////////////////////////////////////////////
OGLWidget::~OGLWidget() {
    m_ptr_LMap->close();
}
///////////////////////////////////////////////////////////////////////////////
/// \brief mousePressEvent
/// \param event
///
void OGLWidget::mousePressEvent(QMouseEvent *event){
    Qt::KeyboardModifiers   em = event->modifiers();
    Qt::MouseButton         mb = event->button();// Qt::LeftButton Qt::MiddleButton Qt::RightButton
#if 0
    Qt::MouseButtons       mbs = event->buttons();
    Qt::KeyboardModifiers  kbm = QGuiApplication::keyboardModifiers();
    Qt::KeyboardModifiers qkbm = QApplication::queryKeyboardModifiers();
    auto mbShft   =   mb & Qt::ShiftModifier;
    auto mbsShft  =  mbs & Qt::ShiftModifier;
    auto emShft   =   em & Qt::ShiftModifier;
    auto kbmShft  =  kbm & Qt::ShiftModifier;
    auto qkbmShft = qkbm & Qt::ShiftModifier;
    auto mbCtl   =   mb & Qt::ControlModifier;
    auto mbsCtl  =  mbs & Qt::ControlModifier;
    auto emCtl   =   em & Qt::ControlModifier;
    auto kbmCtl  =  kbm & Qt::ControlModifier;
    auto qkbmCtl = qkbm & Qt::ControlModifier;
#endif

    if(mb == Qt::LeftButton && (em & Qt::ShiftModifier) ) //TRANSLATE
    {
        auto xx = em & Qt::ShiftModifier;
        auto yy = xx;
        QSize size = this->size();
        QRect r{0,0,size.width(),size.height()};
        QPoint p  = ScreenToModel( event->pos() );
        Q_ASSERT(r.contains(p));
        if (    auto onboundary = {
                p.rx()<=static_cast<int>(g_default___screen_col_min),
                p.rx()>=static_cast<int>(g_default___screen_col_max),
                p.ry()<=static_cast<int>(g_default___screen_row_min),
                p.ry()>=static_cast<int>(g_default___screen_row_max)};
                !std::any_of(onboundary.begin(), onboundary.end(),
                             [](const bool& kw) { return true == kw; }))
        {
            //m_ptr_LMap->translate( p,  size );
            //std::cerr << "Token must not be a keyword\n";
        }
        m_ptr_LMap->translate( p,  size );
        clear_mousePressEvent_and_QPoints();
        return;
    }
    if ( mb == Qt::LeftButton && (em & Qt::ControlModifier) ) // record  P.O.I.
    {
        QPoint p  = ScreenToModel( event->pos() );
        std::string s{""};
        if (em & Qt::ShiftModifier) {
            s="";
        }
        else {
            bool ok{false};
            QString text = QInputDialog::getText(this, tr("Description for P.O.I.:"),
                                                 tr("P.O.I.:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty()) {
                s = text.toStdString();
            }
        }
        m_ptr_LMap->set_point_of_interest(p, s);
        clear_mousePressEvent_and_QPoints();
        return;
    }
    if ( mb == Qt::LeftButton ) // set_Rate_to_Play
    {
        QPoint p  = ScreenToModel( event->pos() );
        m_ptr_LMap->set_Rate_to_Play( p );
        clear_mousePressEvent_and_QPoints();
        return;
    }

    if ( mb == Qt::RightButton ) // zoom in
    {
        b_mousePress = true;
        m_mseDn = ScreenToModel( event->pos()  );
        m_mseUp =  QPoint();//Q_NULLPTR;
        m_rubberBand =  std::make_unique<QRubberBand>(QRubberBand::Rectangle /*| Qt::KeepAspectRatio*/, this);
        dragging_QRubberBand = true;
        origin_QRubberBand = event->pos();
      //m_rubberBand->setGeometry(QRect(origin_QRubberBand, QSize()));
        m_rubberBand->setGeometry(QRect(origin_QRubberBand, event->pos()).normalized());
        m_rubberBand->show();
        QRect r0   = m_rubberBand->rect();
        QPoint p02 =  origin_QRubberBand+r0.bottomRight();
//    if (false){
//        //frameOGL->mouseMoveEventQPoint=m_mseDn=m_mseUp=enterEventQPoint=leaveEventEventQPoint = QPoint();

//    }
//    else m_mseDn = ScreenToModel( event->pos()  );
    }

//    switch (mb) {
//    case Qt::RightButton:
//    {
//        //if(em & Qt::ShiftModifier){
//        //return;
//        //}
//        b_mousePress = true;
//        m_mseUp =  QPoint();//Q_NULLPTR;
//        return;
//    }
//    case Qt::MiddleButton:
//        std::cout << "Qt::MiddleButton\n" << std::boolalpha  << (mbs==Qt::MiddleButton)   << std::endl << std::flush;
//        break;
//    default:
//        break;
//    }
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
QPoint OGLWidget::ScreenToModel( QPoint const &pos) const {
    return QPoint( pos.x(), this->size().height() - 1 - pos.y() );
//    int hmenu = m_ptr_LMap->menuBar->height();
//    int htbar = m_ptr_LMap->mainToolBar->height();
    //    return QPoint( pos.x(), this->size().height()/*+hmenu+htbar*/ - 1 - pos.y() );
}

void OGLWidget::clear_mousePressEvent_and_QPoints()
{
        b_mousePress = false;
        frameOGL->clear_mousePressEvent_and_QPoints();
        mouseMoveEventQPoint=m_mseDn=m_mseUp=enterEventQPoint=leaveEventEventQPoint = QPoint();
        m_rubberBand.release();
        m_rubberBand = nullptr;
        dragging_QRubberBand = false;
        origin_QRubberBand = QPoint{};
}
///////////////////////////////////////////////////////////////////////////////
void OGLWidget::DisplayMap()
{
    try {
        Assemble_block ab{};
        connect(&ab, SIGNAL(map(QImage)), this, SLOT(newPixmapFromThreadDraw(QImage)));
        ////    QObject::connect(Assemble_block::ab, SIGNAL(&Assemble_block::map(QImage) ), this, SLOT(&OGLWidget::newPixmapFromThreadDraw(QImage)) );
        std::size_t ret = ab.assemble(m_ptr_LMap->m_color==LMap::COLOR::RedGreenBlue_FromWaveLength);
        disconnect(&ab, SIGNAL(map(QImage)), this, SLOT(newPixmapFromThreadDraw(QImage)));
        disconnect(&ab, nullptr, nullptr, nullptr);
#if 0
#endif
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// \brief OGLWidget::mouseReleaseEvent
/// \param event
///
void OGLWidget::mouseReleaseEvent(QMouseEvent *event){
    m_mseUp = ScreenToModel( event->pos()  );

    Qt::MouseButton        mb  = event->button();// Qt::LeftButton Qt::MiddleButton Qt::RightButton
    Qt::MouseButtons       mbs = event->buttons();
    Qt::KeyboardModifiers   em = event->modifiers();
    Qt::KeyboardModifiers  kbm = QGuiApplication::keyboardModifiers();
    Qt::KeyboardModifiers qkbm = QApplication::queryKeyboardModifiers();
    auto mbShft   =   mb & Qt::ShiftModifier;
    auto mbsShft  =  mbs & Qt::ShiftModifier;
    auto emShft   =   em & Qt::ShiftModifier;
    auto kbmShft  =  kbm & Qt::ShiftModifier;
    auto qkbmShft = qkbm & Qt::ShiftModifier;
    auto mbCtl   =   mb & Qt::ControlModifier;
    auto mbsCtl  =  mbs & Qt::ControlModifier;
    auto emCtl   =   em & Qt::ControlModifier;
    auto kbmCtl  =  kbm & Qt::ControlModifier;
    auto qkbmCtl = qkbm & Qt::ControlModifier;


//QPoint delta = m_mseDn;//scope of all vars must exist throughout 'switch'
    switch (mb) {//scope of all vars must exist throughout 'switch'
    case Qt::RightButton:
        //m_mseUp = ScreenToModel( event->pos()  );

        if (dragging_QRubberBand) {

            QRect rc = QRect{origin_QRubberBand, event->pos()}.normalized();//normalized rectangle=rectangle w/ non-negative width and height.
            QSize sz{g_default___screen_width, g_default___screen_height};
            if (m_ptr_LMap->get_fixedAspectRatio()) {
                sz.scale(rc.size().rwidth(), rc.size().rheight(), Qt::KeepAspectRatio);//shrink width
                //  sz.scale(rc.size().rwidth(), rc.size().rheight(), Qt::KeepAspectRatioByExpanding);//expand height
                rc.setBottomRight(rc.topLeft() + QPoint{sz.rwidth(), sz.rheight()} );
                QPointF point = event->pos() - rc.center();
                //std::arg(std::complex<double>(x,y))
                double theta = std::atan2(-point.y(), point.x() );

                auto Intervals =  std::tuple{Interval<double>(-M_PI, -M_PI/2),Interval<double>(-M_PI/2, 0),Interval<double>(0, M_PI/2),Interval<double>(M_PI/2, M_PI)};
                auto Vertices  =  std::tuple{                 rc.bottomLeft(),            rc.bottomRight(),              rc.topRight(),                  rc.topLeft()};
                auto VERTEXinINTERVAL = [Intervals,Vertices](double const &f){
                    if (auto &e=std::get<0>(Intervals);e.lower() < f && f <= e.upper()) return std::get<0>(Vertices);
                    if (auto &e=std::get<1>(Intervals);e.lower() < f && f <= e.upper()) return std::get<1>(Vertices);
                    if (auto &e=std::get<2>(Intervals);e.lower() < f && f <= e.upper()) return std::get<2>(Vertices);
                    if (auto &e=std::get<3>(Intervals);e.lower() < f && f <= e.upper()) return std::get<3>(Vertices);
                    return std::get<1>(Vertices);//fail-safe
                };
                m_mseUp = QPoint{ VERTEXinINTERVAL(theta).x() , static_cast<int>(g_default___screen_row_max) - VERTEXinINTERVAL(theta).y() };
            }
            m_rubberBand->setGeometry(rc);
            QRect r0 = m_rubberBand->rect();
            m_rubberBand->hide();
            QRect r = m_rubberBand->geometry();
            b_mousePress = false;
            if (emShft) {
                m_ptr_LMap->play_rubberBand_This_Rect(r);//m_rubberBand->rect());
                origin_QRubberBand = QPoint{};
            }
            else {
                //                b_mousePress = false;
                //                m_mseUp =  QPoint();//Q_NULLPTR;
                //                m_mseDn =  QPoint();//Q_NULLPTR;

                //delta -= m_mseUp;
                // THE FOLLOWING WILL NOw COMPILE:
                QPoint delta(m_mseUp.x() - m_mseDn.x(), m_mseUp.y() - m_mseDn.y());// ==  m_mseUp - m_mseDn;
                //"Manhattan length" = sum of the absolute values of x() and y() if (delta.manhattanLength() > 3)
                if ( std::abs(delta.x()) > 1  && std::abs(delta.y()) > 1 ) {
                    setCursor(Qt::BusyCursor);
                    m_ptr_LMap->setCursor(Qt::BusyCursor);
                    m_ptr_LMap->newRegion( m_mseDn, m_mseUp );
                }
            }
            m_rubberBand.release();
            m_rubberBand = nullptr;
            dragging_QRubberBand = false;
            origin_QRubberBand = QPoint{};
            return;
        }


        m_mseUp =  QPoint();//Q_NULLPTR;
        m_mseDn =  QPoint();//Q_NULLPTR;
        clear_mousePressEvent_and_QPoints();
        b_mousePress = false;
        break;
    case Qt::LeftButton:
        m_mseUp =  QPoint();//Q_NULLPTR;
        m_mseDn =  QPoint();//Q_NULLPTR;
        clear_mousePressEvent_and_QPoints();
        b_mousePress = false;
        break;
    case Qt::MiddleButton:
        std::cout << "Qt::MiddleButton\n" << std::boolalpha  << (mbs==Qt::MiddleButton)   << std::endl << std::flush;
        m_mseUp =  QPoint();//Q_NULLPTR;
        m_mseDn =  QPoint();//Q_NULLPTR;
        clear_mousePressEvent_and_QPoints();
        b_mousePress = false;
        break;
    default:
        break;
    }

}
///////////////////////////////////////////////////////////////////////////////
/// \brief OGLWidget::mouseMoveEvent
/// \param event
///
///////////////////////////////////////////////////////////////////////////////
void OGLWidget::mouseMoveEvent(QMouseEvent *event){
    mouseMoveEventQPoint = ScreenToModel( event->pos()  );
    Qt::MouseButton        mb  = event->button();// Qt::LeftButton Qt::MiddleButton Qt::RightButton
    Qt::MouseButtons       mbs = event->buttons();
    Qt::KeyboardModifiers   em = event->modifiers();
    Qt::KeyboardModifiers  kbm = QGuiApplication::keyboardModifiers();
    Qt::KeyboardModifiers qkbm = QApplication::queryKeyboardModifiers();
    auto mbShft   =   mb & Qt::ShiftModifier;
    auto mbsShft  =  mbs & Qt::ShiftModifier;
    auto emShft   =   em & Qt::ShiftModifier;
    auto kbmShft  =  kbm & Qt::ShiftModifier;
    auto qkbmShft = qkbm & Qt::ShiftModifier;
    auto mbCtl   =   mb & Qt::ControlModifier;
    auto mbsCtl  =  mbs & Qt::ControlModifier;
    auto emCtl   =   em & Qt::ControlModifier;
    auto kbmCtl  =  kbm & Qt::ControlModifier;
    auto qkbmCtl = qkbm & Qt::ControlModifier;

    constexpr const char qs_ZOOM[]{"ZOOM"};
    constexpr const char qs_PLAY[] = R"(PLAY)";
    QString ate{};

    if(dragging_QRubberBand) {
        QRect rc = QRect{origin_QRubberBand, event->pos()}.normalized();//normalized rectangle=rectangle w/ non-negative width and height.
        QSize sz{g_default___screen_width, g_default___screen_height};
        if (m_ptr_LMap->get_fixedAspectRatio()) {
            sz.scale(rc.size().rwidth(), rc.size().rheight(), Qt::KeepAspectRatio);//shrink width
            //  sz.scale(rc.size().rwidth(), rc.size().rheight(), Qt::KeepAspectRatioByExpanding);//expand height
            rc.setBottomRight(rc.topLeft() + QPoint{sz.rwidth(), sz.rheight()} );
        }
        m_rubberBand->setGeometry(rc);//QRect(origin_QRubberBand, event->pos()).normalized());
        QToolTip::showText( event->globalPos(), QString("%1,%2,%3")
                            .arg((emShft? qs_PLAY:qs_ZOOM))
                            .arg(m_rubberBand->size().width())
                            .arg(m_rubberBand->size().height()),this );
        //        QToolTip::showText( event->globalPos(), QString("%1,%2")
        //                                                     .arg(m_rubberBand->size().width())
        //                                                     .arg(m_rubberBand->size().height()),this );
        QRect r1 = m_rubberBand->geometry();
        QRect r0 = m_rubberBand->rect();
        Q_ASSERT(r0.bottomRight()==r0.topLeft()+r0.topRight()+r0.bottomLeft());
        Q_ASSERT(r0.topLeft()== QPoint(0,0));
        QPoint r4 =  origin_QRubberBand;
        QPoint r2{r1.center()- r0.center()};// ?== origin_QRubberBand
        QPoint r3{r1.width() - r0.width(), r1.height()-r0.height()};

        QPointF point = event->pos() - m_rubberBand->geometry().center();
        double theta = std::atan2(-point.y(), point.x() ) * 180.0 / M_PI; //std::arg(std::complex<double>(x,y))
        theta = std::atan2(-point.y(), point.x() );

        auto Intervals =  std::tuple{Interval<double>(-M_PI, -M_PI/2),Interval<double>(-M_PI/2, 0),Interval<double>(0, M_PI/2),Interval<double>(M_PI/2, M_PI)};
        auto Vertices  =  std::tuple{                 r1.bottomLeft(),            r1.bottomRight(),              r1.topRight(),                  r1.topLeft()};
        auto VERTEXinINTERVAL = [Intervals,Vertices](double const &f){
            if (auto &e=std::get<0>(Intervals);e.lower() < f && f <= e.upper()) return std::get<0>(Vertices);
            if (auto &e=std::get<1>(Intervals);e.lower() < f && f <= e.upper()) return std::get<1>(Vertices);
            if (auto &e=std::get<2>(Intervals);e.lower() < f && f <= e.upper()) return std::get<2>(Vertices);
            if (auto &e=std::get<3>(Intervals);e.lower() < f && f <= e.upper()) return std::get<3>(Vertices);
            return std::get<1>(Vertices);//fail-safe
        };
        //auto t = VERTEXinINTERVAL(theta);

        //                    auto [I0,I1,I2,I3] =  std::tuple{Interval<double>(-M_PI, -M_PI/2),Interval<double>(-M_PI/2, 0),Interval<double>(0, M_PI/2),Interval<double>(M_PI/2, M_PI)};
        //                    auto [q0,q1,q2,q3] =  std::tuple{                 r0.bottomLeft(),            r0.bottomRight(),              r0.topRight(),                  r0.topLeft()};
        //                    auto duh = Interval<double>(-M_PI, -M_PI/2);
        //                    auto invl = [duh](double const &f)->bool{return duh.lower() < f && f <= duh.upper();};

        //                    auto EP =  std::tuple{Interval<double>(-M_PI, -M_PI/2),Interval<double>(-M_PI/2, 0),Interval<double>(0, M_PI/2),Interval<double>(M_PI/2, M_PI)};
        //                    auto LEP =  std::tuple{-M_PI, -M_PI/2, 0, M_PI/2, M_PI};
        //                    auto intvl = [theta,LEP](double const &f)->int{return 0;};
        //                    auto [R0,R1,R2,R3,R4] =  std::tuple{-M_PI, -M_PI/2, 0, M_PI/2, M_PI};

        //                    auto [p0,p1,p2,p3] =  std::tuple{origin_QRubberBand+r0.bottomRight(),origin_QRubberBand+r0.topRight(),origin_QRubberBand+r0.topLeft(),origin_QRubberBand+r0.bottomLeft()};
        //                    auto Q =  std::tuple{r0.bottomRight(),r0.topRight(),r0.topLeft(),r0.bottomLeft()};
        //                    auto [v0,v1] =  std::tuple{r0.topLeft()-r0.bottomRight(), r0.topRight()-r0.bottomLeft()};

        QString x0, y0, x1, y1, x2, y2, x3, y3;


        QString stheta; stheta.setNum(theta);
        x0.setNum( origin_QRubberBand.x());
        y0.setNum( origin_QRubberBand.y());
        x2.setNum( r2.x());
        y2.setNum( r2.y());

        x3.setNum( VERTEXinINTERVAL(theta).x());
        y3.setNum(  static_cast<int>(g_default___screen_row_max) - VERTEXinINTERVAL(theta).y());

        ate="origin= "+x0+";"+y0+"\nrb.geo.c-rb.rct.c="+x2+";"+y2+"\n"+stheta+"\n"+x3+";"+y3;
    }
    QPoint p = ScreenToModel( event->pos()  );
    Datum const& dum = Data::datum(m_ptr_LMap->m_selected);
    auto [mpf_x , mpf_y] = dum.get_mpf_XY_tuple( p );
            //MPF_Vec_Ptr pv = Data::vec_LogisticMap_Data::get_JSON_Data()->get_mpf_XY( p );
            //MPF_Vec v = *(pv.get());
            mpf_class y_t = mpf_y;
            //*((v[1]).get());//static_cast<std::size_t>(Data::vec_LogisticMap_Data::COORD::Y_MIN_T-Data::vec_LogisticMap_Data::COORD::X_MIN_T)]).get()); //std::get<1>(chosen_range);
            std::stringstream ss;
            //ss  << std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << y_t  << std::flush;
            ss  << std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << mpf_y  << std::flush;
            std::string rs{ss.str()};
    std::string rs2{remove_ws(rs)};
    QString rate{rs2.c_str()};
    QString x; x.setNum( p.x());
    QString y; y.setNum( p.y());
    QString qs{"<html><head/><body><p>Screen Mouse:</p><p>x= " + x + "; y = "+  y + "</p><p>R= " + rate + "</p></body></html>"};
//m_ptr_LMap->onSetText( qs ); employ signal
    qs = "Screen Mouse:\nx= " + x + "; y = "+  y + "\nR= " + rate + "\n" + ate;
    emit set_mouse_Text( qs );
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//void OGLWidget::keyPressEvent(QKeyEvent *event){
//    if (event->key() && Qt::Key_Escape) {
//        b_mousePress = false;
//    }
////    if (b_mousePress) {
////        b_mousePress = false;
////    }
////    switch (event->key()) {
////    case Qt::Key_Plus:
////        //reCalculateMap(ZoomInFactor);
////        break;
////    case Qt::Key_Minus:
////        //reCalculateMap(ZoomOutFactor);
////        break;
////    case Qt::Key_Left:
////        //scroll(-ScrollStep, 0);
////        break;
////    case Qt::Key_Right:
////        //scroll(+ScrollStep, 0);
////        break;
////    case Qt::Key_Down:
////        //scroll(0, -ScrollStep);
////        break;
////    case Qt::Key_Up:
////        //scroll(0, +ScrollStep);
////        break;
////    default:
////        QWidget::keyPressEvent(event);
////    }
//}
////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//void OGLWidget::wheelEvent( QWheelEvent *wheelEvent )
//{
//    if( wheelEvent->modifiers() & Qt::ShiftModifier )
//    {
//    // do something awesome
//    }
//    else if( wheelEvent->modifiers() & Qt::ControlModifier )
//    {
//    // do something even awesomer!
//    }
//}
///////////////////////////////////////////////////////////////////////////////
#if 0
http://doc.qt.io/qt-5/implicit-sharing.html

The classes listed below automatically detach from common data if an object is about to be changed.
"The programmer will not even notice that the objects are shared."
Thus you should treat separate instances of them as separate objects.
They will always behave as separate objects
... QByteArray ... QImage

auto dest = const_cast<void*>( (const void *) ( ( (const char *)dotstr.buffer ) + m_id * nrows * g_default___screen_width * sizeof(data_t::value_type) ) );

if ( m_id == (num_THREADS - 1) ) {
    std::memcpy(dest, src, (g_default___screen_height - m_id * nrows ) * g_default___screen_width * sizeof(data_t::value_type)  );//g_default___screen_width * sizeof(data_t::value_type));
}
else {
std::memcpy(dest, src, nrows * g_default___screen_width * sizeof(data_t::value_type)  );// * g_default___screen_width * sizeof(data_t::value_type));
}

#endif
///////////////////////////////////////////////////////////////////////////////
void OGLWidget::newPixmapFromThreadDraw(const QImage &image) {
    if (!pixmap.isNull()) {
        pixmap.fill(Qt::white);
        //pixmap.fill(Qt::black);
        pixmap.detach();
    }
//pixmap.sharedPainter() = nullptr;
    pixmap = QPixmap::fromImage(image);
    if (!pixmap.isNull()) {
        update();//crash = repaint()
    }
}
///////////////////////////////////////////////////////////////////////////////
void OGLWidget::paintEvent(QPaintEvent *  event ) {
    setCursor(Qt::CrossCursor);
    m_ptr_LMap->setCursor(Qt::CrossCursor);
    QPainter _painter{this};// = *painter.get();
    _painter.begin(this);
    _painter.fillRect(this->rect(), background);//, Qt::white);
    if (pixmap.isNull()) {
        _painter.setPen(Qt::red);
        _painter.drawText(rect(), Qt::AlignCenter, tr("Rendering initial image, please wait..."));
        std::cout << "OGLWidget::paintEvent pixmap.isNull pixmap == nullptr" << std::endl;
        return;
    }
    auto rect_0 = rect();// 960x600+0+0
    auto rect_1 = event->rect();
    bool r{rect_0==rect_1};
//    _painter.begin(this);
//    _painter.fillRect(this->rect(), Qt::white);
//    //_painter.drawPixmap(QPoint(0,0), pixmap);

//    background = QBrush(Qt::white);
//    _painter.fillRect(rect(), background);
    _painter.drawPixmap(this->rect(), this->pixmap );

    if (m_hack.goldenHACK) {
        //QMutexLocker locker(&playRows_Worker::playRows_Worker_mutex);
        _painter.save();
        _painter.setPen(Qt::NoPen);
        _painter.setBrush(circleBrush);
        qreal w = 8;
        _painter.drawEllipse(QRectF(m_hack.p.x(), 600-w-m_hack.p.y(), w * 2, w * 2));
        if (m_hack.prev != QPoint{})
            _painter.drawEllipse(QRectF(m_hack.prev.x(), 600-w-m_hack.prev.y(), w * 2, w * 2));
        _painter.restore();
        m_hack.goldenHACK = false;
    }

    _painter.end();

#if 0
    QPainter p(this);
    QPixmap img("e://img.png");
    p.drawPixmap(QRect(50, 0, 50, 50), img);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.drawPixmap(QRect(0, 0, 50, 50), img);
    img = img.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    p.drawPixmap(100, 0, img);
    QString text = tr("Use mouse wheel or the '+' and '-' keys to reCalculateMap. "
                      "Press and hold left mouse button to scroll.");
    QFontMetrics metrics = painter.fontMetrics();
    int textWidth = metrics.horizontalAdvance(text);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 127));
    painter.drawRect((width() - textWidth) / 2 - 5, 0, height() - (textWidth + 10), metrics.lineSpacing() + 5);
    painter.setPen(Qt::white);
    painter.drawText((width() - textWidth) / 2, height() - (metrics.leading() + metrics.ascent()), text);
#endif

}

///////////////////////////////////////////////////////////////////////////////
//void OGLWidget::keyPressEvent(QKeyEvent *event){
//    if (event->key() && Qt::Key_Escape) {
//        b_mousePress = false;
//    }
////    if (b_mousePress) {
////        b_mousePress = false;
////    }
////    switch (event->key()) {
////    case Qt::Key_Plus:
////        //reCalculateMap(ZoomInFactor);
////        break;
////    case Qt::Key_Minus:
////        //reCalculateMap(ZoomOutFactor);
////        break;
////    case Qt::Key_Left:
////        //scroll(-ScrollStep, 0);
////        break;
////    case Qt::Key_Right:
////        //scroll(+ScrollStep, 0);
////        break;
////    case Qt::Key_Down:
////        //scroll(0, -ScrollStep);
////        break;
////    case Qt::Key_Up:
////        //scroll(0, +ScrollStep);
////        break;
////    default:
////        QWidget::keyPressEvent(event);
////    }
//}
////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void OGLWidget::draw(QPoint const &prev, QPoint const &p)
{
    m_hack.goldenHACK=true;
    m_hack.prev = prev;
    m_hack.p = p;
    return;
    painter->save();
    painter->setBrush(circleBrush);
    qreal radius = 21.0;
    qreal circleRadius = 21;
    painter->drawEllipse(QRectF(radius, -circleRadius,
                                circleRadius * 2, circleRadius * 2));
    painter->restore();
}
///////////////////////////////////////////////////////////////////////////////
void OGLWidget::draw(QPoint const &p)
{
    m_hack.goldenHACK=true;
    m_hack.prev = QPoint{};
    m_hack.p = p;
    {
        //QMutexLocker locker(&playRows_Worker::playRows_Worker_mutex);
        //update();
    }
    return;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(circleBrush);
    qreal radius = 21.0;
    qreal circleRadius = 121;
    painter->drawEllipse(QRectF(p.x(), p.y(),
                                circleRadius * 2, circleRadius * 2));
    painter->restore();
}

///////////////////////////////////////////////////////////////////////////////
#if 0
#endif
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void OGLWidget::enterEvent(QEvent *event) {
    enterEventQPoint = /*ScreenToModel*/( frameOGL->mouseMoveEventQPoint  );
}
///////////////////////////////////////////////////////////////////////////////
void OGLWidget::leaveEvent(QEvent *event) {
    leaveEventEventQPoint = mouseMoveEventQPoint/*ScreenToModel( frameOGL->mouseMoveEventQPoint  )*/;
}
///////////////////////////////////////////////////////////////////////////////
