/*
 * pdf-presenter - Tobias Alexander Franke 2008
 * For copyright and license see LICENSE
 * http://www.tobias-franke.eu
 */
 
#include "tools.h"

#include <wx/gdicmn.h>
#include <wx/image.h>

void get_screen_inch(double *w, double *h)
{
    // figure out dpi of screen (1 inch = 25.4 milimeter)
    int mm_w, mm_h;
    ::wxDisplaySizeMM(&mm_w, &mm_h);
    *w = static_cast<double>(mm_w) / 25.4;
    *h = static_cast<double>(mm_h) / 25.4;
}

void get_screen_dpi(double *w, double *h)
{
    // figure out dpi of screen (1 inch = 25.4 milimeter)
    double inch_w, inch_h;
    get_screen_inch(&inch_w, &inch_h);

    int pix_w, pix_h;
    ::wxDisplaySize(&pix_w, &pix_h);
    *w = static_cast<double>(pix_w)/inch_w;
    *h = static_cast<double>(pix_h)/inch_h;
}

double get_pdf_doc_dpi(double media_width, double media_height, size_t pixels_width, size_t pixels_height)
{
    const double PDF_FILE_DPI = 72.0;

    // page size
    const double doc_inch_w = media_width/PDF_FILE_DPI;
    const double doc_inch_h = media_height/PDF_FILE_DPI;

    // screen dpi
    double dpi_w, dpi_h;
    get_screen_dpi(&dpi_w, &dpi_h);

    const double w = PDF_FILE_DPI * (static_cast<double>(pixels_width)/(doc_inch_w*dpi_w));
    const double h = PDF_FILE_DPI * (static_cast<double>(pixels_height)/(doc_inch_h*dpi_h));

    if (w < h)
        return w;
    else
        return h;
}

void render_pdf_to(pdf_document* pdf, wxBitmap& target, size_t slide_nr, size_t w, size_t h)
{
    if (pdf->good() && slide_nr <= pdf->page_count())
    {
        raw_image raw = pdf->render(slide_nr, w, h);
        target = wxBitmap(wxImage(static_cast<int>(w), static_cast<int>(h), raw));
    }
    else
        target = wxBitmap();
}
