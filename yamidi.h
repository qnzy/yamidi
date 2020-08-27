/** 
 * yamidi: yet another midi library
 * cc0 / public domain
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#define midiParseInitState 0

enum midiStatus {
    midiStatusNoteOff = 0x80,
    midiStatusNoteOn = 0x90,
    midiStatusPolyAT = 0xa0,
    midiStatusCC = 0xb0,
    midiStatusProgramChange = 0xc0,
    midiStatusChannelAT = 0xd0,
    midiStatusPitchBend = 0xe0
};

struct midiParamNoteOn_s        { uint8_t chan; uint8_t key; uint8_t vel;  };
struct midiParamNoteOff_s       { uint8_t chan; uint8_t key; uint8_t vel;  };
struct midiParamPolyAT_s        { uint8_t chan; uint8_t key; uint8_t vel;  };
struct midiParamCC_s            { uint8_t chan; uint8_t ctrl; uint8_t val; };
struct midiParamProgramChange_s { uint8_t chan; uint8_t prog;              };
struct midiParamChannelAT_s     { uint8_t chan; uint8_t vel;               };
struct midiParamPitchBend_s     { uint8_t chan; uint16_t val;              };

struct midiMsg_s {
    int status;
    union {
        struct midiParamNoteOn_s midiParamNoteOn;
        struct midiParamNoteOff_s midiParamNoteOff;
        struct midiParamPolyAT_s midiParamPolyAT;
        struct midiParamCC_s midiParamCC;
        struct midiParamProgramChange_s midiParamProgramChange;
        struct midiParamChannelAT_s midiParamChannelAT;
        struct midiParamPitchBend_s midiParamPitchBend;
    } params;
};

struct midiBytes_s {
    uint8_t len;
    uint8_t data[3];
};

struct midiBytes_s genMidiMessage(struct midiMsg_s msg);
bool parseMidiByte(uint8_t b, struct midiMsg_s *msg, int* state);


#ifdef YAMIDI_IMPLEMENTATION
struct midiBytes_s genMidiMessage(struct midiMsg_s msg) {
    struct midiBytes_s ret={0};
    switch (msg.status) {
        case midiStatusNoteOff: 
            ret.len=3;
            ret.data[0] = (unsigned)midiStatusNoteOff | (msg.params.midiParamNoteOff.chan & 0x0fu);
            ret.data[1] = msg.params.midiParamNoteOff.key;
            ret.data[2] = msg.params.midiParamNoteOff.vel;
            break;
        case midiStatusNoteOn:
            ret.len=3;
            ret.data[0] = (unsigned)midiStatusNoteOn | (msg.params.midiParamNoteOn.chan & 0x0fu);
            ret.data[1] = msg.params.midiParamNoteOn.key;
            ret.data[2] = msg.params.midiParamNoteOn.vel;
            break;
        case midiStatusPolyAT:
            ret.len=3;
            ret.data[0] = (unsigned)midiStatusPolyAT | (msg.params.midiParamPolyAT.chan & 0x0fu);
            ret.data[1] = msg.params.midiParamPolyAT.key;
            ret.data[2] = msg.params.midiParamPolyAT.vel;
            break;
        case midiStatusCC:
            ret.len=3;
            ret.data[0] = (unsigned)midiStatusCC | (msg.params.midiParamCC.chan & 0x0fu);
            ret.data[1] = msg.params.midiParamCC.ctrl;
            ret.data[2] = msg.params.midiParamCC.val;
            break;
        case midiStatusProgramChange:
            ret.len=2;
            ret.data[0] = (unsigned)midiStatusProgramChange | (msg.params.midiParamProgramChange.chan & 0x0fu);
            ret.data[1] = msg.params.midiParamProgramChange.prog;
            break;
        case midiStatusChannelAT:
            ret.len=2;
            ret.data[0] = (unsigned)midiStatusChannelAT | (msg.params.midiParamChannelAT.chan & 0x0fu);
            ret.data[1] = msg.params.midiParamChannelAT.vel;
            break;
        case midiStatusPitchBend:
            ret.len=3;
            ret.data[0] = (unsigned)midiStatusPitchBend | (msg.params.midiParamPitchBend.chan & 0x0fu);
            ret.data[1] = msg.params.midiParamPitchBend.val & 0x7fu;
            ret.data[2] = msg.params.midiParamPitchBend.val >> 7u;
            break;
        default:
            ret.len = 0;
    }
    ret.data[1] &= 0x0f;
    ret.data[2] &= 0x0f;
    return ret;
}

bool parseMidiByte(uint8_t b __attribute__((unused)), struct midiMsg_s *msg __attribute__((unused)), int *state __attribute__((unused))) {
    return false;
}
#endif // #ifdef YAMIDI_IMPLEMENTATION
