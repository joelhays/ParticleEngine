#ifndef RESOURCE_H
#define RESOURCE_H

#include <QList>
#include <QString>

class Resource
{
public:
    static QList<QString> particleImagePaths();
private:
    Resource();
};

#endif // RESOURCE_H
