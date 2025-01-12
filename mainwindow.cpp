#include "mainwindow.h"
#include "ImageViewer.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QToolBar>
#include <QAction>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), imageViewer(new ImageViewer(this)) {
    setCentralWidget(imageViewer);

    // Создаем меню "Файл"
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    // Действие "Открыть изображение"
    QAction *openAction = fileMenu->addAction(tr("&Open Image"));
    connect(openAction, &QAction::triggered, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png)"));
        if (!filePath.isEmpty()) {
            imageViewer->loadImage(filePath);
        }
    });
    // Меню "Настройки"
    QMenu *settingsMenu = menuBar()->addMenu(tr("&Settings"));

    QAction *setScaleAction = settingsMenu->addAction(tr("Set &Scale Factor"));
    connect(setScaleAction, &QAction::triggered, this, &MainWindow::setScaleFactor);

    // Действие "Сброс"
    QAction *resetAction = fileMenu->addAction(tr("&Reset"));
    connect(resetAction, &QAction::triggered, this, &MainWindow::resetImage);

    // Панель инструментов
    QToolBar *toolbar = addToolBar(tr("Main Toolbar"));
    toolbar->addAction(openAction);
    toolbar->addAction(resetAction);
    toolbar->addAction(setScaleAction);
}

MainWindow::~MainWindow(){}

void MainWindow::resetImage() {
    imageViewer->loadImage("");
    imageViewer->resetLines(); // Сбрасываем линии    // Очищаем изображение
    imageViewer->update();      // Обновляем виджет
}

void MainWindow::setScaleFactor() {
    bool ok;
    double newScaleFactor = QInputDialog::getDouble(this, tr("Set Scale Factor"),
                                                    tr("Enter scale factor (mm per pixel):"),
                                                    scaleFactor, 0.001, 1000.0, 3, &ok);
    if (ok) {
        scaleFactor = newScaleFactor;
        imageViewer->setScaleFactor(scaleFactor);
    }
}
