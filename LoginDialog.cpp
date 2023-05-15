#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QSettings>
#include <QCryptographicHash>
#include <QMouseEvent>
#include <QMessageBox>
#include <LoginedAccountSingle.h>
#include <QDebug>
#include "theQSS.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->resize({1000, 800});

    ui->passwordLnEd->setEchoMode(QLineEdit::Password); // 设置密码输入模式

    this->setAttribute(Qt::WA_DeleteOnClose); // 窗口关闭时自动删除
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
    //this->setWindowFlags(Qt::SplashScreen); // 窗口无边框,不在任务栏显示

    theQSS::instance()->MacOSStyle(this);
}

void LoginDialog::__readSettings()
{
    QString organization("Space University"), appname("EduManSys");
    QSettings settings(organization, appname);
    QString defaultPSWD = __encrypt("12345"); // 缺省密码加密后的数据

    bool saved = settings.value("saved", false).toBool();
    __username = settings.value("Username", "admin").toString();
    __password = settings.value("Password", defaultPSWD).toString();

    if(saved) ui->usernameLnEd->setText(__username);
    ui->SaveChB->setChecked(saved);
}

void LoginDialog::__writeSettings()
{
    //保存用户名，密码等设置
    QString organization("Space University"), appname("EduManSys");
    QSettings settings(organization, appname);

    settings.setValue("Username", __username); //用户名
    settings.setValue("PSWD", __password);   //密码，经过加密的
    settings.setValue("saved",ui->SaveChB->isChecked());
}

QString LoginDialog::__encrypt(const QString &str)
{
    //字符串MD5算法加密
    QByteArray btArray;
    btArray.append(str);//加入原始字符串
    QCryptographicHash hash(QCryptographicHash::Md5);  //Md5加密算法
    hash.addData(btArray);  //添加数据到加密哈希值
    QByteArray resultArray(hash.result());  //返回最终的哈希值
    QString md5(resultArray.toHex());//转换为16进制字符串

    return  md5;
}

void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    //鼠标按键被按下
    if (event->button() == Qt::LeftButton)
    {
        b_moving = true;
        //记录下鼠标相对于窗口的位置
        //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
        //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
        lastPos = event->globalPos() - pos();
    }
    return QDialog::mousePressEvent(event);  //
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标按下左键移动
    //(event->buttons() && Qt::LeftButton)按下是左键
    //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    if (b_moving && (event->buttons() & Qt::LeftButton)
        && (event->globalPos() - lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos() - lastPos);
        lastPos = event->globalPos() - pos();
    }
    QDialog::mouseMoveEvent(event);
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *event)
{
    //鼠标按键释放
    Q_UNUSED(event);
    b_moving = false; //停止移动
}


void LoginDialog::on_LoginPtn_clicked()
{
    QString user = ui->usernameLnEd->text().trimmed();//输入用户名
    QString pswd = ui->passwordLnEd->text().trimmed(); //输入密码
    QString admin("admin"), adminPassword("password");
    QString student("student"), studentPassword("student");

    if (user == admin && pswd == adminPassword)
    {

        LoginedAccountSingle::instance()->setAccount(user, pswd, ACCTYPE::STAFF);
        this->accept();
    }
    else if(user == student && pswd == studentPassword)
    {
        LoginedAccountSingle::instance()->setAccount(user, pswd, ACCTYPE::STUDENT);
        this->accept();
    }
    else
    {
        ui->remind->setText("用户名或密码错误");
        this->update();
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

