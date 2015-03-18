# Rationale #

I work in research, and once in a while I need to give a talk or lecture. Normally I would use Apple's Keynote to show the presentation, but right now I have a Vista-based notebook. So my idea was to simply export the slides to a PDF using my Mac at home or create some slides with [Beamer](http://latex-beamer.sourceforge.net/) or [Google Docs](http://docs.google.com), and then show the presentation using my laptop and some ordinary PDF viewer.

After I tried that for the first time I instantly noticed something very useful is missing: The ability to have one screen that displays the content of the current slide, while the other one - the so called _presenter screen_ - will show the presenter more content, e.g. notes, the next slide and a timer. Since I haven't found one Windows PDF viewer among the billions out there that supports this, **PDF Presenter** is here to fill this gap.

# Goals #

The following features should preferably be supported in the long run:

  * configurable presenter screen
  * loading notes directly from the PDF
  * transition effects via OpenGL
  * multi-platform support (wxWidgets)
  * a nice GUI
  * small enough to fit with slides on a USB stick
  * if possible, scripted video support outside of PDF files

# News #

**12/15/2008** - The build directory now contains the first version of a CMake environment, which will sooner or later replace all current build files.

**11/04/2008** - PDF Presenter needs an icon! If you are artistically inclined, feel free to contribute.

**10/23/2008** - I was able to build the first version of PDF-Presenter on Ubuntu Hardy. If you want to try it out, check out the source and use the minimal build script in builds/linux/.

**10/21/2008** - The first beta version is available for download. Bug reports and suggestions are welcome! And don't forget to look at BasicUsage.

**09/17/2008** - Still looking for a bug that's killing my render context. If this is stable, I'll put some binaries (Microsoft Windows and hopefully Mac OS X 10.4 upwards) online.

**09/03/2008** - The project was inactive for a whole while, but I'm back on it.

**03/29/2008** - PDF presenter is in first usable version. The slide rendering finally matches the DPI of the slides to the size of the screen, but has some troubles after loading two or three documents in a row with the fonts. I've uploaded a build environment for Visual Studio 2008 Express Edition and hope to get an XCode version running soon.

**03/27/2008** - Initial checkin of some source code. This first version needs a slight update for a wxWidgets definition and yet has no build files. Also, I'm not sure about the license issues with the icons used on some of the buttons, but I hope to sort that out in a few days. Currently, PDF Presenter displays two small preview images (current and next slide) and opens another window which can be maximized on a secondary screen showing just the current slide. Rather slow right now, but it works to actually present something ;-)

# Related Projects #

[KeyJnote](http://keyjnote.sourceforge.net/) - A python based one screen presentation tool with pretty slide effects.

[BOSS Presentation Tool](https://sourceforge.net/projects/bosskeyjnotegui/) - A GUI for KeyJnote, however not yet released.

[Projector](https://sourceforge.net/projects/pdf-projector/) - Unreleased tool similar to KeyJnote.

[Haga](https://sourceforge.net/projects/haga/) - An unreleased dual screen PDF presentation tool, apparently for X.

[PDFBeamer](https://sourceforge.net/projects/pdfbeamer) - An unreleased dual screen PDF presentation tool, apparently for Mac OS X.

[SplitShow](http://code.google.com/p/splitshow/) - Mac OS X tool for splitview of PDF files with presenter notes.

# Screenshots #

![http://pdf-presenter.googlecode.com/files/pdf_presenter.jpg](http://pdf-presenter.googlecode.com/files/pdf_presenter.jpg)

![http://pdf-presenter.googlecode.com/files/pdf_presenter_scr.jpg](http://pdf-presenter.googlecode.com/files/pdf_presenter_scr.jpg)

