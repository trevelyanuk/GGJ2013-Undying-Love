#pragma once
#include "Object.h"
#include "Game.h"


class CLove
	:public CObject
{


public:
	CLove(float x_, float y_, float rot_);
	virtual ~CLove();
	void Update(DWORD _timeFrame);
	void Render();
	float yvel;
	float xvel;
	float m_fRotation;

};

