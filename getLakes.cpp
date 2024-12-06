#include "getLakes.hpp"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QSet>

QStringList ExtractUniqueColumns::extractUniqueColumnItems(const QString& filePath, int columnIndex) {
    QStringList uniqueItems;
    QFile file(filePath);
    
    // Check if the file exists and can be opened
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return uniqueItems;
    }

    QTextStream in(&file);
    bool headerLine = true;  // To skip the header row if needed

    while (!in.atEnd()) {
        QString line = in.readLine();

        // Skip header line if it's the first line
        if (headerLine) {
            headerLine = false;
            continue;
        }

        // Split the line by commas (assuming CSV format with commas as separators)
        QStringList fields = line.split(',');

        // Ensure the column index is valid
        if (columnIndex < fields.size()) {
            QString item = fields[columnIndex].trimmed();  // Remove any leading/trailing spaces
            if (!item.isEmpty()) {
                uniqueItems.append(item);  // Add item to the list
            }
        }
    }

    file.close();

    // Remove duplicates by converting QStringList to QSet and back to QStringList
    QSet<QString> uniqueSet(uniqueItems.begin(), uniqueItems.end());  // Create QSet from QStringList
    uniqueItems = QStringList(uniqueSet.begin(), uniqueSet.end());  // Convert QSet back to QStringList

    return uniqueItems;
}
