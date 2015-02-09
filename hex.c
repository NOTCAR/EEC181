// Simple test program  
int main(void) 
{ 
 
volatile int * led  
 
= (int *) 0xFF200040;  // red LED address 
 
volatile int * switchptr   
= (int *) 0xFF200030;  // SW slider switch address 
 
 
int switch_value; 
 
 
while (1) 
 
{ 
 
 
switch_value = *(switchptr); 
 
 
*(led) = switch_value; 
 
} 
}

