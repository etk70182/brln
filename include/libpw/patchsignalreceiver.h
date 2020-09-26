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

#include <string>
#include <map>
#include "PdBase.hpp"

// custom receiver class
class PatchSignalReceiver : public pd::PdReceiver, public pd::PdMidiReceiver {
 public:
    // pd message receiver callbacks
    void print(const std::string& message);
    void receiveBang(const std::string& dest);
    void receiveFloat(const std::string& dest, float num);
    void receiveSymbol(const std::string& dest, const std::string& symbol);
    void receiveList(const std::string& dest, const pd::List& list);
    void receiveMessage(const std::string& dest, const std::string& msg,
                        const pd::List& list);
    // pd midi receiver callbacks
    void receiveNoteOn(const int channel, const int pitch, const int velocity);
    void receiveControlChange(const int channel,
                              const int controller, const int value);
    void receiveProgramChange(const int channel, const int value);
    void receivePitchBend(const int channel, const int value);
    void receiveAftertouch(const int channel, const int value);
    void receivePolyAftertouch(const int channel,
                               const int pitch, const int value);
    void receiveMidiByte(const int port, const int byte);
    float get(std::string const& key);
 private:
    std::map<std::string, float> values;
};

