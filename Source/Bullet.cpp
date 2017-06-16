#include "StdAfx.h"

#include "Bullet.h"
#include <math.h>
#include "Particle.h"
CBullet::CBullet(float x_, float y_, float rot_)
	: CObject(x_, y_)
{
	xvel = cos(rot_ * (PI / 180) );
	yvel = sin(rot_ * (PI / 180) );
	m_fRotation = rot_;
	m_eID = eBullet;
	m_uiW = m_uiH = 1;
}

CBullet::~CBullet(void)
{
}

void CBullet::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
	glPushMatrix();
		glTranslatef(m_fX, m_fY,1);
		glRotatef(RAD2DEG(m_fRotation),0,0,1);
		glScalef(1,1,1);
		glBegin(GL_LINES);
		
		glColor4ub(250,250,10,255);
			glVertex2f(0,0);
			
		glColor4ub(250,250,10,0);
			glVertex2f(-2,0);
		glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();
}
void CBullet::Update(DWORD _timeFrame)
{
	m_fY += yvel * 8 * _timeFrame;
	m_fX += xvel * 8 * _timeFrame;

	if ((m_fX > WIDTH) || (m_fX < 0) || (m_fY > HEIGHT) || (m_fY < 0))
	{
		bTagged = true;
	}
	CollisionTest();
	
		if ( m_pGame->m_uiParticlesLoaded < 6000 )
		m_pGame->addPart(new CParticle ( m_fX , m_fY , 64 ,"images/s_blood.png", 6 , rand()%6 , rand()%255 , rand()%255 , rand()%255 , 255 , -180 + rand()%180 , -10 + rand()%20, -10 + rand()%20, 0.55 , 0 + (rand()%15)* 0.015 , 2 , 1 ) );



}