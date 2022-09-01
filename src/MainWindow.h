//
// Created by genas on 30.08.2022.
//

#ifndef GRAPHICSPROJECT_MAINWINDOW_H
#define GRAPHICSPROJECT_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "widgets/GraphicsListWidget.h"
#include "widgets/PlotArea.h"
#include "widgets/other/StyleSheetsHelper.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

    QWidget* centralWidget;

    GraphicsListWidget* graphics;
    PlotArea* plotWidget;

    QFrame* areaSeparator;

    int sideAreaCurrentWidth;
    int sideMinimumWidth;
    int expandAreaWidth;

    bool isMousePressed;
    int mousePressedX;

public:
    explicit MainWindow(QWidget* parent = Q_NULLPTR);

    void setupUI();

protected:
    void resizeEvent(QResizeEvent* event) override;

    bool eventFilter(QObject* target, QEvent* event) override;

public slots:
    void expandLeft();
    void expandRight();
};


#endif//GRAPHICSPROJECT_MAINWINDOW_H
