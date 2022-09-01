//
// Created by genas on 30.08.2022.
//

#include "GraphicsListWidget.h"

GraphicsListWidget::GraphicsListWidget(QWidget* parent) : QWidget{parent}
{
    setupUI();

    graphics = QVector<GraphicsItem*>(0);
    lastColor = GraphicsColors::red;

    connect(expandLeftButton, &QPushButton::clicked, this, [this](){
        emit expandButtonClicked();
    });
    connect(addButton, &QPushButton::clicked, this, &GraphicsListWidget::addNewGraphic);
}

void GraphicsListWidget::setupUI()
{
    setAttribute(Qt::WA_StyledBackground, true);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    graphicsSettings = new QWidget(this);
    graphicsSettings->setFixedHeight(50);
    graphicsSettings->setObjectName("graphicsSettings");
    graphicsSettings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    settingsLayout = new QHBoxLayout(graphicsSettings);
    settingsLayout->setContentsMargins(5, 5, 5, 5);
    settingsLayout->setSpacing(5);

    addButton = new IconsButton(graphicsSettings);
    addButton->setEnabledIcon(QPixmap(":/resources/icons/add.png"));
    addButton->setHoverIcon(QPixmap(":/resources/icons/add_active.png"));
    addButton->setDisabledIcon(QPixmap(":/resources/icons/add_deactive.png"));
    addButton->setCursor(QCursor(Qt::PointingHandCursor));
    addButton->setObjectName("addButton");
    addButton->setFixedSize(40, 40);

    settingsButton = new IconsButton(graphicsSettings);
    settingsButton->setEnabledIcon(QPixmap(":/resources/icons/settings.png"));
    settingsButton->setHoverIcon(QPixmap(":/resources/icons/settings_active.png"));
    settingsButton->setDisabledIcon(QPixmap(":/resources/icons/settings_deactive.png"));
    settingsButton->setCursor(QCursor(Qt::PointingHandCursor));
    settingsButton->setObjectName("settingsButton");
    settingsButton->setFixedSize(40, 40);

    expandLeftButton = new IconsButton(graphicsSettings);
    expandLeftButton->setEnabledIcon(QPixmap(":/resources/icons/left_expand.png"));
    expandLeftButton->setHoverIcon(QPixmap(":/resources/icons/left_expand_active.png"));
    expandLeftButton->setDisabledIcon(QPixmap(":/resources/icons/left_expand_deactive.png"));
    expandLeftButton->setCursor(QCursor(Qt::PointingHandCursor));
    expandLeftButton->setObjectName("expandLeftButton");
    expandLeftButton->setFixedSize(40, 40);

    spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    settingsLayout->addWidget(addButton);
    settingsLayout->addItem(spacer);
    settingsLayout->addWidget(settingsButton);
    settingsLayout->addWidget(expandLeftButton);

    scrollArea = new QScrollArea(this);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    scrollArea->setWidgetResizable(true);
    scrollArea->setObjectName("scrollArea");
    scrollArea->setAttribute(Qt::WA_StyledBackground, true);

    graphicsWidget = new QWidget(this);
    graphicsWidget->setObjectName("graphicsWidget");
    graphicsWidget->setAttribute(Qt::WA_StyledBackground, true);
    graphicsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    scrollArea->setWidget(graphicsWidget);

    mainLayout->addWidget(graphicsSettings);
    mainLayout->addWidget(scrollArea);
}

void GraphicsListWidget::repaintGraphics(qsizetype last_idx)
{
    int marginRight = 0;

    if (graphics.size() * GraphicsItem::fixedHeight > scrollArea->geometry().height())
    {
        marginRight = 10;
    }

    for (qsizetype i = 0; i < last_idx; i++)
    {
        graphics[i]->setGeometry(0, i * GraphicsItem::fixedHeight - i - 1, geometry().width() - marginRight + 1, GraphicsItem::fixedHeight);
    }
    graphicsWidget->setFixedHeight(graphics.size() * GraphicsItem::fixedHeight);
}

void GraphicsListWidget::resizeEvent(QResizeEvent* event)
{
    repaintGraphics(graphics.size());
}

void GraphicsListWidget::renumberGraphics()
{
    for (qsizetype i = 0; i < graphics.size(); i++)
    {
        graphics[i]->setNumber(i + 1);
    }
}

void GraphicsListWidget::addNewGraphic()
{
    auto* graphic = new GraphicsItem(graphicsWidget);
    graphic->setColor(lastColor);
    graphics.push_back(graphic);
    graphic->show();

    lastColor = static_cast<GraphicsColors>((static_cast<int>(lastColor) + 1) % 7);
    if (lastColor == GraphicsColors::none)
    {
        lastColor = GraphicsColors::red;
    }

    renumberGraphics();
    repaintGraphics(graphics.size());

    emit newGraphicCreated(graphic->getFunction(), graphic->getColor());

    connect(graphic, &GraphicsItem::deleted, this, [this, graphic](){
        qsizetype idx = graphics.indexOf(graphic);

        if (graphic->state) {
            return;
        }

        emit graphicDeleted(idx);

        for (auto & _graphic : graphics)
        {
            _graphic->state = true;
        }

        auto* animationGroup = new QSequentialAnimationGroup();

        auto* disappearingAnimation = new QParallelAnimationGroup();

        auto* animation1 = new QPropertyAnimation(graphic, "geometry");
        animation1->setDuration(50);
        animation1->setStartValue(graphic->geometry());
        animation1->setEndValue(QRect(-graphic->geometry().width(), graphic->geometry().y(), graphic->geometry().width() + 1, graphic->geometry().height()));
        animation1->setEasingCurve(QEasingCurve::Linear);

        disappearingAnimation->addAnimation(animation1);

        auto* shiftAnimation = new QParallelAnimationGroup();

        for (qsizetype i = idx + 1; i < graphics.size(); i++)
        {
            auto* animation = new QPropertyAnimation(graphics[i], "geometry");
            animation->setDuration(50);
            animation->setStartValue(graphics[i]->geometry());
            animation->setEndValue(QRect(0, GraphicsItem::fixedHeight * (i - 1) - i, geometry().width() + 1, GraphicsItem::fixedHeight));
            animation->setEasingCurve(QEasingCurve::Linear);

            shiftAnimation->addAnimation(animation);
        }

        animationGroup->addAnimation(disappearingAnimation);
        animationGroup->addAnimation(shiftAnimation);

        animationGroup->start();

        connect(animationGroup, &QSequentialAnimationGroup::finished, [this, graphic](){
            graphics.removeOne(graphic);
            delete graphic;
            renumberGraphics();
            repaintGraphics(graphics.size());
            for (auto & _graphic : graphics)
            {
                _graphic->state = false;
            }
            graphicsWidget->setFixedHeight(graphics.size() * GraphicsItem::fixedHeight);
        });
    });

    connect(graphic, &GraphicsItem::functionChanged, this, [this, graphic](){
        qsizetype idx = graphics.indexOf(graphic);
        emit graphicChanged(idx, graphic->getFunction(), graphic->getColor());
    });
}