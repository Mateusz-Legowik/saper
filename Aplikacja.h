#pragma once
//the class that is the louncher of the application 
#include "wx/wx.h"
#include "AppMain.h"//inclusion of wxWidgets widgets 



class Aplikacja : public wxApp //inheritance from the base class 
{
public:
	Aplikacja();
	~Aplikacja();

private:
	AppMain* m_frame1 = nullptr;

public:
	virtual bool OnInit(); //function implementation 
};