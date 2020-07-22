// ScryTheSpire.h : The main header file for the application.

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CScryTheSpireApp:
// See ScryTheSpire.cpp for the implementation of this class
//

class CScryTheSpireApp : public CWinApp
{
public:
	CScryTheSpireApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CScryTheSpireApp theApp;
