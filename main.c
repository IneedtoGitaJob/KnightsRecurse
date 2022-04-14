/*
Andreas Hinsch
UCF-COP3502 Spring 0001
Program 3: KnightsRecurse
3/15/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
double KnightsMultiply(int Bottom, int Top);
double KnightsMultiplyWrapper(FILE * fptr, FILE * ptr);

int KnightsFlip(char *array, int control, int location, int LocOrig, FILE * ptr);
void KnightsFlipWrapper(FILE * fptr, FILE * ptr);

int KnightsShape(int width, int control, int control2,FILE * ptr);
int KnightsShapeWrapper(FILE * fptr, FILE * ptr);

int KnightsScotch(int start, int length,int location, int  *array, int hold);
int KnightsScotchWrapper(FILE * fptr, FILE * ptr);

int KnightsDepot(int *array,int max_size, int length, int control, int answer);
int KnightsDepotWrapper(FILE * fptr, FILE * ptr);

//fills in an array with integers read in
int KnightsintFills(int length, int *array, FILE * fptr);

//Fills in an array with Ks
char KnightscharFills(int length, char *array);


void ExchangeCharacters(char *array, int i, int j);

int main()
{
    //The command of size 15 the longest a command can be
    char command[16];

    //opens input file
FILE*fptr;

fptr = fopen("KnightsRecurse.in", "r");

//opens output file
FILE*ptr;

ptr = fopen("KnightsRecurse.out", "w");

//read until end of file
while(fscanf(fptr, "%s", command) != EOF){
//Takes in the command

if(strcmp(command,"KnightsMultiply") == 0){
//Determines the value
    KnightsMultiplyWrapper(fptr, ptr);

}
if(strcmp(command,"KnightsScotch") == 0){
//Determines if it is solvable
KnightsScotchWrapper(fptr, ptr);
}

if(strcmp(command,"KnightsDepot") == 0){
//Determines the minimum number of 2x4s the students need
        KnightsDepotWrapper(fptr, ptr);
}
if(strcmp(command,"KnightsShape") == 0){
//Determines A X

        KnightsShapeWrapper(fptr, ptr);
}
if(strcmp(command,"KnightsFlip")== 0){
//prints all combinations given the number of trials
    KnightsFlipWrapper(fptr, ptr);
}

}



    return 0;
}
double KnightsMultiplyWrapper(FILE * fptr, FILE *ptr){
    //the answer
 double output;

 //Bottom number
 int Bottom;

 //Top number
 int Top;

    //Gets the Bottom number
fscanf(fptr, "%d", &Bottom);

//gets the Top number
fscanf(fptr, "%d", &Top);

output = KnightsMultiply(Bottom, Top);

fprintf(ptr, "Knights Multiply: %.0lf\n\n", output);

return 0;
}


double KnightsMultiply(int Bottom, int Top){


if(Bottom == Top){
    return Top;
}
else{
//Implements Recursion
return (Bottom * KnightsMultiply(Bottom + 1, Top));

}
}


int KnightsFlip(char *array, int control, int location, int LocOrig, FILE *ptr){

//if all permutations are done
if(control == pow(2,location+1)-1){
    return 1;
}


//if last char in array is K make it F
if(array[location] == 'K'){
    array[location] = 'F';
}
else{
//if last char in array is F but there is a K next to it swap F and K
   if(array[location] == 'F'){

    if(array[location-1] == 'K'){

     array[location] = 'K';

     array[location-1] = 'F';

    }
    else{
//If Last char in array is F and the char to the left is also a F traverse the array until an F has a K to its left, turn all traversed chars into K, turn the K to the leftmost F into an F
            while(array[location-1] == 'F'){
                array[location] = 'K';
                location--;

            }

        array[location] = 'K';

        array[location-1] = 'F';

    }

   }
}

//Print the array
for(int x = 0; x < LocOrig+1;x++){
    fprintf(ptr, "%c", array[x]);
}

fprintf(ptr, "\n");

location = LocOrig;

//Implements recursion
KnightsFlip(array, control + 1, location, LocOrig, ptr);
}

void KnightsFlipWrapper(FILE * fptr, FILE *ptr){

    //scan in number of combinations per session
    int length;

    fscanf(fptr, "%d", &length);

    //control variable for the location in the array
    int location = length-1;

    //Variable use to make location return to the origin
    int LocOrig = location;

    //Used to end the recursive program when all permutations are complete
    int control = 0;

    //allocates memory
    char *array = malloc(length * sizeof(char));

    //Fills the array with Ks
*array = KnightscharFills(length, array);

//Prints out the base case
fprintf(ptr, "KnightsFlip: \n");
for(int x = 0; x < LocOrig+1;x++){
    fprintf(ptr, "%c", array[x]);
}
fprintf(ptr, "\n");

    KnightsFlip(array, control, location, LocOrig, ptr);
    fprintf(ptr, "\n");
}

int KnightsShape(int width, int control, int control2,FILE* ptr){

//ends the function
if(control < -2 && control2 == 1){

        return 1;
}

//The number of spaces between a Line of Xs is equal to the current input - 2
int num_spaces = width - 2;

//If not the middle
if(width > 1){
fprintf(ptr, "X");

//prints out a number of spaces and the Succeding X
for(int c = 0 ;c < num_spaces; c++){

        fprintf(ptr, " ");
        }



    fprintf(ptr, "X\n");



//Indents
for(int c = 0; c <= control; c++){

    fprintf(ptr, " ");}
}
//If the middle only print an X
else{
        control = control - 2;
       fprintf(ptr, "X\n");



//Indents
for(int c = 0; c <= control; c++){

    fprintf(ptr, " ");}


}

//Recursion
if(width > 1 && control2 == 0){
return KnightsShape(width-2, control+1, control2, ptr);
}
else{
        return KnightsShape(width+2, control-1, 1, ptr);}

}

int KnightsShapeWrapper(FILE * fptr, FILE* ptr){
    //width of the X
int width;

//control variables used to give the X its shape
int control = 0;
int control2 = 0;


fscanf(fptr, "%d", &width);
fprintf(ptr, "KnightsShape:\n");

KnightsShape(width, control, control2, ptr);
fprintf(ptr, "\n");
}

int KnightsScotch(int start, int length, int location, int *array, int hold){

//If we are at zero in the array the array is solvable
if(array[location] == 0){
    return 1;
}

//If we can move to the left, move to the left
        if(location - array[location]  > 0){
//If in an infinite loop
if(array[location - array[location]] == array[location] ){
    return 0;
}
    location = location - array[location];

        }
//If we cant move to the right or to the left the array is not solvable and returns a 0

//If we can move to the right, move to the right
if(location + array[location] < length){

    location = location + array[location];
}
else{return 0;}



//Implements recursion
KnightsScotch(start, length, location, array, hold);
}

int KnightsScotchWrapper(FILE * fptr, FILE * ptr){
    //start point
    int start;

    //length of the array
    int length;

    //location in the array
    int location;

    //1 or 0 if it is solvable or not
    int output;

int hold = 0;

    //Gets the starting point
fscanf(fptr, "%d", &start);

location = start;
//gets the length of the array
fscanf(fptr, "%d", &length);

int *array = malloc(length * sizeof(int));

 *array = KnightsintFills(length, array, fptr);

 output = KnightsScotch(start, length, location, array, hold);

     if(output == 1){
        fprintf(ptr, "KnightsScotch: Solvable\n\n");

    }
    else{
        fprintf(ptr, "KnightsScotch: Not Solvable\n\n");

    }
free(array);
}

int KnightsDepot(int *array,int max_size, int length,int control, int answer){

//if total - the size of one 2x4 is still greater than zero increase answer and call the function again
if(control - max_size > 0){
control = control - max_size;

answer++;
}
else{
        if(control == 0){
            return answer;
       }
        else{
    answer++;
   return answer;
        }
}

//recursion
KnightsDepot(array, max_size, length, control, answer);
}

int KnightsDepotWrapper(FILE * fptr, FILE*ptr){
    //Size of a 2x4
int max_size;

//number of numbers in the array
int length;

//Amount of wood needed
int control = 0;

//the output
int output;

int answer = 0;

    //Gets the starting length of the boards
fscanf(fptr, "%d", &max_size);

//gets the length of the array
fscanf(fptr, "%d", &length);

int *array = malloc(length * sizeof(int));

*array = KnightsintFills(length, array, fptr);

//find how much wood is needed
for(int r =0; r < length;r++){

    control = control + array[r];

}

output = KnightsDepot(array, max_size, length, control, answer);

fprintf(ptr, "KnightsDepot: %d\n\n",output);
free(array);
return 0;
}

//Fills in an array
int KnightsintFills(int length, int *array, FILE * fptr){

//Fills in the array
for(int x = 0; x < length;x++){
fscanf(fptr, "%d", &array[x]);
}

return *array;
}


char KnightscharFills(int length, char *array){

//Fills in the array
for(int x = 0; x < length;x++){
array[x] = 'K';
}

return *array;


}
