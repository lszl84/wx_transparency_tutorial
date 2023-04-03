#include <wx/wx.h>

#include "mybutton.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MyFrame *frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    auto sizer = new wxBoxSizer(wxVERTICAL);

    auto panel = new wxPanel(this);
    panel->SetBackgroundColour("#1E4471");

    auto custom = new MyButton(panel, wxID_ANY, wxDefaultPosition, FromDIP(wxSize(320, 100)));
    custom->text = "SUBSCRIBE";

    auto panelSizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->Add(custom, 1, wxEXPAND | wxALL, FromDIP(50));
    panel->SetSizer(panelSizer);

    sizer->Add(panel, 1, wxEXPAND);

    SetSizerAndFit(sizer);
}
