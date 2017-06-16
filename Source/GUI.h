#pragma once
#include "Object.h"
#include "Font.h"
#include <sstream>
#include <string>
using namespace std;
class CGUI
	:public CObject
{
private:
	

public:
	
	virtual ~CGUI();
	virtual void Render();
	CGUI(CObject * target_);
	
	CFont *m_pFont;
	void instanceFont(void);

private:
stringstream ss;

char a[5];
	  string mystr;

	CObject * m_pTarget;
	float m_pTargetX,m_pTargetY;

	void CreateDisplayList();
	bool bDisplayListCreated;
	GLuint m_uiDisplayList;
	bool canIncreaseDisplayCount;

	unsigned short m_usAlarm;
	unsigned short m_usAlarmTime;
	unsigned short m_usAlarmTimeDefault;


	//print what?
	void printCharacter(void);
	void printHud(void);



};