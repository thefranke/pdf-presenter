/*
 * pdf-presenter - Tobias Alexander Franke 2008
 * For copyright and license see LICENSE
 * http://www.tobias-franke.eu
 */
 
#pragma once
#include <wx/wx.h>
#include "pdf_document.h"
#include "pdf_frame.h"

/*!
 * \brief A minimal window that renders a single PDF page as big as possible.
 */
class slide_screen : public wxFrame
{
protected:
    void on_key(wxKeyEvent &e);
    void on_close(wxCloseEvent &e);
    void on_click(wxMouseEvent &e);

    pdf_frame* pdf_;

public:
    slide_screen(wxFrame* parent, pdf_document* pdf);
    void load_slide(size_t slide_nr);

    DECLARE_EVENT_TABLE()
};
