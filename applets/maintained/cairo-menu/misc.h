

#ifndef _CAIRO_MISC
#define _CAIRO_MISC

#include <libdesktop-agnostic/fdo.h>
#include <gtk/gtk.h>
#include <libdesktop-agnostic/gtk.h>
#include <libdesktop-agnostic/vfs.h>
#include "cairo-menu-item.h"
#include "cairo-menu.h"

#define XDG_OPEN "xdg-open"

DesktopAgnosticFDODesktopEntry * get_desktop_entry (gchar * desktop_file);

void _launch (GtkMenuItem *menu_item,gchar * desktop_file);

GtkWidget * get_gtk_image (gchar * icon_name);

GtkWidget * get_recent_menu (void);


void  _remove_menu_item  (GtkWidget *menu_item,GtkWidget * menu);
void  _fillin_connected(DesktopAgnosticVFSVolume *volume,CairoMenu *menu);
void _exec (GtkMenuItem *menuitem,gchar * cmd);



#endif /* _CAIRO_MISC */