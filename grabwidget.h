#ifndef GRAWWIDGET_H
#define GRAWWIDGET_H

#include <QWidget>

class QMouseEvent;
class QPoint;

class GrabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GrabWidget(QWidget *parent = 0);

signals:

public slots:

public:
    void savePixmap();

protected:
    void mouseMoveEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

private:
    QPoint ptCur_;
    QPoint ptStart_;
    QPoint ptEnd_;
    bool isDrawing_;
};

#endif // GRAWWIDGET_H
