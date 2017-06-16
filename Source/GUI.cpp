#include "StdAfx.h"

#include "GUI.h"
#include "Game.h"
#include <typeinfo>
#include <vector>
#include <algorithm>
//rand
//#include "boost/random.hpp"
//#include "boost/generator_iterator.hpp"

//props
#include <glaux.h>
// basic file operations
#include <iostream>
#include <fstream>



CGUI::CGUI(CObject * target_):CObject(0,0,0,0,0,0,0,0,0,0,0,0,0,0,false){

	bDisplayListCreated = false;
	canIncreaseDisplayCount = true;
	m_usAlarmTimeDefault = 32;
	m_usAlarmTime = m_usAlarmTimeDefault;
	m_usAlarm = m_usAlarmTime;

	m_pTarget = target_;
	m_pTargetX = m_pTarget->m_fX;
	m_pTargetY = m_pTarget->m_fY;
	m_fAngle0 = 0;
	//srand ( time(NULL) );



}			  ///


CGUI::~CGUI(void){
}



void CGUI::printCharacter(){

	if (m_pGame->eCurrentState == m_pGame->eStateMENU)
	{
		std::stringstream ssTextC;
		ssTextC << "Undying Love";	
		m_pFont->DrawText(ssTextC.str(),HALFWIDTH - ssTextC.str().length()*3,30,255,255,255,255);		

		
		std::stringstream ssTextD;
		ssTextD << "W, S, A and D keys move the player, Left mouse button fires your gun";		
		m_pFont->DrawText(ssTextD.str(),HALFWIDTH - ssTextD.str().length()*3,60,255,255,255,255);	
	
		std::stringstream ssTextE;
		ssTextE << "Right mouse button fires your LOVE GUN";		
		m_pFont->DrawText(ssTextE.str(),HALFWIDTH - ssTextE.str().length()*3,90,255,255,255,255);	
		
		
		std::stringstream ssTextF;
		ssTextF << "Killing zombies will save your life, but decrease you score. Instead, SAVE THEM with your LOVE GUN!";		
		m_pFont->DrawText(ssTextF.str(),HALFWIDTH - ssTextF.str().length()*3,120,255,255,255,255);	

		std::stringstream ssTextG;
		ssTextG << "The LOVE GUN will return the zombie to a (zombie-killing) human. The E key will call all humans currently on-screen to the safe base";		
		m_pFont->DrawText(ssTextG.str(),HALFWIDTH - ssTextG.str().length()*3,150,255,255,255,255);

		std::stringstream ssTextH;
		ssTextH << "Press Space to Begin";		
		m_pFont->DrawText(ssTextH.str(),HALFWIDTH - ssTextH.str().length()*3,180,255,255,255,255);	
	}
if (m_pGame->eCurrentState == m_pGame->eStateLOSE)
	{
		std::stringstream ssTextD;
		ssTextD << "You died.";	
		m_pFont->DrawText(ssTextD.str(),HALFWIDTH - ssTextD.str().length()*3,200,255,255,255,255);		

		
		std::stringstream ssTextE;
		ssTextE << "Press space to restart";		
		m_pFont->DrawText(ssTextE.str(),HALFWIDTH - ssTextE.str().length()*3,250,255,255,255,255);	

		
		std::stringstream ssTextF;
		ssTextF << "Your score was " << m_pGame->score << " and you saved " <<m_pGame->survivors << " people. Kill less, love more <3";
		m_pFont->DrawText(ssTextF.str(),HALFWIDTH - ssTextF.str().length()*3,300,255,255,255,255);	

	}
if (m_pGame->eCurrentState == m_pGame->eStatePLAY)
	{

	for (unsigned int i = 0; i < m_pGame->m_uiObjectsLoaded; ++i){
		CObject * pObj_;
		pObj_ = m_pGame->m_pObjects[i];
		std::stringstream ssTextC;
		if ( pObj_ ){
			if ( pObj_->m_eID == eZombie ){
				m_pFont->DrawText(ssTextC.str(),pObj_->m_fX - 32,pObj_->m_fY - 48,255,255,255,255);		
			}
		}
}

}




/*
		CObject * pObj = m_pGame->m_pCharacter;

  cout << "What's your name? ";
  getline (cin, mystr);
  cout << "Hello " << mystr << ".\n";
  cout << "What is your favorite team? ";
  getline (cin, mystr);
  cout << "I like " << mystr << " too!\n";


stringstream ss("bla bla");
string s;

while (getline(ss, s, ' ')) {
 cout << s << endl;
}

		std::stringstream ssTextC;
		ssTextC << "FPS: " << s << ss;//m_pGame->m_fPrint;// << "isMoving: " << m_fPrint;//pObj->m_bPrint;

		m_pFont->DrawText(ssTextC.str(),-2048,-1024,255,255,255,255);
		ssTextC.str("");
		ssTextC << "X: " << pObj->m_fX << " Y: " << pObj->m_fY;
		m_pFont->DrawText(ssTextC.str(),-2048,-1024+80,255,255,255,255);*/
}

