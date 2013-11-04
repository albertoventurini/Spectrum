#include "jackclient.h"
#include <QDebug>



JackClient::JackClient(QString name)
{
    // Convert name from QString to char*
    client_name = name.toLocal8Bit().data();

    // Create a new jack client
    client = jack_client_open(client_name, JackNullOption, NULL);
    if(client == NULL)
    {
        throw 1;
    }

    // Get jack's buffer size
    buffer_size = (int)jack_get_buffer_size(client);

    // Set up jack callback
    jack_set_process_callback(client, static_process, this);

    // Set up shutdown callback
    jack_on_shutdown(client, static_shutdown, this);

    // Register input port
    port = jack_port_register(client, "spectrum", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    if (port == NULL)
    {
       // printf("Cannot register input port\n");
        jack_client_close(client);
        throw 1;
    }

    if (jack_activate (client))
    {
        throw 1;
    }
}


JackClient::~JackClient()
{
    // Close jack client
    jack_client_close(client);
}


// Static callback function. In "arg" we have a pointer to the class instance.
// So we'll just dispatch the call to the class instance callback.
int JackClient::static_process(jack_nframes_t nframes, void *arg)
{
    JackClient *c = (JackClient *)arg;
    return c->process(nframes);
}


// Class instance callback
int JackClient::process(jack_nframes_t nframes)
{
    // Here we just collect the incoming samples. No further processing at this stage

    incoming = (jack_default_audio_sample_t *)jack_port_get_buffer(port, nframes);
    return 0;
}


// Shutdown callback
void JackClient::static_shutdown(void *arg)
{
    JackClient *c = (JackClient *)arg;
    return c->shutdown();
}


// Shutdown callback
void JackClient::shutdown()
{
}
