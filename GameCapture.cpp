#include "pch.h"

#include "GameCapture.h"

GameCapture::GameCapture()
{
	m_hCapC = GetDC(NULL);
	m_hDestC = CreateCompatibleDC(m_hCapC);

	m_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	m_width = GetSystemMetrics(SM_CXVIRTUALSCREEN);

	m_hbCapture = CreateCompatibleBitmap(m_hCapC, m_width, m_height);
	SelectObject(m_hDestC, m_hbCapture);
}

GameCapture::~GameCapture()
{
	ReleaseDC(NULL, m_hCapC);
	DeleteObject(m_hbCapture);
	DeleteDC(m_hDestC);
}

HBITMAP GameCapture::CaptureFrame()
{
	BitBlt(m_hDestC, 0, 0, m_width, m_height, m_hCapC, 0, 0, SRCCOPY);
	
	return m_hbCapture;
}