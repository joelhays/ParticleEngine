#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //clear margins from the main layout
    ui->horizontalLayout->setContentsMargins(0,0,0,0);

    //populate the particle images into the QListWidget and select the first image
    foreach(QString imagePath, Resource::particleImagePaths())
    {
        QListWidgetItem *item=new QListWidgetItem(QIcon(imagePath), "");
        ui->particleImage->addItem(item);
    }
    ui->particleImage->setCurrentRow(0);

    connectSpinnersWithSliders();

    connect(ui->emitters, SIGNAL(currentRowChanged(int)), this, SLOT(selectedEmitterChanged(int)));
    connect(ui->emitters->model(), SIGNAL(layoutChanged()), this, SLOT(rearrangeEmitters()));

    connect(ui->btnAddEmitter, SIGNAL(clicked()), this, SLOT(addEmitter()));
    connect(ui->btnToggleEmitter, SIGNAL(clicked()), this, SLOT(toggleEmitter()));
    connect(ui->btnDeleteEmitter, SIGNAL(clicked()), this, SLOT(deleteEmitter()));

    //Notify this UI that the QGLWidget has been initialized and it's safe start using.
    connect(ui->glView, SIGNAL(glInitialized()), this, SLOT(glInitialized()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::glInitialized()
{
    addEmitter();
    connectControlsToEmitter();
}

void MainWindow::connectSpinnersWithSliders()
{
    foreach(QDoubleSpinBox* spinbox, this->findChildren<QDoubleSpinBox*>())
        connect(spinbox, SIGNAL(valueChanged(double)), this, SLOT(convertSpinboxValueToSlider(double)));

    foreach(QSpinBox* spinbox, this->findChildren<QSpinBox*>())
        connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(convertSpinboxValueToSlider(int)));

    foreach(QSlider* slider, this->findChildren<QSlider*>())
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(convertSliderValueToSpinbox(int)));
}

void MainWindow::setControlValuesFromEmitter()
{
    if (!ui->glView->activeEmitter) return;

    ui->life->setValue(ui->glView->activeEmitter->life);
    ui->lifeRange->setValue(ui->glView->activeEmitter->lifeRange);
    ui->size->setValue(ui->glView->activeEmitter->size);
    ui->sizeRange->setValue(ui->glView->activeEmitter->sizeRange);
    ui->spread->setValue(ui->glView->activeEmitter->spread);
    ui->saturation->setValue(ui->glView->activeEmitter->saturation);
    ui->emissionRadius->setValue(ui->glView->activeEmitter->emissionRadius);
    ui->emissionRate->setValue(ui->glView->activeEmitter->emissionRate);
    ui->gravity->setValue(ui->glView->activeEmitter->gravity);
    ui->offsetX->setValue(ui->glView->activeEmitter->position.x());
    ui->offsetY->setValue(ui->glView->activeEmitter->position.y());
    ui->offsetZ->setValue(ui->glView->activeEmitter->position.z());
    ui->vortex->setValue(ui->glView->activeEmitter->rotation.y());
    ui->alpha->setValue(ui->glView->activeEmitter->alpha);

    ui->blendMode->setCurrentIndex((int)ui->glView->activeEmitter->textureBlendMode);

    ui->particleImage->setCurrentRow(ui->glView->activeEmitterTextureIndex());

}

void MainWindow::connectControlsToEmitter()
{
    //connect spinners to update the emitter
    connect(ui->life, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->lifeRange, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->size, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->sizeRange, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->spread, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->saturation, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->emissionRadius, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->emissionRate, SIGNAL(valueChanged(int)), ui->glView, SLOT(updateEmitterProperty(int)));
    connect(ui->gravity, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->offsetX, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->offsetY, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->offsetZ, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->vortex, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));
    connect(ui->alpha, SIGNAL(valueChanged(double)), ui->glView, SLOT(updateEmitterProperty(double)));

    //connect particle image list
    connect(ui->particleImage, SIGNAL(currentRowChanged(int)), ui->glView, SLOT(updateEmitterTexture(int)));

    connect(ui->blendMode, SIGNAL(currentIndexChanged(int)), ui->glView, SLOT(updateEmitterTextureBlendMode(int)));
}

void MainWindow::convertSpinboxValueToSlider(int value)
{
    //The associated slider for a spinbox has the same name, plus s_ at the beginning.
    QString associatedObjectName = "s_" + QObject::sender()->objectName();
    QSlider *slider = this->findChild<QSlider*>(associatedObjectName);
    if (slider) slider->setValue(value);
}

