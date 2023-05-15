#include "StudentFaceWidget.h"
#include "ui_StudentFaceWidget.h"

StudentFaceWidget::StudentFaceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentFaceWidget)
{
    ui->setupUi(this);

    init();
}

void StudentFaceWidget::init()
{
    this->resize({1000, 800});

    btnGp.addButton(ui->personInfoTtn, 0);
    btnGp.addButton(ui->examTtn, 1);

    //QOverload确定具体的某个重载函数
    connect(&btnGp, QOverload<int>::of(&QButtonGroup::idClicked), ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    // 设置默认选中的页面
    btnGp.button(0)->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);

}

StudentFaceWidget::~StudentFaceWidget()
{
    delete ui;
}
