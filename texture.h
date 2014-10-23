#ifndef TEXTURE_H
#define TEXTURE_H

#include <qgl.h>
#include <QString>
#include <QImage>

class Texture
{
public:
    Texture(QString filename);

public:
    GLuint id;
};

#endif // TEXTURE_H
