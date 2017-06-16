#include "StdAfx.h"

#include "Game.h"
#include <time.h>
#include "Input.h"
#include "Mouse.h"
#include "Object.h"
#include "Player.h"
#include "Zombie.h"
#include "Human.h"
#include "GUI.h"
#include "Audio.h"
#include "Overlay.h"
#include "Base.h"
#include <math.h>
#include <glu.h>

#include "Particle.h"

//require
//#include "o_exit.h"

CGame::CGame(void)
{
	m_pMouse = new CMouse(0,0,16,16,0,255,255,255,255,1,1,0,0,0,0,false);
	m_pGUI = new CGUI(m_pMouse);
	m_pOverlay = new COverlay(false,60,255,255,255,200,127,127,127,64);
	//addInst (new o_exit(608 , 610));

	
	int tempint = 0;
	nextDifficultyIncremement[tempint++] = 5;
	nextDifficultyIncremement[tempint++] = 15;
	nextDifficultyIncremement[tempint++] = 30;
	nextDifficultyIncremement[tempint++] = 60;
	nextDifficultyIncremement[tempint++] = 100;
	nextDifficultyIncremement[tempint++] = 140;	
	nextDifficultyIncremement[tempint++] = 200;
	nextDifficultyIncremement[tempint++] = 280;	
	nextDifficultyIncremement[tempint++] = 400;	
	nextDifficultyIncremement[tempint++] = 600;

	Reset();
}
CGame::~CGame(void){
	
	//delete all Objects if exists.
	for (unsigned int i = 0; i < m_uiObjectsLoaded; ++i)
	{
		delete m_pObjects[i];
		m_pObjects[i] = NULL;
	}
	//external function to kill game using the escape button.
	Cmain::s_pKillProgram();
}

//function to add a Object, can be accessed by other classes, helps to shorten instance creation code. 
//e.g. m_pGame->addInst   instead of   CGame::getInst()->addInst 
void CGame::addInst(CObject * pobject_)
{
	m_pObjects[m_uiObjectsLoaded++] = pobject_;
	//m_vArray.push_back(pobject_);
}

void CGame::addPart(CObject * pobject_)
{
	m_pParticles[m_uiParticlesLoaded++] = pobject_;
	//m_vArray.push_back(pobject_);
}

//loop function updates and renders every Object.


void CGame::doFrame()
{

	getInput();
	setAudioPosition();
	
	m_pGUI->Update(1);
	m_pMouse->Update(1);


	switch (eCurrentState) 
	{
		case eStatePLAY : 
			{
				gsPlay();
			}
			break;
		case eStateMENU : 
			{
				gsMenu();				
			}
			break;
		case eStateLOSE : 
			{
				gsLose();				
			}
			break;
		case eStateWIN : 
			{
				gsWin();				
			}
			break;
		default:break;
	}


}
void CGame::gsPlay()
{
	checkTagged();
	m_pCharacter->Update(1);
	m_pBase->Update(1);
	spawnZombie();
}
void CGame::gsLose()
{
	
	

	if (!m_pOverlay->Update(1))
	{
		
		if (m_pInput->igetIfKeyDown(DIK_SPACE))
		{ 
			for (unsigned int i = 0; i < m_uiObjectsLoaded; ++i)
				{
					delete m_pObjects[i];
					m_pObjects[i] = NULL;
				}
			Reset();
			
			m_pOverlay = new COverlay(true,180,m_pOverlay->m_ubR,m_pOverlay->m_ubG,m_pOverlay->m_ubB,m_pOverlay->m_ubA,255,255,255,200);
		}
	}
}
void CGame::gsWin()
{
	checkTagged();
	m_pCharacter->Update(1);
	m_pBase->Update(1);
	spawnZombie();
}
void CGame::gsMenu()
{

	if (m_pInput->igetIfKeyDown(DIK_SPACE))
	{ 
		m_pOverlay->transitioning = true;
	}
	
	if (m_pOverlay->transitioning)
	{
		if (!m_pOverlay->Update(1))
		{
			eCurrentState =eStatePLAY;
			delete m_pOverlay;
			m_pOverlay = NULL;
		}
	}
		
}
void CGame::spawnZombie()
{
	zombieTimer--; 
	if (zombieTimer <= 0)
	{
		float zombieSpeed;
		int type = rand()%3 + 1;
		float newZombieVector = rand()%360;
		newZombieVector  *= 180/3.1415;
		float r = rand()%500;
		unsigned int radius = 500;

		float newZombieX = HALFWIDTH + ( (radius + r ) * cos(newZombieVector));
		float newZombieY = HALFHEIGHT + ( (radius + r ) * sin(newZombieVector));

		switch (type)
		{
		case 1:
			{
				zombieSpeed = 0.1;
			}
			break;
		case 2:
			{
				zombieSpeed = 0.3;
			}
			break;
		case 3:
			{
				zombieSpeed = 0.5;
			}
			break;
		default:
			break;
		}

		for (int d = 0; d < zombieDifficultyNumPerSpawn; d++)
		{
			addInst(new CZombie(newZombieX, newZombieY, 64,64,1,255,255,25,255,1,1,zombieSpeed,-newZombieVector,0,0,type));
		}
		zombieTimer = resetZombieTimer;
	}
}

