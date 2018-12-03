#include <stdio.h>
#include <stdbool.h>

int global_board[8][8] = {0};
bool whiteturn = true;
bool jumped = false;

// Initialize checker board
void initboard(int board[8][8]){
    for (int i = 0; i < 3; i++){
	for (int j = 0; j < 4; j++){
	    if(i%2 == 0){
		board[i][2*j+1] = 1;
	    } else {
		board[i][2*j] = 1;
	    }

	}	    
    }

    for (int i = 5; i < 8; i++){
	for (int j = 0; j < 4; j++){
	    if(i%2 == 0){
		board[i][2*j+1] = 2;
	    } else {
		board[i][2*j] = 2;
	    }

	}	    
    }

}

// Print current board
void printboard(int board[8][8]){
    printf("   1 2 3 4 5 6 7 8\n");
    for(int i = 0; i < 8; i++){
	putchar('A'+i);
	printf("| ");
	for(int j = 0; j < 8; j++){
	    printf("%d ", board[i][j]);
	}
	printf("\n");
    }
}

// Check for win conditions
int checkwin(int board[8][8]){
    int white = 0;
    int red = 0;
    
    for(int i = 0; i < 8; i++){
	for(int j = 0; j < 8; j++){
	    if(board[i][j] == 1||board[i][j] == 3){
		white++;
	    } else if (board[i][j] == 2||board[i][j] == 4){
		red++;
	    }
	}
    }

    if(white == 0){
	return 2;
    } else if (red == 0){
	return 1;
    } else {
	return 0;
    }
}

// Check validity of moves
int checkmove (int board[8][8], int irow, int icol, int frow, int fcol){

    // Check if values may go over the board
    if(irow < 0 || irow >= 8){
	//printf("Invalid values\n");
	return 1;
    } else if(icol < 0 || icol >= 8){
	//printf("Invalid values\n");
	return 1;
    } else if(frow < 0 || frow >= 8){
	//printf("Invalid values\n");
	return 1;
    } else if(fcol < 0 || fcol >= 8){
	//printf("Invalid values\n");
	return 1;
    }

    // Check if correct initial pieces were given based on the current turn
    if(whiteturn == true && board[irow][icol] != 1 && board[irow][icol] != 3){
	//printf("Invalid piece\n");
	return 1;
    } else if (whiteturn != true && board[irow][icol] != 2 && board[irow][icol] != 4){
	//printf("Invalid piece\n");
	return 1;
    }

    // Destination is not a empty space
    if(board[frow][fcol] != 0){
	//printf("Invalid destination\n");
	return 1;
    }
    
    // Check if normal pieces are moving in the correct y range
    if (board[irow][icol] == 1 || board[irow][icol] == 2){
	if (whiteturn == true && (frow <= irow || frow > irow + 2)){
	    //printf("Invalid whitepiece movement\n");
	    return 1;
	} else if (whiteturn != true && (frow >= irow|| frow < irow - 2)){
	    //printf("Invalid redpiece movement\n");
	    return 1;
	}
    // Check if promoted pieces are moving in the correct y range
    } else if (board[irow][icol] == 3 || board[irow][icol] == 4){
	if (frow < irow - 2 || frow > irow + 2 || frow == irow){
	    //printf("Invalid diagonal movement\n");
	    return 1;
	}
    }

    // Check if the pieces are moving in the correct x range
    if(fcol > icol + 2 || fcol < icol - 2 || fcol == icol){
	//printf("Invalid diagonal movement\n");
	return 1;
    }


    // Checking for single space movements
    if(frow == irow + 1 || frow == irow -1){
	if(! (fcol == icol + 1 || fcol == icol -1) ){
	    //printf("Invalid movement\n");
	    return 1;
	}
    }

    // Check if jumping is valid for normal pieces
    if (board[irow][icol] == 1 || board[irow][icol] == 2){
	if(whiteturn == true && frow == irow + 2){
	    if(fcol == icol + 2){
		if(board[irow+1][icol+1] == 0){
		    //printf("Invalid jump\n");
		    return 1;
		}
	    } else if (fcol == icol - 2){
		if(board[irow+1][icol-1] == 0){
		    //printf("Invalid jump\n");
		    return 1;
		}
	    } else {
		//printf("Invalid movement\n");
		return 1;
	    }
	} else if(whiteturn != true && frow == irow - 2){
	    if(fcol == icol + 2){
		if(board[irow-1][icol+1] == 0){
		    //printf("Invalid jump\n");
		    return 1;
		}
	    } else if (fcol == icol - 2){
		if(board[irow-1][icol-1] == 0){
		    //printf("Invalid jump\n");
		    return 1;
		}
	    } else {
		//printf("Invalid movement\n");
		return 1;
	    }
	}
    // Check if jumping is valid for promoted pieces
    } else if (board[irow][icol] == 3 || board[irow][icol] == 4){
	// Jumping downwards
	if(frow == irow + 2){	
	    // Jumping right
	    if(fcol == icol + 2){
		if(board[irow+1][icol+1] == 0){
		    //printf("Invalid jump\n");
		    return 1;	
		}
	    // Jumping left
	    } else if (fcol == icol - 2){
		if(board[irow+1][icol-1] == 0){
		    //printf("Invalid jump\n");
		    return 1;	
		}
	    } else {
		//printf("Invalid movement\n");
		return 1;
	    }	
    
	// Jumping upwards
	} else if (frow == irow - 2){
	    // Jumping right
	    if(fcol == icol + 2){
		if(board[irow-1][icol+1] == 0){
		    //printf("Invalid jump\n");
		    return 1;	
		}
	    // Jumping left
	    } else if (fcol == icol - 2){
		if(board[irow-1][icol-1] == 0){
		    //printf("Invalid jump\n");
		    return 1;	
		}
	    } else {
		//printf("Invalid movement\n");
		return 1;
	    }
	}
    }
           
    return 0;
}

