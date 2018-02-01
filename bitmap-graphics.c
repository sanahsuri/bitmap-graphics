/***********************************************************************
 * Homework: Bitmap Graphics
 ***********************************************************************/

#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>

// defining macros
#define DTYPE unsigned long
#define DSIZE (sizeof(DTYPE) * 8)
#define DFRMT "%lu"

// function declarations
DTYPE moveLeft(DTYPE num);
DTYPE moveRight(DTYPE num);
DTYPE makeComplement(DTYPE num);
void rowTransform(DTYPE pfunc(DTYPE), DTYPE arr[]);
void bitUpwardShift(DTYPE binArray[]);
void bitDownwardShift(DTYPE binArray[]);
void drawBits(DTYPE arr[]);

int
main (void)
{
  DTYPE binArray[DSIZE];
  char option;
  printf("Enter image rows:\n");
  for (int i = 0; i < DSIZE; i++)
  {
    scanf(DFRMT, &binArray[i]);
  } // user input for image rows

  while (1)
    {
      printf("Menu Options\n");
      printf("  I - Enter a new image\n");
      printf("  C - Image complement\n");
      printf("  L - Shift image left\n");
      printf("  R - Shift image right\n");
      printf("  U - Shift image up\n");
      printf("  D - Shift image down\n");
      printf("  P - Print image to screen\n");
      printf("  Q - Quit\n");
      printf("Enter option:\n");

      scanf(" %c", &option);
      switch (tolower(option))
        {
         case 'i':
           printf("Enter image rows: \n");
           for (int i = 0; i < DSIZE; i++)
           {
             scanf(DFRMT, &binArray[i]);
           } // puts image rows into 1D array
           break;
         case 'c':
          rowTransform(makeComplement, binArray);
          break;
         case 'l':
           rowTransform(moveLeft, binArray);
           break;
         case 'r':
           rowTransform(moveRight, binArray);
           break;
         case 'u':
           bitUpwardShift(binArray);
           break;
         case 'd':
           bitDownwardShift(binArray);
           break;
         case 'p':
           drawBits(binArray);
          break;
        case 'q':
          printf("Program terminated.\n");
          return 0;
         default:
          printf("Invalid input. Try again.\n");
          continue;
        } // switch
    } // while(1)
}// main

/*  barrel shifts num to the left by 1
 *    preconditions:
 *          num must be DTYPE
 *    postconditions:
 *          returns DTYPE lbarrel
 */
DTYPE
moveLeft(DTYPE num)
{
  DTYPE lbarrel;
  lbarrel = (num << 1L) | (num >> (DSIZE-1));
  return lbarrel;
} // moveLeft

/*  barrel shifts num to the right by 1
 *    preconditions:
 *          num must be DTYPE
 *    postconditions:
 *          returns DTYPE rbarrel
 */
DTYPE
moveRight(DTYPE num)
{
  DTYPE rbarrel;
  rbarrel = (num >> 1L) | (num << (DSIZE-1));
  return rbarrel;
} // moveRight

/*  flips the 1s and 0s in the bitwise representation of num
 *    preconditions:
 *          num must be DTYPE
 *    postconditions:
 *          returns ones complement of num
 */
DTYPE
makeComplement(DTYPE num)
{
  return (~ num);
} // makeComplement

/*  applies input function to each element of input array
 *    preconditions:
 *          pfunc must be a pointer to a function that accepts
 *          and returns a DTYPE
 *          arr must be an array of type DTYPE
 *    postconditions:
 *          no additional
 */
void
rowTransform(DTYPE pfunc(DTYPE), DTYPE arr[])
{
  for (int i = 0; i < DSIZE; i++)
  {
    arr[i] = pfunc(arr[i]);
  }
} // rowTransform

/*  shifts the image up by barrel shifting the elements of the
 *  input array up
 *    preconditions:
 *          binArray must be an array of type DTYPE
 *    postconditions:
 *          no additional
 */
void
bitUpwardShift(DTYPE binArray[])
{
  unsigned int copyArray[DSIZE];

  for (int j = 0; j < DSIZE; j++)
  {
    copyArray[j]=binArray[j];
  }

  binArray[DSIZE-1]=copyArray[0];
  for (int i = 0; i <DSIZE-1; i++)
  {
    binArray[i] = copyArray[i+1];
  }
}  // bitUpwardShift

/*  shifts the image down by barrel shifting the elements of the
 *  input array down
 *    preconditions:
 *          binArray must be an array of type DTYPE
 *    postconditions:
 *          no additional
 */
void
bitDownwardShift(DTYPE binArray[])
{
  unsigned int copyArray[DSIZE];

  for (int j = 0; j < DSIZE; j++)
  {
    copyArray[j]=binArray[j];
  }

  binArray[0]=copyArray[DSIZE-1];
  for (int i = 1; i < DSIZE; i++)
  {
    binArray[i] = copyArray[i-1];
  }
} // bitDownwardShift

/*  using bitwise & and left shift drawBits compares each
 *  element of input array with 1 shifted incrementally in
 *  array
 *  * is printed if the result is 1 and a space is
 *  printed if the result is 0
 *    preconditions:
 *          arr must be an array of type DTYPE
 *    postconditions:
 *          no additional
 */
void
drawBits(DTYPE arr[])
{
  for (int i = 0; i < DSIZE; i++)
  {
    int n=DSIZE-1;
    for (int j = 0; j < DSIZE; j++)
    {
    if (arr[i] & 1L << n)
      printf("*");
    else
      printf(" ");
    n--;
    }
    printf("\n");
  }
} // drawBits
