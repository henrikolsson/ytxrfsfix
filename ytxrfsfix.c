#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>


static void ytxrfsfix_init(void) __attribute__((constructor));
static Status (*_XGetGeometry)(Display* display,Drawable d,Window* root_return,
                               int* x_return, int* y_return, unsigned int* width_return,
                               unsigned int* height_return, unsigned int* border_width_return,
                               unsigned int* depth_return) = NULL;
static int fullWidth = -1;
static int screenWidth = -1;

static void ytxrfsfix_init(void)
{
  Display *display;
  int screen;
  int minWidth, minHeight, maxWidth, maxHeight, currentWidth;
  
  _XGetGeometry = dlsym(RTLD_NEXT, "XGetGeometry");

  display = XOpenDisplay(NULL);
  if (display == NULL)
  {
    printf("Failed to open display\n");
  }
  else
  {
    screen = DefaultScreen(display);
    currentWidth = DisplayWidth(display, 0);
    XRRGetScreenSizeRange (display, RootWindow(display, screen),
                           &minWidth, &minHeight,
                           &maxWidth, &maxHeight);
    printf("Translating %d -> %d\n", currentWidth, minWidth);
    screenWidth = minWidth;
    fullWidth = currentWidth;
    XCloseDisplay(display);
  }
}


Status XGetGeometry(Display* display, Drawable d, Window* root_return,
                    int* x_return, int* y_return, unsigned int* width_return,
                    unsigned int* height_return, unsigned int* border_width_return,
                    unsigned int* depth_return)
{
  Status result = _XGetGeometry(display,d,root_return,x_return,y_return,
                                width_return,height_return,border_width_return,
                                depth_return);
  
  if (*width_return == fullWidth)
    *width_return = screenWidth;
  
  return result;
}
