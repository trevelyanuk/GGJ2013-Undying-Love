#pragma once
#include "Game.h"
#include "Object.h"

//transitionTo structs

class COverlay
{
public:
	COverlay(bool transitioning_, float transitionVariable, 
		 float r_, float g_, float b_, float a_, float r2_, float g2_, float b2_, float a2_);

	virtual ~COverlay();
	bool Update(DWORD dt_);
	void Render();
	float transitionTime;
	bool transitioning;
	float transitionToTime;
	float transitionIncrement;


	GLubyte m_ubDesiredR;
	GLubyte m_ubDesiredG;
	GLubyte m_ubDesiredB;
	GLubyte m_ubDesiredA;

	float absm_ubR;
	float absm_ubG;
	float absm_ubB;
	float absm_ubA;

	float m_ubR;
	float m_ubG;
	float m_ubB;
	float m_ubA;


	float m_ubIncrementR;
	float m_ubIncrementG;
	float m_ubIncrementB;
	float m_ubIncrementA;

};

