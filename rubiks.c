#include "rubiks.h"

int main() 
{
	int cube[6][3][3] = { {{0,0,0},{0,0,0},{0,0,0}},   //Red 
						   {{1,1,1},{1,1,1},{1,1,1}},   //BLUE
						   {{2,2,2},{2,2,2},{2,2,2}},   //Orange
						   {{3,3,3},{3,3,3},{3,3,3}},   //Green
						   {{4,4,4},{4,4,4},{4,4,4}},   //Yellow
						   {{5,5,5},{5,5,5},{5,5,5}}};  //White
	char cont;

	do
	{
		scramble(cube);
		printf("SCRAMBLED CUBE: \n");
		state(cube);

		int num = edgesolve(cube);
		printf("AFTER EDGEFIXES: \n");
		state(cube);

		if (num % 2 == 1)  //if odd number of moves
		{
			parity(cube, num);
			printf("REQUIRE PARITY FIX. \n\n");
		}
		else
		{
			printf("NO PARITY FIX REQUIRED. \n\n");
		}

		cornersolve(cube);
		printf("AFTER CORNERFIXES: \n");
		state(cube);

		printf("Enter Y to repeat another scramble and solve.\nPress any other keys to exit\n");
		/*use scanf for compilers other than Microsoft Visual Studio*/
		scanf_s(" %c",&cont);
		printf("\n\n");
	} while (cont == 'Y' || cont == 'y');

	return 0;
}

void state(int array[maxface][maxrow][maxcol]) 
{
	int i, j;
	for (i = 0;i < maxrow;i++) 
	{
		printf("     ");
		for (j = 0;j < maxcol;j++) 
		{
			printcolor(array[4][i][j]);
		}
		printf("\n");
	}

	printf("\n");

	for (i = 0;i < maxrow;i++)
	{
		for (j = 0;j < maxcol;j++)
		{
			printcolor(array[1][i][j]);
		}
		printf("  ");
		for (j = 0;j < maxcol;j++)
		{
			printcolor(array[0][i][j]);
		}
		printf("  ");
		for (j = 0;j < maxcol;j++)
		{
			printcolor(array[3][i][j]);
		}
		printf("  ");
		for (j = 0;j < maxcol;j++)
		{
			printcolor(array[2][2-i][2-j]);
		}
		printf("\n");
	}

	printf("\n");

	for (i = 0;i < maxrow;i++)
	{
		printf("     ");
		for (j = 0;j < maxcol;j++)
		{
			printcolor(array[5][i][j]);
		}
		printf("\n");
	}

	printf("\n");
}

void printcolor(int num)
{
	int color[6] = { 4,1,6,2,14,15};
	char array[] = "RBOGYW";
	textcolor(color[num]);
	printf("%c", array[0+num]);

}

void textcolor(int color)
{
	static int __BACKGROUND;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


	GetConsoleScreenBufferInfo(h, &csbiInfo);

	SetConsoleTextAttribute(h,color);
}

void fixsideCW(int sidenum, int array[maxface][maxrow][maxcol])//rotate the side face
{    
	int temp = array[sidenum][0][0]; //upper left cornor
	array[sidenum][0][0] = array[sidenum][2][0];
	array[sidenum][2][0] = array[sidenum][2][2];
	array[sidenum][2][2] = array[sidenum][0][2];
	array[sidenum][0][2] = temp;

    temp = array[sidenum][0][1]; //upper middle edge
	array[sidenum][0][1] = array[sidenum][1][0];
	array[sidenum][1][0] = array[sidenum][2][1];
	array[sidenum][2][1] = array[sidenum][1][2];
	array[sidenum][1][2] = temp;
}

