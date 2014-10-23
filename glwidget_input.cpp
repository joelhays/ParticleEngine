#include "glwidget.h"

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    key[e->key()] = true;

    if (key[Qt::Key_F])
    {
        camera.reset();
        return;
    }
}

void GLWidget::keyReleaseEvent(QKeyEvent *e)
{
    key[e->key()] = false;
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{
    prevMousePos = e->pos();

    mouse[e->button()] = true;
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mouse[e->button()] = false;
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    int xdelta = e->pos().x() - prevMousePos.x();
    int ydelta =  e->pos().y() - prevMousePos.y();

    if (/*ROTATE*/ mouse[Qt::LeftButton])
    {
        camera.rotate(xdelta, ydelta);
    }
    else if (/*PAN*/ mouse[Qt::MiddleButton])
    {
        camera.pan(xdelta, ydelta);
    }
    else if (/*ZOOM*/ mouse[Qt::RightButton])
    {
        camera.zoom(xdelta);
    }

    prevMousePos = e->pos();
}

void GLWidget::wheelEvent(QWheelEvent *e)
{
    camera.zoom(e->delta());
}
