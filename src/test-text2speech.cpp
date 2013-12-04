#include <stdio.h>
#include <iostream>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char* speech2textWebsite = "/usr/bin/mplayer -ao alsa -really-quiet -noconsolecontrols \"http://translate.google.com/translate_tts?tl=en&q=";
    char* endQuote = "\"";
    char* inputText = "Yo Amber. What's happenin'";
    char cmd[500];
    sprintf(cmd, "%s%s%s", speech2textWebsite, inputText, endQuote);
    system(cmd);
    return 0;
}
