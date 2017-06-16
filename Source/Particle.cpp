
#include "StdAfx.h"

#include "Particle.h"

CParticle::CParticle(float x_, float y_ , int width_, const string& spr_ , int framecount_, uc ind_ , 
					 uc r_ , uc g_ , uc b_ , uc a_ , float zrot_ ,
				     char xo_ , char yo_ , float scastart_ , float scaend_ ,
			         char spdfade_ , char spdrot_ )	: CObject(x_ , y_)
{
	m_fXVel = cos(zrot_);
	m_fYVel = sin(zrot_);
	m_fRotation = zrot_;
	//m_eID = eParticle;
	
	//import
	m_fX = x_;
	m_fY = y_;
	//m_pSprite = spr_;
	m_ucIndex = ind_;
	m_ubR = r_;
	m_ubG = g_;
	m_ubB = b_;
	m_ubA = a_;
	m_cXOff = xo_;
	m_cYOff = yo_;
	m_fUScaStart = scastart_;
	m_fUScaEnd = scaend_;
	m_cXOff = xo_;
	m_cYOff = yo_;
	m_cSpdFade = spdfade_;
	m_cSpdRot = spdrot_;
	m_ucFramesTotal = framecount_ - 1;
	m_iWidth = width_;
	//0 96 96 * m_ucIndex,96 * ( m_ucIndex + 1 )
	//top bottom left right
	//m_pSprite = CImage::CreateImage("images/s_particles.png",TRectanglei(0,74,0,74));//TRectanglei(0 , 96 , 96 * m_ucIndex , 96 * ( m_ucIndex + 1 ) ));
	m_pSprite = CImage::CreateImage(spr_,TRectanglei(0,m_iWidth,0,m_iWidth));//TRectanglei(0 , 96 , 96 * m_ucIndex , 96 * ( m_ucIndex + 1 ) ));

	m_uiW = m_pSprite->m_pTexture->m_TextData.nWidth;
   	m_uiH = m_pSprite->m_pTexture->m_TextData.nHeight;

	

	m_uiW = m_uiW * 0.5;
	m_uiH = m_uiH * 0.5;

	bTagged = false;


	//glScalef( m_ucUScaStart , m_ucUScaStart , 0 );
}


CParticle::~CParticle(void)
{
}

void CParticle::Render()	
{
	//Update(1);
	
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_usTextureID);	
		glColor4ub(m_ubR,m_ubG,m_ubB,m_ubA);
		
		
		
		glTranslatef(m_fX,m_fY,0);
		glScalef( m_fUScaStart, m_fUScaStart , 0 );
		glRotatef( m_fRotation ,  0 , 0 , 1 );
		if ( m_iWidth == 76 ){
			m_pSprite->SnkyBlit(-m_iWidth*0.5,-m_iWidth*0.5,m_ucIndex*m_iWidth);
		}
		else
		if ( m_iWidth == 64 ){
			m_pSprite->SnkyBlit(-m_uiW,-m_uiW,m_ucIndex*(m_uiW*2));

		}
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
	


}
void CParticle::Update(DWORD _timeFrame)
{
	m_fY += m_fYVel * 3;
	m_fX += m_fXVel * 3;
	m_fRotation += m_cSpdRot;

	if ( m_fUScaStart > m_fUScaEnd ) m_fUScaStart -= 0.025;

	if ( m_ubA > 1 ) m_ubA -= m_cSpdFade; else bTagged = true;

}