// Evaluates the board to make promotions
void makepromotion(int board[8][8]){
    for(int i = 0; i < 8; i++){
	if(board[0][i] == 2){
	    printf("Red piece at A%c promoted!\n", i+'1');
	    board[0][i] = 4;
	} else if (board[7][i] == 1){
	    printf("White piece at F%c promoted!\n", i+'1');
	    board[7][i] = 3;
	}
    }
}

// Moves the pieces accordingly
void movepiece (int board[8][8], int irow, int icol, int frow, int fcol){

    // No jumping (normal + promoted)
    if(frow == irow + 1||frow == irow - 1){
	board[frow][fcol] = board[irow][icol];
	board[irow][icol] = 0;

    // Jumping
    } else if (frow == irow  + 2 || frow == irow - 2){

	jumped = true;

	board[frow][fcol] = board[irow][icol];
	board[irow][icol] = 0;

	// Jumping downwards
	if(frow == irow + 2){	
	    // Jumping right
	    if(fcol == icol + 2){

		if(whiteturn == true && (board[irow+1][icol+1] == 2 || board[irow+1][icol+1] == 4)){
		    printf("Red piece at %c%c taken!\n", irow+'A'+1, icol+'0'+2);
		    board[irow+1][icol+1] = 0;
		} else if (whiteturn != true && (board[irow+1][icol+1] == 1 || board[irow+1][icol+1] == 3)){
		    printf("White piece at %c%c taken!\n", irow+'A'+1, icol+'0'+2);
		    board[irow+1][icol+1] = 0;
		}

	    // Jumping left
	    } else if (fcol == icol - 2){
		
		if(whiteturn == true && (board[irow+1][icol-1] == 2 || board[irow+1][icol-1] == 4)){
		    printf("Red piece at %c%c taken!\n", irow+'A'+1, icol+'0');
		    board[irow+1][icol-1] = 0;
		} else if (whiteturn != true && (board[irow+1][icol-1] == 1 || board[irow+1][icol-1] == 3)){
		    printf("White piece at %c%c taken!\n", irow+'A'+1, icol+'0');
		    board[irow+1][icol-1] = 0;
		}

	    }
    
	// Jumping upwards
	} else if (frow == irow - 2){
	    // Jumping right
	    if(fcol == icol + 2){
		
		if(whiteturn == true && (board[irow-1][icol+1] == 2 || board[irow-1][icol+1] == 4)){
		    printf("Red piece at %c%c taken!\n", irow+'A'-1, icol+'0'+2);
		    board[irow-1][icol+1] = 0;
		} else if (whiteturn != true && (board[irow-1][icol+1] == 1 || board[irow-1][icol+1] == 3)){
		    printf("White piece at %c%c taken!\n", irow+'A'-1, icol+'0'+2);
		    board[irow-1][icol+1] = 0;
		}

	    // Jumping left
	    } else if (fcol == icol - 2){
		
		if(whiteturn == true && (board[irow-1][icol-1] == 2 || board[irow-1][icol-1] == 4)){
		    printf("Red piece at %c%c taken!\n", irow+'A'-1, icol+'0');
		    board[irow-1][icol-1] = 0;
		} else if (whiteturn != true && (board[irow-1][icol-1] == 1 || board[irow-1][icol-1] == 3)){
		    printf("White piece at %c%c taken!\n", irow+'A'-1, icol+'0');
		    board[irow-1][icol-1] = 0;
		}

	    }
	}

    }

    makepromotion(board);
}


