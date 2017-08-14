/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: ggps.h
--
-- PROGRAM: GPS receiver
--
-- DATE: October 18, 2016
--
-- DESIGNER: Terry Kang 
--
-- PROGRAMMER: Terry Kang
--
-- NOTES:
-- This header file contains the declreations of the functions and macros that are used 
-- in g_gps.cpp and g_gpsprint.cpp for version 2 of this program.
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _GCGPS_H
#define _GCGPS_H
#include "dcgps.h"

#define ESCAPE 27
#define ENTER 10
#define HEADER_HEIGHT 13
#define FOOTER_HEIGHT 4
#define CONTENT_HEIGHT LINES - HEADER_HEIGHT - FOOTER_HEIGHT
#define TITLE_X_LEFT_BOX 3
#define VALUE_X_LEFT_BOX 15


const string menu_item[] = {"", "Help", "About", "Quit"};


void about_window();
int check_quit();
void init_scr();
void init_menubar(WINDOW *);
void init_printBox(WINDOW *);
void read_proc();
void *test_thread(void *);
void init_printBoxes(WINDOW *, WINDOW *);
void print_header(WINDOW *);
void print_footer(WINDOW *);
int printWinGPS(struct gps_data_t *, GpsWinParam *);
void *gpsThread(void *);

#endif


