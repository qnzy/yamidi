#include <stdio.h>
#define YAMIDI_IMPLEMENTATION
#include "yamidi.h"

void printMsg(struct midiMsg_s msg) {
    switch(msg.status) {
        case midiStatusNoteOff:
            printf("Note Off, chan=%d, key=%d, vel=%d\n", 
                    msg.params.midiParamNoteOff.chan,
                    msg.params.midiParamNoteOff.key,
                    msg.params.midiParamNoteOff.vel);
            break;
        case midiStatusNoteOn:
            printf("Note On, chan=%d, key=%d, vel=%d\n", 
                    msg.params.midiParamNoteOn.chan,
                    msg.params.midiParamNoteOn.key,
                    msg.params.midiParamNoteOn.vel);
            break;
        case midiStatusPolyAT:
            printf("PolyAT, chan=%d, key=%d, vel=%d\n", 
                    msg.params.midiParamPolyAT.chan,
                    msg.params.midiParamPolyAT.key,
                    msg.params.midiParamPolyAT.vel);
            break;
        case midiStatusCC:
            printf("CC, chan=%d, ctrl=%d, vll=%d\n", 
                    msg.params.midiParamCC.chan,
                    msg.params.midiParamCC.ctrl,
                    msg.params.midiParamCC.val);
            break;
        case midiStatusProgramChange:
            printf("ProgramChange, chan=%d, prog=%d\n", 
                    msg.params.midiParamProgramChange.chan,
                    msg.params.midiParamProgramChange.prog);
            break;
        case midiStatusChannelAT:
            printf("ChannelAT, chan=%d, vel=%d\n", 
                    msg.params.midiParamChannelAT.chan,
                    msg.params.midiParamChannelAT.vel);
            break;
        case midiStatusPitchBend:
            printf("Pitch Bend, chan=%d, val=%d\n", 
                    msg.params.midiParamPitchBend.chan,
                    msg.params.midiParamPitchBend.val);
            break;
        default:
            printf("unknown midi msg\n");
    }
}

int main() {
    struct midiBytes_s raw;
    raw = genMidiMessage(
            (struct midiMsg_s) {
            .status = midiStatusNoteOn, 
            .params.midiParamNoteOn = {.chan=5, .key=10, .vel=60}});

    for (int i=0; i<raw.len; i++) {
        printf ("%02x ",raw.data[i]);
    }
    printf("\n");

   int state = 0;
   struct midiMsg_s msg;
    if (parseMidiByte(0x85, &msg, &state)) {printf("error on line %d\n", __LINE__);}
    if (parseMidiByte(0x01, &msg, &state)) {printf("error on line %d\n", __LINE__);}
    if (!parseMidiByte(0x02, &msg, &state)) {printf("error on line %d\n", __LINE__);}
    printMsg(msg);

    return 0;
}
