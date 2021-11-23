#include <stdio.h>
#include <stdlib.h>

char board[8][8] = {
                    { 'R' , 'N' , 'B' , 'Q' , 'K' , 'B' , 'N' , 'R' },
                    { 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' },
                    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
                    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
                    { 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' },
                    { 'r' , 'n' , 'b' , 'q' , 'k' , 'b' , 'n' , 'r' }
                    };
char board2[8][8];

char captured[30] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int num_captured = 0;

char moves[1000][5];

int num_moves = 0;

void capture(char movement[]){
captured[num_captured] = board[movement[3] - '1'][movement[2] - 'A'];
num_captured++;
}

void print_caotured(){
for(int i = 0;i < (num_captured - 1);i++){
    printf(" %c ,", captured[i]);
}
printf(" %c",captured[num_captured - 1]);
}

void confirm_move(){
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        board2[i][j] = board[i][j];
    }
}
}

void delete_move(){
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        board[i][j] = board2[i][j];
    }
}
}

//function of movement
void moving(char movement[]){
board[movement[3] - '1'][movement[2] - 'A'] = board[movement[1] - '1'][movement[0] - 'A'];
if(((movement[1] - '1') + (movement[0] - 'A')) %2 == 0)
    board[movement[1] - '1'][movement[0] - 'A'] = '.';
else
    board[movement[1] - '1'][movement[0] - 'A'] = '-';
}

//print the board
void print_board(){
printf("\n      A   B   C   D   E   F   G   H  ");
printf("\n  __|___|___|___|___|___|___|___|___|\n  ");
for(int i = 0;i < 8;i++){
    printf("%d | ", i + 1);
    for(int j = 0;j < 8;j++){
        printf("%c | ",board[i][j]);
    }
       printf("%d  ", i + 1);

    printf("\n  __|___|___|___|___|___|___|___|___|\n  ");
}
    printf("  | A | B | C | D | E | F | G | H |\n  ");
}

//absolute function
int abs(int n){
if(n < 0){
    n = n * (-1);
}
return n;
}

//a function that checks if there is a white item at the second place
int white_existance(char movement[]){
int n = 0;
if(board[movement[3] - '1'][movement[2] - 'A'] == 'p'){
    n = 1;
}
else if(board[movement[3] - '1'][movement[2] - 'A'] == 'q'){
    n = 1;
}
else if(board[movement[3] - '1'][movement[2] - 'A'] == 'n'){
    n = 1;
}
else if(board[movement[3] - '1'][movement[2] - 'A'] == 'r'){
    n = 1;
}
else if(board[movement[3] - '1'][movement[2] - 'A'] == 'k'){
    n = 1;
}
else if(board[movement[3] - '1'][movement[2] - 'A'] == 'b'){
    n = 1;
}
return n;
}

//a function that checks if there is a black item at the second place
int black_existance(char movement[]){
int n = 0;
if(board[movement[3] - '1'][movement[2] - 'A'] == 'P'){
    n = 1;
}
else if(board[movement[3] - '1'][movement[2] - 'A'] == 'Q'){
    n = 1;
}
else if(board[movement[3] - '1'][movement[2] - 'A'] == 'N'){
    n = 1;
}
else if(board[movement[3] - '1'][movement[2] - 'A'] == 'R'){
    n = 1;
}
else if(board[movement[3] - '1'][movement[2] - 'A'] == 'K'){
    n = 1;
}
else if(board[movement[3] - '1'][movement[2] - 'A'] == 'B'){
    n = 1;
}
return n;
}

//checking possibility of the white king move(don,t care about check)
int Wk_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
if((abs(movement[2] - movement[0]) <= 1) && (abs(movement[1] - movement[3]) <= 1) && (!white_existance(movement)) && !(movement[0] == movement[2] && movement[1] == movement[3]))
    return 1;
else
    return 0;
}
}

//checking possibility of the black king move(don,t care about check)
int Bk_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
if((abs(movement[2] - movement[0]) <= 1) && (abs(movement[1] - movement[3]) <= 1) && (!black_existance(movement)) && !(movement[0] == movement[2] && movement[1] == movement[3]))
    return 1;
else
    return 0;
}
}

//checking possibility of the white pawn move(don,t care about promotion or en passent)
int Wp_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
    int n = 0;
if(movement[1] == '7'){
    if((movement[0] == movement[2]) && ((movement[3] == '6') || (movement[3] == '5')) && (!black_existance(movement)) && (!white_existance(movement))){
            n = 1;
    }
}
if(movement[1] - movement[3] == 1 && movement[0] == movement[2] && !black_existance(movement) && !white_existance(movement)){
        n = 1;
}
if(movement[1] - movement[3] == 1 && abs(movement[0] - movement[2]) == 1 && black_existance(movement)){
        n = 1;
}
return n;
}
}

//checking possibility of the black pawn move(don,t care about promotion or en passent)
int Bp_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
    int n = 0;
if(movement[1] == '2'){
    if((movement[0] == movement[2]) && ((movement[3] == '3') || (movement[3] == '4')) && (!black_existance(movement)) && (!white_existance(movement))){
        n = 1;
    }
}
if(movement[1] - movement[3] == -1 && movement[0] == movement[2] && !black_existance(movement) && !white_existance(movement)){
        n = 1;
}
if(movement[1] - movement[3] == -1 && abs(movement[0] - movement[2]) == 1 && white_existance(movement)){
        n = 1;
}
return n;
}
}

