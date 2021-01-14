/*
E/17/207
MARASINGHE MAPG
CO222 PROJECT 1
e17207@eng.pdn.ac.lk
*/

//preprossesor directives.
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//declaring constant values for spaces with coloured backgrounds
#define BLACK "\e[40m " 
#define RED "\e[41m "
#define GREEN "\e[42m "
#define YELLOW "\e[43m "
#define BLUE "\e[44m "
#define MAGENTA "\e[45m "
#define CYAN "\e[46m "
#define WHITE "\e[47m "
#define NOCOLOUR "\e[0m" //turn off using a background colour

//function prototype
void up(int times);//move the cursor up
void down(int times);//move the cursor down
void left(int times);//move the cursor left
void right(int times);//move the cursor right
int len(unsigned char string[]);//a function that returns the len(url) of a string.
void frame24();//a function that prints the frame of a url of size <=20
void frame132();//a function that prints the frame of a url of size >20
void positionalSquare(char* colour);//a funtion that prints a positional identification square
void block24(char* colour);//a function that prints the frame and the positional identification squares of a url of (size<=20).
void block132(char* colour);//a function that prints the frame and the positional identification squares of a url of (size>20).
void hash(unsigned char url[]);//the function that hashes the given URL.
void encode(int ascii,char* colour);//a function that encodes a single positional square
void generate(char* colour);//a function that generates the QR code
void print24(int v1, int v2, char* colour);//the function that prints the encoded unit squares from hashed[v1] to hashed[v2] in the smaller QR code.
void print132(int v1, int v2, char* colour);//the function that prints the encoded unit squares from hashed[v1] to hashed[v2] in the bigger QR code.

//declaring a global variable
unsigned char hashed[256];

int main(int argc, char *argv[]){

	if(argc>3){//if there are more than 3 command line arguments the programme prints the following message.(usage pf the program.)
		printf("Incorrect usage of arguments.\nusage :\n%s -c [black|red|green|yellow|blue|magenta|cyan]\n%s -h for the help about the program\n",argv[0],argv[0]);
	}

	else{//checking the command line arguments and act accordingly.

		if(argc == 1){//if there are no flags, the generated QR code will be in black and white.
			generate(BLACK);			
		}
		else if((argc == 2) && !(strcmp(argv[1],"-h"))){//if the user enters -h flag,the program prints the usage of the program.
			printf("usage :\n%s -c [black|red|green|yellow|blue|magenta|cyan]\n%s -h for the help about the program\n",argv[0],argv[0]);
		}
		else if((argc == 3) && !(strcmp(argv[1],"-c"))){
			/*if the -c flag is given, the program generates the QR code in the required colour.
			(as given in the next command line argument). */	

			//transform the colour argument into lowercase letters because the colour arguments are not case sensitive.
			char lower[strlen(argv[2])];
			for(int i = 0;argv[2][i] != '\0';i++){
        		lower[i] = tolower(argv[2][i]);
    		}

			//generate the QR code according to the colour argument.		
			if(!(strcmp(lower,"black"))) generate(BLACK);
			else if(!(strcmp(lower,"red"))) generate(RED);
			else if(!(strcmp(lower,"green"))) generate(GREEN);
			else if(!(strcmp(lower,"yellow"))) generate(YELLOW);
			else if(!(strcmp(lower,"blue"))) generate(BLUE);
			else if(!(strcmp(lower,"magenta"))) generate(MAGENTA);
			else if(!(strcmp(lower,"cyan"))) generate(CYAN);			
			else{//print an error message and the usage if an invalid colour argument is given.
				printf("Invalid argument for color.\nusage :\n%s -c [black|red|green|yellow|blue|magenta|cyan]\n%s -h for the help about the program\n",argv[0],argv[0]);
				return 0;
			}
		}
		else{//print an error message and the usage if an invalid flag is given.
			printf("Incorrect usage of arguments.\nusage :\n%s -c [black|red|green|yellow|blue|magenta|cyan]\n%s -h for the help about the program\n",argv[0],argv[0]);
		}
	}
return 0;
}

//function description 
void up(int times){//move the up a specified number of times 
	for(int i=0;i<times;i++){
		printf("\e[1A");
	}
}

void down(int times){//move the down a specified number of times 
	for(int i=0;i<times;i++){
		printf("\e[1B");
	}
}

void left(int times){//move the left a specified number of times 
	for(int i=0;i<times;i++){
		printf("\e[1D");
	}
}

void right(int times){//move the right a specified number of times 
	for(int i=0;i<times;i++){
		printf("\e[1C");
	}
}

