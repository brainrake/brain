brain
=====

brain is a vj tool


dependencies:

- OpenGL
- ffmpeg
- pthreads
- SFML - for windowing and input


build system:

- scons


building
--------

on debian-based systems (tested on ubuntu 10.10)::

    sudo apt-get install scons libgl1-mesa-dev libglu1-mesa-dev libsfml-dev libavcodec-dev libavformat-dev libswscale-dev
    scons


running
-------

::

    ./brain
