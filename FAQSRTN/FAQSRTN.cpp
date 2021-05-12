// FAQSRTN.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "FAQSRTN.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CFAQSRTNApp

BEGIN_MESSAGE_MAP(CFAQSRTNApp, CWinApp)
	//{{AFX_MSG_MAP(CFAQSRTNApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFAQSRTNApp construction

CFAQSRTNApp::CFAQSRTNApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFAQSRTNApp object

CFAQSRTNApp theApp;




#define DLLSUCCES	1
#define DLLERROR	2
#define LOGNORMAL	1
#define LOGERROR	2
#define LNORM( txt )	Log(txt, LOGNORMAL, FALSE);
#define LERR( txt )		Log(txt, LOGERROR, FALSE);
#define LJNORM( txt )	Log(txt, LOGNORMAL, TRUE);
#define LJERR( txt )	Log(txt, LOGERROR, TRUE);

HANDLE hLogEvent, hLogReady;
TCHAR log_txt[500];
int log_mode, log_job;
int filenumber = 1;

void Log(LPCTSTR txt, int mode, int job) {
	WaitForSingleObject(hLogReady, INFINITE);
	strcpy(log_txt, txt);
	log_mode = mode;
	log_job = job;
	SetEvent(hLogEvent);
}

extern "C" int PASCAL EXPORT DllGetLog(LPTSTR txt, int *mode, int *job)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	strcpy(txt, log_txt);
	*mode = log_mode;
	*job = log_job;
	return(0);
}

extern "C" int PASCAL EXPORT DllLogReg( HANDLE set_event, HANDLE set_ready )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	hLogEvent = set_event;
	hLogReady = set_ready;
	return(0);
}

extern "C" int PASCAL EXPORT DllWorker ( int argc, char *argv[] )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	TCHAR tmp_str[200];

	LJNORM("VSE FAQS job svar utility")

	if (argc != 1) {
		LJERR("Forkert brug !!!! Korrekt brug: FAQSRTN svar")
		return(DLLERROR);
	}

	sprintf(tmp_str, "%s.%06d", "E:\\FTPROOT\\PC_til_VM\\FAQSRTN", filenumber++);
	CStdioFile tempfile(tmp_str, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
	CString tmpsvar(argv[0]);
	CString faqssvar = "DW" + tmpsvar.Left(2) + tmpsvar.Mid(3) + "O\n";
	tempfile.WriteString(" \n");
	tempfile.WriteString("ICX002\n");
	tempfile.WriteString(faqssvar);
	tempfile.Close();

	return(DLLSUCCES);
}
