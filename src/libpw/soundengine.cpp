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
#include "soundengine.h"
#include <functional>
#include "PdBase.hpp"

pd::PdBase lpd;
static int audioCallback(void *outputBuffer, void *inputBuffer,
                  unsigned int nBufferFrames, double streamTime,
                  RtAudioStreamStatus status, void *userData);

SoundEngine& SoundEngine::instance() {
    static std::unique_ptr<SoundEngine> single( new SoundEngine() );
    return *single;
}

SoundEngine::SoundEngine() {
}

SoundEngine::~SoundEngine() {
}

void SoundEngine::update() {
    lpd.receiveMessages();
}

void SoundEngine::set(std::string const & key, int const & value) {
    lpd.sendFloat(key, value);
}

float SoundEngine::get(std::string const & key) {
    return patchSignalReceiver.get(key);
}

EngineStatus SoundEngine::init(std::string const & patchDirectory) {
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 256;

    // init pd
    if (!lpd.init(0, 2, sampleRate)) {
       std::cerr << "Could not init pd" << std::endl;
       return EngineStatus::uninitialized;
    }

    // receive messages from pd
    lpd.setReceiver(&patchSignalReceiver);
    lpd.subscribe("frequencyInput");

    // send DSP 1 message to pd
    lpd.computeAudio(true);

    // load the patch
    pd::Patch patch = lpd.openPatch("brln.pd", patchDirectory);
    if (!patch.isValid()) {
        return EngineStatus::patchInvalid;
    }

    // use the RtAudio API to connect to the default audio device
    if (audio.getDeviceCount() == 0) {
       return EngineStatus::noSoundDevices;
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = audio.getDefaultOutputDevice();
    parameters.nChannels = 2;

    RtAudio::StreamOptions options;
    options.streamName = "brln realtime stream";
    try {
       audio.openStream(&parameters, NULL, RTAUDIO_FLOAT32,
                        sampleRate, &bufferFrames, &audioCallback,
                        NULL, &options);
       audio.startStream();
    }
    catch(RtAudioError& e) {
       std::cerr << e.getMessage() << std::endl;
       if (audio.isStreamOpen()) audio.closeStream();
       return EngineStatus::thrownError;
    }
    return EngineStatus::ready;
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
