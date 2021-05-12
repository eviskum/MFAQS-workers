// CLEANUP.h : main header file for the CLEANUP DLL
//

#if !defined(AFX_CLEANUP_H__DF6F4C30_B4D4_4C7A_9476_E59216A3F7A1__INCLUDED_)
#define AFX_CLEANUP_H__DF6F4C30_B4D4_4C7A_9476_E59216A3F7A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCLEANUPApp
// See CLEANUP.cpp for the implementation of this class
//

class CCLEANUPApp : public CWinApp
{
public:
	CCLEANUPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCLEANUPApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCLEANUPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLEANUP_H__DF6F4C30_B4D4_4C7A_9476_E59216A3F7A1__INCLUDED_)
