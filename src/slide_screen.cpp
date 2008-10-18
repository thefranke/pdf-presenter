// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#include "slide_screen.h"
#include "pdf_presenter.h"
#include "tools.h"

BEGIN_EVENT_TABLE(slide_screen, wxFrame)
    EVT_KEY_DOWN(slide_screen::on_key)
    EVT_CLOSE(slide_screen::on_close)
    EVT_LEFT_DCLICK(slide_screen::on_click)
END_EVENT_TABLE()

slide_screen::slide_screen(wxFrame* parent, pdf_document* pdf) : 
wxFrame(parent, -1, wxT(APPNAME), wxDefaultPosition, wxSize(400,325)), pdf_(new pdf_frame(this, pdf))
{
    SetBackgroundColour(wxColour(0,0,0));
}

void slide_screen::on_key(wxKeyEvent &e)
{
    // if the usual "fullscreen" keycombo was pressed
    if (((e.AltDown() || e.CmdDown()) && e.GetKeyCode() == WXK_RETURN) ||
        (e.CmdDown() && e.GetKeyCode() == 'F'))
        ShowFullScreen(!IsFullScreen());
    else if (e.GetKeyCode() == WXK_ESCAPE)
    {
        ShowFullScreen(false);

        // send stop event to parent
        wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED, wxID_STOP);
        evt.SetEventObject(GetParent());
        GetParent()->GetEventHandler()->ProcessEvent(evt);
    }
}

void slide_screen::on_click(wxMouseEvent &e)
{
    if (e.ButtonDClick())
        ShowFullScreen(!IsFullScreen());
}

void slide_screen::on_close(wxCloseEvent &e)
{
    // define nothing to prevent the user closing the window manually
}

void slide_screen::load_slide(size_t slide_nr)
{
    pdf_->load_slide(slide_nr);
}