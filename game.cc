#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>

using namespace std;

int read_keybord();
/******************************************************************************/
#define H 20
#define L 40
char tab[H][L];
bool arreter = false;

/* le screen***********************************************************/
void cadre() {
	for (int i = 0; i<H; i++) {
		for (int j = 0; j<L; j++)
		if (i == 0 || i == H - 1 || j == L - 1 || j == 0)
			tab[i][j] = '|';
		cout << endl;
	}
	for (int i = 0; i<H; i++){
		for (int j = 0; j<L; j++)
			cout << tab[i][j];
		cout << endl;
	}
}

/*clear screen*************************************************************/
void clear_screen() {
	for (int i = 1; i<H - 1; i++)
	for (int j = 1; j<L - 1; j++)
		tab[i][j] = ' ';
}

/****************************************************************/
int x = 1, y = 1;
int dx = 1, dy = 1;
void leballe() {
	tab[x][y] = 'O';
	if ((x == H-3) && (tab[x][y]=='O') && (tab[x+1][y]==' ')) arreter=true;
	if (x == H - 3)  dx = -1;
	if (y == L - 2)  dy = -1;
	if (x == 1)   dx = 1;
	if (y == 1)   dy = 1;
	x += dx;
	y += dy;
}

/*la barre**************************************************************/

int n = 12, m = 26;
int key = read_keybord();

void labarre() {
	for (int i = 0; i<L; i++)
	{
		if (i>n && i<m)
			tab[H - 2][i] = '=';
	}
	for (int i = 0; i<L; i++)
		cout << tab[H - 2][i];

}
/*Deplacement la barre******************************************************/
void deplacement(char key) {
	if ((key == 'a') && (n>0)){
		n--; m--;
	}
	if ((key == 'd') && (m<L - 1)){
		m++; n++;
	}
}


/*les briques ************************************************************/

int i = 0, j = 0;
int b1[H][L];
int a = 0;

void briques() {
	for (i = 0; i<L; i++)
	{
		if ((i>9 && i<30) && i != a)
			tab[2][i] = 'X';
		if ((i>12 && i<27) && i != a)
			tab[3][i] = 'X';
	}
}

/*faire disparaitre les briques************************************************/




/*compte le score**************************************************************/
int cpt = 0;
void compte() {
	if (dx == 1 && (y>n && y<m) && x == H - 3)
		cpt = cpt + 50;
	if (dx == 1 && (y <= n && y >= m) && x == H - 3) {
		cout << " you lose!" << endl;
		cout << "your score:" << cpt << endl;
		exit(0);

	}
}
/******************************************************************************/
int main() {
        system("clear");
	char play; 
        cout << "Bienvenue au jeux casse brique!"<< endl;
        cout << "Appuyez a pour deplacer vers la gauche" << endl;
	cout << "Appuyez d pour deplacer vers la droite" << endl;
	do { cout <<"Appuyez 'y' pour jouer :";
	    cin >> play;
	}while (play !='y');
        int key;
	int score = 0;
	do
	{
		key = read_keybord();
		clear_screen();
		briques();
		labarre();
		leballe();
		deplacement(key);
		compte();
		cadre();
		usleep(10 * 10000);
	} while ((key != 'q')&& (arreter==false));
	system("clear");
	cout << "GAME OVER"<< endl;
}
/******************************************************************************/

int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

int read_keybord() {
	int key;
	if (kbhit())
		key = getc(stdin);
	else
		key = 0;
	return key;
}
