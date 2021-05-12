// FAQSRTN.h : main header file for the FAQSRTN DLL
//

#if !defined(AFX_FAQSRTN_H__A96E6F0B_2746_11D3_9020_00104BA3042C__INCLUDED_)
#define AFX_FAQSRTN_H__A96E6F0B_2746_11D3_9020_00104BA3042C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFAQSRTNApp
// See FAQSRTN.cpp for the implementation of this class
//

class CFAQSRTNApp : public CWinApp
{
public:
	CFAQSRTNApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFAQSRTNApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CFAQSRTNApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAQSRTN_H__A96E6F0B_2746_11D3_9020_00104BA3042C__INCLUDED_)
