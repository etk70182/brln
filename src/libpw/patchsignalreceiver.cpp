/*
 * Copyright (c) 2012 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/libpd/libpd for documentation
 *
 * This file was adapted from the ofxPd openFrameworks addon example:
 * https://github.com/danomatika/ofxPd
 *
 */
#include "patchsignalreceiver.h"
#include <iostream>

using std::cout;
using std::endl;
using pd::List;

//--------------------------------------------------------------
void PatchSignalReceiver::print(const std::string& message) {
    cout << message << endl;
}

//--------------------------------------------------------------
void PatchSignalReceiver::receiveBang(const std::string& dest) {
    cout << "CPP: bang " << dest << endl;
}

void PatchSignalReceiver::receiveFloat(const std::string& dest, float num) {
    values[dest] = num;
}

void PatchSignalReceiver::receiveSymbol(const std::string& dest,
                                        const std::string& symbol) {
    cout << "CPP: symbol " << dest << ": " << symbol << endl;
}

void PatchSignalReceiver::receiveList(const std::string& dest,
                                      const List& list) {
    cout << "CPP: list " << dest << ": " << list << endl;
}

void PatchSignalReceiver::receiveMessage(const std::string& dest,
                                         const std::string& msg,
                                         const List& list) {
    cout << "CPP: message " << dest << ": " << msg
         << " " << list.toString() << list.types() << endl;
}

//--------------------------------------------------------------
void PatchSignalReceiver::receiveNoteOn(const int channel,
                                        const int pitch, const int velocity) {
    cout << "CPP MIDI: note on: " << channel << " "
         << pitch << " " << velocity << endl;
}

void PatchSignalReceiver::receiveControlChange(const int channel,
                                               const int controller,
                                               const int value) {
    cout << "CPP MIDI: control change: " << channel << " "
         << controller << " " << value << endl;
}

void PatchSignalReceiver::receiveProgramChange(const int channel,
                                               const int value) {
    cout << "CPP MIDI: program change: " << channel << " " << value << endl;
}

void PatchSignalReceiver::receivePitchBend(const int channel, const int value) {
    cout << "CPP MIDI: pitch bend: " << channel << " " << value << endl;
}

void PatchSignalReceiver::receiveAftertouch(const int channel,
                                            const int value) {
    cout << "CPP MIDI: aftertouch: " << channel << " " << value << endl;
}

void PatchSignalReceiver::receivePolyAftertouch(const int channel,
                                                const int pitch,
                                                const int value) {
    cout << "CPP MIDI: poly aftertouch: " << channel
         << " " << pitch << " " << value << endl;
}

void PatchSignalReceiver::receiveMidiByte(const int port, const int byte) {
    cout << "CPP MIDI: midi byte: " << port << " " << byte << endl;
}

float PatchSignalReceiver::get(std::string const& key) {
    return values[key];
}
