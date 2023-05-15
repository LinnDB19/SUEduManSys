#include "StaffFaceWidget.h"
#include "StudentFaceWidget.h"
#include "LoginDialog.h"
#include "LoginedAccountSingle.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SUEduManSys_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    LoginDialog* login = new LoginDialog;
    if(login->exec() == QDialog::Accepted)
    {
        if(LoginedAccountSingle::instance()->getType() == ACCTYPE::STAFF)
        {

            StaffFaceWidget staffwid;
            staffwid.show();
            return a.exec();
        }
        else
        {
            StudentFaceWidget studentWid;
            studentWid.show();
            return a.exec();
        }
    }

    return 0;
}
