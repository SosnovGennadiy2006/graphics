//
// Created by genas on 30.08.2022.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent}
{
    setupUI();

    isMousePressed = false;

    connect(graphics, &GraphicsListWidget::expandButtonClicked, this, &MainWindow::expandLeft);
    connect(plotWidget, &PlotArea::expandButtonClicked, this, &MainWindow::expandRight);
}

void MainWindow::setupUI()
{
    setMinimumSize(900, 600);

    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");

    setCentralWidget(centralWidget);

    sideAreaCurrentWidth = 400;
    sideMinimumWidth = 200;

    graphics = new GraphicsListWidget(centralWidget);
    graphics->setGeometry(0, 0, sideAreaCurrentWidth, geometry().height());
    graphics->installEventFilter(this);
    graphics->setObjectName("graphicsList");

    areaSeparator = new QFrame(this);
    areaSeparator->setFixedWidth(5);
    areaSeparator->setFrameShape(QFrame::VLine);
    areaSeparator->setFrameShadow(QFrame::Plain);
    areaSeparator->setGeometry(sideAreaCurrentWidth - 1, 0, 1, geometry().height());
    areaSeparator->setObjectName("areaSeparator");
    areaSeparator->setCursor(QCursor(Qt::SizeHorCursor));
    areaSeparator->installEventFilter(this);
    areaSeparator->stackUnder(graphics);

    plotWidget = new PlotArea(centralWidget);
    plotWidget->setGeometry(sideAreaCurrentWidth, 0, \
                            geometry().width() - sideAreaCurrentWidth, geometry().height());
    plotWidget->setObjectName("plotWidget");
    plotWidget->hideExpandButton();

    setStyleSheet(StyleSheetsHelper::loadStyles(":/resources/styles/main.qss"));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (sideAreaCurrentWidth > event->size().width() - 200)
    {
        sideAreaCurrentWidth = event->size().width() - 200;
    }

    graphics->setGeometry(0, 0, sideAreaCurrentWidth, event->size().height());
    areaSeparator->setGeometry(sideAreaCurrentWidth - 1, 0, 1, event->size().height());
    plotWidget->setGeometry(sideAreaCurrentWidth, 0, event->size().width() - sideAreaCurrentWidth, event->size().height());
}

bool MainWindow::eventFilter(QObject* target, QEvent* event)
{
    if (target == graphics)
    {
        if (event->type() == QEvent::Resize)
        {
            auto* resizeEvent = dynamic_cast<QResizeEvent*>(event);
            sideAreaCurrentWidth = resizeEvent->size().width();
            graphics->setGeometry(0, 0, sideAreaCurrentWidth, geometry().height());
            areaSeparator->setGeometry(sideAreaCurrentWidth - 1, 0, 1, geometry().height());
            plotWidget->setGeometry(sideAreaCurrentWidth, 0, geometry().width() - sideAreaCurrentWidth, geometry().height());
        }
    }else if (target == areaSeparator)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            auto* mouseEvent = dynamic_cast<QMouseEvent*>(event);
            mousePressedX = mouseEvent->pos().x();
            isMousePressed = true;

        }else if (event->type() == QEvent::MouseButtonRelease)
        {
            isMousePressed = false;
        }else if (event->type() == QEvent::MouseMove)
        {
            auto* mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if (isMousePressed)
            {
                QPoint pos = areaSeparator->mapToParent(mouseEvent->pos());
                int newWidth = pos.x() - mousePressedX;

                sideAreaCurrentWidth = newWidth;

                if (sideAreaCurrentWidth < sideMinimumWidth)
                {
                    sideAreaCurrentWidth = sideMinimumWidth;
                }else if (sideAreaCurrentWidth > geometry().width() - 200)
                {
                    sideAreaCurrentWidth = geometry().width() - 200;
                }

                graphics->setGeometry(0, 0, sideAreaCurrentWidth, geometry().height());
                areaSeparator->setGeometry(sideAreaCurrentWidth - 1, 0, 1, geometry().height());
                plotWidget->setGeometry(sideAreaCurrentWidth, 0, geometry().width() - sideAreaCurrentWidth, geometry().height());
            }
        }
    }
    return false;
}

void MainWindow::expandLeft()
{
    expandAreaWidth = sideAreaCurrentWidth;

    auto* animationGroup = new QParallelAnimationGroup();

    auto* animation1 = new QPropertyAnimation(graphics, "geometry");
    animation1->setDuration(100);
    animation1->setStartValue(graphics->geometry());
    animation1->setEndValue(QRect(0, 0, 0, geometry().height()));
    animation1->setEasingCurve(QEasingCurve::Linear);

    auto* animation2 = new QPropertyAnimation(areaSeparator, "geometry");
    animation2->setDuration(100);
    animation2->setStartValue(areaSeparator->geometry());
    animation2->setEndValue(QRect(0, 0, 1, geometry().height()));
    animation2->setEasingCurve(QEasingCurve::Linear);

    auto* animation3 = new QPropertyAnimation(plotWidget, "geometry");
    animation3->setDuration(100);
    animation3->setStartValue(plotWidget->geometry());
    animation3->setEndValue(QRect(0, 0, geometry().width(), geometry().height()));
    animation3->setEasingCurve(QEasingCurve::Linear);

    animationGroup->addAnimation(animation1);
    animationGroup->addAnimation(animation2);
    animationGroup->addAnimation(animation3);

    animationGroup->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animationGroup, &QParallelAnimationGroup::finished, this, [this](){
        graphics->hide();
        areaSeparator->hide();
        plotWidget->showExpandButton();
    });
}

void MainWindow::expandRight()
{
    if (expandAreaWidth > geometry().width() - 200)
    {
        expandAreaWidth = geometry().width() - 200;
    }

    graphics->show();
    areaSeparator->show();

    auto* animationGroup = new QParallelAnimationGroup();

    auto* animation1 = new QPropertyAnimation(graphics, "geometry");
    animation1->setDuration(100);
    animation1->setStartValue(graphics->geometry());
    animation1->setEndValue(QRect(0, 0, expandAreaWidth, geometry().height()));
    animation1->setEasingCurve(QEasingCurve::Linear);

    auto* animation2 = new QPropertyAnimation(areaSeparator, "geometry");
    animation2->setDuration(100);
    animation2->setStartValue(areaSeparator->geometry());
    animation2->setEndValue(QRect(expandAreaWidth - 1, 0, 1, geometry().height()));
    animation2->setEasingCurve(QEasingCurve::Linear);

    auto* animation3 = new QPropertyAnimation(plotWidget, "geometry");
    animation3->setDuration(100);
    animation3->setStartValue(plotWidget->geometry());
    animation3->setEndValue(QRect(expandAreaWidth, 0, geometry().width() - expandAreaWidth, geometry().height()));
    animation3->setEasingCurve(QEasingCurve::Linear);

    animationGroup->addAnimation(animation1);
    animationGroup->addAnimation(animation2);
    animationGroup->addAnimation(animation3);

    animationGroup->start(QAbstractAnimation::DeleteWhenStopped);

    plotWidget->hideExpandButton();
}
