#include "ImageViewer.h"
#include <QPainter>
#include <QMouseEvent>

ImageViewer::ImageViewer(QWidget *parent)
    : QWidget(parent), drawing(false), scaleFactor(1.0) {}

void ImageViewer::loadImage(const QString &filePath) {
    image.load(filePath);
    lines.clear(); // Очищаем линии при загрузке нового изображения
    update();
}

void ImageViewer::setScaleFactor(double scaleFactor) {
    this->scaleFactor = scaleFactor;
}

void ImageViewer::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Отрисовка изображения
    if (!image.isNull()) {
        painter.drawImage(0, 0, image);
    }

    // Отрисовка завершенных линий
    painter.setPen(Qt::red);
    for (const QLine &line : lines) {
        painter.drawLine(line);

        double pixelDistance = std::hypot(line.x2() - line.x1(), line.y2() - line.y1());
        double mmDistance = pixelDistance * scaleFactor;
        painter.drawText(line.p2(), QString::number(mmDistance) + " mm");
    }

    // Отрисовка текущей линии, если рисование в процессе
    if (drawing) {
        painter.drawLine(startPoint, endPoint);

        double pixelDistance = std::hypot(endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y());
        double mmDistance = pixelDistance * scaleFactor;
        painter.drawText(endPoint, QString::number(mmDistance) + " mm");
    }
}

void ImageViewer::resetLines() {
    lines.clear(); // Очищаем список линий
    update();      // Перерисовываем виджет
}


void ImageViewer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        endPoint = startPoint;
        drawing = true;
        update();
    }
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        endPoint = event->pos();
        lines.append(QLine(startPoint, endPoint)); // Добавляем линию в список
        drawing = false;
        update();
    }
}

