#ifndef _Font_H_
#define _Font_H_

#include "Rectangle.h"
#include <string>
#include <Windows.h>
#include <gl.h>

// Utility class used to draw text on the screen using a 
// specific font.
class CFont
{

public:
	// The device context used to create the font.
	static HDC m_hDeviceContext;

public:
	// Default constructor
	CFont();
	// Default destructor
	~CFont();

	// Create the font with a specific height and weight.
	void CreateFont(const std::string& strTypeface, 
					int iFontHeight, 
					int iFontWeight);
	// Draw text on the screen at the specified location with
	// the specified colour.
	void DrawText(const std::string& strText, float fXPos, 
				  float fYPos, GLubyte iRed=255, 
				  GLubyte iGreen=255, GLubyte iBlue=255, GLubyte iAlpha=255);

	// Returns the size of the text. The top and right fields
	// of the returned rectangle are set to 0.
	TRectanglei GetTextSize(const std::string& strText);

	static void SetDeviceContext(HDC hDevContext)
	{ m_hDeviceContext = hDevContext; }

private:

	// The index of the base of the list.
	GLuint m_uiListBase;
	// The win32 font
	HFONT m_hFont;
};

#endif  // _Font_H_