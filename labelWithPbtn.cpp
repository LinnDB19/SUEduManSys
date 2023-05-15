#include "labelWithPbtn.h"
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QPalette>
#include <QBuffer>
#include <QFileDialog>

labelWithPbtn::labelWithPbtn(QWidget *parent) :QLabel(parent)
{
    init();
}

void labelWithPbtn::init()
{
    hlay->addWidget(setPhotoBtn);
    this->setLayout(hlay);

    setPhotoBtn->setObjectName("setPhotoBtn");
    setPhotoBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); //尺寸固定
    setPhotoBtn->resize(this->size());
    setPhotoBtn->setText("修改头像");
    setPhotoBtn->setStyleSheet("QPushButton#setPhotoBtn"
                               "{"
                                   "background-color: transparent;"  //鼠标未在按钮上时透明，要包括背景和字体透明
                                   "color: transparent;"
                                   "border: none;"  //不设置border,前两个会失效
                                   "font: 20pt \"微软雅黑\";"
                               "}"
                               "QPushButton#setPhotoBtn:hover"
                               "{"
                                   "background-color: rgba(173, 173, 173, 75);"
                                   "color: rgb(117, 117, 117);"
                                   "border: none;"
                               "}");

    connect(setPhotoBtn, &QPushButton::clicked, this, &labelWithPbtn::setImage);
}

void labelWithPbtn::setPixmap(const QPixmap & pix)
{
    QLabel::setPixmap(pix);

    //更新iamgeData
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    pix.save(&buffer,"png");

    emit imageDataChanged(imageData);
}

void labelWithPbtn::setImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,"选择图片文件","","照片(*.jpg *.png)");
    if (fileName.isEmpty())
       return;

    QPixmap pix;
    pix.load(fileName);

    this->setPixmap(pix);
}

QByteArray labelWithPbtn::getImageData()
{
    return imageData;
}
