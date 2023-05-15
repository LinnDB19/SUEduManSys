/*用于维护一个已经登陆的账号，有且仅有一个这个实例，当登陆窗口关闭后，main函数依靠这个实例的数据
  来判断应该启用哪一个类型的客户端界面*/


#ifndef LOGINEDACCOUNTSINGLE_H
#define LOGINEDACCOUNTSINGLE_H

#include <QString>


enum ACCTYPE{STUDENT, STAFF};
class LoginedAccountSingle
{
private:
    static LoginedAccountSingle * _instance;

    //私有数据
    QString username;
    QString password;
    ACCTYPE type;

protected:
    LoginedAccountSingle() { username = "", password = "", type = ACCTYPE::STUDENT;}

public:
    static LoginedAccountSingle* instance();
    QString getUsername() const {return username;}
    QString getPassword() const {return password;}
    ACCTYPE getType() const {return type;}
    void setAccount(const QString& name,const QString& pwd, const ACCTYPE& t)
    {
        username = name, password = pwd, type = t;
    }
    void setUsername(const QString& name) {username = name;}
    void setPassword(const QString& pwd) {password = pwd;}
    void setType(const ACCTYPE& t) {type = t;}
    ~LoginedAccountSingle() {}
};




#endif // LOGINEDACCOUNTSINGLE_H
