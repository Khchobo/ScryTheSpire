// ScryTheSpireDlg.cpp : The implementation file.

#include "pch.h"
#include "framework.h"
#include "ScryTheSpire.h"
#include "ScryTheSpireDlg.h"
#include "afxdialogex.h"
#include "atlenc.h"
#include "atlutil.h"
#include "atlimage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScryTheSpireDlg dialog

BEGIN_DHTML_EVENT_MAP(CScryTheSpireDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
END_DHTML_EVENT_MAP()

BEGIN_DISPATCH_MAP(CScryTheSpireDlg, CDHtmlDialog)
	DISP_FUNCTION(CScryTheSpireDlg, "GetState", GetCurrentState, VT_I2, VTS_NONE)
END_DISPATCH_MAP()

CScryTheSpireDlg::CScryTheSpireDlg(CWnd* pParent /*=nullptr*/)
	: CDHtmlDialog(IDD_SCRYTHESPIRE_DIALOG, IDR_HTML_SCRYTHESPIRE_DIALOG, pParent),
	  m_appState(AS_WAITING_FOR_WINDOW)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScryTheSpireDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScryTheSpireDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CScryTheSpireDlg message handlers

BOOL CScryTheSpireDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Setup external dispatch

	EnableAutomation();
	LPDISPATCH pDisp = GetIDispatch(FALSE);
	SetExternalDispatch(pDisp);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScryTheSpireDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScryTheSpireDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

void CScryTheSpireDlg::OnOK()
{
	LoadAndDisplayImage(_T(".\\png\\LimitBreak.png"), _T("IMG_1"));
	LoadAndDisplayImage(_T("D:\\Users\\rishi\\Documents\\Programming\\ScryTheSpire\\png\\LimitBreak.png"), _T("IMG_2"));
	LoadAndDisplayImage(_T("D:\\Users\\rishi\\Documents\\Programming\\ScryTheSpire\\png\\LimitBreak.png"), _T("IMG_3"));
}

void CScryTheSpireDlg::LoadAndDisplayImage(CString fileName, CString elementId)
{
	// Find and normalize dimensions of image
	int width = 0, height = 0;
	{
		CImage img;
		img.Load(fileName);

		width = img.GetWidth();
		height = img.GetHeight();

		if (width > height)
		{
			height = MulDiv(250, height, width);
			width = 250;
		}
		else
		{
			width = MulDiv(250, width, height);
			height = 250;
		}
	}


	HANDLE hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (INVALID_HANDLE_VALUE != hFile)
	{
		DWORD size = GetFileSize(hFile, NULL);
		LPBYTE buffer = (LPBYTE)LocalAlloc(LPTR, size);

		DWORD read = 0;
		if (ReadFile(hFile, buffer, size, &read, NULL) && read)
		{
			int base64Len = size * 14 / 10;
			LPSTR base64Str = (LPSTR)LocalAlloc(LPTR, base64Len);
			if (Base64Encode(buffer, size, base64Str, &base64Len))
			{
				TRACE("%s\n", base64Str);
				LPSTR base64Esc = (LPSTR)LocalAlloc(LPTR, size * 2);

				DWORD escLen;
				if (AtlEscapeUrl(base64Str, base64Esc, &escLen, size * 2))
				{
					TRACE("Esc:\n%s\n", base64Esc);

					CString param;
					param.Format(TEXT("data:image/%s;base64,%s"), _T("png"), CString(base64Esc));

					CComPtr<IHTMLElement> pImg;
					HRESULT hr = GetElement(elementId, &pImg);
					if (SUCCEEDED(hr))
					{
						CString outerHtml;
						outerHtml.Format(TEXT("<IMG ID=\"%s\" SRC=\"%s\" ALT=\"%s\" STYLE=\"width:%d;height%d\"/>"), elementId, param, param, width, height);
						
						hr = pImg->put_outerHTML(CComBSTR(outerHtml));
						ASSERT(SUCCEEDED(hr));
					}
				}
				LocalFree(base64Esc);
			}
			LocalFree(base64Str);
		}
		CloseHandle(hFile);
		LocalFree(buffer);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScryTheSpireDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CScryTheSpireDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CScryTheSpireDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	CDHtmlDialog::OnCancel();
	return S_OK;
}

// Get current app state
AppState CScryTheSpireDlg::GetCurrentState()
{
	return m_appState;
}
