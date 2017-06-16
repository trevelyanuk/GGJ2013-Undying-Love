#pragma once
#include "Object.h"

class CCamera
{

public:

	float m_fPrint;
	float m_fX;
	float m_fY;
	float m_fZ;
	float m_fLookAtX;
	float m_fLookAtY;
	float m_fLookAtZ;
	float m_cZoom;
	unsigned char m_ucScrollDelay;


private:
	
	CObject * m_pTarget;
	float m_TargetX,m_TargetY;
	void setpTarget(CObject * target_);


	float m_uiHalfWidth,m_uiHalfHeight;
	bool snkyFrustum(void);




/* need to zero out the ticklist array before starting */
/* average will ramp up until the buffer is full */
/* returns average ticks per frame over the MAXSAMPPLES last frames */

public:
	CCamera(CObject * target_);
	~CCamera();
	void Render();
	void Render3D();
	void Update(DWORD _timeFrame);

	
};