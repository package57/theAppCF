// theAppCF
// copy a text file - byte by byte
#include <iostream>
#include <fstream>
#include <ctime>

// files
// the input file stream name
std::fstream filei;
// the input file name
std::string fileiname = "theAppCpp-in.txt";
// a byte read from filei
char fileic;
// the record
char fileir[81];
// the integer count of what byte was read from filei from the tellg method
int filei_tellg;
// bytes in the input file
int fileibytecnt;
// records in the input file
int fileireccnt;

// the output file stream name
std::fstream fileo;
// the output file name
std::string fileoname = "theAppCpp-out.txt";
// bytes in the input file
int fileobytecnt;
// records in the input file
int fileoreccnt;

// variables
// counters
int i;
int j;
// logging
// start time
int start_s;
// end time
int stop_s;
// error message
std::string msg;
// abend code
int abendi;
// abend flag
bool abend;

// functions/methods (paragraphs)
// declared here - so that they can be defined 'below' (main) - like normal
// initialize - begin process
void p000100_init();
// open input file
void p000200_openfo();
// open the output file
void p000300_openfi();
// close the input file
void p000400_closefi();
// close the output file
void p000500_closefo();
// end of process
void p000600_eop();
// process the input file
void p100000_processfir();
// read the input file
void p110000_readfir();
// write the output file
void p120000_writefor();
// initialize the record
void p130000_init_fileir();
// abnormal termination - boom
void p999999_abnormal();

// the mainline
int main()
{
    start_s = clock();
// get the file names
    fileiname = "theAppCpp-in.txt";
    fileoname = "theAppCpp-out.txt";

    p000100_init();

    p000200_openfo();   // exit on error

    p000300_openfi();   // exit on error

    p110000_readfir();  // byte by byte

    while (filei_tellg > 0)  // at end of file the read returns -1
    {
        p100000_processfir();
    }

    p000400_closefi();

    p000500_closefo();

    p000600_eop();

    return 0;

}

void p000100_init()
{

    std::time_t currentdatetime = std::time(nullptr);

    std::cout << "Welcome " << std::ctime(&currentdatetime) << std::endl;

    fileic = ' ';

    p130000_init_fileir();

    filei_tellg = 0;
    fileibytecnt = 0;
    fileireccnt = 0;
    fileobytecnt = 0;
    fileoreccnt = 0;
    i = 0;
    j = 0;
    start_s = 0;
    stop_s = 0 ;
    msg = "";
    abendi = 0;
    abend = false;

}

void p000200_openfo()
{

    fileo.open(fileoname, std::ios::out | std::ios::trunc );

    if  (!fileo.is_open())
    {
        abend = true;
        msg = "file Out Open error";
        abendi = 3500;
        p999999_abnormal(); // exits program
    }
}

void p000300_openfi()
{

     filei.open(fileiname, std::ios::in );

    if  (!filei.is_open())
    {
        abend = true;
        msg = "file In Open error";
        abendi = 3500;
        p999999_abnormal();   // exits program
    }

}
void p000400_closefi()
{

    filei.close();

}

void p000500_closefo()
{

    fileo.close();

}

void p000600_eop()
{

    std::cout << "File In Bytes " << fileibytecnt << std::endl;

    std::cout << "File In Records " << fileireccnt << std::endl;

    std::cout << "File Out Bytes " << fileobytecnt << std::endl;

    std::cout << "File Out Records " << fileoreccnt << std::endl;

    stop_s = clock();

    std::cout << "elapsed time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}

void p100000_processfir()
{

    j++;

    fileir[i] = fileic;

    i++;

    if  (fileic == '\n')
    {
       fileireccnt++;
       p120000_writefor();
       p130000_init_fileir();
    }

    p110000_readfir();

}

void p110000_readfir()
{

    fileic = filei.get();   // one byte at a time

    filei_tellg = filei.tellg();

    if  (filei_tellg > 0)
    {
        fileibytecnt = filei_tellg;
    }

}

void p120000_writefor()
{

    fileo << fileir;

    fileoreccnt++;

}

void p130000_init_fileir()
{

    for (i = 0; i < j; i++)   // i < j to save time
    {
        fileir[i] = '\0';     // set to null
    }

    i = 0;
    j = 0;

}

 void p999999_abnormal()
 {

    std::cout << msg << " : " << abendi << std::endl;

    exit(abendi);

 }

