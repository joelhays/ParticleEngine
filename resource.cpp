#include "resource.h"

#include <QDir>
#include <QFileInfo>

Resource::Resource()
{
}

QList<QString> Resource::particleImagePaths()
{
    QList<QString> files;

    QDir dir(":/images");
    foreach(QFileInfo file, dir.entryList())
    {
        QString imagePath = dir.absolutePath() + "/" + file.fileName();
        files.append(imagePath);
    }

    return files;
}
