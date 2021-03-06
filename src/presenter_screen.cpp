/*
 * pdf-presenter - Tobias Alexander Franke 2008
 * For copyright and license see LICENSE
 * http://www.tobias-franke.eu
 */
 
#include "presenter_screen.h"

#include <stdexcept>
#include <wx/aboutdlg.h>
#include <boost/lexical_cast.hpp>

#include "tools.h"
#include "resource.h"

BEGIN_EVENT_TABLE(presenter_screen, wxFrame)
    EVT_MENU(wxID_ANY, presenter_screen::on_toolbar)
    EVT_KEY_DOWN(presenter_screen::on_key)
END_EVENT_TABLE()

presenter_screen::presenter_screen() : wxFrame(NULL, -1, wxT(APPNAME), wxDefaultPosition, wxSize(700, 328))
{
    SetMinSize(wxSize(700, 328));

    // setup toolbar
    toolbar_ = CreateToolBar(wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT);
    toolbar_->AddTool       (wxID_OPEN,         wxT("Open PDF"),            wxBMP(OPEN));
    toolbar_->AddSeparator  ();

    // there seems to be no wxID_START, but wxID_STOP, WTF?!
    // disable both, since no pdf is loaded at startup
    toolbar_->AddCheckTool  (wxID_OK,           wxT("Toggle presentation"), wxBMP(RUN),  wxBMP(RUN_INACT));
    toolbar_->AddCheckTool  (wxID_CONTEXT_HELP, wxT("Toggle notes"),        wxBMP(INFO), wxBMP(INFO_INACT));

    toolbar_->AddSeparator  ();

    toolbar_->AddTool       (wxID_BACKWARD,     wxT("Previous slide"),      wxBMP(PREV), wxBMP(PREV_INACT));
    toolbar_->AddTool       (wxID_FORWARD,      wxT("Next slide"),          wxBMP(NEXT), wxBMP(NEXT_INACT));

    toolbar_->AddSeparator  ();
    toolbar_->AddTool       (wxID_ABOUT,        wxT("About"),               wxBMP(HELP));

    toolbar_->Realize();

    presentation_ = 0;

    wxSize tb_size = toolbar_->GetSize();

    splitter_ = new wxSplitterWindow(this, wxID_ANY, wxPoint(0, 0), GetClientSize());

    // TODO: make this configurable
    notes_space_    = new wxScrolledWindow(splitter_);
    slides_space_   = new wxSplitterWindow(splitter_, wxID_ANY, wxPoint(0, 0), GetClientSize());
    slide_first_    = new pdf_frame(slides_space_, &pdf_);
    slide_second_   = new pdf_frame(slides_space_, &pdf_);

    // HACK: subtract x to set ruler to true center
    slides_space_->SplitVertically(slide_first_, slide_second_, GetSize().GetWidth()/2 - 10);
    slides_space_->SetSashGravity(0.5);

    notes_ = new wxTextCtrl(notes_space_, wxID_ANY, _T("This is the log window.\n"), wxPoint(0,0));

    slides_space_->SetBackgroundColour(wxColour(*wxBLACK));
    notes_space_->SetBackgroundColour(wxColour(*wxWHITE));

    splitter_->SplitHorizontally(slides_space_, notes_space_, -100);
    splitter_->SetSashGravity(0.8);
    splitter_->Unsplit();

    slides_space_->Show();
    notes_space_->Hide();
    reset_controls();
    refresh_title();
}

