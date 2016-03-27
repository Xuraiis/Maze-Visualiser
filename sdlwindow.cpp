#include <iostream>

#include "sdlwindow.h"

using namespace std;

bool SDLWindow::sdl_ready = false;
int SDLWindow::window_counter = 0;

bool SDLWindow::sdl_init(){
    if(SDLWindow::sdl_ready){
        cout << "SDL already initialised." << endl;
        return true;
    }

    cout << "Initialising SDL" << endl;

    if(SDL_Init( SDL_INIT_VIDEO ) < 0){
        cerr << "SDL Initialization Error: " << SDL_GetError() << endl;
        return false;
    }

    if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY,"1")){
        cerr << "Warning: Linear texture filtering not enabled!" << endl;
    }

    sdl_ready = true;
    return true;
}

void SDLWindow::sdl_close(){
    cout << "Quitting SDL" << endl;
    SDL_Quit();
}

SDLWindow::SDLWindow(int width, int height) : SCREEN_WIDTH(width), SCREEN_HEIGHT(height) {
    sdl_init();

    window = SDL_CreateWindow( "COMS1017", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        cerr << "Window could not be created: " <<  SDL_GetError() << endl;
        return;
    }

    window_counter++;
    cout << "Created window " << window_counter << endl;

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if( renderer == NULL )
    {
        cerr << "Renderer could not be created: " << SDL_GetError() << endl;
        return;
    }

    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

SDLWindow::SDLWindow() : SDLWindow(640,480) { }

SDLWindow::~SDLWindow(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    cout << "Destroyed window " << window_counter << endl;

    window_counter--;
    if(window_counter == 0){
        sdl_close();
    }
}

void SDLWindow::render(){
    SDL_RenderPresent(renderer);
    clearEvents();
}

void SDLWindow::clear(){
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
}

bool SDLWindow::closed(){
    clearEvents();
    return is_closed;
}

void SDLWindow::wait(){
    SDL_Event e;
    SDL_WaitEvent(&e);
    processEvent(e);
}

void SDLWindow::waitForClosed(){
    while(!is_closed) wait();
}

void SDLWindow::clearEvents(){
    SDL_Event e;
    while(SDL_PollEvent( &e) != 0){
        processEvent(e);
    }
}

void SDLWindow::processEvent(SDL_Event &e){
    if(e.type == SDL_QUIT){
        is_closed = true;
    }
}

//setColor
void SDLWindow::setColor(int intensity) {
	r = intensity;
	g = intensity;
	b = intensity;
	a = 0xFF;
}
void SDLWindow::setColor(int intensity, int arg_a) {
	r = intensity;
	g = intensity;
	b = intensity;
	a = arg_a;
}
void SDLWindow::setColor(int arg_r, int arg_g, int arg_b) {
	r = arg_r;
	g = arg_g;
	b = arg_b;
	a = 0xFF;
}
void SDLWindow::setColor(int arg_r, int arg_g, int arg_b, int arg_a) {
	r = arg_r;
	g = arg_g;
	b = arg_b;
	a = arg_a;
}

//SetColorHSB
void SDLWindow::setColorHSV(float h, float s, float v) {
	float fr, fg, fb;
	HSVtoRGB(&fr, &fg, &fb, h, s, v);
	r = fr * 255;
	g = fg * 255;
	b = fb * 255;
	a = 0xFF;
}

//setPixel
void SDLWindow::setPixel(int x, int y){
    SDL_SetRenderDrawColor( renderer, r, g, b, 0xFF );
    SDL_RenderDrawPoint( renderer, x, y );
}
void SDLWindow::setPixel(int x, int y, int intensity){
    SDL_SetRenderDrawColor( renderer, intensity, intensity, intensity, 0xFF );
    SDL_RenderDrawPoint( renderer, x, y );
}
void SDLWindow::setPixel(int x, int y, int r, int g, int b){
    SDL_SetRenderDrawColor( renderer, r, g, b, 0xFF );
    SDL_RenderDrawPoint( renderer, x, y );
}

//drawLine
void SDLWindow::drawLine(int x1, int y1, int x2, int y2){
    SDL_SetRenderDrawColor( renderer, r, g, b, 0xFF );
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
void SDLWindow::drawLine(int x1, int y1, int x2, int y2, int intensity){
    SDL_SetRenderDrawColor( renderer, intensity, intensity, intensity, 0xFF );
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
void SDLWindow::drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a){
    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

//drawRect
void SDLWindow::drawRect(int x_ul, int y_ul, int w, int h){
    SDL_SetRenderDrawColor( renderer, r, g, b, 0xFF );
    SDL_Rect rect{x_ul, y_ul, w, h};
    SDL_RenderDrawRect(renderer, &rect);
}
void SDLWindow::drawRect(int x_ul, int y_ul, int w, int h, int intensity){
    SDL_SetRenderDrawColor( renderer, intensity, intensity, intensity, 0xFF );
    SDL_Rect rect{x_ul, y_ul, w, h};
    SDL_RenderDrawRect(renderer, &rect);
}
void SDLWindow::drawRect(int x_ul, int y_ul, int w, int h, int r, int g, int b, int a){
    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    SDL_Rect rect{x_ul, y_ul, w, h};
    SDL_RenderDrawRect(renderer, &rect);
}

//fillRect
void SDLWindow::fillRect(int x_ul, int y_ul, int w, int h){
    SDL_SetRenderDrawColor( renderer, r, g, b, 0xFF );
    SDL_Rect rect{x_ul, y_ul, w, h};
    SDL_RenderFillRect(renderer, &rect);
}
void SDLWindow::fillRect(int x_ul, int y_ul, int w, int h, int intensity){
    SDL_SetRenderDrawColor( renderer, intensity, intensity, intensity, 0xFF );
    SDL_Rect rect{x_ul, y_ul, w, h};
    SDL_RenderFillRect(renderer, &rect);
}
void SDLWindow::fillRect(int x_ul, int y_ul, int w, int h, int r, int g, int b, int a){
    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    SDL_Rect rect{x_ul, y_ul, w, h};
    SDL_RenderFillRect(renderer, &rect);
}



void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
{
	float min, max, delta;

	min = r; max = r;
	if(g < min) min = g; else if(g > max) max = g;
	if(b < min) min = b; else if(b > max) max = b;

	*v = max;				// v
	delta = max - min;
	if( max != 0 )
		*s = delta / max;		// s
	else {
		// r = g = b = 0		// s = 0, v is undefined
		*s = 0;
		*h = -1;
		return;
	}
	if( r == max )
		*h = ( g - b ) / delta;		// between yellow & magenta
	else if( g == max )
		*h = 2 + ( b - r ) / delta;	// between cyan & yellow
	else
		*h = 4 + ( r - g ) / delta;	// between magenta & cyan
	*h *= 60;				// degrees
	if( *h < 0 )
		*h += 360;
}

void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
	int i;
	float f, p, q, t;
	if( s == 0 ) {
		*r = *g = *b = v;
		return;
	}
	h = ((int)h) % 360; //added
	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}
}
