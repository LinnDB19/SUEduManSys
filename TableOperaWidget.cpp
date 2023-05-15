#include "TableOperaWidget.h"
#include "ui_TableOperaWidget.h"
#include <QMessageBox>
#include "AppendStudentRowDig.h"
#include <QDebug>
#include "theQSS.h"

TableOperaWidget::TableOperaWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableOperaWidget)
{
    ui->setupUi(this);

    init();
    SetTableModel();
    SetTableView();
    SetDataMapper();
}

void TableOperaWidget::init()
{
    //theSelection当前项变化时触发currentChanged信号
    connect(&theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),
        this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    //选择行变化时
    connect(&theSelection,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
        this,SLOT(on_currentRowChanged(QModelIndex,QModelIndex)));

    //thpoto的pixmap变化时
    connect(ui->thePhoto, &labelWithPbtn::imageDataChanged, this, &TableOperaWidget::on_pixmap_changed);

    theQSS::instance()->MacOSStyle(this);
}

void TableOperaWidget::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

}

void TableOperaWidget::on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    qDebug() << "当前行有变化" << Qt::endl;

    ui->thePhoto->clear();

    if(current.isValid())
    {
        //更新数据
        int curRecNo=current.row();//获取行号
        dataMapper.setCurrentIndex(curRecNo);

        //设置新照片
        QSqlRecord  curRec = tableModel.record(curRecNo); //获取当前记录
        if (!curRec.isNull("Photo"))  //图片字段内容不为空
        {
            QByteArray data = curRec.value("Photo").toByteArray();
            QPixmap pic;
            pic.loadFromData(data);
            ui->thePhoto->setPixmap(pic.scaledToWidth(ui->thePhoto->size().width()));
        }
    }

    if(tableModel.isDirty())
    {
        tableSubmitAndUpadate();
    }
}

void TableOperaWidget::SetTableModel()
{
    tableModel.setTable("studentTable");

    /*若用QSqlTableModel::OnFieldChange 会出现：改了几个数据之后，就没法双击单元格修改了*/
    tableModel.setEditStrategy(QSqlTableModel::OnManualSubmit);  // 放到on_currentChanged中自动确认

    if (!(tableModel.select()))//查询数据
    {
       QMessageBox::critical(this, "错误信息",
              "打开数据表错误,错误信息\n"+tableModel.lastError().text(),
                 QMessageBox::Ok,QMessageBox::NoButton);
       return;
    }

    //设置字段显示名
    tableModel.setHeaderData(tableModel.fieldIndex("id"), Qt::Horizontal, "学号");
    tableModel.setHeaderData(tableModel.fieldIndex("name"), Qt::Horizontal, "姓名");
    tableModel.setHeaderData(tableModel.fieldIndex("gender"), Qt::Horizontal, "性别");
    tableModel.setHeaderData(tableModel.fieldIndex("age"), Qt::Horizontal, "年龄");
    tableModel.setHeaderData(tableModel.fieldIndex("NativePlace"), Qt::Horizontal, "籍贯");
    tableModel.setHeaderData(tableModel.fieldIndex("memo"), Qt::Horizontal, "备注");
}


void TableOperaWidget::SetTableView()
{
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);

    ui->tableView->setModel(&tableModel);
    ui->tableView->setSelectionModel(&theSelection);

    ui->tableView->setColumnHidden(tableModel.fieldIndex("photo"),true);//不显示photo栏
}

void TableOperaWidget::SetDataMapper()
{
    dataMapper.setModel(&tableModel);
    dataMapper.setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    //界面组件与tabModel字段的关系
    dataMapper.addMapping(ui->theID, tableModel.fieldIndex("id"));
    dataMapper.addMapping(ui->theName, tableModel.fieldIndex("name"));
    dataMapper.addMapping(ui->theGender, tableModel.fieldIndex("gender"));
    dataMapper.addMapping(ui->theAge, tableModel.fieldIndex("age"));
    dataMapper.addMapping(ui->theNativePlace, tableModel.fieldIndex("NativePlace"));
    dataMapper.addMapping(ui->theMemo, tableModel.fieldIndex("memo"));

    //dataMapper.toFirst();  //默认显示首行
}

TableOperaWidget::~TableOperaWidget()
{
    delete ui;
}

void TableOperaWidget::on_appendBtn_clicked()
{
    AppendStudentRowDig appendDig;
    appendDig.exec();
    tableSubmitAndUpadate();
}


void TableOperaWidget::on_removeBtn_clicked()
{
    QModelIndex curIndex=theSelection.currentIndex();//获取当前选择单元格的模型索引
    if(curIndex.isValid())
    {
        if(!tableModel.removeRow(curIndex.row()))
            QMessageBox::warning(this, "删除学生错误", tableModel.lastError().text());
        else
        {
            tableSubmitAndUpadate();
            qDebug() << "成功删除行" << Qt::endl;
        }
    }
    else qDebug() << "选择下标无效，删除行失败" << Qt::endl;
}


void TableOperaWidget::on_pixmap_changed(const QByteArray& ig)
{
    if(!theSelection.currentIndex().isValid())  //先判断当前是否选中了tableModel的某一行
        return;

    int curRecNo = theSelection.currentIndex().row();
    QSqlRecord curRec = tableModel.record(curRecNo);
    curRec.setValue("photo", ig);
    tableModel.setRecord(curRecNo, curRec);
}

void TableOperaWidget::tableSubmitAndUpadate()
{
    //保存选中的行，更新之后选中单元格会失效，手动再让theselection选中该单元格
    QModelIndex idx = theSelection.currentIndex();

    if(!tableModel.submitAll())
    {
        QMessageBox::warning(this, "数据更新失败", tableModel.lastError().text());
        return;
    }
    tableModel.select();

    if(idx.isValid()) theSelection.setCurrentIndex(idx, QItemSelectionModel::Select);

    qDebug() << "数据修改已确认" << Qt::endl;
}
