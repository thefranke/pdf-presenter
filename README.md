# pdf-presenter

I work in research, and once in a while I need to give a talk or lecture. Normally I would use Apple's Keynote to show the presentation, but right now I have a Vista-based notebook. So my idea was to simply export the slides to a PDF using my Mac at home or create some slides with Beamer or Google Docs, and then show the presentation using my laptop and some ordinary PDF viewer.

After I tried that for the first time I instantly noticed something very useful is missing: The ability to have one screen that displays the content of the current slide, while the other one - the so called presenter screen - will show the presenter more content, e.g. notes, the next slide and a timer. Since I haven't found one Windows PDF viewer among the billions out there that supports this, PDF Presenter is here to fill this gap.

This is an import from the **original, discontinued [Google Code project] (https://code.google.com/archive/p/pdf-presenter/)**.

# Goals

The following features should preferably be supported in the long run:

 * configurable presenter screen
 * loading notes directly from the PDF
 * transition effects via OpenGL
 * multi-platform support (wxWidgets)
 * a nice GUI
 * small enough to fit with slides on a USB stick
 * if possible, scripted video support outside of PDF files

# Related Projects

* [KeyJnote](http://keyjnote.sourceforge.net/) - A python based one screen presentation tool with pretty slide effects.
* [BOSS Presentation Tool](http://sourceforge.net/projects/bosskeyjnotegui/) - A GUI for KeyJnote, however not yet released.
* [Projector](http://sourceforge.net/projects/pdf-projector/) - Unreleased tool similar to KeyJnote.
* [Haga](http://sourceforge.net/projects/haga/) - An unreleased dual screen PDF presentation tool, apparently for X.
* [PDFBeamer](http://sourceforge.net/projects/pdfbeamer) - An unreleased dual screen PDF presentation tool, apparently for Mac OS X.
* [SplitShow](http://code.google.com/p/splitshow/) - Mac OS X tool for splitview of PDF files with presenter notes.

# Screenshot

![Running pdf-presenter with main screen in the background](http://www.tobias-franke.eu/projects/pdf_presenter/pdf_presenter_f.jpg)
