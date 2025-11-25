#include <stdio.h>
#include <time.h>
#include<string.h>
#include<stdlib.h>
void rules();
int levels();
int level;
int type_test(const char *sentence);
void save_score(const char *name , float score);
float score = 0;


void print_colored_sentence(const char *sentence, int level) {
    const char *color;
    if (level ==1){
	
        color= "\033[33m";  // yellow for easy
    }
    else{

        color = "\033[36m";  // cyan for hard
    }

    printf("%s%s\033[0m\n", color, sentence);  // print sentence with color
}

void save_score(const char *name , float score){
    FILE *file = fopen("scores.txt" , "a");   //a is used for append
    fprintf(file , "\n\nNAME :%s" , name);
    fprintf(file , "level(1.easy , 2.hard):%d\n" , level);
    fprintf(file , "SCORE :%.2f/5\n" , score);
    
     if (file==NULL) {
        printf("Error\n");
        return;
    }
    fclose(file);
    printf("\nscores saved!!");
}


void rules(){
	printf("1. Your goal is to type the displayed sentence exactly as shown.\n2. Capitalization, spaces, and punctuation must be correct.\n3. The timer starts as soon as the sentence is displayed.\n4. Press 'Enter' after completing the sentence.\n5. Accuracy must be 99% or higher to earn a point.\n6. Word Per Second (WPS) and accuracy will be shown after each sentence.\n7. You will be given 5 sentences to type.\n8. Your final score will be out of 5.\n9. Do not use backspace while typing (if possible).\n10. Try to complete the sentence as fast and accurately as possible.\nGOOD LUCK!");
}
int levels(){
	printf("choose between\n\033[33m1.EASY MODE\n\033[36m2.HARD MODE\033[0m\n");
	scanf("%d" , &level);
	return level;
}
	

int type_test(const char *sentence){
		char uw[300] ;
		
		int ch;
while((ch = getchar()) != '\n' && ch != EOF);           //when enter is pressed it clears the buffer including \n
		printf("\n\ntype the following sentence:\n");
		print_colored_sentence(sentence , level);
		time_t start, end;
        time(&start);       //to record the start time 
		fgets(uw, sizeof(uw), stdin);
			time(&end);       //to record the end time
			
	uw[strcspn(uw, "\n")] = '\0';       //remove newline from input
			
			double time_taken = difftime(end, start);   //to calc time taken
				int len = strlen(sentence);
			
			float wps = len/time_taken;
int correct = 0;
for (int i =0 ; i<len ; i++){
	if(sentence[i] == uw[i]){
		correct ++;
	}
}
for(int i =0; i <strlen(sentence); i++){
    if(sentence[i] != uw[i]){
        printf("^"); // mistake
    } 
	else {
        printf(" ");
    }
}
double acc = ((double)correct/len)*100;
	

		printf("\naccuracy is:%.2f %%", acc);
		printf("\nword per second count is :%.2f" , wps);     //words in one second
		if(acc > 99){
			score+=1;
		}
		else if(acc>=90){
			score+=0.5;
		}
		printf("\nscore:%.2f" , score);
		return score;
}

int main() {
	while(1){
		#ifdef _WIN32
			system("cls");    //clearing windows screen
		#else
			system("clear");            // for mac
		#endif
	int menu;
	char name[50];
  printf("\033[32m======================================= WELCOME TO TYPING TUTOR ======================================================\033[0m \n\n");
  printf("---------MAIN MENU------------\n");
  printf("1.START \n2.VIEW RULES\n");
  scanf("%d" , &menu);
  getchar();     //used to clear out previous 
  switch(menu){
  	case 1:
  		
  	printf("enter your name: ");
  fgets(name, sizeof(name), stdin);
  score = 0;
  	levels();
  	if(level == 1){
  			printf("\neasy mode selected!");
  		type_test("Humans have 206 bones");
  		type_test("Your heart pumps blood through your body");
  		type_test("Earth revolves around sun");
  		type_test("Save the File!");
  		type_test("Accuracy is more important than speed");
	  }
	  else{
	     type_test("#codelikeApro@$");
	      type_test("That will be $20,847,817.92 (*** plus 5% tax)!");
        type_test("Fact #417: 2^8 is 2^(2^2)*2^(2^2))!");
    type_test("#4 hotdogs, 50% off @ 1$ ea. for Jim & I (*** w/o ketchup)!");
            type_test("The Milky Way contains over 100400 billion stars and moves at ~220 km/s around its center.");
            
		  }
		  printf("\n\nNAME: %sfinal score:%d/5\n" , name , score);
  if(score == 5){
  	printf("well done");
  }
  else if(score ==4){
  	printf("Practice more");
  }
  else{
  	printf("You need to work hard");
  }
  
  save_score(name , score);
  		break;	
  	case 2:
  	rules();
  	printf("\nenter space to return back to the menu!");
  	getchar();
  		
  	break;
  		
  	default:
  		printf("invalid");
  }
  }
    return 0;
}


