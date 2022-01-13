#include "Aplikacja.h"

wxIMPLEMENT_APP(Aplikacja);//generating WinMain 

Aplikacja::Aplikacja()
{

}

Aplikacja::~Aplikacja()
{

}

bool Aplikacja::OnInit()//frame initialization from AppMain 
{
	m_frame1 = new AppMain();
	m_frame1->Show();
	return true;
}