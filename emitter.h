#ifndef EMITTER_H
#define EMITTER_H

#include <qgl.h>

#include "glextensions.h"

#include <QList>
#include "particle.h"
#include "texture.h"

class Emitter
{
public:
    Emitter();
    ~Emitter();

    void Update(float time);
    void setTexture(Texture *texture);

protected:
    void addParticle(void);
    float frand(float start = 0, float end = 1);

public:
    enum TEXTURE_BLEND_MODE
    {
        BLEND_NORMAL = 0,
        BLEND_NOCOLOR,
        BLEND_SUBTRACT
    };

public:
    QList<Particle *> particles;
    Texture *texture;
    TEXTURE_BLEND_MODE textureBlendMode;

    bool active;

    float
        emissionRate, emissionRadius,
        life, lifeRange,
        size, sizeRange,
        saturation, alpha,
        spread,
        gravity;

    QVector3D
        position,
        wind,
        rotation;

private:
    float elapsedTime;

};

#endif // EMITTER_H
