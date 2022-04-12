#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
#include<Windows.h>

#define maxface 6
#define maxrow 3
#define maxcol 3

//structures
typedef struct Node{
	int data;
	struct Node* next;
}Node;
typedef struct Queue 
{
	struct Node* front;
	struct Node* back;
	int num;
	int total;
}Queue;

//display functions
void state(int array[maxface][maxrow][maxcol]); //check the current state of cube
void printcolor(int num); //prints the color
void textcolor(int color); //text color

//queue functions
void initialize(Queue* q); //initialize queue
int isEmpty(Queue* q); // check whether the queue is empty,empty on 1
int enqueue(Queue* q, int val);// enqueue, return 1 upon success
int dequeue(Queue* q);//dequeue, return 0 when empty list, return 1 upon sucess
int peek(Queue* q); //peek, return 0 when empty list,else return peeked value


//move functions
void R(int array[maxface][maxrow][maxcol]);  //R move
void Rp(int array[maxface][maxrow][maxcol]); //Rprime
void L(int array[maxface][maxrow][maxcol]);  //L move
void Lp(int array[maxface][maxrow][maxcol]); //Lprime
void U(int array[maxface][maxrow][maxcol]);  //U move
void Up(int array[maxface][maxrow][maxcol]); //Uprime
void D(int array[maxface][maxrow][maxcol]);  //D move
void Dp(int array[maxface][maxrow][maxcol]); //Dprime
void F(int array[maxface][maxrow][maxcol]);  //F move
void Fp(int array[maxface][maxrow][maxcol]); //Fprime
void B(int array[maxface][maxrow][maxcol]);  //B move
void Bp(int array[maxface][maxrow][maxcol]); //Bprime
void M(int array[maxface][maxrow][maxcol]);  //M move
void Mp(int array[maxface][maxrow][maxcol]); //Mprime
void E(int array[maxface][maxrow][maxcol]);  //E move
void Ep(int array[maxface][maxrow][maxcol]); //Eprime
void S(int array[maxface][maxrow][maxcol]);  //S move
void Sp(int array[maxface][maxrow][maxcol]); //Sprime
void fixsideCW(int sidenum, int array[maxface][maxrow][maxcol]); //rotate the side face,CW
void fixsideCCW(int sidenum, int array[maxface][maxrow][maxcol]); //rotate the side face,CCW

//Solve functions
void scramble(int array[maxface][maxrow][maxcol]); //scrambles the cube with 20 moves, also prints out each move
int edgesolve(int array[maxface][maxrow][maxcol]); //solve edges,return number of swaps
void cornersolve(int array[maxface][maxrow][maxcol]); //solve corners
int checkedge(int array[maxface][maxrow][maxcol]); //check whether edges have been solved, return 1 upon solved
int checkcorner(int array[maxface][maxrow][maxcol]); //check whether corners have been solved, return 1 upon solved
int edgecode(int array[maxface][maxrow][maxcol], int code); //base on current swap get next edge swap
int cornercode(int array[maxface][maxrow][maxcol], int code); //base on current swap get next corner swap
void edgemove(Queue* turns, int array[maxface][maxrow][maxcol]);   //dequeue the queue made from edgecode and perform edge fixes
void cornermove(Queue* moves, int array[maxface][maxrow][maxcol]); //dequeue the queue made from cornercode and perform corner fixes
void edgenewcyle(int array[maxface][maxrow][maxcol], int* i, int* j); //find an unsolved edge as new buffer and store the buffer as i and j 
void cornernewcyle(int array[maxface][maxrow][maxcol], int* i, int* j, int* k); //find an unsolved corner as new buffer and store the buffer as i, j and k
void Yperm(int array[maxface][maxrow][maxcol]);//perfroms a partial Yperm aka corner swap
void Tperm(int array[maxface][maxrow][maxcol]);//perfroms Tperm aka edge swap
void parity(int array[maxface][maxrow][maxcol]); //solves parity through Ra perm
