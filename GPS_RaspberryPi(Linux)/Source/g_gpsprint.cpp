/*------------------------------------------------------------------------------
-- SOURCE FILE: g_gpsprint.cpp 
--
-- PROGRAM: 	GPS receiver
--
-- FUNCTIONS:
--              int printWinGPS(struct gps_data_t *, GpsWinParam *)
--              void *gpsThread(void *)
--              void init_printBoxes(WINDOW *, WINDOW *)
--              void print_header(WINDOW *)
--              void init_scr()
--              void print_header(WINDOW *)
--              void print_footer(WINDOW *)
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 

-- DESIGNER: 	Terry Kang, Tim Makimov 
--
-- PROGRAMMER: 	Terry Kang
--
-- NOTES: This file contains the functions related to draw windows and print 
-- gps data on the windows using ncurses.    
------------------------------------------------------------------------------*/
#include "headers/ggps.h"
#include "headers/gpsprint.h"

int last_visible_satellites = 0;


/*--------------------------------------------------------------------------
-- FUNCTION: 	printWinGPS 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	int printWinGPS(struct gps_data_t *, GpsWinParam *)
--
-- RETURNS: 	int 

-- NOTE: this function gets gps data and displays on the windows if satelites are visible.
--------------------------------------------------------------------------*/
int printWinGPS(struct gps_data_t *newdata, GpsWinParam *gpsWinParam)
{
    bool usedflags[MAXCHANNELS];

    if (newdata->satellites_visible < 1)
        return 1;

    for (int i = 0; i < MAXCHANNELS; i++)
    {
        usedflags[i] = false;
        for (int j = 0; j < newdata->satellites_used; j++)
            if (newdata->used[j] == newdata->PRN[i])
                usedflags[i] = true;
    }


    int right_x = (COLS / 2) / 7 + 1;
    int y = 2;
    for (int i = 0; i < MAX_POSSIBLE_SATS; i++)
    {
        if (i < newdata->satellites_visible)
        {
            int j = 1;
            string prn = to_string(newdata->PRN[i]);
            string elevation = to_string(newdata->elevation[i]);
            string azimuth = to_string(newdata->azimuth[i]);
            string ss = to_string(newdata->ss[i]);
            string used = ((usedflags[i]) ? "Y" : "N");

            wmove(gpsWinParam->win_right, y, right_x * j++);
            wprintw(gpsWinParam->win_right, prn.c_str());
            wmove(gpsWinParam->win_right, y, right_x * j++);
            wprintw(gpsWinParam->win_right, elevation.c_str());
            wmove(gpsWinParam->win_right, y, right_x * j++);
            wprintw(gpsWinParam->win_right, azimuth.c_str());
            wmove(gpsWinParam->win_right, y, right_x * j++);
            wprintw(gpsWinParam->win_right, ss.c_str());
            wmove(gpsWinParam->win_right, y, right_x * j++);
            wprintw(gpsWinParam->win_right, used.c_str());
            y++;
        }
    }

    /* if previous visible statelite are more than current */
    /* removes the screen for dummy */
    if (y - 2 < last_visible_satellites)
    {
        for (int i = y; y <= last_visible_satellites; i++)
        {
            wmove(gpsWinParam->win_right, y, 1);
            wprintw(gpsWinParam->win_right, "%-*s", (COLS / 2) - 3, "");
        }
    }

    /* Fill in the time. */
    char time[256];
    if (isnan(newdata->fix.time) == 0)
    {
        (void)unix_to_iso8601(newdata->fix.time, time, sizeof(time));
    }
    else
        (void)snprintf(time, sizeof(time), "n/a");

    /* default values */
    string lat = "n/a";
    string lng = "n/a";
    string address = "n/a";
    string altitude = "n/a";
    string speed = "n/a";
    string climb = "n/a";
    string status = "NO FIX";

    /* Fill in the latitude and longitude. */
    if (newdata->fix.mode >= MODE_2D && isnan(newdata->fix.latitude) == 0 && isnan(newdata->fix.longitude) == 0)
    {
	    lat = to_string(fabs(newdata->fix.latitude));
	    lng = to_string(fabs(newdata->fix.longitude));
        address = getAddress(to_string(newdata->fix.latitude), to_string(newdata->fix.longitude));
        lat += "  " + (newdata->fix.latitude < 0) ? 'S' : 'N';
        lng += "  " + (newdata->fix.longitude < 0) ? 'W' : 'E';
    }
    /* Fill in the altitude. */
    if (newdata->fix.mode >= MODE_3D && isnan(newdata->fix.altitude) == 0)
        altitude = to_string(newdata->fix.altitude);

    /* Fill in the speed. */
    if (newdata->fix.mode >= MODE_2D && isnan(newdata->fix.track) == 0)
        speed = to_string(newdata->fix.speed);

    /* Fill in the rate of climb. */
    if (newdata->fix.mode >= MODE_3D && isnan(newdata->fix.climb) == 0)
        climb = to_string(newdata->fix.climb);

    /* Fill in status of fix. */
    switch (newdata->fix.mode) {
       case MODE_2D:
           status = "2D FIX";
           break;
       case MODE_3D:
           status = "3D FIX";
           break;
       default:
           status = "NO FIX";
           break;
    }

    int row = 1;
    wmove(gpsWinParam->win_left, row++, VALUE_X_LEFT_BOX);
    wprintw(gpsWinParam->win_left, time);
    wmove(gpsWinParam->win_left, row++, VALUE_X_LEFT_BOX);
    wprintw(gpsWinParam->win_left, lat.c_str());
    wmove(gpsWinParam->win_left, row++, VALUE_X_LEFT_BOX);
    wprintw(gpsWinParam->win_left, lng.c_str());
    wmove(gpsWinParam->win_left, row++, VALUE_X_LEFT_BOX);
    wprintw(gpsWinParam->win_left, address.c_str());
    wmove(gpsWinParam->win_left, row++, VALUE_X_LEFT_BOX);
    wprintw(gpsWinParam->win_left, altitude.c_str());
    wmove(gpsWinParam->win_left, row++, VALUE_X_LEFT_BOX);
    wprintw(gpsWinParam->win_left, speed.c_str());
    wmove(gpsWinParam->win_left, row++, VALUE_X_LEFT_BOX);
    wprintw(gpsWinParam->win_left, climb.c_str());
    wmove(gpsWinParam->win_left, row++, VALUE_X_LEFT_BOX);
    wprintw(gpsWinParam->win_left, status.c_str());

    /* refresh to show changes */
    wrefresh(gpsWinParam->win_left);
    wrefresh(gpsWinParam->win_right);

    return 0;
}


