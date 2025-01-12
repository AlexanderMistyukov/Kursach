#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QVector>
#include <QLine>

class ImageViewer : public QWidget {
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);
    void loadImage(const QString &filePath);
    void setScaleFactor(double scaleFactor);
    void resetLines(); // Объявление метода для сброса линий

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QImage image;
    QVector<QLine> lines;  // Список завершенных линий
    QPoint startPoint;
    QPoint endPoint;
    bool drawing;
    double scaleFactor;
};

#endif // IMAGEVIEWER_H
