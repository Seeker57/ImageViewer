#include "ScaledLabel.h"

ScaledLabel::ScaledLabel(QWidget *parent) : QLabel(parent), zoom(1.0) {}


void ScaledLabel::setScaledLabel(const QImage& newMap) {
   map = newMap;
   update();
}

void ScaledLabel::paintEvent(QPaintEvent* event) {

    QPainter painter(this);
    if (map.isNull() == false) {
        QSize widgetSize = size();
        QImage scaledMap = map.scaled(widgetSize, Qt::KeepAspectRatio);
        QPoint center((widgetSize.width() - scaledMap.width()) / 2,
                      (widgetSize.height() - scaledMap.height()) / 2);
        painter.drawImage(center, scaledMap);
    }
    QLabel::paintEvent(event);
}

void ScaledLabel::wheelEvent(QWheelEvent* event )
{
    if (event->modifiers() & Qt::ControlModifier) {
        zoom = qPow(1.2, event->delta() / 240.0);
        resize(size() * zoom);
    }
}

void ScaledLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        mStart = event->globalPos();
}

void ScaledLabel::mouseMoveEvent(QMouseEvent* event)
{
    if(( event->buttons() & Qt::LeftButton ) && !map.isNull()) {

        QPoint dm = QPoint(mStart - event->globalPos());
        move(pos() - dm);
        mStart = event->globalPos();
    }
}

