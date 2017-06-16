#include "stdafx.h"
#include "Audio.h"


#include <stdio.h>




CAudio::CAudio(void)
{
	initialize();
	dVolume01 = 1;
}

CAudio::~CAudio(void)
{
	shutDown();
}
				     

CAudio *CAudio::s_pgetInst()
{
	if (0==_pAudioinst){
		_pAudioinst=new CAudio();
	}
	return _pAudioinst;
}
CAudio *CAudio::_pAudioinst=0;
/*
CAudio* 
CAudio::Instance()
{
	if (instance==NULL)
	{
		instance=new CAudio();
	}
	return instance;
}*/

//initialize singleton static variable on startup
//CAudio * CAudio::instance=0;


void
CAudio::setListenerLookAt(ALfloat x_,ALfloat y_, ALfloat z_)
{
	// Position of the listener.
	ALfloat ListenerOri[6];
	ListenerOri[0]=x_;
	ListenerOri[1]=y_;
	ListenerOri[2]=z_;
	ListenerOri[3]=0.0f;
	ListenerOri[4]=1.0f;
	ListenerOri[5]=0.0f;

	alListenerfv(AL_ORIENTATION, ListenerOri);
}

void 
CAudio::setListenerPosition(ALfloat x_,ALfloat y_, ALfloat z_)
{
	// Position of the listener.
	ALfloat ListenerPos[3];
	ListenerPos[0]=x_;
	ListenerPos[1]=y_;
	ListenerPos[2]=z_;


	// Velocity of the listener.
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

	// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
	ALfloat ListenerOri[] = { 0,-1,0,0,0,-1};
	//ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

	alListenerfv(AL_POSITION,    ListenerPos);
    alListenerfv(AL_VELOCITY,    ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
	
	
	alListenerf ( AL_GAIN,     70.0f     );
}

//method returns an integer which represents
//the sound and buffer which is used to play the sound
//to control the sound, you  need to use this value
//with the setVolume() and stop() methods
int 
CAudio::playSound(char * filename_,double x, double y, double z, bool brepeat_, bool relativeToListener_)
{

	int sourceNumber;

	sourceNumber=this->getNextFreeBuffer();
	if (sourceNumber==-1)
		{
		sourceNumber=freeUpABuffer();
		}


	// Position of the source sound.
	ALfloat SourcePos[] = { x, y, z };

	// Velocity of the source sound.
	ALfloat SourceVel[] = { 0, 0, 0 };

	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	// Load wav data into a buffer.

	alGenBuffers(1, &buffer[sourceNumber]);

	if(alGetError() != AL_NO_ERROR)
	{
		return -1;
	}

	alutLoadWAVFile(filename_, &format, &data, &size, &freq, &loop);
	alBufferData(buffer[sourceNumber], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);


	// Bind buffer with a source.
    alGenSources(1, &source[sourceNumber]);

    if (alGetError() != AL_NO_ERROR)
	{
	return -1;
	}
        

    alSourcei (source[sourceNumber], AL_BUFFER,   buffer[sourceNumber]  );
    alSourcef (source[sourceNumber], AL_PITCH,    1.0f     );
    alSourcef (source[sourceNumber], AL_GAIN,     dVolume01     );//Snky 1.0f
    alSourcefv(source[sourceNumber], AL_POSITION, SourcePos);
    alSourcefv(source[sourceNumber], AL_VELOCITY, SourceVel);
    alSourcei (source[sourceNumber], AL_LOOPING,  brepeat_     );
	alSourcei(source[sourceNumber],  AL_ROLLOFF_FACTOR, 2);
	alSourcei(source[sourceNumber], AL_SOURCE_RELATIVE ,relativeToListener_);
	alSourcePlay(source[sourceNumber]);

	bBufferInUse[sourceNumber]=true;
	
	return sourceNumber;
}

void
CAudio::setVolume(int sourceNumber_,double value_)
{
double value;
if (value_<=0.0)
{
	value=0.0;
}
else value=value_;

alSourcef (source[sourceNumber_], AL_GAIN,value);
  
}

bool
CAudio::initialize()
{

	m_pDevice = alcOpenDevice(NULL);
	if (m_pDevice == NULL)
	{
		return 0;
	}

	//Create context(s)
	m_pContext=alcCreateContext(m_pDevice,NULL);

	//Set active context
	alcMakeContextCurrent(m_pContext);

	//alutInit(NULL, 0);
	alGetError();

	for (unsigned char i = 0; i < 10; ++i)
	{
	bBufferInUse[i]=0;
	}
	return true;
}


int
CAudio::getNextFreeBuffer()
{
	for (unsigned char i = 0; i < 10; ++i)
	{
	if (bBufferInUse[i]==0)
		{
		return i;
		}
	}
	return -1;
}

//function used to identify a buffer that has finished
//and delete it for reuse
int 
CAudio::freeUpABuffer()
{
	for (unsigned char i = 0; i < 10; ++i)
	{
		ALint value;
		alGetSourcei(source[i],AL_SOURCE_STATE,&value);
		if (value==AL_STOPPED)
			{
			alDeleteSources(1, &source[i]);
			alDeleteBuffers(1, &buffer[i]);
			bBufferInUse[i]=0;
			return i;
			}
	}
	return -1;
}

void
CAudio::shutDown()
{
	alDeleteSources(NUM_SOURCES, source);
	alDeleteBuffers(NUM_BUFFERS, buffer);

	//Get active context
	m_pContext=alcGetCurrentContext();

	//Get device for active context
	m_pDevice=alcGetContextsDevice(m_pContext);

	//Disable context
	alcMakeContextCurrent(NULL);

	//Release context(s)
	alcDestroyContext(m_pContext);

	//Close device
	alcCloseDevice(m_pDevice);
}

void
CAudio::stop(int sourceNumber_)
{
alSourceStop(source[sourceNumber_]);
}