
#include "declarations_logisticMap_4.inc"


///********************************************************************************
//** Form generated from reading UI file 'logisticMap_4.ui'
//**
//** Created by: Qt User Interface Compiler version 5.12.1
//**
//** WARNING! All changes made in this file will be lost when recompiling UI file!
//********************************************************************************/

//#ifndef LOGISTICMAP_4_H
//#define LOGISTICMAP_4_H

//#include <QtCore/QVariant>
//#include <QtWidgets/QAction>
//#include <QtWidgets/QApplication>
//#include <QtWidgets/QCheckBox>
//#include <QtWidgets/QFrame>
//#include <QtWidgets/QGroupBox>
//#include <QtWidgets/QLabel>
//#include <QtWidgets/QMainWindow>
//#include <QtWidgets/QMenu>
//#include <QtWidgets/QMenuBar>
//#include <QtWidgets/QPlainTextEdit>
//#include <QtWidgets/QPushButton>
//#include <QtWidgets/QRadioButton>
//#include <QtWidgets/QSlider>
//#include <QtWidgets/QStatusBar>
//#include <QtWidgets/QToolBar>
//#include <QtWidgets/QWidget>
//#include "src/glwidget.h"
//#include "src/rate_label.h"

//QT_BEGIN_NAMESPACE

//class Ui_LogisticMap
//{
//public:
//    QAction *action_Save;
//    QAction *action_Load;
//    QAction *action_Quit;
//    QWidget *centralWidget;
//    OGLWidget *openGLWidget;
//    QWidget *Parameters;
//    QGroupBox *points_per_rowBox;
//    QLabel *nbaseLabel;
//    QLabel *nbaseLabel_2;
//    QLabel *nbaseLabel_3;
//    QLabel *nbaseLabel_4;
//    QLabel *n_total;
//    QLabel *relativePointDensity;
//    QPushButton *pb_n_base;
//    QPushButton *pb_n_exponent;
//    QLabel *nbaseLabel_5;
//    QLabel *sampleIncrease;
//    QGroupBox *numThreadsBox;
//    QPushButton *pb_numThreads;
//    QCheckBox *fixedAspectRatio;
//    QGroupBox *colorTimeSeries;
//    QRadioButton *blackWhiteRadio;
//    QRadioButton *colorRadio;
//    QLabel *points_per_row;
//    QCheckBox *checkBox_auto_save;
//    QPushButton *pb_re_compute;
//    QFrame *frame_Goto_R_2;
//    QPushButton *pb_Rate_Goto;
//    QLabel *label_R_goto;
//    QPushButton *pb_abort;
//    QFrame *fr_Music;
//    QLabel *mousePOSITION;
//    QPlainTextEdit *//plainTextEdit_rate;
//    Rate_Label *//lbl_rate;
//    QGroupBox *groupBox_Options;
//    QFrame *fr_param_play;
//    QFrame *fr_to;
//    QPushButton *pb_to;
//    QLabel *lbl_to;
//    QFrame *fr_from;
//    QPushButton *pb_from;
//    QLabel *lbl_from;
//    QFrame *fr_num_notes;
//    QPushButton *pb_num_notes;
//    QLabel *lbl_num_notes;
//    QFrame *frame_Tone;
//    QLabel *label_tone;
//    QSlider *horizontalSlider_ms;
//    QLabel *label_ms;
//    QLabel *label_ms_lbl;
//    QPushButton *pb_playMusic;
//    QPushButton *pb_cancel;
//    QPushButton *lineEdit_Rate_Play;
//    QRadioButton *rb_playRate;
//    QRadioButton *rb_playRows;
//    QToolBar *mainToolBar;
//    QStatusBar *statusBar;
//    QMenuBar *menuBar;
//    QMenu *menuLogisticMap;

    void setupUi(LMap *LogisticMap)
    {
#include "definitions_logisticMap_4.inc"
        if (LogisticMap->objectName().isEmpty())
            LogisticMap->setObjectName(QString::fromUtf8("LogisticMap"));
        LogisticMap->resize(1371, 1198);
        LogisticMap->setMouseTracking(true);
//        action_Save = new QAction(LogisticMap);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
//        action_Load = new QAction(LogisticMap);
        action_Load->setObjectName(QString::fromUtf8("action_Load"));
//        action_Quit = new QAction(LogisticMap);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
//        centralWidget = new QWidget(LogisticMap);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
//        openGLWidget = new OGLWidget(centralWidget);


//        frameOGL = new OGLframe(centralWidget);
        frameOGL->setObjectName(QString::fromUtf8("frameOGL"));
        frameOGL->setGeometry(QRect(0, 0, 9640, 640));
        frameOGL->setFrameShape(QFrame::StyledPanel);
        frameOGL->setFrameShadow(QFrame::Raised);


        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(20, 20, 960, 600));
        openGLWidget->setMinimumSize(QSize(96, 60));
        openGLWidget->setMouseTracking(true);
