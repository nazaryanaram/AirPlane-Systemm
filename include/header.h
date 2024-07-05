#include <stdio.h>
#include "cJSON/cJSON.h"


#ifndef FLIGHT_BOOKING_H
#define FLIGHT_BOOKING_H


typedef struct
{
    int ID;
    int age;
    char *name;
    char *PhoneNumber;
    char *email;
} User;

typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    int ID;
    char *from;
    char *to;
    Date date;
    char *model;
} Flight;

typedef struct
{
    int user_id;
    int flight_id;
} Book_Flights;

#endif
