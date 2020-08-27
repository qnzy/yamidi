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
    return 0;
}
