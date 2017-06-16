#pragma once
#include "Object.h"
#include "Game.h"
#include "Input.h"


class CPlayer
	:public CObject
{


public:
	CPlayer(float x_, float y_,unsigned width_,unsigned height_, unsigned short textureID_, GLubyte r_, GLubyte g_, GLubyte b_,GLubyte a_,
		float xsca_, float ysca_,	float spd_, float rad_, float ang0_, bool fadeable_);

	virtual ~CPlayer();
	void Update(DWORD dt_);
	void Render();
	float m_ucHealth;
	void collided(CObject *obj_);

	TImagePtr m_pSpriteGun;

	unsigned char m_ucDelayBullet;
	unsigned char m_ucDelayLove;

	int angdif (int tar_ , int cur_);
	int sign ( int int_ );
};

