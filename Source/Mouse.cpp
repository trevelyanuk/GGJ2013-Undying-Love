#include "StdAfx.h"

#include <stdio.h>
#include <stdlib.h>
//#include <ctime>
#include <time.h>
#include "Mouse.h"
#include "Input.h"
#include "Audio.h"
#include "Bullet.h"
#include "Love.h"
//rand
//#include "boost/random.hpp"
//#include "boost/generator_iterator.hpp"

//props


// basic file operations
#include <iostream>
#include <fstream>
 #include <sstream>
#include <math.h>	 
using namespace std;
#include "Game.h"



CMouse::CMouse(float x_, float y_, unsigned width_,unsigned height_,unsigned short textureID_, GLubyte r_, GLubyte g_, GLubyte b_,GLubyte a_,
		float xsca_, float ysca_,	float spd_, float rad_, float ang0_, float ang1_, bool fadeable_)
		:CObject(0,0,0,0,0,0,0,0,0,0,0,0,0,0){

	m_fX = 0;
	m_fY = 0;
	m_fZ = -0;
	m_ubR=255;//r_;
	m_ubG=127;//g_;
	m_ubB=127;//b_;
	m_ubA=255;
	m_usTextureID=textureID_;
	m_uiW = m_pSprite->m_pTexture->m_TextData.nWidth;
   	m_uiH = m_pSprite->m_pTexture->m_TextData.nHeight;

	m_usDelay = 3;
	m_fRotAng = 360;
	m_fSze = 5;//sze_;
	m_ucItemType = 0;


	canLoad = false;
	m_uiObjCount = m_uiSpawnDelay = m_uiObjectsLoaded = 0;
	
	m_fMouseX = m_pInput->getdMouseX();
	m_fMouseY = m_pInput->getdMouseY();
	//m_uiRotation = 0;
}

CMouse::~CMouse(void){
	//char message[]="**** Object destroyed ***\n";
	//OutputDebugString(message);
}

void CMouse::Render(){
//if (m_fRotation < 360)m_fRotation+= 1; else m_fRotation = 0;
glPushMatrix();
	glLoadIdentity();		
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
		glBegin(GL_LINES);
		glColor4ub(255,255,255,255);	
			glVertex2d(m_fX,m_fY);
		glColor4ub(255,255,255,20);	
			glVertex2d(m_pGame->m_pCharacter->m_fX,m_pGame->m_pCharacter->m_fY);
		glEnd();
	glTranslated(m_fX,m_fY,m_fZ);	 
	glDisable(GL_BLEND);
	m_pSprite->SnkyBlit(0,0,0);
	//wheres mouse to character
	//glColor4ub(255,255,255,m_ubA);


glPopMatrix();
	/*
glPushMatrix();

	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);




	if (m_usTextureID){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_usTextureID);	
		glColor4ub(255,255,255,m_ubA);
	}else {
		glDisable(GL_TEXTURE_2D);
		glColor4ub(m_ubR,m_ubG,m_ubB,m_ubA);
	}

	glTranslated(m_fX,m_fY,0);
	glRotated(m_fRotAng,0,0,1);

	//draw a quad and adjust it's size with a variable.
	glBegin(GL_QUADS);
		//glTexCoord2d(0.0f, 0.0f);
		glVertex2d(m_fSze, m_fSze);
		//glTexCoord2d(1.0f, 0.0f);
		glVertex2d(-m_fSze, m_fSze);
		//glTexCoord2d(1.0f, 1.0f);
		glVertex2d(-m_fSze, -m_fSze);
		//glTexCoord2d(0.0f, 1.0f);
		glVertex2d(m_fSze, -m_fSze);
	glEnd();

glPopMatrix();*/
}

void CMouse::Update(DWORD f_DT){
	


	m_pInput->getMouseInput();
	//get mouse input from Input class mouse functions.
	m_fMouseX += m_pInput->getdMouseX();
	m_fMouseY += m_pInput->getdMouseY();
    //short scrollWheel = m_pInput->getdMouseZ();


		m_fX = m_fMouseX;// + m_pGame->m_pCenterX;
		m_fY = m_fMouseY;// + m_pGame->m_pCenterY;



	//mouse editor
	
	editorUpdate();
	loadLevel();



}


//mouse editor

void CMouse::editorUpdate(){

	if(m_usDelay)--m_usDelay;

	checkButtons();
	



}

void CMouse::loadLevel(){

    if (canLoad){
		for (unsigned int i = 2000; i > 0; --i){
			
			//if(!m_uiSpawnDelay){
				//m_uiSpawnDelay = 0;
				if(m_uiObjCount < m_uiObjectsLoaded){
m_pGame->m_pObjects[m_pGame->m_uiObjectsLoaded++] = m_pObjects[m_uiObjCount++];
				}
				else {
					canLoad = false;
					//CreateDisplayList();
					for (unsigned int i = 0; i < m_uiObjCount; ++i){ 
						//m_pObjects[i]->m_pSprite = 0;
						//delete m_pObjects[i];
						//m_pObjects[i] = NULL;

					}
					//m_uiObjCount = 0;
				}

			//}
			//else --m_uiSpawnDelay;
		}	
	}
	//

}

void CMouse::checkButtons()
{


}