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
#include "qttypes.h"
#include "soundengine.h"

class AudioThread : public QThread {
 public:
    explicit AudioThread(QObject *parent = 0);
    void run();
 private:
    SoundEngine engine;
 PUBLIC_SLOTS:
    void setFrequency(int frequency);
};
#endif  // INCLUDE_APP_AUDIOTHREAD_H_
