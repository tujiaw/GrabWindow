#include "grabwidget.h"
#include <QtWidgets>
#include <QApplication>
#include <QDesktopWidget>

GrabWidget::GrabWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowOpacity(0.1);

    resize(QApplication::desktop()->width(), QApplication::desktop()->height());
    setCursor(Qt::CrossCursor);
    isDrawing_ = false;
}

void GrabWidget::savePixmap()
{

}

void GrabWidget::mouseMoveEvent(QMouseEvent *ev)
{
    ptCur_.setX(ev->x());
    ptCur_.setY(ev->y());
    update();
}

void GrabWidget::paintEvent(QPaintEvent *)
{
    int width, height;
    QPen pen(QBrush(QColor(255, 0, 0)), 3);
    QPainter painter(this);
    painter.setPen(pen);
    if (isDrawing_) {
        width = ptCur_.x() - ptStart_.x();
        height = ptCur_.y() - ptStart_.y();
        painter.drawRect(ptStart_.x(), ptStart_.y(), width, height);
    } else {
        if (ptEnd_ != ptStart_) {
            width = ptEnd_.x() - ptStart_.x();
            height = ptEnd_.y() - ptStart_.y();
            painter.drawRect(ptStart_.x(), ptStart_.y(), width, height);
        }
    }
    update();
}

void GrabWidget::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::MiddleButton) {
        hide();
        int width = ptEnd_.x() - ptStart_.x();
        int height = ptEnd_.y() - ptStart_.y();
        QPixmap tmpPixmap = QPixmap::grabWindow(QApplication::desktop()->winId(),
                                                ptStart_.x(), ptStart_.y(), width, height);
        QDateTime dt = QDateTime::currentDateTime();
        QString filename = dt.toString("yyyyMMddhhmmss") + ".jpg";
        tmpPixmap.save(filename, 0, 100);
        exit(1);
    } else if (ev->button() == Qt::RightButton) {
        exit(1);
    } else if (ev->button() == Qt::LeftButton) {
        ptStart_ = ev->pos();
        isDrawing_ = true;
    }
    update();
}

void GrabWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        ptEnd_ = ev->pos();
        isDrawing_ = false;
    }
}
