//qjsontreeview.h
/*
#include "QJsonModel/qjsontreeview.h"
#include "../QJsonModel/qjsontreeview.h"
#include "qjsontreeview.h"
*/
#ifndef QJSONTREEVIEW_H
#define QJSONTREEVIEW_H

#include <QObject>
#include <QTreeView>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QListWidget>

#include "qjsonmodel.h"


class LMap;
#include <QCloseEvent>

///////////////////////////////////////////////////////////////////////////////
//friend class LogisticMap;

class QJsonTreeView : public QTreeView
{
    Q_OBJECT
    friend LMap;
public:
    //QJsonTreeView();
    QJsonTreeView(QWidget *parent = nullptr);
    virtual ~QJsonTreeView() override {
        //if (pmodel != nullptr) delete pmodel;
    }
    bool load(const QString& fileName) {
        bool ret =  model.load(fileName);
        update();
        return ret;
    }
    bool load(void) {
        QFile file(uniqueFilename);
        if (file.isOpen()) {
            file.close();
        }
        bool ret =  model.load(uniqueFilename);
        update();
        //repaint();
        return ret;
    }
protected:
//     void closeEvent(QCloseEvent *event) override;
protected:
    LMap *ptr_LMap{nullptr};
    void setCPU(LMap *_ptr_LMap){ptr_LMap=_ptr_LMap;}
    void setFilename(QString const &_uniqueFilename){uniqueFilename=_uniqueFilename;}
    //void mousePressEvent(QMouseEvent *event) override;
///////////////////////////////////////////////////////////////////////////////
    //QJsonModel *pmodel{nullptr};
    //std::unique_ptr<QJsonModel> pmodel{nullptr};
    int selectedFromQTreeView{-1};
    QJsonModel model;//{};
    QString uniqueFilename{""};

public slots:
    void updateActions();
    void on_Clicked(const QModelIndex&);
};

#endif // QJSONTREEVIEW_H
