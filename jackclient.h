#ifndef JACKCLIENT_H
#define JACKCLIENT_H

#include <QString>
#include <jack/jack.h>


class JackClient
{
public:
    JackClient(QString name);  // Create a new Jack client with the given name
    ~JackClient();

    jack_default_audio_sample_t *incoming; // array for incoming samples
    int buffer_size;

private:
    char *client_name;
    jack_client_t *client;
    jack_port_t *port;

    // dummy static callback function. We need this because jack will only accept it.
    static int static_process(jack_nframes_t nframes, void *arg);

    // The "real" process callback function. See here: http://linux-audio.4202.n7.nabble.com/jack-and-c-td70485.html
    int process(jack_nframes_t nframes);

    // Same as "process", we declare a static and a non-static version of the shutdown callback
    static void static_shutdown(void *arg);
    void shutdown();



};

#endif // JACKCLIENT_H