//checking the possibility of the white knite move
int Wn_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
if((((abs(movement[0] - movement[2]) == 2) && (abs(movement[1] - movement[3]) == 1)) || ((abs(movement[1] - movement[3]) == 2) && (abs(movement[0] - movement[2]) == 1))) && (!white_existance(movement)))
    return 1;
else
    return 0;
}
}

//checking the possibility of the black knite move
int Bn_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
if((((abs(movement[0] - movement[2]) == 2) && (abs(movement[1] - movement[3]) == 1)) || ((abs(movement[1] - movement[3]) == 2) && (abs(movement[0] - movement[2]) == 1))) && (!black_existance(movement)))
    return 1;
else
    return 0;
}
}

//checking the possibility of the white rook move
int Wr_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
if((movement[0] == movement[2]) && (movement[1] != movement[3]) && (!white_existance(movement))){
    int i = 0,n = 1;
    if(movement[3] > movement[1]){
        while(movement[1] + n < movement[3]){
            if((board[movement[1] + n - '1'][movement[0] - 'A'] != '-') && (board[movement[1] + n - '1'][movement[0] - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
    }
    else{
        while(movement[3] + n < movement[1]){
            if((board[movement[3] + n - '1'][movement[0] - 'A'] != '-') && (board[movement[3] + n - '1'][movement[0] - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
    }
}
else if((movement[0] != movement[2]) && (movement[1] == movement[3]) && (!white_existance(movement))){
        int i = 0,n = 1;
    if(movement[0] > movement[2]){
        while(movement[2] + n < movement[0]){
            if((board[movement[3] - '1'][movement[2] + n - 'A'] != '-') && (board[movement[3] - '1'][movement[2] + n - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
    }
    else{
        while(movement[0] + n < movement[2]){
            if(board[movement[3] - '1'][movement[0] + n - 'A'] != '-' && board[movement[3] - '1'][movement[0] + n - 'A'] != '.'){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
    }
}
else return 0;
}
}

//checking the possibility of the black rook move
int Br_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
if((movement[0] == movement[2]) && (movement[1] != movement[3]) && (!black_existance(movement))){
    int i = 0,n = 1;
    if(movement[3] > movement[1]){
        while(movement[1] + n < movement[3]){
            if((board[movement[1] + n - '1'][movement[0] - 'A'] != '-') && (board[movement[1] + n - '1'][movement[0] - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
    }
    else{
        while(movement[3] + n < movement[1]){
            if((board[movement[3] + n - '1'][movement[0] - 'A'] != '-') && (board[movement[3] + n - '1'][movement[0] - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
    }
}
else if((movement[0] != movement[2]) && (movement[1] == movement[3]) && (!black_existance(movement))){
        int i = 0,n = 1;
    if(movement[0] > movement[2]){
        while(movement[2] + n < movement[0]){
            if((board[movement[3] - '1'][movement[2] + n - 'A'] != '-') && (board[movement[3] - '1'][movement[2] + n - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
    }
    else{
        while(movement[0] + n < movement[2]){
            if(board[movement[3] - '1'][movement[0] + n - 'A'] != '-' && board[movement[3] - '1'][movement[0] + n - 'A'] != '.'){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
    }
}
else return 0;
}
}

//checking the possibility of white bishop move
int Wb_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
if((abs(movement[2] - movement[0]) == abs(movement[3] - movement[1])) && !white_existance(movement)){
int i = 0,n = 1;
if(((movement[0] - movement[2]) == (movement[1] - movement[3])) && (movement[0] > movement[2])){
    while(movement[2] + n < movement[0]){
            if((board[movement[3] - '1' + n][movement[2] + n - 'A'] != '-') && (board[movement[3] - '1' + n][movement[2] + n - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
}
else if(((movement[0] - movement[2]) == (movement[3] - movement[1])) && (movement[0] > movement[2])){
    while(movement[2] + n < movement[0]){
            if((board[movement[3] - '1' - n][movement[2] + n - 'A'] != '-') && (board[movement[3] - '1' - n][movement[2] + n - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
}
else if(((movement[0] - movement[2]) == (movement[1] - movement[3])) && (movement[0] < movement[2])){
    while(movement[0] + n < movement[2]){
            if((board[movement[1] - '1' + n][movement[0] + n - 'A'] != '-') && (board[movement[1] - '1' + n][movement[0] + n - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
}
else if(((movement[0] - movement[2]) == (movement[3] - movement[1])) && (movement[0] < movement[2])){
    while(movement[0] + n < movement[2]){
            if((board[movement[1] - '1' - n][movement[0] + n - 'A'] != '-') && (board[movement[1] - '1' - n][movement[0] + n - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
}
else return 0;
}
else return 0;
}
}

//checking the possibility of black bishop move
int Bb_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
if((abs(movement[2] - movement[0]) == abs(movement[3] - movement[1])) && !black_existance(movement)){
int i = 0,n = 1;
if(((movement[0] - movement[2]) == (movement[1] - movement[3])) && (movement[0] > movement[2])){
    while(movement[2] + n < movement[0]){
            if((board[movement[3] - '1' + n][movement[2] + n - 'A'] != '-') && (board[movement[3] - '1' + n][movement[2] + n - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
}
else if(((movement[0] - movement[2]) == (movement[3] - movement[1])) && (movement[0] > movement[2])){
    while(movement[2] + n < movement[0]){
            if((board[movement[3] - '1' - n][movement[2] + n - 'A'] != '-') && (board[movement[3] - '1' - n][movement[2] + n - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
}
else if(((movement[0] - movement[2]) == (movement[1] - movement[3])) && (movement[0] < movement[2])){
    while(movement[0] + n < movement[2]){
            if((board[movement[1] - '1' + n][movement[0] + n - 'A'] != '-') && (board[movement[1] - '1' + n][movement[0] + n - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
}
else if(((movement[0] - movement[2]) == (movement[3] - movement[1])) && (movement[0] < movement[2])){
    while(movement[0] + n < movement[2]){
            if((board[movement[1] - '1' - n][movement[0] + n - 'A'] != '-') && (board[movement[1] - '1' - n][movement[0] + n - 'A'] != '.')){
            i ++;
            }
            n++;
        }
        if(i == 0)return 1;
        else return 0;
}
else return 0;
}
else return 0;
}
}

//checking the possibility of the white queen move
int Wq_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
if(Wb_move_allowence(movement) || Wr_move_allowence(movement))
    return 1;
else
    return 0;
}
}

//checking the possibility of the black queen move
int Bq_move_allowence(char movement[]){
if(movement[0] < 'A' || movement[0] > 'H' || movement[1] < '1' || movement[1] > '8' || movement[2] < 'A' || movement[2] > 'H' || movement[3] < '1' || movement[3] > '8'){
    return 0;
}
else{
if(Bb_move_allowence(movement) || Br_move_allowence(movement))
    return 1;
else
    return 0;
}
}

//checking if the white king in check
int W_check(){
char a[5];
int f = 0;
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        if(board[i][j] == 'k'){
            a[2] = ('A' + j);
            a[3] = ('1' + i);
        }
    }
}
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        if(board[i][j] == 'P'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Bp_move_allowence(a))
                f = 1;
        }
        else if(board[i][j] == 'K'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Bk_move_allowence(a))
                f = 1;
        }
        else if(board[i][j] == 'N'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Bn_move_allowence(a))
                f = 1;
        }
        else if(board[i][j] == 'B'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Bb_move_allowence(a))
                f = 1;
        }
        else if(board[i][j] == 'R'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Br_move_allowence(a))
                f = 1;
        }
        else if(board[i][j] == 'Q'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Bq_move_allowence(a))
                f = 1;
        }
    }
}
return f;
}

//checking if the black king in check
int B_check(){
char a[5];
int f = 0;
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        if(board[i][j] == 'K'){
            a[2] = ('A' + j);
            a[3] = ('1' + i);
        }
    }
}
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        if(board[i][j] == 'p'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Wp_move_allowence(a))
                f = 1;
        }
        else if(board[i][j] == 'k'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Wk_move_allowence(a))
                f = 1;
        }
        else if(board[i][j] == 'n'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Wn_move_allowence(a))
                f = 1;
        }
        else if(board[i][j] == 'b'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Wb_move_allowence(a))
                f = 1;
        }
        else if(board[i][j] == 'r'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Wr_move_allowence(a))
                f = 1;
        }
        else if(board[i][j] == 'q'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            if(Wq_move_allowence(a))
                f = 1;
        }
    }
}
return f;
}

//returns the number of white items possible moves which will not make the white king in check
int W_allowed_moves(){
confirm_move();
char a[5];
int n = 0;
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        if(board[i][j] == 'p'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Wp_move_allowence(a)){
                        moving(a);
                        if(!W_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
        if(board[i][j] == 'k'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Wk_move_allowence(a)){
                        moving(a);
                        if(!W_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
        if(board[i][j] == 'n'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Wn_move_allowence(a)){
                        moving(a);
                        if(!W_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
        if(board[i][j] == 'b'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Wb_move_allowence(a)){
                        moving(a);
                        if(!W_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
        if(board[i][j] == 'r'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Wr_move_allowence(a)){
                        moving(a);
                        if(!W_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
        if(board[i][j] == 'q'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Wq_move_allowence(a)){
                        moving(a);
                        if(!W_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
    }
}
return n;
}

//returns the number of black items possible moves which will not make the black king in check
int B_allowed_moves(){
confirm_move();
char a[5];
int n = 0;
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        if(board[i][j] == 'P'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Bp_move_allowence(a)){
                        moving(a);
                        if(!B_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
        if(board[i][j] == 'K'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Bk_move_allowence(a)){
                        moving(a);
                        if(!B_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
        if(board[i][j] == 'N'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Bn_move_allowence(a)){
                        moving(a);
                        if(!B_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
        if(board[i][j] == 'B'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Bb_move_allowence(a)){
                        moving(a);
                        if(!B_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
        if(board[i][j] == 'R'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Br_move_allowence(a)){
                        moving(a);
                        if(!B_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
        if(board[i][j] == 'Q'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            for(int k = 0;k < 8;k++){
                for(int l = 0;l < 8;l++){
                    a[2] = ('A' + k);
                    a[3] = ('1' + l);
                    if(Bq_move_allowence(a)){
                        moving(a);
                        if(!B_check())
                            n++;
                        delete_move();
                    }
                }
            }
        }
    }
}
return n;
}

//checking if E8 or F8 or G8 are checked by black
int wr_castling(){
int n = 0;
char a[5];
char b[5];
char c[5];
a[2] = 'G';
a[3] = '8';
b[2] = 'F';
b[3] = '8';
c[2] = 'E';
c[3] = '8';
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        if(board[i][j] == 'P'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Bp_move_allowence(a) || Bp_move_allowence(b) || Bp_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'K'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Bk_move_allowence(a) || Bk_move_allowence(b) || Bk_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'N'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Bn_move_allowence(a) || Bn_move_allowence(b) || Bn_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'B'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Bb_move_allowence(a) || Bb_move_allowence(b) || Bb_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'R'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Br_move_allowence(a) || Br_move_allowence(b) || Br_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'Q'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Bq_move_allowence(a) || Bq_move_allowence(b) || Bq_move_allowence(c))
                n++;
        }
    }
}
return n;
}

//checking if C8 or D8 or E8 are checked by black
int wl_castling(){
int n = 0;
char a[5];
char b[5];
char c[5];
a[2] = 'C';
a[3] = '8';
b[2] = 'D';
b[3] = '8';
c[2] = 'E';
c[3] = '8';
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        if(board[i][j] == 'P'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Bp_move_allowence(a) || Bp_move_allowence(b) || Bp_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'K'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Bk_move_allowence(a) || Bk_move_allowence(b) || Bk_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'N'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Bn_move_allowence(a) || Bn_move_allowence(b) || Bn_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'B'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Bb_move_allowence(a) || Bb_move_allowence(b) || Bb_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'R'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Br_move_allowence(a) || Br_move_allowence(b) || Br_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'Q'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Bq_move_allowence(a) || Bq_move_allowence(b) || Bq_move_allowence(c))
                n++;
        }
    }
}
return n;
}

//checking if C1 or D1 or E1 are checked by white
int bl_castling(){
int n = 0;
char a[5];
char b[5];
char c[5];
a[2] = 'C';
a[3] = '1';
b[2] = 'D';
b[3] = '1';
c[2] = 'E';
c[3] = '1';
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        if(board[i][j] == 'p'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wp_move_allowence(a) || Wp_move_allowence(b) || Wp_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'k'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wk_move_allowence(a) || Wk_move_allowence(b) || Wk_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'n'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wn_move_allowence(a) || Wn_move_allowence(b) || Wn_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'b'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wb_move_allowence(a) || Wb_move_allowence(b) || Wb_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'r'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wr_move_allowence(a) || Wr_move_allowence(b) || Wr_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'q'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wq_move_allowence(a) || Wq_move_allowence(b) || Wq_move_allowence(c))
                n++;
        }
    }
}
return n;
}

//checking if E1 or F1 or G1 are checked by white
int br_castling(){
int n = 0;
char a[5];
char b[5];
char c[5];
a[2] = 'G';
a[3] = '1';
b[2] = 'F';
b[3] = '1';
c[2] = 'E';
c[3] = '1';
for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
        if(board[i][j] == 'p'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wp_move_allowence(a) || Wp_move_allowence(b) || Wp_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'k'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wk_move_allowence(a) || Wk_move_allowence(b) || Wk_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'n'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wn_move_allowence(a) || Wn_move_allowence(b) || Wn_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'b'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wb_move_allowence(a) || Wb_move_allowence(b) || Wb_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'r'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wr_move_allowence(a) || Wr_move_allowence(b) || Wr_move_allowence(c))
                n++;
        }
        else if(board[i][j] == 'q'){
            a[0] = ('A' + j);
            a[1] = ('1' + i);
            b[0] = ('A' + j);
            b[1] = ('1' + i);
            c[0] = ('A' + j);
            c[1] = ('1' + i);
            if(Wq_move_allowence(a) || Wq_move_allowence(b) || Wq_move_allowence(c))
                n++;
        }
    }
}
return n;
}

char board0[8][8];

//making all the moves again except last one or redo it
void undoorredo(){
    for(int i = 0;i < 8;i++){
        for(int j = 0;j < 8;j++){
            board[i][j] = board0[i][j];
        }
    }
    confirm_move();
    char W_move[6];
    char B_move[6];
    int B = 0,W = 0,wk = 0,bk = 0,wlr = 0,wrr = 0,blr = 0,brr = 0,p;
    int nmove = 0;
    num_captured = 0;
    while((num_moves) > nmove){
        while(W == 0 && (num_moves) > nmove){
            confirm_move();
            for(int i = 0;i < 4;i++){
                W_move[i] = moves[nmove][i];
            }
            nmove ++;
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'p'){
                if(Wp_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        confirm_move();

                        //promotion
                        if(W_move[3] == '1'){
                            p = moves[nmove - 1][4] - '0';
                                if(p == 1){
                                    board[0][W_move[2] - 'A'] = 'q';
                                    }
                                else if(p == 2){
                                    board[0][W_move[2] - 'A'] = 'r';
                                    }
                                else if(p == 3){
                                    board[0][W_move[2] - 'A'] = 'b';
                                    }
                                else if(p == 4){
                                    board[0][W_move[2] - 'A'] = 'n';
                                    }
                            }
                            confirm_move();
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
                //en passent
                if(B_move[1] == '2' && B_move[3] == '4' && ((B_move[0] - B_move[2]) == 0) && board[3][B_move[2] - 'A'] == 'P'){
                    if(W_move[1] == '4' && W_move[3] == '3' && abs(W_move[0] - W_move[2]) == 1 && W_move[2] == B_move[2]){
                        moving(W_move);
                        if(!W_check()){
                        W = 1;
                        capture(B_move);
                        if(((B_move[3] - '1') + (B_move[2] - 'A')) %2 == 0)
                            board[B_move[3] - '1'][B_move[2] - 'A'] = '.';
                        if(((B_move[3] - '1') + (B_move[2] - 'A')) %2 == 1)
                            board[B_move[3] - '1'][B_move[2] - 'A'] = '-';
                        confirm_move();
                        }
                        if(W_check()){
                            delete_move();
                        }
                    }
                }
            }
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'k'){
                if(wk == 0 && W_move[2] == 'G' && W_move[3] == '8' && wrr == 0 && board[7][7] == 'r' && board[7][6] == '-' && board[7][5] == '.' && board[7][4] == 'k' && !wr_castling()){
                    W = 1;
                    wk = 1;
                    wrr = 1;
                    moving(W_move);
                    board[7][7] = '.';
                    board[7][5] = 'r';
                    confirm_move();
                }
                else if(wk == 0 && W_move[2] == 'C' && W_move[3] == '8' && wlr == 0 && board[7][0] == 'r' && board[7][1] == '.' && board[7][2] == '-' && board[7][3] == '.' && board[7][4] == 'k' && !wl_castling()){
                    W = 1;
                    wk = 1;
                    wlr = 1;
                    moving(W_move);
                    board[7][0] = '-';
                    board[7][3] = 'r';
                    confirm_move();
                }
                else if(Wk_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        wk = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        confirm_move();
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
            }
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'q'){
                if(Wq_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        confirm_move();
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
            }
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'r'){
                if(Wr_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        confirm_move();
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
            }
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'n'){
                if(Wn_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        confirm_move();
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
            }
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'b'){
                if(Wb_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        confirm_move();
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
            }
            if(W == 0){
                nmove -= 1;
                W = 1;
            }
        }
        //castling requierments
        if(W_move[0] =='A' && W_move[1] == '8'){
                wlr = 1;
        }
        if(W_move[0] =='H' && W_move[1] == '8'){
                wrr = 1;
        }
        if(W_move[2] =='A' && W_move[3] == '1'){
                blr = 1;
        }
        if(W_move[2] =='H' && W_move[3] == '1'){
                brr = 1;
        }
        while(B == 0 && (num_moves) > nmove){
            confirm_move();
            for(int i = 0;i < 4;i++){
                B_move[i] = moves[nmove][i];
            }
            nmove ++;
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'P'){
                if(Bp_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        confirm_move();
                        //promotion
                        if(B_move[3] == '8'){
                            int p = moves[nmove - 1][4] - '0';
                                if(p == 1){
                                    board[7][B_move[2] - 'A'] = 'Q';
                                    }
                                if(p == 2){
                                    board[7][B_move[2] - 'A'] = 'R';
                                    }
                                if(p == 3){
                                    board[0][B_move[2] - 'A'] = 'B';
                                    }
                                if(p == 4){
                                    board[7][B_move[2] - 'A'] = 'N';
                                    }
                            }
                            confirm_move();
                    }
                    if(B_check()){
                        delete_move();
                    }
                }
                //en passent
                if(W_move[1] == '7' && W_move[3] == '5' && ((W_move[0] - W_move[2]) == 0) && board[4][W_move[2] - 'A'] == 'p'){
                    if(B_move[1] == '5' && B_move[3] == '6' && abs(B_move[2] - B_move[0]) == 1 && B_move[2] == W_move[2]){
                        moving(B_move);
                        if(!B_check()){
                        B = 1;
                        capture(W_move);
                        if(((W_move[3] - '1') + (W_move[2] - 'A')) %2 == 0)
                            board[W_move[3] - '1'][W_move[2] - 'A'] = '.';
                        else
                            board[W_move[3] - '1'][W_move[2] - 'A'] = '-';
                        confirm_move();
                        }
                        if(B_check()){
                            delete_move();
                        }
                    }
                }
            }
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'K'){
                if(bk == 0 && B_move[2] == 'G' && B_move[3] == '1' && brr == 0 && board[0][7] == 'R' && board[0][6] == '.' && board[0][5] == '-' && board[0][4] == 'K' && !br_castling()){
                    B = 1;
                    bk = 1;
                    brr = 1;
                    moving(B_move);
                    board[0][7] = '-';
                    board[0][5] = 'R';
                    confirm_move();
                }
                else if(bk == 0 && B_move[2] == 'C' && B_move[3] == '1' && blr == 0 && board[0][0] == 'R' && board[0][1] == '-' && board[0][2] == '.' && board[0][3] == '-' && board[0][4] == 'K' && !bl_castling()){
                    B = 1;
                    bk = 1;
                    blr = 1;
                    moving(B_move);
                    board[0][0] = '.';
                    board[0][3] = 'R';
                    confirm_move();
                }
                else if(Bk_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        bk = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        confirm_move();
                        }
                    if(B_check()){
                        delete_move();
                    }
                }
            }
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'Q'){
                if(Bq_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        confirm_move();
                        }
                    if(B_check()){
                        delete_move();
                    }
                }
            }
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'R'){
                if(Br_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        confirm_move();
                        }
                    if(B_check()){
                        delete_move();
                    }
                }
            }
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'N'){
                if(Bn_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        confirm_move();
                        }
                    if(B_check()){
                        delete_move();
                    }
                }
            }
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'B'){
                if(Bb_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        confirm_move();
                        }
                    if(B_check()){
                        delete_move();
                    }
                }
            }
        }
        //castling requierments
        if(B_move[0] =='A' && B_move[1] == '1'){
                blr = 1;
        }
        if(B_move[0] =='H' && B_move[1] == '1'){
                brr = 1;
        }
        if(B_move[2] =='A' && B_move[3] == '8'){
                wlr = 1;
        }
        if(B_move[2] =='H' && B_move[3] == '8'){
                wrr = 1;
        }
    W = 0;
    B = 0;
    }
}

//saving the file
void SAVE_FILE(int W){
FILE*fil_out;
FILE*Capture;

fil_out = fopen("lastgame.txt","w");
if(fil_out==NULL){
    printf ("\nNO FILE");
    exit(1);
}
for(int k = 0;k < 8;k++){
    for(int j = 0;j < 8;j++){
        fprintf(fil_out, "%c ", board[k][j]);
    }
}
fprintf(fil_out, "%d", W);
fclose(fil_out);
Capture = fopen("Capture.txt","a");
for(int i = 0;i < (num_captured - 1);i++){
    fprintf(Capture," %c ,", captured[i]);
}
fprintf(Capture, " %c,", captured[num_captured - 1]);
fclose(Capture);
}

//load the file
int LOAD_FILE(int W){
FILE*fil_out;

if(fil_out==NULL){
    printf ("\nNO FILE");
    exit(1);
}
fil_out=fopen("lastgame.txt", "r");
for(int k = 0;k < 8;k++){
    for(int j = 0;j < 8;j++){
        fscanf(fil_out,"  %c " , &board[k][j]);
    }
}
fscanf(fil_out, " %d", &W);
return W;
fclose(fil_out);

}
//load the file of capture
void LOAD_CAP(){
        FILE*Capture;
        int c;
        Capture = fopen("Capture.txt", "r");
        if(Capture == NULL){
            printf("\nNO FILE");
            exit(1);
        }
        while(1){
            c = fgetc(Capture);
        if(feof(Capture)){
            break;
        }
        if(c != 32){
                printf("%c ",c);
        }
        }
        fclose(Capture);
}

void SCapture(){
FILE*SCapture;
SCapture = fopen("SCapture.txt","a+");
    for(int i = 0;i < (num_captured - 1);i++){
        fprintf(SCapture," %c ,", captured[i]);
    }
    fprintf(SCapture, " %c", captured[num_captured - 1]);
    fprintf(SCapture, " %d",num_captured);
    for(int i = 0;i < (num_captured - 1);i++){
        fscanf(SCapture," %c ,", &captured[i]);
    }
    fscanf(SCapture, " %c", &captured[num_captured - 1]);
    fscanf(SCapture, " %d",&num_captured);

fclose(SCapture);
}
int main()
{
    int flag =0;
    int B = 0, W = 0, wk = 0, bk = 0, wlr = 0, wrr = 0, blr = 0, brr = 0, p;
    int d = 0;
    printf("Enter 2 to load the last game or any number else to enter a new game\n");
    scanf("%d", &d);
    printf("\nNOTE : The small letters are the white & The capital letters are the black\n");
    if(d == 2){
       W = LOAD_FILE(W);
       flag = 1;
    }
    if(d != 2){fclose(fopen("Capture.txt", "w"));
        fclose(fopen("lastgame.txt", "w"));}
    for(int i = 0;i < 8;i++){
        for(int j = 0;j < 8;j++){
            board0[i][j] = board[i][j];
        }
    }
    printf("\nWhile playing\nTo undo Enter 0, To redo Enter 1, To save game Enter 2\n");
    char W_move[6];
    char B_move[6];
    print_board();
    if(flag == 1&&W == 0){
        printf("\nCaptured items : ");
        LOAD_CAP();
    }
    d = 0;
    while(W_allowed_moves() && num_captured <= 30 && d == 0){
        while(W == 0 && W_allowed_moves()){
            confirm_move();
            printf("\nThe white's move : ");
            scanf("%s", W_move);
            if(W_move[0] == '0' && num_moves != 0){
                num_moves -= 1;
                undoorredo();
                W = 1;
            }
            if(W_move[0] == '1' && moves[num_moves][0] <= 'H' && moves[num_moves][0] >= 'A'){
                num_moves += 1;
                undoorredo();
                W = 1;
            }
            if(W_move[0] == '2'){
                //printf("%d",W);
                SAVE_FILE(W);
                return ;
            }
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'p'){
                if(Wp_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        //promotion
                        if(W_move[3] == '1'){
                                if(W_move[4] == 'Q'){
                                    board[0][W_move[2] - 'A'] = 'q';
                                    moves[num_moves][4] = '1';
                                    }
                                else if(W_move[4] == 'R'){
                                    board[0][W_move[2] - 'A'] = 'r';
                                    moves[num_moves][4] = '2';
                                    }
                                else if(W_move[4] == 'B'){
                                    board[0][W_move[2] - 'A'] = 'b';
                                    moves[num_moves][4] = '3';
                                    }
                                else if(W_move[4] == 'N'){
                                    board[0][W_move[2] - 'A'] = 'n';
                                    moves[num_moves][4] = '4';
                                    }
                                else{
                                    W = 0;
                                    delete_move();
                                }
                            confirm_move();
                        }
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
                //en passent
                if(B_move[1] == '2' && B_move[3] == '4' && ((B_move[0] - B_move[2]) == 0) && board[3][B_move[2] - 'A'] == 'P'){
                    if(W_move[1] == '4' && W_move[3] == '3' && abs(W_move[0] - W_move[2]) == 1 && W_move[2] == B_move[2]){
                        moving(W_move);
                        if(!W_check()){
                        W = 1;
                        capture(B_move);
                        if(((B_move[3] - '1') + (B_move[2] - 'A')) %2 == 0)
                            board[B_move[3] - '1'][B_move[2] - 'A'] = '.';
                        else
                            board[B_move[3] - '1'][B_move[2] - 'A'] = '-';
                        confirm_move();
                        }
                        if(W_check()){
                            delete_move();
                        }
                    }
                }
            }
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'k'){
                if(wk == 0 && W_move[2] == 'G' && W_move[3] == '8' && wrr == 0 && board[7][7] == 'r' && board[7][6] == '-' && board[7][5] == '.' && board[7][4] == 'k' && !wr_castling()){
                    W = 1;
                    wk = 1;
                    wrr = 1;
                    moving(W_move);
                    board[7][7] = '.';
                    board[7][5] = 'r';
                    confirm_move();
                }
                else if(wk == 0 && W_move[2] == 'C' && W_move[3] == '8' && wlr == 0 && board[7][0] == 'r' && board[7][1] == '.' && board[7][2] == '-' && board[7][3] == '.' && board[7][4] == 'k' && !wl_castling()){
                    W = 1;
                    wk = 1;
                    wlr = 1;
                    moving(W_move);
                    board[7][0] = '-';
                    board[7][3] = 'r';
                    confirm_move();
                }
                else if(Wk_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        wk = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        confirm_move();
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
            }
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'q'){
                if(Wq_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        confirm_move();
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
            }
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'r'){
                if(Wr_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        confirm_move();
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
            }
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'n'){
                if(Wn_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        confirm_move();
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
            }
            if(board[W_move[1] - '1'][W_move[0] - 'A'] == 'b'){
                if(Wb_move_allowence(W_move)){
                    moving(W_move);
                    if(!W_check()){
                        W = 1;
                        delete_move();
                        if(black_existance(W_move)){
                        capture(W_move);
                        }
                        moving(W_move);
                        confirm_move();
                    }
                    if(W_check()){
                        delete_move();
                    }
                }
            }
            if(W == 1 && W_move[0] != '0' && W_move[0] != '1' && W_move[0] != '2'){
                for(int i = 0;i < 4;i++){
                    moves[num_moves][i] = W_move[i];
                }
                num_moves += 1;
            }
            if(W == 0){
                printf("\nInvalid move!\n");
            }
        }
        if(B_check() && B_allowed_moves()){
            printf("\nCheck!!!!!!!!      Black king in danger\n");
        }
        print_board();
        printf("\nCaptured items : ");
        if(flag==1){LOAD_CAP();}
          if(flag==0 || B==0)
         {print_caotured();}

        printf("\n");
        //castling requierments
        if(W_move[0] =='A' && W_move[1] == '8'){
                wlr = 1;
            }
            if(W_move[0] =='H' && W_move[1] == '8'){
                wrr = 1;
            }
            if(W_move[2] =='A' && W_move[3] == '1'){
                blr = 1;
            }
            if(W_move[2] =='H' && W_move[3] == '1'){
                brr = 1;
            }
        while(B == 0 && B_allowed_moves() && W != 0){
            confirm_move();
            printf("\nThe black's move : ");
            scanf("%s", B_move);
            if(B_move[0] == '0' && num_moves != 0){
                num_moves -= 1;
                undoorredo();
                B = 1;
            }
            if(B_move[0] == '1' && moves[num_moves][0] <= 'H' && moves[num_moves][0] >= 'A'){
                num_moves += 1;
                undoorredo();
                B = 1;
            }
            if(B_move[0] == '2'){
                SAVE_FILE(W);
                //printf("%d",W);
                return ;
            }
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'P'){
                if(Bp_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        //promotion
                        if(B_move[3] == '8'){
                                if(B_move[4] == 'Q'){
                                    board[7][B_move[2] - 'A'] = 'Q';
                                    moves[num_moves][4] = '1';
                                    }
                                else if(B_move[4] == 'R'){
                                    board[7][B_move[2] - 'A'] = 'R';
                                    moves[num_moves][4] = '2';
                                    }
                                else if(B_move[4] == 'B'){
                                    board[7][B_move[2] - 'A'] = 'B';
                                    moves[num_moves][4] = '3';
                                    }
                                else if(B_move[4] == 'N'){
                                    board[7][B_move[2] - 'A'] = 'N';
                                    moves[num_moves][4] = '4';
                                    }
                                else{
                                    B = 0;
                                    delete_move();
                                }
                            confirm_move();
                        }
                    }
                    if(B_check()){
                        delete_move();
                    }
                }
                //en passent
                if(W_move[1] == '7' && W_move[3] == '5' && ((W_move[0] - W_move[2]) == 0) && board[4][W_move[2] - 'A'] == 'p'){
                    if(B_move[1] == '5' && B_move[3] == '6' && abs(B_move[2] - B_move[0]) == 1 && B_move[2] == W_move[2]){
                        moving(B_move);
                        if(!B_check()){
                        B = 1;
                        capture(W_move);
                        if(((W_move[3] - '1') + (W_move[2] - 'A')) %2 == 0)
                            board[W_move[3] - '1'][W_move[2] - 'A'] = '.';
                        else
                            board[W_move[3] - '1'][W_move[2] - 'A'] = '-';
                        confirm_move();
                        }
                        if(B_check()){
                            delete_move();
                        }
                    }
                }
            }
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'K'){
                if(bk == 0 && B_move[2] == 'G' && B_move[3] == '1' && brr == 0 && board[0][7] == 'R' && board[0][6] == '.' && board[0][5] == '-' && board[0][4] == 'K' && !br_castling()){
                    B = 1;
                    bk = 1;
                    brr = 1;
                    moving(B_move);
                    board[0][7] = '-';
                    board[0][5] = 'R';
                    confirm_move();
                }
                else if(bk == 0 && B_move[2] == 'C' && B_move[3] == '1' && blr == 0 && board[0][0] == 'R' && board[0][1] == '-' && board[0][2] == '.' && board[0][3] == '-' && board[0][4] == 'K' && !bl_castling()){
                    B = 1;
                    bk = 1;
                    blr = 1;
                    moving(B_move);
                    board[0][0] = '.';
                    board[0][3] = 'R';
                    confirm_move();
                }
                else if(Bk_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        bk = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        confirm_move();
                        }
                    if(B_check()){
                        delete_move();
                    }
                }
            }
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'Q'){
                if(Bq_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        confirm_move();
                        }
                    if(B_check()){
                        delete_move();
                    }
                }
            }
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'R'){
                if(Br_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        confirm_move();
                        }
                    if(B_check()){
                        delete_move();
                    }
                }
            }
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'N'){
                if(Bn_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        confirm_move();
                        }
                    if(B_check()){
                        delete_move();
                    }
                }
            }
            if(board[B_move[1] - '1'][B_move[0] - 'A'] == 'B'){
                if(Bb_move_allowence(B_move)){
                    moving(B_move);
                    if(!B_check()){
                        B = 1;
                        delete_move();
                        if(white_existance(B_move)){
                        capture(B_move);
                        }
                        moving(B_move);
                        confirm_move();
                        }
                    if(B_check()){
                        delete_move();
                    }
                }
            }
            if(B == 1 && B_move[0] != '0' && B_move[0] != '1' && B_move[0] != '2'){
                for(int i = 0;i < 4;i++){
                    moves[num_moves][i] = B_move[i];
                }
                num_moves += 1;
            }
            else if(B == 0){
                printf("\nInvalid move!\n");
            }
        }
        if(B == 0){
            d = 1;
        }
        if(W_check() && W_allowed_moves()){
            printf("\nCheck!!!!!!!!      White king in danger\n");
        }
        print_board();
        printf("\nCaptured items : ");
        if(flag==1){LOAD_CAP();}
       if(flag==0 || W==1)
         {print_caotured();}

        printf("\n");
        //castling requierments
        if(B_move[0] =='A' && B_move[1] == '1'){
                blr = 1;
        }
        if(B_move[0] =='H' && B_move[1] == '1'){
                brr = 1;
        }
        if(B_move[2] =='A' && B_move[3] == '8'){
                wlr = 1;
        }
        if(B_move[2] =='H' && B_move[3] == '8'){
                wrr = 1;
        }
    W = 0;
    B = 0;
    }
    if(W_check() && !W_allowed_moves())
        printf("\nCheckmate!!!!!!!!!!    Black wins");
    else if(B_check() && !B_allowed_moves())
        printf("\nCheckmate!!!!!!!!!!    White wins");
    else if((!W_allowed_moves() || B_allowed_moves()) && !(W_check() || B_check()))
        printf("\nstalemate!!!!!!!!!!    Draw");
    else
        printf("\nDraw");
    return 0;
}