void CGUI::printHud(){
		
	/*
		CCamera * pObj = m_pGame->m_pCamera;
		std::stringstream ssTextC;
		ssTextC << "Diamonds Collected: " << m_pGame->m_usScore;
		m_pFont->DrawText(ssTextC.str(),pObj->m_fX-320,pObj->m_fY-160,204,255,51,225);
		std::stringstream ssTextD;
		unsigned short usArrayItems = m_pGame->m_uiObjectsLoaded;
		unsigned short i;

		unsigned short counter = 0;
		for ( i = 0; i < usArrayItems; ++i){
			if(m_pGame->m_pObjects[i])
			if (m_pGame->m_pObjects[i]->m_eID == m_pGame->m_pObjects[i]->eDiamond){
				++counter;
			}
		}
		ssTextD << "Diamonds Total: " << m_pGame->m_uiDisplayList;
		m_pFont->DrawText(ssTextD.str(),pObj->m_fX-320,pObj->m_fY-160+16,204,255,51,225);
		*/
}



void CGUI::Render()
{

	
	/*
	glPushMatrix();
 	//glEnable(GL_BLEND);// Turn Blending On
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glTranslated(m_fX,m_fY,0);		// move to proper position
		//glScaled(m_uiW,m_uiH,1);
		glColor4ub(m_ubR,m_ubG,m_ubB,m_ubA);		// set color
		//if (m_usTextureID)
		//{
			//use texture
			//glEnable(GL_TEXTURE_2D);
			//glBindTexture(GL_TEXTURE_2D, m_usTextureID); 
		//}

			
	glPopMatrix();
  */
	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);


/*
		std::stringstream ssTextA;
		ssTextA << "Render Frames: " << m_pGame->m_usRenderRate << " /" << " Update Frames: " << m_pGame->m_usUpdateRate;
		m_pFont->DrawText(ssTextA.str(),m_pTargetX-32,m_pTargetY-128,255,255,255,127);

		std::stringstream ssTextB;
		ssTextB << "COUNT: " << m_pGame->m_uiObjectsLoaded-1;
		//ssTextB << "COUNT: " << m_pGame->m_pCamera->m_fMouseZ;
		m_pFont->DrawText(ssTextB.str(),m_pTargetX-32,m_pTargetY-96,255,255,255,127);
*/




  /*
		//distance between two points - Snky.
		float x1,x2,y1,y2;
		float distanceX,distanceY;
		float distance;
		x1 = m_pTargetX; y1 = m_pTargetY;    x2 = m_pGame->m_pCharacter->m_fX; y2 = m_pGame->m_pCharacter->m_fY;
		//x1 = 1; y1 = 7; x2 = 2; y2 = -3;
		distanceX = x1 - x2;
		distanceY = y1 - y2;
		distance = sqrt( (distanceX * distanceX) + (distanceY * distanceY) );
		//distance = sqrt( pow(distanceX, distanceY));
		m_fPrint = distance;


		//square root


	float m = 1129;
     float i=0;
   //float x1,x2;
   while( (i*i) <= m )
          i+=0.1;
   x1=i;
   for(int j=0;j<10;j++)
   {
        x2=m;
      x2/=x1;
      x2+=x1;
      x2/=2;
      x1=x2;
   }
   //m_fPrint = x2;
   //return x2;

	float x,y;
	float radius;
	x = m_pGame->m_pCharacter->m_fX;
	y = m_pGame->m_pCharacter->m_fY;
	radius = 32;
    float angle;
    glPushMatrix();
    glLoadIdentity();
    //glDisable(GL_TEXTURE_2D);
    glColor4ub(255,255,0,255);
    //glLineWidth(4.0f);
    //glBegin(GL_LINE_LOOP);
	glBegin(GL_LINES);
	unsigned short edges = 360;  if(m_fAngle0)--m_fAngle0; else m_fAngle0 = edges;
    for(unsigned short i = 0; i < 20; ++i) {
	
        angle = (m_fAngle0+i)*2*3.14159265/edges;
        glVertex2d(x + (cos(angle) * radius), y + (sin(angle) * radius));

    }
 
    glEnd();
	//glLineWidth(1.0f);
    //glEnable(GL_TEXTURE_2D);
    glPopMatrix();
 */

	printCharacter();
	//printHud();
	//CreateDisplayList();
	//glCallList(m_uiDisplayList);
	

}



void CGUI::instanceFont(void)
{	
	m_pFont = new CFont;
	m_pFont->CreateFont("Arial", 12, FW_EXTRABOLD);
}

/*
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900
*/