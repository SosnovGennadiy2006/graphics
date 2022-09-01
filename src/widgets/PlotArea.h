//
// Created by genas on 30.08.2022.
//

#ifndef GRAPHICSPROJECT_PLOTAREA_H
#define GRAPHICSPROJECT_PLOTAREA_H

#include <QWidget>
#include <QResizeEvent>
#include "../widgets/buttons/IconsButton.h"

class PlotArea : public QWidget{
    Q_OBJECT

    IconsButton* expandButton;

    QVector<QString> graphics;

public:
    explicit PlotArea(QWidget* parent = Q_NULLPTR);

    void setupUI();

protected:
    void resizeEvent(QResizeEvent* event) override;

public slots:
    void hideExpandButton();
    void showExpandButton();

signals:
    void expandButtonClicked();
};


#endif//GRAPHICSPROJECT_PLOTAREA_H
