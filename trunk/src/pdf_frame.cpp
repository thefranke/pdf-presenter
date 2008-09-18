// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#include "pdf_frame.h"
#include "tools.h"

BEGIN_EVENT_TABLE(pdf_frame, wxScrolledWindow)
    EVT_SIZE(pdf_frame::on_resize)
    EVT_PAINT(pdf_frame::on_paint)
END_EVENT_TABLE()

pdf_frame::pdf_frame(wxWindow *parent, pdf_document* pdf) : 
wxScrolledWindow(parent), pdf_(pdf)
{
    if (parent)
        SetNextHandler(GetParent()->GetEventHandler());
}

void pdf_frame::on_resize(wxSizeEvent &e)
{
    refresh();
}

void pdf_frame::on_paint(wxPaintEvent &e)
{
    wxPaintDC dc(this);

    int iw, ih;

    // center view
    GetClientSize(&iw, &ih);
    iw = (iw - slide_.GetWidth())/2;
    ih = (ih - slide_.GetHeight())/2;

    if (slide_.Ok())
        dc.DrawBitmap(slide_, iw, ih, true);
}

void pdf_frame::load_slide(size_t slide_nr)
{
    slide_nr_ = slide_nr;

    int iw, ih; 
    GetClientSize(&iw,&ih);
    size_t w=iw, h=ih;

    if (pdf_)
        render_pdf_to(pdf_, slide_, slide_nr, iw, ih);

    // force repaint
    Refresh();
}

void pdf_frame::refresh()
{
    load_slide(slide_nr_);
}