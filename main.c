/**********************************************
 KU Rechnerorganisation, 2015
 
 Datei liest von stdin Paare von Hex-Werten
 und multipliziert diese. Das Produkt wird
 in Hex-Format am stdout ausgegeben.
 
 Wenn der Wert 0 vom stdin gelesen wird,
 hält das Programmc an.
 
 KC Posch, Nov 2014
 **********************************************/

//BZ = if == 0
//BP = if > 0

#include <stdio.h>
#include <stdlib.h>

int main(void){
        int16_t OutHigh = 0;
        int16_t OutLow = 0;
        int16_t temp = 0;
        int16_t MaxCount = 16;
        int16_t CurrentCount = MaxCount;
        int16_t ONE = 1;
        int16_t truthMask = 0;
        int16_t tempShiftLOW = 0;
        int16_t tempShiftHIGH = 0;
        int16_t carryMask = 0;
        int16_t addWork1 = 0;
        int16_t addWork2 = 0;
        int16_t addWorkResult = 0;
        int16_t invertMask = 0xFFFF;
        int16_t carry = 0;
        ///////////UNUSED IN ASSEMBLER/////////
        int16_t Input1;
        int16_t Input2;
        int16_t tempInput1;
        int16_t tempInput2;
        ///////////////////////////////////////
START:  CurrentCount = 16;
        OutHigh += carry;
        printf("Result = %x \nOuthigh= %x \nOutlow =     %x",(uint16_t)Input1*(uint16_t)Input2,OutHigh,OutLow);
        carry = 0;
        OutHigh = 0;
        OutLow = 0;
        printf("\nPlease enter two Numbers: \n");
        scanf("%hd",&Input1);
        if(Input1 == 0){goto EXIT;}
        scanf("%hd",&Input2);
        if(Input2 == 0){goto EXIT;}
        //printf("\nAm i drunk? Input1: %d, Input2: %d \n",Input1,Input2);


LOOP:   tempInput1 = Input1;
        tempInput2 = Input2;
        CurrentCount = CurrentCount - ONE;
        tempInput2 = tempInput2 >> CurrentCount;
        truthMask = tempInput2 & ONE;
        if(truthMask == 0){goto SKIP;}
        //printf("Doing Math!\n");
        tempShiftLOW = Input1 << CurrentCount;
        temp = MaxCount - CurrentCount;
        tempShiftHIGH = Input1 >> temp;
        OutHigh = OutHigh + tempShiftHIGH;
        addWork1 = OutLow;
        addWork2 = tempShiftLOW;
        OutLow = OutLow + tempShiftLOW;
        goto ADDC;//jump and link
R1:
SKIP:   if(CurrentCount == 0){goto START;}
        if (0 == 0){goto LOOP;}
    
EXIT:   return 0;
  
ADDC:   addWorkResult = addWork1 + addWork2;
        carryMask = addWork1 & addWork2;
        carryMask = carryMask ^ invertMask;
        if(carryMask > 0){
          goto CARRY;
        }
        if(carryMask == 0){
          goto CARRY;
        }
        carryMask = addWork1 ^ addWork2;
        addWorkResult = addWorkResult ^ invertMask;
        carryMask = carryMask & addWorkResult;
        carryMask = carryMask ^ invertMask;
        if(carryMask > 0){
          goto CARRY;
        }
        if(carryMask == 0){
          goto CARRY;
        }
        goto R1;
        //BZ und BP
CARRY:  carry = carry + ONE;
        goto R1; //this needs to be a jump and link

}
/*
 
 printf("tempShiftLOW: %x !\n",tempShiftLOW);
 printf("tempInput1: %x !\n",tempInput1);
 printf("MaxCount: %x !\n",MaxCount);
 printf("tempShiftHIGH: %x !\n",tempShiftHIGH);
 
LDA OutHigh 0 // initialize Output High
LDA OutLow 0 // initialize Output Low
LDA temp 0 // Initalize working register C
LDA MaxCount 16 // initalize the Counter
LDI CurrentCount MaxCount // initalize the working Counter
LDA ONE 1 // initialize a 1
LDI truthMask 0 // initalize another working Directory
LDI tempShiftLOW 0 // init another Working Directory
LDI tempShiftHIGH 0 // init another working Directory
START 	LD Input1 0xFF // Load Input 1 in Input1
LD Input2 0xFF // Load Input 2 in Input2
BZ Input1 EXIT // HLT if input is 0
BZ Input2 EXIT // HLT if input is 0
LDI tempInput1 Input1 // Load Input 1 into the working register A
LDI tempInput2 Input2 // Load Input 2 into the working register B
LOOP	SUB CurrentCount CurrentCount ONE //Sub 1 from CurrentCount and store in CurrentCount
SHR tempInput1 tempInput1 CurrentCount // Shifte tempInput1 um Counter
AND truthMask tempInput1 ONE // truthMask = tempInput1 & 1
BZ truthMask SKIP // If truthMask == 0 Keine Rechnung
SHL tempShiftLOW tempInput1 MaxCount // Linksshift für den LowPart
SUB temp MaxCount CurrentCount  // 16-i
SHR tempShiftHIGH tempInput1 temp // Rechtsshift für den Higher Part

SKIP	BZ CurrentCount START //get new Input if counter is 0
BZ R0 LOOP // Loop

EXIT	HLT
*/
/*
int main() {
    uint16_t input1 = 12345;
    uint16_t input2 = 54321;
    uint16_t outputH = 0;
    uint16_t outputL = 0;
    uint16_t work1 = input1;
    uint16_t work2 = input2;
    int r = input1*input2; // testcase
    
    for (int i=15; i>=0; i--) {
        if ((work2 >> i) & 1)
        {
            outputL = outputL + (work1 << i);
            outputH = outputH + (work1 >> (16-i));
        }
    }
    printf("Reslut: 0x%x ; Output L: 0x%x \n",r,outputL);
    printf("Reslut: 0x%x ; Output H: 0x%x \n",r,outputH);
 
    return 0;
}*/