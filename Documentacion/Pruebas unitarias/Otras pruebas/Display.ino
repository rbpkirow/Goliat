void resetpos(void)
{
    mydisp.setPrintPos(0, 1);
    delay(2000); //delay 2 seconds
    mydisp.println("                "); //display space, use to clear the demo line
    mydisp.setPrintPos(0, 1);
}

void ActDatos(void)
{
    mydisp.setPrintPos(2, 1);
    mydisp.print(KP,DEC);
    mydisp.setPrintPos(9, 1);
    mydisp.print(KD,DEC);
    mydisp.setPrintPos(16, 1);
    mydisp.print(Velocidad,DEC);
}

void ResetDisplay(void)
{
    mydisp.begin();
    mydisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
    mydisp.clearScreen(); //CLear screen
}  