//        Parameters = new QWidget(centralWidget);
        Parameters->setObjectName(QString::fromUtf8("Parameters"));
        Parameters->setGeometry(QRect(1000, 0, 372, 833));//, 801));
        Parameters->setMinimumSize(QSize(60, 40));
        Parameters->setMouseTracking(true);
//        points_per_rowBox = new QGroupBox(Parameters);
        points_per_rowBox->setObjectName(QString::fromUtf8("points_per_rowBox"));
        points_per_rowBox->setGeometry(QRect(0, 430, 370, 281));
//        nbaseLabel = new QLabel(points_per_rowBox);
        nbaseLabel->setObjectName(QString::fromUtf8("nbaseLabel"));
        nbaseLabel->setGeometry(QRect(10, 30, 109, 24));
//        nbaseLabel_2 = new QLabel(points_per_rowBox);
        nbaseLabel_2->setObjectName(QString::fromUtf8("nbaseLabel_2"));
        nbaseLabel_2->setGeometry(QRect(10, 90, 109, 24));
//        nbaseLabel_3 = new QLabel(points_per_rowBox);
        nbaseLabel_3->setObjectName(QString::fromUtf8("nbaseLabel_3"));
        nbaseLabel_3->setGeometry(QRect(10, 239, 109, 24));
//        nbaseLabel_4 = new QLabel(points_per_rowBox);
        nbaseLabel_4->setObjectName(QString::fromUtf8("nbaseLabel_4"));
        nbaseLabel_4->setGeometry(QRect(10, 150, 109, 24));
//        n_total = new QLabel(points_per_rowBox);
        n_total->setObjectName(QString::fromUtf8("n_total"));
        n_total->setGeometry(QRect(120, 230, 250, 40));
        n_total->setMinimumSize(QSize(250, 40));
        n_total->setMaximumSize(QSize(500, 40));
//        relativePointDensity = new QLabel(points_per_rowBox);
        relativePointDensity->setObjectName(QString::fromUtf8("relativePointDensity"));
        relativePointDensity->setGeometry(QRect(120, 140, 250, 40));
        relativePointDensity->setMinimumSize(QSize(250, 40));
        relativePointDensity->setMaximumSize(QSize(500, 40));
//        pb_n_base = new QPushButton(points_per_rowBox);
        pb_n_base->setObjectName(QString::fromUtf8("pb_n_base"));
        pb_n_base->setGeometry(QRect(120, 30, 129, 32));
//        pb_n_exponent = new QPushButton(points_per_rowBox);
        pb_n_exponent->setObjectName(QString::fromUtf8("pb_n_exponent"));
        pb_n_exponent->setGeometry(QRect(120, 90, 129, 32));
//        nbaseLabel_5 = new QLabel(points_per_rowBox);
        nbaseLabel_5->setObjectName(QString::fromUtf8("nbaseLabel_5"));
        nbaseLabel_5->setGeometry(QRect(10, 190, 109, 24));
//        sampleIncrease = new QLabel(points_per_rowBox);
        sampleIncrease->setObjectName(QString::fromUtf8("sampleIncrease"));
        sampleIncrease->setGeometry(QRect(120, 180, 250, 40));
        sampleIncrease->setMinimumSize(QSize(250, 40));
        sampleIncrease->setMaximumSize(QSize(500, 40));
//        numThreadsBox = new QGroupBox(Parameters);
        numThreadsBox->setObjectName(QString::fromUtf8("numThreadsBox"));
        numThreadsBox->setGeometry(QRect(0, 132, 370, 71));
        numThreadsBox->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
//        pb_numThreads = new QPushButton(numThreadsBox);
        pb_numThreads->setObjectName(QString::fromUtf8("pb_numThreads"));
        pb_numThreads->setGeometry(QRect(120, 33, 129, 32));
//        fixedAspectRatio = new QCheckBox(Parameters);
        fixedAspectRatio->setObjectName(QString::fromUtf8("fixedAspectRatio"));
        fixedAspectRatio->setGeometry(QRect(20, 90, 461, 30));
