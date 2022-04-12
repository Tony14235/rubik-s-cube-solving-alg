#include "rubiks.h"
/*improve scramble*/
/*improve printing*/

int edgesolve(int array[maxface][maxrow][maxcol]) //solve all edges
{
	Queue turns;
	initialize(&turns);
	int code = array[4][1][2] * 10 + array[3][0][1];//buffer piece B,M
	int newbuffer1 = 0;
	int newbuffer2 = 0;
	int* i = &newbuffer1;
	int* j = &newbuffer2;
	int cycles = 0;

	printf("EDGESOLVE MOVES: ");
	
	while (checkedge(array) != 1) //while not solved
	{
		if (cycles == 0)//starting a cycle
		{
			while (code != 43 && code != 34) //while not a buffer swap
			{
				enqueue(&turns, code); //store the move
				code = edgecode(array, code); //get next move				
			}
			edgemove(&turns, array); //dequeue and perform move
			cycles++; //go to new cycles
		}
		else   //new cycles,cannot have buffer swap here 
		{
			edgenewcyle(array, i, j);  //i,j for the 2 configurations of the newbuffer
			code = (*i);                    //first move for new cycle
			enqueue(&turns, code);          //store the move
			code = edgecode(array, code); //get next move	

			while (code != *i && code != *j)
			{
				enqueue(&turns, code);
				code = edgecode(array, code); //get next move	
			}

			enqueue(&turns, code);        //move for the same piece
			edgemove(&turns, array); //dequeue and perform move
		}
	} 
	printf("\n\n");
	return turns.total;
}

int checkedge(int array[maxface][maxrow][maxcol])//check whether edges have been solved, return 1 upon solved
{
	for (int i = 0;i < 6;i++)
	{
		if (array[i][0][1] != i || array[i][1][0] != i || array[i][1][2] != i || array[i][2][1] != i)
		{
			return 0;
		}
	}
	return 1;
}

int edgecode(int array[maxface][maxrow][maxcol], int code) //base on color get next swap
{
	switch (code)
	{
	case(42):      //A swap,yellow orange
		code = array[4][0][1] * 10 + array[2][2][1];
		break;
	case(24):    //Q swap,orange yellow
		code = array[2][2][1] * 10 + array[4][0][1];
		break;

	case(40):      //C swap,yellow red
		code = array[4][2][1] * 10 + array[0][0][1];
		break;
	case(4):    //I swap,red yellow
		code = array[0][0][1] * 10 + array[4][2][1];
		break;

	case(41):    //D swap
		code = array[4][1][0] * 10 + array[1][0][1];
		break;
	case(14):    //E swap,blue yellow
		code = array[1][0][1] * 10 + array[4][1][0];
		break;

	case(10):    //F swap,blue red
		code = array[1][1][2] * 10 + array[0][1][0];
		break;
	case(1):    //L swap,red blue
		code = array[0][1][0] * 10 + array[1][1][2];
		break;

	case(15):    //G swap,blue white
		code = array[1][2][1] * 10 + array[5][1][0];
		break;
	case(51):    //X swap,white blue
		code = array[5][1][0] * 10 + array[1][2][1];
		break;

	case(12):    //H swap,blue orange
		code = array[1][1][0] * 10 + array[2][1][0];
		break;
	case(21):    //R swap,orange blue
		code = array[2][1][0] * 10 + array[1][1][0];
		break;

	case(3):    //J swap,red green
		code = array[0][1][2] * 10 + array[3][1][0];
		break;
	case(30):    //P swap,green red
		code = array[3][1][0] * 10 + array[0][1][2];
		break;

	case(5):    //K swap,red white
		code = array[0][2][1] * 10 + array[5][0][1];
		break;
	case(50):    //U swap,white red
		code = array[5][0][1] * 10 + array[0][2][1];
		break;

	case(32):    //N swap,green orange
		code = array[3][1][2] * 10 + array[2][1][2];
		break;
	case(23):    //T swap,orange green
		code = array[2][1][2] * 10 + array[3][1][2];
		break;

	case(35):    //O swap,green white
		code = array[3][2][1] * 10 + array[5][1][2];
		break;
	case(53):    //V swap,white green
		code = array[5][1][2] * 10 + array[3][2][1];
		break;

	case(25):    //S swap,orange white
		code = array[2][0][1] * 10 + array[5][2][1];
		break;
	case(52):    //W swap,white orange
		code = array[5][2][1] * 10 + array[2][0][1];
		break;
	}
	return code;
}

