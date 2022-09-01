//
// Created by genas on 31.08.2022.
//

#ifndef GRAPHICSPROJECT_GRAPHICSITEM_H
#define GRAPHICSPROJECT_GRAPHICSITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QLabel>
#include <QLineEdit>
#include <QGraphicsOpacityEffect>
#include "../widgets/buttons/IconsButton.h"
#include "../widgets/buttons/CustomButton.h"

enum GraphicsColors
{
    red = 0,
    blue,
    green,
    orange,
    purple,
    black
};

class GraphicsItem : public QWidget{
    Q_OBJECT

    QHBoxLayout* mainLayout;

    QWidget* colorPanel;

    QVBoxLayout* colorPanelLayout;
    QLabel* graphicsNumber;
    CustomButton* graphicsColorButton;

    QLineEdit* functionLineEdit;

    IconsButton* deleteGraphicsButton;

    GraphicsColors _color;
    bool _isShown;
    QPixmap colorIcon;

public:
    explicit GraphicsItem(QWidget* parent = Q_NULLPTR);

    void setupUI();

    bool isSelected();
    void toggleSelect();

    void setColor(GraphicsColors color);
    void setNumber(int newNumber);

    [[nodiscard]] GraphicsColors getColor() const;
    [[nodiscard]] bool isGraphicsShown() const;

    static const int fixedHeight = 50;

    bool state = false;

protected:
    void resizeEvent(QResizeEvent* event) override;

signals:
    void selected();
    void deleted();

public slots:
    void toggleGraphicsVisibility();
};


#endif//GRAPHICSPROJECT_GRAPHICSITEM_H
