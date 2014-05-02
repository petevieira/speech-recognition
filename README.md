Speech-Recognition
==================

Installation
============
From http://cmusphinx.sourceforge.net/wiki/download/ install the following packages using tar -xvf to uncompress them.
 
 - Sphinxbase - support library required by Pocketsphinx and Sphinxtrain
 - Sphinxtrain - acoustic model training tools
 - Pocketsphinx - recognizer library written in C
 - CMUclmtk - language model tools

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
