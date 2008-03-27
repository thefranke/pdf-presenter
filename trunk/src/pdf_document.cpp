// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#include "pdf_document.h"

#include <stdexcept>
#include <memory>
#include <cmath>

#include "tools.h"

void poppler_document::load(const char* filename)
{
    // note: don't delete fileNameStr since PDFDoc takes ownership and deletes them itself
    GooString *file_name_str = new GooString(filename);

    cleanup();
	
    doc_ = boost::shared_ptr<PDFDoc>(new PDFDoc(file_name_str, NULL, NULL, NULL));
    if (!doc_->isOk())
		throw std::runtime_error("Couldn't open PDF file");

	if (!output_dev_) 
	{	
		// black background
		SplashColor bg_color;
		bg_color[0] = 0;
		bg_color[1] = 0;
		bg_color[2] = 0;

        output_dev_ = boost::shared_ptr<SplashOutputDev>(new SplashOutputDev(splashModeRGB8, 3, gFalse, bg_color));

        if (output_dev_)
            output_dev_->startDoc(doc_->getXRef());
        else
            throw std::runtime_error("Output dev not initialized");
    }

/*	
	// what's this for?
    _linksForPage = (Links**)malloc(page_count() * sizeof(Links*));
    if (!_linksForPage) return false;
    for (int i=0; i < _pageCount; i++)
        _linksForPage[i] = NULL;
*/
}

size_t poppler_document::page_count() const
{
	return static_cast<size_t>(doc_->getNumPages());
}

float poppler_document::page_size_ratio(size_t page_nr) const
{
	return	static_cast<float>(doc_->getPageCropWidth (static_cast<int>(page_nr))) /
			static_cast<float>(doc_->getPageCropHeight(static_cast<int>(page_nr)));
}

raw_image poppler_document::render(size_t page_nr, size_t& width, size_t& height)
{
	assert(output_dev_);

    const double dpi = get_pdf_doc_dpi(get_width_inch(page_nr), get_height_inch(page_nr), width, height);

    doc_->displayPage(output_dev_.get(), static_cast<int>(page_nr), dpi, dpi, 0, gFalse, gFalse, gFalse);
    SplashBitmap *bmp = output_dev_->getBitmap();

	if (!bmp)
		throw std::runtime_error("Couldn't get bitmap from output device");

    // copy bitmap
    width = bmp->getWidth();
    height = bmp->getHeight();
    const size_t s = bmp->getHeight() * bmp->getRowSize();

    raw_image ret(new unsigned char[s]);
    std::memcpy(ret, bmp->getDataPtr(), s);

	return ret;
}

void poppler_document::cleanup()
{
    /*
    delete output_dev_;
	delete doc_;

    output_dev_ = 0;
    doc_ = 0;
    */
}