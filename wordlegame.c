#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
void random_word_maker(char *word);
void letter_to_board(int *board);
void check_guess(char *guess, char *secret, char *feedback, int *board);
int  valid_guess(char *guess);

void random_word_maker(char *word)
{
    FILE *dosya;
    int   count = 0;
    int   random_index, i;
    char  temp[20];
 
    dosya = fopen("word.txt", "r");
 
    if (dosya == NULL) 
	{
        printf("Hata: word.txt dosyasi bulunamadi!\n");
    }
 
    while (fscanf(dosya, "%19s", temp) == 1)
        count++;
 
    if (count == 0) 
	{
        fclose(dosya);
    }
 
    rewind(dosya);
    random_index = rand() % count;
 
    for (i = 0; i <= random_index; i++)
        fscanf(dosya, "%19s", word);
 
    fclose(dosya);
    
    for (i = 0; word[i]; i++)
        word[i] = (char)tolower((unsigned char)word[i]);
}
void letter_to_board(int *board) 
{
    int i;
    printf("--- Harf Tahtasi ---\n");
    printf("Kalan harfler : ");
    for (i = 0; i < 26; i++) 
	{
        if (board[i] >= 1)
            printf("%c ", 'a' + i);
    }
    printf("\n");
}
 

void check_guess(char *guess, char *secret, char *feedback, int *board) 
{
    int i, j;
    int found;
    char used[5];   
 
    memset(used, 0, sizeof(used));
 
    for (i = 0; i < 5; i++) 
	{
        if (guess[i] == secret[i]) {
        	
            feedback[i] = '+';
            used[i] = 1;
            board[guess[i] - 'a'] = 2;
        } else 
		{
            feedback[i] = 0; 
        }
    }
 
    for (i = 0; i < 5; i++) 
	{
        if (feedback[i] == '+') continue;
 
        found = 0;
        for (j = 0; j < 5; j++) 
		{
            if (!used[j] && guess[i] == secret[j]) 
			{
                found = 1;
                used[j] = 1;
                break;
            }
        }
 
        if (found) 
		{
            feedback[i] = '?';
            if (board[guess[i] - 'a'] != 2)
                board[guess[i] - 'a'] = 1; 
        } else 
		{
            feedback[i] = 'X';
            if (board[guess[i] - 'a'] == 1)
                board[guess[i] - 'a'] = 0;
        }
    }
 
    feedback[5] = '\0';
}
int valid_guess(char *guess) 
{
    int i;
    if ((int)strlen(guess) != 5) 
	{
        printf("Hata: Tam olarak 5 harf girmelisiniz!\n");
        return 0;
    }
    for (i = 0; i < 5; i++) 
	{
        if (!isalpha((unsigned char)guess[i])) 
		{
            printf("Hata: Sadece harf girebilirsiniz!\n");
            return 0;
        }
    }
    return 1;
}
int main() 
{
    char play_again;
    char secret_word[6];
    char guess[20];
    char feedback[6];
    int  board[26];
    int  attempt;
    int  i;
    int  won;
 
    srand((unsigned int)time(NULL));
 
    do 
	{
        random_word_maker(secret_word);
 
        for (i = 0; i < 26; i++)
            board[i] = 1;
 
        won = 0;
 
        for (attempt = 1; attempt <= 10; attempt++) 
		{
            letter_to_board(board);
            printf("Deneme %2d: ", attempt);
 
            do 
			{
                scanf("%19s", guess);
                for (i = 0; guess[i]; i++)
                    guess[i] = (char)tolower((unsigned char)guess[i]);
            } 
			while (!valid_guess(guess));
 
            check_guess(guess, secret_word, feedback, board);
 
            printf("Sonuc    : ");
            for (i = 0; i < 5; i++)
                printf("%c ", feedback[i]);
            printf("\n\n");
 
            if (strcmp(feedback, "+++++") == 0) 
			{
                won = 1;
                printf("Tebrikler! Kelimeyi buldunuz. \n\n",
                       attempt, secret_word);
                break;
            }
        }
 
       if (!won)
       {
       	    printf("Kaybettiniz! 10 hakkinizi da kullandiniz.\n");
    		printf("Gizli kelime: %s\n\n", secret_word);
	   }
	   printf("Tekrar oynamak ister misiniz? (y/n): ");
       scanf(" %c", &play_again);
   	   printf("\n");
   }
	while (play_again == 'y' || play_again == 'Y');
    printf("Oynadiginiz icin tesekkurler.");
 
    return 0;
}
