/*
  Q Light Controller Plus
  audiocapture_portaudio.cpp

  Copyright (c) Massimo Callegari

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include <QSettings>
#include <QDebug>

#ifdef PA_JACK
#include <pa_jack.h>
#endif

#include "audiocapture_portaudio.h"

PaStream *AudioCapturePortAudio::Stream=NULL;

AudioCapturePortAudio::AudioCapturePortAudio(QObject * parent)
    : AudioCapture(parent)
{
#ifdef PA_JACK
    PaJack_SetClientName("QLCPlusCapture");
#endif
}

AudioCapturePortAudio::~AudioCapturePortAudio()
{
    stop();
    Q_ASSERT(AudioCapturePortAudio::Stream == NULL);
}

bool AudioCapturePortAudio::initialize()
{
    PaError err;
    PaStreamParameters inputParameters;
    
    memset( &inputParameters, 0 ,sizeof( inputParameters ) );
    
    Volume=1.0;
    
    err = Pa_Initialize();
    if( err != paNoError )
        return false;

    QSettings settings;
    QVariant var = settings.value(SETTINGS_AUDIO_INPUT_DEVICE);
    if (var.isValid() == true)
        inputParameters.device = QString(var.toString()).toInt();
    else
        inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */

    if (inputParameters.device == paNoDevice)
    {
        qWarning("Error: No default input device found.\n");
        Pa_Terminate();
        return false;
    }

    inputParameters.channelCount = m_channels;
    inputParameters.sampleFormat = paInt16;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;

    // ensure initialize() has not been called multiple times
    Q_ASSERT(AudioCapturePortAudio::Stream == NULL);

    /* -- setup stream -- */
    err = Pa_OpenStream( &AudioCapturePortAudio::Stream, &inputParameters, NULL, m_sampleRate, paFramesPerBufferUnspecified,
              paClipOff, /* we won't output out of range samples so don't bother clipping them */
              paNoFlag , /* no callback, use blocking API */
              NULL ); /* no callback, so no callback userData */
    if( err != paNoError )
    {
        qWarning("Cannot open audio input stream (%s)\n",  Pa_GetErrorText(err));
        Pa_Terminate();
        return false;
    }

    /* -- start capture -- */
    err = Pa_StartStream( AudioCapturePortAudio::Stream );
    if( err != paNoError )
    {
        qWarning("Cannot start stream capture (%s)\n",  Pa_GetErrorText(err));
        Pa_CloseStream( AudioCapturePortAudio::Stream );
        AudioCapturePortAudio::Stream = NULL;
        Pa_Terminate();
        return false;
    }

    return true;
}

void AudioCapturePortAudio::uninitialize()
{
    Q_ASSERT(AudioCapturePortAudio::Stream != NULL);

    PaError err;

    /* -- Now we stop the stream -- */
    err = Pa_StopStream( AudioCapturePortAudio::Stream );
    if( err != paNoError )
        qDebug() << "PortAudio error: " << Pa_GetErrorText( err );

    /* -- don't forget to cleanup! -- */
    err = Pa_CloseStream( AudioCapturePortAudio::Stream );
    if( err != paNoError )
        qDebug() << "PortAudio error: " << Pa_GetErrorText( err );
    AudioCapturePortAudio::Stream = NULL;

    err = Pa_Terminate();
    if( err != paNoError )
        qDebug() << "PortAudio error: " << Pa_GetErrorText( err );
}

qint64 AudioCapturePortAudio::latency()
{
    return Pa_GetStreamTime(AudioCapturePortAudio::Stream);
}

void AudioCapturePortAudio::setVolume(qreal volume){
    Volume=volume;
}

void AudioCapturePortAudio::suspend()
{
}

void AudioCapturePortAudio::resume()
{
}

bool AudioCapturePortAudio::readAudio(int maxSize)
{
    Q_ASSERT(AudioCapturePortAudio::Stream != NULL);

    int err = Pa_ReadStream( AudioCapturePortAudio::Stream, m_audioBuffer, maxSize );
    if( err )
    {
        qWarning("read from audio interface failed (%s)\n", Pa_GetErrorText (err));
        return false;
    }
    
    qDebug() << "[PORTAUDIO readAudio] " << maxSize << "bytes read";

//     *m_audioBuffer=(short)(*m_audioBuffer*Volume);
    return true;
}
