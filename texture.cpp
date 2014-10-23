#include "texture.h"

Texture::Texture(QString filename)
{
    QImage imgGL, img;

    if (!img.load(filename)) {
        throw "Failed to load texture file " + filename;
    }

    imgGL = QGLWidget::convertToGLFormat(img);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgGL.width(), imgGL.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imgGL.bits());
}
