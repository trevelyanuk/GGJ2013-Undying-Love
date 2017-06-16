#include "StdAfx.h"

#include "Player.h"
#include "Math.h"
#include "Bullet.h"
#include "Love.h"
#include "Audio.h"

#include "Overlay.h"
CPlayer::CPlayer(float x_, float y_,unsigned width_,unsigned height_, unsigned short textureID_, GLubyte r_, GLubyte g_, GLubyte b_,GLubyte a_,
		float xsca_, float ysca_,	float spd_, float rad_, float ang0_, bool fadeable_)
		:CObject(x_, y_,width_,height_, textureID_, r_, g_, b_, a_,	xsca_, ysca_, spd_, rad_, ang0_, fadeable_)
{
	
	m_eID = eCharacter;
	m_ucHealth = 100;
	m_pSprite = CImage::CreateImage("images/s_character.png",TRectanglei(0,64,0,64));
	m_pSpriteGun = CImage::CreateImage("images/s_gun0.png",TRectanglei(0,5,0,8));
	m_ubA = 255;
	m_fAngle0 = 0; // players current rotation
	m_ucDelayBullet = 0;
}

CPlayer::~CPlayer(void)
{
}

INT CPlayer::sign( int int_){

	if(int_ > 0)
		return 1; 
	else if(int_ < 0)
		return -1;
	else return 0;

}


void CPlayer::Update(DWORD _timeFrame)
{
	if (m_pInput->igetIfKeyDown(DIK_W))
	{ 
		m_fY -=2 * _timeFrame;
	}
	if (m_pInput->igetIfKeyDown(DIK_S))
	{ 
		m_fY +=2 * _timeFrame;
	}
	if (m_pInput->igetIfKeyDown(DIK_A))
	{ 
		m_fX -=2 * _timeFrame;
	}
	if (m_pInput->igetIfKeyDown(DIK_D))
	{ 
		m_fX +=2 * _timeFrame;
	}

	if (m_ucDelayLove)
	{
		m_ucDelayLove--;
	}
	if (m_ucDelayBullet)
	{
		m_ucDelayBullet--;
	}

		float dx , dy;
		dx = m_fX - m_pGame->m_pMouse->m_fX;
		dy = m_fY - m_pGame->m_pMouse->m_fY;
		float ang = -90 + DEG2RAD(atan2( dy , dx ));

		int idist = angdif(ang , m_fAngle0 );


		m_fAngle0 += min ( abs ( idist ) , 3 ) * sign ( idist );


		//bullet angle
		float bullAngle = ( m_fAngle0 - 90 ) - 10 + rand()%20;

	if (m_pInput->bMouseButtonDown(0))
	{
		if (m_ucDelayBullet <= 0)
		{

			m_pGame->addInst(new CBullet(m_fX ,m_fY, bullAngle ));
			m_ucDelayBullet = 2;
			m_pAudio->playSound(x_player_fire , m_fX, m_fY , 0 , false , false ); // ( sound , x ,y , z , repeat , relative )
		}
		
	}
	else
	if (m_pInput->bMouseButtonDown(1))
	{
		if (m_ucDelayLove <= 0)
		{
			m_pGame->addInst(new CLove(m_fX,m_fY, bullAngle ));
			m_ucDelayLove = 60;

		}
	}

	CollisionTest();


}

int CPlayer::angdif(int tar_ , int cur_){

	return ((((tar_ - cur_) % 360) + 540) % 360) - 180;



}

void CPlayer::Render(){
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_usTextureID);	
		glColor4ub(255,255,255,m_ubA);
		
		

		glTranslatef(m_fX,m_fY,0);


		glRotatef( m_fAngle0 , 0 , 0 , 1 );



		m_pSprite->SnkyBlit(0,0,0);

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

		
		m_pSpriteGun->SnkyBlit(0,0,0);

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

void CPlayer::collided(CObject *obj_)
{
	--m_ucHealth;
	if(m_ucHealth <= 0)
	{
		m_pGame->eCurrentState = m_pGame->eStateLOSE;
		m_pGame->m_pOverlay = new COverlay(true, 160, 
			255, 255, 255,255,
			96,0,0,160);
	}
}