//        colorTimeSeries = new QGroupBox(Parameters);
        colorTimeSeries->setObjectName(QString::fromUtf8("colorTimeSeries"));
        colorTimeSeries->setGeometry(QRect(0, 0, 370, 80));
//        blackWhiteRadio = new QRadioButton(colorTimeSeries);
        blackWhiteRadio->setObjectName(QString::fromUtf8("blackWhiteRadio"));
        blackWhiteRadio->setGeometry(QRect(10, 40, 211, 30));
        blackWhiteRadio->setAutoFillBackground(true);
        blackWhiteRadio->setChecked(true);
//        colorRadio = new QRadioButton(colorTimeSeries);
        colorRadio->setObjectName(QString::fromUtf8("colorRadio"));
        colorRadio->setGeometry(QRect(260, 40, 91, 30));
        colorRadio->setAutoFillBackground(true);
//        points_per_row = new QLabel(Parameters);
        points_per_row->setObjectName(QString::fromUtf8("points_per_row"));
        points_per_row->setGeometry(QRect(0, 210, 370, 211));
        points_per_row->setFrameShape(QFrame::StyledPanel);
        points_per_row->setFrameShadow(QFrame::Raised);
//        checkBox_auto_save = new QCheckBox(Parameters);
        checkBox_auto_save->setObjectName(QString::fromUtf8("checkBox_auto_save"));
        checkBox_auto_save->setGeometry(QRect(120, 720, 121, 30));
        checkBox_auto_save->setChecked(true);
//        pb_re_compute = new QPushButton(Parameters);
        pb_re_compute->setObjectName(QString::fromUtf8("pb_re_compute"));
        pb_re_compute->setGeometry(QRect(0, 720, 101, 32));
        pb_re_compute->setAutoFillBackground(false);
        pb_re_compute->setStyleSheet(QString::fromUtf8(""));
        pb_re_compute->setFlat(false);
//        frame_Goto_R_2 = new QFrame(Parameters);
        frame_Goto_R_2->setObjectName(QString::fromUtf8("frame_Goto_R_2"));
        frame_Goto_R_2->setGeometry(QRect(0, 760, 521, 70));//, 38));
        frame_Goto_R_2->setFrameShape(QFrame::NoFrame);
        frame_Goto_R_2->setFrameShadow(QFrame::Plain);
        frame_Goto_R_2->setLineWidth(0);
//        pb_Rate_Goto = new QPushButton(frame_Goto_R_2);
        pb_Rate_Goto->setObjectName(QString::fromUtf8("pb_Rate_Goto"));
        //pb_Rate_Goto->setGeometry(QRect(110, 0, 261, 32));
        pb_Rate_Goto->setGeometry(QRect(110, 15, 261, 32));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pb_Rate_Goto->sizePolicy().hasHeightForWidth());
        pb_Rate_Goto->setSizePolicy(sizePolicy);
        pb_Rate_Goto->setMaximumSize(QSize(400, 16777215));
        pb_Rate_Goto->setStyleSheet(QString::fromUtf8("text-align:left;"));
//        label_R_goto = new QLabel(frame_Goto_R_2);
        label_R_goto->setObjectName(QString::fromUtf8("label_R_goto"));
        label_R_goto->setGeometry(QRect(0, 0, 108, 63));//, 31));
//        pb_abort = new QPushButton(Parameters);
        pb_abort->setObjectName(QString::fromUtf8("pb_abort"));
        pb_abort->setGeometry(QRect(250, 720, 121, 32));
        pb_abort->setAutoFillBackground(false);
        pb_abort->setStyleSheet(QString::fromUtf8("QPushButton#pb_re_compute {\n"
"    background-color: red;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-radius: 10px;\n"
"    border-color: beige;\n"
"    font: bold 14px;\n"
"    min-width: 10em;\n"
"    padding: 6px;\n"
"}"));
        pb_abort->setFlat(false);
//        fr_Music = new QFrame(centralWidget);
        fr_Music->setObjectName(QString::fromUtf8("fr_Music"));
        fr_Music->setGeometry(QRect(20, 630, 971, 231));
        //fr_Music->setGeometry(QRect(20, 630, 971, 431));
        fr_Music->setStyleSheet(QString::fromUtf8("text-align:left;"));
//        mousePOSITION = new QLabel(fr_Music);
        mousePOSITION->setObjectName(QString::fromUtf8("mousePOSITION"));
