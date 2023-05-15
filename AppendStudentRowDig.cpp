#include "AppendStudentRowDig.h"
#include "ui_AppendStudentRowDig.h"
#include "theDB.h"
#include "theQSS.h"

AppendStudentRowDig::AppendStudentRowDig(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AppendStudentRowDig)
{
    ui->setupUi(this);

    theQSS::instance()->MacOSStyle(this);
}

AppendStudentRowDig::~AppendStudentRowDig()
{
    delete ui;
}

void AppendStudentRowDig::on_pushButton_clicked()
{
    STUTABELROW val = {ui->theID->value(), ui->theName->text(), ui->theGender->text(),
                        ui->theAge->value(), ui->theNativePlace->text(), ui->thePhoto->getImageData(),
                        ui->theMemo->toPlainText()};

    //输入没问题就关闭窗口
    if(theDB::instance()->insertToStudentTable(val))
        this->accept();
}

