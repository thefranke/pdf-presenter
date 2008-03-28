// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#include "slide_screen.h"
#include "pdf_presenter.h"
#include "tools.h"

BEGIN_EVENT_TABLE(slide_screen, wxFrame)
    EVT_KEY_DOWN(slide_screen::on_key)
    EVT_CLOSE(slide_screen::on_close)
    EVT_LEFT_DCLICK(slide_screen::on_click)
    EVT_PAINT(slide_screen::on_paint)
    EVT_SIZE(slide_screen::on_resize)
END_EVENT_TABLE()

slide_screen::slide_screen(wxFrame *parent, poppler_document& pdf) : 
wxFrame(parent, -1, wxT(APPNAME)), pdf_(pdf)
{}

void slide_screen::on_resize(wxSizeEvent &e)
{
    refresh();
}

void slide_screen::on_key(wxKeyEvent &e)
{
    // if the usual "fullscreen" keycombo was pressed
    else if (((e.AltDown() || e.CmdDown()) && e.GetKeyCode() == WXK_RETURN) ||
        (e.CmdDown() && e.GetKeyCode() == 'F'))
    {
        ShowFullScreen(!IsFullScreen());
        refresh();
    }
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
    {
        ShowFullScreen(!IsFullScreen());
        refresh();
    }
}

void slide_screen::on_close(wxCloseEvent &e)
{
    // define nothing to prevent the user closing the window manually
}

void slide_screen::on_paint(wxPaintEvent &e)
{
    wxPaintDC dc(this);

    int iw, ih; 

    // paint background black
    GetSize(&iw, &ih);
    dc.SetBrush(wxBrush(*wxBLACK, wxSOLID));
    dc.DrawRectangle(0, 0, iw, ih);

    // center view
    GetClientSize(&iw, &ih);
    iw = (iw - current_slide_.GetWidth())/2;
    ih = (ih - current_slide_.GetHeight())/2;

    if (current_slide_.Ok())
        dc.DrawBitmap(current_slide_, iw, ih, true);
}

void slide_screen::load_slide(size_t slide_nr)
{
    slide_nr_ = slide_nr;

    int iw, ih; 
    GetClientSize(&iw,&ih);
    size_t w=iw, h=ih;

    render_pdf_to(&pdf_, current_slide_, slide_nr, iw, ih);

    // force repaint
    Refresh();
}

void slide_screen::refresh()
{
    load_slide(slide_nr_);
}