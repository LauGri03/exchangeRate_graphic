#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/spinctrl.h>
#include <exchanger.h>



class Frame: public wxFrame
{
public:
    Frame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void onFromChange(wxCommandEvent& event);
    void onBtnClick(wxCommandEvent& event);
    void init();
    void setCurrenciesTo();
    wxDECLARE_EVENT_TABLE();
    wxPanel* m_panel1;
	wxSpinCtrlDouble* m_spinCtrlDouble1;
	wxComboBox* m_comboBox1;
	wxComboBox* m_comboBox2;
	wxButton* m_button1;
	wxStaticText* m_staticText1;
	wxPanel* m_panel2;
    wxGrid* m_grid1;
    Exchanger::exchanger ex;
};

enum
{
    ID_FROM = 1001,
    ID_BTN = 1002
};
