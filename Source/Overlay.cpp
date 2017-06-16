#include "StdAfx.h"
#include "Overlay.h"

COverlay::COverlay(bool transitioning_, float transitionVariable, 
		 float r_, float g_, float b_, float a_, float r2_, float g2_, float b2_, float a2_)
{
	transitioning = transitioning_;
	transitionIncrement = transitionVariable;
	transitionTime = 0;
	m_ubR= absm_ubR = r_;
	m_ubG=absm_ubG = g_;
	m_ubB=absm_ubB = b_;
	m_ubA=absm_ubA =a_;

	m_ubDesiredR=r2_;
	m_ubDesiredG=g2_;
	m_ubDesiredB=b2_;
	m_ubDesiredA=a2_;

	m_ubIncrementR=r2_ - r_;
	m_ubIncrementG=g2_ - g_;
	m_ubIncrementB=b2_ - b_;
	m_ubIncrementA=a2_ - a_;


	m_ubIncrementR/= transitionIncrement;
	m_ubIncrementG/= transitionIncrement;
	m_ubIncrementB/= transitionIncrement;
	m_ubIncrementA/= transitionIncrement;	



	

}
COverlay::~COverlay()
{};
void COverlay::Render()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);		
		glColor4ub(m_ubR,m_ubG,m_ubB,m_ubA);

		glBegin(GL_QUADS);
			glVertex2d(0,0);
			glVertex2d(0, HEIGHT);
			glVertex2d(WIDTH, HEIGHT);
			glVertex2d(WIDTH, 0);
		glEnd();
		glDisable(GL_BLEND);
	glPopMatrix();
}

bool COverlay::Update(DWORD dt_)
{
	if (transitioning)
	{			
		if (transitionTime < transitionIncrement)
		{
			transitionTime++;		

			absm_ubR+= m_ubIncrementR;
			absm_ubG+= m_ubIncrementG;
			absm_ubB+= m_ubIncrementB;
			absm_ubA+= m_ubIncrementA;

			m_ubR = absm_ubR;
			m_ubG = absm_ubG;
			m_ubB = absm_ubB;
			m_ubA = absm_ubA;
		}
		else
		{
			return false;
		}

	}
	return true;

}

