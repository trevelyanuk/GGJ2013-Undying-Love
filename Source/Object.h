#pragma once
//#include <gl.h>
#include "Game.h"


class CObject  
{


protected:
	//constructor.
	CObject();

public:

	float debug_float;
	
	bool bFadeable;
	unsigned int bHit;
	
public:

	int angdif (int tar_ , int cur_);
	int sign ( int int_ );


	enum ID_ENUM
	{
		eUndefined,
		eCharacter,
		eZombie,
		eLove,
		eSurvivor,
		eDirt,			
		eBullet
	};
	ID_ENUM m_eID;


	bool bTagged;

	unsigned char  m_ucHealth;
	unsigned char  m_ucDepth;
	unsigned char  m_ucSolid;



	float m_fX;						//x position.
	float m_fY;						//y position.
	float m_fZ;						//z position.
	float m_fStartX;
	float m_fStartY;
	float m_fStartZ;
	float m_fXscale;				//x scale.
	float m_fYscale;				//y scale.
	float m_fZscale;				//z scale.


	float m_fGravity;

	TImagePtr m_pSprite;
	unsigned short m_usTextureID;	//which of the preloaded textures to use.
	unsigned int m_uiW;				//half width of image.
	unsigned int m_uiH;				//half height of image.

	float m_fAngle0;				//angle0, the start position of drawing a circle.
	float m_fRotation;
	float m_fSpeed;					//speed.
	char  m_cRadius;				//radius.
	bool  m_isMoving;
	
	GLubyte m_ubR;					//red component between 0 and 255.
	GLubyte m_ubG;					//green component between 0 and 255.
	GLubyte m_ubB;					//blue component between 0 and 255.
	GLubyte m_ubA;					//alpha value 0-255.
	
	

	



public:
	bool AABB(CObject * obj_);
	bool Circle(CObject * obj_, float rad_);
	void CollisionTest();
	virtual void collided(CObject * obj_);

	//main function of Object.
	CObject(float x_, float y_,unsigned width_,unsigned height_, unsigned short textureID_ = 0,
		GLubyte r_ = 255, GLubyte g_ = 255, 
		GLubyte b_ = 255,GLubyte a_ = 255,
		float xsca_ = 1.00, float ysca_ = 1.00, 
		float spd_ = 0.00,	float rad_ = 0.00, float ang0_ = 0.00,
		bool fadeable_ = false); 
	CObject(float x_, float y_); 



	virtual void destroyEvent(void){;}
	virtual ~CObject();
	virtual void Render();
	virtual void Update(DWORD dt_);
	virtual void soundPlay(char * filename_, float x_, float y_, float z_ = -32);

	void vector2d(float x_ , float y_ , float scalar_ = 1.0f);


private:
	GLubyte ubScale;

}; 