void edgemove(Queue* turns, int array[maxface][maxrow][maxcol])   //perform edge fixes
{
	int code = 0;
	//dequeue moves and perform them
	while (isEmpty(turns) != 1)
	{
		code = peek(turns);
		printf("%d ", code);
		dequeue(turns);
		switch (code)
		{
		case(42):      //A swap,yellow orange
			L(array);
			M(array);
			L(array);
			M(array);
			Dp(array);
			L(array);
			M(array);
			L(array);
			M(array);
			Tperm(array);
			L(array);
			M(array);
			L(array);
			M(array);
			D(array);
			L(array);
			M(array);
			L(array);
			M(array);
			break;
		case(40):      //C swap,yellow red
			L(array);
			M(array);
			L(array);
			M(array);
			D(array);
			L(array);
			M(array);
			L(array);
			M(array);
			Tperm(array);
			L(array);
			M(array);
			L(array);
			M(array);
			Dp(array);
			L(array);
			M(array);
			L(array);
			M(array);
			break;
		case(41):    //D swap
			Tperm(array);
			break;
		case(14):    //E swap,blue yellow
			L(array);
			Dp(array);
			Ep(array);
			L(array);
			Tperm(array);
			Lp(array);
			D(array);
			E(array);
			Lp(array);
			break;
		case(10):    //F swap,blue red
			Dp(array);
			Ep(array);
			L(array);
			Tperm(array);
			Lp(array);
			D(array);
			E(array);
			break;
		case(15):    //G swap,blue white
			Lp(array);
			Dp(array);
			Ep(array);
			L(array);
			Tperm(array);
			Lp(array);
			D(array);
			E(array);
			L(array);
			break;
		case(12):    //H swap,blue orange
			D(array);
			E(array);
			Lp(array);
			Tperm(array);
			L(array);
			Dp(array);
			Ep(array);
			break;
		case(4):    //I swap,red yellow
			L(array);
			Mp(array);
			Dp(array);
			L(array);
			L(array);
			Tperm(array);
			L(array);
			L(array);
			D(array);
			M(array);
			Lp(array);
			break;
		case(3):    //J swap,red green
			D(array);
			E(array);
			D(array);
			E(array);
			L(array);
			Tperm(array);
			Lp(array);
			Ep(array);
			Dp(array);
			Ep(array);
			Dp(array);
			break;
		case(5):    //K swap,red white
			L(array);
			Mp(array);
			D(array);
			L(array);
			L(array);
			Tperm(array);
			L(array);
			L(array);
			Dp(array);
			M(array);
			Lp(array);
			break;
		case(1):    //L swap,red blue
			Lp(array);
			Tperm(array);
			L(array);
			break;
		case(32):    //N swap,green orange
			D(array);
			E(array);
			L(array);
			Tperm(array);
			Lp(array);
			Dp(array);
			Ep(array);
			break;
		case(35):    //O swap,green white
			Dp(array);
			L(array);
			Mp(array);
			D(array);
			L(array);
			L(array);
			Tperm(array);
			Lp(array);
			Lp(array);
			Dp(array);
			M(array);
			Lp(array);
			D(array);
			break;
		case(30):    //P swap,green red
			Dp(array);
			Ep(array);
			Lp(array);
			Tperm(array);
			L(array);
			D(array);
			E(array);
			break;
		case(24):    //Q swap,orange yellow
			Lp(array);
			M(array);
			D(array);
			L(array);
			L(array);
			Tperm(array);
			Lp(array);
			Lp(array);
			Dp(array);
			Mp(array);
			L(array);
			break;
		case(21):    //R swap,orange blue
			L(array);
			Tperm(array);
			Lp(array);
			break;
		case(25):    //S swap,orange white
			Lp(array);
			M(array);
			Dp(array);
			L(array);
			L(array);
			Tperm(array);
			Lp(array);
			Lp(array);
			D(array);
			Mp(array);
			L(array);
			break;
		case(23):    //T swap,orange green
			D(array);
			E(array);
			D(array);
			E(array);
			Lp(array);
			Tperm(array);
			L(array);
			Dp(array);
			Ep(array);
			Dp(array);
			Ep(array);
			break;
		case(50):    //U swap,white red
			Dp(array);
			L(array);
			L(array);
			Tperm(array);
			L(array);
			L(array);
			D(array);
			break;
		case(53):    //V swap,white green
			Dp(array);
			Dp(array);
			L(array);
			L(array);
			Tperm(array);
			L(array);
			L(array);
			D(array);
			D(array);
			break;
		case(52):    //W swap,white orange
			D(array);
			L(array);
			L(array);
			Tperm(array);
			L(array);
			L(array);
			Dp(array);
			break;
		case(51):    //X swap,white blue
			L(array);
			L(array);
			Tperm(array);
			L(array);
			L(array);
			break;
		}
	}
}



