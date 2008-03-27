// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.

#include <wx/wx.h>
#include "presenter_screen.h"

#include <boost/lexical_cast.hpp>

#include <SecurityHandler.h>
void *StandardSecurityHandler::getAuthData()
{
    return NULL;
}

void CDECL error(int pos, char *msg, ...) {
    /*va_list args;
    char        buf[4096], *p = buf;

    // NB: this can be called before the globalParams object is created
    if (globalParams && globalParams->getErrQuiet()) {
        return;
    }

    if (pos >= 0) {
        p += _snprintf(p, sizeof(buf)-1, "Error (%d): ", pos);
        *p   = '\0';
        OutputDebugString(p);
    } else {
        OutputDebugString("Error: ");
    }

    p = buf;
    va_start(args, msg);
    p += _vsnprintf(p, sizeof(buf) - 1, msg, args);
    while ( p > buf  &&  isspace(p[-1]) )
            *--p = '\0';
    *p++ = '\r';
    *p++ = '\n';
    *p   = '\0';
    OutputDebugString(buf);
    va_end(args);

    if (pos >= 0) {
        p += _snprintf(p, sizeof(buf)-1, "Error (%d): ", pos);
        *p   = '\0';
        OutputDebugString(buf);
        if (gErrFile)
            fprintf(gErrFile, buf);
    } else {
        OutputDebugString("Error: ");
        if (gErrFile)
            fprintf(gErrFile, "Error: ");
    }

    p = buf;
    va_start(args, msg);
    p += _vsnprintf(p, sizeof(buf) - 3, msg, args);
    while ( p > buf  &&  isspace(p[-1]) )
            *--p = '\0';
    *p++ = '\r';
    *p++ = '\n';
    *p   = '\0';
    OutputDebugString(buf);
    if (gErrFile)
        fprintf(gErrFile, buf);
    va_end(args);*/
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
	globalParams = new GlobalParams("");

	//wxMessageBox(wxString(boost::lexical_cast<std::string>(sizeof(jpe)).c_str(), wxConvUTF8));
	
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