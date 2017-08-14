/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: dcgps.h
--
-- PROGRAM: GPS receiver
--
-- DATE: October 18, 2016
--
-- DESIGNER: Terry Kang, Tim Makimov 
--
-- PROGRAMMER: Terry Kang, Tim Makimov 
--
-- NOTES:
-- This header file contains the declreations of the functions for dcgps.cpp
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _DCGPS_H
#define _DCGPS_H
#include <libgpsmm.h>
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include <iomanip>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <cstring>

using namespace std;

/* struct used for read thread */
typedef struct {
    /* pointer to window that diplays fix */
    WINDOW *win_left;
    /* pointer to window that diplays visible satelites info */
    WINDOW *win_right;
     /* pointer to gpsd */
    gpsmm *gps_rec;
} GpsWinParam;

int printGPSReport(struct gps_data_t*);
int readGPS(gpsmm&);

size_t write_data(void*, size_t, size_t, void*);
string getAddress(const string&, const string&);

void initializeWindows(gpsmm &);


#endif
