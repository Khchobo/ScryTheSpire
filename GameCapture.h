// GameCapture.h : The header file for the game screen capture of the application.

#pragma once
class GameCapture
{
public:
	GameCapture();
	~GameCapture();

	HBITMAP CaptureFrame();
private:
	HDC m_hCapC;
	HDC m_hDestC;
	HBITMAP m_hbCapture;
	RECT m_rDimensions;
};

