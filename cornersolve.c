#include "rubiks.h"

void cornersolve(int array[maxface][maxrow][maxcol]) //solve corners
{
	Queue moves;
	initialize(&moves);
	int code = array[1][0][0] * 100 + array[4][0][0] * 10 + array[2][2][0];//in the form of blue(1),yellow(4),orange(2)
	int newbuffer1 = 0;
	int newbuffer2 = 0;
	int newbuffer3 = 0;
	int* i = &newbuffer1;
	int* j = &newbuffer2;
	int* k = &newbuffer3;
	int cycles = 0;

	printf("CORNERSOLVE MOVES: ");

	while (checkcorner(array) != 1)  //while not solved 
	{
		if(cycles == 0)//starting a cycle
		{
			while(code != 142 && code != 421 && code != 214 ) //while not a buffer swap
			{
				enqueue(&moves, code); //store the move
				code = cornercode(array, code); //get next move				
			}
			cornermove(&moves, array); //dequeue and perform move
			cycles++; //go to new cycles
		}
		else   //new cycles,cannot have buffer swap here 
		{
			cornernewcyle(array, i, j, k);  //i,j,k for the 3 configurations of the newbuffer
			code = (*i);                    //first move for new cycle
			enqueue(&moves, code);          //store the move
			code = cornercode(array, code); //get next move	

			while (code != *i && code != *j && code != *k) 
			{
				enqueue(&moves, code);
				code = cornercode(array, code); //get next move	
			}

			enqueue(&moves, code);        //move for the same piece
			cornermove(&moves, array); //dequeue and perform move
		}
	}
	printf("\n\n");
}

int checkcorner(int array[maxface][maxrow][maxcol]) //check whether corners have been solved, return 1 upon solved
{
	for (int i = 0;i < 6;i++)
	{
		if (array[i][0][0] != i || array[i][0][2] != i || array[i][2][2] != i || array[i][2][0] != i)
		{
			return 0;
		}
	}
	return 1;
}


int cornercode(int array[maxface][maxrow][maxcol], int code) //base on color get next swap
{
	switch (code)
	{
	case(432): //B
		code = array[4][0][2] * 100 + array[3][0][2] * 10 + array[2][2][2];
		break;
	case(324): //N
		code = array[3][0][2] * 100 + array[2][2][2] * 10 + array[4][0][2];
		break;
	case(243): //Q
		code = array[2][2][2] * 100 + array[4][0][2] * 10 + array[3][0][2];
		break;

	case(403): //C
		code = array[4][2][2] * 100 + array[0][0][2] * 10 + array[3][0][0];
		break;
	case(34): //J
		code = array[0][0][2] * 100 + array[3][0][0] * 10 + array[4][2][2];
		break;
	case(340): //M
		code = array[3][0][0] * 100 + array[4][2][2] * 10 + array[0][0][2];
		break;

	case(410): //D
		code = array[4][2][0] * 100 + array[1][0][2] * 10 + array[0][0][0];
		break;
	case(104): //F
		code = array[1][0][2] * 100 + array[0][0][0] * 10 + array[4][2][0];
		break;
	case(41): //I
		code = array[0][0][0] * 100 + array[4][2][0] * 10 + array[1][0][2];
		break;

	case(150): //G
		code = array[1][2][2] * 100 + array[5][0][0] * 10 + array[0][2][0];
		break;
	case(15): //L
		code = array[0][2][0] * 100 + array[1][2][2] * 10 + array[5][0][0];
		break;
	case(501): //U
		code = array[5][0][0] * 100 + array[0][2][0] * 10 + array[1][2][2];
		break;

	case(125): //H
		code = array[1][2][0] * 100 + array[2][0][0] * 10 + array[5][2][0];
		break;
	case(251): //S
		code = array[2][0][0] * 100 + array[5][2][0] * 10 + array[1][2][0];
		break;
	case(512): //X
		code = array[5][2][0] * 100 + array[1][2][0] * 10 + array[2][0][0];
		break;

	case(53): //K
		code = array[0][2][2] * 100 + array[5][0][2] * 10 + array[3][2][0];
		break;
	case(305): //P
		code = array[3][2][0] * 100 + array[0][2][2] * 10 + array[5][0][2];
		break;
	case(530): //V
		code = array[5][0][2] * 100 + array[3][2][0] * 10 + array[0][2][2];
		break;

	case(352): //O
		code = array[3][2][2] * 100 + array[5][2][2] * 10 + array[2][0][2];
		break;
	case(235): //T
		code = array[2][0][2] * 100 + array[3][2][2] * 10 + array[5][2][2];
		break;
	case(523): //W
		code = array[5][2][2] * 100 + array[2][0][2] * 10 + array[3][2][2];
		break;
	}
	return code;
}

