// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#pragma once
#include <wx/wx.h>
#include "pdf_document.h"

/*!
 * \brief A minimal window that renders a single PDF page as big as possible.
 */
class slide_screen : public wxFrame
{
protected:
    void on_key(wxKeyEvent &e);
    void on_close(wxCloseEvent &e);
    void on_click(wxMouseEvent &e);
    void on_paint(wxPaintEvent &e);
    void on_resize(wxSizeEvent &e);

    poppler_document pdf_;
    wxBitmap current_slide_;
    size_t slide_nr_;

public:
    slide_screen(wxFrame *parent, poppler_document& pdf);
    void load_slide(size_t slide_nr);
    void refresh();

    DECLARE_EVENT_TABLE()
};
