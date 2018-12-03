#include <stdio.h>
#include <stdbool.h>

int board[8][8] = {0};
bool whiteturn = true;

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

int checkwin(int board[8][8]){
    int white = 0;
    int red = 0;
    
    for(int i = 0; i < 8; i++){
	for(int j = 0; j < 8; j++){
	    if(board[i][j] == 1){
		white++;
	    } else if (board[i][j] == 2){
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

int checkmove (int board[8][8], int irow, int icol, int frow, int fcol){

    // Check if values may go over the board
    if(irow < 0 || irow >= 8){
	printf("Invalid values\n");
	return 1;
    } else if(icol < 0 || icol >= 8){
	printf("Invalid values\n");
	return 1;
    } else if(frow < 0 || frow >= 8){
	printf("Invalid values\n");
	return 1;
    } else if(fcol < 0 || fcol >= 8){
	printf("Invalid values\n");
	return 1;
    }

    // Check if correct initial pieces were given based on the current turn
    if(whiteturn == true && board[irow][icol] != 1){
	printf("Invalid piece\n");
	return 1;
    } else if (whiteturn != true && board[irow][icol] != 2){
	printf("Invalid piece\n");
	return 1;
    }

    // Destination is not a empty space
    if(board[frow][fcol] != 0){
	printf("Invalid destination\n");
	return 1;
    }
    
    // Check if the pieces are moving in the correct y direction
    if (whiteturn == true && (frow <= irow || frow > irow + 2)){
	printf("Invalid whitepiece movement\n");
	return 1;
    } else if (whiteturn != true && (frow >= irow|| frow < irow - 2)){
	printf("Invalid redpiece movement\n");
	return 1;
    }

    // Check if the pieces are moving in the correct x direction
    if(fcol > icol + 2 || fcol < icol - 2 || fcol == icol){
	printf("Invalid diagonal movement\n");
	return 1;
    }

    // Check if jumping is valid
    if(whiteturn == true && frow == irow + 2){
	if(fcol == icol + 2){
	    if(board[irow+1][icol+1] == 0){
		printf("Invalid jump\n");
		return 1;
	    }
	} else if (fcol == icol - 2){
	    if(board[irow+1][icol-1] == 0){
		printf("Invalid jump\n");
		return 1;
	    }
	}
    } else if(whiteturn != true && frow == irow - 2){
	if(fcol == icol + 2){
	    if(board[irow-1][icol+1] == 0){
		printf("Invalid jump\n");
		return 1;
	    }
	} else if (fcol == icol - 2){
	    if(board[irow-1][icol-1] == 0){
		printf("Invalid jump\n");
		return 1;
	    }
	}
    }
           
    return 0;
}


void movepiece (int board[8][8], int irow, int icol, int frow, int fcol){

    if(whiteturn == true){
	
	// No jumping
	if(frow == irow + 1){
	    board[irow][icol] = 0;
	    board[frow][fcol] = 1;

	// Jumping
	} else if (frow == irow + 2){
	    board[irow][icol] = 0;
	    board[frow][fcol] = 1;
	    if(fcol == icol + 2){
		if(board[irow+1][icol+1] == 2){
		    board[irow+1][icol+1] = 0;
		}
	    } else if (fcol == icol - 2){
		if(board[irow+1][icol-1] == 2){
		    board[irow+1][icol-1] = 0;
		}
	    }
	}



    } else if (whiteturn != true){

	// No jumping
	if(frow == irow - 1){
	    board[irow][icol] = 0;
	    board[frow][fcol] = 2;
	
	// Jumping
	} else if (frow == irow + 2){
	    board[irow][icol] = 0;
	    board[frow][fcol] = 2;
	    if(fcol == icol + 2){
		if(board[irow+1][icol+1] == 1){
		    board[irow+1][icol+1] = 0;
		}
	    } else if (fcol == icol - 2){
		if(board[irow+1][icol-1] == 1){
		    board[irow+1][icol-1] = 0;
		}
	    }
	}

    }
}

int checkjump (int board[8][8], int row, int col){
    
    if(whiteturn == true){
	if((row + 1) < 7 && (col + 1) < 7){
	    if(board[row+1][col+1] == 2){
		if(board[row+2][col+2] == 0){
		    return 1;
		}
	    }
	} else if ((row + 1) < 7 && (col - 1) > 0){
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
	} else if ((row-1) > 0 && (col - 1) > 0){
	    if(board[row-1][col-1] == 1){
		if(board[row-2][col-2] == 0){
		    return 1;
		}
	    }
	}

    }
    return 0;
}


// 1 = white piece, 2 = red piece
int main (){
    initboard(board);
    
    while(checkwin(board) == 0){
	printboard(board);

	if(whiteturn){
	    printf("White move: ");
	} else {
	    printf("Red move: ");
	}

	int irow = getchar()-'A';
	int icol = getchar()-'0'-1;

	getchar();

	int frow = getchar()-'A';	
	int fcol = getchar()-'0'-1;

	getchar();

	if(checkmove(board, irow, icol, frow, fcol) == 0){
	    movepiece(board,irow,icol,frow,fcol);

	    // Must Jump!
	    if(checkjump(board,frow,fcol) == 1){
		printf("You must make a jump!\n");
	    } else if (checkjump(board,frow,fcol) != 1){
		whiteturn = !whiteturn;
	    }
	}

    }

    if(checkwin(board) == 2){
	printf("White win\n");
	return 0;
    } else if(checkwin(board) == 1){
	printf("Red win\n");
	return 0;
    }


}
