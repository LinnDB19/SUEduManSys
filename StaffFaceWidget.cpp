#include "StaffFaceWidget.h"
#include "ui_StaffFaceWidget.h"

StaffFaceWidget::StaffFaceWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StaffFaceWidget)
{
    ui->setupUi(this);

    init();
}

void StaffFaceWidget::init()
{
    //this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    btnGp.addButton(ui->stuInfoTtn, 0);
    btnGp.addButton(ui->examTtn, 1);
    btnGp.addButton(ui->sumTtn, 2);

    //QOverload确定具体的某个重载函数
    connect(&btnGp, QOverload<int>::of(&QButtonGroup::idClicked), ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    // 设置默认选中的页面
    btnGp.button(0)->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);
}

StaffFaceWidget::~StaffFaceWidget()
{
    delete ui;
}

