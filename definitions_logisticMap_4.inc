 _action_Save =  std::make_unique<QAction>(LogisticMap);
action_Save = _action_Save.get();


 _action_Load =  std::make_unique<QAction>(LogisticMap);
action_Load = _action_Load.get();


 _action_Quit =  std::make_unique<QAction>(LogisticMap);
action_Quit = _action_Quit.get();


 _centralWidget =  std::make_unique</*QWidget*/ MyCentralWidget>(LogisticMap);
centralWidget = _centralWidget.get();



_frameOGL = std::make_unique<OGLframe>(centralWidget);
frameOGL = _frameOGL.get();



 _openGLWidget =  std::make_unique<OGLWidget>(LogisticMap, /*centralWidget*/ frameOGL);
openGLWidget = _openGLWidget.get();


 _Parameters =  std::make_unique<QWidget>(centralWidget);
Parameters = _Parameters.get();


 _points_per_rowBox =  std::make_unique<QGroupBox>(Parameters);
points_per_rowBox = _points_per_rowBox.get();


 _nbaseLabel =  std::make_unique<QLabel>(points_per_rowBox);
nbaseLabel = _nbaseLabel.get();


 _nbaseLabel_2 =  std::make_unique<QLabel>(points_per_rowBox);
nbaseLabel_2 = _nbaseLabel_2.get();


 _nbaseLabel_3 =  std::make_unique<QLabel>(points_per_rowBox);
nbaseLabel_3 = _nbaseLabel_3.get();


 _nbaseLabel_4 =  std::make_unique<QLabel>(points_per_rowBox);
nbaseLabel_4 = _nbaseLabel_4.get();


 _n_total =  std::make_unique<QLabel>(points_per_rowBox);
n_total = _n_total.get();


 _relativePointDensity =  std::make_unique<QLabel>(points_per_rowBox);
relativePointDensity = _relativePointDensity.get();


 _pb_n_base =  std::make_unique<QPushButton>(points_per_rowBox);
pb_n_base = _pb_n_base.get();


 _pb_n_exponent =  std::make_unique<QPushButton>(points_per_rowBox);
pb_n_exponent = _pb_n_exponent.get();


 _nbaseLabel_5 =  std::make_unique<QLabel>(points_per_rowBox);
nbaseLabel_5 = _nbaseLabel_5.get();


 _sampleIncrease =  std::make_unique<QLabel>(points_per_rowBox);
sampleIncrease = _sampleIncrease.get();


 _numThreadsBox =  std::make_unique<QGroupBox>(Parameters);
numThreadsBox = _numThreadsBox.get();


 _pb_numThreads =  std::make_unique<QPushButton>(numThreadsBox);
pb_numThreads = _pb_numThreads.get();


 _fixedAspectRatio =  std::make_unique<QCheckBox>(Parameters);
fixedAspectRatio = _fixedAspectRatio.get();


 _colorTimeSeries =  std::make_unique<QGroupBox>(Parameters);
colorTimeSeries = _colorTimeSeries.get();


 _blackWhiteRadio =  std::make_unique<QRadioButton>(colorTimeSeries);
blackWhiteRadio = _blackWhiteRadio.get();


 _colorRadio =  std::make_unique<QRadioButton>(colorTimeSeries);
colorRadio = _colorRadio.get();


 _points_per_row =  std::make_unique<QLabel>(Parameters);
points_per_row = _points_per_row.get();


 _checkBox_auto_save =  std::make_unique<QCheckBox>(Parameters);
checkBox_auto_save = _checkBox_auto_save.get();


 _pb_re_compute =  std::make_unique<QPushButton>(Parameters);
pb_re_compute = _pb_re_compute.get();


 _frame_Goto_R_2 =  std::make_unique<QFrame>(Parameters);
frame_Goto_R_2 = _frame_Goto_R_2.get();


 _pb_Rate_Goto =  std::make_unique<QPushButton>(frame_Goto_R_2);
