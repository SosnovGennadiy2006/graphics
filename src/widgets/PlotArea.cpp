//
// Created by genas on 30.08.2022.
//

#include "PlotArea.h"

PlotArea::PlotArea(QWidget* parent) : QWidget{parent}
{
    setupUI();

    graphicsFunctions = QVector<QString>(0);
    graphicsColors = QVector<QColor>(0);

    connect(expandButton, &QPushButton::clicked, this, [this](){
        emit expandButtonClicked();
    });
}

void PlotArea::setupUI()
{
    setAttribute(Qt::WA_StyledBackground, true);

    expandButton = new IconsButton(this);
    expandButton->setEnabledIcon(QPixmap(":/resources/icons/right_expand.png"));
    expandButton->setDisabledIcon(QPixmap(":/resources/icons/right_expand_deactive.png"));
    expandButton->setHoverIcon(QPixmap(":/resources/icons/right_expand_active.png"));
    expandButton->setCursor(QCursor(Qt::PointingHandCursor));
    expandButton->setObjectName("expandRightButton");
    expandButton->setFixedSize(40, 40);

    expandButton->setGeometry(5, 5, 40, 40);

    plotWidget = new QCustomPlot(this);
    plotWidget->setObjectName("plotWidget");
    plotWidget->setGeometry(0, 0, geometry().width(), geometry().height());
    startX = -10;
    startY = -10;
    endX = 10;
    endY = 10;
    h = (endX - endY) / 2000;
    plotWidget->stackUnder(expandButton);
    plotWidget->xAxis->setRange(startX, endX);
    plotWidget->yAxis->setRange(startY, endY);
    plotWidget->show();
}

void PlotArea::repaintGraphics()
{
    QVector<double> dotsX = QVector<double>(0);
    QVector<double> dotsY = QVector<double>(0);
    mu::Parser p;

    for (qsizetype i = 0; i < graphicsFunctions.size(); i++)
    {
        plotWidget->graph(i)->setPen(QPen(graphicsColors[i]));

        dotsX = QVector<double>(0);
        dotsY = QVector<double>(0);

        if (graphicsFunctions[i].startsWith("y="))
        {
            for (double j = startX; j <= endX + h; j += h)
            {
                QString function = graphicsFunctions[i];
                function = function.mid(2);
                qsizetype idx = function.indexOf("x");

                while (idx >= 0)
                {
                    function.replace(idx, 1, "(" + QString::number(j) + ")");

                    idx = function.indexOf("x");
                }

                try
                {
                    p.SetExpr(function.toStdWString());
                    mu::value_type result = p.Eval();
                    dotsX.push_back(j);
                    dotsY.push_back(result);
                }
                catch(mu::Parser::exception_type &e)
                {
                    continue;
                }
            }
        }

        plotWidget->graph(i)->setData(dotsX, dotsY);
    }

    plotWidget->replot();
}

void PlotArea::resizeEvent(QResizeEvent *event)
{
    startX = static_cast<double>(geometry().size().width()) / event->size().width() * startX;
    startY = static_cast<double>(-geometry().size().width()) / event->size().width() * startX;
    endX = static_cast<double>(geometry().size().height()) / event->size().height() * startY;
    endY = static_cast<double>(-geometry().size().height()) / event->size().height() * startY;
    h = (endX - endY) / 2000;
    plotWidget->xAxis->setRange(startX, endX);
    plotWidget->yAxis->setRange(startY, endY);
    plotWidget->setGeometry(0, 0, event->size().width(), event->size().height());
    repaintGraphics();
}

void PlotArea::hideExpandButton()
{
    expandButton->hide();
}

void PlotArea::showExpandButton()
{
    expandButton->show();
}

void PlotArea::createNewGraphic(const QString &graphicFunction, GraphicsColors color)
{
    graphicsFunctions.push_back(graphicFunction.trimmed());
    graphicsColors.push_back(StyleSheetsHelper::colorNameToColor(color));

    plotWidget->addGraph();

    repaintGraphics();
}

void PlotArea::deleteGraphic(qsizetype idx)
{
    graphicsFunctions.remove(idx);
    graphicsColors.remove(idx);

    plotWidget->removeGraph(idx);

    repaintGraphics();
}

void PlotArea::changeGraphic(qsizetype idx, const QString &newFunction, GraphicsColors color)
{
    graphicsFunctions[idx] = newFunction.trimmed();
    graphicsColors[idx] = StyleSheetsHelper::colorNameToColor(color);

    repaintGraphics();
}
