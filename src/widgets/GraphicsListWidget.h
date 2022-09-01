//
// Created by genas on 30.08.2022.
//

#ifndef GRAPHICSPROJECT_GRAPHICSLISTWIDGET_H
#define GRAPHICSPROJECT_GRAPHICSLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QScrollArea>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include "../widgets/GraphicsItem.h"
#include "../widgets/buttons/IconsButton.h"

class GraphicsListWidget : public QWidget {
    Q_OBJECT

    QVBoxLayout* mainLayout;
    QWidget* graphicsSettings;
    QHBoxLayout* settingsLayout;

    IconsButton* addButton;
    IconsButton* settingsButton;
    IconsButton* expandLeftButton;

    QSpacerItem* spacer;

    QScrollArea* scrollArea;

    QWidget* graphicsWidget;

    QVector<GraphicsItem*> graphics;

    GraphicsColors lastColor;

public:
    explicit GraphicsListWidget(QWidget* parent = Q_NULLPTR);

    void setupUI();

    void renumberGraphics();

    void repaintGraphics(qsizetype last_idx);

protected:
    void resizeEvent(QResizeEvent* event) override;

public slots:
    void addNewGraphic();

signals:
    void expandButtonClicked();
    void newGraphicCreated(const QString& graphicFunction, GraphicsColors color);
    void graphicDeleted(qsizetype idx);
    void graphicChanged(qsizetype idx, const QString& newFunction, GraphicsColors newColor);
};


#endif//GRAPHICSPROJECT_GRAPHICSLISTWIDGET_H
