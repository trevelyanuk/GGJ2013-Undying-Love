#pragma once
#include "Object.h"
#include "Game.h"
#include "Input.h"


class CBase
	:public CObject
{


public:
	CBase(float x_, float y_,unsigned width_,unsigned height_, unsigned short textureID_, GLubyte r_, GLubyte g_, GLubyte b_,GLubyte a_,
		float xsca_, float ysca_,	float spd_, float rad_, float ang0_, bool fadeable_);

	virtual ~CBase();
	void Update(DWORD dt_);


};