void presenter_screen::reset_controls(bool active)
{
    toolbar_->EnableTool(wxID_OK, active);
    toolbar_->EnableTool(wxID_CONTEXT_HELP, !notes_data_.empty());
    toolbar_->ToggleTool(wxID_CONTEXT_HELP, false);
    toolbar_->EnableTool(wxID_BACKWARD, false);
    toolbar_->EnableTool(wxID_FORWARD, active);

    if (splitter_->IsSplit())
    {
        splitter_->Unsplit();
        notes_space_->Hide();
    }
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

                std::string notes_file(file->GetPath().char_str());
                notes_file += ".txt";
                notes_data_.read(notes_file.c_str());

                toolbar_->EnableTool(wxID_OK, true);
                toolbar_->EnableTool(wxID_FORWARD, true);

                // updates done, load first slide
                slide_nr_ = 1;
                reset_controls(true);
                refresh();
            }
            catch(std::exception &ex)
            {
                wxMessageBox(wxString(ex.what(), wxConvUTF8), wxT(APPNAME), wxICON_ERROR, this);
            }
        }
    }
    else if (e.GetId() == wxID_OK)
    {
        toggle_presentation();
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
        next_slide();
    }
    else if (e.GetId() == wxID_BACKWARD)
    {
        prev_slide();
    }
    else if (e.GetId() == wxID_CONTEXT_HELP)
    {
        toggle_notes();
    }
}

void presenter_screen::next_slide()
{
    if (slide_nr_ < pdf_.page_count())
    {
        toolbar_->EnableTool(wxID_BACKWARD, true);
        toolbar_->EnableTool(wxID_FORWARD, !(slide_nr_ == pdf_.page_count() - 1));
        ++slide_nr_;
        refresh();
    }
}

void presenter_screen::prev_slide()
{
    if (slide_nr_ > 1)
    {
        toolbar_->EnableTool(wxID_FORWARD, true);
        toolbar_->EnableTool(wxID_BACKWARD, !(slide_nr_ == 2));
        --slide_nr_;
        refresh();
    }
}

void presenter_screen::on_key(wxKeyEvent &e)
{
    if (e.GetKeyCode() == WXK_LEFT)
        prev_slide();
    else if (e.GetKeyCode() == WXK_RIGHT)
        next_slide();
}

void presenter_screen::toggle_presentation()
{
    if (!presentation_)
    {
        presentation_ = new slide_screen(this, &pdf_);
        refresh_slide_screen();
        presentation_->Show(true);
    }
    else
    {
        if(!presentation_->IsBeingDeleted())
            presentation_->Destroy();

        presentation_ = 0;
    }
}

void presenter_screen::toggle_notes()
{
    if (splitter_->IsSplit())
    {
        splitter_->Unsplit();
        notes_space_->Hide();
    }
    else
    {
        splitter_->SplitHorizontally(slides_space_, notes_space_, -100);
        splitter_->SetSashGravity(0.8);

        notes_space_->Show();
        slides_space_->Show();

        notes_->SetSize(notes_space_->GetClientSize());
    }
}

void presenter_screen::load_slide(size_t slide_nr)
{
    slide_first_->load_slide(slide_nr);
    slide_second_->load_slide(slide_nr + 1);

    // force repaint
    Refresh();
}

void presenter_screen::load_note(size_t slide_nr)
{
    if (notes_data_.good())
    {
        wxString wx_note(notes_data_.note(slide_nr).c_str(), wxConvUTF8);
        notes_->Clear();
        notes_->WriteText(wx_note);
    }
}

void presenter_screen::refresh_title()
{
    std::stringstream title;

    title << APPNAME
          << " "
          << VERSION;

    if (pdf_.good())
    {
        title << " - Slide ";
        title << boost::lexical_cast<std::string>(static_cast<unsigned int>(slide_nr_));
        title << "/";
        title << boost::lexical_cast<std::string>(static_cast<unsigned int>(pdf_.page_count()));
    }

    wxString wx_title(title.str().c_str(), wxConvUTF8);

    SetTitle(wx_title);
}

void presenter_screen::refresh()
{
    load_slide(slide_nr_);
    load_note(slide_nr_);
    refresh_title();
    refresh_slide_screen();
}

void presenter_screen::refresh_slide_screen()
{
    // if presentation window is open (i.e. slide screen)
    if (presentation_)
    {
        presentation_->load_slide(slide_nr_);
        presentation_->SetTitle(GetTitle());
    }
}
