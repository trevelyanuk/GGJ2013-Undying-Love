#if !defined(AFX_INPUT_H__9F947E83_2A3B_4B63_8675_83B41506943E__INCLUDED_)
#define AFX_INPUT_H__9F947E83_2A3B_4B63_8675_83B41506943E__INCLUDED_

#if _MSC_VER > 1000						  
#pragma once
#endif // _MSC_VER > 1000

//set directinput version (used in the include files below it, it will enable extra mouse buttons etc).
#define DIRECTINPUT_VERSION 0x0800
//#include "main.h"
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")

class CInput  
{
private:
	//static pointer to the Input(this) instance.
	static CInput * s_pInstance;

protected:
	CInput();

public:
	virtual ~CInput();
	
	// sets up and initializes DirectInput.
	void initDInput(HINSTANCE hInst, HWND g_hWnd);

	// gets the current input data.
	void getMouseInput(void);    
	void getKeyboardInput();

	// the WindowProc function prototype.
	LRESULT CALLBACK WindowProc(HWND g_hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//grabs mouse button pressed.
	bool bMouseButtonDown(char Button);

	//grabs keyboard button pressed (true as long as key still down).

	int igetIfKeyDown(int whichkey_);
	//grabs keyboard button pressed (occurs only when key first pressed).
	int igetIfKeyPressed(int whichkey_); 

	//get mouse x&y input functions.
	double getdMouseX(void);
	double getdMouseY(void);
	short getdMouseZ(void);
	//static pointer function to grab the static pointer of the Game(this) instance.
	static CInput * s_pgetInst();

};

#endif // !defined(AFX_INPUT_H__9F947E83_2A3B_4B63_8675_83B41506943E__INCLUDED_)