void MainWindow::convertSpinboxValueToSlider(double value)
{
    //The associated slider for a spinbox has the same name, plus s_ at the beginning.
    QString associatedObjectName = "s_" + QObject::sender()->objectName();
    int newValue = (int)(value * 100);

    QSlider *slider = this->findChild<QSlider*>(associatedObjectName);
    if (slider) slider->setValue(newValue);
}

void MainWindow::convertSliderValueToSpinbox(int value)
{
    //The associated spinbox for a slider has the same name, minus the s_ at the beginning.
    QString associatedObjectName = QObject::sender()->objectName().remove(0, 2);
    float newValue = (float) value / 100.0f;

    QDoubleSpinBox *doublespinbox = this->findChild<QDoubleSpinBox*>(associatedObjectName);
    if (doublespinbox) doublespinbox->setValue(newValue);
    else {
        QSpinBox *spinbox = this->findChild<QSpinBox*>(associatedObjectName);
        if (spinbox) spinbox->setValue(value);
    }
}

void MainWindow::selectedEmitterChanged(int index)
{
    ui->glView->updateActiveEmitter(index);
    setControlValuesFromEmitter();
}

void MainWindow::addEmitter()
{
    static int totalEmittersAdded = 0;
    totalEmittersAdded++;

    ui->glView->addEmitter();

    int emitterIndex = ui->glView->numEmitters() - 1;

    ui->glView->updateActiveEmitter(emitterIndex);
    ui->glView->updateEmitterTexture(0);

    setControlValuesFromEmitter();

    QListWidgetItem *item = new QListWidgetItem("Emitter " + QString::number(totalEmittersAdded));
    //Use Qt's User Role to store the corresponding index in the emitter list.
    //This will be used when we rearrange emitters in the QListWidget to adjust the underlying list
    item->setData(Qt::UserRole, emitterIndex);
    ui->emitters->addItem(item);

    ui->emitters->setCurrentRow(emitterIndex);
}

void MainWindow::toggleEmitter()
{
    QListWidgetItem *item = ui->emitters->selectedItems().at(0);
    QColor color;
    bool active = ui->glView->activeEmitter->active;

    if (active)
        color = ui->emitters->palette().color(QPalette::Disabled, QPalette::Text);
    else
        color = ui->emitters->palette().color(QPalette::Active, QPalette::Text);

    item->setData(Qt::TextColorRole, color);

    ui->glView->activeEmitter->active = !active;
}

void MainWindow::deleteEmitter()
{
    int deletedEmitterIndex = ui->emitters->currentRow();

    //Delete the selected emitter from the QListWidget.
    //Qt will automatically select a different emitter and emit the changed signal to selectedEmitterChanged slot.
    delete ui->emitters->selectedItems().at(0);

    //Tell the GLWidget to delete the emitter from its list.
    ui->glView->deleteEmitter(deletedEmitterIndex);

    //Now that the item has been deleted, need to update the data on each item to reflect
    //the index in the actual list.
    for(int i = 0; i < ui->emitters->count(); i++)
    {
        QListWidgetItem *item = ui->emitters->item(i);
        item->setData(Qt::UserRole, i);
    }
}

void MainWindow::rearrangeEmitters()
{
    bool bUpdated = false;

    for(int i = 0; i < ui->emitters->count(); i++)
    {
        QListWidgetItem *item = ui->emitters->item(i);

        //Get the previous list index and set the data on the QListWidgetItem
        //to the current index
        int previousIndex = item->data(Qt::UserRole).toInt();
        item->setData(Qt::UserRole, i);

        //If the previous index = the current index, the item has not moved, so don't update its
        //index in the underlying emitters list.
        if (previousIndex == i) continue;

        //As we iterate, we will be updating the first item that has a different index.
        //All items after this item will also have a different index, but updating the
        //index in the underlying list will automatically adjust any subsequent items.
        //If we have already updated 1 item, then we only need to adjust the data on the item,
        //and the underlying list does not need to be changed anymore.
        if (bUpdated == true) continue;

        //Found the first item with a different index, so update its position in the list
        //and set updated to true so we don't do this anymore.
        ui->glView->updateEmitterIndex(previousIndex, i);

        bUpdated = true;
    }
}
