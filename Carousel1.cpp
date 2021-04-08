#include "Carousel1.h"

Carousel1::Carousel1(QWidget *parent)
    : QDialog(parent)
{
    //设置窗口大小
    setFixedSize(QSize(800,500));
    //添加一个属性
    setProperty("CarouselOpacity",QVariant(1.0));
    //去掉问号
    Qt::WindowFlags flags= this->windowFlags();
    setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);

    try {
        indexImage=1;
        imageOpacity=0;
        //初始化变量
        opacityAnimation=new QPropertyAnimation(this,"CarouselOpacity");
        //设置属性值变化范围
        opacityAnimation->setStartValue(1.0);
        opacityAnimation->setEndValue(0.0);
        //设置动画时间
        opacityAnimation->setDuration(2000);
        //添加动画响应槽
        connect(opacityAnimation,&QPropertyAnimation::valueChanged,this,&Carousel1::SlotUpdateChanged);
    } catch (...) {}
}

Carousel1::~Carousel1(){}

void Carousel1::timerEvent(QTimerEvent*)
{
    if(imageList.size()<2)
        return;
    imageCurr=imageList.at(indexImage);
    ++indexImage;
    if(indexImage>=imageList.size())
        indexImage=0;
     imageNext=imageList.at(indexImage);
    opacityAnimation->start();
}

void Carousel1::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect widgetRect = this->rect();
    //先绘制下一张图片
    painter.setOpacity(1-imageOpacity);
    painter.drawPixmap(widgetRect, imageNext.scaled(widgetRect.size()));
    //再绘制第一张图片
    painter.setOpacity(imageOpacity);
    painter.drawPixmap(widgetRect, imageCurr.scaled(widgetRect.size()));
}

void Carousel1::StartPlay()
{
    if(imageList.size()==0)
        return;
    if(imageList.size()>0){
      imageCurr=imageList.at(0);
      imageNext=imageList.at(0);
    }
    if(imageList.size()>1)
        imageNext=imageList.at(1);
    //启动定时器
    startTimer(5000);
}

void Carousel1::AddImageList(QString path)
{
    imageList.append(path);
}

void Carousel1::SlotUpdateChanged(const QVariant& value)
{
    imageOpacity=value.toFloat();
    update();
}
