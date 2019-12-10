/*
 First PIC32MM program
 
 This simple example program lets LED1 blink
 */

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

void SYSTEM_Initialize(void);

#define LEDS 24
//Arrays
uint8_t rgb[24][32]={
    //      G           |          R              |        B             |        W         
    {0,0,0,0,0,0,0,0   ,1,1,1,1,1,1,1,1 ,   0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, //RED
    {0,0,0,0,0,1,0,0   ,0,1,0,1,0,0,1,1     ,0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, // ORANGE
    {1,1,1,1,1,1,1,1   ,1,1,1,1,1,1,1,1     ,0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, //YELLOW
    {1,1,1,1,1,1,1,1   ,0,0,0,0,0,0,0,0     ,0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, //Green
    { 0,0,0,0,0,0,0,0   ,0,0,0,0,0,0,0,0   ,1,1,1,1,1,1,1,1   ,0,0,0,0,0,0,0,0}, //Blue
     { 0,0,0,0,0,1,0,0   ,0,0,0,0,0,0,0,0   ,0,0,0,1,0,0,1,1   ,0,0,0,0,0,0,0,0}, //Indigo
     { 0,0,0,0,0,0,0,0    ,0,0,0,1,0,1,1,1 , 0,0,0,1,0,1,1,0   ,0,0,0,0,0,0,0,0}, //Violet
     { 1,1,1,1,1,1,1,1     ,0,0,0,0,0,0,0,0  , 1,1,1,1,1,1,1,1     ,0,0,0,0,0,0,0,0}, //Cyan
     { 0,0,0,0,0,0,0,0   ,1,1,1,1,1,1,1,1   ,1,1,1,1,1,1,1,1     ,0,0,0,0,0,0,0,0}, //Magenta
     
    {0,0,0,0,0,0,0,0   ,1,1,1,1,1,1,1,1   , 0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, //RED
    {0,0,0,0,0,1,0,0  , 0,1,0,1,0,0,1,1    ,0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, // ORANGE
    {1,1,1,1,1,1,1,1   ,1,1,1,1,1,1,1,1     ,0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, //YELLOW
    {1,1,1,1,1,1,1,1   ,0,0,0,0,0,0,0,0      ,0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, //Green
    { 0,0,0,0,0,0,0,0   , 0,0,0,0,0,0,0,0   ,1,1,1,1,1,1,1,1   ,0,0,0,0,0,0,0,0}, //Blue
     { 0,0,0,0,0,1,0,0   , 0,0,0,0,0,0,0,0    ,0,0,0,1,0,0,1,1   ,0,0,0,0,0,0,0,0}, //Indigo
     { 0,0,0,0,0,0,0,0    ,0,0,0,1,0,1,1,1   ,0,0,0,1,0,1,1,0   ,0,0,0,0,0,0,0,0}, //Violet
     { 1,1,1,1,1,1,1,1    ,0,0,0,0,0,0,0,0   ,1,1,1,1,1,1,1,1     ,0,0,0,0,0,0,0,0}, //Cyan
     { 0,0,0,0,0,0,0,0  , 1,1,1,1,1,1,1,1   ,1,1,1,1,1,1,1,1     ,0,0,0,0,0,0,0,0}, //Magenta

    {0,0,0,0,0,0,0,0   ,1,1,1,1,1,1,1,1 ,   0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, //RED
    {0,0,0,0,0,1,0,0   ,0,1,0,1,0,0,1,1     ,0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, // ORANGE
    {1,1,1,1,1,1,1,1   ,1,1,1,1,1,1,1,1    , 0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, //YELLOW
    {1,1,1,1,1,1,1,1   ,0,0,0,0,0,0,0,0    , 0,0,0,0,0,0,0,0  ,0,0,0,0,0,0,0,0}, //Green
    { 0,0,0,0,0,0,0,0   , 0,0,0,0,0,0,0,0  , 1,1,1,1,1,1,1,1   ,0,0,0,0,0,0,0,0}, //Blue
     { 0,0,0,0,0,1,0,0   , 0,0,0,0,0,0,0,0  , 0,0,0,1,0,0,1,1   ,0,0,0,0,0,0,0,0} //Indigo
};

uint8_t pixels[768]={0};
int i = 0;
int state=0;
void setup() { 
SYSTEM_Initialize();  // set 16 MHz clock for CPU and Peripheral Bus
                          // clock period = 41,667 ns = 0,0417 us   
TRISCbits.TRISC0 = 1;//Output RB0
TRISCbits.TRISC11 = 1;//Output RB0

TRISC &= 0xFFFFFFFE ;     // clear bit 0 of Port B for output


}


void sendAssembler(){  
asm volatile("nop");
asm volatile(
    "addi $t0,$zero,0           \n\t" //j=0
    "addi $t5,$zero,768     \n\t" // $t5=768
     "for:" 
  "beq $t0,$t5,end          \n\t" // j==32 jump ende
    "la $s0,pixels              \n\t" // Adresse des Arrays laden in $s0
    //"sll $t0,$t0,2\n\t" //i*4
    "add $t1,$t0,$s0        \n\t"  //Adresse berechnen von pixels[i]]
    "lbu $s1,0($t1)         \n\t" //$s1= pixels[i] Adresse Laden
    "beq $s1,1,sendeeins \n\t"
     "b sendenull \n\t"

     // case 1
     "sendeeins:"
       "li $t1, 1           \n\t"     //loadi       
      "sw $t1,PORTC  \n\t" //1 an PORT C ausgeben
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
      "nop \n\t"
        "sw $zero,PORTC \n\t" // clear port c
        
        "addi $t0,$t0,1     \n\t" //j++
       "b for                   \n\t"//0 an PORT C ausgeben
       // case 0
       "sendenull: "
        "li $t1, 1                  \n\t"     //loadi       
       "sw $t1,PORTC        \n\t" //1 an PORT C ausgeben
       "nop \n\t"
       "nop \n\t"
       "nop \n\t"
       "nop \n\t"
       "nop \n\t"
       "li $t1, 0 \n\t"     //loadi       
       "sw $t1,PORTC    \n\t" //0 an PORT C aus
      "nop \n\t"
      "nop \n\t"
      "nop \n\t"

       "addi $t0,$t0,1\n\t" // increment t0 as loop variable
       "b for \n\t"
       "end: \n\t"
     :
    :
    :"t1"   
     );
}


void display(){
    sendAssembler();
    
    }



void loop() { 
    char active_led =0;
    int i=0;
    int durchlauf=0;
    int bitstelle=0;
    int y=0;
    uint8_t nullen[768];
       for(i=0;i<768;i++) {   
           nullen[i]=0;
       }
      
    
    durchlauf= 0;
    while(durchlauf<24){
        //Pixel mit Nullen fühlen
         for(i=0;i<768;i++) {   
           pixels[i]=0;
       }
         //Pro durchlauf 32 Bit nullen
     for(y=0;y<32*durchlauf ;y++) {         
        pixels[bitstelle] = nullen[y];
        bitstelle++;
     }
         // led farbe 
        for(i=0;i<32;i++){
              pixels[bitstelle] = rgb[durchlauf][i];
              bitstelle++;
        }
        i=0;
         for(i=0;i<(768-((durchlauf+1)*32));i++){
              pixels[bitstelle] = 0;
              bitstelle++;
        }  
        // update LEDs
       display();
        // delay between to updates
        delay_us(50000);
        durchlauf++;
        bitstelle=0;
    
    }
    
}
    

    
  

  
    
   
    


//int i =0;
//int state=0;
//for(i=0;i<32;i++){
//    state = pixels[i];
//    
//    if(state==0){
//        LATCbits.LATC0 = 1;
//        asm("nop");
//         asm("nop");
//          asm("nop");
//         
//       LATCbits.LATC0 = 0;
//    }
//    
//    else{
//        LATCSET=1;
//              asm("nop");
//               asm("nop");
//                  asm("nop");
//                        asm("nop");
//         asm("nop");
//          asm("nop");
//               asm("nop");
//         asm("nop");
//          asm("nop");
//               asm("nop");
//               asm("nop");
//               asm("nop");
//        LATCCLR=1;
//    }
//}




int main(void) {
    setup();
    while(1){
        loop();
    }
}