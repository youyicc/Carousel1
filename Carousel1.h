#ifndef CAROUSEL1_H
#define CAROUSEL1_H

#include <QList>
#include <QDialog>
#include <QDebug>
#include <QPainter>
#include <QVariant>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QPropertyAnimation>

class Carousel1 : public QDialog
{
    Q_OBJECT

private:
    int indexImage;
    double imageOpacity;
    QList<QString> imageList;
    QPixmap imageCurr,imageNext;
    QPropertyAnimation* opacityAnimation;

public:
    Carousel1(QWidget *parent = nullptr);
    ~Carousel1();

protected:
    virtual void timerEvent(QTimerEvent*);
    virtual void paintEvent(QPaintEvent*);

public:
    void StartPlay();
    void AddImageList(QString);

public slots:
    void SlotUpdateChanged(const QVariant&);
};
#endif
