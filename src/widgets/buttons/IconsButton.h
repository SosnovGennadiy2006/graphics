//
// Created by genas on 30.08.2022.
//

#ifndef GRAPHICSPROJECT_ICONSBUTTON_H
#define GRAPHICSPROJECT_ICONSBUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QEvent>
#include <QHoverEvent>

class IconsButton : public QPushButton{
    Q_OBJECT

    QLabel* textLabel;
    QHBoxLayout* btnLayout;

    QPixmap _icon;
    QPixmap _hoverIcon;
    QPixmap _disabledIcon;

public:
    explicit IconsButton(QWidget* parent = Q_NULLPTR);

    void _setEnabled(bool _isEnabled);

    void setEnabledIcon(const QPixmap& icon);
    void setHoverIcon(const QPixmap& icon);
    void setDisabledIcon(const QPixmap& icon);

    [[nodiscard]] QIcon getIcon() const;
    [[nodiscard]] QIcon getHoverIcon() const;
    [[nodiscard]] QIcon getDisabledIcon() const;

protected:
    bool event(QEvent* event) override;

    void hoverEvent(QHoverEvent* event);
    void hoverLeave(QHoverEvent* event);
};


#endif//GRAPHICSPROJECT_ICONSBUTTON_H