void fixsideCCW(int sidenum, int array[maxface][maxrow][maxcol])//rotate the side face,CCW
{
	int temp = array[sidenum][0][0]; //upper left cornor
	array[sidenum][0][0] = array[sidenum][0][2];
	array[sidenum][0][2] = array[sidenum][2][2];
	array[sidenum][2][2] = array[sidenum][2][0];
	array[sidenum][2][0] = temp;

    temp = array[sidenum][0][1]; //upper middle edge
	array[sidenum][0][1] = array[sidenum][1][2];
	array[sidenum][1][2] = array[sidenum][2][1];
	array[sidenum][2][1] = array[sidenum][1][0];
	array[sidenum][1][0] = temp;
}

void R(int array[maxface][maxrow][maxcol])
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[0][i][2];   //red side
	}
	for (int i = 0;i < maxcol;i++) {
		array[0][i][2] = array[5][i][2];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][i][2] = array[2][i][2];
	}
	for (int i = 0;i < maxcol;i++) {
		array[2][i][2] = array[4][i][2];
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][i][2] = temp[i];
	}
	fixsideCW(3, array);
}

void Rp(int array[maxface][maxrow][maxcol])
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[0][i][2];   //red side
	}
	for (int i = 0;i < maxcol;i++) {
		array[0][i][2] = array[4][i][2];
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][i][2] = array[2][i][2];
	}
	for (int i = 0;i < maxcol;i++) {
		array[2][i][2] = array[5][i][2];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][i][2] = temp[i];
	}
	fixsideCCW(3, array);
}

void L(int array[maxface][maxrow][maxcol]) 
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[0][i][0];   //red side
	}
	for (int i = 0;i < maxcol;i++) {
		array[0][i][0] = array[4][i][0];
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][i][0] = array[2][i][0];
	}
	for (int i = 0;i < maxcol;i++) {
		array[2][i][0] = array[5][i][0];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][i][0] = temp[i];
	}
	fixsideCW(1, array);
}


void Lp(int array[maxface][maxrow][maxcol])
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[0][i][0];   //red side
	}
	for (int i = 0;i < maxcol;i++) {
		array[0][i][0] = array[5][i][0];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][i][0] = array[2][i][0];
	}
	for (int i = 0;i < maxcol;i++) {
		array[2][i][0] = array[4][i][0];
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][i][0] = temp[i];
	}
	fixsideCCW(1, array);
}

