#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char *value;
    int state;
}square;

void default_square(square *sq) {
    
    for(int i = 0; i <= sizeof(*sq); i++)
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

int win(int play[15], int pc_play[15], square *sq)
{
    for(int i = 0; i < 15; i++) {
        if((play[i] && play[i+2] && play[i+4]) || play[i] && play[i+3] && play[i+6]
        || play[i] && play[i+4] && play[i+8] || ((i + 3) % 3 == 0) && play[i] && play[i+1] && play[i+2])
        {
            printf("USER WINS!\n");
            
            return 1;
        }
        
        if((pc_play[i] && pc_play[i+2] && pc_play[i+4]) || (pc_play[i] && pc_play[i+4] && pc_play[i+8] && i == 0) || (pc_play[i] && pc_play[i+2] && pc_play[i+4] && i == 2) || pc_play[i] && pc_play[i+3] && pc_play[i+6]
        || pc_play[i] && pc_play[i+4] && pc_play[i+8] || ((i + 3) % 3 == 0) && pc_play[i] && pc_play[i+1] && pc_play[i+2])
        {
            printf("PC WINS!\n");
            system("pause");
            return 2;
        }
    }
    
    return 0;
}

void corners_pos(int corner[4]){

    int k = 0;

    for(int i = 0; i < 4; i++)
    {
        //printf("corners =%d\n", k);
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

int *check_usr_p(int play[9], int corner[4]) {
    
    static int corner_p[4];
    int j = 0;
        
        for(int i = 0; i < 9; i++)
        {
            for(int k = 0; k < 4; k++)
            {
                //printf("numb = %d\n", corner[k]);

                if(play[i] && i == corner[k])
                {
                    corner_p[k] = i+1;
                }
            }
        }

    return corner_p;
}

int random_losangle(int a, int b, int c, int d)
{
    int random = rand() % 4;

    switch(random)
    {
        case 0:
            return a;
            break;
        case 1:
            return b;
            break;
        case 2:
            return c;
            break;
        case 3:
            return d;
            break;

        default:
            break;
    }
}

int p2defend(square *sq, int usr_play[15],int play[15]) {
    int a = 0;
    int con = 0;
    
    /*
    for(int i = 0; i < 15; i++)
    {
        if(play[15])
            con++;
    }
    */
   
     for(int i = 0; i < 15; i++) {
         
        if((usr_play[i] && usr_play[i+1] && !usr_play[i+2] && !play[i+2] && i != 2 && i != 5 && i != 8))
         {
             

            if(!((i+3)%3))
            {
                a = 1;

                play[i+2] = 1;

                sq = sq + (i+2);
                sq->value = "O";
                sq = sq - (i+2);

            }
            else if(!play[i-1])
            {
                a = 1;

                play[i-1] = 1;

                sq = sq + (i-1);
                sq->value = "O";
                sq = sq - (i-1);
            }

            
        }

        if((usr_play[i] && !usr_play[i+1] && !play[i+1] && usr_play[i+2] && (i == 0 || i == 3 || i == 6)))
        {
            a = 1;

            play[i+1] = 1;

            sq = sq + (i+1);
            sq->value = "O";
            sq = sq - (i+1);
        }

        if((usr_play[i] && usr_play[i+3] && !usr_play[i+6] && !play[i+6] && i != 6 && i != 7 && i != 8))
        {

            if(i < 3)
            {
                a = 1;

                play[i+6] = 1;
                sq = sq + (i+6);
                sq->value = "O";
                sq = sq - (i+6);
            }
            else if(!play[i-3])
            {
                a = 1;

                play[i-3] = 1;
                sq = sq + (i-3);
                sq->value = "O";
                sq = sq - (i-3);
            }
        }

        if((usr_play[i] && !usr_play[i+3] && !play[i+3] && usr_play[i+6] && (i == 0 || i == 2 || i == 3)))
        {
            a = 1;

            play[i+3] = 1;
            sq = sq + (i+3);
            sq->value = "O";
            sq = sq - (i+3);
        }

        if(usr_play[i] && usr_play[i+4] && !usr_play[i+8] && !play[i+8] && (i == 0 || i == 4))
        {
            
            if(!i)
            {
                a = 1;

                play[i+8] = 1;
                sq = sq + (i+8);
                sq->value = "O";
                sq = sq - (i+8);
            }
            else if(!play[i-4])
            {
                a = 1;
                play[i-4] = 1;
                sq = sq + (i-4);
                sq->value = "O";
                sq = sq - (i-4);
            }
        }

        if(usr_play[i] && usr_play[i+2] && !usr_play[i+4] && !usr_play[i+4] && (i == 2 || i == 4))
        {
             

            if(!i)
            {
                a = 1;

                play[i+4] = 1;
                sq = sq + (i+4);
                sq->value = "O";
                sq = sq - (i+4);
            }
            else if(!play[i-2])
            {
                a = 1;

                play[i-2] = 1;
                sq = sq + (i-2);
                sq->value = "O";
                sq = sq - (i-2);
            }
        }
    }
    return a;
}

    int p2win(square *sq,int u_play[15], int usr_play[15]) {
        int a = 0;

        for(int i = 0; i < 15; i++) {
            if((usr_play[i] && usr_play[i+1] && !u_play[i+2] && i != 2 && i != 5 && i != 8))
            {
            
                if(!((i+3)%3))
                {
                    a = 1;
                    usr_play[i+2] = 1;
                    sq = sq + (i+2);
                    sq->value = "O";
                    sq = sq - (i+2);
                }
                else if(!u_play[i-1])
                {
                    a = 1;
                    usr_play[i-1] = 1;
                    sq = sq + (i-1);
                    sq->value = "O";
                    sq = sq - (i-1);
                }
            }

            if((usr_play[i] && !u_play[i+1] && usr_play[i+2] && (i == 0 || i == 3 || i == 6)))
            {
                a = 1;

                usr_play[i+1] = 1;
                sq = sq + (i+1);
                sq->value = "O";
                sq = sq - (i+1);
            }

            if((usr_play[i] && usr_play[i+3] && !u_play[i+6] && i != 6 && i != 7 && i != 8))
            {            

                if(i < 3)
                {
                    a = 1;
                    usr_play[i+6] = 1;
                    sq = sq + (i+6);
                    sq->value = "O";
                    sq = sq - (i+6);
                }
                else if(!u_play[i-3])
                {
                    a = 1;
                    usr_play[i-3] = 1;
                    sq = sq + (i-3);
                    sq->value = "O";
                    sq = sq - (i-3);
                }
            }

            if((usr_play[i] && !u_play[i+3] && usr_play[i+6] && (i == 0 || i == 2 || i == 3)))
            {
                a = 1;

                usr_play[i+3] = 1;
                sq = sq + (i+3);
                sq->value = "O";
                sq = sq - (i+3);
            }

            if(usr_play[i] && usr_play[i+4] && !u_play[i+8] && (i == 0 || i == 4))
            {
                

                if(!i)
                {
                    a = 1;
                    usr_play[i+8] = 1;
                    sq = sq + (i+8);
                    sq->value = "O";
                    sq = sq - (i+8);
                }
                else if(!u_play[i-4])
                {
                    a = 1;
                    usr_play[i-4] = 1;
                    sq = sq + (i-4);
                    sq->value = "O";
                    sq = sq - (i-4);
                }
            }

            if(usr_play[i] && usr_play[i+2] && !u_play[i+4]  && (i == 2 || i == 4))
            {
                 
                if(i == 2)
                {
                    a = 1;
                    usr_play[i+4] = 1;
                    sq = sq + (i+4);
                    sq->value = "O";
                    sq = sq - (i+4);
                }
                else if(!u_play[i-2])
                {
                    a = 1;
                    usr_play[i-2] = 1;
                    sq = sq + (i-2);
                    sq->value = "O";
                    sq = sq - (i-2);
                }
            }
        }
        
        return a;
    }

void pc_move(square *sq, int corn[4], int play[15], int usr_play[15]) {
    int aux = 0;
    srand(time(NULL));
    int random = rand() % 4;
    
    int random_p;

    int moves = 0;
    moves = count_moves(sq);

    if(moves >= 3)
    {   
        aux = p2win(sq, usr_play, play);
       //  if(!aux)
          //  exit(0);

        if(!aux)
            aux = p2defend(sq, usr_play, play);

    }

    //printf("moves = %d\n", moves);

    if(moves == 1)
    {
        aux = 1;
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

    if(moves == 3)
    {
        //pc pla
    

        if(play[4])
        {

            int *corner;

            corner = check_usr_p(usr_play,corn);

            //printf("size = %d\n", sizeof(corner));


            if(usr_play[0] && usr_play[8] || usr_play[2] && usr_play[6])
            {
                random_p = random_losangle(1,3,5,7); 
                aux = 1;

                play[random_p] = 1;

                sq += random_p;
                sq->value = "O";
                sq -= random_p;
            }

            //check_if_win
        }
    }


    if(!aux)
    {
        
        int cont = 0;
        int random_a = 0;

        for(int i = 0; i <= sizeof(*sq); i++)
        {
            if(sq->value == "-" && (i == 0 || i == 2 ||i == 6 || i == 8))
                cont++;

            sq++;
        }

        
        
         for(int i = 0; i <= sizeof(*sq); i++)
            sq--;

        if(cont)
        {
           

            if(play[random_a] || usr_play[random_a])
            {
                while(play[random_a] || usr_play[random_a])
                {
                
                    random_a = random_losangle(0,2,6,8);
                
                }
                play[random_a] = 1;

            sq += random_a;
            sq->value = "O";
            sq -= random_a;  
            }
            else
            {
             play[random_a] = 1;

            sq += random_a;
            sq->value = "O";
            sq -= random_a;   
            }
            

            
        }
        else
        {
            int b = -1;

            for(int i = 0; i <= sizeof(*sq); i++)
            {
                if(sq->value == "-")
                {
                    b = i;
                }

                sq++;
            }

            for(int i = 0; i <= sizeof(*sq); i++)
                sq--;

            if(b > 0)
            {
                play[b] = 1;

                sq += b;
                sq->value = "O";
                sq -= b; 
            }
        }
        

        
        

        /*
        int *a_corners;
        int random_a = 0;
        int dif = 1;
        int igual = 0;
   
        a_corners = avaible_corners(sq);

        while(igual)
        {
            
            random_a = random_losangle(1,3,5,7); 

            for(int i = 0; i <= 3; i++)
            {
                if(a_corners[i] == random_a)
                    igual = 1;
            }
        }
            //printf(a_corners[i]);
        
       */

    }
}

int draw(square *sq)
{
    int count = 0;
        
    for(int i = 0; i <= sizeof(*sq); i++)
    {
        if(strcmp(sq->value,"-"))
            count++;

        sq++;
        //a
    }

    for(int i = 0; i <= sizeof(*sq); i++)
        sq--;

    if(count == 9)
        return 1;
    else
        return 0;
}

void play(square *sq, int play[9],int pc_p[9], int corn[4]) {

    int usr_choice;
    
    while(!win(play,pc_p,sq)) {
        printf("\nChoose the position: ");
        scanf("%d",&usr_choice);

        sq = sq + (usr_choice-1);

    
        if(sq->value != "-" &&  usr_choice >= 1 && usr_choice <= 9)
        {
            //sq -= usr_choice-1;

            printf("Someone already played there!\n");
            system("pause");
            print_square(sq); 
        }
        else if(!(usr_choice >= 1 && usr_choice <= 9))
        {
            //sq -= usr_choice-1;

            printf("Choose a number between 1 and 9!\n");
            system("pause");
            system("cls");
            print_square(sq);
        }
        else
        {
            play[usr_choice-1] = 1;

            
            sq->value = "X";
            sq = sq - (usr_choice-1);
            
            system("cls");
            pc_move(sq, corn, pc_p, play);
            print_square(sq);
        }

        if(draw(sq))
        {
            printf("It's a draw!\n");
            system("pause");
            break;
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