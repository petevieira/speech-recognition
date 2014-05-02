Speech-Recognition
==================

Installation
============
From http://cmusphinx.sourceforge.net/wiki/download/ install the following packages using tar -xvf to uncompress them.
 
 - Sphinxbase 0.8 - support library required by Pocketsphinx and Sphinxtrain
 - Sphinxtrain 1.0.8 - acoustic model training tools
 - Pocketsphinx 0.8 - recognizer library written in C
 - CMUclmtk 0.7 - language model tools

Then, in each package run
 
    autoreconf -i
    ./configure
    make
    sudo make install

Compilation
===========

    mkdir build
    cd build
    cmake ..
    make
    ./hello-world_sphinx
    
Testing
=======
Run pocketsphinx_continuous to test the installation. When it says "Ready..." say something and wait for the translation.

    pocketsphinx_continuous

Miscellaneous
=============
List audio devices

    pacmd list-source


Project Layout
==============
Processes

  - speech_recogntion
  - speech_generation

Messages

  - recognized speech
  - speech to generate
  - command from speech recognition
  
