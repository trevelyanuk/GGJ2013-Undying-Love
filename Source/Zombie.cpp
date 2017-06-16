#include "StdAfx.h"

#include "Zombie.h"
#include "Human.h"
#include "Player.h"
#include <math.h>
#include "Particle.h"
CZombie::CZombie(float x_, float y_,unsigned width_,unsigned height_, unsigned short textureID_, GLubyte r_, GLubyte g_, GLubyte b_,GLubyte a_,
		float xsca_, float ysca_,	float spd_, float rad_, float ang0_, bool fadeable_, int type_)
		:CObject(x_, y_,width_,height_, textureID_, r_, g_, b_, a_,	xsca_, ysca_, spd_, rad_, ang0_, fadeable_)
{
	
	m_eID = eZombie;
	m_ucHits = 0;
	m_ucMaxHits = 5;
	velX = 1;
	velY = 1;
	anim1 = 0;
	timer1 =0;
	m_eZombieState = zombieIdle;
	fleeTimer = 50;
	patrolTimer = 50;
	willAttack = 0;

	float randomFleeX = 0;
	float randomFleeY = 0;
	float randomPatrolX = 0;
	float randomPatrolY = 0;
	
	fleeSpeeed = 3;
	speeed = spd_;

	//MEOW -snky
	m_pSprite = CImage::CreateImage("images/s_zombie.png",TRectanglei(0,64,0,64));
}

CZombie::~CZombie(void)
{
}

void CZombie::Render()
{
		
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_usTextureID);	
		glColor4ub(m_ubR,m_ubG,m_ubB,m_ubA);
		
		
		glTranslatef(m_fX,m_fY,0);
		glScalef( 1, 1 , 0 );
		glRotatef( m_fAngle0 ,  0 , 0 , 1 );
		
		if (anim1 > 0)
		{
			int x = 9;
		}
		m_pSprite->SnkyBlit(-37,-37,anim1*74);

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
}

void CZombie::Update(DWORD _timeFrame)
{
	if (!timer1)
	{
		timer1 = 30;
		if ( anim1 < 1 ) ++anim1; else anim1 = 0;
	}
	else --timer1;

	switch (m_eZombieState)
	{
	case zombieIdle:
		{
			//this->m_fX++;
			float playerX = m_pGame->m_pCharacter->m_fX;
			float playerY = m_pGame->m_pCharacter->m_fY;
			float vectorPlayerX = playerX - m_fX;
			float vectorPlayerY = playerY - m_fY;
			distanceToPlayer = sqrt((vectorPlayerX * vectorPlayerX) + (vectorPlayerY * vectorPlayerY));
			normalisedX = vectorPlayerX / distanceToPlayer;
			normalisedY = vectorPlayerY / distanceToPlayer;

			m_fX += ( normalisedX * speeed ) * _timeFrame;
			m_fY += ( normalisedY * speeed ) * _timeFrame;
			//this->m_fX++;
			patrolTimer--;

			if (patrolTimer <= 0)
			{
				randomPatrolX = rand()%40 - 20;
				randomPatrolY = rand()%40 - 20;
				patrolTimer = 120;
			}

			float patrolX = m_fX + (randomPatrolX);
			float patrolY = m_fY + (randomPatrolY);
			float vectorPatrolX = patrolX - m_fX;
			float vectorPatrolY = patrolY - m_fY;
			distanceToPatrol = sqrt((vectorPatrolX * vectorPatrolX) + (vectorPatrolY * vectorPatrolY));
			
			if ( abs(distanceToPatrol) )
			{
				float dx , dy;
				dx = m_fX - patrolX;
				dy = m_fY - patrolY;
				float ang = -90 + DEG2RAD(atan2( dy , dx ));
				int idist = angdif(ang , m_fAngle0 );
				m_fAngle0 += min ( abs ( idist ) , 3 ) * sign ( idist );

				normalisedX = vectorPatrolX / distanceToPatrol;
				normalisedY = vectorPatrolY / distanceToPatrol;

				m_fX += ( normalisedX * speeed ) * _timeFrame;
				m_fY += ( normalisedY * speeed ) * _timeFrame;
			}

			if (distanceToPlayer < 150)
			{
				m_eZombieState = zombieMove;
			}
		}
		break;
	case zombieMove:
		{
			float dx , dy;
			dx = m_fX - m_pGame->m_pCharacter->m_fX;
			dy = m_fY - m_pGame->m_pCharacter->m_fY;
			float ang = -90 + DEG2RAD(atan2( dy , dx ));
			int idist = angdif(ang , m_fAngle0 );
			m_fAngle0 += min ( abs ( idist ) , 3 ) * sign ( idist );

			float playerX = m_pGame->m_pCharacter->m_fX;
			float playerY = m_pGame->m_pCharacter->m_fY;
			float vectorPlayerX = playerX - m_fX;
			float vectorPlayerY = playerY - m_fY;
			distanceToPlayer = sqrt((vectorPlayerX * vectorPlayerX) + (vectorPlayerY * vectorPlayerY));
			normalisedX = vectorPlayerX / distanceToPlayer;
			normalisedY = vectorPlayerY / distanceToPlayer;

			m_fX += ( normalisedX * speeed ) * _timeFrame;
			m_fY += ( normalisedY * speeed ) * _timeFrame;

			if (distanceToPlayer < 25)
			{
				willAttack = rand()%15 + 1;

				if (willAttack == 1)
				{
					m_eZombieState = zombieFlee;
				}
				else
				{
					m_eZombieState = zombieAttack;
				}
			}
		}
		break;
	case zombieAttack:
		{
			//this->m_fX++;
			//Code to interact with the health of the player
			float playerX = m_pGame->m_pCharacter->m_fX;
			float playerY = m_pGame->m_pCharacter->m_fY;
			float vectorPlayerX = playerX - m_fX;
			float vectorPlayerY = playerY - m_fY;
			distanceToPlayer = sqrt((vectorPlayerX * vectorPlayerX) + (vectorPlayerY * vectorPlayerY));
			normalisedX = vectorPlayerX / distanceToPlayer;
			normalisedY = vectorPlayerY / distanceToPlayer;

			m_fX += ( normalisedX * speeed ) * _timeFrame;
			m_fY += ( normalisedY * speeed ) * _timeFrame;

			if (distanceToPlayer > 25)
			{
				m_eZombieState = zombieMove;
			}
		}
		break;
	case zombieFlee:
		{
			fleeTimer--;

			float fleeX = m_fX + (randomFleeX);
			float fleeY = m_fY + (randomFleeY);
			float vectorFleeX = fleeX - m_fX;
			float vectorFleeY = fleeY - m_fY;
			float distanceToFlee = sqrt((vectorFleeX * vectorFleeX) + (vectorFleeY * vectorFleeY));
			normalisedX = vectorFleeX / distanceToFlee;
			normalisedY = vectorFleeY / distanceToFlee;

			m_fX += (normalisedX * fleeSpeeed) * _timeFrame;
			m_fY += (normalisedY * fleeSpeeed) * _timeFrame;

			if (fleeTimer <= 0)
			{
				randomFleeX = rand()%300 + 100;
				randomFleeY = rand()%300 + 100;
				fleeTimer = 50;

				m_eZombieState = zombieIdle;
			}
		}
		break;
	default:
		break;
	}
}

