// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#pragma once
#include <wx/wx.h>
#include "slide_screen.h"
#include "pdf_presenter.h"
#include "pdf_document.h"
#include <jpeglib.h>

/*!
 * \brief The presenter screen.
 *
 * \par JPEG lib, wxWidgets and Poppler
 *
 * To get this combo working in harmony on windows, link Poppler
 * against the modified JPEG lib from wxWidgets. After doing so
 * DCTStream.cc's str_fill_input_buffer function return type needs 
 * to be redefined to wxjpeg_boolean.
 */
class presenter_screen : public wxFrame
{
protected:
    wxToolBar *toolbar_;
    slide_screen *presentation_;
	poppler_document pdf_;
    
    size_t slide_nr_;
    void load_slide(size_t slide_nr);

    void on_toolbar(wxCommandEvent &e);
    void on_paint(wxPaintEvent &e);

    wxBitmap current_slide_, next_slide_;
public:
    presenter_screen();

    DECLARE_EVENT_TABLE()
};
