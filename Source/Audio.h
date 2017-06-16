#pragma once
//#include "al.h"
#include "alut.h"

#define NUM_BUFFERS 10
#define NUM_SOURCES 10
#define NUM_ENVIRONMENTS 1

class CAudio
{
public:
	CAudio(void);
	~CAudio(void);
	static CAudio * s_pgetInst();
	static CAudio * _pAudioinst;
	bool version1();
	void setListenerPosition(ALfloat x,ALfloat y, ALfloat z);
	void setListenerLookAt(ALfloat x,ALfloat y,ALfloat z);
	int playSound(char * filename_,double x, double y, double z, bool brepeat_=false,bool relativeToListener_=false);
	void setVolume(int sourceNumber_,double value_);
	void stop(int sourceNumber_);
	bool initialize();
	void shutDown();
private:
	

	int getNextFreeBuffer();

	//listener properties
	double listenerPos[3];
	double listenerVel[3];
	double listenerOri[6];
	//source properties
	double source0Pos[3];
	double source0Vel[3];

	//similar to textures, sounds loaded in an array
	ALuint  buffer[NUM_BUFFERS];
	ALuint  source[NUM_SOURCES];
	ALuint  environment[NUM_ENVIRONMENTS];

	ALsizei size,freq;
	ALenum  format;
	ALvoid  *data;

	ALCcontext *m_pContext;
	ALCdevice *m_pDevice;

	bool bBufferInUse[10];
	
	int freeUpABuffer();
	double dVolume01;

};