/*--------------------------------------------------------------------------
-- FUNCTION: 	gpsThread 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	void *gpsThread(void *)
--
-- RETURNS: 	void 

-- NOTE: This function is a thread to keep waiting and reading gps data
-- from gps.
--------------------------------------------------------------------------*/
void *gpsThread(void *context)
{
    GpsWinParam *gpsWinParam = reinterpret_cast<GpsWinParam *>(context);

    for (;;)
    {
        struct gps_data_t *newdata;

        /* time out for 5 sec*/
        if (!gpsWinParam->gps_rec->waiting(50000000))
            continue;
        if ((newdata = gpsWinParam->gps_rec->read()) == NULL)
        {
            endwin();
            exit(0);
        }
        else
        {
            printWinGPS(newdata, gpsWinParam);
        }
    }
}


/*--------------------------------------------------------------------------
-- FUNCTION: 	init_printBoxes 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	void init_printBoxes(WINDOW *, WINDOW *)
--
-- RETURNS: 	void 

-- NOTE: This function prints the names of gps data and default values
-- on windows. 
--------------------------------------------------------------------------*/
void init_printBoxes(WINDOW *left, WINDOW *right)
{
    wclear(left);
    wclear(right);
    init_printBox(left);
    init_printBox(right);
    int row = 1;
    wmove(left, row++, TITLE_X_LEFT_BOX);
    wprintw(left, "Time:");
    wmove(left, row++, TITLE_X_LEFT_BOX);
    wprintw(left, "Latitude:");
    wmove(left, row++, TITLE_X_LEFT_BOX);
    wprintw(left, "Longitude:");
    wmove(left, row++, TITLE_X_LEFT_BOX);
    wprintw(left, "Address:");
    wmove(left, row++, TITLE_X_LEFT_BOX);
    wprintw(left, "Altitude:");
    wmove(left, row++, TITLE_X_LEFT_BOX);
    wprintw(left, "Speed:");
    wmove(left, row++, TITLE_X_LEFT_BOX);
    wprintw(left, "Climb:");
    wmove(left, row++, TITLE_X_LEFT_BOX);
    wprintw(left, "Status:");

    row = 1;
    wmove(left, row++, VALUE_X_LEFT_BOX);
    wprintw(left, "n/a");
    wmove(left, row++, VALUE_X_LEFT_BOX);
    wprintw(left, "n/a");
    wmove(left, row++, VALUE_X_LEFT_BOX);
    wprintw(left, "n/a");
    wmove(left, row++, VALUE_X_LEFT_BOX);
    wprintw(left, "n/a");
    wmove(left, row++, VALUE_X_LEFT_BOX);
    wprintw(left, "n/a");
    wmove(left, row++, VALUE_X_LEFT_BOX);
    wprintw(left, "n/a");
    wmove(left, row++, VALUE_X_LEFT_BOX);
    wprintw(left, "n/a");
    wmove(left, row++, VALUE_X_LEFT_BOX);
    wprintw(left, "n/a");


    int right_x = (COLS / 2) / 7 + 1;
    int col = 1;
    wmove(right, 1, right_x * col++);
    wprintw(right, "PRN:");
    wmove(right, 1, right_x * col++);
    wprintw(right, "Elev:");
    wmove(right, 1, right_x * col++);
    wprintw(right, "Azim:");
    wmove(right, 1, right_x * col++);
    wprintw(right, "SNR:");
    wmove(right, 1, right_x * col++);
    wprintw(right, "Used:");

    wrefresh(left);
    wrefresh(right);
}

