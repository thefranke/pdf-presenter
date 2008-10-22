#ifndef WIN32

#define wxBMP(x) wxBitmap(wxT(x))

#define NEXT                            "../share/pdf-presenter/control_end_blue.bmp"
#define NEXT_INACT                      "../share/pdf-presenter/control_end.bmp"
#define PREV                            "../share/pdf-presenter/control_start_blue.bmp"
#define PREV_INACT                      "../share/pdf-presenter/control_start.bmp"
#define RUN                             "../share/pdf-presenter/control_play_blue.bmp"
#define RUN_INACT                       "../share/pdf-presenter/control_play.bmp"
#define OPEN                            "../share/pdf-presenter/control_eject_blue.bmp"
#define HELP                            "../share/pdf-presenter/help.bmp"
#define INFO				            "../share/pdf-presenter/comments.bmp"
#define INFO_INACT			            "../share/pdf-presenter/comments_ia.bmp"

#else

#define wxBMP(x) wxBITMAP(x)

#define NEXT                            102
#define NEXT_INACT                      103
#define PREV                            104
#define PREV_INACT                      105
#define RUN                             106
#define RUN_INACT                       107
#define OPEN                            108
#define STOP                            109
#define HELP                            110
#define NOTES                           111

#endif
