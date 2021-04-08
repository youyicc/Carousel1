#include "Carousel1.h"

Carousel1::Carousel1(QWidget *parent)
    : QDialog(parent)
{
    //���ô��ڴ�С
    setFixedSize(QSize(800,500));
    //���һ������
    setProperty("CarouselOpacity",QVariant(1.0));
    //ȥ���ʺ�
    Qt::WindowFlags flags= this->windowFlags();
    setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);

    try {
        indexImage=1;
        imageOpacity=0;
        //��ʼ������
        opacityAnimation=new QPropertyAnimation(this,"CarouselOpacity");
        //��������ֵ�仯��Χ
        opacityAnimation->setStartValue(1.0);
        opacityAnimation->setEndValue(0.0);
        //���ö���ʱ��
        opacityAnimation->setDuration(2000);
        //��Ӷ�����Ӧ��
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
    //�Ȼ�����һ��ͼƬ
    painter.setOpacity(1-imageOpacity);
    painter.drawPixmap(widgetRect, imageNext.scaled(widgetRect.size()));
    //�ٻ��Ƶ�һ��ͼƬ
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
    //������ʱ��
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
