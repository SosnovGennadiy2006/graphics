//
// Created by genas on 30.08.2022.
//

#include "IconsButton.h"

IconsButton::IconsButton(QWidget *parent) : QPushButton{parent}
{
    setAttribute(Qt::WA_Hover, true);
    setAttribute(Qt::WA_StyledBackground, true);

    btnLayout = new QHBoxLayout();
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->setSpacing(0);

    setLayout(btnLayout);

    textLabel = new QLabel(this);
    textLabel->setMouseTracking(false);
    textLabel->setAlignment(Qt::AlignCenter);

    layout()->addWidget(textLabel);

    _icon = QPixmap();
    _hoverIcon = QPixmap();
    _disabledIcon = QPixmap();
}

void IconsButton::_setEnabled(bool _isEnabled)
{
    setDisabled(_isEnabled);

    if (isEnabled())
    {
        textLabel->setPixmap(_icon);
    }else
    {
        textLabel->setPixmap(_disabledIcon);
    }
}

void IconsButton::setEnabledIcon(const QPixmap &icon)
{
    _icon = icon;

    textLabel->setPixmap(icon);
}

void IconsButton::setHoverIcon(const QPixmap &icon)
{
    _hoverIcon = icon;
}

void IconsButton::setDisabledIcon(const QPixmap &icon)
{
    _disabledIcon = icon;
}

QIcon IconsButton::getIcon() const
{
    return _icon;
}

QIcon IconsButton::getHoverIcon() const
{
    return _hoverIcon;
}

QIcon IconsButton::getDisabledIcon() const
{
    return _disabledIcon;
}

bool IconsButton::event(QEvent* event)
{
    switch(event->type())
    {
        case (QEvent::HoverEnter):
        {
            hoverEvent(dynamic_cast<QHoverEvent*>(event));
            break;
        }
        case (QEvent::HoverLeave):
        {
            hoverLeave(dynamic_cast<QHoverEvent*>(event));
            break;
        }
        default:
            break;
    }
    return QPushButton::event(event);
}

void IconsButton::hoverEvent(QHoverEvent *event)
{
    if (isEnabled())
    {
        textLabel->setPixmap(_hoverIcon);
    }
}

void IconsButton::hoverLeave(QHoverEvent* event)
{
    if (isEnabled())
    {
        textLabel->setPixmap(_icon);
    }
}
