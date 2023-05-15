/*一个singleton模式*/

#ifndef THEQSS_H
#define THEQSS_H

#include <QWidget>

class theQSS
{

private:
    static theQSS* _instance;

public:
    static theQSS* instance();

    void MacOSStyle(QWidget* wid);

protected:
    theQSS();
};

#endif // THEQSS_H
