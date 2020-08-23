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
#ifndef INCLUDE_APP_AUDIOTHREAD_H_
#define INCLUDE_APP_AUDIOTHREAD_H_
#include <QThread>

class AudioThread : public QThread {
 public:
    // constructor
    // set name using initializer
    explicit AudioThread(QObject *parent = 0);

    // overriding the QThread's run() method
    void run();
};
#endif  // INCLUDE_APP_AUDIOTHREAD_H_
