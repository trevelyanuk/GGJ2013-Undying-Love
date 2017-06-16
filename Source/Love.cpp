#include "StdAfx.h"

#include "Love.h"
#include <math.h>

CLove::CLove(float x_, float y_, float rot_)
	: CObject(x_, y_)
{
	xvel = cos(rot_ * (PI / 180) );
	yvel = sin(rot_ * (PI / 180) );
	m_fRotation = rot_;
	m_eID = ID_ENUM::eLove;
}

CLove::~CLove(void)
{
}

void CLove::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
	glPushMatrix();
		glTranslatef(m_fX, m_fY,1);
		glRotatef(m_fRotation,0,0,1);
		glScalef(1,1,1);
		glBegin(GL_LINES);
		
		glColor4ub(255,230,255,255);
			glVertex2f(5,0);
			
		glColor4ub(250,230,255,50);
			glVertex2f(0,0);
		glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();
}
void CLove::Update(DWORD _timeFrame)
{
	m_fY += yvel * 5;
	m_fX += xvel * 5;
	CollisionTest();
	
}