#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>

#include <qmatrix4x4.h>

#include "resource.h"
#include "texture.h"
#include "camera.h"
#include "emitter.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    // _input
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);

public:
    int activeEmitterTextureIndex();
    int numEmitters();

public:
    Emitter* activeEmitter;

signals:
    void glInitialized();

public slots:
    void updateEmitterProperty(double value);
    void updateEmitterProperty(int value);
    void updateEmitterTexture(int index);
    void updateEmitterTextureBlendMode(int index);
    void updateActiveEmitter(int index);
    void addEmitter();
    void deleteEmitter(int index);

    void updateEmitterIndex(int previousIndex, int newIndex);

private:
    void loadTextures();
    void transformCamera();
    void drawGrid();

private:
    QTimer timer;
    Camera camera;

    QPoint prevMousePos;
    std::map<int, bool> key, mouse;

    QList<Texture*> textures;
    QList<Emitter*> emitters;
};

#endif // GLWIDGET_H
