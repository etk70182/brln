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

#include <QApplication>
#include <QFile>
#include <QCommandLineParser>
#include <iostream>
#include "mainwindow.h"
#include "version.h"

void setProgrammOptions(QApplication* app);
QString loadStyle();

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    setProgrammOptions(&app);
    QString style = loadStyle();
    app.setStyleSheet(style);
    MainWindow window;
    window.show();
    return app.exec();
}

void setProgrammOptions(QApplication* app) {
    app->setApplicationName(APP_NAME);
    app->setApplicationDisplayName(APP_NAME);
    app->setApplicationVersion(APP_VERSION);
    QString applicationDescription =
            APP_NAME" is a free software synthesizer\n"
            "under the GPLv3.";
    QCommandLineParser parser;
    parser.setApplicationDescription(applicationDescription);
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(*app);
}

QString loadStyle() {
    QFile styleFile(":/styles/brln.qss");
    styleFile.open(QFile::ReadOnly);
    return styleFile.readAll();
}
