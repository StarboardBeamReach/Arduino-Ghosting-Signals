# Arduino-Ghosting-Signals
Explores what happens to ghosting when two measurements are taken by swapping rows and columns.

//This is described best at https://deskthority.net/wiki/Rollover,_blocking_and_ghosting

//The example in that website has fixed digital inputs and outputs
//Arduino has the ability to swap inputs and outputs
//This script explores what happens to ghosting when two measurements are taken
//One measurement where the rows are inputs, the second measurement where the columns are inputs

//The circuit required is a grid of almost intersecting wires
//The grid is 16 rows (col 1 I/O pins) x 16 columns (col 2 I/O pins)
//At any time there may be any number of connections made on the grid
//With any luck this script will be able to determine empty, ghosted, and connected intersections.

//Reference materials
//http://mayhewlabs.com/media/Mux_Shield_II_User_Guide.pdf

