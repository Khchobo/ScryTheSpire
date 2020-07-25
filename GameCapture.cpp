#include "pch.h"

#include "GameCapture.h"

GameCapture::GameCapture()
{
	HWND hwnd = GetForegroundWindow();
	m_hCapC = GetDC(hwnd);
	m_hDestC = CreateCompatibleDC(m_hCapC);

	if (!GetClientRect(hwnd, &m_rDimensions))
	{
		throw "Could not get Window dimensions!";
	}
	
	int width = m_rDimensions.right - m_rDimensions.left;
    int height = m_rDimensions.bottom - m_rDimensions.top;

	m_hbCapture = CreateCompatibleBitmap(m_hCapC, width, height);

	if (!SelectObject(m_hDestC, m_hbCapture))
	{
		throw "Could not select bitmap handle into the destination device context!";
	}
}

GameCapture::~GameCapture()
{
	ReleaseDC(NULL, m_hCapC);
	DeleteObject(m_hbCapture);
	DeleteDC(m_hDestC);
}

HBITMAP GameCapture::CaptureFrame()
{
	int width = m_rDimensions.right - m_rDimensions.left;
	int height = m_rDimensions.bottom - m_rDimensions.top;

	if (!BitBlt(m_hDestC, 0, 0, width, height, m_hCapC, m_rDimensions.left, m_rDimensions.top, SRCCOPY))
	{
		throw "Bit block transfer failed!";
	}
	
	return m_hbCapture;
}