//        mousePOSITION->setGeometry(QRect(660, 0, 301, 151));
        mousePOSITION->setGeometry(QRect(621, 0, 349, 231));
//        mousePOSITION->setInputMethodHints(Qt::ImhMultiLine|Qt::ImhPreferLatin);
//        mousePOSITION->setStyleSheet(QString::fromUtf8("text-align:left;"));

        mousePOSITION->setFrameStyle(QFrame::Panel | QFrame::Sunken);
//        mousePOSITION->setText("first line\nsecond line");
        mousePOSITION->setAlignment(Qt::AlignTop | Qt::AlignLeft);


//        groupBox_Options = new QGroupBox(fr_Music);
        groupBox_Options->setObjectName(QString::fromUtf8("groupBox_Options"));
        groupBox_Options->setGeometry(QRect(0, 0, 621, 221));
//        fr_param_play = new QFrame(groupBox_Options);
        fr_param_play->setObjectName(QString::fromUtf8("fr_param_play"));
        fr_param_play->setGeometry(QRect(130, 70, 501, 42));
        fr_param_play->setFrameShape(QFrame::NoFrame);
        fr_param_play->setFrameShadow(QFrame::Plain);
        fr_param_play->setLineWidth(0);
//        fr_to = new QFrame(fr_param_play);
        fr_to->setObjectName(QString::fromUtf8("fr_to"));
        fr_to->setGeometry(QRect(152, 0, 131, 41));
        fr_to->setFrameShape(QFrame::NoFrame);
        fr_to->setFrameShadow(QFrame::Plain);
        fr_to->setLineWidth(0);
//        pb_to = new QPushButton(fr_to);
        pb_to->setObjectName(QString::fromUtf8("pb_to"));
        pb_to->setGeometry(QRect(50, 5, 71, 32));
//        lbl_to = new QLabel(fr_to);
        lbl_to->setObjectName(QString::fromUtf8("lbl_to"));
        lbl_to->setGeometry(QRect(8, 10, 51, 24));
//        fr_from = new QFrame(fr_param_play);
        fr_from->setObjectName(QString::fromUtf8("fr_from"));
        fr_from->setGeometry(QRect(0, 0, 151, 41));
        fr_from->setFrameShape(QFrame::NoFrame);
        fr_from->setFrameShadow(QFrame::Plain);
        fr_from->setLineWidth(0);
//        pb_from = new QPushButton(fr_from);
        pb_from->setObjectName(QString::fromUtf8("pb_from"));
        pb_from->setGeometry(QRect(70, 5, 71, 32));
//        lbl_from = new QLabel(fr_from);
        lbl_from->setObjectName(QString::fromUtf8("lbl_from"));
        lbl_from->setGeometry(QRect(2, 10, 71, 24));
//        fr_num_notes = new QFrame(fr_param_play);
        fr_num_notes->setObjectName(QString::fromUtf8("fr_num_notes"));
        fr_num_notes->setGeometry(QRect(290, 0, 211, 41));
        fr_num_notes->setFrameShape(QFrame::NoFrame);
        fr_num_notes->setFrameShadow(QFrame::Plain);
        fr_num_notes->setLineWidth(0);
//        pb_num_notes = new QPushButton(fr_num_notes);
        pb_num_notes->setObjectName(QString::fromUtf8("pb_num_notes"));
        pb_num_notes->setGeometry(QRect(90, 5, 111, 32));
//        lbl_num_notes = new QLabel(fr_num_notes);
        lbl_num_notes->setObjectName(QString::fromUtf8("lbl_num_notes"));
        lbl_num_notes->setGeometry(QRect(0, 10, 81, 24));
//        frame_Tone = new QFrame(groupBox_Options);
        frame_Tone->setObjectName(QString::fromUtf8("frame_Tone"));
        frame_Tone->setGeometry(QRect(0, 170, 351, 56));
        frame_Tone->setFrameShape(QFrame::NoFrame);
        frame_Tone->setFrameShadow(QFrame::Plain);
        frame_Tone->setLineWidth(0);
//        label_tone = new QLabel(frame_Tone);
        label_tone->setObjectName(QString::fromUtf8("label_tone"));
        label_tone->setGeometry(QRect(0, 0, 350, 24));
