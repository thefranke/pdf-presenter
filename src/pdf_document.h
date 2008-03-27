// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

#include <GlobalParams.h>
#include <SplashBitmap.h>
#include <Object.h> /* must be included before SplashOutputDev.h because of sloppiness in SplashOutputDev.h */
#include <SplashOutputDev.h>
#include <PDFDoc.h>

//typedef boost::shared_array<unsigned char> raw_image;
typedef unsigned char* raw_image;

class pdf_document
{
public:
    virtual void load(const char* filename) = 0;
    virtual raw_image render(size_t page_nr, size_t& width, size_t& height) = 0;
    virtual size_t page_count() const = 0;
	virtual float page_size_ratio(size_t page_nr) const = 0;
    virtual void cleanup() = 0;

    virtual double get_width_inch(size_t page_nr) const = 0;
    virtual double get_height_inch(size_t page_nr) const = 0;
};

class poppler_document : public pdf_document
{
protected:
    boost::shared_ptr<PDFDoc> doc_;
    boost::shared_ptr<SplashOutputDev> output_dev_;

public:
    void load(const char* filename);
    raw_image render(size_t page_nr, size_t& width, size_t& height);
    size_t page_count() const;
	float page_size_ratio(size_t page_nr) const;
    void cleanup();

    double get_width_inch(size_t page_nr) const
    {
        return doc_->getPageMediaWidth(static_cast<int>(page_nr));
    }

    double get_height_inch(size_t page_nr) const
    {
        return doc_->getPageMediaHeight(static_cast<int>(page_nr));
    }
	
	poppler_document() {}    
    ~poppler_document() { cleanup(); }
};

/*
class fitz_document : public pdf_document
{
public:
    void load(const char* filename);
    raw_image render(size_t page_nr);
    size_t page_count();
};
*/
