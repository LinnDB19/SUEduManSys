#ifndef LABELWITHPBTN_H
#define LABELWITHPBTN_H

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QByteArray>

class labelWithPbtn : public QLabel
{
    Q_OBJECT

private:
    QHBoxLayout *hlay = new QHBoxLayout;
    QPushButton *setPhotoBtn = new QPushButton;
    QByteArray imageData;
private:
    //工具私有函数
    void init();
    void getImageFile();

public:
    labelWithPbtn(QWidget *parent = nullptr);
    void setPixmap(const QPixmap & pix); //需要重写以保存二进制图片文件
    QByteArray getImageData();

public: signals:
    void imageDataChanged(const QByteArray& ig);
private slots:
    void setImage();  //通过文件设置labelpixmap

};

#endif // LABELWITHPBTN_H