//        horizontalSlider_ms = new QSlider(frame_Tone);
        horizontalSlider_ms->setObjectName(QString::fromUtf8("horizontalSlider_ms"));
        horizontalSlider_ms->setGeometry(QRect(0, 20, 200, 32));
        sizePolicy.setHeightForWidth(horizontalSlider_ms->sizePolicy().hasHeightForWidth());
        horizontalSlider_ms->setSizePolicy(sizePolicy);
        horizontalSlider_ms->setMinimumSize(QSize(200, 32));
        horizontalSlider_ms->setMaximumSize(QSize(200, 32));
        horizontalSlider_ms->setInputMethodHints(Qt::ImhDigitsOnly);
        horizontalSlider_ms->setMinimum(50);
        horizontalSlider_ms->setMaximum(500);
        horizontalSlider_ms->setSliderPosition(116);
        horizontalSlider_ms->setOrientation(Qt::Horizontal);
        horizontalSlider_ms->setTickPosition(QSlider::TicksBothSides);
//        label_ms = new QLabel(frame_Tone);
        label_ms->setObjectName(QString::fromUtf8("label_ms"));
        label_ms->setGeometry(QRect(220, 25, 51, 24));
//        label_ms_lbl = new QLabel(frame_Tone);
        label_ms_lbl->setObjectName(QString::fromUtf8("label_ms_lbl"));
        label_ms_lbl->setGeometry(QRect(270, 25, 41, 24));
//        pb_playMusic = new QPushButton(groupBox_Options);
        pb_playMusic->setObjectName(QString::fromUtf8("pb_playMusic"));
        pb_playMusic->setGeometry(QRect(10, 130, 129, 32));
        pb_playMusic->setFocusPolicy(Qt::StrongFocus);
        pb_playMusic->setContextMenuPolicy(Qt::NoContextMenu);
//        pb_cancel = new QPushButton(groupBox_Options);
        pb_cancel->setObjectName(QString::fromUtf8("pb_cancel"));
        pb_cancel->setGeometry(QRect(190, 130, 129, 32));
//        lineEdit_Rate_Play = new QPushButton(groupBox_Options);
        lineEdit_Rate_Play->setObjectName(QString::fromUtf8("lineEdit_Rate_Play"));
        lineEdit_Rate_Play->setGeometry(QRect(137, 30, 400, 32));
        sizePolicy.setHeightForWidth(lineEdit_Rate_Play->sizePolicy().hasHeightForWidth());
        lineEdit_Rate_Play->setSizePolicy(sizePolicy);
        lineEdit_Rate_Play->setMaximumSize(QSize(400, 16777215));
        lineEdit_Rate_Play->setStyleSheet(QString::fromUtf8("text-align:left;"));
//        rb_playRate = new QRadioButton(groupBox_Options);
        rb_playRate->setObjectName(QString::fromUtf8("rb_playRate"));
        rb_playRate->setGeometry(QRect(0, 30, 131, 29));
//        rb_playRows = new QRadioButton(groupBox_Options);
        rb_playRows->setObjectName(QString::fromUtf8("rb_playRows"));
        rb_playRows->setGeometry(QRect(0, 70, 131, 41));
        LogisticMap->setCentralWidget(centralWidget);
