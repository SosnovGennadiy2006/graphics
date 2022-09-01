//
// Created by genas on 30.08.2022.
//

#ifndef GRAPHICSPROJECT_PLOTAREA_H
#define GRAPHICSPROJECT_PLOTAREA_H

#include <QWidget>
#include <QResizeEvent>
#include "../widgets/buttons/IconsButton.h"
#include "../widgets/other/StyleSheetsHelper.h"
#include "../external/QCustomPlot/qcustomplot.h"
#include "../external/parser/muParser.h"

class PlotArea : public QWidget{
    Q_OBJECT

    IconsButton* expandButton;
    QCustomPlot* plotWidget;

    QVector<QString> graphicsFunctions;
    QVector<QColor> graphicsColors;

    double h;
    double startX, endX;
    double startY, endY;

public:
    explicit PlotArea(QWidget* parent = Q_NULLPTR);

    void setupUI();

    void repaintGraphics();

protected:
    void resizeEvent(QResizeEvent* event) override;

public slots:
    void hideExpandButton();
    void showExpandButton();

    void createNewGraphic(const QString& graphicFunction, GraphicsColors color);
    void deleteGraphic(qsizetype idx);
    void changeGraphic(qsizetype idx, const QString& newFunction, GraphicsColors color);

signals:
    void expandButtonClicked();
};


#endif//GRAPHICSPROJECT_PLOTAREA_H
