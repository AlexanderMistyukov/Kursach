#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ImageViewer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void resetImage(); // Метод для сброса
    void setScaleFactor();        // Установка коэффициента

private:
    Ui::MainWindow *ui;
    ImageViewer *imageViewer;
    double scaleFactor;  // Коэффициент преобразования пикселей в мм
};
#endif // MAINWINDOW_H
