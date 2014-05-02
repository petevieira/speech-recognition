#include "ears.h"
#include <iostream>

int main(int argc, char **argv)
{
    Ears ears;

    //this is the location of the file we will be comparing against our langauge model
    std::string fileLoc = "../resources/goforward.raw";

    //holds the decoded string
    std::string outputString;

    if(ears.Init()>0)
    {
        std::cerr << "error on init" << std::endl;
        return 1;
    }

    //process the .raw file and store the string
    outputString = ears.RawToString(fileLoc.c_str());


    //print to terminal
    std::cout << "Got: " << outputString << std::endl;

    return 0;
}
