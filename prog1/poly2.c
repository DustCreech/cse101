#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

//if c is plus return true
int  isPlus( char c ){
    if (c == '+'){
        return true;
    }
    return false;
}

//if c is a minus, return true
int isMinus(char c){
    if (c == '-'){
        return true;
    }
    return false;
}


//if c is in [a...z], return true
int isVar(char c){
    if (c >= 'a' && c <= 'z'){
	return true;
    }
    return false;
}

//if c is a power (^), return true
int isPower(char c){
    if (c == '^'){
	return true;
    }
    return false;
}

//if c is a space or a tab, return true
int isWhite(char c){
    if (c == ' ' || c == '\t'){
	return true;
    }
    return false;
}

int isNum(char c){
    if (c >= '0' && c <= '9'){
	return true;
    }
    return false;
}

//puts the polynomial in the correct order
void polyOrder(List degree, List coeff){
    List newDegree = newList();
    List newCoeff = newList();
    while (length(degree) > 0){
        int index = max(degree);
        int maxValue = delElement(degree, index); //deleting the max degree
	int coeffVal = delElement(coeff, index); //deleting the corresponding coefficient value
	appendList(newDegree, maxValue); //appending into a new list
	appendList(newCoeff, coeffVal);
    }
    
    while (length(newDegree) != 0){ //loop appends the contents back to the original list for later
	appendList(degree, delElement(newDegree, 0)); 
	appendList(coeff, delElement(newCoeff, 0));
    }
    freeList(&newDegree);
    freeList(&newCoeff);
     
}


//prints out the product of the two polys
void polyPrint(List degree, List coeff, char var){
    for(int i = 0; i != length(degree); i++){
	int degVal = delElement(degree, 0);
	int coefVal = delElement(coeff, 0);
	appendList(degree, degVal);
	appendList(coeff, coefVal);
	if (i == 0){
	    if (coefVal < 0 && coefVal != -1){
	        if (degVal > 1){
		    printf("-%d%c^%d ", coefVal * -1, var, degVal);
		} else if (degVal == 1){
		    printf("-%d%c ", coefVal * -1, var);
		} else {
		    printf("-%d ", coefVal * -1);
		}
	    } else if (coefVal == 1 || coefVal == -1){
		if (coefVal == -1){
		    if (degVal > 1){
                        printf("-%c^%d ", var, degVal);
                    } else if (degVal == 1){
                        printf("-%c ", var);
                    } else {
                        printf("-%d ", coefVal * -1);
                    }
		} else {
		    if (degVal > 1){
                        printf("%c^%d ", var, degVal);
                    } else if (degVal == 1){
                        printf("%c ", var);
                    } else {
                        printf("%d ", coefVal);
                    }
		}	

	    } else {
		if (degVal > 1){
                    printf("%d%c^%d ", coefVal, var, degVal);
                } else if (degVal == 1){
                    printf("%d%c ", coefVal, var);
                } else {
                    printf("%d ", coefVal);
                }
	    }
	} else if (i == length(degree) - 1){
	    if (coefVal < 0 && coefVal != -1){
		if (degVal > 1){
		    printf("- %d%c^%d\n", coefVal * -1, var, degVal);
		} else if (degVal == 1){
		    printf("- %d%c\n", coefVal * -1, var);
		} else {
		    printf("- %d\n", coefVal * -1);
		}
	    } else if (coefVal == 1 || coefVal == -1){
		if (coefVal == -1){
                    if (degVal > 1){
                        printf("- %c^%d\n", var, degVal);
                    } else if (degVal == 1){
                        printf("- %c\n", var);
                    } else {
                        printf("- %d\n", coefVal * -1);
                    }
                } else {
                    if (degVal > 1){
                        printf("+ %c^%d\n", var, degVal);
                    } else if (degVal == 1){
                        printf("+ %c\n", var);
                    } else {
                        printf("+ %d\n", coefVal);
                    }
                }	
	    } else {
		if (degVal > 1){
                    printf("+ %d%c^%d\n", coefVal, var, degVal);
                } else if (degVal == 1){
                    printf("+ %d%c\n", coefVal, var);
                } else {
                    printf("+ %d\n", coefVal);
                }
	    }
	} else {
	    if (coefVal < 0 && coefVal != -1){
                if (degVal > 1){
                    printf("- %d%c^%d ", coefVal * -1, var, degVal);
                } else if (degVal == 1){
                    printf("- %d%c ", coefVal * -1, var);
                } else {
                    printf("- %d ", coefVal * -1);
                }
		
            } else if (coefVal == 1 || coefVal == -1){
		if (coefVal == -1){
                    if (degVal > 1){
                        printf("- %c^%d ", var, degVal);
                    } else if (degVal == 1){
                        printf("- %c ", var);
                    } else {
                        printf("- %d ", coefVal * -1);
                    }
                } else {
                    if (degVal > 1){
                        printf("+ %c^%d ", var, degVal);
                    } else if (degVal == 1){
                        printf("+ %c ", var);
                    } else {
                        printf("+ %d ", coefVal);
                    }
                }		
		
	    } else {
                if (degVal > 1){
                    printf("+ %d%c^%d ", coefVal, var, degVal);
                } else if (degVal == 1){
                    printf("+ %d%c ", coefVal, var);
                } else {
                    printf("+ %d ", coefVal);
                }
            }
	}
    }
    
}

