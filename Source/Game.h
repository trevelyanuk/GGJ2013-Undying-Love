#pragma once

#include "Main.h"
//#include "Input.h"
#include "gl.h"
//#include "Audio.h"
//#include "boost/cstdint.hpp"
//#include <vector>
//#include <algorithm>
#include "Image.h"



#define x_player_fire "audio/x_dirtDig.wav"


class COverlay;
class CObject;
class CCamera;
class CGUI;

class CGame
{


public:
	int score;
	short xMin, xMax, yMin, yMax, xBet, yBet;
	unsigned short m_usTimerFood;
	float resetZombieTimer;
	float zombieDifficultyNumPerSpawn;
	unsigned short m_usScore;
	float m_pCenterX;
	float m_pCenterY;
	//std::vector <CObject *> m_vArray;
	CObject *m_pObjects[MAXOBJECTS];
	CObject *m_pParticles[MAXPARTICLES];

	unsigned int getNumObjects();
	
	unsigned int iArrayItems;


	CObject * getObjectByIndex(unsigned int index_);
	CObject * m_pCharacter;
	CObject * m_pBase;
	CObject * m_pHuman;
	
    CGUI * m_pGUI;
	CObject *m_pMouse;
	COverlay * m_pOverlay;
	
	//CGameFont *m_pFont;
	//CAudio * m_pAudio;

	//how many Objects have been loaded (increments in .cpp file when Objects are added).
	unsigned int m_uiObjectsLoaded;
	unsigned int m_uiParticlesLoaded;
	
	//enumeration game states (being able to switch states using words instead of 'ints').
	enum eSTATE
	{
		eStateMENU,
		eStatePLAY,
		eStateLOSE,
		eStateWIN
	};

	eSTATE eCurrentState;
	


public:
	~CGame(void);
	
	void Reset();
	void gsPlay();
	void gsMenu();
	void gsLose();
	void gsWin();
	void spawnZombie();
	//loop frame, keeps returning and continues to re-execute.
	void doFrame(void);//bEnterFrame
	void doRender(void);
	void getInput(void);
	void checkTagged(void); 
	void eCheckStateandSwitch(void);
	void addInst(CObject * pObject_);
	void addPart(CObject * pObject_);
	void setAudioPosition(void);
	void beginFrame(void);
	bool m_bActiveWindow;
	//static pointer function to grab the static pointer of the Game(this) instance.
	static CGame *s_pgetInst();	



	int survivors;
	int currentIncrement;
	int nextDifficultyIncremement[10];

protected:
	CGame(void);

private:
	//static pointer to the Game(this) instance.
	static CGame * _pGameinst;
	float zombieTimer;
	


	

};