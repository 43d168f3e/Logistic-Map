
#if !defined(LMAP_H_741bc550b53c48ab80a4232466ea81af)
#define	  LMAP_H_741bc550b53c48ab80a4232466ea81af

#include "global.h"
#include "mycentralwidget.h"


#include <iostream>
#include <fstream>
#include <type_traits>
#include <cstring>
#include <string>
#include <iomanip>
#include <cerrno>
#include <cfenv>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <functional>
#include <stdexcept>
#include <algorithm>

#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QPainter>
#include <QPaintEvent>

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

//using xxxQLineEdit = QPushButton;
using xxxQLineEdit = QLabel;
//using xxxQLineEdit = QLineEdit;//dies
//using xxxQLineEdit = QTextEdit; error: no member named 'text' in 'QTextEdit'

//namespace Ui {
//class LMap;
//}

//namespace Ui {
//class LMap;
//}

//#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

//typedef QRgb
//An ARGB quadruplet on the format #AARRGGBB, equivalent to an unsigned int.
//QT += gui

#include <QColor>

#include "src/data.h"
#include "src/oglwidget.h"
//using Rate_Label = QLabel;
#include "src/rate_label.h"

class playRows_Controller;
class playRows_Worker;
class QJsonTreeView;
class Play_Music_ROOT;
///////////////////////////////////////////////////////////////////////////////
//static constexpr const long double R_try{3.569945671870944901842};
//static constexpr const double R_try1{3.864};
//static constexpr const double R_try2{3.828714};
//static constexpr const double R_try{3.569945671870944901842};
//static constexpr const long double R_music{3.450918196994991652754590984974958263772954924874791318864774624373956594323873121869782971619365609348914858096828046744574290484140232};
///////////////////////////////////////////////////////////////////////////////
class LMap : public QMainWindow
{
    Q_OBJECT

