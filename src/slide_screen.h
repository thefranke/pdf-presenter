// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#pragma once
#include <wx/wx.h>
#include "pdf_document.h"

class slide_screen : public wxFrame
{
protected:
    void on_key(wxKeyEvent &e);
    void on_close(wxCloseEvent &e);
    void on_click(wxMouseEvent &e);
    void on_paint(wxPaintEvent &e);

    poppler_document pdf_;
    wxBitmap current_slide_;

public:
    slide_screen(wxFrame *parent, poppler_document& pdf);
    void change_slide(size_t slide_nr);

    DECLARE_EVENT_TABLE()
};
