#include "glwidget.h"

void GLWidget::updateEmitterProperty(double value) {
    if (!activeEmitter) return;

    QString sender = QObject::sender()->objectName();

    if (sender == "life") activeEmitter->life = value;
    else if (sender == "lifeRange") activeEmitter->lifeRange = value;
    else if (sender == "size") activeEmitter->size = value;
    else if (sender == "sizeRange") activeEmitter->sizeRange = value;
    else if (sender == "spread") activeEmitter->spread = value;
    else if (sender == "saturation") activeEmitter->saturation = value;
    else if (sender == "emissionRadius") activeEmitter->emissionRadius = value;
    else if (sender == "gravity") activeEmitter->gravity = value;
    else if (sender == "offsetX") activeEmitter->position.setX(value);
    else if (sender == "offsetY") activeEmitter->position.setY(value);
    else if (sender == "offsetZ") activeEmitter->position.setZ(value);
    else if (sender == "vortex") activeEmitter->rotation.setY(value);
    else if (sender == "alpha") activeEmitter->alpha = value;
}

void GLWidget::updateEmitterProperty(int value) {
    if (!activeEmitter) return;

    QString sender = QObject::sender()->objectName();

    if (sender == "emissionRate") activeEmitter->emissionRate = value;
}

void GLWidget::updateEmitterTexture(int index)
{
    if (!activeEmitter) return;
    activeEmitter->setTexture(textures[index]);
}

void GLWidget::updateEmitterTextureBlendMode(int index)
{
    if (!activeEmitter) return;
    activeEmitter->textureBlendMode = (Emitter::TEXTURE_BLEND_MODE)index;
}

void GLWidget::updateActiveEmitter(int index)
{
    if (index < 0) activeEmitter = NULL;
    else activeEmitter = emitters[index];
}

void GLWidget::addEmitter()
{
    emitters.append(new Emitter());
}

void GLWidget::deleteEmitter(int index)
{
    if (activeEmitter == emitters[index])
        activeEmitter = NULL;

    delete emitters.takeAt(index);
}

void GLWidget::updateEmitterIndex(int previousIndex, int newIndex)
{
    emitters.move(previousIndex, newIndex);
}