    friend OGLWidget;
    friend QJsonTreeView;
    friend playRows_Controller;
    friend playRows_Worker;
    friend class Assemble_block;
    friend Play_Music_ROOT;

#include "logisticMap_4.ui.inc"

public:
    static QWaitCondition t1_condv;
    explicit LMap(const char* argv1, QWidget *parent = nullptr);
    ~LMap() override;
    void keyPressEvent(QKeyEvent *event) override;
///////////////////////////////////////////////////////////////////////////////
public:
    enum class COLOR {
        BlackAndWhite = 0,
        RedGreenBlue_FromWaveLength = 1
    } m_color{COLOR::BlackAndWhite};
    void InitializeMpfRect(/*QSize const &size*/ void);
protected:
    void abort(void);
    void abort_ON(void);
    void abort_OFF(void);
    void close(void);
    void closeEvent(QCloseEvent *event) override;
    void compute(void);//QSize const & size) ;
    void ComputeMap(void);
    void compute_map_threadCaller(void);
    friend void compute_independentThread();
///////////////////////////////////////////////////////////////////////////////
/// get
///////////////////////////////////////////////////////////////////////////////
    bool get_abort_play_rows(void) const { return b_abort_play_rows;}
    QRgb get_chaos_threshold_rate_get_screen_Row_y() const;
    std::string get_dialog_Play_Rate_mpf(void);//bool b_Rate_Play);
    //mpf_class get_dialog_Play_Rate_mpf(bool b_Rate_Play);
    bool get_fixedAspectRatio(void) const { return b_fixedAspectRatio;}
    //static int get_number_KEYS(void) {return g_number_KEYS;}
    int  get_milliSeconds(void) const { return lLength_ms;}
    QRgb get_FROM(void) const { return m_FROM;}
    QRgb get_TO  (void) const { return m_TO;}
    QRgb get_NUM_NOTES(void) const { return m_NUM_NOTES;}
    double get_increase_sample_size_by(void) const;
    QRgb get_num_iterations_base(void) const;
    QRgb get_num_iterations(void) const;
    QRgb get_num_THREADS(void) const { return m_num_THREADS;}
    std::string get_rate_string( QRgb row_y, bool prefix=false) const;
    double get_relativeDensity_exponent(void) const;
    double get_relativeDensity(void) const;
    std::string get_relativeDensity_str(void) const;
    QString get_rate_QString( QRgb row_y, bool prefix=false) const;
    std::uint32_t get_screen_Row_y( mpf_class const &y_t ) const;
    std::uint32_t get_screen_Col_x( mpf_class const &x_t ) const;
    std::size_t get_selected(void) const { return m_selected;}
    mpf_class get_y_mpf( QRgb row_y) const;
///////////////////////////////////////////////////////////////////////////////
    //void gotoThisRate(mpf_class const &r);
    void gotoThisRate(std::string const &s);
    void InitializeConnections(void);
    void music_threadCaller(bool b_Rate_Play);
    friend void music_independentThread(bool b_Rate_Play);
    void newColor(int i);
///////////////////////////////////////////////////////////////////////////////
    void set_fixedAspectRatio(bool res) {b_fixedAspectRatio = res;}
    void newRegion( QPoint const &pos1, QPoint const &pos2);
    //void on_action_Save_triggered(void);//http://doc.qt.io/qt-5/designer-using-a-ui-file.html#automatic-connections
    void onSelect(std::size_t selected );
    void Play_Music(bool b_Rate_Play);
    void play_rubberBand_This_Rect(QRect const &rect);
    friend void play_rubberBand_Rect_independentThread(void);
    void play_rubberBand_Rect(void);
    void playROWS_ON(void);
    void playROWS_OFF(void);
    void playROWS_and_cancel_OFF(void);
    void playThisRate(mpf_class const &r);
    void record_history(void);
    void redraw(QSize size, bool useColor);
    void ReleaseMouse(void);
    void requestRedraw(QPoint const &m_mseDn, QPoint const &m_mseUp, QSize const & size, double const &aspectRatio);
    //void save(QString const &fileName);
    void save_png(QSize const &size, char const *filename = nullptr);
///////////////////////////////////////////////////////////////////////////////
/// set
///////////////////////////////////////////////////////////////////////////////
    void set_point_of_interest( QPoint const &pos, std::string const& text) ;
    void setDouble_relativeDensity_exponent(double f);
    void setIntegerITERATION_NUM(QRgb n);//{if (n>0 && n<20000) Data::vec_LogisticMap_Data::num_iterations_base() = n;}
    void setIntegerNumThreads(QRgb n) {

        size_t w = std::max(unsigned{1}, std::thread::hardware_concurrency());
        if (n>0 && n<w) m_num_THREADS = n;
    }
    void setFROM(QRgb n) {if (static_cast<int>(n)>=0) m_FROM =n<g_default___screen_height? n:g_default___screen_height-1;}
    void setTO  (QRgb n) {if (static_cast<int>(n)>=0) m_TO   =n<g_default___screen_height? n:g_default___screen_height-1;}
    void setNUM_NOTES(QRgb n) {if (static_cast<int>(n)>=1 && n<99999) m_NUM_NOTES = n;}
    void set_milliSeconds(int n);
    void set_Rate_to_Play( QPoint const &pos ) ;
    void set_selected(std::size_t n) { m_selected = n;}
///////////////////////////////////////////////////////////////////////////////
    void translate( QPoint const &pos);
    void translate( QPoint const &pos, QSize const &size );
    void updateAfterRenderedImage(void);
    void updateLabels(void);
///////////////////////////////////////////////////////////////////////////////
// dialog
        void gotoThisRate(void);
        void playThisRate(void);
        void setDouble_relativeDensity_exponent(void);
        void setIntegerFROM(void);
        void setIntegerITERATION_NUM(void);
        void setIntegerTO(void);
        void setIntegerNUM_NOTES(void);
        void setIntegerNumThreads(void);
///////////////////////////////////////////////////////////////////////////////
/// data
///////////////////////////////////////////////////////////////////////////////
    std::atomic<int> spi{0};
    std::shared_ptr<playRows_Controller> spR;
    mpf_class m_play_this_ROW_Rate{g_demo_Rate_s, NS_LogisticMap::prec, 10};
    QRgb m_play_this_ROW{364};
    std::vector< std::string > points_of_interest;
    std::string unique_filename;
    QString uniqueFilename;
    void get_uniqueFilename(void);
    std::string dtTemplate;
///////////////////////////////////////////////////////////////////////////////
///QTemporaryFile is used to create unique temporary files safely. The file itself is created by calling open().
///The name of the temporary file is guaranteed to be unique
///and the file will subsequently be removed upon destruction of the QTemporaryFile object.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
    QPixmap pixmap;
    QBrush background;
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//template<int width, int height>
//    struct programData {
//        QImage image{ QSize{ width , height }, QImage::Format_RGB32 };
//        unsigned char* buffer() {return image.bits();}
//    };
//    static programData<g_default___screen_width, g_default___screen_height> global_image;
///////////////////////////////////////////////////////////////////////////////
private:// more data
    std::size_t m_selected{0};
    QRgb m_num_THREADS{8};
    int lLength_ms{116};
    //LogisticMap::COLOR  m_color{LogisticMap::COLOR::BlackAndWhite};
    bool m_b_playRate{true};
    bool b_threadRunning{false};
    bool b_fixedAspectRatio{false};
    bool b_abort_play_rows{false};
    bool b_playingMusic{false};
    QString currentFile;
    QString qs_n_total{""};
    QRgb m_FROM{364};
    QRgb m_TO{366};
    QRgb m_NUM_NOTES{24};
    QJsonTreeView *ptr_QJsonTreeView{nullptr};
    QWaitCondition condition;
    bool restart{false};
///////////////////////////////////////////////////////////////////////////////
protected slots:
    void on_action_Save_triggered(void);//http://doc.qt.io/qt-5/designer-using-a-ui-file.html#automatic-connections
    void on__Clicked(void);
    //void onRate(std::shared_ptr<std::string const>s);
    void onSet_mouse_Text( QString const &mouse_xy);
    void on_Set_ms_Value(int);
    void on_Suicide(void);
    void on_Begin(void);
    void on_End(void);
    void pb_Rate_Goto_setText(QString const &qs);


///////////////////////////////////////////////////////////////////////////////
signals:
    void set_abort_play_rows(bool);
    void qs_rate(const QString &);
//    void play_rows(void);
//    void sig_cpr(std::shared_ptr<int>);
//    void sig_playRows(LogisticMap_Data_Structure_Ptr pv, QRgb num_iterationsBASE, double increase_sample_size_by,
//                  QRgb begin, QRgb end, QRgb num_notes, std::shared_ptr<int> ppr);
    void sig_playROWS(std::size_t);
    void sig_playThisRate(std::size_t);
    //void sendBlock(mpf_Block const &block);
//    void windowDoWork(void);
//    void updateMilliSeconds(int);
    void map(QImage const &image);//std::size_t const n, QRgb *buffer);
};


