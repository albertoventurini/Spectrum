This is a simple Qt application that shows the frequency spectrum of a JACK audio stream.

It uses the following libraries:

Qt, for a minimal interface
OpenGL, to display the power spectrum
FFTW (libfftw3-dev), to calculate the FFT of the audio stream;
the JACK sound server, to get an audio stream.
Compile with "qmake && make".

