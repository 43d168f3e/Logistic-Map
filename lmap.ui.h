/********************************************************************************
** Form generated from reading UI file 'lmap.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LMAP_H
#define LMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LMap
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LMap)
    {
        if (LMap->objectName().isEmpty())
            LMap->setObjectName(QStringLiteral("LMap"));
        LMap->resize(400, 300);
        menuBar = new QMenuBar(LMap);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        LMap->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LMap);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LMap->addToolBar(mainToolBar);
        centralWidget = new QWidget(LMap);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LMap->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(LMap);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LMap->setStatusBar(statusBar);

        retranslateUi(LMap);

        QMetaObject::connectSlotsByName(LMap);
    } // setupUi

    void retranslateUi(QMainWindow *LMap)
    {
        LMap->setWindowTitle(QApplication::translate("LMap", "LMap", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LMap: public Ui_LMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LMAP_H
