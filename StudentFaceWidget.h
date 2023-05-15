#ifndef STUDENTFACEWIDGET_H
#define STUDENTFACEWIDGET_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class StudentFaceWidget;
}

class StudentFaceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentFaceWidget(QWidget *parent = nullptr);
    ~StudentFaceWidget();

private:
    Ui::StudentFaceWidget *ui;

    QButtonGroup btnGp;

private:
    //私有处理函数
    void init();
};

#endif // STUDENTFACEWIDGET_H
