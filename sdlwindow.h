#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <SDL2/SDL.h>

class SDLWindow
{
private:
    bool is_closed = false;
    int r = 0, g = 0, b = 0, a = 0xFF;

public:
    static bool sdl_ready;
    static int window_counter;

    static bool sdl_init();
    static void sdl_close();

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

public:
    SDLWindow(int width, int height);
    SDLWindow();
    ~SDLWindow();

    void render();
    void clear();

    void setColor(int intensity);
    void setColor(int intensity, int a);
    void setColor(int r, int g, int b);
    void setColor(int r, int g, int b, int a);

    void setColorHSV(float h, float s, float v);

    void setPixel(int x, int y);
    void setPixel(int x, int y, int intensity);
    void setPixel(int x, int y, int r, int g, int b);

    void drawLine(int x1, int y1, int x2, int y2);
    void drawLine(int x1, int y1, int x2, int y2, int intensity);
    void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a);

    void drawRect(int x_ul, int y_ul, int w, int h);
    void drawRect(int x_ul, int y_ul, int w, int h, int intensity);
    void drawRect(int x1, int y1, int x2, int y2, int r, int g, int b, int a);

    void fillRect(int x_ul, int y_ul, int w, int h);
    void fillRect(int x_ul, int y_ul, int w, int h, int intensity);
    void fillRect(int x1, int y1, int x2, int y2, int r, int g, int b, int a);

    bool closed();
    void clearEvents();
    void processEvent(SDL_Event &e);
    void wait();
    void waitForClosed();
};

void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );
void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v );

#endif // MYWINDOW_H
