#include "qjsontreeview.h"
#include "../lmap.h"

#include <pwd.h>
#include <unistd.h>
int getlogin_r(char *buf, size_t bufsize);

class Env{
    public:
    static std::string getUserName()
    {
        uid_t uid = geteuid ();
        struct passwd *pw = getpwuid (uid);
        if (pw) {
            return std::string(pw->pw_name);
        }
        else {
            static char buf[128];
            int res = getlogin_r(buf, sizeof(buf)/sizeof(buf[0]) );
            return std::string(buf);
        }
        return std::string{""};
    }
};
///////////////////////////////////////////////////////////////////////////////
QJsonTreeView::QJsonTreeView(QWidget *parent) :
    QTreeView{parent},
    model{}
{
    setSortingEnabled(false) ;
    this->setWindowTitle("LM History");
    this->setAttribute(Qt::WidgetAttribute::WA_QuitOnClose, true);
    auto flags = windowFlags();//save current configuration
    //your main configuration which do the trick
    //setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint );
// enable custom window hint
setWindowFlags( windowFlags() | Qt::CustomizeWindowHint);

// disable (but not hide) close button
setWindowFlags( windowFlags() & ~Qt::WindowCloseButtonHint);
//    setWindowFlags(flags);//restore

    QHeaderView *phv = QTreeView::header();
    phv->setSortIndicator(-1, Qt::AscendingOrder);
    phv->setMinimumSectionSize(400);
    phv->setSortIndicatorShown(true);
    phv->setHighlightSections(true);
    phv->setCascadingSectionResizes(true);
    phv->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);
#if 0
setSortIndicator(int logicalIndex, Qt::SortOrder order) - "logicalIndex may be -1, "
in which case no sort indicator will be shown and the model will return to its natural, unsorted order.

        s = QtCore.QSize(self.doc.idealWidth(), self.doc.size().height())
        index.model().setData(index, s, QtCore.Qt.SizeHintRole)
#endif



    this->resize(600,600);
//this->adjustSize();
    this->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->setSelectionBehavior (QAbstractItemView::SelectRows);
    this->setSelectionBehavior (QAbstractItemView::SelectRows);
    this->setObjectName(QStringLiteral("qjsontreeview"));
    this->setAlternatingRowColors(true);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setAnimated(false);
this->setColumnWidth(0, width()/3);
this->setColumnWidth(1, (2*width())/3);
    this->setAllColumnsShowFocus(true);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    setModel(&model);
    QStringList list{"Region","Parameters"};
    //model.setHorizontalHeaderLabels(list);
    connect(this, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_Clicked(const QModelIndex &)));

}
///////////////////////////////////////////////////////////////////////////////
void QJsonTreeView::updateActions() {
    bool hasSelection = !this->selectionModel()->selection().isEmpty();
    bool hasCurrent = this->selectionModel()->currentIndex().isValid();
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void QJsonTreeView::on_Clicked(const QModelIndex& I) {
    QModelIndex inx = I;
    int row{-1};
    QModelIndex selectedIndex;
    std::size_t selected = static_cast<std::size_t>(inx.row());
    QModelIndexList indexes = this->selectionModel()->selectedIndexes();
    if (indexes.size() > 0) {
        selectedIndex = indexes.at(0);
        row = selectedIndex.row();
        if (row == inx.row()) {
            ptr_LMap->onSelect(selected);
        }
    }

    if(I.row() == -1) {
        return;
    }

    if (I.parent().row() != -1)  {
        QModelIndex idx = model.index(I.row(), 1, I.parent());
        auto value = model.data(idx, Qt::DisplayRole).toInt();
    }

}
