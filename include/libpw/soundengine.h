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
#pragma once
#include <memory>
#include <string>
#include "RtAudio.h"
#include "patchsignalreceiver.h"

enum EngineStatus { ready, uninitialized, patchInvalid, noSoundDevices,
                  thrownError };

class SoundEngine {
 public:
    static SoundEngine& instance();
    SoundEngine();
    ~SoundEngine();
    void update();
    void set(std::string const & key, int const & value);
    float get(std::string const & key);
    EngineStatus init(std::string const& patchDirectory);
 private:
    RtAudio audio;
    PatchSignalReceiver patchSignalReceiver;
};
