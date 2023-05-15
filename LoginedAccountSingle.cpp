#include "LoginedAccountSingle.h"

//静态成员只能在类外初始化
LoginedAccountSingle* LoginedAccountSingle::_instance = nullptr;

LoginedAccountSingle* LoginedAccountSingle::instance()
{
    if(_instance == nullptr) _instance = new LoginedAccountSingle;
    return _instance;
}