pb_Rate_Goto = _pb_Rate_Goto.get();


 _label_R_goto =  std::make_unique<QLabel>(frame_Goto_R_2);
label_R_goto = _label_R_goto.get();


 _pb_abort =  std::make_unique<QPushButton>(Parameters);
pb_abort = _pb_abort.get();


 _fr_Music =  std::make_unique<QFrame>(centralWidget);
fr_Music = _fr_Music.get();


 _mousePOSITION =  std::make_unique<QLabel>(fr_Music);
mousePOSITION = _mousePOSITION.get();


// _plainTextEdit_rate =  std::make_unique<QPlainTextEdit>(fr_Music);
//plainTextEdit_rate = _plainTextEdit_rate.get();


// _lbl_rate =  std::make_unique<Rate_Label>(fr_Music);
//lbl_rate = _lbl_rate.get();


 _groupBox_Options =  std::make_unique<QGroupBox>(fr_Music);
groupBox_Options = _groupBox_Options.get();


 _fr_param_play =  std::make_unique<QFrame>(groupBox_Options);
fr_param_play = _fr_param_play.get();


 _fr_to =  std::make_unique<QFrame>(fr_param_play);
fr_to = _fr_to.get();


 _pb_to =  std::make_unique<QPushButton>(fr_to);
pb_to = _pb_to.get();


 _lbl_to =  std::make_unique<QLabel>(fr_to);
lbl_to = _lbl_to.get();


 _fr_from =  std::make_unique<QFrame>(fr_param_play);
fr_from = _fr_from.get();


 _pb_from =  std::make_unique<QPushButton>(fr_from);
pb_from = _pb_from.get();


 _lbl_from =  std::make_unique<QLabel>(fr_from);
lbl_from = _lbl_from.get();


 _fr_num_notes =  std::make_unique<QFrame>(fr_param_play);
fr_num_notes = _fr_num_notes.get();


 _pb_num_notes =  std::make_unique<QPushButton>(fr_num_notes);
pb_num_notes = _pb_num_notes.get();


 _lbl_num_notes =  std::make_unique<QLabel>(fr_num_notes);
lbl_num_notes = _lbl_num_notes.get();


 _frame_Tone =  std::make_unique<QFrame>(groupBox_Options);
frame_Tone = _frame_Tone.get();


 _label_tone =  std::make_unique<QLabel>(frame_Tone);
label_tone = _label_tone.get();


 _horizontalSlider_ms =  std::make_unique<QSlider>(frame_Tone);
horizontalSlider_ms = _horizontalSlider_ms.get();


 _label_ms =  std::make_unique<QLabel>(frame_Tone);
label_ms = _label_ms.get();


 _label_ms_lbl =  std::make_unique<QLabel>(frame_Tone);
label_ms_lbl = _label_ms_lbl.get();


 _pb_playMusic =  std::make_unique<QPushButton>(groupBox_Options);
pb_playMusic = _pb_playMusic.get();


 _pb_cancel =  std::make_unique<QPushButton>(groupBox_Options);
pb_cancel = _pb_cancel.get();


 _lineEdit_Rate_Play =  std::make_unique<xxxQLineEdit>(groupBox_Options);
lineEdit_Rate_Play = _lineEdit_Rate_Play.get();


 _rb_playRate =  std::make_unique<QRadioButton>(groupBox_Options);
rb_playRate = _rb_playRate.get();


 _rb_playRows =  std::make_unique<QRadioButton>(groupBox_Options);
rb_playRows = _rb_playRows.get();


 _mainToolBar =  std::make_unique<QToolBar>(LogisticMap);
mainToolBar = _mainToolBar.get();


 _statusBar =  std::make_unique<QStatusBar>(LogisticMap);
statusBar = _statusBar.get();


 _menuBar =  std::make_unique<QMenuBar>(LogisticMap);
menuBar = _menuBar.get();


 _menuLogisticMap =  std::make_unique<QMenu>(menuBar);
menuLogisticMap = _menuLogisticMap.get();