void CGame::doRender()
{
	glClear(GL_COLOR_BUFFER_BIT);

	

	unsigned int usArrayItems = m_uiObjectsLoaded;
	unsigned int i;

//depth
	m_pBase->Render();

	for (i = 0; i < usArrayItems; i++)
	{
		if(m_pObjects[i] != NULL)
		{
				m_pObjects[i]->Render();

		}  
	}

	usArrayItems = m_uiParticlesLoaded;
	for (i = 0; i < usArrayItems; i++)
	{
		if(m_pParticles[i] != NULL)
		{
				m_pParticles[i]->Render();

		}  
	}
	m_pCharacter->Render();
	if(m_pOverlay)
	{
		m_pOverlay->Render();
	}
	else
	{
		
		m_pMouse->Render();
		
	}
	m_pGUI->Render();
}

void CGame::setAudioPosition()
{

		m_pCenterX = m_pCharacter->m_fX;
		m_pCenterY = m_pCharacter->m_fY;
   		m_pAudio->setListenerPosition(m_pCenterX,m_pCenterY,0);

		//if ( m_uiParticlesLoaded < MAXPARTICLES )
		//addPart(new CParticle ( m_fX , m_fY , "images/spritesheet.png" , rand()%10 , rand()%255 , rand()%255 , rand()%255 , 255 , -180 + rand()%180 , -10 + rand()%20, -10 + rand()%20, 0.5 , 0 + (rand()%15)* 0.025 , 2 , 2 ) );


}
void CGame::getInput()
{
				

	if(m_bActiveWindow)m_pInput->getKeyboardInput();	
	
	
	if (m_pInput->igetIfKeyDown(DIK_ESCAPE))
	{ // || m_pInput->igetIfKeyDown(DIK_Q))
		CGame::~CGame();
	}
}



void CGame::checkTagged()
{

	iArrayItems = m_uiObjectsLoaded;
	unsigned int i;
	unsigned int j;
	
	for (i = 0; i < iArrayItems;++i)
	{	
		if(m_pObjects[i])
		{
			if (m_pObjects[i]->bTagged)
			{
				m_pObjects[i]->m_pSprite = 0;
				delete m_pObjects[i];
				m_pObjects[i] = NULL;
				if (i < (m_uiObjectsLoaded-1))
				{
						m_pObjects[i] = m_pObjects[m_uiObjectsLoaded-1];
						m_pObjects[m_uiObjectsLoaded-1] = NULL;
				}
				--m_uiObjectsLoaded;		   
			}
			else m_pObjects[i]->Update(1); 
			

		}
	}

	iArrayItems = m_uiParticlesLoaded;
	for (i = 0; i < iArrayItems;++i)
	{	
		if(m_pParticles[i])
		{
			if (m_pParticles[i]->bTagged)
			{
				m_pParticles[i]->m_pSprite = 0;
				delete m_pParticles[i];
				m_pParticles[i] = NULL;
				if (i < (m_uiParticlesLoaded-1))
				{
						m_pParticles[i] = m_pParticles[m_uiParticlesLoaded-1];
						m_pParticles[m_uiParticlesLoaded-1] = NULL;
				}
				--m_uiParticlesLoaded;		   
			}
			else m_pParticles[i]->Update(1); 
			

		}
	}

}
unsigned int CGame::getNumObjects()
{
	return m_uiObjectsLoaded;
}

CObject * CGame::getObjectByIndex(unsigned int index_)
{
	return m_pObjects[index_];
}



CGame *CGame::_pGameinst=0;
CGame *CGame::s_pgetInst()
{
	if (0==_pGameinst){
		_pGameinst=new CGame();
	}
	return _pGameinst;
}

void CGame::Reset()
{
	score = 0;	
	srand ( time(NULL) );
	zombieDifficultyNumPerSpawn = 1;
	resetZombieTimer = 120;
	eCurrentState = eStateMENU;
	//load Objects.
	m_usScore = m_uiParticlesLoaded = m_uiObjectsLoaded = 0;
	//m_uiDisplayList = 1;
	
	resetZombieTimer = 180;
	xMin = -672;
	xMax = 608;
	yMin = -32;
	yMax = 864;

	xBet = xMax - xMin;
	yBet = yMax - yMin;
	m_usTimerFood = 400;

	//m_pAudio = new CAudio(); /// OLIVA y u remove!
	m_pBase = new CBase(HALFWIDTH,HALFHEIGHT,64,64,1,255,0,0,50,1,1,1,0,0,0);
	m_pCharacter = new CPlayer(HALFWIDTH,HALFHEIGHT,64,64,1,255,200,255,25,1,1,1,0,0,0);

	currentIncrement = 0;
	survivors = 0;
}