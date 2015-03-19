#include <stdio.h>
#include <stdlib.h>

int main(void){
  int OutHigh = 0; //R1
  int OutLow = 0; //R2
  int Mask = 0; //R3
  int MaxCount = 32; //R4
  int CurrentCount = MaxCount; //R5
  int ONE = 1; //R6
  int tempShiftLOW = 0; //R7
  int tempShiftHIGH = 0; //R8
  int addWork1 = 0; //R9
  int addWork2 = 0; //RA
  int tempInput2 = 0; //RB
  int invertMask = 0xFFFFFFFF; //RC
  int carry = 0; //RD
  int Input1; //RE
  int Input2; //RF
  
  goto FIRSTIN;
  
START:  OutHigh += carry;
  printf("Result = %x \nOuthigh= %x \nOutlow =     %x",Input1*Input2,OutHigh,OutLow);
FIRSTIN:
  CurrentCount = 32;
  carry = 0;
  OutHigh = 0;
  OutLow = 0;
  printf("\n------------------------------\nPlease enter two Numbers: \n");
  scanf("%d",&Input1);
  if(Input1 == 0){goto EXIT;}
  scanf("%d",&Input2);
  if(Input2 == 0){goto EXIT;}
  
  
LOOP:   tempInput2 = Input2;
        CurrentCount = CurrentCount - ONE;
        tempInput2 = tempInput2 >> CurrentCount;
        Mask = tempInput2 & ONE;
        if(Mask == 0){goto SKIP;}
        tempShiftLOW = Input1 << CurrentCount;
        Mask = MaxCount - CurrentCount;
        if(CurrentCount == 0){goto SKIP2;}
        tempShiftHIGH = Input1 >> Mask;
        Mask = invertMask + 0;
        Mask = Mask << CurrentCount;
        Mask = Mask ^ invertMask;
        tempShiftHIGH = tempShiftHIGH & Mask;
        OutHigh = OutHigh + tempShiftHIGH;
SKIP2:  addWork1 = OutLow;
        addWork2 = tempShiftLOW;
        OutLow = OutLow + tempShiftLOW;
        goto ADDC;
SKIP:   if(CurrentCount == 0){goto START;}
        if (0 == 0){goto LOOP;}
  
EXIT:   return 0;
  
ADDC:   tempInput2 = addWork1 + addWork2;
  Mask = addWork1 & addWork2;
  Mask = Mask ^ invertMask;
  if(Mask > 0){goto CARRY;}
  if(Mask == 0){goto CARRY;}
  Mask = addWork1 ^ addWork2;
  tempInput2 = tempInput2 ^ invertMask;
  Mask = Mask & tempInput2;
  Mask = Mask ^ invertMask;
  if(Mask > 0){goto CARRY;}
  if(Mask == 0){goto CARRY;}
  goto SKIP;
  
CARRY:  carry = carry + ONE;
  goto SKIP;
  
}