//function simplifies the polynomial
void polySimplify(List degree, List coeff, char var){
    List newDeg = newList();
    List newCoeff = newList();
    int sum;
    //int coefVal;
    while ( length(degree) > 0){ //iterates until an empty list 
        int maxIndex = max(degree); //max index
        int degVal = delElement(degree, maxIndex); //getting value of deg and corresponding coeff.
	int coefVal = delElement(coeff, maxIndex);
        //printf("max index: %d, maxvalue: %d\n", maxIndex, degVal);
	sum += coefVal; // will be the sum of the coefficients
	int findIndex = find(degree, degVal);
        printf("max index: %d, maxvalue: %d, findIndex: %d\n", maxIndex, degVal, findIndex);
	if (findIndex == -1){ // there is no more terms of the same degree
	    appendList(newDeg, degVal);
	    appendList(newCoeff, sum);
	    sum = 0;
	} 
    }
    polyPrint(newDeg, newCoeff, var);
}

//performs the poly multiplication and also prints the desired output
void polyMult(List degree, List coeff, List degree2, List coeff2, char var){
    List multDegree = newList(); //the degree list
    List multCoeff = newList(); //the coefficient list
    List cpyDegree = newList(); //a cpy for printing and simplifying
    List cpyCoeff = newList(); 
    int count = length(degree); //for the iterations
    int count2 = length(degree2);
    int index = 0;

    for( int i = count2; i != 0; i--){ //iterates through the lists in order to add the degree and mult. the coeff.
        int deg2val = delElement(degree2, 0); //deleting the 0th element due to the next element always moving to the 0th index
        int coef2val = delElement(coeff2, 0);
        for(int j = count; j != 0; j--){
            int degVal = delElement(degree, 0);
            int coefVal = delElement(coeff, 0);
            appendList(multDegree, deg2val + degVal); 
            appendList(multCoeff, coef2val * coefVal);
            appendList(cpyDegree, degVal);
            appendList(cpyCoeff, coefVal);
        }
        degree = cpyDegree; //setting the original lists as the copies
        coeff  = cpyCoeff;
    }
    polyPrint(multDegree, multCoeff, var);
    //printList(multDegree);
   // polySimplify(multDegree, multCoeff, var);
   printf("which simplifies to\n");
   polySimplify(multDegree, multCoeff, var);
}


