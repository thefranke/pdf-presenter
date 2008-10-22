#pragma once
#include <wx/wx.h>
#include "pdf_document.h"

/*!
 * \brief A frame containig one maximized PDF slide.
 */
class pdf_frame : public wxScrolledWindow
{
protected:
    void on_paint(wxPaintEvent &e);
    void on_resize(wxSizeEvent &e);

    pdf_document* pdf_;
    wxBitmap slide_;
    size_t slide_nr_;

public:
    pdf_frame(wxWindow *parent, pdf_document* pdf);
    void load_slide(size_t slide_nr);
    void refresh();

    DECLARE_EVENT_TABLE()
};