/*
void movepiece (int board[8][8], int irow, int icol, int frow, int fcol){

    if(whiteturn == true){
	
	// No jumping (normal + promoted)
	if(frow == irow + 1||frow == irow - 1){
	    board[frow][fcol] = board[irow][icol];
	    board[irow][icol] = 0;

	// Jumping
	} else if (frow == irow + 2){
	    board[frow][fcol] = board[irow][icol];
	    board[irow][icol] = 0;

	    if(fcol == icol + 2){
		if(board[irow+1][icol+1] == 2){
		    printf("Red piece at %c%c taken!\n", irow+'A'+1, icol+'0'+2);
		    board[irow+1][icol+1] = 0;
		}
	    } else if (fcol == icol - 2){
		if(board[irow+1][icol-1] == 2){
		    printf("Red piece at %c%c taken!\n", irow+'A'+1, icol+'0');
		    board[irow+1][icol-1] = 0;
		}
	    }
	}


    } else if (whiteturn != true){

	// No jumping (normal + promoted)
	if(frow == irow + 1||frow == irow - 1){
	    board[frow][fcol] = board[irow][icol];
	    board[irow][icol] = 0;
	
	// Jumping
	} else if (frow == irow - 2){
	    board[frow][fcol] = board[irow][icol];
	    board[irow][icol] = 0;

	    if(fcol == icol + 2){
		if(board[irow-1][icol+1] == 1){
		    printf("White piece at %c%c taken!\n", irow+'A'-1, icol+'0'+2);
		    board[irow-1][icol+1] = 0;
		}
	    } else if (fcol == icol - 2){
		if(board[irow-1][icol-1] == 1){
		    printf("White piece at %c%c taken!\n", irow+'A'-1, icol+'0');
		    board[irow-1][icol-1] = 0;
		}
	    }
	}

    }

    makepromotion(board);
}*/

// Checks if more jumps are necessary
int checkjump (int board[8][8], int row, int col, int irow, int icol){
   
    // Normal pieces
    if(board[row][col] == 1 || board[row][col] == 2){ 

	if(whiteturn == true){
	    if((row + 1) < 7 && (col + 1) < 7){
		if(board[row+1][col+1] != 0){
		    if(board[row+2][col+2] == 0){
			return 1;
		    }
		}
	    } 
	    
	    if ((row + 1) < 7 && (col - 1) > 0){
		if(board[row+1][col-1] != 0){
		    if(board[row+2][col-2] == 0){
			return 1;
		    }
		}
	    }
	}  else if (whiteturn != true){
	    if((row-1) > 0 && (col + 1) < 7){
		if(board[row-1][col+1] != 0){
		    if(board[row-2][col+2] == 0){
			return 1;
		    }
		}
	    } 
	    
	    if ((row-1) > 0 && (col - 1) > 0){
		if(board[row-1][col-1] != 0){
		    if(board[row-2][col-2] == 0){
			return 1;
		    }
		}
	    }
	}

    //	Promoted pieces
    } else if (board[row][col] == 3 || board[row][col] == 4){ 
	
	if((row + 1) < 7 && (col + 1) < 7){

	    if(board[row+1][col+1] != 0){
		if(board[row+2][col+2] == 0 && !(row+2 == irow && col+2 == icol)){
		    return 1;
		}
	    }

	} 
	
	if ((row + 1) < 7 && (col - 1) > 0){

	    if(board[row+1][col-1] != 0){
		if(board[row+2][col-2] == 0 && !(row+2 == irow && col-2 == icol)){
		    return 1;
		}
	    }

	} 
	
	if((row-1) > 0 && (col + 1) < 7){

	    if(board[row-1][col+1] != 0){
		if(board[row-2][col+2] == 0 && !(row-2 == irow && col+2 == icol)){
		    return 1;
		}
	    }

	} 
	
	if ((row - 1) > 0 && (col - 1) > 0){

	    if(board[row-1][col-1] != 0){
		if(board[row-2][col-2] == 0 && !(row-2 == irow && col-2 == icol)){
		    return 1;
		}
	    }

	}
    
    }

    return 0;
}


