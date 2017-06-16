#include "stdafx.h"

#include "main.h"
#include "resource.h"
//#include <gl.h>
#include <glut.h>
#include <glaux.h>
//#include "Game.h"
#include "TGALoader.h"
#include "Input.h"
#include "Font.h"
#include "GUI.h"
#include <tchar.h>

#define MAX_LOADSTRING 100



UINT g_Texture[100]; //array of texture names


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name


HDC   g_hDC; // General HDC - (handle to device context)
HGLRC g_hRC; // General OpenGL_DC - Our Rendering Context for OpenGL
HINSTANCE g_hInstance;	
HWND g_hWnd;



// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

bool  bSetupPixelFormat(HDC hDC); //added by RM in week 1
//void RenderScene();





int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	//HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_EXAM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	//hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_EXAM);

	//prime message
	PeekMessage(&msg, g_hWnd, NULL, NULL, PM_REMOVE);


	//create Game
	//CGame::s_pgetInst();

//enter main loop
while (msg.message != WM_QUIT)
	{
	if (PeekMessage(&msg, g_hWnd, NULL, NULL, PM_REMOVE))
		{
		TranslateMessage(&msg);//translate +dispatch to event queue
		DispatchMessage(&msg);
		}
		else
		//do rendering here
		{
		// clear screen and depth buffer
		
		//if (CGame::s_pgetInst()->doFrame()==0) PostQuitMessage(WM_QUIT);
		//if (CGame::s_pgetInst()->doFrame2()==0) PostQuitMessage(WM_QUIT);
		m_pGame->doFrame();
		m_pGame->doRender();
		SwapBuffers(g_hDC);// bring backbuffer to foreground
		}
	}


	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_EXAM);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = (LPCTSTR)IDC_EXAM;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   

   hInst = hInstance; // Store instance handle in our global variable
   g_hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,512,300, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   m_pInput->initDInput(hInst, g_hWnd);

   return TRUE;
}


//function to kill game using the escape button.
Cmain * Cmain::s_pKillProgram()
{
		wglMakeCurrent(NULL, NULL); //This frees our rendering memory and sets 
									//everything back to normal
		wglDeleteContext(g_hRC);	// Delete our OpenGL Rendering Context	
		g_hRC=NULL; 
		if (g_hDC) 
		{
		ReleaseDC(g_hWnd, g_hDC);
		g_hDC=NULL;
		}
		g_hWnd=NULL;
		PostQuitMessage(0);

return 0;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		wglMakeCurrent(NULL, NULL); //This frees our rendering memory and sets 
									//everything back to normal
		wglDeleteContext(g_hRC);	// Delete our OpenGL Rendering Context	
		g_hRC=NULL; 

		if (g_hDC) 
		{
		ReleaseDC(g_hWnd, g_hDC);
		g_hDC=NULL;
		}

		g_hWnd=NULL;

		PostQuitMessage(0);
		break;
	case WM_CREATE:

		g_hDC= GetDC(hWnd);
		CFont::SetDeviceContext(g_hDC);

		bSetupPixelFormat(g_hDC); // call our pixel format setup function
		g_hRC = wglCreateContext(g_hDC); // create rendering context 
		wglMakeCurrent(g_hDC, g_hRC); //and make it current
		m_pGame->m_pGUI->instanceFont();


		break;
	case WM_SETFOCUS:
		//puts( "Got the focus" ) ;
	break ;

	case WM_KILLFOCUS:
		m_pGame->m_bActiveWindow = false;
		//puts( "Lost the focus" ) ;
	break;

	case WM_ACTIVATE:

		m_pGame->m_bActiveWindow = true;

	break;

	case WM_SIZE:

		
		

	//	glViewport(0, 0, 720, 480);	// reset the viewport to new dimensions
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,WIDTH,HEIGHT,0);

		glMatrixMode(GL_MODELVIEW);	// set modelview matrix
		glLoadIdentity();		// reset modelview matrix
		glClearColor(0,0,0,0);
		return 0;
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

bool
bSetupPixelFormat(HDC hDC)
{
PIXELFORMATDESCRIPTOR pfd; 
int pixelformat; 
 
pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);// Set the size of the structure
pfd.nVersion = 1;					// Always set this to 1
												// Pass in the appropriate OpenGL flags
pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
pfd.dwLayerMask = PFD_MAIN_PLANE;	
// We want the standard mask (this is ignored anyway)
pfd.iPixelType = PFD_TYPE_RGBA;	// We want RGB and Alpha pixel type
pfd.cColorBits = 16;						
pfd.cDepthBits = 0;// Depthbits is ignored for RGBA, but do it anyway
pfd.cAccumBits = 0;	// No special bitplanes needed
pfd.cStencilBits = 0;	// We desire no stencil bits
 
// get a pixel format that best matches one passed in from the device
    if ( (pixelformat = ChoosePixelFormat(hDC, &pfd)) == FALSE ) 
    { 
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK); 
        return FALSE; 
    } 
 
// This sets the pixel format that we extracted from above
    if (SetPixelFormat(hDC, pixelformat, &pfd) == FALSE) 
    { 
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK); 
        return FALSE; 
    } 
 
    return TRUE;
}
