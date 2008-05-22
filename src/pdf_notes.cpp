#include "pdf_notes.h"

#include <fstream>
#include <string>

pdf_notes::pdf_notes() : can_be_empty_(false)
{
}

std::string pdf_notes::get_note(size_t page_nr) const
{
    note_map::const_iterator n = notes_.find(page_nr);

    if (n != notes_.end())
        return n->second;
    else
        return "";
}

bool pdf_notes::good() const
{
    return notes_.size() > 0 || can_be_empty_;
}

void pdf_notes::read(const char* file, bool can_be_empty)
{
    can_be_empty_ = can_be_empty;
    notes_.clear();

    std::ifstream stream(file);

    if (!stream.good() && !can_be_empty_)
        throw std::runtime_error("Couldn't open notes.");

    while(!stream.eof())
    {
        size_t page;
        std::string note;

        stream >> page;
        stream >> note;

        notes_.insert(std::make_pair(page, note));
    }
}
