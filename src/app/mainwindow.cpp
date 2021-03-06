/**
 *  Copyright 2020 by André Schlinke <schlinke.andre@gmail.com>
 *
 *  This file is part of brln.
 *
 *  brln is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  brln is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with brln.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "mainwindow.h"
#include <QDial>
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("BRLN");
    setWindowIcon(QIcon(":images/brln.png"));
    QDial* frequencyDial = this->findChild<QDial *>("frequencyDial");
    frequencyDial->setMaximum(0);
    frequencyDial->setMaximum(127);
    audioThread = new AudioThread(this);
    QObject::connect(frequencyDial, &QDial::valueChanged,
                     audioThread, &AudioThread::setFrequency);
    audioThread->start();
}

MainWindow::~MainWindow() {
    delete ui;
}