void CZombie::collided(CObject * obj_)
{
	if (obj_->m_eID == eBullet)
	{
		obj_->bTagged = 1;
		m_ucHits++;

		if ( m_pGame->m_uiParticlesLoaded < MAXPARTICLES )
		for (int i = 0; i < 125; ++i)
		m_pGame->addPart(new CParticle ( m_fX , m_fY , 76 ,"images/s_particles.png", 10 , rand()%10 , 200 + rand()%55 , 200 + rand()%55 ,60 + rand()%180 , 200 + rand()%50 , -180 + rand()%180 , -10 + rand()%20, -10 + rand()%20, 0.6 , 0 + (rand()%15)* 0.02 , 2 , -8 + rand()%16 ) );

		m_fX -= -cos(RAD2DEG(obj_->m_fRotation));
		m_fY -= -sin(RAD2DEG(obj_->m_fRotation));
		if (m_ucHits >= m_ucMaxHits)
		{			
			
			bTagged = 1;
			m_pGame->score--;

		}
	}
	if ((obj_->m_eID == eCharacter) || (obj_->m_eID == eSurvivor))
	{
		
		obj_->collided(this);
	}
	if (obj_->m_eID == eLove)
	{

			if ( m_pGame->m_uiParticlesLoaded < MAXPARTICLES )
		for (int i = 0; i < 1200; ++i)
		m_pGame->addPart(new CParticle ( m_fX , m_fY , 64 ,"images/s_blood.png", 6 , rand()%6 , rand()%255 , rand()%255 , rand()%255 , 255 , -180 + rand()%180 , -10 + rand()%20, -10 + rand()%20, 0.5 , 0 + (rand()%15)* 0.025 , 2 , 2 ) );

		obj_->bTagged = 1;
		float tempRot = RAD2DEG(normalisedX, normalisedY);
		tempRot = DEG2RAD(normalisedX, normalisedY);
		m_pGame->addInst(new CHuman(m_fX,m_fY,64,64,5,255,255,255,255,1,1,m_fSpeed,0,tempRot,0));
		bTagged = 1;
		//code to change into a survivor
	}
	
	else
	{
	}
}