void frame24(){//print the outer frame of the QR code of a url which has less than or equal to 20 characters.
	int i;

	for(i=0;i<40;i++){
		printf(WHITE);//print spaces white background colour	
	}
	down(1);//move the cursor to the required position.
	left(2);

	for(i=1;i<20;i++){//print the right vertical side of the frame.
		printf(WHITE);
		printf(WHITE);	
		down(1);
		left(2);
	}
	up(1);
	right(1);

	for(i=0;i<40;i++){//print the bottom horizontal side of the frame.
		printf(WHITE);
		left(2);
	}

	for(i=0;i<20;i++){//print the left vertical side of the frame.
		printf(WHITE);
		printf(WHITE);
		up(1);
		left(2);		
	}
}

void positionalSquare(char* colour){//a function that prints one positional square with a given colour.
		int i;
		for(i=0;i<12;i++){
		printf("%s",colour);//print spaces with the specified backgrounf colour.	
	}
	down(1);//move the cursor down
	left(2);

	for(i=0;i<5;i++){//print the rightmost verticle side of the positional square
		printf("%s",colour);
		printf("%s",colour);
		down(1);
		left(2);
	}
	up(1);//moving the cursor up
	right(1);

	for(i=0;i<11;i++){//print the bottom horizintal side of the positional square
		printf("%s",colour);
		left(2);
	}
	
	for(i=0;i<5;i++){//print the leftmost vertical side of the positional square
		printf("%s",colour);
		printf("%s",colour);
		left(2);
		up(1);
	}
	right(2);
	down(1);

	//ptint out the middle square of the positional square.
	for(i=0;i<8;i++){//print the top side of the middle square
		printf(WHITE);
	}
	left(2);
	down(1);
	
	for(i=0;i<3;i++){//print the right side of the middle square
		printf(WHITE);
		printf(WHITE);
		down(1);
		left(2);
	}
	up(1);
	for(i=0;i<7;i++){//print the bottom side of the middle square
		printf(WHITE);
		left(2);
	}
	right(1);
	up(1);

	for(i=0;i<3;i++){//print the left side of the middle square
		printf(WHITE);
		printf(WHITE);
		left(2);
		up(1);
	}
	down(2);
	right(2);

	//print the inner square with the given coulur.
	for(i=0;i<4;i++){
		printf("%s",colour);
	}

	down(1);
	left(2);
	printf("%s",colour);
	printf("%s",colour);
	left(4);
	printf("%s",colour);
	printf("%s",colour);
	up(1);
	left(2);
	printf("%s",colour);
	printf("%s",colour);
}


void block24(char* colour){/*the function that prints the block(frame+ 3 positional squares) of a 
url which is no longer than 20 characters with the specifies colour for the positional squares*/

	//printing the outline
	frame24();

	//moving the cursor to the required position
	right(2);
	down(1);

	//printing a positional identification square
	positionalSquare(colour);

	//moving the cursor to the required position
	up(2);
	right(18);

	//printing a positional identification square
	positionalSquare(colour);

	//moving the cursor to the required position
	left(30);
	down(10);

	//printing a positional identification square
	positionalSquare(colour);

	//moving the cursor to the next position
	up(8);
	right(6);
}



void encode(int ascii,char* colour){//the function that encodes the given URL
	int binary[9];//finding the 9-digit binary value of the ascii value of the character
	for(int i=8;i>=0;i--){
		binary[i] = ascii%2;
		ascii = ascii/2;
	}

	for(int i=0;i<3;i++){//encoding the character squares.if the bit is 0,the square is printed white.otherwise it is printed in the given color.
		if(binary[i] == 0){
			printf(WHITE);
			printf(WHITE);
		}
		else{
			printf("%s",colour);
			printf("%s",colour);
		}
	}

		down(1);//move the cursor to the beginning of the next row.
		left(6);

	for(int i=3;i<6;i++){//encoding the 2nd row of the character square
		if(binary[i] == 0){
			printf(WHITE);
			printf(WHITE);
		}
		else{
			printf("%s",colour);
			printf("%s",colour);
		}
	}

		down(1);//moving the cusor to the beginning of the next row. 
		left(6);

	for(int i=6;i<9;i++){//encoding the 3rd row of the character square
		if(binary[i] == 0){
			printf(WHITE);
			printf(WHITE);
		}
		else{
			printf("%s",colour);
			printf("%s",colour);
		}
	}
	up(2);
}

int len(unsigned char string[]){//a function to find the len(url) of an unsigned character array.
    int count=0;
    while(string[count] != '\0'){
        count++;
    }
    return count;
}

