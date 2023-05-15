#ifndef TABLEOPERAWIDGET_H
#define TABLEOPERAWIDGET_H

#include <QWidget>
#include <QtSql>
#include <QDataWidgetMapper>
#include "theDB.h"
#include <QDataWidgetMapper>
#include <QObject>
#include <QByteArrayData>

namespace Ui {
class TableOperaWidget;
}

class TableOperaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableOperaWidget(QWidget *parent = nullptr);
    ~TableOperaWidget();

private slots:
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);

// QTableView的SelectionModel的行发生了变化，进行处理
    void on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_appendBtn_clicked();

    void on_removeBtn_clicked();
    void on_pixmap_changed(const QByteArray& ig);

private:
    Ui::TableOperaWidget *ui;

    QSqlTableModel tableModel = QSqlTableModel(this, *(theDB::instance()->getDataBase()));
    QItemSelectionModel theSelection = QItemSelectionModel(&tableModel);
    QDataWidgetMapper dataMapper;

private:
    //私有工具函数
    void init();
    void SetTableModel();
    void SetTableView();
    void SetDataMapper();
    //数据修改后得确认更改和更新显示数据表
    void tableSubmitAndUpadate();
};

#endif // TABLEOPERAWIDGET_H