void U(int array[maxface][maxrow][maxcol])
{
	int temp[maxrow];

	for (int i = 0;i < maxrow;i++) {
		temp[i] = array[0][0][i];   //red side
	}
	for (int i = 0;i < maxrow;i++) {
		array[0][0][i] = array[3][0][i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[3][0][i] = array[2][2][2-i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[2][2][2-i] = array[1][0][i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[1][0][i] = temp[i];
	}
	fixsideCW(4, array);
}
void Up(int array[maxface][maxrow][maxcol])
{
	int temp[maxrow];

	for (int i = 0;i < maxrow;i++) {
		temp[i] = array[0][0][i];   //red side
	}
	for (int i = 0;i < maxrow;i++) {
		array[0][0][i] = array[1][0][i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[1][0][i] = array[2][2][2-i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[2][2][2-i] = array[3][0][i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[3][0][i] = temp[i];
	}
	fixsideCCW(4, array);
}

void D(int array[maxface][maxrow][maxcol])
{
	int temp[maxrow];

	for (int i = 0;i < maxrow;i++) {
		temp[i] = array[0][2][i];   //red side
	}
	for (int i = 0;i < maxrow;i++) {
		array[0][2][i] = array[1][2][i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[1][2][i] = array[2][0][2 - i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[2][0][2 - i] = array[3][2][i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[3][2][i] = temp[i];
	}
	fixsideCW(5, array);
}

void Dp(int array[maxface][maxrow][maxcol])
{
	int temp[maxrow];

	for (int i = 0;i < maxrow;i++) {
		temp[i] = array[0][2][i];   //red side
	}
	for (int i = 0;i < maxrow;i++) {
		array[0][2][i] = array[3][2][i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[3][2][i] = array[2][0][2 - i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[2][0][2 - i] = array[1][2][i];
	}
	for (int i = 0;i < maxrow;i++) {
		array[1][2][i] = temp[i];
	}
	fixsideCCW(5, array);
}
void F(int array[maxface][maxrow][maxcol])  //F move
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[3][i][0];   //blue side
	}
	for (int i = 0;i < maxcol;i++) {
		array[3][i][0] = array[4][2][i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][2][i] = array[1][2-i][2];
	}
	for (int i = 0;i < maxcol;i++) {
		array[1][2-i][2] = array[5][0][2-i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][0][2-i] = temp[i];
	}
	fixsideCW(0, array);	
}

void Fp(int array[maxface][maxrow][maxcol])
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[3][i][0];   //blue side
	}
	for (int i = 0;i < maxcol;i++) {
		array[3][i][0] = array[5][0][2-i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][0][2-i] = array[1][2 - i][2];
	}
	for (int i = 0;i < maxcol;i++) {
		array[1][2 - i][2] = array[4][2][i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][2][i] = temp[i];
	}
	fixsideCCW(0, array);
}

void B(int array[maxface][maxrow][maxcol])  //B move
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[3][i][2];   //blue side
	}
	for (int i = 0;i < maxcol;i++) {
		array[3][i][2] = array[5][2][2-i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][2][2-i] = array[1][2 - i][0];
	}
	for (int i = 0;i < maxcol;i++) {
		array[1][2 - i][0] = array[4][0][i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][0][i] = temp[i];
	}
	fixsideCW(2, array);
}

void Bp(int array[maxface][maxrow][maxcol]) //Bprime
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[3][i][2];   //blue side
	}
	for (int i = 0;i < maxcol;i++) {
		array[3][i][2] = array[4][0][i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][0][i] = array[1][2 - i][0];
	}
	for (int i = 0;i < maxcol;i++) {
		array[1][2 - i][0] = array[5][2][2-i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][2][2-i] = temp[i];
	}
	fixsideCCW(2, array);
}

void M(int array[maxface][maxrow][maxcol])   //M move
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[0][i][1];   //red side,middle strip
	}
	for (int i = 0;i < maxcol;i++) {
		array[0][i][1] = array[5][i][1];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][i][1] = array[2][i][1];
	}
	for (int i = 0;i < maxcol;i++) {
		array[2][i][1] = array[4][i][1];
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][i][1] = temp[i];
	}
}

void Mp(int array[maxface][maxrow][maxcol]) //Mprime
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[0][i][1];   //red side,middle strip
	}
	for (int i = 0;i < maxcol;i++) {
		array[0][i][1] = array[4][i][1];
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][i][1] = array[2][i][1];
	}
	for (int i = 0;i < maxcol;i++) {
		array[2][i][1] = array[5][i][1];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][i][1] = temp[i];
	}
}

void E(int array[maxface][maxrow][maxcol])  //E move
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[0][1][i];   //red side,middle horizontal strip
	}
	for (int i = 0;i < maxcol;i++) {
		array[0][1][i] = array[1][1][i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[1][1][i] = array[2][1][2-i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[2][1][2-i] = array[3][1][i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[3][1][i] = temp[i];
	}
}
void Ep(int array[maxface][maxrow][maxcol]) //Eprime
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[0][1][i];   //red side,middle horizontal strip
	}
	for (int i = 0;i < maxcol;i++) {
		array[0][1][i] = array[3][1][i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[3][1][i] = array[2][1][2 - i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[2][1][2 - i] = array[1][1][i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[1][1][i] = temp[i];
	}
}

void S(int array[maxface][maxrow][maxcol])  //S move
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[4][1][i];   //yellow side,middle horizontal strip
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][1][i] = array[1][2-i][1];
	}
	for (int i = 0;i < maxcol;i++) {
		array[1][2-i][1] = array[5][1][2 - i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][1][2 - i] = array[3][i][1];
	}
	for (int i = 0;i < maxcol;i++) {
		array[3][i][1] = temp[i];
	}
}

