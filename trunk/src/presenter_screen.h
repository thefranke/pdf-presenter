// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#pragma once
#include <wx/wx.h>
#include <wx/splitter.h>
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
 * to be redefined to wxjpeg_boolean, otherwise the boolean sizes
 * do not match each other.
 */
class presenter_screen : public wxFrame
{
protected:
    wxSplitterWindow *splitter_, *slides_space_;
    wxScrolledWindow *notes_space_;

    wxToolBar *toolbar_;
    wxTextCtrl *notes_;

    slide_screen *presentation_;
    pdf_frame *slide_first_;
    pdf_frame *slide_second_;
    poppler_document pdf_;

    size_t slide_nr_;

    void load_slide(size_t slide_nr);
    void refresh();
    void refresh_title();
    void refresh_slide_screen();
    void reset_controls(bool active = false);
    void toggle_notes();
    void toggle_presentation();

    void on_toolbar(wxCommandEvent &e);
    void on_paint(wxPaintEvent &e);
    void on_resize(wxSizeEvent &e);
public:
    presenter_screen();

    DECLARE_EVENT_TABLE()
};