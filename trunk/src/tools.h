// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#include <wx/bitmap.h>
#include "pdf_document.h"

void get_screen_dpi(double *w, double *h);
void get_screen_inch(double *w, double *h);
double get_pdf_doc_dpi(double media_width, double media_height, size_t pixels_width, size_t pixels_height);
void render_pdf_to(pdf_document* pdf, wxBitmap& target, size_t slide_nr, size_t w, size_t h);