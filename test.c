#include <stdio.h>
#define YAMIDI_IMPLEMENTATION
#include "yamidi.h"

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
    printf("msg.status = %x\n",msg.status);

    return 0;
}
