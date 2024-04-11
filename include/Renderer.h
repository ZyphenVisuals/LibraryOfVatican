#ifndef RENDERER
#define RENDERER

void render_footer(const char *fmt, ...);
void setup_screen();
int render_menu(unsigned int count, char *choices[]);

#endif