#ifndef ALFY_ENUMERATIONS_H
#define ALFY_ENUMERATIONS_H

enum MONTH  {BAD_MONTH,JANUARY,FEBRUARY,MARCH,APRIL,MAY,JUNE,JULY,AUGUST,SEPTEMBER,OCTOBER,NOVEMBER,DECEMBER};

enum DAY    {SUNDAY,MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY,BAD_DAY = -1};

enum NAME_TYPE {ALFY_FULL,ALFY_ABREV,ALFY_CODE};

enum STATE {
        ALABAMA, ALASKA, ARIZONA, ARKANSAS,
        CALIFORNIA, COLORADO, CONNECTICUT,
        DELAWARE,
        FLORIDA,
        GEORGIA,
        HAWAII,
        IDAHO, ILLINOIS, INDIANA, IOWA,
        KANSAS, KENTUCKY,
        LOUISIANA,
        MAINE, MARYLAND, MASSACHUSETTS, MICHIGAN, MINNESOTA, MISSISSIPPI, MISSOURI, MONTANA,
        NEBRASKA, NEVADA, NEW_HAMPSHIRE, NEW_JERSEY, NEW_MEXICO, NEW_YORK, NORTH_CAROLINA, NORTH_DAKOTA,
        OHIO, OKLAHOMA, OREGON,
        PENNSYLVANIA,
        RHODE_ISLAND,
        SOUTH_CAROLINA, SOUTH_DAKOTA,
        TENNESSEE, TEXAS,
        UTAH,
        VERMONT, VIRGINIA,
        WASHINGTON, WEST_VIRGINIA, WISCONSIN, WYOMING,
        BAD_STATE
};

#endif
