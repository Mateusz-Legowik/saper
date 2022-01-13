//graphical user interface component, where structure and event handling are defined 
#include "AppMain.h"
#include<iostream>
#include<fstream>
#include <windows.h>
#include <winbase.h>
using namespace std;//the information that we will be using std and we do not need to write it later 

wxBEGIN_EVENT_TABLE(AppMain, wxFrame)//allowing the display of static event handlers for a specified class to begin. Takes the name of the class that creates the events which is AppMain, requires a base class which is wxFrame 
EVT_BUTTON(999, Witaj) //combines an identifier with a function 
wxEND_EVENT_TABLE()


AppMain::AppMain() : wxFrame(nullptr, wxID_ANY, "Gra SAPER by Mateusz Łęgowik", wxPoint(30, 30), wxSize(800, 650)) //creating a frame 
{
	wxBitmap bitmap;
	bitmap.LoadFile("Blue.bmp", wxBITMAP_TYPE_BMP);//pointing to the image path 
	m_btn1 = new wxBitmapButton(this, 999, bitmap, wxPoint(0, 0));
	btn = new wxButton*[nFieldWidth * nFieldHeight]; //an array of a hundred buttons 
	wxGridSizer *grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0); //creating mesh size, spacing set to 0 
	nField = new int[nFieldWidth * nFieldHeight];//dynamic array min  
	mineloc = new int[nFieldWidth * nFieldHeight];//dynamic table of user M flags 

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0;x < nFieldWidth;x++)//loops forming buttons 
	{
		for (int y = 0;y < nFieldHeight;y++)
		{
			btn[y * (nFieldWidth) + x] = new wxButton(this, 10000 + (y * (AppMain::nFieldWidth) + x));
			btn[y * (nFieldWidth) + x]->SetFont(font);
			grid->Add(btn[y * (nFieldWidth) + x], 1, wxEXPAND | wxALL);//adding a button to the size of the grid, the arguments make it take up the entire space of the cell in the grid and expand it if necessary according to the limiting dimensions imposed by the grid ruler 
			btn[y * AppMain::nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AppMain::OnButtonClicked, this);//using the Bind function to connect the event handler with a specific event, the argument is the button being clicked, which connects it to the given function 
			btn[y * AppMain::nFieldWidth + x]->Bind(wxEVT_RIGHT_DOWN, &AppMain::rclick, this);//right button - setting a mine sign 
			nField[y * nFieldWidth + x] = 0;//default value for each location in the minefield table
			mineloc[y * nFieldWidth + x] = 0;//default value for each location in the user M-flag table 
		}
	}

	this->SetSizer(grid);//telling parent window what size to use, in this case it's the size of the grid 
	grid->Layout();//restructuring of the appearance 


}
void AppMain::Witaj(wxCommandEvent &evt) //delete greeting 
{
	delete m_btn1;
	
}
AppMain::~AppMain()
{
	delete[]btn;//removing the board so that there are no leaks 
}

int xyz=0;//a variable that counts clicks 
void AppMain::OnButtonClicked(wxCommandEvent &evt)
{	//each button has an individual ID, so we can get the coordinates in the following way 
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;
	xyz++;
	if (bFirstClick)
	{
		int mines = 30;//quantity min 
		gameminectr = mines;//variable for flags M 

		while (mines)
		{	//random generation of min 
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y)//checking the conditions if it is zero and if it is not the first click
			{
				nField[ry * nFieldWidth + rx] = -1; //setting a mine 
				mines--;
			}
		}
		bFirstClick = false;//changing the value to false so as not to generate a minefield every time 
	}



	if (nField[y * nFieldWidth + x] == -1 && mineloc[y * nFieldWidth + x] != 1)//sprawdzenie czy trafiono na min� lub flag� M
	{
		SYSTEMTIME st;//getting time from SYSTEMTIME C ++ 
		GetSystemTime(&st);
		wxString Foobar;//creating a Foobar string 
		Foobar.Printf(wxT("Przykro mi, trafiłeś na minę przy %d ruchu. Wynik został zapisnay na pulpicie"), xyz);//show 
		wxMessageBox(Foobar);//okienko
		ofstream zapis("C:/Users/Mati/Desktop/wynik.txt", ios_base::app);//writing to the end of the file 
		zapis << "O godzinie: " << st.wHour + 2 << ", minucie: " << st.wMinute <<", sekundzie:" << st.wSecond <<" zgin��e� za ruchem " << xyz << endl;//stream
		zapis.close();//closing the file 
		xyz = 0;//reset the click counter 
		bFirstClick = true;//resetting the first click 

		for (int x = 0;x < nFieldWidth;x++)//resetting the game 
		{
			for (int y = 0;y < nFieldHeight;y++)//going through the entire array 
			{
				nField[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");//resetting the label 
				btn[y * nFieldWidth + x]->Enable(true);//the button is clickable 
				mineloc[y * nFieldWidth + x] = 0;
			}
		}
	}
	else
	{
		int mine_count = 0;

		for (int i = -1; i < 2; i++)//iterating around the field to calculate the mines - which is only 8 cells 
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
				{
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1)//if any one is minus one, we count 
					{
						mine_count++;

					}
				}
			}
		}

		if (mineloc[y * nFieldWidth + x] != 1)
		{
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));//displaying how many mines are in surrounding cells 

			btn[y*nFieldWidth + x]->Enable(false);//disabling the button 
		}

	}

	if (gameminectr == 0)//If all mines have been flagged 
	{
		wxMessageBox("Wygrałeś! Gratuluję");
		bFirstClick = true;

		for (int x = 0;x < nFieldWidth;x++)//resetting the game 
		{
			for (int y = 0;y < nFieldHeight;y++)//going through the entire array 
			{
				nField[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");//resetting the labels 
				btn[y * nFieldWidth + x]->Enable(true);//switching on the button 
				mineloc[y * nFieldWidth + x] = 0;
			}
		}
	}



	evt.Skip();//says that the event was handled and you don't need to check the tree further 

}

void AppMain::rclick(wxMouseEvent &evt)
{//each button has an individual ID, so we can get the coordinates in the following way  
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (mineloc[y * nFieldWidth + x] == 0)//if there is no sign of a mine 
	{
		mineloc[y * nFieldWidth + x] = 1;//in the flags table we mark it as 1 
		btn[y * nFieldWidth + x]->SetLabel("M");//making a sign of a mine 
		//btn[y * nFieldWidth + x] -> Enable(false);
	}
	else//if the mark was there, remove it 
	{
		mineloc[y * nFieldWidth + x] = 0;
		btn[y * nFieldWidth + x]->SetLabel("");//removal of the mine mark 
		//btn[y * nFieldWidth + x] -> Enable(true);
	}
	if (mineloc[y * nFieldWidth + x] == 1 && nField[y * nFieldWidth + x] == -1)//if the mine has been flagged with M 
	{
		gameminectr--; // variable decrementation 
	}
	evt.Skip();//says that the event was handled and you don't need to check the tree further 
}