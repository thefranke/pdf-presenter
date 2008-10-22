// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#include <wx/bitmap.h>
#include "pdf_document.h"

/*!
 * \brief Fetch the screen DPI for width and height.
 */
void get_screen_dpi(double *w, double *h);

/*!
 * \brief Fetch the screen size in inch for width and height.
 */
void get_screen_inch(double *w, double *h);

/*!
 * \brief Calculate and return the required DPI value to render an image of a PDF page with a certain size in pixels.
 */
double get_pdf_doc_dpi(double media_width, double media_height, size_t pixels_width, size_t pixels_height);

/*!
 * \brief Shortcut to render a PDF page with a given maximum height/width into a wxBitmap.
 */
void render_pdf_to(pdf_document* pdf, wxBitmap& target, size_t slide_nr, size_t w, size_t h);

