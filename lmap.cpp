#include "lmap.h"
#include "dialogForRATE.h"
#include "src/worker_thread.h"
#include "src/data.h"
#include "src/assemble_block.h"
#include "src/playRows.h"
#include "src/play_music_root.h"
#include "src/generateTemplate.h"
#include "src/rate_label.h"
#include "src/colormap.h"
#include "src/notes.h"

#include "nlohmann/json.hpp"
#include "png/PngWriter.hpp"
#include "QJsonModel/qjsontreeview.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
//#include <QSoundEffect>

#include <cstring>
#include <filesystem>
#include <ctime>
#include <locale>
#include <regex>
#include <iterator>

///////////////////////////////////////////////////////////////////////////////

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

QWaitCondition LMap::t1_condv;


LMap::LMap(const char* argv1, QWidget *parent) :
    QMainWindow(parent)/*,*/
//    m_sptr_Play_Music_ROOT{ std::make_shared<Play_Music_ROOT>(this) },
//    m_ptr_Play_Music_ROOT{m_sptr_Play_Music_ROOT.get()}
{
    setWindowTitle("LM History");
    setAttribute(Qt::WidgetAttribute::WA_QuitOnClose, true);
    auto flags = windowFlags();
    setWindowFlags( windowFlags() | Qt::CustomizeWindowHint);
    setWindowFlags( windowFlags() & Qt::WindowCloseButtonHint);
    setupUi(this);
#if 0
QPoint globalCursorPos = QCursor::pos();
int mouseScreen = qApp->desktop()->screenNumber(globalCursorPos);
Now you know which screen the cursor is in. Then you could find the cursor position within that screen doing this:

QRect mouseScreenGeometry = qApp->desktop()->screen(mouseScreen)->geometry();
QPoint localCursorPos = globalCursorPos - mouseScreenGeometry.topLeft();
#endif

///////////////////////////////////////////////////////////////////////////////
    InitializeConnections();

foreach (QWidget *widget, QApplication::allWidgets()) {
    if (auto mainWindow = qobject_cast<QJsonTreeView *>(widget)) {
        ptr_QJsonTreeView = mainWindow;
    }
}
if (ptr_QJsonTreeView==nullptr) {
    std::cout << "ptr_QJsonTreeView==nullptr" << std::endl;
    exit(-9);
}

    get_uniqueFilename();
    if (argv1 == nullptr) {
        InitializeMpfRect( );
    }
    else {
        {
            QString fileName{argv1};
            QFile ifile(fileName);
            bool success = false;
            if (ifile.open(QIODevice::ReadOnly)) {
                ifile.close();
                QFile ofile(uniqueFilename);
                success = QFile::copy(fileName, uniqueFilename);
            }
            if (success && ptr_QJsonTreeView != nullptr) {
                ptr_QJsonTreeView->load();
                ptr_QJsonTreeView->update();
                ptr_QJsonTreeView->show();
            }
        }
        std::ifstream i(argv1);
        if (i.is_open()) {
        nlohmann::json j;
        i >> j;
        for (auto &e : j) {
//std::array< std::string const , 5> s5 = {e["x_min"], e["y_min"], e["x_max"], e["y_max"], e["D"]};
m_selected = Data::add_datum(
            e["x_min"].get<std::string>(), e["y_min"].get<std::string>(),
            e["x_max"].get<std::string>(), e["y_max"].get<std::string>(),
            e["D"].get<std::string>(),
            std::stod ( e["n"].get<std::string>()),
            static_cast<std::uint32_t>( std::stoi ( e["N_base"].get<std::string>() ) )
        );
        }
        std::ofstream o("pretty.json");
        o << std::setw(4) << j << std::endl;
        }
 }


    ptr_QJsonTreeView->setCPU(this);
    ptr_QJsonTreeView->setFilename(uniqueFilename);
    setCursor(Qt::CrossCursor);
    checkBox_auto_save->setCheckState(Qt::Unchecked);
    playROWS_ON();

//    fr_Music->setStyleSheet(QString{Music_buttonstyle});
//    fr_Music->show();
//    fr_Music->update();
//    fr_Music->setStyleSheet(QString{Music_buttonstyle});
//    fr_Music->update();
//    fr_Music->show();

    QRgb row_y = get_chaos_threshold_rate_get_screen_Row_y();
    row_y = get_chaos_threshold_rate_get_screen_Row_y();
    setFROM(row_y);
    setFROM(row_y);
    setTO(get_FROM()+2);
    setTO(get_FROM()+2);
    pb_from->setText(std::to_string(row_y).c_str());
    pb_to->setText(std::to_string(row_y+2).c_str());
    pb_from->update();
    pb_to->update();
    setCursor(Qt::CrossCursor);

//not used ->
#if 0
    lbl_rate->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextEditable);
    lbl_rate->setUpdatesEnabled(true);
    lbl_rate->setVisible(false);
    lbl_rate->setHidden(true);
    plainTextEdit_rate->setUpdatesEnabled(true);
    plainTextEdit_rate->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextEditable);
    plainTextEdit_rate->setVisible(false);
    plainTextEdit_rate->setHidden(true);
#endif
// <- not used
    rb_playRate->setChecked(m_b_playRate);
    rb_playRate->setChecked(!m_b_playRate);

    //pb_Rate_Goto->setStyleSheet("text-align:left");
    pb_Rate_Goto->setText(tr("%1").arg( g_demo_Rate ) );
    lineEdit_Rate_Play->setText(tr("%1").arg( g_demo_Rate ) );
    pb_playMusic->setFocusPolicy(Qt::StrongFocus);
    pb_Rate_Goto->setFocusPolicy(Qt::StrongFocus);
    lineEdit_Rate_Play->setFocusPolicy(Qt::StrongFocus);
    pb_playMusic->setContextMenuPolicy(Qt::DefaultContextMenu);

    fr_Music->setStyleSheet(QString{Music_buttonstyle});
    groupBox_Options->setStyleSheet(QString{groupBox_Options_buttonstyle});
    pb_re_compute->setStyleSheet(QString{pb_re_compute_buttonstyle});
//lineEdit_Rate_Play->setStyleSheet(QString{pb_Rate_Play_buttonstyle});
    pb_playMusic->setStyleSheet(QString{pb_playROWS_buttonstyle});
    pb_Rate_Goto->setStyleSheet(QString{pb_Rate_Goto_buttonstyle});


    fr_Music->show();
    fr_Music->update();
    pb_playMusic->update();
    pb_Rate_Goto->update();
    lineEdit_Rate_Play->update();
