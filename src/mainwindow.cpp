#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    f = new Field(this);
    connect(f, SIGNAL(nextStep()), this, SLOT(update()));
}

void MainWindow::paintEvent(QPaintEvent *e) {
    QImage im(FIELD_WIDTH, FIELD_HEIGHT, QImage::Format_RGB888);
    QPainter imagePainter(&im);
    if(run) {
        for (int i = 0; i < FIELD_WIDTH ; ++i) {
            for (int j = 0; j < FIELD_HEIGHT; ++j) {
                if(f->getCell(Coords{i, j}).getWolfIndexesSize() &&
                        f->getCell(Coords{i, j}).getRabbitIndexesSize()) {
                    imagePainter.setPen(Qt::yellow);
                    imagePainter.drawPoint(i, j);
                }else if(f->getCell(Coords{i, j}).getWolfIndexesSize()) {
                    imagePainter.setPen(Qt::red);
                    imagePainter.drawPoint(i, j);
                }else if(f->getCell(Coords{i, j}).getRabbitIndexesSize()) {
                    imagePainter.setPen(Qt::blue);
                    imagePainter.drawPoint(i, j);
                }else if(f->wasWolfHere(Coords{i, j})) {
                    unsigned red = std::min(255u, f->getCell({i, j}).getTotalSmell());
                    imagePainter.setPen(QColor::fromHsv(0, red / 20.0 * 255, 100 + 5 * red));
                    imagePainter.drawPoint(i, j);
                }else if(f->wasRabbitHere(Coords{i, j})) {
                    unsigned blue = std::min(255u, f->getCell({i, j}).getTotalSmell());
                    imagePainter.setPen(QColor::fromHsv(240, blue / 20.0 * 255, 100 + 5 * blue));
                    imagePainter.drawPoint(i, j);
                }else if(f->getCell(Coords{i, j}).isThereGrass()) {
                    imagePainter.setPen(QColor::fromHsv(120, 255, f->getCell(Coords{i, j}).grass / 150.0 * 255));
                    imagePainter.drawPoint(i, j);
                }else{
                    imagePainter.setPen(Qt::white);
                    imagePainter.drawPoint(i, j);
                }
            }
        }
        QPainter painter(this);
        painter.drawImage(0,0, im.scaled(this->width(), this->height()));
        if(write_im) {
            write_im = false;
            im.scaled(1920, 1080).save("image.png");
        }
    }
    e->accept();
}

MainWindow::~MainWindow() {
    f->stop();
    while (!f->stopped.load(std::memory_order_relaxed));
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_W) {
        if(e->modifiers() & Qt::ControlModifier) {
            f->populateWolfs();
        }else{
            f->write();
        }
    }
    if(e->key() == Qt::Key_I) {
        write_im = true;
    }
    if(e->key() == Qt::Key_R && e->modifiers() & Qt::ControlModifier) {
        f->populateRabbits();
    }
}

void MainWindow::on_actionRun_triggered() {
    if(!run) {
        run = true;
        QThreadPool::globalInstance()->start(f);    
    }
}