void Sp(int array[maxface][maxrow][maxcol]) //Sprime
{
	int temp[maxcol];

	for (int i = 0;i < maxcol;i++) {
		temp[i] = array[4][1][i];   //yellow side,middle horizontal strip
	}
	for (int i = 0;i < maxcol;i++) {
		array[4][1][i] = array[3][i][1];
	}
	for (int i = 0;i < maxcol;i++) {
		array[3][i][1] = array[5][1][2 - i];
	}
	for (int i = 0;i < maxcol;i++) {
		array[5][1][2 - i] = array[1][2-i][1];
	}
	for (int i = 0;i < maxcol;i++) {
		array[1][2-i][1] = temp[i];
	}
}

void scramble(int array[maxface][maxrow][maxcol]) //scrambles the cube, still have error such as R, L, Rp
{
	srand((unsigned int)time(NULL)); //initialize seed based on current time
	char moveset[6]="RLUDFB";
	printf("SCRAMBLE MOVES: ");
	int prev_move = -1;
	int move;
	int set;
	int code;

	for (int i = 0;i <20;i++)   //20 moves scramble
	{
		set = (rand() % 3);
		move = (rand() % 6);
		
		while (move == prev_move) //prevent consecutive moves being rotations on the same face
		{
			move = (rand() % 6);
		}

		if (set == 2) //180 degree turns 
		{
			printf("%c%d ", moveset[move], 2);
		}
		else if(set == 1) //prime turns
		{
			printf("%c%c ", moveset[move], 'p');
		}
		else
		{
			printf("%c ", moveset[move]);
		}

		code = set * 10 + move;

		switch (code)
		{
			case(0):
				R(array);
				break;
			case(1):
				L(array);
				break;
			case(2):
				U(array);
				break;
			case(3):
				D(array);
				break;
			case(4):
				F(array);
				break;
			case(5):
				B(array);
				break;
			case(10):
				Rp(array);
				break;
			case(11):
				Lp(array);
				break;
			case(12):
				Up(array);
				break;
			case(13):
				Dp(array);
				break;
			case(14):
				Fp(array);
				break;
			case(15):
				Bp(array);
				break;
			case(20):
				R(array);
				R(array);
				break;
			case(21):
				L(array);
				L(array);
				break;
			case(22):
				U(array);
				U(array);
				break;
			case(23):
				U(array);
				U(array);
				break;
			case(24):
				F(array);
				F(array);
				break;
			case(25):
				B(array);
				B(array);
				break;
		}
		prev_move = move; //record the current set
	}
	printf("\n\n");
}

void initialize(Queue* q)  //initialization 
{ 
	q->front = NULL;
	q->back = NULL;
	q->num = 0;
	q->total = 0;
}

int isEmpty(Queue* q) // check whether the queue is empty,empty on 1
{
	if (q->front == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int enqueue(Queue* q, int val)// enqueue, return 1 upon success
{
	struct  Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->data = val;

	if(q->front == NULL)
	{
		q->front = newnode;
		q->back = newnode;
	}
	else
	{
		q->back->next = newnode;
		q->back = newnode;
	}
	q->num++;
	q->total++;
	return 1;
}
int dequeue(Queue* q)//dequeue, return 0 when empty list, return 1 upon sucess
{
	struct Node* temp = q->front;
	if (isEmpty(q))
		return 0;
	else {
		q->front = q->front->next;
		free(temp);
		temp = NULL;
		q->num--;
		if (q->num==0) 
		{
			q->back = NULL;
			q->front = NULL;
		}
		return 1;
	}
}
int peek(Queue* q) //peek, return 0 when empty list,else return peeked value
{
	if (isEmpty(q))
		return 0;
	else
		return q->front->data;
}

void parity(int array[maxface][maxrow][maxcol]) //solves parity through Ra perm
{
		R(array);
		Up(array);
		Rp(array);
		Up(array);
		R(array);
		U(array);
		R(array);
		D(array);
		Rp(array);
		Up(array);
		R(array);
		Dp(array);
		Rp(array);
		U(array);
		U(array);
		Rp(array);
		Up(array);
}
