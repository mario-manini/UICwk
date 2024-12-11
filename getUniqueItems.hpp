#ifndef EXTRACTUNIQUECOLUMNS_HPP
#define EXTRACTUNIQUECOLUMNS_HPP

#include <QStringList>

class ExtractUniqueColumns
{
public:
    static QStringList extractUniqueColumnItems(const QString& filePath, int columnIndex);
};

#endif 