void edgenewcyle(int array[maxface][maxrow][maxcol],int* i,int* j) //setup newcycle
{
	if (array[4][0][1] != 4 || array[2][2][1] != 2)
	{
		*i = array[4][0][1] * 10 + array[2][2][1];
		*j = array[2][2][1] * 10 + array[4][0][1];
		return;
	}
	if (array[4][1][0] != 4 || array[1][0][1] != 1)
	{
		*i = array[4][1][0] * 10 + array[1][0][1];
		*j = array[1][0][1] * 10 + array[4][1][0];
		return;
	}
	if (array[4][2][1] != 4 || array[0][0][1] != 0)
	{
		*i = array[4][2][1] * 10 + array[0][0][1];
		*j = array[0][0][1] * 10 + array[4][2][1];
		return;
	}
	if (array[0][1][0] != 0 || array[1][1][2] != 1)
	{
		*i = array[0][1][0] * 10 + array[1][1][2];
		*j = array[1][1][2] * 10 + array[0][1][0];
		return;
	}
	if (array[1][1][0] != 1 || array[2][1][0] != 2)
	{
		*i = array[1][1][0] * 10 + array[2][1][0];
		*j = array[2][1][0] * 10 + array[1][1][0];
		return;
	}
	if (array[0][1][2] != 0 || array[3][1][0] != 3)
	{
		*i = array[0][1][2] * 10 + array[3][1][0];
		*j = array[3][1][0] * 10 + array[0][1][2];
		return;
	}
	if (array[3][1][2] != 3 || array[2][1][2] != 2)
	{
		*i = array[3][1][2] * 10 + array[2][1][2];
		*j = array[2][1][2] * 10 + array[3][1][2];
		return;
	}
	if (array[3][2][1] != 3 || array[5][1][2] != 5)
	{
		*i = array[3][2][1] * 10 + array[5][1][2];
		*j = array[5][1][2] * 10 + array[3][2][1];
		return;
	}
	if (array[0][2][1] != 0 || array[5][0][1] != 5)
	{
		*i = array[0][2][1] * 10 + array[5][0][1];
		*j = array[5][0][1] * 10 + array[0][2][1];
		return;
	}
	if (array[1][2][1] != 1 || array[5][1][0] != 5)
	{
		*i = array[1][2][1] * 10 + array[5][1][0];
		*j = array[5][1][0] * 10 + array[1][2][1];
		return;
	}
	if (array[2][0][1] != 2 || array[5][2][1] != 5)
	{
		*i = array[2][0][1] * 10 + array[5][2][1];
		*j = array[5][2][1] * 10 + array[2][0][1];
		return;
	}
}

void Tperm(int array[maxface][maxrow][maxcol])//perfroms Tperm aka edge swap
{
	R(array);
	U(array);
	Rp(array);
	Up(array);
	Rp(array);
	F(array);
	R(array);
	R(array);
	Up(array);
	Rp(array);
	Up(array);
	R(array);
	U(array);
	Rp(array);
	Fp(array);
}