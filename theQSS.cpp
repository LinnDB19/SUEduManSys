#include "theQSS.h"
#include <QFile>
#include <QString>

theQSS* theQSS::_instance = nullptr;

theQSS::theQSS() {}

theQSS* theQSS::instance()
{
    if(_instance == nullptr) _instance = new theQSS();
    return _instance;
}

void theQSS::MacOSStyle(QWidget * wid)
{
    QFile file(":/new/QSS/MacOS.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet(QString::fromLatin1(file.readAll()));
    wid->setStyleSheet(styleSheet);
}
