#include <stdio.h>

#define MATRIX_SIZE 16

float matrix[MATRIX_SIZE];
float sum[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
float determinant = 0.0f;

int main(void) {

    for(unsigned i = 0; i  < MATRIX_SIZE; ++i) {
        scanf("%f", &matrix[i]);
    }

    asm (
        "movups (%0), %%xmm0 \n\t"
        "movups (%1), %%xmm1 \n\t"
       
        "shufps $0x48 , %%xmm0, %%xmm0 \n\t"	//A'
        "shufps $0xb1 , %%xmm1, %%xmm1 \n\t"	//B'
        "mulps %%xmm0,%%xmm1 \n\t"				//A' * B'
       
        "movups (%0), %%xmm0 \n\t"    
        "movups (%1), %%xmm2 \n\t"
       
        "shufps $0xb1,%%xmm0,%%xmm0 \n\t"		//A"
        "shufps $0x48,%%xmm2,%%xmm2 \n\t"		//B"
        "mulps  %%xmm0,%%xmm2 \n\t"				//A" * B"
       
        "subps %%xmm1, %%xmm2 \n\t"				//A'B' - A"B"
       
        "movups (%2), %%xmm0 \n\t"     
        "movups (%3), %%xmm1 \n\t"       		
       
        "shufps $0x16 , %%xmm0, %%xmm0 \n\t"	//C'	
        "shufps $0xef , %%xmm1, %%xmm1 \n\t"	//D'
        "mulps %%xmm0,%%xmm1 \n\t"  			//C' * D'

        "movups (%2), %%xmm0 \n\t"
        "movups (%3), %%xmm3 \n\t"  
       
        "shufps $0xef,%%xmm0 ,%%xmm0 \n\t"   	//C"
        "shufps $0x16, %%xmm3, %%xmm3 \n\t"     //D"      
        "mulps  %%xmm0,%%xmm3 \n\t"             //C"*D"
       
        "subps %%xmm1, %%xmm3 \n\t"             //C'D' - C"D" 

        "mulps %%xmm2,%%xmm3 \n\t" 				//(A'B' - A"B") (C'D' - C"D")
   
        "movups (%0), %%xmm0     \n\t"      
        "movups (%1), %%xmm2 \n\t"
	    "shufps $0x0e , %%xmm0, %%xmm0  \n\t"   //A'
        "shufps $0x07 , %%xmm2, %%xmm2 \n\t"    //B'       
       
        "mulps %%xmm0, %%xmm2 \n\t"             //A' * B'  
       
        "movups (%0), %%xmm0 \n\t"                   
        "movups (%1), %%xmm4 \n\t"
		"shufps $0x07 , %%xmm0, %%xmm0 \n\t" 	//A"
        "shufps $0x0e , %%xmm4, %%xmm4 \n\t"    //B"    
       
        "mulps %%xmm0,%%xmm4 \n\t"              //A" * B"  
       
        "subps %%xmm4, %%xmm2 \n\t"             //A'B' - A"B"    
       
        "movups (%2), %%xmm0 \n\t"         
        "movups (%3), %%xmm4 \n\t"
	    "shufps $0x00 , %%xmm0, %%xmm0 \n\t"   	//C'
        "shufps $0x09 , %%xmm4, %%xmm4 \n\t"    //D'    
       
        "mulps %%xmm0, %%xmm4 \n\t"             //(A'B' - A"B")(C'D' - C"D")
       
        "movups (%2), %%xmm0 \n\t"        
        "movups (%3), %%xmm5 \n\t"
		"shufps $0x09 , %%xmm0, %%xmm0 \n\t"  	//C"
        "shufps $0x00 , %%xmm5, %%xmm5 \n\t"    //D"      
       
        "mulps %%xmm5,%%xmm0 \n\t"              //C" * D"  
       
        "subps %%xmm4, %%xmm0 \n\t"             //C'D' - C"D"    
       
        "mulps %%xmm0,%%xmm2 \n\t"              //(A'B' - A"B")(C'D' - C"D")
      
        "subps %%xmm2,%%xmm3 \n\t"              
        "movups %%xmm3,(%4) \n\t"
        :
        : "r" (matrix),"r" (&matrix[4]) , "r" (&matrix[8]), "r"(&matrix[12]), "r" (sum)
    );

    printf("Matrix determinant: %f \n", determinant);

    return 0;
}