#pragma once
#include "Object.h"
#include "Game.h"


class CBullet
	:public CObject
{


public:
	CBullet(float x_, float y_, float rot_);
	virtual ~CBullet();
	void Update(DWORD _timeFrame);
	void Render();
	float yvel;
	float xvel;
	
};

