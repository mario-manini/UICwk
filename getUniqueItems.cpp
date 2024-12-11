#include "getUniqueItems.hpp"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QSet>

QStringList ExtractUniqueColumns::extractUniqueColumnItems(const QString& filePath, int columnIndex) {
    QStringList uniqueItems;
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return uniqueItems;
    }

    QTextStream in(&file);
    bool headerLine = true;  

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (headerLine) {
            headerLine = false;
            continue;
        }

        QStringList fields = line.split(',');


        if (columnIndex < fields.size()) {
            QString item = fields[columnIndex].trimmed();  
            if (!item.isEmpty()) {
                uniqueItems.append(item);  
            }
        }
    }

    file.close();

    QSet<QString> uniqueSet(uniqueItems.begin(), uniqueItems.end());  
    uniqueItems = QStringList(uniqueSet.begin(), uniqueSet.end());  

    return uniqueItems;
}
