// CLEANUP.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "CLEANUP.h"

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
// CCLEANUPApp

BEGIN_MESSAGE_MAP(CCLEANUPApp, CWinApp)
	//{{AFX_MSG_MAP(CCLEANUPApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCLEANUPApp construction

CCLEANUPApp::CCLEANUPApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCLEANUPApp object

CCLEANUPApp theApp;

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


int CleanUp(LPCTSTR cleanpath);

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

	LJNORM("Starter CLEANUP arkivering/sletning")

	if (argc != 2 && argc != 1) {
		LJERR("Forkert brug !!!! Korrekt brug: CLEANUP pattern <trigger>")
		return(DLLERROR);
	}

	Sleep(5000);
	if (argc == 2) {
		TRY
		{
			CFile::Remove(argv[1]);
		}
		CATCH( CFileException, e )
		{
			LJERR("FEJL: kunne ikke slette trigger-fil")
			return(DLLERROR);
		}
		END_CATCH
	}
	
	return(CleanUp(argv[0]));
}

TCHAR logstr[1024];

class FileName {
public:
	CString path;
	CString extension;
	FileName(LPCTSTR set_path, LPCTSTR set_extension);
	FileName *next;
};

FileName::FileName(LPCTSTR set_path, LPCTSTR set_extension) {
	path = set_path;
	extension = set_extension;
	next = NULL;
}

class Files {
public:
	CString name;
	FileName *files;
	Files(LPCTSTR set_name, LPCTSTR set_path, LPCTSTR set_extension);
	void Insert(LPCTSTR set_path, LPCTSTR set_extension);
	Files *next;
};

Files::Files(LPCTSTR set_name, LPCTSTR set_path, LPCTSTR set_extension) {
	name = set_name;
	files = new FileName(set_path, set_extension);
	next = NULL;
}

void Files::Insert(LPCTSTR set_path, LPCTSTR set_extension) {
	FileName *current, **prev;
	prev = &files;
	for (current = files; current != NULL; prev = &current->next, current = current->next) {
		if (current->extension < set_extension) {
			*prev = new FileName(set_path, set_extension);
			(*prev)->next = current;
			break;
		}
		if (current->next == NULL) {
			current->next = new FileName(set_path, set_extension);
			break;
		}
	}
}

int CleanUp(LPCTSTR cleanpath) {
	int retcode;
	Files *datafiles, *current;
	datafiles = current = NULL;

	CString searchpath;
	searchpath = cleanpath;
	searchpath += "\\*.*";

	CString filename, extension;

	CFileFind filefind;
	if (filefind.FindFile(searchpath)) {
		do {
			retcode = filefind.FindNextFile();
			filename = filefind.GetFileTitle();
			extension = filefind.GetFileName().Mid(filefind.GetFileTitle().GetLength());
			current = datafiles;
			if (filename == filefind.GetFileName());
			else if (extension.Left(2) < ".0" || extension.Left(2) > ".9");
			else if (current == NULL) {
				datafiles = new Files(filename, filefind.GetFilePath(), extension);
			} else {
				while (current != NULL) {
					if (filename == current->name) {
						current->Insert(filefind.GetFilePath(), extension);
						break;
					}	
					if	(current->next == NULL) {
						current->next = new Files(filename, filefind.GetFilePath(), extension);
						break;
					}
					current = current->next;
				}
			}
		} while (retcode != 0);
	}
	filefind.Close();

	LJNORM("CLEANUP arkivering/sletning starter")
	int archived = 0, deleted = 0, errorcode = DLLSUCCES;

	current = datafiles;
	while (current != NULL) {
		FileName *dataelm, *prevdataelm;
		dataelm = current->files;
		int version = 0;
		while (dataelm != NULL) {
			version++;
			if (version > 3) {
				deleted++;
				TRY
				{
					CFile::Remove((LPCTSTR) dataelm->path);
				}
				CATCH( CFileException, e )
				{
					LJERR("FEJL: kunne ikke slette data-fil")
					errorcode = DLLERROR;
				}
				END_CATCH
			} else archived++;
			prevdataelm = dataelm;
			dataelm = dataelm->next;
			delete prevdataelm;
		}
		datafiles = current;
		current = current->next;
		delete datafiles;
	}

	sprintf(logstr, "CLEANUP> %d filer arkiveret, %d filer slettet", archived, deleted);
	LJNORM(logstr)

	return (errorcode);
}
