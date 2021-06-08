//This script explores ghosting, blocking, and rollovers in electronic
//These are false signal readings that when switches or connection points are made in a circuit that contains a grid
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

#include <MuxShield.h>

//Initialize the Mux Shield
MuxShield muxShield;

//Arrays to store digital values
int IO1DigitalVals[16][16];
int IO2DigitalVals[16][16];
int IOCombinedVals[16][16];

void setup()
{

  resetAllArrays();
  Serial.begin(9600);

}

void loop()
{

  resetAllArrays();
 
  //measure the grid one way
  rowOneInputRowTwoOutput();
  resetRowTwo();
  readRowOne();
  
  //then measure it in perpendicular direction by swapping inputs/outputs
  rowOneOutputRowTwoInput();
  resetRowOne();
  readRowTwo();
  
  //add the results together and print them
  combinedBothArrays();
  printCombinedArray();

  delay(10000);
  Serial.println();

  
}

void resetAllArrays(){
  for (int i=0; i<16; i++)
  {
    for (int i=0; i<16; i++)
    {
      
      IO1DigitalVals[i][j] = 0;
      IO2DigitalVals[i][j] = 0;
      IOCombinedVals[i][j] = 0;
    }
  }
}


void resetRowOne(){
  for (int i=0; i<16; i++)
  {
    //int row 1-3, int pin 0-15, int digital_state 0 or 1
    muxShield.digitalWriteMS(1,i,0);
  }
}

void resetRowTwo(){
  for (int i=0; i<16; i++)
  {
    //int row 1-3, int pin 0-15, int digital_state 0 or 1
    muxShield.digitalWriteMS(2,i,0);
  }
}

void rowOneInputRowTwoOutput(){
 
  //Set mode sets the same mode for the entire column of pins (1, 2 or 3)
  muxShield.setMode(1,DIGITAL_IN);
  muxShield.setMode(2,DIGITAL_OUT);

}

void rowOneOutputRowTwoInput(){
 
  //Set mode sets the same mode for the entire column of pins (1, 2 or 3)
  muxShield.setMode(1,DIGITAL_OUT);
  muxShield.setMode(2,DIGITAL_IN);
  
}

void readRowOne(){
  
  // loop through array's rows
   for ( int j = 0; j < 16; ++j ) 
   {
  
    //raise the pin and see what inputs are connected 
    muxShield.digitalWriteMS(1,j,1);
    delay(50);

    // loop through columns of current row
    for ( int i = 0; i < 16; ++i )
    {
    
      //the rows and columns are switched in this array so it is compatible with the other 2d array
      IO2DigitalVals[i][j] = muxShield.digitalReadMS(2,j);
 
    }
    
    //reset that pin low
    muxShield.digitalWriteMS(1,j,0);
    delay(50);

   }
}
  

void readRowTwo(){
  
  // loop through array's rows
   for ( int i = 0; i < 16; ++i ) 
   {
  
    //raise the pin and see what inputs are connected 
    muxShield.digitalWriteMS(1,i,1);
    delay(50);

    // loop through columns of current row
    for ( int j = 0; j < 16; ++j )
    {
    
      IO2DigitalVals[i][j] = muxShield.digitalReadMS(2,i);
 
    }
    
    //reset that pin low
    muxShield.digitalWriteMS(1,i,0);
    delay(50);

   }
}
  
 
}


void combinedBothArraysArrays() {
  
   // loop through array's rows
   for ( int i = 0; i < rows; ++i ) {
  
      // loop through columns of current row
      for ( int j = 0; j < columns; ++j )
      {
        
        IOCombinedVals[i][j] = IO1DigitalVals[i][j] + IO2DigitalVals[i][j]
        
      }
   } 

} 

void printCombinedArray() {
  
   // loop through array's rows
   for ( int i = 0; i < rows; ++i ) {
  
      // loop through columns of current row
      for ( int j = 0; j < columns; ++j )
      {
        
        //if there are no readings, the intersection is empty
        if(IOCombinedArray[i][j] = 0)
        {
          Serial.print ("   EMPTY  ");
        }
        
        //if one, but not both, reading, then this is ghosting!
        if(IOCombinedArray[i][j] = 1)
        {
          Serial.print ("   GHOST  ");
        }
         
        //if both readings find something, then this is a true reading 
        if(IOCombinedArray[i][j] = 2)
        {
          Serial.print ("CONNECTION");
        }
        
        Serial.print (“\r” ) ; // start new line of output
        
      }
   } 

} 
