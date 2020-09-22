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
#include "audiothread.h"
#include <QDebug>
#include <QCoreApplication>
#ifndef __WINDOWS_DS__
#include <unistd.h>
#endif
#include <stdlib.h>

pd::PdBase lpd;
static int audioCallback(void *outputBuffer, void *inputBuffer,
                  unsigned int nBufferFrames, double streamTime,
                  RtAudioStreamStatus status, void *userData);

AudioThread::AudioThread(QObject *parent) {
}

void AudioThread::run() {
    AudioThread::init();
    // keep the program alive until it's killed with Ctrl+C
    while (!isThreadstopped) {
       lpd.receiveMessages();
       lpd.sendFloat("FromCpp", 578);
       QThread::msleep(100);
    }
}

void AudioThread::init() {
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 128;

    // init pd
    if (!lpd.init(0, 2, sampleRate)) {
       std::cerr << "Could not init pd" << std::endl;
       isThreadstopped = true;
       return;
    }

    // receive messages from pd
    lpd.setReceiver(&pdObject);
    lpd.subscribe("cursor");

    // send DSP 1 message to pd
    lpd.computeAudio(true);

    // load the patch
    pd::Patch patch = lpd.openPatch("brln.pd",
        QCoreApplication::applicationDirPath().toStdString() + "/pd");
    std::cout << patch << std::endl;

    // use the RtAudio API to connect to the default audio device
    if (audio.getDeviceCount() == 0) {
       std::cout << "There are no available sound devices." << std::endl;
       isThreadstopped = true;
       return;
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = audio.getDefaultOutputDevice();
    parameters.nChannels = 2;

    RtAudio::StreamOptions options;
    options.streamName = "libpd rtaudio test";
    options.flags = RTAUDIO_SCHEDULE_REALTIME;
    if (audio.getCurrentApi() != RtAudio::MACOSX_CORE) {
        // CoreAudio doesn't seem to like this
        options.flags |= RTAUDIO_MINIMIZE_LATENCY;
    }
    try {
       audio.openStream(&parameters, NULL, RTAUDIO_FLOAT32,
                        sampleRate, &bufferFrames, &audioCallback,
                        NULL, &options);
       audio.startStream();
    }
    catch(RtAudioError& e) {
       std::cerr << e.getMessage() << std::endl;
       isThreadstopped = true;
       return;
    }
}

int audioCallback(void *outputBuffer, void *inputBuffer,
                  unsigned int nBufferFrames, double streamTime,
                  RtAudioStreamStatus status, void *userData) {
    // pass audio samples to/from libpd
    int ticks = nBufferFrames / 64;
    lpd.processFloat(ticks,
                     reinterpret_cast<float *>(inputBuffer),
                     reinterpret_cast<float *>(outputBuffer));
    return 0;
}
