#ifndef SCALEDLABEL_H
#define SCALEDLABEL_H

#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QImage>
#include <QtMath>

//реализация собственного label-виджета, который пропорционально масштабируется при изменении размеров окна
class ScaledLabel : public QLabel {

    Q_OBJECT
    QImage map;
    QPoint mStart;
    QSize mStartSize;
    qreal zoom;
protected slots:
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
public:
    explicit ScaledLabel(QWidget *parent = nullptr);
    void setScaledLabel(const QImage& newMap);
    void setZoom(qreal newZoom) { zoom = newZoom; }
    qreal getZoom() {return zoom; }
    QSize getStartSize() { return mStartSize; }
    void setStartSize(QSize size) { mStartSize = size; }
};

#endif // SCALEDLABEL_H
