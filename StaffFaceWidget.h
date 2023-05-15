#ifndef STAFFFACEWIDGET_H
#define STAFFFACEWIDGET_H

#include <QWidget>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class StaffFaceWidget; }
QT_END_NAMESPACE

class StaffFaceWidget : public QWidget
{
    Q_OBJECT

public:
    StaffFaceWidget(QWidget *parent = nullptr);
    ~StaffFaceWidget();

private:
    Ui::StaffFaceWidget *ui;

    QButtonGroup btnGp;

private:
    //私有的处理函数
    void init();
};
#endif // STAFFFACEWIDGET_H
