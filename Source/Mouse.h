#pragma once
#include "Object.h"

class CMouse
	:public CObject
{
private:
	float m_fRotAng;			//rotation angle.
	float m_fSze;				//size of mouse.
	unsigned short m_usDelay;
	float accumVal; 
	int loveDelay;
	int bulletDelay;

public:
	CMouse(float x_, float y_,unsigned width_,unsigned height_, unsigned short textureID_, GLubyte r_, GLubyte g_, GLubyte b_,GLubyte a_,
		float xsca_, float ysca_,	float spd_, float rad_, float ang0_, float ang1_, bool fadeable_);

	virtual ~CMouse();
	virtual void Render();
	virtual void Update(DWORD dt_);

	// global mouse position variables (gets direct input from 'Input' class).
	float m_fMouseX;
	float m_fMouseY;
	void loadLevel();
//mouse editor
private:

	void editorUpdate(void);
	void checkButtons(void);

	void addInst(CObject * pobject_);

	unsigned char m_ucItemType;
	unsigned int m_usPosRead;
	CObject *m_pObjects[MAXOBJECTS];

	unsigned int m_uiObjectsLoaded;
	unsigned short m_uiSpawnDelay;
	unsigned int m_uiObjCount;

	bool canLoad;

	int fun;
//.
};