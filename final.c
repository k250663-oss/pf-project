#include <stdio.h>
#include <time.h>         //for timer
#include<string.h>
#include<stdlib.h>                  //for clearing screen
#include<unistd.h>             //for usleep - transition
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
	char *lvl_ptr;
    FILE *file = fopen("scores.txt" , "a");   //a is used for append
     if (file==NULL) {
        printf("Error\n");
        return;
    }
    fprintf(file , "\n\nNAME :%s\n" , name);
    if(level == 1){
    	lvl_ptr = "easy";
	}
	else{
		lvl_ptr = "hard";
	}
    fprintf(file , "Level : %s\n" , lvl_ptr);
    fprintf(file , "SCORE :%.2f/5\n" , score);
    

    fclose(file);
    printf("\nscores saved!!");
}


void rules(){
	printf("1. Your goal is to type the displayed sentence exactly as shown.\n2. Capitalization, spaces, and punctuation must be correct.\n3. The timer starts as soon as the sentence is displayed.\n4. Press 'Enter' after completing the sentence.\n5. Accuracy must be 99% or higher to earn a point.\n6. Word Per Second (WPS) and accuracy will be shown after each sentence.\n7. You will be given 5 sentences to type.\n8. Your final score will be out of 5.\n9. Do not use backspace while typing (if possible).\n10. Try to complete the sentence as fast and accurately as possible.\nGOOD LUCK!");
}
int levels(){
	while(1){
	
	printf("Choose between\n\033[33m1.EASY MODE\n\033[36m2.HARD MODE\033[0m\n");
	scanf("%d" , &level);
	if(level == 1|| level==2){

		return level;
}
	else{
		printf("invalid input");
		
}
}
}
	

int type_test(const char *sentence){
		char uw[300] ;
		memset(uw , 0 ,sizeof(uw));
		
		int ch;
while((ch = getchar()) != '\n' && ch != EOF);           //when enter is pressed it clears the buffer including \n
		printf("\n\nType the following sentence:\n");
		print_colored_sentence(sentence , level);
		time_t start, end;
        time(&start);       //to record the start time 
		fgets(uw, sizeof(uw), stdin);
			time(&end);       //to record the end time
			
	uw[strcspn(uw, "\n")] = '\0';       //remove newline from input
			
			double time_taken = difftime(end, start);   //to calc time taken
				int len = strlen(sentence);
			
			float cps = len/time_taken;
int correct = 0;
for (int i =0 ; i<len ; i++){
	if(sentence[i] == uw[i]){
		correct ++;
	}
}
for(int i =0; i <strlen(sentence); i++){
    if(i>=strlen(uw)||(sentence[i] != uw[i])){
        printf("^"); // mistake
    } 
	else {
        printf(" ");
    }
}
double acc = ((double)correct/len)*100;
	

		printf("\naccuracy is:%.2f %%", acc);
		printf("\ncharacter per second count is :%.2f" , cps);     //char in one second
		if(acc > 99){
			score+=1;
		}
		else if(acc>=90){
			score+=0.5;
		}
		printf("\nscore:%.2f" , score);
		return score;
}
void title_animation() {
	printf("======================================================================================================================\n");
    char title[] = "                              WELCOME TO TYPING TUTOR\n\n by 25k-0663 & 25k-0803";
    printf("\n\033[32m");
    for (int i = 0; i < strlen(title); i++) {
        printf("%c", title[i]);
        fflush(stdout);
        usleep(50000);
    }
    printf("\033[0m\n");
    printf("========================================================================================================================");
}

int main() {
	while(1){
		#ifdef _WIN32
			system("cls");    //clearing windows screen
		#else
			system("clear");            // for mac
		#endif
		
		title_animation(); 
		
	int menu;
	char name[50];
  //printf("\033[32m======================================= WELCOME TO TYPING TUTOR ======================================================\033[0m \n\n");
  printf("\n\n-MAIN MENU-\n");
  printf("1.START \n2.VIEW RULES\n");
  scanf("%d" , &menu);
  getchar();     //used to clear out previous 
  switch(menu){
  	case 1:
  		
  	printf("Enter your name: ");
  fgets(name, sizeof(name), stdin);
  score = 0;
  level = levels();
  char p;
  	if(level == 1){

  			printf("\nEasy mode selected!");
  		type_test("Humans have 206 bones");
  		type_test("Your heart pumps blood through your body");
  		type_test("Earth revolves around sun");
  		type_test("Save the File!");
  		type_test("Accuracy is more important than speed");
	  }
	  else{
	printf("\a\a");       //beep
	printf("Hard mode selected\n");
	printf("\033[31mThis level is extra challenging are you sure you want to continue?(y/n): \033[0m");
	scanf(" %c" , &p);
	if(p =='y' || p =='Y'){
	     type_test("#codelikeApro@$");
	      type_test("That will be $20,847,817.92 (*** plus 5% tax)!");
        type_test("Fact #417: 2^8 is 2^(2^2)*2^(2^2))!");
    type_test("#4 hotdogs, 50% off @ 1$ ea. for Jim & I (*** w/o ketchup)!");
            type_test("The Milky Way contains over 100400 billion stars and moves at ~220 km/s around its center.");
            
		  }
		  else{
		  	printf("Dont! Give up");
		  	level = levels();
		  }
	}
		  name[strcspn(name,"\n")]=0;
		  printf("\n\nNAME: %s  final score: %.2f/5\n" , name , score);
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
    	printf("\npress enter to return back to the menu!");
    	getchar();
  		break;	
  	case 2:
  	rules();
  	printf("\npress enter to return back to the menu!");
  	getchar();
  		
  	break;
  		
  	default:
  		printf("invalid");
  }
  }
    return 0;
}