void frame132(){//the function which prints the frame of the QR code whose URL len(url) is more then 20 and less than 120.
		int i;

	for(i=0;i<76;i++){//print the top side of the frame
		printf(WHITE);		
	}

	down(1);
	left(2);

	for(i=1;i<38;i++){//print the right side of the frame
		printf(WHITE);
		printf(WHITE);
		;
		down(1);
		left(2);
	}
	up(1);
	right(1);

	for(i=0;i<76;i++){//print the bottom side of the frame
		printf(WHITE);
		left(2);
	}

	for(i=0;i<38;i++){//print the left side of the frame
		printf(WHITE);
		printf(WHITE);
		up(1);//cursor up
		left(2);		
	}
}

void block132(char *colour){//the function which prints the block of the bigger QR code(frame+3 positional squares)
	//printing the outline
	frame132();

	//moving the cursor to the requiGREEN position
	right(2);
	down(1);

	//printing a positional identification square
	positionalSquare(colour);

	//moving the cursor to the requiGREEN position
	up(2);
	right(54);

	//printing a positional identification square
	positionalSquare(colour);

	//moving the cursor to the requiGREEN position
	left(66);
	down(28);

	//printing a positional identification square
	positionalSquare(colour);

	//moving the cursor to the next position
	up(26);
	right(6);
}

void generate(char* colour){//a function which generates QR codes(smaller or bigger)
			unsigned char url[256];
			
			//prompt the user to input the url
			printf("Enter the URL: ");
			scanf("%s",url);

			//len(url) = len(url);//find the len(url) of the unsigned char array url.

			if (len(url) <= 3){//if the len(url) of the url is less than or equal to 3 characters display and error message.
				
				printf("String is too short. Not supported by available QR versions\n");
			}

			else if (len(url) >= 120){//if the len(url) of the url is greater than or equal to 120 characters display and error message.
				
				printf("String is too long. Not supported by available QR versions\n");
			}

			else{//if the url has a proper length.

				printf("\e[;H\e[2J");//move the cursor to the upper left corner.

				//hash the string
				if (len(url)<=20){//considering the instance where the len(url) of the url is <= 20.
					hash(url);//hash the url

					//printing the block
					block24(colour);
					
					//encoding and printing the QR code		
					for(int i=0;i<=12;i+=4){
						print24(i,(i+4),colour);
					}
					up(18);
					print24(16,18,colour);
					right(12);
					print24(18,20,colour);
					print24(20,22,colour);
					right(2);
					print24(22,24,colour);
					down(8);
				}

				else if (len(url)>20){//generating the bigger QR code(of a URL which has more than 20 and less than 120 characters)
					hash(url);//hash the string.

					//printing the block
					block132(colour);

					//encoding and printing the QR code			
					for(int i=0;i<=90;i+=10){
						print132(i,(i+10),colour);
					}
					up(36);
					print132(100,108,colour);
					right(12);
					print132(108,116,colour);
				
					for(int i=116;i<=128;i+=2){
						print132(i,(i+2),colour);
						right(2);
					}

					print132(130,132,colour);
					down(8);
				}
				printf(NOCOLOUR); //stop using a background colour
			}	
}

void hash(unsigned char url[]){//the function that hashes the given URL
	if(len(url)<=20){//the case where the URL has less than or equal to 20 characters.
		hashed[0] = len(url)+50;//ASCII value of the 1st element of the hashed string = length of the URL + 8.
		for(int i=0;i<len(url);i++){//if the length of the URL is L the next L characters of the hashed string will be the characters of the URL.
			hashed[i+1] = url[i];
		}
	/*for the next elements in the hashed string until the required length is obtained,
	add 1 to the ASCII value of the corresponding element of the input string(URL).For each round, add 1 to the ASCII value of the
	corresponding element of the last round*/

		for(int j=0;j<(23-len(url));j++){//determine the error detection part of the hashed string and reverse it.
			hashed[23-j] = url[j%len(url)]+((j/len(url))+1);
		}
	}
	else{//the case where the URL length is more than 20 and less than 120 characters.
		hashed[0] = len(url)+50;
		for(int i=0;i<len(url);i++){
			hashed[i+1] = url[i];
		}
		for(int j=0;j<(131-len(url));j++){
			hashed[131-j] = url[j%len(url)]+((j/len(url))+1);
		}
	}
}

void print24(int v1, int v2,char* colour){
	/*This function prints out encoded unit squares for the smaller QR code horizontally from hashed[v1] to hashed[v2] with
	the specified colour.*/
	for(int i=v1;i<v2;i++){
		encode(hashed[i],colour);
	}
	down(3);
	left(24);	
}

void print132(int v1, int v2,char* colour){
	/*This function prints out encoded unit squares for the bigger QR code horizontally from hashed[v1] to hashed[v2] with
	the specified colour.*/
	for(int i=v1;i<v2;i++){
		encode(hashed[i],colour);
	}
	down(3);
	left(60);
}