//this function puts the degree and coefficient values into two separate lists
void getLists(List lineDegree, List lineCoeff, int len, char *line){
    for(int i = 0; i < len; i++){ //iterates through line
        if (isPower(line[i]) == true){ //this section gets the degree integer value
	    if (isNum(line[i+1]) == true && isNum(line[i+2]) == true && isNum(line[i+3]) == true && isNum(line[i+4]) == true && isNum(line[i+5]) == true){
	        int sum = ((line[i+1] - '0') * 10000) + ((line[i+2] - '0') * 1000) + ((line[i+3] - '0') * 100) + ((line[i+4] - '0') * 10) + (line[i+5] - '0');
	        appendList(lineDegree, sum);
	        i += 5;
            } else if (isNum(line[i+1]) == true && isNum(line[i+2]) == true && isNum(line[i+3]) == true && isNum(line[i+4]) == true && isNum(line[i+5]) == false){
                int sum = ((line[i+1] - '0') * 1000) + ((line[i+2] - '0') * 100) + ((line[i+3] - '0') * 10) + (line[i+4] - '0');
                appendList(lineDegree, sum);
	        i += 4;
            } else if (isNum(line[i+1]) == true && isNum(line[i+2]) == true && isNum(line[i+3]) == true && isNum(line[i+4]) == false){
                int sum = ((line[i+1] - '0') * 100) + ((line[i+2] - '0') * 10) + (line[i+3] - '0');
                appendList(lineDegree, sum);
	        i += 3;
	    } else if (isNum(line[i+1]) == true && isNum(line[i+2]) == true && isNum(line[i+3]) == false){
                int sum = ((line[i+1] - '0') * 10) + (line[i+2] - '0'); //adds the char by 0 in order to get the integer value
                appendList(lineDegree, sum);
	        i += 2;
	    } else if (isNum(line[i+1]) == true && isNum(line[i+2]) == false){
	        int sum = line[i+1] - '0';
                appendList(lineDegree, sum); //appends the degree to the degree list   
	    }
        } else if (isVar(line[i]) == true){ //this section gets me the coefficient of a term
	  
	    if (isPower(line[i+1]) == false){
	        appendList(lineDegree, '1' - '0'); //gets the degree of 1
	    }
	    if (i == 0){
	        appendList(lineCoeff, '1' - '0'); //there is no coefficient which means its 1
	    }
	    if (i == 1 && isMinus(line[i-1]) == true){ //there is no coefficient and a minus prior, which means its -1
	        appendList(lineCoeff, ('1' - '0') * -1);
	    }
	    if (isWhite(line[i-1]) == true && isMinus(line[i-2]) == false){
	        appendList(lineCoeff, '1' - '0');
	    } else if (isWhite(line[i-1]) == true && isMinus(line[i-2]) == true){ //gettig the coefficient values
                appendList(lineCoeff, ('1' - '0') * -1);
	    } else if (isNum(line[i-1]) == true && isNum(line[i-2]) == true && isNum(line[i-3]) == true && isNum(line[i-4]) == true && isNum(line[i-5]) == true){
	        int sum = ((line[i-5] - '0') * 10000) + ((line[i-4] - '0') * 1000) + ((line[i-3] - '0') * 100) + ((line[i-2] - '0') * 10) + (line[i-1] - '0');
	        if (isMinus(line[i-6]) == true || isMinus(line[i-7]) == true){
	            appendList(lineCoeff, sum * -1);
	        } else {
	            appendList(lineCoeff, sum);
	        }
	    } else if (isNum(line[i-1]) == true && isNum(line[i-2]) == true && isNum(line[i-3]) == true && isNum(line[i-4]) == true && isNum(line[i-5]) == false){
                int sum = ((line[i-4] - '0') * 1000) + ((line[i-3] - '0') * 100) + ((line[i-2] - '0') * 10) + (line[i-1] - '0');
                if (isMinus(line[i-5]) == true || isMinus(line[i-6]) == true){
                    appendList(lineCoeff, sum * -1);
                } else {
                    appendList(lineCoeff, sum);
	        }
            } else if (isNum(line[i-1]) == true && isNum(line[i-2]) == true && isNum(line[i-3]) == true && isNum(line[i-4]) == false){
                int sum = ((line[i-3] - '0') * 100) + ((line[i-2] - '0') * 10) + (line[i-1] - '0');
                if (isMinus(line[i-4]) == true || isMinus(line[i-5]) == true){
                    appendList(lineCoeff, sum * -1);
                } else {
                    appendList(lineCoeff, sum);
	        }
            } else if (isNum(line[i-1]) == true && isNum(line[i-2]) == true && isNum(line[i-3]) == false){
                int sum = ((line[i-2] - '0') * 10) + (line[i-1] - '0');
                if (isMinus(line[i-3]) == true || isMinus(line[i-4]) == true){
                    appendList(lineCoeff, sum * -1);
                } else {
                    appendList(lineCoeff, sum);
	        }
            } else if (isNum(line[i-1]) == true && isNum(line[i-2]) == false){
	        if ((isMinus(line[i-2]) == true || isMinus(line[i-3]) == true) && isNum(line[i-1]) == true){
	            appendList(lineCoeff, (line[i-1] - '0') * -1);
	        } else {
	            appendList(lineCoeff, line[i-1] - '0');
		
	        }
	    }
        } else if ((isMinus(line[i-1]) == true || isWhite(line[i-1]) == true || isVar(line[i+1]) == false) && isNum(line[i]) == true && isPower(line[i-1]) == false){
            if (isNum(line[i]) == true && isNum(line[i+1]) == true && isNum(line[i+2]) == true && isNum(line[i+3]) == true && isNum(line[i+4]) == true && isVar(line[i+5]) == false){ //this portion of the code is for terms without a degree
                int sum = ((line[i] - '0') * 10000) + ((line[i+1] - '0') * 1000) + ((line[i+2] - '0') * 100) + ((line[i+3] - '0') * 10) + (line[i+4] - '0');	
	        appendList(lineDegree, '0' - '0');
	        if ((isMinus(line[i-1]) == true || isMinus(line[i-2]) == true)){
	            appendList(lineCoeff, sum * -1);
		
	        } else {
	            appendList(lineCoeff, sum);
                }
	        i += 5;
            } else if (isNum(line[i]) == true && isNum(line[i+1]) == true && isNum(line[i+2]) == true && isNum(line[i+3]) == true && isNum(line[i+4]) == false && isVar(line[i+4]) == false){
                int sum = ((line[i] - '0') * 1000) + ((line[i+1] - '0') * 100) + ((line[i+2] - '0') * 10) + (line[i+3] - '0');
                appendList(lineDegree, '0' - '0');
                if ((isMinus(line[i-1]) == true || isMinus(line[i-2]) == true)){
                    appendList(lineCoeff, sum * -1);
                } else{
                    appendList(lineCoeff, sum);
	        }
	        i += 4;
            } else if (isNum(line[i]) == true && isNum(line[i+1]) == true && isNum(line[i+2]) == true && isNum(line[i+3]) == false && isVar(line[i+3]) == false){
                int sum = ((line[i] - '0') * 100) + ((line[i+1] - '0') * 10) + (line[i+2] - '0');
                appendList(lineDegree, '0' - '0');
	        if ((isMinus(line[i-1]) == true || isMinus(line[i-2]) == true) && find(lineCoeff, sum) != -1){
                    appendList(lineCoeff, sum * -1);
                } else { 
                    appendList(lineCoeff, sum);
	        }
	        i += 3;
            } else if (isNum(line[i]) == true && isNum(line[i+1]) == true && isNum(line[i+2]) == false && isVar(line[i+2]) == false){
                int sum = ((line[i] - '0') * 10) + (line[i+1] - '0');
                appendList(lineDegree, '0' - '0');
                if ((isMinus(line[i-1]) == true || isMinus(line[i-2]) == true)){
                    appendList(lineCoeff, sum * -1);
                } else {
                    appendList(lineCoeff, sum);  
	        }
	        i += 2;
            } else if (isNum(line[i]) == true && isNum(line[i+1]) == false && isVar(line[i+1]) == false){
                appendList(lineDegree, '0' - '0');
                if (isMinus(line[i-1]) == true || isMinus(line[i-2]) == true ){
                    appendList(lineCoeff, (line[i] - '0') * -1);
                } else {
                    appendList(lineCoeff, line[i] - '0');
	        }
            }
        }
    }
}

