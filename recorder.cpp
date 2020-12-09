//=========================================================================================
// KeyBoard Recorder
// @author: Gonzales Cenelia
// homepage: www.ai-search.4t.com
//
// The purpose of these program is to simulate a human typist,the way that these
// program proceed to do this is to first record the time delays between each keyboard
// hit,those time delays are saved into and array and later,they are saved into a file.
// Once the the time delays are saved the program can use them for writing any given text.
// this code is copyrighted and has limited warranty. //****************
//=========================================================================================
#include "recorder.h"

#define WAIT(x) sleep((double)(x));
#define SPEED 2.2f
// buffer for saving the string entered by the user
std::string sBuffer = "";
unsigned int numOfLines = 0;
//===========================
// generates a random number
//===========================
int Random( const int val ) {
	if( val == 0 ) return 0;
	else { 
		return rand() % val; 
	}
}

//====================
// chronometing time
//====================
double countTime(void)
{
	LARGE_INTEGER liFreq;
    LARGE_INTEGER liStart;
    LARGE_INTEGER liStop;

	QueryPerformanceCounter(&liStart);
	QueryPerformanceFrequency(&liFreq);

	while(!kbhit())
	{
	}

	QueryPerformanceCounter(&liStop);
	return ((double)(liStop.QuadPart - liStart.QuadPart)/liFreq.QuadPart);
}

//========================================
// pause for a specific number of seconds
//========================================
void sleep( double goal ) 
{
	LARGE_INTEGER liFreq;
    LARGE_INTEGER liStart;
    LARGE_INTEGER liStop;

	QueryPerformanceCounter(&liStart);
	QueryPerformanceFrequency(&liFreq);
	
	double clock = 0.0f;
	while( clock < goal )
	{
		QueryPerformanceCounter(&liStop);
		clock = (double)(liStop.QuadPart - liStart.QuadPart)/liFreq.QuadPart;
	}
}

//========================================
// records and saves time delays to file
//========================================
void save_delay(void)
{
	FILE *ft = fopen("time records.txt", "w");
	if(!ft) perror("time records.txt");
	sBuffer.erase();
	int key = 0;
	numOfLines = 0;
	std::vector<double> delay;
	// recording time delays
	int i = 0;
	for(; (key = getche()) != 9; ++i)
	{
		if(key == 13) 
		{
			key = '\n';
			cprintf("\r\n   ");
			numOfLines++;
		}
		delay.push_back(countTime());
		sBuffer += (char)key;
	}
	// saving time delays to file
	for(int j = 1; j < i; ++j)
	{
		fprintf( ft, "%lf ", delay[j] );
		if( j > 0 && !(j % 10)) putc('\n', ft);
	}
	fflush(ft);
	fclose(ft);
}

//=============================
// reads time delays from file
//=============================
void read_time_delay(std::vector<double> &time_delay)
{
	FILE *ft = fopen("time records.txt", "r");
	if(!ft) perror("time records.txt");
	double delay = 0.0f;
	for( int i = 0; fscanf( ft, "%lf ", &delay  ) != EOF; ++i )
	{
		time_delay.push_back(delay);
	}
	fclose(ft);
}

//==============================================================
// printing the given string by using prerecorded time delays
//==============================================================
void print_string(const char *string, std::vector<double> time_delay, size_t linePos) {
	int start = 0;
	int delay_num = time_delay.size();
	int x = 0, y = linePos;
	for( int i = 0, j = start, counter = 0; string[i] != 0; ++i, ++j, ++counter ) {
		gotoxy(x, y);
		if(string[i] == 8 && x > 0) {
			--x;
		} else {
			++x;
		}
		if( j >= delay_num - 1 ) {
			int back_pos = j;
			j = Random(delay_num);
			if( delay_num > 2 ) {
				int diff = abs(j - back_pos);
				while( diff < 2 ) {
					j = Random(delay_num);
					diff = abs(j - back_pos);
				}
			}
		}
		double delay = time_delay[j]/SPEED;
		WAIT(delay);
		if((string[i] == '\n')) {
			x = 0; y++;
			gotoxy(x, y);
		}
		printf("%c", string[i]);
	}
}
