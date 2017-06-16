#include "stdafx.h"

#include <windows.h>
#include <OBJBASE.H>
#include "Input.h"

//grab external instances.
extern HWND  g_hWnd;
extern HINSTANCE hInst;

LPDIRECTINPUT lpdi;							//pointer to direct input object.
LPDIRECTINPUTDEVICE lpdikey;				//the keyboard device.
LPDIRECTINPUT8 din;							//the pointer to our DirectInput interface.
LPDIRECTINPUTDEVICE8 dinmouse;				//the pointer to the mouse device.
DIMOUSESTATE mousestate;					//the storage for the mouse-information.

//storage for keyboard state
UCHAR keystate[256];
UCHAR oldkeystate[256];
bool keydown[256];

CInput::CInput(){

	if (DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&lpdi, NULL)) //DirectInput8Create(hInst, DIRECTINPUT_VERSION, &lpdi, NULL)!=DI_OK)
	{ 
		// DirectInput not available; take appropriate action.
	} 

	//create keyboard device.
	if(lpdi->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL)!=DI_OK){
		//error
		}

	//set cooperation level.
	if(lpdikey->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)!=DI_OK){
		//error
		}

	//set data format.
	if(lpdikey->SetDataFormat(&c_dfDIKeyboard)!=DI_OK){
		//error
		}

	//acquire the keyboard device.
	if(lpdikey->Acquire()!=DI_OK){
		//error
		}


}

//this is the function that initializes DirectInput.
void CInput::initDInput(HINSTANCE hInst, HWND g_hWnd){

    // create the DirectInput interface
     DirectInput8Create(hInst,							// the handle to the application.
                        DIRECTINPUT_VERSION,			// the compatible version.
                        IID_IDirectInput8,				// the DirectInput interface version.
                        (void**)&din,					// the pointer to the interface.
                        NULL);							// COM stuff, so we'll set it to NULL.

    din->CreateDevice(GUID_SysMouse,
                       &dinmouse,
                       NULL);
    dinmouse->SetDataFormat(&c_dfDIMouse);
	dinmouse->SetCooperativeLevel(g_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
 }

CInput::~CInput(){
	//unaquire keyboard.
	lpdikey->Unacquire();

	//close DirectInput before exiting.
	lpdi->Release();

	//unaquire keyboard.
	dinmouse->Unacquire();

	//close DirectInput before exiting.
	din->Release();    
}






// this is the function that gets the latest input data for the mouse.
 void CInput::getMouseInput(){
	dinmouse->Acquire();
	dinmouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mousestate);
 }


//this function refreshes the CInput class's data on which keys are currently down
//this data is stored in an array called keystate[ ].
void CInput::getKeyboardInput(){

	//copy old keystate array
	int i;
	for (i=0;i<256;++i){
			oldkeystate[i]=keystate[i];
	}

	if (lpdikey->GetDeviceState(256,keystate)!=DI_OK){
		//error
	}

	//now check which keys are now down that weren't down last time.
	for (i=0;i<256;++i){
		if ((keystate[i]>0)&&(oldkeystate[i]==0)){

			//key is now down and it wasn't before
			keydown[i]=1;

		} else keydown[i]=0;
	}
}


//use this function with DirectX character constants
//which are defined in dinput.h  such as DIK_SPACE
//relies on the GetInput( ) function being called first to
//update the data on which keys are currently down
//if this function doesn't seem to work then make sure you
//are calling GetInput( ) first.
int CInput::igetIfKeyDown(int whichkey){

	if ((whichkey>256)|(whichkey<0)) return 0;
	return (int)(keystate[whichkey] & 0x80);
}

//function returns 1 or 0 depending on whether
//specified key has just been pressed.
int	CInput::igetIfKeyPressed(int whichkey){
	if ((whichkey>256)|(whichkey<0)) return 0;
	return (int)(keydown[whichkey]);
}

//returns mouse button press. (0 = leftclick 1=rightclick 2=mousewheel click 3=bottom thumb).
bool CInput::bMouseButtonDown(char Button){
	if(mousestate.rgbButtons[Button] & 0x80){
		return true;
	}
	return false;
} 


//grabs mouse x&y position, for other classes to respond to.
double CInput::getdMouseX(){
	return (double)mousestate.lX;
}
double CInput::getdMouseY(){
	return (double)mousestate.lY;
}

short CInput::getdMouseZ(){
	return mousestate.lZ;
}

//function to get instance of Input class and set a pointer to it, helps to shorten instance creation code. 
//e.g. m_pInput-> ..   instead of   CInput::getInst()-> .. 

CInput * CInput::s_pInstance=0;
CInput * CInput::s_pgetInst()
{
	if (s_pInstance==0){
		s_pInstance=new CInput();
	}
	return s_pInstance;
}

