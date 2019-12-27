#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char *value;
    int state;
}square;

void default_square(square *sq) {
    
    for(int i = 0; i <=  sizeof(*sq); i++)
    {
       sq->value = "-";
       sq->state = 0;
       sq++;
    }
}

void default_play(int play[15]) {

    for (int i = 0; i < 15; i++)
    {
        play[i] = 0;
    }
}

void help_square() {
    
    for(int i = 0; i <  9; i++)
    {
       printf("%d\t", (i+1));

       if(!((i+1) % 3))
           printf("\n");
    }
}

void print_square(square *sq) {

    for(int i = 0; i <=  sizeof(*sq); i++)
    {
       printf("%s\t", sq->value);
       sq++;

       if(!((i+1) % 3))
           printf("\n");
    }
}

int win(int play[15], square *sq)
{
    for(int i = 0; i < 15; i++) {
        if((play[i] && play[i+2] && play[i+4]) || play[i] && play[i+3] && play[i+6]
        || play[i] && play[i+4] && play[i+8] || ((i + 3) % 3 == 0) && play[i] && play[i+1] && play[i+2])
        {
            return 1;
        }
    }
    return 0;
}

void corners_pos(int corner[4]){

    int k = 0;

    for(int i = 0; i < 4; i++)
    {
        corner[i] = k;

        if(!((i + 2) % 2))
            k += 2;
        else
            k += 4;
    }
}

int count_moves(square *sq) {

    int count = 0;

    for(int i = 0; i <= sizeof(*sq); i++)
    {
        if(sq->value != "-")
        {
            count++;
        }
        sq++;
    }

    return count;
}

int check_usr_p(int play[9], int corner[4]) {
    
        for(int i = 0; i < 9; i++)
        {
            for(int k = 0; k < 4; k++)
            {
                if(play[i] && i == corner[k])
                    return i;
            }
        }

        return 0;
}

void pc_move(square *sq, int corn[4], int play[15], int usr_play[15]) {

    srand(time(NULL));
    int random = rand() % 4;

    int moves = 0;
    moves = count_moves(sq);

    // can´t count 9

    //printf("moves = %d\n", moves);

    if(moves == 1)
    {
        sq += 4;
        
        if(sq->value == "-")
        {
            sq->value = "O";
            play[4] = 1;

            sq -= 4;
        }
        else
        {
             sq -= 4;

            //printf("random = %d\n", random);
            //printf("corner = %d\n", corn[random]);
            
            play[corn[random]] = 1;
            
            sq += corn[random];
            sq->value = "O";
            sq -= corn[random];
        }
    }
    
    //print_square(sq);
    if(moves > 2)
    {
        if(play[4])
        {
            int corner;

            corner = check_usr_p(usr_play,corn);

            printf("corner = %d\n", corner);
        }
    }
}

void play(square *sq, int play[9],int pc_p[9], int corn[4]) {

    int usr_choice;

    while(!win(play,sq)) {
        printf("\nChoose the position: ");
        scanf("%d",&usr_choice);

        sq += usr_choice-1;

        printf("user_choice = %d\n", usr_choice);

        if(sq->value != "-" &&  usr_choice >= 1 && usr_choice <= 9)
        {
            sq -= usr_choice-1;

            printf("Someone already played there!\n");
            system("pause");
            print_square(sq); 
        }
        else if(!(usr_choice >= 1 && usr_choice <= 9))
        {
            sq -= usr_choice-1;

            printf("Choose a number between 1 and 9!\n");
            system("pause");
            system("cls");
            print_square(sq);
        }
        else
        {
            sq->value = "X";
            play[usr_choice-1] = 1;

            sq -= usr_choice-1;
            
            system("cls");
            pc_move(sq, corn, pc_p, play);
            print_square(sq);
        }
    }
}

int main() {
    square sq[9];
    int option;
    int usr_play[15];
    int pc_play[15];
    int corner[4];

    int a;

    default_square(sq);
    default_play(usr_play);
    default_play(pc_play);
    corners_pos(corner);

    printf("\t\t Welcome to TicTacToe!\n");
    printf("------------------------------------------\n\n");

    do {
        printf("Main Menu\n");
        printf("1. Play against the computer.\n");
        printf("2. How to play.\n");
        printf("0. Quit.\n");
        printf(" Please enter an option from the main menu: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                system("cls");
                
                help_square(); 
                play(sq, usr_play, pc_play, corner);
                
                system("cls");

                print_square(sq);
                default_square(sq);
                default_play(usr_play);
                default_play(pc_play);
                
                system("pause");
                system("cls");

                break;
            case 2:
                system("cls");

                help_square(); 
                printf("\nEach number in the table above represents the position your going to play.\n");

                system("pause");
                system("cls");
                break;
            case 0:
                printf("Bye bye!");
                break;
            default:
                printf("Option unavailable! Try again.\n\n");
                //system("pause");
                //system("cls");
                break;
    }

    }while(option != 0);

    return 0;
}