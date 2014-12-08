void resetpos(void)
{
    mydisp.setPrintPos(0, 1);
    delay(2000); //delay 2 seconds
    mydisp.println("                "); //display space, use to clear the demo line
    mydisp.setPrintPos(0, 1);
}


void ResetDisplay(void)
{
    mydisp.begin();
    mydisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
    mydisp.clearScreen(); //CLear screen
}  
