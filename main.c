/*
 Benotete Programmieraufgabe
 LED NEO PIXELRING 
 von:
 Imad Abu Shammah Matrikelnummer: 2424340
 Fehmi Pakir  Matrikelnummer: 5122868
 */

//Included Libaries
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

void SYSTEM_Initialize(void);

#define LEDS 24
//Define Arrays fpr GRBW Colors
uint8_t rgb[24][32]={
        //      G               |       R             |       B       |          W
        {0,0,0,0,0,0,0,0 ,1,0,1,0,1,0,0,0 ,0,0,1,1,1,0,0,1 ,0,0,0,0,0,0,0,0} ,//Voilette29
        {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0} ,//Pink28
        {0,1,1,0,1,0,0,1 ,1,1,1,1,1,1,1,1 ,1,0,1,1,0,1,0,0 ,0,0,0,0,0,0,0,0}, //Rosa27
        {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1 ,1,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //Magenta26
        {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //Rot25
        {0,1,0,0,1,0,0,1 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //RotOrange24
        {0,1,1,0,1,1,0,1 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //OrangeOrange23
        {1,0,0,1,0,0,1,0 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //Orange22
        {1,0,1,1,0,1,1,0 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //OrangeGelb21
        {1,1,0,1,1,0,1,1 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //DunkelGelb20
        {1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //Gelb19
        {1,1,1,1,1,1,1,1 ,1,1,0,0,1,0,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //GelbGrün18
        {1,1,1,1,1,1,1,1 ,1,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //GelbGrünGrün17
        {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //Grün16
        {1,1,0,1,0,1,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,1,1,1,0,0 ,0,0,0,0,0,0,0,0}, //DunkelGrün15
        {1,0,1,1,0,0,1,1 ,0,0,0,1,0,1,1,1 ,0,1,0,0,1,1,0,1 ,0,0,0,0,0,0,0,0}, //DunkelGrün14
        {1,0,1,0,1,1,1,1 ,0,0,0,0,1,0,1,1 ,1,0,1,0,0,0,1,0 ,0,0,0,0,0,0,0,0}, //Mint13
        {1,0,0,1,1,1,1,1 ,0,0,0,0,0,0,0,1 ,1,1,1,0,1,0,0,0 ,0,0,0,0,0,0,0,0}, //MintBlau12
        {0,1,1,1,0,0,1,0 ,0,0,0,0,0,0,0,1 ,1,1,1,0,0,0,1,0 ,0,0,0,0,0,0,0,0}, //Blau11
        {0,1,0,0,0,1,0,0 ,0,0,0,0,0,0,0,0 ,1,1,0,1,1,1,0,0 ,0,0,0,0,0,0,0,0}, //Cyan10
        {0,0,0,0,0,0,0,0 ,0,0,0,0,0,1,0,0 ,1,1,0,1,0,0,0,0 ,0,0,0,0,0,0,0,0}, //DunkelBlau9
        {0,0,0,0,0,0,0,0 ,0,1,0,0,1,0,0,0 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0}, //DunkelBlau8
        {0,0,0,0,0,0,0,0 ,0,1,1,0,0,1,0,1 ,1,0,0,1,1,0,1,1 ,0,0,0,0,0,0,0,0}, //LilaBlau7
        {0,0,0,0,0,0,0,0 ,1,0,0,0,0,0,0,0 ,1,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, //Lila6
};
//Variable for direction of rotation
bool direction = 0;
// Variable for speed of the delay
unsigned long speed;
//Define PixelBuffer

uint8_t pixels[768] = { 0 };
// Define Global Iteration variable I
int i = 0;

// Variable which defines the mode when button s2 is pressed
int mode=1;
//Setup Method
void setup()
{
    SYSTEM_Initialize();   // set 16 MHz clock for CPU and Peripheral Bus

    TRISCbits.TRISC0 = 1;  //Output RC0

    TRISC &= 0xFFFFFFFE;  // Clear Output Port C

    TRISBSET = 1 << 9; //   Init Button S1 on RB9
    TRISCSET = 1 << 10; // Init Button S1 on RB9Button S2 on RC10)
   
    //ADC Initialization for Potentiometer
    TRISCbits.TRISC8 = 1; //  RC8 = analog input
    ANSELCbits.ANSC8 = 1; 
    AD1CHSbits.CH0SA = 14; 
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.ADCS = 8;
    AD1CON1SET = 0x8000;
}
// Assembler Routine for sending bitbanging buffer to RC0 PIN
void sendAssembler()
{
    asm volatile ("nop");
    asm volatile (
    "addi $t0,$zero,0       \n\t"  // i=0 for Buffer Iteration
    "addi $t5,$zero,768     \n\t"  // $t5=768 Buffersize
    "for:"
    "beq $t0,$t5,end        \n\t"  // if i==768 (end of buffer) then  jump end
    "la $s0,pixels          \n\t"  // Load Adress of Buffer in $s0
    "add $t1,$t0,$s0        \n\t"  // Calculate Adress berechnen of pixels[i]]
    "lbu $s1,0($t1)         \n\t"  // $s1= pixels[i]  Load Adress
    "beq $s1,1,sendeeins    \n\t"  // Send 1 if $s1=1
     "b sendenull           \n\t"  // else send 0 

     // case 1 (HIGH)
    "sendeeins:"
      "li $t1, 1            \n\t"  // t1=1    
      "sw $t1,PORTC         \n\t"  // Send 1 to PortC (RC0)
      "nop \n\t"                   // Nops for Time Delay of 0,6us
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "sw $zero,PORTC       \n\t"  // Send 0 to PortC (RC0)
      "addi $t0,$t0,1       \n\t"  // i++
      "b for                \n\t"  // branch to for
      // case 0 (LOW)
      "sendenull: "
      "li $t1, 1            \n\t"  // t1=1       
      "sw $t1,PORTC         \n\t"  // Send 1 to PortC (RC0)
      "nop \n\t"                   // Nops for Time Delay of 0,3us
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"
      "li $t1, 0            \n\t"  //t1=1       
      "sw $t1,PORTC         \n\t"  // Send 0 to PortC (RC0)
      "nop \n\t"                   // Nops for Time Delay of 0,9us
      "nop \n\t"
      "nop \n\t"
      "addi $t0,$t0,1       \n\t"  // i++
      "b for                \n\t"  // branch to for 
      "end:                 \n\t"  // end of one buffer iteration through the whole buffer
     :
    :
    :"t1"
     );
}

// Display Function to Call Assembler Routine to 
// Iterate through the whole Buffer
void display()
{
    sendAssembler();
}


// Main Loop Function
void loop()
{
    //Iteration variables
    int i = 0;
    int y = 0;
    int z=0;
    //Variable for actual lednumber (color)
    int lednumber = 0;
    // Bitnumber of the Buffer (from 0 to 768)
    int bitposition = 0;

    //Null Array to Fill the Unused LEDs Buffer with Nulls

    uint8_t nulls[768];
        // 576 --> 768
    for (i = 0; i < 768; i++)
    {
        nulls[i] = 0;
    }
    
    //Setting Lednumber 0 before start
    lednumber = 0;
    
    while (lednumber < 24)
    {
        //Check if Mode has changed and user pressed S2
        checkForButtonInput();
        
       //Read Potentiometer Value
        readPotiADC();
        
        //Check if Mode 1 is activatet (Rotating Rainbow)
        if(mode==1){
        //Fill Pixel Buffer with Nulls 
        for (i = 0; i < 768; i++)
        {
            pixels[i] = 0;
        }
        //Fill Pixel Buffer with Nulls to the selected LED
        for (y = 0; y < 32 * lednumber; y++)
        {
            pixels[bitposition] = nulls[y];
            bitposition++;
        }
        // LOAD GRBW Color in selected LED 
        for (i = 0; i < 32; i++)
        {
            pixels[bitposition] = rgb[lednumber][i];
            bitposition++;
        }
        // Fill the Rest of the Buffer with Nulls 
        for (i = 0; i < (768 - ((lednumber + 1) * 32)); i++)
        {
            pixels[bitposition] = 0;
            bitposition++;
        }
        }
    
        //Check if Mode 2 is activated (All LEDS same Color changing with delay)
        if(mode==2){
        //Changing Color in every iteration by using lednumber(color variable)
        for(z=0;z<24;z++){
            
        for (i = 0; i < 32; i++)
        {
            pixels[bitposition] = rgb[lednumber][i];
            bitposition++;
        }
        }
        }
        
        //Check if mode 3 is activated (changing led color alternately to to random colors)
          if(mode==3){
        // LOAD GRBW Color in selected LED 
         // switcher variable to switch color for every LED
          int switcher=0;    
          //Load random led color
          int randomled=rand() % 23;
          // Load second random led color
          int randomled2=rand() % 23;
          // Check if random colors are the same if yes then get a new random color
          if(randomled==randomled2)
              randomled2=rand() % 23;
        // 24 --> 32
        // Load the color after every 32 Bits in Buffer  
        for(z=0;z<24;z++){
        // 576--> 768
            if(switcher==0){
        for (i = 0; i < 32; i++)
        {
            pixels[bitposition] = rgb[randomled][i];
            bitposition++;
        }
        switcher=1;
            }
            else{
        for (i = 0; i < 32; i++)
        {
            pixels[bitposition] = rgb[randomled2][i];
            bitposition++;
        }
        switcher=0;
            }
        }
        }
        // Load Buffer in the Ring by calling Assembler Routine
        display();
        // delay between to each LED every Mode needs different delay to make it look nice
        if(mode==2)
        delay_us(speed*500);
        else if(mode==1) 
         delay_us(speed*100);
          else if(mode==3) 
         delay_us(speed*500);
        
        // Check if user pressed button s2 to change the mode
        checkForButtonInput();
        // If direction forward and not the last one reached then iterate
        // else start with the first one
        if (direction == 0) {
            if (lednumber < 23)  lednumber++;
            else lednumber = 0;
        }
        // If direction backware and lednumber not the first one then
        // iterate normally backward else set the actual led to the last one
        if (direction == 1)
        {
            if (lednumber > 0) lednumber--;
            else lednumber = 23;
        }
        //Reset Bitposition for next iteration to start filling the 768 Bit buffer from beginning
        bitposition = 0;
    }
}



checkForButtonInput(){
   
        bool S1Button = !(PORTB & 1 << 9); // Check if user pressed  s1 button

        while (S1Button)
        {
            S1Button = !(PORTB & 1 << 9); // Check if user pressed  s1 button

            if (S1Button == 0) // when button is released change direction
            {
                direction = !direction; // change direction
            
            }
        }
        
        bool S2Button = !(PORTC & 1 << 10); // Check if user pressed  s2 button

        while (S2Button)
        {
            S2Button = !(PORTC & 1 << 10); // Check if user pressed  s2 button
            if (S2Button == 0) // when button is release change mode
            {
                if(mode==2){ 
                    mode=3;
               } 
                else if(mode==3){ 
                    mode=1;
               } 
                else  if(mode==1){ 
                    mode=2;
               } 
            }
        }
}
//Read value with ADC from potentiometer
 readPotiADC(){
    AD1CON1SET = 0x0002;
    delay_us(1000);
    AD1CON1CLR = 2;
    while(!AD1CON1bits.DONE){}
    speed=(ADC1BUF0);   // 0 to 1023
    T2CONbits.TON = 0;
    IFS0bits.T3IF = 0;
    PR2 = speed;
    T2CONbits.TON = 1;
}

// MAIN Program    
int main(void)
{
    setup();
    while (1)
    {
        loop();
    }
}