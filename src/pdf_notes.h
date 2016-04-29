/*
 * pdf-presenter - Tobias Alexander Franke 2008
 * For copyright and license see LICENSE
 * http://www.tobias-franke.eu
 */

#pragma once
#include <map>
#include <string>

class pdf_notes
{
protected:
    typedef std::map<size_t, std::string> note_map;
    note_map notes_;
    bool can_be_empty_;

public:
    pdf_notes();
    void read(const char* file, bool can_be_empty = true);
    bool good() const;
    bool empty() const;
    std::string note(size_t page_nr) const;
};