int main(void){
//printf("input string: %s\n", line);

int MAX_LEN = 1000;
char *line = (char *) calloc(MAX_LEN, sizeof(char));
char *line2 = (char *) calloc(MAX_LEN, sizeof(char));
//printf("enter something here:\n");
fgets(line, MAX_LEN, stdin); //gets the poly line from stdin
fgets(line2, MAX_LEN, stdin);
int len = strlen(line); //stores the len of the lines
int len2 = strlen(line2);
line[len-1] = '\0';
line2[len2-1] = '\0';
char lineVar;
for (int i = 0; i < len; i++){
    if (isVar(line[i]) == true){
	lineVar = line[i];
	break;
    }
}
printf("input string: %s\n", line);
printf("input string2: %s\n", line2);
List lineDegree = newList();
List lineCoeff = newList();
List line2Degree = newList();
List line2Coeff = newList();
getLists(lineDegree, lineCoeff, len, line);
getLists(line2Degree, line2Coeff, len2, line2);
//printList(lineDegree);
//printList(lineCoeff);
//printList(line2Degree);
//printList(line2Coeff);
polyOrder(lineDegree, lineCoeff);
polyOrder(line2Degree, line2Coeff);
polyPrint(lineDegree, lineCoeff, lineVar);
printf("multiply by\n");
polyPrint(line2Degree, line2Coeff, lineVar);
printf("is\n");
polyMult(lineDegree, lineCoeff, line2Degree, line2Coeff, lineVar);
//printf("which simplifies to\n");
//polySimplify(
//printList(lineDegree);
//printList(lineCoeff);
//printList(line2Degree);
//printList(line2Coeff);
//polyMult(lineDegree, lineCoeff, line2Degree, line2Coeff, lineVar, line, line2); 
//printList(lineDegree);
return 0;
}
