#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QString>


namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    bool b_moving = false; // 是否正在移动
    QPoint lastPos;
    QString __username = "user"; //初始化用户名
    QString __password = "12345"; // 初始化密码，未加密
    int tryCount = 0; //试错次数

private:        //私有工具接口
    void __readSettings();
    void __writeSettings();
    QString __encrypt(const QString& str);  // 字符串加密

protected:
    //鼠标拖动窗口事件
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public:

private slots:
    void on_LoginPtn_clicked();
};

#endif // LOGINDIALOG_H
