// pdf-presenter (c) 2008 Tobias Alexander Franke. Please see license.txt.
#include "presenter_screen.h"
#include <stdexcept>
#include <wx/aboutdlg.h>
#include "tools.h"

BEGIN_EVENT_TABLE(presenter_screen, wxFrame)
    EVT_MENU(wxID_ANY, presenter_screen::on_toolbar)
    EVT_PAINT(presenter_screen::on_paint)
    EVT_SIZE(presenter_screen::on_resize)
END_EVENT_TABLE()

presenter_screen::presenter_screen() : wxFrame(NULL, -1, wxT(APPNAME), wxDefaultPosition, wxSize(500, 400))
{
    // setup toolbar
    toolbar_ = CreateToolBar(wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT);
    toolbar_->AddTool   (wxID_OPEN, wxT("Open PDF"),            wxBITMAP(open));
    toolbar_->AddSeparator();

    // there seems to be no wxID_START, but wxID_STOP, WTF?!
    // disable both, since no pdf is loaded at startup
    toolbar_->AddTool   (wxID_OK,   wxT("Run"),                 wxBITMAP(RUN)); 
    toolbar_->AddTool   (wxID_STOP, wxT("Stop"),                wxBITMAP(STOP));
    toolbar_->EnableTool(wxID_OK, false);
    toolbar_->EnableTool(wxID_STOP, false);

    toolbar_->AddSeparator();
    toolbar_->AddTool   (wxID_BACKWARD, wxT("Previous slide"),  wxBITMAP(PREV));
    toolbar_->AddTool   (wxID_FORWARD,  wxT("Next slide"),      wxBITMAP(NEXT));
    toolbar_->EnableTool(wxID_BACKWARD, false);
    toolbar_->EnableTool(wxID_FORWARD, false);

    toolbar_->AddSeparator();
    toolbar_->AddTool   (wxID_ABOUT,    wxT("About"),           wxBITMAP(help));

    toolbar_->Realize();

    presentation_ = 0;
}

void presenter_screen::on_resize(wxSizeEvent &e)
{
    refresh();
}

void presenter_screen::on_paint(wxPaintEvent &e)
{
    wxPaintDC dc(this);
    PrepareDC(dc);

    int iw, ih, sw, sh;
    
    // paint background black
    GetSize(&iw, &ih);
    dc.SetBrush(wxBrush(*wxBLACK, wxSOLID));
    dc.DrawRectangle(0, 0, iw, ih);

    // figure out coordinates to center both slides on the screen
    toolbar_->GetSize(&iw, &ih);
    GetClientSize(&sw, &sh);

    sh = ih + (sh - std::max(current_slide_.GetHeight(), next_slide_.GetHeight()))/2;
    
    if (sh < ih) 
        sh = ih;

    sw -= std::max(current_slide_.GetWidth(), next_slide_.GetWidth())*2;
    sw/=2;

    // make this configurable!!!
    if (current_slide_.Ok())
        dc.DrawBitmap(current_slide_, sw, sh, true);

    if (next_slide_.Ok())
        dc.DrawBitmap(next_slide_, sw+current_slide_.GetWidth(), sh, true);
}

void presenter_screen::on_toolbar(wxCommandEvent &e)
{
    if (e.GetId() == wxID_OPEN)
    {
        wxFileDialog* file = new wxFileDialog(this, wxT("Open a PDF Presentation"), wxEmptyString, 
            wxEmptyString, wxT("PDF File|*.pdf|All files|*.*"));

        if (file->ShowModal() == wxID_OK)
        {
            try
            {
                pdf_.load(file->GetPath().char_str());
                toolbar_->EnableTool(wxID_OK, true);
                toolbar_->EnableTool(wxID_FORWARD, true);

                // updates done, load first slide
                slide_nr_ = 1;
                load_slide(slide_nr_);
            }
            catch(std::exception &ex)
            {
                wxMessageBox(wxString(ex.what(), wxConvUTF8), wxT(APPNAME), wxICON_ERROR, this);
            }
        }
    }
    else if (e.GetId() == wxID_OK)
    {
        presentation_ = new slide_screen(this, pdf_);

        presentation_->load_slide(slide_nr_);
        presentation_->Show(true);

        toolbar_->EnableTool(wxID_STOP, true);
        toolbar_->EnableTool(wxID_OK, false);
    }
    else if (e.GetId() == wxID_STOP)
    {
        toolbar_->EnableTool(wxID_STOP, false);
        toolbar_->EnableTool(wxID_OK, true);

        if(!presentation_->IsBeingDeleted())
            presentation_->Destroy();

        presentation_ = 0;
    }
    else if (e.GetId() == wxID_ABOUT)
    {
        wxAboutDialogInfo info;
        info.SetName(wxT(APPNAME));
        info.SetVersion(wxT(VERSION));
        info.SetDescription(wxT(DESCRIPTION));
        info.SetCopyright(wxT(COPYRIGHT));
        info.SetWebSite(wxT(WEBSITE));

        wxAboutBox(info);
    }
    else if (e.GetId() == wxID_FORWARD)
    {
        toolbar_->EnableTool(wxID_BACKWARD, true);
        toolbar_->EnableTool(wxID_FORWARD, !(slide_nr_ == pdf_.page_count() - 1));
        load_slide(++slide_nr_);
    }
    else if (e.GetId() == wxID_BACKWARD)
    {
        toolbar_->EnableTool(wxID_FORWARD, true);
        toolbar_->EnableTool(wxID_BACKWARD, !(slide_nr_ == 2));
        load_slide(--slide_nr_);
    }
}

void presenter_screen::load_slide(size_t slide_nr)
{
    try 
    {
        // this kind of sucks...
        int iw, ih; 
        GetClientSize(&iw,&ih);
        size_t w=iw, h=ih;

        w/=2;

        render_pdf_to(&pdf_, current_slide_, slide_nr, w, h);

        if (pdf_.page_count() != 0 && slide_nr != pdf_.page_count())
            render_pdf_to(&pdf_, next_slide_, slide_nr+1, w, h);
        else
            next_slide_ = wxBitmap();

        // force repaint
        Refresh();

        // if presentation window is open (i.e. slide screen)
        if (presentation_)
            presentation_->load_slide(slide_nr);

    }
    catch(std::exception &ex)
    {
        wxMessageBox(wxString(ex.what(), wxConvUTF8), wxT(APPNAME), wxICON_ERROR, this);
    }
}

void presenter_screen::refresh()
{
    load_slide(slide_nr_);
}