/*
int checkjump (int board[8][8], int row, int col){
   
    if(board[row][col] == 1 || board[row][col] == 2){ 

	if(whiteturn == true){
	    if((row + 1) < 7 && (col + 1) < 7){
		if(board[row+1][col+1] == 2){
		    if(board[row+2][col+2] == 0){
			return 1;
		    }
		}
	    } 
	    
	    if ((row + 1) < 7 && (col - 1) > 0){
		if(board[row+1][col-1] == 2){
		    if(board[row+2][col-2] == 0){
			return 1;
		    }
		}
	    }
	}  else if (whiteturn != true){
	    if((row-1) > 0 && (col + 1) < 7){
		if(board[row-1][col+1] == 1){
		    if(board[row-2][col+2] == 0){
			return 1;
		    }
		}
	    } 
	    
	    if ((row-1) > 0 && (col - 1) > 0){
		if(board[row-1][col-1] == 1){
		    if(board[row-2][col-2] == 0){
			return 1;
		    }
		}
	    }
	}

    } else if (board[row][col] == 3 || board[row][col] == 4){ 
	
	if((row + 1) < 7 && (col + 1) < 7){

	    if(whiteturn == true && (board[row+1][col+1] == 2 || board[row+1][col+1] == 4)){
		if(board[row+2][col+2] == 0){
		    return 1;
		}
	    } else if(whiteturn != true && (board[row+1][col+1] == 1 || board[row+1][col+1] == 3)){
		if(board[row+2][col+2] == 0){
		    return 1;
		}
	    }

	} 
	
	if ((row + 1) < 7 && (col - 1) > 0){

	    if(whiteturn == true && (board[row+1][col-1] == 2 || board[row+1][col-1] == 4)){
		if(board[row+2][col-2] == 0){
		    return 1;
		}
	    } else if(whiteturn != true && (board[row+1][col-1] == 1 || board[row+1][col-1] == 3)){
		if(board[row+2][col-2] == 0){
		    return 1;
		}
	    }

	} 
	
	if((row-1) > 0 && (col + 1) < 7){

	    if(whiteturn == true && (board[row-1][col+1] == 2 || board[row-1][col+1] == 4)){
		if(board[row-2][col+2] == 0){
		    return 1;
		}
	    } else if(whiteturn != true && (board[row-1][col+1] == 1 || board[row-1][col+1] == 3)){
		if(board[row-2][col+2] == 0){
		    return 1;
		}
	    }

	} 
	
	if ((row - 1) > 0 && (col - 1) > 0){

	    if(whiteturn == true && (board[row-1][col-1] == 2 || board[row-1][col-1] == 4)){
		if(board[row-2][col-2] == 0){
		    return 1;
		}
	    } else if(whiteturn != true && (board[row-1][col-1] == 1 || board[row-1][col-1] == 3)){
		if(board[row-2][col-2] == 0){
		    return 1;
		}
	    }

	}
    
    }

    return 0;
}*/

// Prints out all possible move locations
void movelist(int board[8][8], int row, int col ){

    printf("Movelist for %c%c: ", row+'A', col+'0'+1);

    for(int i = -2; i < 3; i++){
	for (int j = -2; j < 3; j++){
	    if(!(i == 0 && j == 0)){
		
		if(checkmove(board, row, col, row + i, col + j) == 0){
		    printf("%c%c ", row + i + 'A', col + j + '0' + 1);
		}
	    }
	}
    }

    printf("\n");

}

// 1 = white piece, 2 = red piece
int main (){

    //int global_board[8][8] = {0};

    initboard(global_board);
    
    while(checkwin(global_board) == 0){

	printboard(global_board);
	jumped = false;
	printf("\n");

	for (int i = 0; i < 8; i++){
	    for(int j = 0; j < 8; j++){
		if(whiteturn && (global_board[i][j] == 1 || global_board[i][j] == 3)){
		    movelist(global_board, i, j);	
		}else if (!whiteturn && (global_board[i][j] == 2 || global_board[i][j] == 4)){
		    movelist(global_board, i, j);
		}
	    }
	}

	if(whiteturn){
	    printf("White move: ");
	} else {
	    printf("Red move: ");
	}

	int input[5] = {0};
	for(int i = 0; i < 5; i++){
	    input[i] = getchar();
	}

	int c = getchar();
	while(c != '\n'){
	    c = getchar();
	}
	
	if(input[0] < 'A' || input[0] > 'H' || input[1] < '1' || input[1] > '8' || input[2] != ' ' || input[3] < 'A' || input[3] > 'H' || input[4] < '1' || input[4] > '8'){
	    printf("Invalid input\n");
	} else {

	    int irow = input[0]-'A';
	    int icol = input[1]-'0'-1;

	    int frow = input[3]-'A';	
	    int fcol = input[4]-'0'-1;

	    printf("Move: %c%c -> %c%c\n",irow+'A', icol+'0'+1, frow+'A', fcol+'0'+1);

	    if(checkmove(global_board, irow, icol, frow, fcol) == 0){
		movepiece(global_board,irow,icol,frow,fcol);

		// Must Jump!
		if(jumped && checkjump(global_board,frow,fcol,irow,icol) == 1){
		    printf("You must make a jump!\n");
		} else {
		    whiteturn = !whiteturn;
		}
	    } else {
		printf("Invalid movement\n");
	    }
	}
    }

    printboard(global_board);

    if(checkwin(global_board) == 2){
	printf("White win!\n");
	return 0;
    } else if(checkwin(global_board) == 1){
	printf("Red win!\n");
	return 0;
    }


}
