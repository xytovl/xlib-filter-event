#define _GNU_SOURCE
#include <dlfcn.h>

#include <string.h>

#include <X11/X.h>
#include <X11/Xlib.h>

// Retur next event, but discard all focusout events
int my_XNextEvent(Display* display, XEvent* event)
{
	int r = XNextEvent(display, event);

	while (event->type == FocusOut)
	{
		r = XNextEvent(display, event);
	}
	return r;
}

// SDL2 loads XNextEvent using dlsym, so we have to intercept this call to provide our function
// https://stackoverflow.com/questions/15599026/how-can-i-intercept-dlsym-calls-using-ld-preload
extern void *_dl_sym(void *, const char *, void *);
void * dlsym(void* handle, const char* name)
{
	if (handle != RTLD_DEFAULT && strcmp("XNextEvent", name) == 0)
	{
		return (void*)my_XNextEvent;
	}
	static void * (*real_dlsym)(void *, const char *)=NULL;
  if (real_dlsym == NULL)
    real_dlsym=_dl_sym(RTLD_NEXT, "dlsym", dlsym);
  /* my target binary is even asking for dlsym() via dlsym()... */
  if (!strcmp(name,"dlsym")) 
    return (void*)dlsym;
  return real_dlsym(handle,name);

}
