#pragma once
//class which is the beginning of the graphical user interface 
#include "wx/wx.h" //we turn on wxWidgets widgets 

class AppMain : public wxFrame //we inherit from the base class 
{
public:
	AppMain();
	~AppMain();

public:
	int nFieldWidth = 10;//number of squares per width 
	int nFieldHeight = 10;//number of squares per height 
	wxButton **btn = nullptr; //an array of button pointers 
	wxBitmapButton *m_btn1 = nullptr; //button with a picture 
	int* nField = nullptr;//an array of where the mine is 
	bool bFirstClick = true;//the flag of the first press, so as not to die immediately 
	int* mineloc = nullptr;//an array specifying where the M flag is 
	int gameminectr = 0;//a counter of correctly marked flags 

	void OnButtonClicked(wxCommandEvent &evt);//functions called when the button is clicked 
	void Witaj(wxCommandEvent &evt);
	void rclick(wxMouseEvent &evt);
	wxDECLARE_EVENT_TABLE();//declaration of the event table, so that if the event is not custom, it has a type and we can handle it 
};
