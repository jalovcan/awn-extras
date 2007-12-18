/*
 * Copyright (c) 2007 Mike Desjardins
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef SHINYSWITCHER_H_
#define SHINYSWITCHER_H_

#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>
#include <libawn/awn-applet.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <libawn/awn-cairo-utils.h>
#include <libawn/awn-applet.h>

#include 	<time.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#ifdef  USE_AWN_DESKTOP_AGNOSTIC
#include <libawn/awn-config-client.h>
#include <libawn/awn-vfs.h>
 
#define CONFIG_KEY(key) key
#else
#include <libgnomevfs/gnome-vfs.h>
#include <libgnomevfs/gnome-vfs-utils.h>
 
#include <gconf/gconf-client.h>	

#define GCONF_MENU "/apps/avant-window-navigator/applets/shinyswitcher"

#define CONFIG_KEY(key) GCONF_MENU "/" key
#endif

enum
{
	CENTRE,
	NW,
	NE,
	SE,
	SW
};

enum 
{
	IMAGE_CACHE_PIXBUF,
	IMAGE_CACHE_SURFACE
};


typedef struct
{
	gpointer	data;
	gint		width;
	gint		height;
	time_t		time_stamp;
	int			img_type;
}Image_cache_item;


typedef struct
{
	GtkWidget 				*min_win;
	WnckWindow				*wnck_window;
	void					*shinyswitcher;
	
}Window_info;

typedef struct
{
	WnckWorkspace 			*space;
	struct Shiny_switcher	*shinyswitcher;
	GtkWidget				*wallpaper_ev;
	int						mini_win_index;
	GList					*event_boxes;
}Workplace_info;


typedef struct
{
	AwnApplet 		*applet;

	GdkPixbuf 		*icon;
	GtkWidget		*container;
	GtkWidget		**mini_wins;
	
	GdkPixmap		*wallpaper_active;
	GdkPixmap		*wallpaper_inactive;
	
	gint 			height;
	gint			width;
	int 			mini_work_width;
	int 			mini_work_height;		
	
	gint 			rows;
	gint 			cols;
	
	
	WnckScreen		*wnck_screen;
	int 			wnck_token;	
	
	double			wallpaper_alpha_active;
	double			wallpaper_alpha_inactive;
	double			applet_scale;
	
	int				show_icon_mode;			//0...no	1...on inactive workspace onlt	2...all but active win	3..all
	int				scale_icon_mode;		//0...none  1...on all active ws  2...on_active_win 3...all
	double			scale_icon_factor;
	int				scale_icon_pos;			//0... centre  1 NW    2 NE   3 SE  4 SW	
	
	int				win_grab_mode;		//0...none	1...all (grab method may override) 2..active ws (and sticky)  3...active win
	int				win_grab_method;	//0...gdk
			
	GTree			*ws_lookup_ev;
	GTree			*ws_changes;
	
	GTree			*pixbuf_cache;
	GTree			*surface_cache;
	
	double			win_active_icon_alpha;
	double			win_inactive_icon_alpha;
	
	int				active_window_on_workspace_change_method;	//0... don't change. 1.. top of stack.
	
	int				do_queue_freq;
	gint			mousewheel;
	
	int				cache_expiry;
	
	gboolean		override_composite_check;
	
	AwnColor		applet_border_colour;
	AwnColor		background_colour;
	
	int				applet_border_width;
		

#ifdef USE_AWN_DESKTOP_AGNOSTIC
	AwnConfigClient		*config;
#else
	GConfClient			*config;
#endif
	
}Shiny_switcher;

// Applet
Shiny_switcher* applet_new (AwnApplet *applet,int width, int height);

#endif