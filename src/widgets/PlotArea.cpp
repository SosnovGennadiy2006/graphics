//
// Created by genas on 30.08.2022.
//

#include "PlotArea.h"

PlotArea::PlotArea(QWidget* parent) : QWidget{parent}
{
    setupUI();

    graphics = QVector<QString>(0);

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
}

void PlotArea::resizeEvent(QResizeEvent *event)
{

}

void PlotArea::hideExpandButton()
{
    expandButton->hide();
}

void PlotArea::showExpandButton()
{
    expandButton->show();
}
