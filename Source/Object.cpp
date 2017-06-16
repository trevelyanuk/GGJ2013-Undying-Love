#include "StdAfx.h"

#include "Object.h"
//#include "Input.h"
#include "Audio.h"
#include "Input.h"
#include <Math.h>

CObject::CObject()
{
	m_fX=0;
	m_fY=0;
	m_uiW=0;
	m_uiH=0;
	m_fXscale=1;
	m_fYscale=1;
	m_fSpeed=0;
	//m_fRadius=0;
	m_ubR=255;
	m_ubG=255;
	m_ubB=255;
	m_ubA=255;
	m_usTextureID=0;
	//m_eID = eUNKNOWN;

	m_ucSolid = 1;
}

CObject::CObject(float x_, float y_, unsigned width_,unsigned height_,unsigned short textureID_, GLubyte r_, GLubyte g_, GLubyte b_,GLubyte a_,
		float xsca_, float ysca_,	float spd_, float rad_, float ang0_, bool fadeable_)
{
	m_fX=x_;
	m_fY=y_;
	m_fXscale = xsca_;
	m_fYscale = ysca_;
	m_fAngle0 = ang0_;
	m_fSpeed=spd_;
	m_ubR=r_;
	m_ubG=g_;
	m_ubB=b_;
	m_ubA=a_;
	m_usTextureID=1;

	bTagged = false;
	//m_eID = _tag;
	//bFadeable = destroyable_;
	ubScale = 150;

	m_pSprite = CImage::CreateImage("images/sDynamite0.png",TRectanglei(0,64,0,64));

	m_uiW = m_pSprite->m_pTexture->m_TextData.nWidth;
   	m_uiH = m_pSprite->m_pTexture->m_TextData.nHeight;
	m_uiW = m_uiW * 0.5;
	m_uiH = m_uiH * 0.5;

	m_isMoving = false;

	/*enum ID_ENUM{
		
			Character,
			Dirt,
			Wall,
			Rock,
			UNKNOWN
	};*/



}CObject::CObject(float x_, float y_)
{
	m_fX=x_;
	m_fY=y_;
	m_isMoving = false;
	bTagged = false;

}
CObject::~CObject(void){
} 

INT CObject::sign( int int_)
{
	if(int_ > 0)
		return 1; 
	else if(int_ < 0)
		return -1;
	else return 0;
}

int CObject::angdif(int tar_ , int cur_)
{
	return ((((tar_ - cur_) % 360) + 540) % 360) - 180;
}

void CObject::Render(){
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_usTextureID);	
		glColor4ub(255,255,255,m_ubA);
		
		

		glTranslatef(m_fX,m_fY,0);
		
		m_pSprite->SnkyBlit(64,64,0);

		glBegin(GL_QUADS);
			glTexCoord2d(0.00, 0.00);
			glVertex2d(-32,-32);
			glTexCoord2d(0.00, 1.00);
			glVertex2d(-32, 32);
			glTexCoord2d(1.00, 1.00);
			glVertex2d(32, 32);
			glTexCoord2d(1.00, 0.00);
			glVertex2d(32, -32);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	glPopMatrix();
}

void CObject::Update(DWORD dt_)
{
	
}


void CObject::CollisionTest()
{
	unsigned int total;
	unsigned int i = 0;
	total = m_pGame->m_uiObjectsLoaded;
	if (total)
	{
		int k = 2;
	}

	for (i = 0; i < total; i++)
	{	
		if (m_pGame->m_pObjects[i])
		{
			if (m_pGame->m_pObjects[i]->m_eID != m_eID)
			{
				if (Circle(m_pGame->m_pObjects[i], 20))
				{
					m_pGame->m_pObjects[i]->collided(this);
				}
			}
		}
	}
}

bool CObject::AABB(CObject * obj_)
{
	if (m_fX + m_uiW < obj_->m_fX)
	{
		return false;
	}
	if (m_fX > obj_->m_fX + obj_->m_uiW)
	{
		return false;
	}
	if (m_fY + m_uiH < obj_->m_fY)
	{
		return false;
	}
	if (m_fY > obj_->m_fY + obj_->m_uiH)
	{
		return false;
	}
	return true;
}
bool CObject::Circle(CObject * obj_, float rad_)
{
	float tx = (m_fX - obj_->m_fX) * (m_fX - obj_->m_fX);
	float ty = (m_fY - obj_->m_fY) * (m_fY - obj_->m_fY);
	if (sqrt(
		(tx) + (ty)
		) > rad_)
	{
		return false;
	}
	return true;
}

void CObject::soundPlay(char * filename_, float x_, float y_, float z_){

	m_pAudio->playSound(filename_,x_,y_,z_,false,false);

}


void CObject::vector2d(float x_, float y_, float scalar_){


	m_fX += x_ * scalar_;
	m_fY += y_ * scalar_;

}

void CObject::collided(CObject * obj_)
{
	
}