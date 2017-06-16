#pragma once
#include "Object.h"
#include "Game.h"
#include "Input.h"

class CHuman
	:public CObject
{
public:
	enum eSurvivorState
	{
		survivorIdle,
		survivorAttack,
		survivorReturn
	};

public:
	CHuman(float x_, float y_,unsigned width_,unsigned height_, unsigned short textureID_, GLubyte r_, GLubyte g_, GLubyte b_,GLubyte a_,
		float xsca_, float ysca_,	float spd_, float rad_, float ang0_, bool fadeable_);

	virtual ~CHuman();
	void Update(DWORD dt_);
	eSurvivorState m_eSurvivorState;
	float normalisedX;
	float normalisedY;
	float delay;
	float shot;
	float maxShots;
};

