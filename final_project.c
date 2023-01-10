#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include <time.h>
#include "stdio.h"
#include "string.h"

// using namespace std;
unsigned char target[]="1234\r\n";

// Global variable
int a = 0x04;
char str[20];

void random_number()
{
    unsigned char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; 
    unsigned char temp=0;
    const int ArraySize = sizeof(numbers) / sizeof(numbers[0]); 
    for (int n = 0; n < ArraySize; ++n) 
    { 
        int pos = rand() % ArraySize;
        temp = numbers[n];
        numbers[n] = numbers[pos];
        numbers[pos] = temp;
        // swap(numbers[n], numbers[pos]); 
    }
        target[0] = numbers[0] ;
        target[1] = numbers[1] ;
        target[2] = numbers[2] ;
        target[3] = numbers[3] ;    
}



void clear_str(){
    for(int i = 0; i < 10 ; i++)
        str[i] = '\0';
    return;
}


void setLight(int value) {
    LATB = value;
    clear_str();
    ClearBuffer(); 
    return;
}

int check_repeat_num(char* num){
    for(int i = 0; i < 4; i++){
        for(int j = i+1; j < 4; j++){
            if (num[i] == num[j]) return 1;
        }
    }
    return 0;
}

void calculate_AB(char* num)
{
    if(check_repeat_num(num)){
        UART_Write_Text("Repeat!!\r\n");
        return;
    }
    int count[2] = {0, 0};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if (i == j && num[i] == target[j]) {
                count[0]++;
                break;
            } else if (i != j && num[i] == target[j]) {
                count[1]++;
                break;
            }
        }
    }
    char A[2], B[2];
    char AB[7];
    sprintf(A, "%d", count[0]);
    sprintf(B, "%d", count[1]);
    sprintf(AB, "%d", count[0]*8 + count[1]);
    UART_Write_Text(AB);
    UART_Write_Text("\r\n");
    UART_Write_Text(A);
    UART_Write_Text("A ");
    UART_Write_Text(B);
    UART_Write_Text("B\r\n");
    
    setLight(count[0]*8 + count[1]);
    
}

void main(void) 
{
    random_number();  // produce a random number
    SYSTEM_Initialize() ;
    UART_Write_Text(target);
    
    while(1) {
        strcpy(str, GetString()); // TODO : GetString() in uart.c
        if (str[4]=='\r'){
            calculate_AB(str);
            clear_str();
            ClearBuffer();
        }
        else{
            for(int i = 0; i <= 3; i++) {
                if (str[i] == '\r') {
                    UART_Write_Text("Error!!\r\n");
                    clear_str();
                    ClearBuffer();
                }
            }
            for(int i = 5; i < strlen(str); i++) {
                if (str[i] == '\r') {
                    UART_Write_Text("Error!!\r\n");
                    clear_str();
                    ClearBuffer();
                }
            }
        }
    }
    return;
}

void __interrupt(high_priority) Hi_ISR(void)
{
    //Timer1
    PIR1bits.TMR1IF = 0;
    TMR1H = 0x0b;
    TMR1L = 0xdb;
    if(a < 0x12){
         a = a+1;
    }
    CCPR1L = a;  // degree of motor
    
    return;
}