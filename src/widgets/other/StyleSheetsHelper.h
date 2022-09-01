//
// Created by genas on 30.08.2022.
//

#ifndef GRAPHICSPROJECT_STYLESHEETSHELPER_H
#define GRAPHICSPROJECT_STYLESHEETSHELPER_H

#include <QFile>

enum GraphicsColors
{
    red = 0,
    blue,
    green,
    orange,
    purple,
    black,
    none
};

class StyleSheetsHelper {
public:
    static QString loadStyles(const QString& path)
    {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly))
        {
            return "";
        }
        return QLatin1String(file.readAll());
    }

    static QColor colorNameToColor(GraphicsColors color)
    {
        switch (color) {
            case (red):
                return {197, 70, 66};
            case blue:
                return {54, 106, 178};
            case green:
                return {56, 142, 70};
            case orange:
                return {247, 130, 33};
            case purple:
                return {99, 56, 166};
            case black:
                return {255, 255, 255};
            case none:
                return {255, 255, 255, 0};
        }
    }
};

#endif//GRAPHICSPROJECT_STYLESHEETSHELPER_H
