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
        int16_t Input1;
        int16_t Input2;
        int16_t tempInput1;
        int16_t tempInput2;
  
        goto FIRSTIN;
  
START:  OutHigh += carry;
        printf("Result = %x \nOuthigh= %x \nOutlow =     %x",(uint16_t)Input1*(uint16_t)Input2,OutHigh,OutLow);
FIRSTIN:CurrentCount = 16;
        carry = 0;
        OutHigh = 0;
        OutLow = 0;
        printf("\n------------------------------\nPlease enter two Numbers: \n");
        scanf("%hd",&Input1);
        if(Input1 == 0){goto EXIT;}
        scanf("%hd",&Input2);
        if(Input2 == 0){goto EXIT;}


LOOP:   tempInput1 = Input1;
        tempInput2 = Input2;
        CurrentCount = CurrentCount - ONE;
        tempInput2 = tempInput2 >> CurrentCount;
        truthMask = tempInput2 & ONE;
        if(truthMask == 0){goto SKIP;}
        tempShiftLOW = Input1 << CurrentCount;
        temp = MaxCount - CurrentCount;
        tempShiftHIGH = Input1 >> temp;
        OutHigh = OutHigh + tempShiftHIGH;
        addWork1 = OutLow;
        addWork2 = tempShiftLOW;
        OutLow = OutLow + tempShiftLOW;
        goto ADDC;
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
        goto SKIP;

CARRY:  carry = carry + ONE;
        goto SKIP;

}