#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/spinctrl.h>
#include "frame.h"

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_COMBOBOX(ID_FROM, Frame::onFromChange) //Definition of basic event for good program execution (Convertion button and definition of possible destination for a given source)
	EVT_BUTTON(ID_BTN, Frame::onBtnClick)
wxEND_EVENT_TABLE()

//Frame generated with wxformbuilder https://github.com/wxFormBuilder/wxFormBuilder
Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size,
                wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX)
{
this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );


	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	m_spinCtrlDouble1 = new wxSpinCtrlDouble( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), wxSP_ARROW_KEYS, 0, 1000, 0, 0.10 );
	m_spinCtrlDouble1->SetDigits( 2 );
	bSizer3->Add( m_spinCtrlDouble1, 0, wxALL, 5 );

	m_comboBox1 = new wxComboBox( m_panel1, ID_FROM, wxT("Combo!"), wxDefaultPosition, wxSize( 200,-1 ), 0, NULL, 0 );
	bSizer3->Add( m_comboBox1, 0, wxALL, 5 );

	m_comboBox2 = new wxComboBox( m_panel1, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxSize( 200,-1 ), 0, NULL, 0 );
	bSizer3->Add( m_comboBox2, 0, wxALL, 5 );

	m_button1 = new wxButton( m_panel1, ID_BTN, wxT("Convert"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button1, 0, wxALL, 5 );


	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );


	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText1 = new wxStaticText( m_panel1, wxID_ANY, wxT("0.00"), wxDefaultPosition, wxSize( 500,50 ), wxALIGN_CENTER_HORIZONTAL );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( 28, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	bSizer4->Add( m_staticText1, 0, wxALL, 5 );


	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer2->Add( bSizer4, 1, wxEXPAND, 5 );


	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );

	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_grid1 = new wxGrid( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_grid1->CreateGrid( 25, 2 );
	m_grid1->EnableEditing( false );
	m_grid1->EnableGridLines( true );
	m_grid1->EnableDragGridSize( false );
	m_grid1->SetMargins( 0, 0 );
	m_grid1->AutoSize();

	// Columns
	m_grid1->SetColSize( 0, 295 );
	m_grid1->SetColSize( 1, 295 );
	m_grid1->EnableDragColMove( false );
	m_grid1->EnableDragColSize( true );
	m_grid1->SetColLabelValue( 0, wxT("DATE") );
	m_grid1->SetColLabelValue( 1, wxT("VALUE") );
	m_grid1->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_grid1->AutoSizeRows();
	m_grid1->EnableDragRowSize( true );
	m_grid1->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance
	m_grid1->SetLabelFont( wxFont( 15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	// Cell Defaults
	m_grid1->SetDefaultCellAlignment( wxALIGN_CENTER, wxALIGN_CENTER );
	bSizer5->Add( m_grid1, 0, wxALL | wxEXPAND, 5 );


	m_panel2->SetSizer( bSizer5 );
	m_panel2->Layout();
	bSizer5->Fit( m_panel2 );
	bSizer1->Add( m_panel2, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	init();
}

//Set possible destination currencies at source changement event
void Frame::onFromChange(wxCommandEvent& event){
	setCurrenciesTo();
}

//Historic of values in grid + most recent value in label
void Frame::onBtnClick(wxCommandEvent& event){
	double value = m_spinCtrlDouble1->GetValue();
	std::string fromCurrency = m_comboBox1->GetStringSelection().ToStdString();
	std::string toCurrency = m_comboBox2->GetStringSelection().ToStdString();

	std::vector<std::pair<std::string, long double>> rates = ex.convert(fromCurrency,toCurrency,value);
	m_staticText1->SetLabel(std::to_string(rates[rates.size() - 1].second));
	m_grid1->ClearGrid();
		for(int i = 0; i <= rates.size() - 1; i++){
			m_grid1->SetCellValue(rates.size() - (i + 1), 0, rates[i].first); //Most recent historical value first (Top of the grid)
			m_grid1->SetCellValue(rates.size() - (i +1), 1, std::to_string(rates[i].second));
		}
	

	
}

void Frame::setCurrenciesTo(){
	 std::string fromSelected = m_comboBox1->GetStringSelection().ToStdString();
	 std::set<std::string> currenciesTo = ex.getPossiblesCurrenciesTo(fromSelected);
	 m_comboBox2->Clear();
	 for(auto c : currenciesTo){
		 m_comboBox2->AppendString(c);
	 }
	 m_comboBox2->Select(0);
}

void Frame::init(){
	std::set<std::string> currenciesFrom  = ex.getAllCurrencies();
	for(auto c : currenciesFrom){
		m_comboBox1->AppendString(c);
	}
	m_comboBox1->Select(0);
	setCurrenciesTo();
}