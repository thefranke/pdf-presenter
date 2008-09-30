// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/noncopyable.hpp>

#include <GlobalParams.h>
#include <SplashBitmap.h>
#include <Object.h>
#include <SplashOutputDev.h>
#include <PDFDoc.h>

/*!
 * \brief Standard pointer type for raw bitmaps.
 */
typedef unsigned char* raw_image;

/*!
 * \brief Pure abstract base for a PDF document container
 *
 * This base class ensures that a PDF document can be loaded from a file
 * and rendered into a raw image pointer, which then can be used with
 * any image container.
 */
class pdf_document
{
public:
    /*!
     * \brief Load a PDF document.
     */
    virtual void load(const char* filename) = 0;

    /*!
     * \brief Render a PDF page to a raw bitmap.
     *
     * Renders an image of a PDF page and returns width and height.
     *
     * \param page_nr The page number to be rendered.
     * \param width A variable containing the maximal width the result might have. The actual
     *              width of the final image is written back to this variable.
     * \param height A variable containing the maximal height the result might have. The actual
     *               height of the final image is written back to this variable.
     */
    virtual raw_image render(size_t page_nr, size_t& width, size_t& height) = 0;

    /*!
     * \brief Return the number of pages of the PDF document.
     */
    virtual size_t page_count() const = 0;

    virtual double width_inch(size_t page_nr) const = 0;
    virtual double height_inch(size_t page_nr) const = 0;

    /*!
     * \brief Returns true if pdf document has been read correctly.
     */
    virtual bool good() const = 0;
};

/*!
 * \brief A pdf_document implementation with the poppler library.
 */
class poppler_document : public pdf_document, private boost::noncopyable
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

    double width_inch(size_t page_nr) const
    {
        return doc_->getPageMediaWidth(static_cast<int>(page_nr));
    }

    double height_inch(size_t page_nr) const
    {
        return doc_->getPageMediaHeight(static_cast<int>(page_nr));
    }

    bool good() const
    {
        return (doc_ && output_dev_);
    }

    poppler_document() {}    
    ~poppler_document() { cleanup(); }
};