///////////////////////////////////////////////////////////////////////////////
//QColor gold("#ffd700");
static constexpr const char *Music_buttonstyle = R"(
QFrame#fr_Music {
    background-color: beige;
    border-style: outset;
    border-width: 2px;
    border-radius: 8px;
    border-color: rgb(0, 255, 0);
    color: red;
    font: bold 18px;
    min-width: 2em;
    padding: 6px;
    text-align:left;
}
)";


static constexpr const char *groupBox_Options_buttonstyle = R"(
QGroupBox#groupBox_Options {
    background-color: beige;
    border-style: outset;
    border-width: 2px;
    border-radius: 8px;
    border-color: rgb(0, 255, 0);
    color: red;
    font: bold 18px;
    min-width: 2em;
    padding: 6px;
    text-align:left;
}
)";



static constexpr const char *pb_Rate_Play_buttonstyle = R"(
xxxQLineEdit#lineEdit_Rate_Play {
    background-color: "#ffd700";
    border-style: outset;
    border-width: 2px;
    border-radius: 8px;
    border-color: rgb(0, 255, 0);
    color: red;
    font: bold 18px;
    min-width: 2em;
    padding: 6px;
    text-align:left;
}
)";

//static constexpr const char *pb_Rate_Play_buttonstyle = R"(
//QPushButton#lineEdit_Rate_Play {
//    background-color: "#ffd700";
//    border-style: outset;
//    border-width: 2px;
//    border-radius: 8px;
//    border-color: rgb(0, 255, 0);
//    color: red;
//    font: bold 18px;
//    min-width: 2em;
//    padding: 6px;
//    text-align:left;
//}
//QPushButton#lineEdit_Rate_Play:pressed {
//    background-color: rgb(255, 255, 255);
//    border-style: inset;
//    text-align:left;
//}
//)";

static constexpr const char *pb_playROWS_buttonstyle = R"(
QPushButton#pb_playMusic {
    background-color: "#ffd700";
    border-style: outset;
    border-width: 2px;
    border-radius: 8px;
    border-color: rgb(0, 255, 0);
    color: red;
    font: bold 18px;
    min-width: 2em;
    padding: 6px;
    text-align:left;
}
QPushButton#pb_playMusic:pressed {
    background-color: rgb(255, 255, 255);
    border-style: inset;
    text-align:left;
}
)";

//background-color: #A3C1DA; color: red;

//static constexpr const char *pb_playROWS_buttonstyle = R"(
//QPushButton#pb_playMusic {
//    background-color: red;
//    border-style: outset;
//    border-width: 2px;
//    border-radius: 8px;
//    border-color: beige;
//    font: bold 16px;
//    min-width: 10em;
//    padding: 6px;
//    text-align:left;
//}
//QPushButton#pb_playMusic:pressed {
//    background-color: rgb(255, 255, 255);
//    border-style: inset;
//    text-align:left;
//}
//)";



static constexpr const char *pb_Rate_Goto_buttonstyle = R"(
QPushButton#pb_Rate_Goto {
    background-color: "#ffd700";
    border-style: outset;
    border-width: 2px;
    border-radius: 8px;
    border-color: rgb(0, 0, 255);
    color: red;
    font: bold 18px;
    min-width: 2em;
    padding: 6px;
    text-align:left;
}
QPushButton#pb_Rate_Goto:pressed {
    background-color: beige;
    border-style: inset;
    text-align:left;
}
)";


static constexpr const char *pb_re_compute_buttonstyle = R"(
QPushButton#pb_re_compute {
    background-color: "#ffd700";
    border-style: outset;
    border-width: 2px;
    border-radius: 10px;
    border-color: blue;
    color: red;
    font: bold 18px;
    min-width: 1em;
    padding: 6px;
    text-align:center;
}
QPushButton#pb_re_compute:pressed {
    background-color: beige;
    border-style: inset;
    text-align:left;
}
)";
static constexpr const char *pb_re_compute_pressed_buttonstyle = R"(
QPushButton#pb_re_compute:pressed {
    background-color: rgb(224, 0, 0);
    border-style: inset;
}
)";//rgb(224, 0, 0)

#endif // LMAP_H_741bc550b53c48ab80a4232466ea81af