/*--------------------------------------------------------------------------
-- FUNCTION: 	print_header 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	void print_header(WINDOW *)
--
-- RETURNS: 	void 

-- NOTE: This function prints the drawing on the header window.
--------------------------------------------------------------------------*/
void print_header(WINDOW *header)
{
    int row = 1;
    string c = "========================================================================================================================";
    size_t n = c.length();
    wmove(header, row++, (COLS - n) / 2);
    wprintw(header, "========================================================================================================================");
    wmove(header, row++, (COLS - n) / 2);
    wprintw(header, "=        ==    ==  =====  ==========  =====  =======  ==       ========        ==        ==       ===       ===  ====  =");
    wmove(header, row++, (COLS - n) / 2);
    wprintw(header, "====  ======  ===   ===   =========    ====   ======  ==  ====  ==========  =====  ========  ====  ==  ====  ==   ==   =");
    wmove(header, row++, (COLS - n) / 2);
    wprintw(header, "====  ======  ===  =   =  ========  ==  ===    =====  ==  ====  ==========  =====  ========  ====  ==  ====  ===  ==  ==");
    wmove(header, row++, (COLS - n) / 2);
    wprintw(header, "====  ======  ===  == ==  =======  ====  ==  ==  ===  ==  ====  ==========  =====  ========  ===   ==  ===   ===  ==  ==");
    wmove(header, row++, (COLS - n) / 2);
    wprintw(header, "====  ======  ===  =====  =======  ====  ==  ===  ==  ==  ====  ==========  =====      ====      ====      ======    ===");
    wmove(header, row++, (COLS - n) / 2);
    wprintw(header, "====  ======  ===  =====  =======        ==  ====  =  ==  ====  ==========  =====  ========  ====  ==  ====  =====  ====");
    wmove(header, row++, (COLS - n) / 2);
    wprintw(header, "====  ======  ===  =====  =======  ====  ==  =====    ==  ====  ==========  =====  ========  ====  ==  ====  =====  ====");
    wmove(header, row++, (COLS - n) / 2);
    wprintw(header, "====  ======  ===  =====  =======  ====  ==  ======   ==  ====  ==========  =====  ========  ====  ==  ====  =====  ====");
    wmove(header, row++, (COLS - n) / 2);
    wprintw(header, "====  =====    ==  =====  =======  ====  ==  =======  ==       ===========  =====        ==  ====  ==  ====  =====  ====");
    wmove(header, row++, (COLS - n) / 2);
    wprintw(header, "========================================================================================================================");
    wrefresh(header);
}

/*--------------------------------------------------------------------------
-- FUNCTION: 	print_footer 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	void print_footer(WINDOW *)
--
-- RETURNS: 	void 

-- NOTE: This function prints how to open menus
--------------------------------------------------------------------------*/
void print_footer(WINDOW *footer)
{
    int row = 1;
    wmove(footer, row++, 5);
    wprintw(footer, "Press 'A' or 'a' to read about this program.");
    wmove(footer, row++, 5);
    wprintw(footer, "Press 'Q' or 'q' to quit this program");
    wrefresh(footer);
}