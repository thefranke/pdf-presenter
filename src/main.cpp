/*
 * pdf-presenter - Tobias Alexander Franke 2008
 * For copyright and license see LICENSE
 * http://www.tobias-franke.eu
 */

#include <wx/wx.h>
#include <SecurityHandler.h>
#include "presenter_screen.h"

void *StandardSecurityHandler::getAuthData()
{
    return NULL;
}

void CDECL error(int pos, char *msg, ...)
{
}

class pdf_presenter : public wxApp
{
protected:
    presenter_screen *presenter_screen_;

public:
    virtual bool OnInit();
    virtual int OnExit();
};

bool pdf_presenter::OnInit()
{
    // initialize global parameters for poppler... who writes such aweful code?
    globalParams = new GlobalParams();

    if (!globalParams)
        return false;

    globalParams->setErrQuiet(gFalse);

    presenter_screen_ = new presenter_screen();

    if (!presenter_screen_)
    {
        delete globalParams;
        return false;
    }

    presenter_screen_->Show(true);
    SetTopWindow(presenter_screen_);

    return true;
}

int pdf_presenter::OnExit()
{
    delete globalParams;
    return 0;
}

IMPLEMENT_APP(pdf_presenter)