///////////////////////////////////////////////////////////////////////////////
    ReleaseMouse();
    updateLabels();
    compute();
    //compute_map_threadCaller();
}
///////////////////////////////////////////////////////////////////////////////
void LMap::close() {
    if (ptr_QJsonTreeView != nullptr) {
    ptr_QJsonTreeView->close();
    ptr_QJsonTreeView = nullptr;
    }
}
LMap::~LMap()
{
}
///////////////////////////////////////////////////////////////////////////////
void LMap::closeEvent (QCloseEvent *event) {
    QJsonTreeView *ptr_CHistoryTree{nullptr};
    foreach (QWidget *widget, QApplication::allWidgets()) {
        if (auto mainWindow = qobject_cast<QJsonTreeView *>(widget)) {
            ptr_CHistoryTree = mainWindow;
        }
    }
    if (ptr_CHistoryTree==nullptr) {
        std::cout << "ptr_QJsonTreeView==nullptr" << std::endl;
        exit(-9);
    }
    ptr_CHistoryTree->close();
    event->accept();
}
///////////////////////////////////////////////////////////////////////////////
void LMap::InitializeMpfRect( ) {
    m_selected = Data::add_datum("0.0","2.9","1.0","4.0","1.0", g_default___point_density_exponent_d, 1000);
    record_history();
}
///////////////////////////////////////////////////////////////////////////////
void LMap::onSet_mouse_Text( QString const &mouse_xy ){
    mousePOSITION->setText( mouse_xy );
    mousePOSITION->setWordWrap(true);
    mousePOSITION->update();
}
///////////////////////////////////////////////////////////////////////////////
void LMap::translate( QPoint const &pos, QSize const &size ) {
    QRect r{0,0,size.width(),size.height()};
    Q_ASSERT(r.contains(pos));
    //RenderThread::mutex.lock();
    m_selected = Data::translate_mpf_XY( m_selected, pos );
    record_history();
    updateLabels();
    compute();
}
#if 0
#endif
///////////////////////////////////////////////////////////////////////////////
void LMap::InitializeConnections() {
//    QObject::connect(this, &LMap::play_rows, this, &LMap::initialize_play_connections );
    connect(this, SIGNAL(map(QImage)), openGLWidget, SLOT(newPixmapFromThreadDraw(QImage)));
    connect(this, SIGNAL(updateAfterRenderedImage(void)), this, SLOT(updateAfterRenderedImage(void)));
    connect(openGLWidget, SIGNAL(set_point_of_interest( QPoint, std::string)),
            this, SLOT(set_point_of_interest( QPoint, std::string) ) );
    connect(openGLWidget, SIGNAL(translate( QPoint, QSize)), this, SLOT(translate( QPoint, QSize) ) );
    connect(openGLWidget, SIGNAL(compute( QSize)),           this, SLOT(compute( QSize) ) );
    connect(horizontalSlider_ms, SIGNAL(valueChanged(int)), this, SLOT(on_Set_ms_Value(int)));
    QObject::connect( horizontalSlider_ms,  &QSlider::valueChanged, this, &LMap::on_Set_ms_Value );
    QObject::connect(this, &LMap::qs_rate,      this, &LMap::pb_Rate_Goto_setText);
    QObject::connect( pb_Rate_Goto ,    &QAbstractButton::clicked, this, &LMap::on__Clicked );
//    QObject::connect( lineEdit_Rate_Play ,    &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( pb_cancel ,       &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( pb_num_notes ,    &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( pb_playMusic ,     &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( pb_from ,         &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( pb_to ,           &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( pb_re_compute ,   &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( pb_abort ,        &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( pb_numThreads ,   &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( pb_n_base ,       &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( pb_n_exponent ,   &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( blackWhiteRadio , &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( colorRadio ,      &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( rb_playRate ,      &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( rb_playRows ,      &QAbstractButton::clicked, this, &LMap::on__Clicked );
    QObject::connect( fixedAspectRatio, &QAbstractButton::clicked, this, &LMap::on__Clicked );

    //QObject::connect(openGLWidget,SIGNAL(set_mouse_Text( QString )), this, SLOT(onSet_mouse_Text( QString )));



    connect(openGLWidget,SIGNAL(set_mouse_Text( QString )), this, SLOT(onSet_mouse_Text( QString )));
    connect(frameOGL,SIGNAL(set_mouse_Text( QString )), this, SLOT(onSet_mouse_Text( QString )));


    //QObject::connect(openGLWidget,SIGNAL(setText( QString )), this, SLOT(setText( QString )));
#if 0
    connect(this, SIGNAL( sig_cpr(std::shared_ptr<int> spi) ),
            &cpr, SLOT( on_Sig_cpr(std::shared_ptr<int> spi) ));
    QObject::connect(this, &LMap::sig_cpr, &cpr, &cancel_play_rows::on_Sig_cpr );
    connect(this, SIGNAL( sig_playRows(LogisticMap_Data_Structure_Ptr pv, QRgb Data::vec_LogisticMap_Data::num_iterations_base(), double increase_sample_size_by,
                       QRgb begin, QRgb end, QRgb num_notes, std::shared_ptr<int> ppr) ),
        &pr, SLOT( on_Sig_playRows(LogisticMap_Data_Structure_Ptr pv, QRgb Data::vec_LogisticMap_Data::num_iterations_base(), double increase_sample_size_by,
                    QRgb begin, QRgb end, QRgb num_notes, std::shared_ptr<int> ppr) ));
    QObject::connect(this, &LMap::sig_playRows, &pr, &playRows::on_Sig_playRows );
    connect(&pr, SIGNAL(rate(std::shared_ptr<std::string const>)), this, SLOT(onRate(std::shared_ptr<std::string const>)));

#endif
#if 0
http:
  Automatic Connections
The signals and slots connections defined for compile time or run time forms can either be set up manually or automatically,
using QMetaObject\'s ability to make connections between signals and suitably-named slots.
    menuUI = ui->menuLogisticMap;
    action_save = new QAction(QIcon(":/rm.png"), tr("&Save..."), menuUI);
    action_save->setShortcuts(QKeySequence::Save);
    action_save->setStatusTip(tr("Save history"));
    menuBar->addAction(action_save);
    menu = new QMenu(this);
    act = new QAction("Save", menu);
    menu->addAction(act);
    connect(act, SIGNAL(triggered()), this, SLOT(on_actionSave_triggered()));
    menuBar->addMenu(menu)->setText("Help");
#endif
}
///////////////////////////////////////////////////////////////////////////////
/// \brief LMap::on__Clicked
///
void LMap::on__Clicked()
{
    QObject *p = sender();
    auto pbtn = qobject_cast<QPushButton *>(p);
    auto rbtn = qobject_cast<QRadioButton *>(p);
    auto cbox = qobject_cast<QCheckBox *>(p);

    if ( pbtn != nullptr ) {
        if (!pbtn->isEnabled()) return;
        if ( pbtn == pb_abort ) {
            ReleaseMouse();
            openGLWidget->setCursor(Qt::CrossCursor);
            setCursor(Qt::CrossCursor);
            abort();// sets spi = 0; calls abort_OFF();
        }
        else if ( pbtn == pb_cancel ) {
            ReleaseMouse();
            b_playingMusic = false;
            //playROWS_ON();
            abort();// sets spi = 0; calls abort_OFF();
            /*m_sptr_Play_Music_ROOT->*/spi = 0;//nullptr;
            LMap::t1_condv.wakeAll();
            openGLWidget->setCursor(Qt::CrossCursor);
            setCursor(Qt::CrossCursor);
        }
        else if ( pbtn == pb_playMusic ) {
            ReleaseMouse();
            if (b_playingMusic) return;
            b_playingMusic = true;
            abort_ON();// calls playROWS_OFF();
            music_threadCaller( m_b_playRate );
            return;
        }
        else if ( pbtn == pb_Rate_Goto ) {
            if (b_playingMusic) {
                spi = 0;
                LMap::t1_condv.wakeAll();
                ReleaseMouse();
                b_playingMusic = false;
                openGLWidget->setCursor(Qt::CrossCursor);
                setCursor(Qt::CrossCursor);
            }
            try {
                abort_ON();// calls playROWS_OFF();
                gotoThisRate();
            }
            catch (std::invalid_argument const& iaex) {
                std::cout << "LMap::gotoThisRate: abort " << iaex.what()  << std::endl;
                return;
            }
            catch(const std::exception& e) {
                std::cout << e.what() << '\n';
                return;
            }
            catch (...) {
                return;
            }
            ReleaseMouse();
            abort_OFF();
        }
        else if ( pbtn == pb_from ) {ReleaseMouse();setIntegerFROM();}
        else if ( pbtn == pb_to ) {ReleaseMouse();setIntegerTO();}
        else if ( pbtn == pb_num_notes ){ReleaseMouse();setIntegerNUM_NOTES();}
        else if ( pbtn == pb_n_base ) {ReleaseMouse();setIntegerITERATION_NUM();}
        else if (pbtn == pb_n_exponent) {ReleaseMouse();setDouble_relativeDensity_exponent();}
        else if (pbtn == pb_numThreads) {ReleaseMouse();setIntegerNumThreads();}
        else if ( pbtn == pb_re_compute ) { compute(); }
        return;
    }
    if ( rbtn != nullptr ) {
        if (!rbtn->isEnabled()) return;
        ReleaseMouse();
        if ( rbtn == blackWhiteRadio ) {newColor( static_cast<int>(COLOR::BlackAndWhite) );}
        else if (rbtn == colorRadio) {newColor( static_cast<int>(COLOR::RedGreenBlue_FromWaveLength) );}
        else if (rbtn == rb_playRate ) {
            m_b_playRate = true;
        }
        else if (rbtn == rb_playRows ) {
            m_b_playRate = false;
        }
        return;
    }
    if ( cbox != nullptr ) {
        if (!cbox->isEnabled()) return;
        ReleaseMouse();
        if ( cbox == fixedAspectRatio ) {set_fixedAspectRatio( fixedAspectRatio->isChecked() );}
        return;
    }
}
///////////////////////////////////////////////////////////////////////////////
//mpf_class
std::string LMap::get_dialog_Play_Rate_mpf(/*bool b_Rate_Play*/) {
    QString qs{pb_Rate_Goto->text()};
//    if (b_Rate_Play) {
//        qs = lineEdit_Rate_Play->text();
//    } else {
//        qs = pb_Rate_Goto->text();
//    }
    auto a11 = qs.isEmpty();
    auto a12 = qs.length();
    auto a13 = qs.size();
    auto a14 = qs.toLatin1();
    auto a15 = qs.toUtf8();
    auto a16 = qs.toLocal8Bit();
    auto a17 = qs.toStdString();
    if (qs.isEmpty())  {
        throw std::invalid_argument("TRANSACTION CANCELLED.");
    }
//    const std::string t{qs.toStdString()};
//    //std::string t = do_replace(s);
//    if (t.empty())  {
//        throw std::invalid_argument("TRANSACTION CANCELLED.");
//    }
//    QString q{t.c_str()};
    DialogForRATE dialog;
//    DialogForRATE qid{this};
//    QAutoPointer<DialogForRATE> dialog(new DialogForRATE(this));
    dialog.setTextValue(qs);
    dialog.setWindowTitle("Center screen on:");
    if (dialog.exec() != QDialog::Accepted) {
        throw std::invalid_argument("TRANSACTION CANCELLED.");
        //return mpf_class{};
    }
    const QString d = dialog.rate_qstring();
    auto a21 = d.isEmpty();
    auto a22 = d.length();
    auto a23 = d.size();
    auto a24 = d.toLatin1();
    auto a25 = d.toUtf8();
    auto a26 = d.toLocal8Bit();
    auto a27 = d.toStdString();
    if (a21) {
        throw std::invalid_argument("    dialog.rate_qstring().isEmpty() .");
    }

    emit qs_rate(d);

    const std::string rate_s{d.toStdString()};
    auto a31 = rate_s.empty();
    auto a32 = rate_s.length();
    auto a33 = rate_s.size();
    auto a34 = rate_s.c_str();
    auto a35 = sizeof(a34);
    auto a36 = strlen(a34);
    return rate_s;

//    pb_Rate_Goto->setText(QString("%1").arg(d));
//    pb_Rate_Goto->update();
//    lineEdit_Rate_Play->setText(QString("%1").arg(d));
//    lineEdit_Rate_Play->update();

//    pb_Rate_Goto->setText(QString("%1").arg(d));
//    pb_Rate_Goto->update();
////    pb_Rate_Goto->updateGeometry();
//    lineEdit_Rate_Play->setText(QString("%1").arg(d));
//    lineEdit_Rate_Play->update();
////    lineEdit_Rate_Play->updateGeometry();
//    return rate_s;

//    char copy[1024];
//    //if (strlcpy(copy, a34, a36) >= a36) return -1;
//    std::strncpy((char*)copy, (const char *)a34, a36);
//    /* add a final null terminator */
//    copy[a36] = 0;
//    auto a37 = sizeof(copy);
//    auto a38 = strlen((char*)copy);

//    auto b4 = a24 == a34;
//    auto b5 = a25 == a34;
//    auto b6 = a26 == a34;
//    auto b7 = a27 == rate_s;

//    if (a31) {
//        throw std::invalid_argument("TRANSACTION CANCELLED.");
//    }
//    if (a35==0||a35==1) {
//        throw std::invalid_argument("TRANSACTION CANCELLED.");
//    }
//    //return mpf_class{lineEdit_Rate_Play->text().toStdString().c_str(), NS_LogisticMap::prec, 10};
//    mpf_class rate((const char *)copy, NS_LogisticMap::prec, 10);
//    return rate;
}
///////////////////////////////////////////////////////////////////////////////
void LMap::playThisRate(void) {
    bool ok{false};
    DialogForRATE qid{this};
    //QAutoPointer<DialogForRATE> dialog(new DialogForRATE(this));
    QString qs = lineEdit_Rate_Play->text();
    std::string s{qs.toStdString()};
    std::string t = do_replace(s);
    QString q{t.c_str()};
    qid.setTextValue(q);
    QString d = qid.getDialogText(this, q, &ok);
    if (ok) {
        std::string t{d.toStdString()};
        mpf_class rate(t.c_str(), NS_LogisticMap::prec, 10);
        QRgb row_y = get_screen_Row_y(rate);
        setFROM(row_y);
        setTO(row_y+2);
        pb_from->setText(tr("%1").arg( get_FROM() ));
        pb_from->update();
        pb_to->setText(tr("%1").arg( get_TO() ));
        pb_to->update();
        lineEdit_Rate_Play->setText(QString("%1").arg(d));
        lineEdit_Rate_Play->update();
        ReleaseMouse();
        //playThisRate(r);
        //spR->worker->do_playThisRate(m_selected);//on_playThisRate();
    }
    else {
        b_playingMusic = false;
        pb_cancel->setVisible(false);
        pb_cancel->setHidden(true);
        ReleaseMouse();
        pb_playMusic->show();
        lineEdit_Rate_Play->show();
        openGLWidget->setCursor(Qt::CrossCursor);
        setCursor(Qt::CrossCursor);
    }
}
///////////////////////////////////////////////////////////////////////////////
void LMap::setIntegerNumThreads() {
    bool ok{false};
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"), tr("reCalculateMap:"), get_num_THREADS(), 1, 32, 1, &ok);
    if (ok) {
        setIntegerNumThreads(static_cast<QRgb>( i ) );
        pb_numThreads->setText(tr("%1").arg(i));
        pb_numThreads->update();
        updateLabels();
    }
}
///////////////////////////////////////////////////////////////////////////////
void LMap::setIntegerITERATION_NUM() {
    bool ok{false};
    QRgb ni = get_num_iterations_base();
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"), tr("reCalculateMap:"), ni, 1, 999999, 100, &ok);
    if (ok) {
        setIntegerITERATION_NUM(static_cast<QRgb>( i ));
        pb_n_base->setText(tr("%1").arg(i));
        n_total->setText(qs_n_total.setNum(get_num_iterations()));
        n_total->update();
        pb_n_base->update();
        updateLabels();
    }
}
///////////////////////////////////////////////////////////////////////////////
void LMap::setDouble_relativeDensity_exponent(double f) {
    if (f>=g_default___min__relativeDensity_exponent && f<=g_default___max__relativeDensity_exponent) {
        Datum::datum_cache_parameter_changes.point_density_exponent_ref() = f;
    }
}
///////////////////////////////////////////////////////////////////////////////
void LMap::setDouble_relativeDensity_exponent() {
    bool ok{false};
    QInputDialog qid{this};
    double min{g_default___min__relativeDensity_exponent};
    double max{g_default___max__relativeDensity_exponent};
    int decimals{6};
    double step{g_default___point_density_exponent_d};

    std::ostringstream oss;
    oss  << "[" << min << "<=n<=" << max << "]n = " << std::ends;
    std::string s0= oss.str();

    Qt::WindowFlags flags = windowFlags();
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint| Qt::WindowMinMaxButtonsHint;
    flags = flags & (~helpFlag);
    double d = qid.getDouble(this, tr("(base*d)^n"), tr(s0.c_str()), get_relativeDensity_exponent(), min, max, decimals, &ok, flags, step);
    if (ok) {
        setDouble_relativeDensity_exponent(d);
        pb_n_exponent->setText(QString("%1").arg(d));
        n_total->setText(qs_n_total.setNum(get_num_iterations()));
        n_total->update();
        pb_n_exponent->update();
        sampleIncrease->update();
        sampleIncrease->setText(qs_n_total.setNum(get_increase_sample_size_by()));
        updateLabels();
    }
}
///////////////////////////////////////////////////////////////////////////////
void LMap::setIntegerFROM() {
    bool ok{false};
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"), tr("Starting ROW:"), get_FROM(), 0, 599, 1, &ok);
    if (ok) {
        setFROM(static_cast<QRgb>( i ));
        pb_from->setText(tr("%1").arg(i));
        pb_from->update();
        //plainTextEdit_rate->setPlainText(get_rate_QString( static_cast<QRgb >(i), true));
        //plainTextEdit_rate->update();
        updateLabels();
    }
}
void LMap::setIntegerTO() {
    bool ok{false};
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"), tr("Last ROW:"), get_TO(), get_FROM(), 599, 1, &ok);
    if (ok) {
        setTO(static_cast<QRgb>( i ));
        pb_to->setText(tr("%1").arg(i));
        pb_to->update();
        updateLabels();
    }
}
void LMap::setIntegerNUM_NOTES() {
    bool ok{false};
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"), tr("Last ROW:"), get_NUM_NOTES(), 1, 99999, 1, &ok);
    if (ok) {
        setNUM_NOTES(static_cast<QRgb>( i ));
        pb_num_notes->setText(tr("%1").arg(i));
        pb_num_notes->update();
        updateLabels();
    }
}
void LMap::updateAfterRenderedImage() {
    QString qs;
    pb_numThreads->setText( qs.setNum( get_num_THREADS()));
    pb_n_base->setText( qs.setNum( get_num_iterations_base()) );
    n_total->setText(qs.setNum(get_num_iterations()));
    pb_n_exponent->setText(qs.setNum(get_relativeDensity_exponent()));
    relativePointDensity->setText(qs.setNum(get_relativeDensity()));
    sampleIncrease->setText(qs.setNum(get_increase_sample_size_by()));
    pb_numThreads->update();
    pb_n_base->update();
    n_total->update();
    pb_n_exponent->update();
    relativePointDensity->update();
    sampleIncrease->update();
    updateLabels();
}
#if 0
#endif
std::string LMap::get_rate_string( QRgb row_y, bool prefix) const {
    mpf_class rate_t = get_y_mpf(row_y);
    std::stringstream ss;
    ss.flush(); ss.clear();
    if (prefix)
    ss << "R="<< std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << rate_t << std::flush;
    else
        ss << std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << rate_t << std::flush;
std::string rs{ss.str()};
std::string rs2{remove_ws(rs)};
    return rs2;
}
QString LMap::get_rate_QString( QRgb row_y, bool prefix) const {
    std::string s = get_rate_string(row_y, prefix);
    QString qs{s.c_str()};
    return qs;
}
void LMap::updateLabels() {
// row at half-height [arbitrary choice]
    QSize map_sz = openGLWidget->size();
    QRgb row_y = static_cast<QRgb >(-1+map_sz.height()/2);//299
//    setFROM(row_y-1);//298
//    setTO  (get_FROM()+2);//300

    pb_from->setText(std::to_string(get_FROM()).c_str());//row_y
    pb_to  ->setText(std::to_string(get_TO  ()).c_str());//row_y+2
    pb_from->update();
    pb_to  ->update();

    //plainTextEdit_rate->setPlainText(get_rate_QString( get_FROM(), true));
    //plainTextEdit_rate->update();
    pb_numThreads->setText(tr("%1").arg(get_num_THREADS()) );
    pb_n_base->setText(tr("%1").arg(get_num_iterations_base()) );
    pb_n_exponent->setText(tr("%1").arg(get_relativeDensity_exponent()) );
    relativePointDensity->setText(tr("%1").arg(get_relativeDensity()) );
    sampleIncrease->setText(tr("%1").arg(get_increase_sample_size_by()) );
    n_total->setText(tr("%1").arg(get_num_iterations()) );
    pb_n_base->update();
    pb_n_exponent->update();
    n_total->update();
    relativePointDensity->update();
    sampleIncrease->update();
}
///////////////////////////////////////////////////////////////////////////////
#if 0
void LMap::closeEvent (QCloseEvent *event) {
    QJsonTreeView *ptr_CHistoryTree{nullptr};
    foreach (QWidget *widget, QApplication::allWidgets()) {
        if (auto mainWindow = qobject_cast<QJsonTreeView *>(widget)) {
            ptr_CHistoryTree = mainWindow;
        }
    }
    if (ptr_CHistoryTree==nullptr) {
        std::cout << "ptr_QJsonTreeView==nullptr" << std::endl;
        exit(-9);
    }
    ptr_CHistoryTree->close();
    event->accept();
}
#endif
///////////////////////////////////////////////////////////////////////////////
void LMap::on_Set_ms_Value(int ms) {
    horizontalSlider_ms->releaseMouse();
    QString qs;
    qs.setNum(ms);
    label_ms->setText(qs);
    set_milliSeconds(ms);
}
///////////////////////////////////////////////////////////////////////////////
void LMap::redraw(QSize size, bool useColor) {
    try {
        std::cout << "m_selected = " << m_selected << std::endl << std::flush;
        std::cout << std::boolalpha << "useColor = " << useColor << std::endl << std::flush;
        data_t processed = g_Logistic_Map_HISTORY_database( m_selected );
        assert(processed.size() == g_uint32_t_size);
        std::uint8_t* buffer = reinterpret_cast<std::uint8_t*>( &processed[0] );
        QImage image( QSize{ g_default___screen_width , g_default___screen_height }, QImage::Format_RGB32 );
        unsigned char* buuffer = image.bits();
        memset(buuffer, 0, g_default___screen_width * g_default___screen_height * sizeof (QRgb));
        std::memcpy(buuffer, buffer, g_default___screen_width * g_default___screen_height * sizeof (QRgb));
        Colorize_map::colorize( reinterpret_cast<std::uint32_t*>(buuffer), static_cast<const QRgb>(g_default___screen_width), static_cast<const QRgb>(g_default___screen_height), useColor);
        emit map( image.mirrored(false,true) );
    }
    catch (const std::out_of_range& oor) {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
    catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
    if (checkBox_auto_save->checkState() == Qt::Checked) save_png(size);
    if ( checkBox_auto_save->QAbstractButton::isChecked() ) {}
}
#if 0
#endif
///////////////////////////////////////////////////////////////////////////////
void LMap::save_png(QSize const &size, char const *filename) {
    std::string attribute = m_color==LMap::COLOR::RedGreenBlue_FromWaveLength? R"(C)" : R"(BW)";
    std::uint32_t imin{1};
    std::uint32_t imax{1};
    std::uint32_t iwidth{1};
        auto cmap = [&imin,&iwidth](std::uint32_t a)->std::uint32_t{return (static_cast<std::uint32_t>( ( (g_control.ColormapSize-1)*(a-imin) )/iwidth) );};
    int screenwidth = static_cast<int>(size.width());
    int screenheight = static_cast<int>(size.height());
    std::uint8_t r{0},g{0},b{0};
    int n{0};
    auto get_byte = [&n](std::uint8_t c)->std::uint8_t{return static_cast<std::uint8_t>( ((unsigned int)c >> (n << 3) ) & 0xff );};
    PngWriter png(screenwidth,screenheight);
    std::uint32_t const * const buffer = reinterpret_cast<std::uint32_t*>(&g_Logistic_Map_HISTORY_database(get_selected())[0]);
    for ( int row_y = 0; row_y < screenheight; ++row_y ) {
        std::uint32_t const * const x = &buffer[row_y*screenwidth];
         std::pair<std::uint32_t const * const, std::uint32_t const * const> result = std::minmax_element(&x[0], &x[screenwidth-1]);
            imin = *result.first;
            imax = *result.second;
            iwidth = imax - imin;
        if (iwidth == 0) iwidth = 1;
        for ( int col_x = 0; col_x < screenwidth; ++col_x) {
            QRgb const p = buffer[row_y*screenwidth+col_x];
            if (m_color==LMap::COLOR::RedGreenBlue_FromWaveLength) {
                if (p > 0) {
                    auto I = cmap(p);
                    QRgb rgb = g_control.colormap[ I ];
                    n = 0;
        r = static_cast<std::uint8_t>( qRed(rgb) );
        g = static_cast<std::uint8_t>( qGreen(rgb) );
        b = static_cast<std::uint8_t>( qBlue(rgb) );
#if 0
        typedef unsigned int QRgb;
        const Q_DECL_UNUSED QRgb RGB_MASK = 0x00ffffff;
        inline Q_DECL_CONSTEXPR int qRed(QRgb rgb)
        { return ((rgb >> 16) & 0xff); }
        inline Q_DECL_CONSTEXPR int qGreen(QRgb rgb)
        { return ((rgb >> 8) & 0xff); }
        inline Q_DECL_CONSTEXPR int qBlue(QRgb rgb)
        { return (rgb & 0xff); }
        inline Q_DECL_CONSTEXPR int qAlpha(QRgb rgb)
        { return rgb >> 24; }
        inline Q_DECL_CONSTEXPR QRgb qRgb(int r, int g, int b)
        { return (0xffu << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu); }
        inline Q_DECL_CONSTEXPR QRgb qRgba(int r, int g, int b, int a)
        { return ((a & 0xffu) << 24) | ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu); }
        inline Q_DECL_CONSTEXPR int qGray(int r, int g, int b)
        { return (r*11+g*16+b*5)/32; }
        inline Q_DECL_CONSTEXPR int qGray(QRgb rgb)
        { return qGray(qRed(rgb), qGreen(rgb), qBlue(rgb)); }
        uint32_t htonl(uint32_t hostlong);
        uint16_t htons(uint16_t hostshort);
        uint32_t ntohl(uint32_t netlong);
        uint16_t ntohs(uint16_t netshort);
        Description
        The htonl() function converts the unsigned integer hostlong from host byte order to network byte order.
        The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
        The ntohl() function converts the unsigned integer netlong from network byte order to host byte order.
        The ntohs() function converts the unsigned short integer netshort from network byte order to host byte order.
        On the i386 the host byte order is Least Significant Byte first, whereas the network byte order, as used on the Internet, is Most Significant Byte first.
    r = (c >> (8*n)) & 0xff;
++n; g = (c >> (8*n)) & 0xff;
++n; b = (c >> (8*n)) & 0xff;
For the (n+1)th byte in whatever order they appear in memory (which is also least- to most- significant on little-endian machines like x86):
int x = ((unsigned char *)(&number))[n];
For the (n+1)th byte from least to most significant on big-endian machines:
int x = ((unsigned char *)(&number))[sizeof(int) - 1 - n];
For the (n+1)th byte from least to most significant (any endian):
int x = ((unsigned int)number >> (n << 3)) & 0xff;
        auto get_byte = [n](std::uint8_t x){return ((unsigned int)x >> (n << 3)) & 0xff;}
#endif
                    png.set(col_x,row_y,r,g,b);
                }
                else png.set(col_x,row_y,255, 255, 255);
            }
            else {
                if(p > 0 ) png.set(col_x,row_y,0,0,0);
                else png.set(col_x,row_y,255, 255, 255);
            }
        }
    }
    if (filename != nullptr) {
        png.write(filename);
        return;
    }
    std::string fileName00{unique_filename};
    if (replace(fileName00, ".json", "__")) {
        std::string fileName = fileName00;
        fileName+= attribute + "__" + std::to_string(Data::vec_LogisticMap_Data.size()-1) + ".png";
        png.write(fileName.c_str());
    }
}
///////////////////////////////////////////////////////////////////////////////
void LMap::gotoThisRate() {
    QString qs{pb_Rate_Goto->text()};
    std::string rate_s{qs.toStdString()};
    try {
        rate_s = get_dialog_Play_Rate_mpf();
    }
    catch (std::invalid_argument const& iaex) {
        setCursor(Qt::CrossCursor);
        abort_OFF();
        playROWS_ON();
        update();
        pb_Rate_Goto->setStyleSheet(QString{pb_Rate_Goto_buttonstyle});
        emit qs_rate(qs);
        std::cout << "LMap::gotoThisRate: abort " << iaex.what()  << std::endl;
        return;
    }
    catch(const std::exception& e) {
        emit qs_rate(qs);
        std::cout << e.what() << '\n';
        return;
    }
    catch (...) {
        emit qs_rate(qs);
        return;
    }
    auto a31 = rate_s.empty();
    auto a32 = rate_s.length();
    auto a33 = rate_s.size();
    auto a34 = rate_s.c_str();
    auto a35 = sizeof(a34);
    auto a36 = strlen(a34);
    if (a31) {
        throw std::invalid_argument("    dialog.rate_qstring().isEmpty() .");
    }
    if (a32==0||a32==1) {
        throw std::invalid_argument("TRANSACTION CANCELLED.");
    }
    if (a33==0||a33==1) {
        throw std::invalid_argument("TRANSACTION CANCELLED.");
    }
    if (a36==0||a36==1) {
        throw std::invalid_argument("TRANSACTION CANCELLED.");
    }
    gotoThisRate( rate_s );
}
///////////////////////////////////////////////////////////////////////////////
void LMap::gotoThisRate(std::string const &newRate_s) {
    try {
        auto ret = Data::gotoThisRate(newRate_s, get_fixedAspectRatio());
        if (static_cast<long>(ret) == -1) return;
        m_selected = ret;
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
        record_history();
    //setFROM(row_y);
    //setTO(row_y+2);
        pb_abort->setVisible(true);
        pb_abort->setHidden(false);
        updateLabels();


        auto a31 = newRate_s.empty();
        auto a32 = newRate_s.length();
        auto a33 = newRate_s.size();
        auto a34 = newRate_s.c_str();
        auto a35 = sizeof(a34);
        auto a36 = strlen(a34);// != sizeof(a34) because of byte padding

        char copy[1024];
        //if (strlcpy(copy, a34, a36) >= a36) return -1;
        std::strncpy((char*)copy, (const char *)a34, a36);
        /* add a final null terminator */
        copy[a36] = 0;
        auto a37 = sizeof(copy);
        auto a38 = strlen((char*)copy);

        if (a31) {
            return;
        }
        if (a35==0||a35==1) {
            return;
        }
        mpf_class rate_t{(const char *)copy, NS_LogisticMap::prec, 10};

    //    mpf_class rate_t(newRate_s.c_str(), NS_LogisticMap::prec, 10);
    QRgb row_y = dum.get_screen_Row_y(rate_t);
    QRgb  from = get_FROM();
    QRgb    to = get_TO();
    QRgb delt = row_y - (to+from)/2;
    std::cout << "LMap::gotoThisRate delt = " << delt << std::endl;


    lineEdit_Rate_Play->setText(QString("%1").arg(newRate_s.c_str()));
    lineEdit_Rate_Play->update();
    pb_from->setText(tr("%1").arg( get_FROM() ));
    pb_to->setText(tr("%1").arg( get_TO() ));
    pb_from->update();
    pb_to->update();
    compute();
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
//void LMap::playThisRate(mpf_class const &rate_t) {
//    emit sig_playThisRate();
//}
///////////////////////////////////////////////////////////////////////////////
void LMap::on_Begin(void) {
    ReleaseMouse();
    openGLWidget->setCursor(Qt::BusyCursor);
    setCursor(Qt::BusyCursor);
    abort_ON();
    //playROWS_OFF();
    update();
    ReleaseMouse();
    for (int j=0;j<3;j++) {
        abort_ON();
        //playROWS_OFF();
        update();
        ReleaseMouse();
        std::this_thread::sleep_for(std::chrono::microseconds(1000*100));
    }
}
///////////////////////////////////////////////////////////////////////////////
void LMap::on_End(void) {
    ReleaseMouse();
    playROWS_ON();
    b_playingMusic = false;
    openGLWidget->setCursor(Qt::CrossCursor);
    setCursor(Qt::CrossCursor);
    spR.reset();
    spR = nullptr;
    spi = 0;
}
///////////////////////////////////////////////////////////////////////////////
void LMap::get_uniqueFilename() {
    uniqueFilename = QString{""};
    std::string dtTemplate = generateTemplate();
    std::cout << "dtTemplate = " << dtTemplate.c_str() << std::endl;
    QTemporaryFile tmpFile;
    tmpFile.setFileTemplate(dtTemplate.c_str());
    (*(QFile*)(&tmpFile)).open(QIODevice::ReadWrite | QIODevice::Text);
    uniqueFilename = tmpFile.fileName();
    tmpFile.close();
    tmpFile.deleteLater();
    std::cout << "uniqueFilename = " << uniqueFilename.toStdString().c_str() << std::endl;
    for (int i = 0; i < uniqueFilename.size(); ++i) {
        if ( uniqueFilename.at(i) == QChar('.') ) {
            uniqueFilename[i-1] = QChar('t');
            uniqueFilename[i-2] = QChar('s');
            uniqueFilename[i-3] = QChar('i');
            uniqueFilename[i-4] = QChar('h');
            uniqueFilename[i-5] = QChar('M');
            uniqueFilename[i-6] = QChar('L');
        }
    }
    unique_filename = uniqueFilename.toStdString();
}
///////////////////////////////////////////////////////////////////////////////
void LMap::onSelect(std::size_t selected ){
    m_selected = selected;
    compute();
}
///////////////////////////////////////////////////////////////////////////////
void LMap::compute( ) {
    Datum const& datum_parameters = Datum::datum_cache_parameter_changes;
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
        auto chk1 = dum.num_iterationsBASE_v()      == datum_parameters.num_iterationsBASE_v();
        auto chk2 = dum.point_density_exponent_v()  == datum_parameters.point_density_exponent_v();
        if (!(chk1&&chk2)) {
            std::size_t ret = Data::vec_LogisticMap_Data.size();
            Datum d{    ret,
                        dum.x_min_v(),
                        dum.y_min_v(),
                        dum.x_max_v(),
                        dum.y_max_v(),
                        dum.point_density_v(),
                        (double)Datum::datum_cache_parameter_changes.point_density_exponent_v(),
                        Datum::datum_cache_parameter_changes.num_iterationsBASE_v()};

            m_selected = Data::add_datum(d);
        }
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
    ReleaseMouse();
    playROWS_OFF();
    abort_ON();
    //playROWS_and_cancel_OFF();
    updateLabels();
    //openGLWidget->setCursor(Qt::BusyCursor);
    setCursor(Qt::BusyCursor);
    compute_map_threadCaller();
}
///////////////////////////////////////////////////////////////////////////////
void LMap::setIntegerITERATION_NUM(QRgb n) {
    if (n>0 && n<999999)
        Datum::datum_cache_parameter_changes.num_iterationsBASE_ref() = n;
}
///////////////////////////////////////////////////////////////////////////////
void LMap::newRegion( QPoint const &pos1,    QPoint const &pos2) {
    m_selected = Data::newRegion( m_selected, pos1, pos2 );
    updateLabels();
    record_history();
    compute();
}
///////////////////////////////////////////////////////////////////////////////
void LMap::ReleaseMouse() {
    pb_n_base->releaseMouse();
    pb_n_exponent->releaseMouse();
    pb_numThreads->releaseMouse();
    pb_re_compute->releaseMouse();
    pb_Rate_Goto->releaseMouse();
    pb_abort->releaseMouse();
    pb_playMusic->releaseMouse();
    pb_to->releaseMouse();
    pb_from->releaseMouse();
    pb_num_notes->releaseMouse();
    pb_cancel->releaseMouse();
    lineEdit_Rate_Play->releaseMouse();
    pb_cancel->releaseMouse();
    pb_Rate_Goto->releaseMouse();
    lineEdit_Rate_Play->releaseMouse();
    pb_playMusic->releaseMouse();
    pb_from->releaseMouse();
    pb_to->releaseMouse();
    releaseMouse();
}
///////////////////////////////////////////////////////////////////////////////
void music_independentThread(bool b_Rate_Play)
{
//    std::cout << "Starting concurrent thread.\n";
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    std::cout << "Exiting concurrent thread.\n";
    foreach (QWidget *widget, QApplication::allWidgets()) {
        if (auto mainWindow = qobject_cast<LMap *>(widget)) {
            auto m_ptr_LMap = mainWindow;
            m_ptr_LMap->Play_Music(b_Rate_Play);
            //m_ptr_LMap->m_sptr_Play_Music_ROOT = std::make_shared<Play_Music_ROOT>(m_ptr_LMap);
            return;
        }
    }
//    m_sptr_Play_Music_ROOT{ std::make_shared<Play_Music_ROOT>(this)
//    foreach (QWidget *widget, QApplication::allWidgets()) {
//        if (auto mainWindow = qobject_cast<LMap *>(widget)) {
//            auto m_ptr_LMap = mainWindow;
//            //m_ptr_LMap->ReleaseMouse();
//            m_ptr_LMap->playROWS_ON();
//            m_ptr_LMap->b_playingMusic = false;
//            m_ptr_LMap->openGLWidget->setCursor(Qt::CrossCursor);
//            m_ptr_LMap->setCursor(Qt::CrossCursor);
//            //q->/*m_sptr_Play_Music_ROOT->*/initialize_play_connections(pbtn == lineEdit_Rate_Play);

//            m_ptr_LMap->m_sptr_Play_Music_ROOT.reset();

//            m_ptr_LMap->m_sptr_Play_Music_ROOT = nullptr;
//        }
//    }
}
///////////////////////////////////////////////////////////////////////////////
void LMap::music_threadCaller(bool b_Rate_Play)
{
    std::cout << "Starting thread caller.\n";
    std::thread t(music_independentThread, b_Rate_Play);
    t.detach();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::cout << "Exiting thread caller.\n";
}
#if 0
#endif
///////////////////////////////////////////////////////////////////////////////
void compute_independentThread() {
    foreach (QWidget *widget, QApplication::allWidgets()) {
        if (auto mainWindow = qobject_cast<LMap *>(widget)) {
            auto m_ptr_LMap = mainWindow;
            m_ptr_LMap->ComputeMap();
            return;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////
void LMap::compute_map_threadCaller()
{
    std::thread t(compute_independentThread);
    t.detach();
}
///////////////////////////////////////////////////////////////////////////////
void LMap::ComputeMap()
{
    std::uint32_t   num_THREADS = static_cast<std::uint32_t> ( get_num_THREADS() );
    std::size_t     selected    = get_selected();

    if (!WORKER_THREAD::initialize(selected, num_THREADS)) return;
    //auto fy =    vp | ranges::view::transform([this](auto &x){ *x.first = as_string2<decltype(*x.second)>( *x.second ); return *x.first; });
    //// use or lose; fy is optimized away [not even calculated] IF NOT USED!
    //for (const auto& e: fy)  std::cout << std::string(8, '!') << e << std::endl;

//auto indices = ranges::view::iota(0u, num_THREADS);
//PLN: for (const auto& b : indices) is replaced by
//RANGES_FOR(auto i, indices) {  const auto& b=i; }
//RANGES_FOR(auto i, ranges::view::iota(0u, get_num_THREADS())) {

    std::vector<std::thread> threads;
    setCursor(Qt::BusyCursor);
    for(QRgb i=0;i<get_num_THREADS(); ++i) {
        auto const & p=i;
        threads.emplace_back( [p]() {
            Fill_in_vector fi{p};
            fi.initialize(WORKER_THREAD::files_lock);
            std::pair< data_t, tup_idANDbeginANDendANDarea> data = fi();
            {
            std::lock_guard<std::mutex> lk(WORKER_THREAD::files_lock);
            Fill_in_vector::g_vec_mem_tup_ibeA_t.emplace_back( std::move(data) );
            //lk.unlock();
            }
            WORKER_THREAD::status_changed.notify_one();
        } );
    }

    try {
    for(QRgb i=0;i<get_num_THREADS(); ++i) {
    //RANGES_FOR(auto i, ranges::view::iota(0u, get_num_THREADS())) {
        (threads[i]).join();//Wait on the other threads
    }
    }
    catch (std::invalid_argument const& iaex) {
        std::cout << "LMap::ComputeMap: abort " << iaex.what()  << std::endl;
        return;
    } catch(std::exception const & e) {
        std::cout << e.what() << '\n';
        return;
    } catch(...) {
    return;
    }

    setCursor(Qt::CrossCursor);
    openGLWidget->DisplayMap();
    abort_OFF();
    playROWS_ON();
    update();
}
///////////////////////////////////////////////////////////////////////////////
void LMap::abort_ON(void){
    playROWS_OFF();
        pb_abort->clearFocus();
        pb_abort->setDisabled(false);
        pb_abort->setEnabled(true);
        pb_abort->setHidden(false);
        pb_abort->setVisible(true);
        pb_abort->show();
        pb_abort->update();//crash = repaint()
    }
///////////////////////////////////////////////////////////////////////////////
void LMap::abort_OFF(void){
        pb_abort->clearFocus();
        pb_abort->setDisabled(true);
        pb_abort->setEnabled(false);
        pb_abort->setHidden(true);
        pb_abort->setVisible(false);
        pb_abort->update();
        playROWS_ON();
    }
///////////////////////////////////////////////////////////////////////////////
void LMap::abort() {
    spi = 0;
    Fill_in_vector::m_abort = true;
    Fill_in_vector::whose_turn = static_cast<std::uint32_t>(0);
    abort_OFF();
}
///////////////////////////////////////////////////////////////////////////////
void LMap::playROWS_ON(void){
        ReleaseMouse();
        pb_cancel->clearFocus();
        pb_playMusic->clearFocus();
        //pb_playMusic->blockSignals(false);
        pb_playMusic->setDisabled(false);
        pb_playMusic->setHidden(false);
        pb_playMusic->setEnabled(true);
        pb_playMusic->setVisible(true);
        pb_playMusic->setDown(false);
        pb_playMusic->setStyleSheet(QString{pb_playROWS_buttonstyle});

        pb_playMusic->show();
        pb_playMusic->update();//crash = repaint()


        lineEdit_Rate_Play->clearFocus();
        lineEdit_Rate_Play->setDisabled(false);
        lineEdit_Rate_Play->setEnabled(true);
        lineEdit_Rate_Play->setHidden(false);
        lineEdit_Rate_Play->setVisible(true);
//lineEdit_Rate_Play->setStyleSheet(QString::fromUtf8("text-align:left;"));dies
//lineEdit_Rate_Play->setStyleSheet(QString{pb_Rate_Play_buttonstyle});
lineEdit_Rate_Play->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        lineEdit_Rate_Play->show();
        lineEdit_Rate_Play->update();


        pb_Rate_Goto->clearFocus();
        pb_Rate_Goto->setDisabled(false);
        pb_Rate_Goto->setEnabled(true);
        pb_Rate_Goto->setHidden(false);
        pb_Rate_Goto->setVisible(true);
        pb_Rate_Goto->setStyleSheet(QString{pb_Rate_Goto_buttonstyle});
        pb_Rate_Goto->show();
        pb_Rate_Goto->update();

        //pb_cancel->blockSignals(true);
        pb_cancel->setDisabled(true);
        pb_cancel->setEnabled(false);
        pb_cancel->setHidden(true);
        pb_cancel->setVisible(false);
        pb_cancel->update();
    }
///////////////////////////////////////////////////////////////////////////////
void LMap::playROWS_OFF(void){
        ReleaseMouse();
        pb_cancel->clearFocus();
        //pb_playMusic->blockSignals(true);
        pb_playMusic->clearFocus();
        pb_playMusic->setDisabled(true);
        pb_playMusic->setEnabled(false);
        pb_playMusic->setHidden(true);
        pb_playMusic->setVisible(false);
        pb_playMusic->setStyleSheet(QString::fromUtf8("text-align:left;"));
        //pb_playMusic->show();
        pb_playMusic->update();//crash = repaint()


        pb_Rate_Goto->clearFocus();
        pb_Rate_Goto->setDisabled(true);
        pb_Rate_Goto->setEnabled(false);
        pb_Rate_Goto->setHidden(true);
        pb_Rate_Goto->setVisible(false);
        pb_Rate_Goto->setStyleSheet(QString::fromUtf8("text-align:left;"));
        pb_Rate_Goto->show();
        pb_Rate_Goto->update();


        lineEdit_Rate_Play->clearFocus();
        lineEdit_Rate_Play->setDisabled(true);
        lineEdit_Rate_Play->setEnabled(false);
        lineEdit_Rate_Play->setHidden(true);
        lineEdit_Rate_Play->setVisible(false);
        lineEdit_Rate_Play->setStyleSheet(QString::fromUtf8("text-align:left;"));
        lineEdit_Rate_Play->show();
        lineEdit_Rate_Play->update();


        //for (int j=0;j<33;j++) {
        //pb_cancel->blockSignals(false);
        pb_cancel->setHidden(false);
        pb_cancel->setVisible(true);
        pb_cancel->setDown(false);
        pb_cancel->setFlat(false);
        pb_cancel->setDisabled(false);
        pb_cancel->setEnabled(true);

        pb_cancel->show();
        pb_cancel->update();
    }
///////////////////////////////////////////////////////////////////////////////
//void LMap::playROWS_and_cancel_OFF(void){
//        pb_cancel->clearFocus();
//        pb_playMusic->clearFocus();
//        pb_playMusic->setDisabled(true);
//        pb_playMusic->setEnabled(false);
//        pb_playMusic->setHidden(true);
//        pb_playMusic->setVisible(false);

//        pb_cancel->setDisabled(true);
//        pb_cancel->setEnabled(false);
//        pb_cancel->setHidden(true);
//        pb_cancel->setVisible(false);
//        pb_playMusic->update();
//        pb_cancel->update();
//    }
///////////////////////////////////////////////////////////////////////////////
void LMap::newColor(int i) {
    m_color = static_cast<LMap::COLOR>(i);
    redraw( openGLWidget->size(), m_color==LMap::COLOR::RedGreenBlue_FromWaveLength);
}
///////////////////////////////////////////////////////////////////////////////
QRgb LMap::get_chaos_threshold_rate_get_screen_Row_y() const {
    //return Data::vec_LogisticMap_Data::chaos_threshold_rate_get_screen_Row_y();
    constexpr const static double chaos_threshold_R = 3.569945671870944901842;
try {
    Datum const& dum = Data::datum(m_selected);
    assert(dum.ID_v() == m_selected);
    mpf_class row_t = ( chaos_threshold_R - dum.y_min_v() ) / dum.normalized_height_v() ;// row_t = (y_t - y_min_mpf)/normalized_height_t;
    std::uint32_t row_y = static_cast<QRgb >(mpf_get_ui(row_t.get_mpf_t()));
    return row_y;
} catch(const std::exception& e) {
    std::cout << e.what() << '\n';
}
}
///////////////////////////////////////////////////////////////////////////////
std::uint32_t LMap::get_screen_Row_y( mpf_class const &y_t ) const {
    std::uint32_t row_y{0};
    //mpf_class row_t = (y_t - y_min_mpf)/normalized_height_t;
    //row_y = static_cast<std::uint32_t>( mpf_get_ui(row_t.get_mpf_t()));
    //return row_y;
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
        //mpf_class row_t = ( y_t - dum.y_min_v() ) / dum.normalized_height_v() ;// row_t = (y_t - y_min_mpf)/normalized_height_t;
        //std::uint32_t row_y = static_cast<QRgb >(mpf_get_ui(row_t.get_mpf_t()));
        return dum.get_screen_Row_y( y_t );//row_y;
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
///////////////////////////////////////////////////////////////////////////////
std::uint32_t LMap::get_screen_Col_x( mpf_class const &x_t ) const {
    std::uint32_t col_x{0};
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
        //mpf_class col_t = ( x_t - dum.x_min_v() ) / dum.normalized_width_v() ;
        //col_x = static_cast<std::uint32_t>( mpf_get_ui(col_t.get_mpf_t()));
        return dum.get_screen_Col_x( x_t );//col_x;
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
///////////////////////////////////////////////////////////////////////////////
mpf_class LMap::get_y_mpf( QRgb row_y) const {
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
        //mpf_set_default_prec (NS_LogisticMap::prec);
        //mpf_class rate_t = dum.y_min_v() + dum.normalized_height_v() * row_y ;// row_t = (y_t - y_min_mpf)/normalized_height_t;
        return dum.get_y_mpf( row_y);//rate_t;
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
//return Data::vec_LogisticMap_Data::Rate(row_y);
}
///////////////////////////////////////////////////////////////////////////////
double LMap::get_relativeDensity_exponent(void) const {
    Datum const& dum = Datum::datum_cache_parameter_changes;
    return dum.point_density_exponent_v();
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
        return dum.point_density_exponent_v();
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
///////////////////////////////////////////////////////////////////////////////
double LMap::get_relativeDensity(void) const {
    Datum const& dum = Datum::datum_cache_parameter_changes;
    return mpf_get_d( dum.point_density_v().get_mpf_t() );
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
        return mpf_get_d( dum.point_density_v().get_mpf_t() );
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
///////////////////////////////////////////////////////////////////////////////
std::string LMap::get_relativeDensity_str(void) const {
    std::ostringstream oss;
    oss.precision(dbl_prec::max_digits10+2);
    oss <<  std::fixed << get_relativeDensity() ;//<< std::ends;
    return oss.str();
}
///////////////////////////////////////////////////////////////////////////////
double LMap::get_increase_sample_size_by(void) const {
    Datum const& dum = Datum::datum_cache_parameter_changes;
    return  dum.get_increase_sample_size_by();
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
        return  dum.get_increase_sample_size_by();
//            mpf_class point_density_exponent = dum.point_density_exponent_v();
//            mpf_class D_n =  pow( dum.point_density_v(), point_density_exponent );
//            double d_n = mpf_get_d( D_n.get_mpf_t() );
//            return d_n;
//            return mpf_get_d( dum.point_density_v().get_mpf_t() );
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
//    return Data::vec_LogisticMap_Data::increase_sample_size_by(m_selected);
}
///////////////////////////////////////////////////////////////////////////////
QRgb LMap::get_num_iterations_base(void) const  {
    Datum const& dum = Datum::datum_cache_parameter_changes;
    return dum.num_iterationsBASE_v();
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
        return dum.num_iterationsBASE_v();
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
///////////////////////////////////////////////////////////////////////////////
QRgb LMap::get_num_iterations(void) const  {
    Datum const& dum = Datum::datum_cache_parameter_changes;
    return dum.get_num_iterations();
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
        return dum.get_num_iterations();
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
///////////////////////////////////////////////////////////////////////////////
void LMap::set_milliSeconds(int n) {
    if (static_cast<int>(n)>=50) lLength_ms =n<=500? n:500;
    if (spi==1&&spR && spR != nullptr && spR.use_count()>0) emit spR->updateMilliSeconds(n);
    //if (spR && spR != nullptr && spR.use_count()>0) emit spR->updateMilliSeconds(n);
    //if (spR.get()  != nullptr ) spR->updateMilliSeconds(n);
}
///////////////////////////////////////////////////////////////////////////////
void LMap::on_Suicide(void) {
//    m_ptr_LMap->ReleaseMouse();
//    m_ptr_LMap->playROWS_ON();
//    m_ptr_LMap->b_playingMusic = false;
//    m_ptr_LMap->openGLWidget->setCursor(Qt::CrossCursor);
//    m_ptr_LMap->setCursor(Qt::CrossCursor);
//    QObject::disconnect(this, &LMap::sig_playROWS,     spR.get(),  &playRows_Controller::on_playROWS );
//    QObject::disconnect(this, &LMap::sig_playThisRate, spR.get(),  &playRows_Controller::on_playThisRate );
    QObject::disconnect(spR.get(), &playRows_Controller::suicide,   this, &LMap::on_Suicide);
    QObject::disconnect(spR.get(), &playRows_Controller::suicide,   this, &LMap::on_End);
    QObject::disconnect(spR.get(), &playRows_Controller::sig_begin, this, &LMap::on_Begin);
    QObject::disconnect(pb_cancel, &QPushButton::clicked, spR.get(), &playRows_Controller::on_StopProcess);

//    QObject::disconnect(spR.get(), &playRows_Controller::qs_rate,      lineEdit_Rate_Play, &xxxQLineEdit::setText);
//    QObject::disconnect(spR.get(), &playRows_Controller::qs_rate,      pb_Rate_Goto, &QPushButton::setText);

    QObject::disconnect(spR.get(), &playRows_Controller::qs_rate,      this, &LMap::pb_Rate_Goto_setText);


//    QObject::disconnect(spR.get(), &playRows_Controller::selectAll,    m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::selectAll);
//    QObject::disconnect(spR.get(), &playRows_Controller::cut,          m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::cut);
//    QObject::disconnect(spR.get(), &playRows_Controller::clear,        m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::clear);
//    QObject::disconnect(spR.get(), &playRows_Controller::qs_rate,      m_ptr_LMap->plainTextEdit_rate, &QPlainTextEdit::setPlainText);

    spR.reset();
    //spi.reset();
    spR = nullptr;
    spi = 0;//nullptr;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LMap::Play_Music(bool b_Rate_Play) {
    //initialize_play_connections(b_Rate_Play);
    ReleaseMouse();
    spR.reset();
    //spi.reset();
    spR = nullptr;
    spi = 0;//nullptr;

#if 0
    for (auto &n : f_notes) {
        std::cout << n.f << " ";
        toot( n.f , 100 ) ;
    }
    std::cout << std::endl;
#endif

//    QString qs = pb_Rate_Goto->text();
//    std::string s{qs.toStdString()};
//    std::string t = do_replace(s);
//    mpf_class r(t.c_str(), NS_LogisticMap::prec, 10);
    mpf_class rate{};//(t.c_str(), NS_LogisticMap::prec, 10);
    //... but not used in the on_playROWS fn call

#if 10
    if (b_Rate_Play) {
        try {
            QString qs;
            qs = lineEdit_Rate_Play->text();
            std::string rate_s = qs.toStdString();


            auto a31 = rate_s.empty();
            auto a32 = rate_s.length();
            auto a33 = rate_s.size();
            auto a34 = rate_s.c_str();
            auto a35 = sizeof(a34);
            auto a36 = strlen(a34);// != sizeof(a34) because of byte padding

            char copy[1024];
            //if (strlcpy(copy, a34, a36) >= a36) return -1;
            std::strncpy((char*)copy, (const char *)a34, a36);
            /* add a final null terminator */
            copy[a36] = 0;
            auto a37 = sizeof(copy);
            auto a38 = strlen((char*)copy);

            if (a31) {
                return;
            }
            if (a35==0||a35==1) {
                return;
            }
            rate = mpf_class{(const char *)copy, NS_LogisticMap::prec, 10};
        } catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            //return r;
        }
        QRgb row_y = get_screen_Row_y(rate);
        setFROM(row_y);
        setTO(row_y+2);
        pb_from->setText(tr("%1").arg( get_FROM() ));
        pb_from->update();
        pb_to->setText(tr("%1").arg( get_TO() ));
        pb_to->update();
    }
    else {
    }
#endif

    spR = std::make_shared<playRows_Controller>(m_selected, m_FROM, m_TO, m_NUM_NOTES,
                                            lLength_ms, spi, this, b_Rate_Play, rate);

auto q= spR;
}
///////////////////////////////////////////////////////////////////////////////
void LMap::set_Rate_to_Play( QPoint const &pos ) {
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
        auto [mpf_x , mpf_y] = dum.get_mpf_XY_tuple( pos );
        mpf_class y_t = mpf_y;
        m_play_this_ROW = dum.get_screen_Row_y(y_t);
        m_play_this_ROW_Rate = mpf_y;

    QRgb row_y = get_screen_Row_y(mpf_y);
    setFROM(row_y-1);
    setTO(row_y+2);
    pb_from->setText(tr("%1").arg( get_FROM() ));
    pb_from->update();
    pb_to->setText(tr("%1").arg( get_TO() ));
    pb_to->update();

    std::stringstream ss;
//ss  << std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << y_t  << std::flush;
    ss  << std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << mpf_y  << std::flush;
    std::string rs{ss.str()};
    std::string newRate_s{remove_ws(rs)};
    //std::string substr = newRate_s.substr(0, 13);
    emit qs_rate(QString("%1").arg(newRate_s.c_str()));
//lineEdit_Rate_Play->setText(QString("%1").arg(newRate_s.c_str()));
//lineEdit_Rate_Play->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//lineEdit_Rate_Play->setCursorPosition(0);
//lineEdit_Rate_Play->show();
//lineEdit_Rate_Play->update();
////lineEdit_Rate_Play->setStyleSheet(QString::fromUtf8("text-align:left;"));//setStyleSheet(QString{pb_Rate_Play_buttonstyle});
    //m_ptr_LMap->lineEdit_Rate_Play->setStyleSheet(QString::fromUtf8("text-align:left;"));//setStyleSheet(QString{pb_Rate_Play_buttonstyle});
    //m_ptr_LMap->lineEdit_Rate_Play->update();
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
/////////////////////////////////////////////////////////////////////////////////
void LMap::record_history() {
try {
    Datum const& dum = Data::datum(m_selected);
    assert(dum.ID_v() == m_selected);
    dum.write_JSON(unique_filename);
} catch(const std::exception& e) {
    std::cout << e.what() << '\n';
}
ptr_QJsonTreeView->load();// QString {unique_filename.c_str()} );
ptr_QJsonTreeView->update();
ptr_QJsonTreeView->show();
}
/////////////////////////////////////////////////////////////////////////////////
void LMap::pb_Rate_Goto_setText(QString const &qs) {
//    setCursor(Qt::CrossCursor);
//    abort_OFF();
//    playROWS_ON();
//    update();
//    pb_Rate_Goto->setStyleSheet(QString{pb_Rate_Goto_buttonstyle});
pb_Rate_Goto->setText(qs);
//pb_Rate_Goto->setCursorPosition(0);
pb_Rate_Goto->update();
pb_Rate_Goto->show();

lineEdit_Rate_Play->setText(qs);
//lineEdit_Rate_Play->setCursorPosition(0);
lineEdit_Rate_Play->update();
lineEdit_Rate_Play->show();
}
/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LMap::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Escape) {
            spi = 0;
            abort_OFF();
            openGLWidget->b_mousePress = false;
    }
//    if (b_mousePress) {
//        b_mousePress = false;
//    }
//    switch (event->key()) {
//    case Qt::Key_Plus:
//        //reCalculateMap(ZoomInFactor);
//        break;
//    case Qt::Key_Minus:
//        //reCalculateMap(ZoomOutFactor);
//        break;
//    case Qt::Key_Left:
//        //scroll(-ScrollStep, 0);
//        break;
//    case Qt::Key_Right:
//        //scroll(+ScrollStep, 0);
//        break;
//    case Qt::Key_Down:
//        //scroll(0, -ScrollStep);
//        break;
//    case Qt::Key_Up:
//        //scroll(0, +ScrollStep);
//        break;
//    default:
//        QMainWindow::keyPressEvent(event);
//    }
}
////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//play_rubberBand_Rect:
void play_rubberBand_Rect_independentThread(){
    foreach (QWidget *widget, QApplication::allWidgets()) {
        if (auto mainWindow = qobject_cast<LMap *>(widget)) {
            auto m_ptr_LMap = mainWindow;
            m_ptr_LMap->play_rubberBand_Rect();
            m_ptr_LMap->abort_OFF();
            return;
        }
    }
}
void LMap::play_rubberBand_Rect() {
    spi=1;
    //on_Begin();
    using pair = std::pair<datum_t, datum_t>;
    std::vector< pair > pairs;
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
    matrix_t m =
    g_Logistic_Map_HISTORY_database.Copy(g_Logistic_Map_HISTORY_database(m_selected));
// find min/max for each row
    for (datum_t row=0; row < static_cast<datum_t>(g_Logistic_Map_HISTORY_database.m_play_rect.height()) ; ++row) {
        pair p;
        p.first = p.second = m[row][0];
        for (datum_t col=1; col< static_cast<datum_t>( g_Logistic_Map_HISTORY_database.m_play_rect.width() ) ; ++col) {
            if (m[row][col] < p.first ) p.first=m[row][col];
            if (m[row][col] > p.second) p.second=m[row][col];
        }
        if ( p.first == p.second ) ++p.second;
        pairs.emplace_back( std::move( p ) );
    }
auto map = [pairs](datum_t const row, datum_t const &a){ datum_t x=(datum_t)((1000.0*(a - pairs[row].first))/(pairs[row].second - pairs[row].first)) ;
                                                         std::cout <<x<<" "<<std::flush;
if (x<222) x=(datum_t)(222+x*NS_LogisticMap::urd());
                                                         return  (x+444)%1000;//>0?x:444;
                                                       };
auto map1 = [pairs](datum_t const row, datum_t const &a){ datum_t x=(datum_t)
((1000.0*(1+(1000.0*a)/pairs[row].second - (1000.0*pairs[row].first)/pairs[row].second))/(1001 - (1000.0*pairs[row].first)/pairs[row].second)) ;
std::cout <<x<<" "<<std::flush;
    return  x/*>0?x:1*/;};
//858 642 3661 x4  x4
    auto &x = m;
    matrix_row_t &x0 = m[0];
    datum_t x00 = x0[0];
    datum_t x01 = x0[1];
    datum_t x02 = x0[2];
    float lFrequency{440.f} ;// toot -f 440. -l 300
//    for (datum_t row=0; row < static_cast<datum_t>( g_Logistic_Map_HISTORY_database.m_play_rect.height()) ; ++row) {
//        std::pair<datum_t, datum_t> result_x = minmax_element(m[row]);
//    }
    for (datum_t row=0; row < static_cast<datum_t>( g_Logistic_Map_HISTORY_database.m_play_rect.height()) ; ++row) {
        for (datum_t col=0; col< static_cast<datum_t>( g_Logistic_Map_HISTORY_database.m_play_rect.width() ) ; ++col) {
            if (spi == 0) {
                for(std::size_t i = 0; i < static_cast<std::size_t>(g_Logistic_Map_HISTORY_database.m_play_rect.height()); ++i) {
                        /*delete[] */m[i].reset();
                    m[i] = nullptr;
                }
                /*delete[] */m.reset();
                m = nullptr;
                return;
            }
            datum_t x_t = m[row][col];
QRgb row_y = dum.get_screen_Col_x( (g_default___screen_height - static_cast<datum_t>(g_Logistic_Map_HISTORY_database.m_play_rect.bottom()) -1)+row );
QRgb col_x = dum.get_screen_Col_x( static_cast<datum_t>(g_Logistic_Map_HISTORY_database.m_play_rect.left())+col );
            QPoint p{static_cast<int>(col_x),static_cast<int>(row_y)};
            openGLWidget->draw(p);
            lFrequency = static_cast<float>( f_notes[map(row, x_t)].f );
    //lLength_ms = 166;
    {
    toot( lFrequency , lLength_ms , openGLWidget->m_hack.fn, openGLWidget) ;
    }
    //std::this_thread::sleep_for(std::chrono::microseconds(1000*lLength_ms));
}
}

    for(std::size_t i = 0; i < static_cast<std::size_t>(g_Logistic_Map_HISTORY_database.m_play_rect.height()); ++i) {
            /*delete[] */m[i].reset();
        m[i] = nullptr;
    }
    /*delete[] */m.reset();
    m = nullptr;
    }
    catch (const std::out_of_range& oor) {
      std::cout << "LMap::play_rubberBand_Rect() Out of Range error: " << oor.what() << '\n';
    }
    catch(const std::exception& e) {
        std::cout << "LMap::play_rubberBand_Rect() " << e.what() << '\n';
    }
    catch (...) {
        std::cerr << "LMap::play_rubberBand_Rect() \n";

    }
}
void LMap::play_rubberBand_This_Rect(QRect const &rect) {
    abort_ON();// calls playROWS_OFF();
    g_Logistic_Map_HISTORY_database.m_play_rect = rect;
    std::thread t(play_rubberBand_Rect_independentThread);
    t.detach();
}
/////////////////////////////////////////////////////////////////////////////////
//void LMap::
/////////////////////////////////////////////////////////////////////////////////
//void LMap::
/////////////////////////////////////////////////////////////////////////////////
//void LMap::
/////////////////////////////////////////////////////////////////////////////////
//void LMap::
/////////////////////////////////////////////////////////////////////////////////
//void LMap::
/////////////////////////////////////////////////////////////////////////////////
//void LMap::
/////////////////////////////////////////////////////////////////////////////////
//void LMap::
/////////////////////////////////////////////////////////////////////////////////
void LMap::on_action_Save_triggered() {
QString fileName;
// If we don't have a filename from before, get one.
//    if (currentFile.isEmpty())
//    {

//        QString filters("JSON files (*.json);;Text files (*.txt);;All files (*.*)");
//        QString defaultFilter("JSON files (*.json)");

    QString filters("png files (*.png);;Text files (*.txt);;All files (*.*)");
    QString defaultFilter("png files (*.png)");


    /* Static method approach */
    fileName = QFileDialog::getSaveFileName(this, "Save history", QDir::currentPath(),
        filters, &defaultFilter);
    //fileName = QFileDialog::getSaveFileName(this, "Save");
    currentFile = fileName;
//    }
//    else
//    {
//        fileName = currentFile;
//    }
QFile file(fileName);
if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
    return;
}
//    setWindowTitle(fileName);
//    QTextStream out(&file);
//    QString text = ui->textEdit->toPlainText();
//    out << text;
    file.close();
    save_png( this->openGLWidget->size() , fileName.toStdString().c_str() );
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/// \brief CPU::set_point_of_interest
/// \param QPoint const &pos
/// \param std::string const& text
///
void LMap::set_point_of_interest( QPoint const &pos, std::string const& text) {
    try {
        Datum const& dum = Data::datum(m_selected);
        assert(dum.ID_v() == m_selected);
    auto [x_t , y_t] = dum.get_mpf_XY_tuple( pos );
//---------------------------------------
    std::ostringstream ss[2];
    ss[0]  << std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << x_t ;//<< std::ends;
    ss[1]  << std::left << std::setfill(' ') << std::setw(NS_LogisticMap::prec) << std::setprecision(NS_LogisticMap::prec) << y_t ;//<< std::ends;
//    std::string sx = "\"" + remove_ws(ss[0].str()) + "\"";
//    std::string sy = "\"" + remove_ws(ss[1].str()) + "\"";
    std::string sx = as_string(x_t);
    std::string sy = as_string(y_t);
    std::cout << sx<< std::endl << ss[0].str() << std::endl;
    std::cout << sy<< std::endl << ss[1].str() << std::endl;
    points_of_interest.push_back(sx);
    points_of_interest.push_back(sy);

    std::fstream outf(unique_filename);//, std::ios_base::app);
    std::string ID{std::to_string(m_selected)};
    nlohmann::json j;
#if 0
#endif
//sg+= std::ends;
//std::stringstream jo{sg};
//jo>>j[ID];


//const char ch[]={']','}','\n','}','\n',']','\n','}'};
//std::array< const char , sizeof(ch) > ach={']','}','\n','}','\n',']','\n','}'};
const char ch[]={']','}','\n','}','\n',']','\n','}'};
std::array< const char , sizeof(ch) > ach={']','}','\n','}','\n',']','\n','}'};
//const char ch0[]={']','}','\n','}','\n',']'};
//std::array< const char , 6 > ach0={']','}','\n','}','\n',']'};


std::string tg{"{\""};
tg+= text+"\":{\n";     //"\"P.O.I.\":[{\"" text+"\":{\n"
tg+= G_POI_KEY_X+sx+",\n"+G_POI_KEY_Y+sy+"\n}}\n]\n}]";



std::string sg{G_POI_KEY}; //"\"P.O.I.\":[{\""
sg+= text+"\":{\n";        //"\"P.O.I.\":[{\"" text+"\":{\n"
sg+= G_POI_KEY_X+sx+",\n"+G_POI_KEY_Y+sy+"\n}}\n]\n}]";
    outf.seekg(std::ios_base::end);
    int I{-1}, c{0};
    outf.seekg(I--, std::ios_base::end);
    c = outf.peek();
    if (c == ']') {
        outf.seekg(I--, std::ios_base::end);
        c = outf.peek();
        if (c == '}') {
            outf.seekg(I--, std::ios_base::end);
            c = outf.peek();
            if (c == '\n') {
                outf.seekg(I--, std::ios_base::end);
                c = outf.peek();
                if (c == ']') {
                    outf.put(',');
                    outf.put('\n');
                    outf << tg;
                    outf.close();
                    return;
                }
                else {
                    outf.put(',');
                    outf.put('\n');
                    outf << sg;
                    outf.close();
                    return;
                }
            }
        }
    }







//            if (I == -6-1) {
//                outf.seekg(-5, std::ios_base::end);
//                c = outf.peek();
//                if (c == '\n') {
//                    outf.put(',');
//                    outf.put('\n');
//                //outf << j.dump(0);
//                outf << sg;
//                    outf.put('}');
//                    outf.put('\n');
//                    outf.put('}');
//                    outf.put(']');
//                    outf.close();
//                    return;
//                }
//            }
////            std::cout << "ABORT CPU::set_point_of_interest\n";
////            exit(-666);
//        }

//        "N_base":1000
//        }]


//        "N_base":1000,
//        "P.O.I.":[{"nsh":{
//        "x":"0.8432847911395364262173514512097129330713584384150591346347266062906594786670595565201412228805422749844783136761551016058829094001072111",
//        "y":"3.542952500132385361244812584134380896374313338034174932622818776982226916870354318967895853133073765123285609571879677035459767391952641"
//        }},
//        {"nsh3":{
//        "x":"0.8082117603821325002908617227060252413608631688596372002901005892260468575516945549598175889248554661888198190459518028533806830846782743",
//        "y":"3.627445018269179851784136610544563699655240648716140701948991223547314528108896017569627732364179587013414120919395430893447900089464632"
//        }}
//        ]
//        }]


#if 0

    outf.seekg(std::ios_base::end);
    int I{-1}, c{0};
    for (auto e : ach) {
        outf.seekg(I--, std::ios_base::end);
        c = outf.peek();
        if (c != e) {
            if (I == -6-1) {
                outf.seekg(-5, std::ios_base::end);
                c = outf.peek();
                if (c == '\n') {
                    outf.put(',');
                    outf.put('\n');
                //outf << j.dump(0);
                outf << sg;
                    outf.put('}');
                    outf.put('\n');
                    outf.put('}');
                    outf.put(']');
                    outf.close();
                    return;
                }
            }
//            std::cout << "ABORT CPU::set_point_of_interest\n";
//            exit(-666);
        }
    }
    if (I == -static_cast<int>(sizeof(ch))-1) {
        outf.seekg(I+2, std::ios_base::end);
        c = outf.peek();
        if (c == '\n') {
            outf.put(',');
            outf.put('\n');
        outf << tg;
            outf.put('}');
            outf.put('\n');
            outf.put('}');
            outf.put(']');
            outf.close();
            return;
        }
    }

#endif
#if 0
#endif
#if 0
#define STR1(x) #x
#define STR2(x) STR1(x)


#define AFTERX(x) / ## #x ## / ## _json_pointer
#define XAFTERX(x) AFTERX(x)
    nlohmann::json &j0 = history["/" STR2(m_selected) "/"_json_pointer];
    j0 += j;
#endif


//    try {

//        nlohmann::json &j0 = history["/0/"_json_pointer];
//        j0 += j;
//        nlohmann::json &j1 = history["/1/"_json_pointer];
//        j1 += j;
//        nlohmann::json &j2 = history["/2/"_json_pointer];
//        j2 += j;
//        nlohmann::json &j3 = history["/3/"_json_pointer];
//        nlohmann::json &j4 = history["/4/"_json_pointer];
//        nlohmann::json &j5 = history["/5/"_json_pointer];
//    } catch (...) {

//    }{}
//    history += j;

#if 0
    /// Qt signals CAN return a value!!!!!!!!!!!!!!!!!

    //    Qt signals CAN return a value!!!!!!!!!!!!!!!!!

    //    Qt signals CAN return a value!!!!!!!!!!!!!!!!!

    //    Qt signals CAN return a value!!!!!!!!!!!!!!!!!
#endif

    ptr_QJsonTreeView->load();// QString {unique_filename.c_str()} );
    ptr_QJsonTreeView->update();
    ptr_QJsonTreeView->show();

    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
///////////////////////////////////////////////////////////////////////////////
