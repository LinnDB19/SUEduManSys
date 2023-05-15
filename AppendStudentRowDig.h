#ifndef APPENDSTUDENTROWDIG_H
#define APPENDSTUDENTROWDIG_H

#include <QDialog>

namespace Ui {
class AppendStudentRowDig;
}

class AppendStudentRowDig : public QDialog
{
    Q_OBJECT

public:
    explicit AppendStudentRowDig(QDialog *parent = nullptr);
    ~AppendStudentRowDig();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AppendStudentRowDig *ui;
};

#endif // APPENDSTUDENTROWDIG_H
