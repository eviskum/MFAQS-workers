// LocalJob.h : main header file for the LOCALJOB DLL
//

#if !defined(AFX_LOCALJOB_H__E54D59EB_5B2F_11D3_9790_00104BA3042C__INCLUDED_)
#define AFX_LOCALJOB_H__E54D59EB_5B2F_11D3_9790_00104BA3042C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLocalJobApp
// See LocalJob.cpp for the implementation of this class
//

class CLocalJobApp : public CWinApp
{
public:
	CLocalJobApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalJobApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CLocalJobApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALJOB_H__E54D59EB_5B2F_11D3_9790_00104BA3042C__INCLUDED_)
