#pragma once
#include "Object.h"
#include "Game.h"
#include "Input.h"


class CZombie
	:public CObject
{
public:
	enum eZombieState
	{
		zombieIdle,
		zombieMove,
		zombieAttack,
		zombieFlee
	};
	eZombieState m_eZombieState;

public:
	CZombie(float x_, float y_,unsigned width_,unsigned height_, unsigned short textureID_, GLubyte r_, GLubyte g_, GLubyte b_,GLubyte a_,
		float xsca_, float ysca_,	float spd_, float rad_, float ang0_,bool fadeable_, int type_);

	int anim1;
	int timer1;
	void Render();
	virtual ~CZombie();
	void Update(DWORD dt_);
	void collided(CObject * obj_);
	unsigned char m_ucHits;
	unsigned char m_ucMaxHits;
	float velX, velY;
	float randomFleeX;
	float randomFleeY;
	float randomPatrolX;
	float randomPatrolY;
	float normalisedX;
	float normalisedY;
	float distanceToPatrol;
	float distanceToPlayer;
	int fleeTimer;
	int patrolTimer;
	int willAttack;

	float fleeSpeeed;
	float speeed;

};