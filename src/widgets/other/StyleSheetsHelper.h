//
// Created by genas on 30.08.2022.
//

#ifndef GRAPHICSPROJECT_STYLESHEETSHELPER_H
#define GRAPHICSPROJECT_STYLESHEETSHELPER_H

#include <QFile>

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
};

#endif//GRAPHICSPROJECT_STYLESHEETSHELPER_H
