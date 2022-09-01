//
// Created by genas on 31.08.2022.
//

#ifndef GRAPHICSPROJECT_CUSTOMBUTTON_H
#define GRAPHICSPROJECT_CUSTOMBUTTON_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

class CustomButton : public QPushButton {
    Q_OBJECT

    QHBoxLayout* btnLayout;
    QLabel* btnLabel;

public:
    explicit CustomButton(QWidget* parent = Q_NULLPTR) : QPushButton{parent}
    {
        btnLayout = new QHBoxLayout();
        btnLayout->setSpacing(0);
        btnLayout->setContentsMargins(0, 0, 0, 0);
        setLayout(btnLayout);

        btnLabel = new QLabel(this);

        btnLayout->addWidget(btnLabel, 1, Qt::AlignCenter);
    }

    void setIcon(const QPixmap& pixmap)
    {
        btnLabel->setPixmap(pixmap);
    }
};


#endif//GRAPHICSPROJECT_CUSTOMBUTTON_H
