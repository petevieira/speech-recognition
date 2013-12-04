Speech-Recognition
==================

Compilation
===========

 `gcc -o hello_ps hello-world_sphinx.c -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" `pkg-config --cflags --libs pocketsphinx sphinxbase``