//        mainToolBar = new QToolBar(LogisticMap);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        LogisticMap->addToolBar(Qt::TopToolBarArea, mainToolBar);
//        statusBar = new QStatusBar(LogisticMap);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        LogisticMap->setStatusBar(statusBar);
//        menuBar = new QMenuBar(LogisticMap);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1371, 28));
//        menuLogisticMap = new QMenu(menuBar);
        menuLogisticMap->setObjectName(QString::fromUtf8("menuLogisticMap"));
        LogisticMap->setMenuBar(menuBar);

        menuBar->addAction(menuLogisticMap->menuAction());
        menuLogisticMap->addSeparator();
        menuLogisticMap->addAction(action_Save);
        menuLogisticMap->addAction(action_Load);
        menuLogisticMap->addSeparator();
        menuLogisticMap->addSeparator();
        menuLogisticMap->addSeparator();
        menuLogisticMap->addAction(action_Quit);

        retranslateUi(LogisticMap);

        QMetaObject::connectSlotsByName(LogisticMap);
    } // setupUi

    void retranslateUi(QMainWindow *LogisticMap)
    {
        LogisticMap->setWindowTitle(QApplication::translate("LogisticMap", "Logistic Map by PLNash", nullptr));
        action_Save->setText(QApplication::translate("LogisticMap", "&Save", nullptr));
        action_Load->setText(QApplication::translate("LogisticMap", "&Load", nullptr));
        action_Quit->setText(QApplication::translate("LogisticMap", "&Quit", nullptr));
        points_per_rowBox->setTitle(QApplication::translate("LogisticMap", "Parameters:", nullptr));
        nbaseLabel->setText(QApplication::translate("LogisticMap", "N_base = ", nullptr));
        nbaseLabel_2->setText(QApplication::translate("LogisticMap", "n      =", nullptr));
        nbaseLabel_3->setText(QApplication::translate("LogisticMap", "N      = ", nullptr));
        nbaseLabel_4->setText(QApplication::translate("LogisticMap", "D      =", nullptr));
        n_total->setText(QApplication::translate("LogisticMap", "1111", nullptr));
        relativePointDensity->setText(QApplication::translate("LogisticMap", "12345", nullptr));
        pb_n_base->setText(QApplication::translate("LogisticMap", "999", nullptr));
        pb_n_exponent->setText(QApplication::translate("LogisticMap", "1.15", nullptr));
        nbaseLabel_5->setText(QApplication::translate("LogisticMap", "D^n    =", nullptr));
        sampleIncrease->setText(QApplication::translate("LogisticMap", "12345", nullptr));
        numThreadsBox->setTitle(QApplication::translate("LogisticMap", "Number of CPU Threads", nullptr));
        pb_numThreads->setText(QApplication::translate("LogisticMap", "27", nullptr));
        fixedAspectRatio->setText(QApplication::translate("LogisticMap", "Fixed Aspect Ratio", nullptr));
        colorTimeSeries->setTitle(QApplication::translate("LogisticMap", "Color of Time Series", nullptr));
        blackWhiteRadio->setText(QApplication::translate("LogisticMap", "Black and White", nullptr));
        colorRadio->setText(QApplication::translate("LogisticMap", "Color", nullptr));
        points_per_row->setText(QApplication::translate("LogisticMap", "<html><head/><body><p>N = number of population </p><p>     values per pixel row</p><p>  = N_base * D^n,</p><p>D = change in relative point</p><p>    density when ZOOMING in/out</p></body></html>", nullptr));
        checkBox_auto_save->setText(QApplication::translate("LogisticMap", "AutoSave", nullptr));
        pb_re_compute->setText(QApplication::translate("LogisticMap", "ReCalc", nullptr));
        pb_Rate_Goto->setText(QString());
        label_R_goto->setText(QApplication::translate("LogisticMap", "GoTo/Play\n R =", nullptr));
        pb_abort->setText(QApplication::translate("LogisticMap", "Abort", nullptr));
        fr_Music->setProperty("title", QVariant(QApplication::translate("LogisticMap", "Music:", nullptr)));
//mousePOSITION->setText(QApplication::translate("LogisticMap", "<html><head/><body><p>Screen Mouse:</p><p>x= y = </p></body></html>", nullptr));
        //lbl_rate->setText(QString());
        groupBox_Options->setTitle(QApplication::translate("LogisticMap", "Music", nullptr));
        pb_to->setText(QApplication::translate("LogisticMap", "366", nullptr));
        lbl_to->setText(QApplication::translate("LogisticMap", "To:", nullptr));
        pb_from->setText(QApplication::translate("LogisticMap", "364", nullptr));
        lbl_from->setText(QApplication::translate("LogisticMap", "From:", nullptr));
        pb_num_notes->setText(QApplication::translate("LogisticMap", "24", nullptr));
        lbl_num_notes->setText(QApplication::translate("LogisticMap", "#Notes:", nullptr));
        label_tone->setText(QApplication::translate("LogisticMap", "Tone duration (ms: 50 - 500)", nullptr));
        label_ms->setText(QApplication::translate("LogisticMap", "116", nullptr));
        label_ms_lbl->setText(QApplication::translate("LogisticMap", "ms", nullptr));
        pb_playMusic->setText(QApplication::translate("LogisticMap", "Play Music", nullptr));
        pb_cancel->setText(QApplication::translate("LogisticMap", "Cancel", nullptr));
        lineEdit_Rate_Play->setText(QString());
        rb_playRate->setText(QApplication::translate("LogisticMap", "Play Rate", nullptr));
        rb_playRows->setText(QApplication::translate("LogisticMap", "Play Rows", nullptr));
        menuLogisticMap->setTitle(QApplication::translate("LogisticMap", "&File", nullptr));
    } // retranslateUi

//};

//namespace Ui {
//    class LogisticMap: public Ui_LogisticMap {};
//} // namespace Ui

//QT_END_NAMESPACE

//#endif // LOGISTICMAP_4_H
