/*
 Benotete Programmieraufgabe
 LED NEO PIXELRING 

 von:
 Imad Abu Shammah Matrikelnummer: 2424340
 Fehmi Pakir  Matrikelnummer: XXXXXXX
 */

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

void SYSTEM_Initialize(void);

#define LEDS 24
//Define Arrays fpr GRBW Colors
uint8_t rgb[24][32]={
        //      G        |       R       |       B       |        W
        {0,0,0,0,0,0,0,0 ,1,0,1,0,1,0,0,0 ,0,0,1,1,1,0,0,1 ,0,0,0,0,0,0,0,0} //Voilette29
        {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0} //Pink28
        {0,1,1,0,1,0,0,1 ,1,1,1,1,1,1,1,1 ,1,0,1,1,0,1,0,0 ,0,0,0,0,0,0,0,0} //Rosa27
        {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1 ,1,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //Magenta26
        {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //Rot25
        {0,1,0,0,1,0,0,1 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //RotOrange24
        {0,1,1,0,1,1,0,1 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //OrangeOrange23
        {1,0,0,1,0,0,1,0 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //Orange22
        {1,0,1,1,0,1,1,0 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //OrangeGelb21
        {1,1,0,1,1,0,1,1 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //DunkelGelb20
        {1,1,1,1,1,1,1,1 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //Gelb19
        {1,1,1,1,1,1,1,1 ,1,1,0,0,1,0,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //GelbGrün18
        {1,1,1,1,1,1,1,1 ,1,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //GelbGrünGrün17
        {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //Grün16
        {1,1,0,1,0,1,0,0 ,0,0,0,0,0,0,0,0 ,0,0,0,1,1,1,0,0 ,0,0,0,0,0,0,0,0} //DunkelGrün15
        {1,0,1,1,0,0,1,1 ,0,0,0,1,0,1,1,1 ,0,1,0,0,1,1,0,1 ,0,0,0,0,0,0,0,0} //DunkelGrün14
        {1,0,1,0,1,1,1,1 ,0,0,0,0,1,0,1,1 ,1,0,1,0,0,0,1,0 ,0,0,0,0,0,0,0,0} //Mint13
        {1,0,0,1,1,1,1,1 ,0,0,0,0,0,0,0,1 ,1,1,1,0,1,0,0,0 ,0,0,0,0,0,0,0,0} //MintBlau12
        {0,1,1,1,0,0,1,0 ,0,0,0,0,0,0,0,1 ,1,1,1,0,0,0,1,0 ,0,0,0,0,0,0,0,0} //Blau11
        {0,1,0,0,0,1,0,0 ,0,0,0,0,0,0,0,0 ,1,1,0,1,1,1,0,0 ,0,0,0,0,0,0,0,0} //Cyan10
        {0,0,0,0,0,0,0,0 ,0,0,0,0,0,1,0,0 ,1,1,0,1,0,0,0,0 ,0,0,0,0,0,0,0,0} //DunkelBlau9
        {0,0,0,0,0,0,0,0 ,0,1,0,0,1,0,0,0 ,1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0} //DunkelBlau8
        {0,0,0,0,0,0,0,0 ,0,1,1,0,0,1,0,1 ,1,0,0,1,1,0,1,1 ,0,0,0,0,0,0,0,0} //LilaBlau7
        {0,0,0,0,0,0,0,0 ,1,0,0,0,0,0,0,0 ,1,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0} //Lila6

};
bool direction = 0;
//Define PixelBuffer
uint8_t pixels[768] = { 0 };
// Define Global Iteration variable I
int i = 0;
int state = 0;

//Setup Method
void setup()
{
    SYSTEM_Initialize();   // set 16 MHz clock for CPU and Peripheral Bus

    TRISCbits.TRISC0 = 1;  //Output RC0

    TRISC &= 0xFFFFFFFE;  // Clear Output Port C

    TRISBSET = 1 << 9; // set bit 9 of Port B for input (Button S1 on RB9)
    TRISCSET = 1 << 10; // set bit 10 of Port C for input (Button S2 on RC10)
    TRISCSET = 1 << 4; // set bit 4 of Port C for input (Button S3 on RC4)
  
}

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
    int i = 0;
    int y = 0;
    int lednumber = 0;
    int bitposition = 0;
 
    //Null Array to Fill the Unused LEDs Buffer with Nulls
    uint8_t nulls[768];
    for (i = 0; i < 768; i++)
    {
        nulls[i] = 0;
    }

    
    lednumber = 0;
    while (lednumber < 24)
    {
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
        // Load Buffer in the Ring by calling Assembler Routine
        display();
        // delay between to each LED
        delay_us(50000);

        bool button_s1 = !(PORTB & 1 << 9); // read status of bit 9 of Port B (1: Button S1 pressed)

        while (button_s1)
        {
            button_s1 = !(PORTB & 1 << 9); // 0: Button S1 not pressed, 1: Button S1 pressed
            if (button_s1 == 0) // when Button is released again, change direction
            {
                direction = !direction; // change direction
            }
        }
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
        bitposition = 0;

    }


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