void cornermove(Queue* moves, int array[maxface][maxrow][maxcol])    //perform corner fixes
{
	int code = 0;
	//dequeue moves and perform them
	while (isEmpty(moves) != 1)
	{
		code = peek(moves);
		printf("%d ", code);
		dequeue(moves);
		switch (code)
		{
		case(432):  //B swap,yellow green orange
			R(array);
			R(array);
			Yperm(array);
			R(array);
			R(array);
			break;
		case(403):  //C swap,yellow red green
			F(array);
			F(array);
			D(array);
			Yperm(array);
			Dp(array);
			F(array);
			F(array);
			break;
		case(410):  //D swap,yellow blue red
			F(array);
			F(array);
			Yperm(array);
			F(array);
			F(array);
			break;
		case(104):  //F swap, blue red yellow
			Fp(array);
			D(array);
			Yperm(array);
			Dp(array);
			F(array);
			break;
		case(150):  //G swap, blue white red 
			Fp(array);
			Yperm(array);
			F(array);
			break;
		case(125):  //H swap, blue orange white
			Dp(array);
			R(array);
			Yperm(array);
			Rp(array);
			D(array);
			break;
		case(41):  //I swap, red yellow blue
			F(array);
			Rp(array);
			Yperm(array);
			R(array);
			Fp(array);
			break;
		case(34):  //J swap, red green yellow
			Rp(array);
			Yperm(array);
			R(array);
			break;
		case(53):  //K swap, red white green
			Fp(array);
			Rp(array);
			Yperm(array);
			R(array);
			F(array);
			break;
		case(15):  //L swap, red blue white
			Fp(array);
			Fp(array);
			Rp(array);
			Yperm(array);
			R(array);
			F(array);
			F(array);
			break;
		case(340):  //M swap, green yellow red
			F(array);
			Yperm(array);
			Fp(array);
			break;
		case(324):  //N swap, green orange yellow
			Rp(array);
			F(array);
			Yperm(array);
			Fp(array);
			R(array);
			break;
		case(352):  //O swap, green white orange
			Rp(array);
			Rp(array);
			F(array);
			Yperm(array);
			Fp(array);
			R(array);
			R(array);
			break;
		case(305):  //P swap, green red white
			R(array);
			F(array);
			Yperm(array);
			Fp(array);
			Rp(array);
			break;
		case(243):  //Q swap, orange yellow green
			R(array);
			Dp(array);
			Yperm(array);
			D(array);
			Rp(array);
			break;
		case(251):  //S swap, orange white blue
			D(array);
			Fp(array);
			Yperm(array);
			F(array);
			Dp(array);
			break;
		case(235):  //T swap, orange green white
			R(array);
			Yperm(array);
			Rp(array);
			break;
		case(501):  //U swap, white red blue
			D(array);
			Yperm(array);
			Dp(array);
			break;
		case(530):  //V swap, white green red
			Yperm(array);
			break;
		case(523):  //W swap, white orange green
			Dp(array);
			Yperm(array);
			D(array);
			break;
		case(512):  //X swap, white blue orange
			D(array);
			D(array);
			Yperm(array);
			D(array);
			D(array);
			break;
		}
	}
}


void cornernewcyle(int array[maxface][maxrow][maxcol], int* i, int* j, int* k) //setup newcycle
{
	if (array[4][0][2] != 4 || array[3][0][2] != 3 || array[2][2][2] != 2) //1st
	{
		*i = array[4][0][2] * 100 + array[3][0][2] * 10 + array[2][2][2];
		*j = array[3][0][2] * 100 + array[2][2][2] * 10 + array[4][0][2];
		*k = array[2][2][2] * 100 + array[4][0][2] * 10 + array[3][0][2];
		return;
	}
	if (array[4][2][2] != 4 || array[0][0][2] != 0 || array[3][0][0] != 3)     //2nd
	{
		*i = array[4][2][2] * 100 + array[0][0][2] * 10 + array[3][0][0];
		*j = array[0][0][2] * 100 + array[3][0][0] * 10 + array[4][2][2];
		*k = array[3][0][0] * 100 + array[4][2][2] * 10 + array[0][0][2];
		return;
	}
	if (array[4][2][0] != 4 || array[1][0][2] != 1 || array[0][0][0] != 0)  //3rd
	{
		*i = array[4][2][0] * 100 + array[1][0][2] * 10 + array[0][0][0];
		*j = array[1][0][2] * 100 + array[0][0][0] * 10 + array[4][2][0];
		*k = array[0][0][0] * 100 + array[4][2][0] * 10 + array[1][0][2];
		return;
	}
	if (array[1][2][2] != 1 || array[5][0][0] != 5 || array[0][2][0] != 0) //4th
	{

		*i = array[1][2][2] * 100 + array[5][0][0] * 10 + array[0][2][0];
		*j = array[0][2][0] * 100 + array[1][2][2] * 10 + array[5][0][0];
		*k = array[5][0][0] * 100 + array[0][2][0] * 10 + array[1][2][2];
		return;
	}
	if (array[1][2][0] != 1 || array[2][0][0] != 2 || array[5][2][0] != 5) //5th
	{
		*i = array[1][2][0] * 100 + array[2][0][0] * 10 + array[5][2][0];
		*j = array[2][0][0] * 100 + array[5][2][0] * 10 + array[1][2][0];
		*k = array[5][2][0] * 100 + array[1][2][0] * 10 + array[2][0][0];
		return;
	}
	if (array[0][2][2] !=0 || array[5][0][2] !=5 || array[3][2][0] !=3) //6th
	{

		*i = array[0][2][2] * 100 + array[5][0][2] * 10 + array[3][2][0];
		*j = array[3][2][0] * 100 + array[0][2][2] * 10 + array[5][0][2];
		*k = array[5][0][2] * 100 + array[3][2][0] * 10 + array[0][2][2];
		return;
	}
	if (array[3][2][2] != 3 || array[5][2][2] !=5 || array[2][0][2] != 2) //7th
	{

		*i = array[3][2][2] * 100 + array[5][2][2] * 10 + array[2][0][2];
		*j = array[2][0][2] * 100 + array[3][2][2] * 10 + array[5][2][2];
		*k = array[5][2][2] * 100 + array[2][0][2] * 10 + array[3][2][2];
		return;
	}
}


void Yperm(int array[maxface][maxrow][maxcol])//perfroms a partial Yperm aka corner swap
{
	R(array);
	Up(array);
	Rp(array);
	Up(array);
	R(array);
	U(array);
	Rp(array);
	Fp(array);
	R(array);
	U(array);
	Rp(array);
	Up(array);
	Rp(array);
	F(array);
	R(array);
}