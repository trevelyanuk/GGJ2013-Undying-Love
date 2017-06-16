#if !defined(AFX_EXAM_H__75CD0E11_20EE_4B88_B690_D01195218237__INCLUDED_)
#define AFX_EXAM_H__75CD0E11_20EE_4B88_B690_D01195218237__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <iostream>							
//#include <boost/shared_ptr.hpp>
//#include <boost/regex.hpp>

//using namespace std;
	//#include <mmsystem.h>
	#define DWORD_MAX 4294967295UL
	#define WIDTH 1024//1280
	#define HEIGHT 768//720
	#define HALFWIDTH WIDTH *0.5
	#define HALFHEIGHT HEIGHT *0.5
	#define PI 3.14159265
	#define DEG2RAD(x) x * (180 / 3.14159265)
	#define RAD2DEG(x) x * (3.14159265 / 180)
	//Exclude rarely-used stuff from Windows headers.
	#define WIN32_LEAN_AND_MEAN	

	#define MAXOBJECTS 5000
	#define MAXPARTICLES 10000
   // #define MAXOBJECTS 5000
	//#define MAXOBJECTS 41000
	typedef unsigned char uc;
	
	//define a variable that points towards 'Game' class pointer instance.
	#define m_pGame CGame::s_pgetInst()
	#define m_pInput CInput::s_pgetInst()
	#define m_pAudio CAudio::s_pgetInst()
	
   //#define MAXSAMPLES 100



class Cmain  
{
protected:
	Cmain();

public:
	//static pointer to the Main(this) kill function.
	static Cmain *s_pKillProgram(void);
};

struct Vector2d{
	float x;
	float y;
};

#endif // !defined(AFX_EXAM_H__75CD0E11_20EE_4B88_B690_D01195218237__INCLUDED_)