Readme file for Door Manager

Table of contents

1. Getting started
2. Folders and Files
3. Acknowledgements


1. Getting Started

   1. Gather information
      1a. Door images in Doors folder named by their style number 
          (ex. CCA211)
      1b. Fill out the spreadsheets* in the data folder (they are the 
          .csv files)

   2. Fill the database
      2a. Run each of the utilities in the data folder to load the 
          internal database (door_loader.exe, price_loader.exe, 
          size_loader.exe)

   3. Use the program
      3a. Launch Door Manager.exe
      3b. Click on a door
      3c. Fill out the information
      3d. Print** (it brings up a print preview)

   *Don't use commas (,) in these files

   **in order to make pdf's you will need to install Ghostscript 
   which is freely downloadable as of the writing of this readme at 
   http://downloads.ghostscript.com/public/gs905w32.exe.
   Simply install it at the default location with default options and
   it should work correctly.


2. Folders and Files (What everything is for)
	
   Folders

	Data - Database and spreadsheet files.
	
	Doors - Contains the picture of each door.

   Files

	Door Manager.exe - The main application

	Readme.txt - This file

	data\doors.csv - Spreadsheet of door information

	data\prices.csv - Spreadsheet of door prices

	data\sizes.csv - Spreadsheet of door sizes

	data\doors.db - the program's internal database

	data\door_loader.exe - loads doors.csv into database

	data\price_loader.exe - loads prices.csv into database
        
	data\size_loader.exe - loads sizes.csv into database


3. Acknowledgements

   Door Manager is based in part on the work of the FLTK project 
   (http://www.fltk.org).