#pragma once
#include "Object.h"
#include "Game.h"
#include <math.h>
using namespace std;


class CParticle
	:public CObject
{

public:
CParticle(float x_, float y_ , int width_, const string& spr_ , int framecount_, uc ind_ , 
					 uc r_ , uc g_ , uc b_ , uc a_ , float zrot_ ,
				     char xo_ , char yo_ , float scastart_ , float scaend_ ,
			         char spdfade_ , char spdrot_ );
	virtual ~CParticle();
	void Update(DWORD _timeFrame);
	void Render();

	

	//PT vars nomnom blahlblshlhllhdlhl-snyk
	float m_fYVel;
	float m_fXVel;
	float m_fRotation;

	unsigned char m_ucFramesTotal;
	unsigned char m_ucIndex;
	float m_fUScaStart;
	float m_fUScaEnd;
	char m_cXOff;
	char m_cYOff;
	char m_cSpdFade;
	char m_cSpdRot;
	int m_iWidth;
	//gravity & gravity_direction

};



