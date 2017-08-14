/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: gps-utils.h
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
-- This header file includes the header files that are referenced by gps_tuils.cpp
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _GPSPRINT_H
#define _GPSPRINT_H
#include "dcgps.h"
#include <curl/curl.h>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/en.h"
using namespace rapidjson;
string *resultString; 

#endif
