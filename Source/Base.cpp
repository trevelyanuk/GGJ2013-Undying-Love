#include "StdAfx.h"

#include "Base.h"

CBase::CBase(float x_, float y_,unsigned width_,unsigned height_, unsigned short textureID_, GLubyte r_, GLubyte g_, GLubyte b_,GLubyte a_,
		float xsca_, float ysca_,	float spd_, float rad_, float ang0_, bool fadeable_)
		:CObject(x_, y_,width_,height_, textureID_, r_, g_, b_, a_,	xsca_, ysca_, spd_, rad_, ang0_, fadeable_)
{
	
	m_eID = eCharacter;
	m_pSprite = CImage::CreateImage("images/s_base.png",TRectanglei(0,64,0,64));
}
CBase::~CBase(void)
{
}


void CBase::Update(DWORD _timeFrame)
{

}