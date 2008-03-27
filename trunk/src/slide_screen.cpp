// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#include "slide_screen.h"
#include "pdf_presenter.h"

BEGIN_EVENT_TABLE(slide_screen, wxFrame)
    EVT_KEY_DOWN(slide_screen::on_key)
    EVT_CLOSE(slide_screen::on_close)
    EVT_LEFT_DCLICK(slide_screen::on_click)
    EVT_PAINT(slide_screen::on_paint)
END_EVENT_TABLE()

slide_screen::slide_screen(wxFrame *parent, poppler_document& pdf) : 
wxFrame(parent, -1, wxT(APPNAME)), pdf_(pdf)
{}

void slide_screen::on_key(wxKeyEvent &e)
{
    // if the usual "fullscreen" keycombo was pressed
    if (((e.AltDown() || e.CmdDown()) && e.GetKeyCode() == WXK_RETURN) ||
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

    if (current_slide_.Ok())
        dc.DrawBitmap(current_slide_, 0, 0, true);
}

void slide_screen::change_slide(size_t slide_nr)
{
    slide_nr_ = slide_nr;

    int iw, ih; 
    GetSize(&iw,&ih);
    size_t w=iw, h=ih;

    raw_image pdf_bmp = pdf_.render(slide_nr, w, h);
    wxImage pdf_image = wxImage(w, h, pdf_bmp);
    current_slide_ = wxBitmap(pdf_image);

    // force repaint
    Refresh();
}

void slide_screen::refresh()
{
    change_slide(slide_nr_);
}