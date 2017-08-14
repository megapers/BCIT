/*------------------------------------------------------------------------------
-- SOURCE FILE: g_gps.cpp
--
-- PROGRAM: 	GPS receiver
--
-- FUNCTIONS:
--              void about_window()
--              int check_quit()
--              void initializeWindows(gpsmm &)
--              void init_scr()
--              void init_menubar(WINDOW *);
--              void init_printBox(WINDOW *);
--              void read_proc();
--              void about_window();
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 

-- DESIGNER: 	Terry Kang, Tim Makimov 
--
-- PROGRAMMER: 	Terry Kang
--
-- NOTES: This file constains the functions related to create and initilize windows
-- on screen using ncurses library.
------------------------------------------------------------------------------*/
#include "headers/ggps.h" 


/*--------------------------------------------------------------------------
-- FUNCTION: 	about_window 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	void about_window()
--
-- RETURNS: 	void 

-- NOTE: this function create window for about menu and pop it up. then
-- wait for user to press any keys to close it.
--------------------------------------------------------------------------*/
void about_window()
{
    WINDOW *about;

    /* create window for showing about */
    about = newwin(6, 40, 15, (COLS - 40) / 2);
    wbkgd(about, COLOR_PAIR(2));
    box(about, ACS_VLINE, ACS_HLINE);
    wmove(about, 1, 2);
    wprintw(about, "DGPS Verson 2.0");
    wmove(about, 2, 2);
    wprintw(about, "Made : Tim and Terry");
    wmove(about, 3, 2);
    wprintw(about, "Date : 2016.10.19");
    wmove(about, 4, 2);
    wprintw(about, "Press any key.. ");
    refresh();

    /* get any key from user */
    wgetch(about);

    /* remove about menu window */
    delwin(about);
}

/*--------------------------------------------------------------------------
-- FUNCTION: 	check_quit 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	int check_quit()
--
-- RETURNS: 	return 1 if user press 'y', otherwise return 0;

-- NOTE: this function create window for quit menu and pop it up. then
-- wait for user to press any keys to close it or 'y' to exit program.
--------------------------------------------------------------------------*/
int check_quit()
{
    WINDOW *check;
    int key;

    /* create window for asking quit */
    check = newwin(3, 40, 15, (COLS - 40) / 2);
    wmove(check, 1, 2);
    wprintw(check, "Exit program (y/n) ? ");
    wbkgd(check, COLOR_PAIR(2));
    box(check, ACS_VLINE, ACS_HLINE);
    refresh();
    
    /* get key from user */
    key = wgetch(check);
    
    /* remove quit menu window */
    delwin(check);
    if (key == 'y')
        return 1;
    else
        return 0;
}

/*--------------------------------------------------------------------------
-- FUNCTION: 	initializeWindows 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	void initializeWindows(gpsmm &)
-- RETURNS: 	void

-- NOTE: this function initializes all the windows of this program, and
-- then create a thread to read gps data and wait for user command.
--------------------------------------------------------------------------*/
void initializeWindows(gpsmm &gps_rec)
{
    init_scr();
    WINDOW *menubar, *win_left, *win_right, *win_header, *win_footer;

    /* init menu at the top */
    bkgd(COLOR_PAIR(1));
    menubar = subwin(stdscr, 1, COLS, 0, 0);
    init_menubar(menubar);

    /* create sub-windows for header, footer */
    win_header = subwin(stdscr, HEADER_HEIGHT, COLS, 1, 0);
    win_footer = subwin(stdscr, FOOTER_HEIGHT, COLS, LINES - FOOTER_HEIGHT, 0);
        
    /* create sub-windows that displays gps data */
    win_left = subwin(stdscr, CONTENT_HEIGHT, COLS / 2, HEADER_HEIGHT, 0);
    win_right = subwin(stdscr, CONTENT_HEIGHT, COLS / 2, HEADER_HEIGHT, COLS / 2);

    /* make a border for header and footer */
    init_printBox(win_header);
    init_printBox(win_footer);

    /* print title on header */
    print_header(win_header);
    /* print help on footer */
    print_footer(win_footer);

    /* initialize the windows for printing gps data*/
    init_printBoxes(win_left, win_right);

    /* refresh the window to show changes */
    refresh();

    GpsWinParam params;
    params.win_left = win_left;
    params.win_right = win_right;
    params.gps_rec = &gps_rec;

    pthread_t threads;
    /* create thread for reading gps data from gpsd */
    int rc = pthread_create(&threads, NULL, gpsThread, &params);
    if (rc)
    {
        cerr<<"Error:unable to create thread,"<<endl;
        endwin();
        return;
    }
    /* start reading command from user */
    read_proc();

    /* remove ncureses screen */
    endwin();
}
/*--------------------------------------------------------------------------
-- FUNCTION: 	init_scr 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	void init_scr()
--
-- RETURNS: 	void

-- NOTE: this function initializes the screen for this program and set colors. 
--------------------------------------------------------------------------*/
void init_scr()
{
    /* Start curses mode 		  */
    initscr();
    /*  initializes eight basic colors */
    start_color();
    /* set color pairs to be used later */
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_CYAN);
    init_pair(3, COLOR_RED, COLOR_CYAN);
    init_pair(4, COLOR_RED, COLOR_BLUE);

    /* Remove the cursor pointer */
    curs_set(0);
    /* Don't echo() while we do getch */
    noecho();
    /* Enables the keypad of the user's terminal */
    keypad(stdscr, TRUE);
}

/*--------------------------------------------------------------------------
-- FUNCTION: 	init_menubar 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	void init_menubar(WINDOW *)
--
-- RETURNS: 	void

-- NOTE: this function initializes the screen for this program and set colors. 
--------------------------------------------------------------------------*/
void init_menubar(WINDOW *menubar)
{
    /* set color for window */
    wbkgd(menubar, COLOR_PAIR(2));
    /* move cursor */
    wmove(menubar, 0, 5);
    wattron(menubar, COLOR_PAIR(3));
    /* Add string for menu */
    waddstr(menubar, "(A)bout");
    wmove(menubar, 0, 15);
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(Q)uit");
}

/*--------------------------------------------------------------------------
-- FUNCTION: 	init_printBox 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	void init_printBox(WINDOW *)
--
-- RETURNS: 	void

-- NOTE: this function initializes the screen for this program and set colors. 
--------------------------------------------------------------------------*/
void init_printBox(WINDOW *window)
{
    /* set color for window */
    wbkgd(window, COLOR_PAIR(1));
    /* make a border for window */
    box(window, ACS_VLINE, ACS_HLINE);
}

/*--------------------------------------------------------------------------
-- FUNCTION: 	read_proc 
--
-- DATE: 		Oct. 18, 2016
--
-- REVISIONS: 
--
-- DESIGNER: 	Terry Kang
--
-- PROGRAMMER: 	Terry Kang
--
-- INTERFACE: 	void read_proc()
--
-- RETURNS: 	void

-- NOTE: this function reads user's command for menus.
--------------------------------------------------------------------------*/
void read_proc()
{
    int key;
    while (1)
    {
        /* Wait for user input */
        key = getch();
        
        if (key == 'A' || key == 'a')
        {
            /* pop up about windows */
            about_window();
        }else if (key == 'q' || key == 'Q')
        {
            /* pop up quit menu and check selection */
            if (check_quit() == 1)
                break;
        }
        touchwin(stdscr);
        refresh();
    }
}

