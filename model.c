/*YUSUF YALÇIN
 * model.c
 * provides the grid (model) 
 * and functions to handle the grid for the game of life
 */

#include "gameoflife.h"
int grid[M][N] = {0}; /*M ve N boyutlarında iki boyutlu bir dizi oluşturur ve bütün değerlerine sıfır atar*/
	/*M and N are constants defined in gameOfLife.h*/
       
/**
 * initializes the grid with the chosen initial state
 */
int initGridWithBlinker(){ /* Her 10x10 alt-gride Blinker yerleştiren fonksiyon*/
	int i = 0,j = 0;
	while(i<M&&j<N){  /*i nin M den,j nın N den küçük olduğu sürece döngü devam eder*/
		grid[i+3][j+4] = 1;
		grid[i+4][j+4] = 1;
		grid[i+5][j+4] = 1;
		i = i+10;
		j = j+10;
	}
	
}
int initGridWithGlider(){ /* Her 10x10 alt-gride Glider yerleştiren fonksiyon*/
	 int i = 0,j = 0;
	 while(i<M&&j<N){     /*i nin M den,j nın N den küçük olduğu sürece döngü devam eder*/
		grid[i+3][j+4] = 1;
		grid[i+4][j+4] = 1;
		grid[i+5][j+4] = 1;
	    grid[i+4][j+2] = 1;
		grid[i+5][j+3] = 1;
		i = i+10;
		j = j+10;
	}
}

int initGrid(int initialState){    /*initalState değerine göre Blinker veya Glider yerleştiren fonksiyon */
	if (initialState==1){          

	initGridWithBlinker();         /* initialState parametresinin değeri 1 ise bu fonksiyonu çağırır.    */

}
else if(initialState==2){
	initGridWithGlider();          /* initialState’in değeri 2 ise bu fonksiyonu çağırır.                */

}
	return 0;

}

/**
 * returns the number of live neighbors of the cell
 * at position (x, y) on the grid
 */
int getNumberOfLiveNeighbors(int x, int y){ /* komşulardaki canlı hücre sayısını bulmak için kullandığımız fonksiyon */
	int neighbors = 0;
	    for (int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++)
            if (!(i == x && j == y))
             /*   continue; */
                
            if(i < M && j < N && i >= 0 && j >= 0){
                if (grid[i][j] == 1){
                    neighbors++;    
                }
            }
        }
    
	
	return neighbors;
}

/**
 * updates each cell by following the update rules of the game of life
 */
int updateGrid(){                 /*Her bir hücrenin komşusundaki canlı hücre sayısını tutacak.*/
	int neighbor[M][N] = {0};     /*M ve N boyutlarında iki boyutlu bir dizi oluşturur ve bütün değerlerine sıfır atar*/ /*Komsu sayısını tutan dizidir*/
	for(int i=0; i<50; i++) {     /*Her  elemanın etrafindaki canlı hücre sayısını neighbor dizisine kaydeden döngü*/
		for(int j=0; j<50; j++){
			neighbor[i][j] = getNumberOfLiveNeighbors(i, j);
		}
	}
		for(int x=0;x<M;x++){     /*Her bir elemanı komşu sayısına bakarak kurallara göre güncelleyen döngü */
			for(int y=0; y<N ; y++){
				if(neighbor[x][y] <=1) {     /* Bir canlı hücrenin bir tane veya hiç komşusu yoksa bu hücre ölür. Yani değeri 0 olur.*/
					grid[x][y]=0;
				}
				else if(grid[x][y]==1 && (neighbor[x][y]==2 || neighbor[x][y]==3)){   /*Bir canlı hücrenin iki veya üç tane komşusu canlı ise bu hücre yaşamaya devam eder.Yani değeri 1 olarak kalır.*/

					grid[x][y]=1;
				}
                else if(grid[x][y]==1 && (neighbor[x][y]>3)) {  /* Bir canlı hücrenin üçten daha fazla canlı komşusu varsa bu hücre ölür. Yani değeri 0 olur.*/
                    grid[x][y]=0;
				}
                else if(grid[x][y]==0 && (neighbor[x][y]==3)) {  /*Ölü bir hücre tam olarak üç tane canlı komşusu varsa bu hücre canlı olur. Yani değeri 1 olur.*/

                    grid[x][y]=1;
				}
			}
		}
				
				
	return 0;
}

