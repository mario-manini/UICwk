#ifndef EXTRACTUNIQUECOLUMNS_HPP
#define EXTRACTUNIQUECOLUMNS_HPP

#include <QStringList>

class ExtractUniqueColumns
{
public:
    // Static method to extract unique items from a specific column in a CSV file
    static QStringList extractUniqueColumnItems(const QString& filePath, int columnIndex);
};

#endif // EXTRACTUNIQUECOLUMNS_HPP
