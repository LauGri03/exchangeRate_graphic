#include "wx/wx.h"
#include "wx/combobox.h"
#include <iostream>
#include <set>
#include "main.h"
#include "Frame.h"

IMPLEMENT_APP(CurrencyExchanger)


bool CurrencyExchanger::OnInit()
{
	Frame *frame = new Frame( "Currency Exchanger", wxPoint(50, 50), wxSize(700, 550) );
    frame->Show( true );
	return true;
}