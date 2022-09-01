//
// Created by genas on 31.08.2022.
//

#include "GraphicsItem.h"

GraphicsItem::GraphicsItem(QWidget *parent) : QWidget{parent}
{
    _isShown = true;
    setupUI();
    setColor(GraphicsColors::red);

    connect(graphicsColorButton, &QPushButton::clicked, this, \
            &GraphicsItem::toggleGraphicsVisibility);
    connect(deleteGraphicsButton, &QPushButton::clicked, this, [this](){
        emit deleted();
    });
    connect(functionLineEdit, &QLineEdit::textChanged, this, [this](const QString& val){
        emit functionChanged();
    });
}

void GraphicsItem::setupUI()
{
    setFixedHeight(fixedHeight);
    setObjectName("graphicsItem");
    setProperty("isSelected", false);
    setAttribute(Qt::WA_StyledBackground, true);

    QFont smallFont = QFont();
    smallFont.setFamily("Leelawadee UI");
    smallFont.setPixelSize(10);
    QFont lineEditFont = QFont();
    lineEditFont.setFamily("Cambria");
    lineEditFont.setPixelSize(18);

    mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    colorPanel = new QWidget(this);
    colorPanel->setFixedSize(40, fixedHeight);
    colorPanel->setObjectName("colorPanel");
    colorPanel->installEventFilter(this);

    colorPanelLayout = new QVBoxLayout(colorPanel);
    colorPanelLayout->setContentsMargins(0, 0, 0, 0);
    colorPanelLayout->setSpacing(3);

    graphicsNumber = new QLabel(colorPanel);
    graphicsNumber->setFont(smallFont);
    graphicsNumber->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    graphicsNumber->setObjectName("graphicsNumber");
    graphicsNumber->setGeometry(0, 0, 40, 20);

    graphicsColorButton = new CustomButton(colorPanel);
    graphicsColorButton->setObjectName("colorButton");
    graphicsColorButton->setFixedSize(29, 29);
    graphicsColorButton->setCursor(QCursor(Qt::PointingHandCursor));
    graphicsColorButton->setIconSize(QSize(29, 29));

    colorPanelLayout->addWidget(graphicsColorButton, 1, Qt::AlignCenter);

    functionLineEdit = new QLineEdit(this);
    functionLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    functionLineEdit->setObjectName("functionLineEdit");
    functionLineEdit->setFont(lineEditFont);
    functionLineEdit->setText("y=x");
    functionLineEdit->installEventFilter(this);

    deleteGraphicsButton = new IconsButton(this);
    deleteGraphicsButton->setEnabledIcon(QPixmap(":/resources/icons/close.png"));
    deleteGraphicsButton->setHoverIcon(QPixmap(":/resources/icons/close_active.png"));
    deleteGraphicsButton->setDisabledIcon(QPixmap(":/resources/icons/close_deactive.png"));
    deleteGraphicsButton->setObjectName("deleteGraphics");
    deleteGraphicsButton->setCursor(QCursor(Qt::PointingHandCursor));
    deleteGraphicsButton->setFixedSize(30, 30);

    deleteGraphicsButton->setGeometry(this->geometry().width() - 30, 0, \
                                      30, 30);

    functionLineEdit->stackUnder(deleteGraphicsButton);

    mainLayout->addWidget(colorPanel);
    mainLayout->addWidget(functionLineEdit);
}

bool GraphicsItem::isSelected()
{
    return property("isSelected").toBool();
}

void GraphicsItem::toggleSelect()
{
    setProperty("isSelected", !isSelected());
    setStyleSheet(styleSheet()); // update styles
}

void GraphicsItem::setColor(GraphicsColors color)
{
    _color = color;
    switch(color)
    {
        case (GraphicsColors::black):
            colorIcon = QPixmap(":/resources/icons/graphicsColors/black.png");
            break;
        case red:
            colorIcon = QPixmap(":/resources/icons/graphicsColors/red.png");
            break;
        case blue:
            colorIcon = QPixmap(":/resources/icons/graphicsColors/blue.png");
            break;
        case green:
            colorIcon = QPixmap(":/resources/icons/graphicsColors/green.png");
            break;
        case orange:
            colorIcon = QPixmap(":/resources/icons/graphicsColors/orange.png");
            break;
        case purple:
            colorIcon = QPixmap(":/resources/icons/graphicsColors/purple.png");
            break;
    }

    if (_isShown)
    {
        graphicsColorButton->setIcon(colorIcon);
    }
}

void GraphicsItem::setNumber(int newNumber)
{
    graphicsNumber->setText(QString::number(newNumber));
}

QString GraphicsItem::getFunction() const
{
    return functionLineEdit->text();
}

GraphicsColors GraphicsItem::getColor() const
{
    if (!_isShown)
    {
        return GraphicsColors::none;
    }
    return _color;
}

bool GraphicsItem::isGraphicsShown() const
{
    return _isShown;
}

void GraphicsItem::resizeEvent(QResizeEvent *event)
{
    deleteGraphicsButton->setGeometry(event->size().width() - deleteGraphicsButton->width(), 0, \
                                      deleteGraphicsButton->width(), deleteGraphicsButton->height());
}

void GraphicsItem::toggleGraphicsVisibility()
{
    _isShown = !_isShown;

    if (_isShown)
    {
        graphicsColorButton->setIcon(colorIcon);
        emit functionChanged();
        return;
    }
    graphicsColorButton->setIcon(QPixmap(":/resources/icons/graphicsColors/opacity.png"));
    emit functionChanged();
}
