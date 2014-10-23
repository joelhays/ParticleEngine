#include "glwidget.h"
#include <QSlider>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    // make this widget accept input
    this->setFocusPolicy(Qt::StrongFocus);
    this->focusWidget();

    // set up timer to automatically call updateGL, which controls when the widget is repainted
    // 16ms = ~62fps
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

GLWidget::~GLWidget()
{
    for (int e = emitters.length()-1; e >= 0; e--)
        deleteEmitter(e);

    for (int t = textures.length()-1; t >= 0; t--)
        delete textures.takeAt(t);
}

void GLWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0,0,0,0);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_PERSPECTIVE_CORRECTION_HINT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    loadTextures();

    emit glInitialized();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    transformCamera();
    drawGrid();

    foreach (Emitter* emitter, emitters)
    {
        emitter->Update((float)timer.interval() / 1000.0f);
    }
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, (GLfloat)w/(GLfloat)h, .001, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::loadTextures() {
    foreach(QString imagePath, Resource::particleImagePaths())
        textures.append(new Texture(imagePath));
}

int GLWidget::activeEmitterTextureIndex()
{
    return textures.indexOf(activeEmitter->texture);
}

int GLWidget::numEmitters()
{
    return emitters.length();
}

void GLWidget::transformCamera()
{
    QMatrix4x4 mCamera;
    //translate to the camera's positions offset by the lookat vector so that
    //all rotations appear at the center of the screen
    mCamera.translate(-camera.lookAt.x(), -camera.lookAt.y(), -camera.distance - camera.lookAt.z());

    //now translate to the camera's lookat and rotate around that point
    mCamera.translate(camera.lookAt.x(), camera.lookAt.y(), camera.lookAt.z());
    mCamera.rotate(camera.rotationY);
    mCamera.rotate(camera.rotationX);

    //translate back to the camera's position or the view will be offset
    mCamera.translate(-camera.lookAt.x(), -camera.lookAt.y(), -camera.lookAt.z());

    //apply the transformation matrix
    glMultMatrixd(mCamera.constData());
}

void GLWidget::drawGrid()
{
    glDisable(GL_TEXTURE_2D);

    glColor3f(0, 1, 0);
    glPointSize(1);
    glLineWidth(1);

    float sizeHalf = 5;

    glBegin(GL_LINES);
    {
        for(int i=-sizeHalf;i<=sizeHalf;i++)
        {
            glVertex3f(-sizeHalf, 0, i);
            glVertex3f(sizeHalf, 0, i);

            glVertex3f(i, 0, -sizeHalf);
            glVertex3f(i, 0, sizeHalf);
        };
    }
    glEnd();
}
