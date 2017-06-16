#include "StdAfx.h"
#include <math.h>
#include "Human.h"
#include "Bullet.h"
CHuman::CHuman(float x_, float y_,unsigned width_,unsigned height_, unsigned short textureID_, GLubyte r_, GLubyte g_, GLubyte b_,GLubyte a_,
		float xsca_, float ysca_,	float spd_, float rad_, float ang0_, bool fadeable_)
		:CObject(x_, y_,width_,height_, textureID_, r_, g_, b_, a_,	xsca_, ysca_, spd_, rad_, ang0_, fadeable_)
{
	
	m_eID = eCharacter;
	delay = 90;
	maxShots = (rand() % 5) + 10;
	m_eSurvivorState = survivorIdle;
	m_pSprite = CImage::CreateImage("images/s_character.png",TRectanglei(0,64,0,64));
}

CHuman::~CHuman(void)
{
}


void CHuman::Update(DWORD _timeFrame)
{
	switch (m_eSurvivorState)
	{
	case eSurvivorState::survivorIdle:
		{
			if (m_pInput->igetIfKeyDown(DIK_E))
			{
				m_eSurvivorState = survivorReturn;
			}

			delay--;
			if (delay <= 0)
			{
				m_eSurvivorState = survivorAttack;
				shot = 0;
				delay  = 0;
			}

			//if (m_pInput->igetIfKeyDown(DIK_R))
			//{
			//	m_eSurvivorState = survivorAttack;
			//}
		}
		break;
	case eSurvivorState::survivorAttack:
		{		
			
			delay--;
			if (delay <= 0)
			{
				m_pGame->addInst(new CBullet(m_fX,m_fY, m_fAngle0));
				delay = 3;
				++shot;
				if (shot >= maxShots)
				{
					delay = 90;
					shot = 0;
					maxShots = (rand() % 5) + 10;
				}

			}

			
			
			if (m_pInput->igetIfKeyDown(DIK_E))
			{
				m_eSurvivorState = survivorReturn;
			}
		}
		break;
	case eSurvivorState::survivorReturn:
		{
			float baseX = m_pGame->m_pBase->m_fX;
			float baseY = m_pGame->m_pBase->m_fY;

			float vectorX = baseX - m_fX;
			float vectorY = baseY - m_fY;

			float distance = sqrt((vectorX * vectorX) + (vectorY * vectorY));

			normalisedX = vectorX / distance;
			normalisedY = vectorY / distance;

			m_fX += normalisedX * _timeFrame;
			m_fY += normalisedY * _timeFrame;
			if (distance < 1)
			{
				m_pGame->score+= 5;
				++m_pGame->survivors;
				if (m_pGame->survivors > m_pGame->nextDifficultyIncremement[m_pGame->currentIncrement])
				{
					++m_pGame->currentIncrement;
					m_pGame->zombieDifficultyNumPerSpawn++;
					m_pGame->resetZombieTimer -= 5;
				}
				bTagged = 1;
			}
		}
		break;
	default:
		break;
	}
}