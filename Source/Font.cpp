#include "stdafx.h"
#include "Font.h"
#include "Exception.h"

using namespace std;

HDC CFont::m_hDeviceContext = NULL;


CFont::CFont() : m_uiListBase(0)
{
}

CFont::~CFont()
{
	if (m_uiListBase)
		glDeleteLists(m_uiListBase,255);
	DeleteObject(m_hFont);
}
/*
void CFont::SetDeviceContext(HDC hDevContext){ 
	m_hDeviceContext = hDevContext; 
}
*/
void CFont::CreateFont(const std::string& strTypeface, 
						   int iFontHeight,
						   int iFontWeight)
{
	if (!m_hDeviceContext)
	{
		string strError = "Impossible to create the font: ";
		strError += strTypeface;
		throw CException(strError);
		return;
	}

	// Ask openGL to generate a contiguous set of 255 display lists.
	m_uiListBase = glGenLists(255);
	if (m_uiListBase == 0)
	{
		string strError = "Impossible to create the font: ";
		strError += strTypeface;
		throw CException(strError);
		return;
	}

	// Create the Windows font
	//m_hFont = ::CreateFont(h,w,escapement,orientation,weight,italic,underline,strikeout,charset,outprecision,clipprecision,iquality,pitchfamily,facename)
	m_hFont = ::CreateFont(-iFontHeight,
								  0,
								  0,
								  0,
								  iFontWeight,
								  TRUE,
								  FALSE,
								  FALSE,
								  ANSI_CHARSET,
								  OUT_TT_PRECIS,
								  CLIP_DEFAULT_PRECIS,
								  PROOF_QUALITY,
								  FF_DECORATIVE|DEFAULT_PITCH,
								  strTypeface.c_str());
	if (m_hFont == NULL)
	{
		m_uiListBase = 0;
		string strError = "Impossible to create the font: ";
		strError += strTypeface;
		throw CException(strError);
		return;
	}

	// Select the newly create font into the device context (and save the previous
	// one).
	HFONT hOldFont = (HFONT)SelectObject(m_hDeviceContext, m_hFont);
	// Generate the font display list (for the 255 characters) starting
	// at display list m_uiListBase.
	wglUseFontBitmaps(m_hDeviceContext, 0, 255, m_uiListBase);	
	// Set the original font back in the device context
	SelectObject(m_hDeviceContext, hOldFont);	
}

TRectanglei CFont::GetTextSize(const std::string& strText)
{
	SIZE TextSize;
	HFONT hOldFont = (HFONT)SelectObject(m_hDeviceContext, m_hFont);
	// Retrieve the size of the text
	GetTextExtentPoint32(m_hDeviceContext,strText.c_str(),(int)strText.size(),&TextSize);
	SelectObject(m_hDeviceContext, hOldFont);	

	TRectanglei newTextSize(0,TextSize.cy,0,TextSize.cx);
	return newTextSize;
}

void CFont::DrawText(const std::string& strText, 
						 float fXPos, float fYPos,
						 GLubyte iRed, 
						 GLubyte iGreen, 
						 GLubyte iBlue,
						 GLubyte iAlpha)
{
	//if (m_uiListBase == 0)
	//{
		//throw CException("Impossible to diplay the text.");
		//return;
	//}
	//else
	//{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		// Disable 2D texturing
		//glDisable(GL_TEXTURE_2D);
		// Specify the current color
		glColor4ub(iRed, iGreen, iBlue,iAlpha);
		// Specify the position of the text
		glRasterPos2d(fXPos, fYPos);
		// Push the list base value
		//glPushAttrib (GL_LIST_BIT);
			// Set a new list base value. 
			glListBase(m_uiListBase);
			// Call the lists to draw the text.
			glCallLists((GLsizei)strText.size(), GL_UNSIGNED_BYTE, 
						(GLubyte *)strText.c_str());
		//glPopAttrib ();

		// Reenable 2D texturing
		//glEnable(GL_TEXTURE_2D);
		//glDisable(GL_BLEND);
	glPopMatrix();
	//}
}


//Snky
//http://msdn.microsoft.com/en-us/library/dd183499%28v=vs.85%29.aspx