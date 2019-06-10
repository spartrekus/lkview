
///////////
// LKVIEW  
///////////

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
#include <stdio.h>
#define PATH_MAX 2500
#if defined(__linux__) //linux
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__) 
#define MYOS 4  // freebsd
#define PATH_MAX 2500
#else
#define MYOS 0
#endif
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <time.h>









#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>  


int show_comment = 1;


int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}






#define ESC "\033"
#define home() 			printf(ESC "[H") //Move cursor to the indicated row, column (origin at 1,1)
#define clrscr()		printf(ESC "[2J") //clear the screen, move to (1,1)
#define gotoxy(x,y)		printf(ESC "[%d;%dH", y, x);

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int rows, cols;
int clip_slot_line = 0;


char user_line_linestr[PATH_MAX];
int  user_line_sel = 2;
char fichier[PATH_MAX];

int  user_block_start = 0;
int  user_block_end = 0;

int clip_line_sel = 0;

int mode_refresh = 0;
int linesel = 0;
int colmax = 0;
int rowmax = 0;
int mode_show_linenb = 0;
int mode_show_wrap = 0;
int viewer_scrolly = 1;

void nsystem( char *mycmd )
{
   printf( "<SYSTEM>\n" );
   printf( " >> CMD:%s\n", mycmd );
   system( mycmd );
   printf( "</SYSTEM>\n");
}

void nrunwith( char *cmdapp , char *filesource)
{
           char cmdi[PATH_MAX];
           strncpy( cmdi , "  " , PATH_MAX );
           strncat( cmdi , cmdapp , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi ,  filesource , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , "\" " , PATH_MAX - strlen( cmdi ) -1 );
           nsystem( cmdi ); 
}


void nruncmd( char *filesource , char *cmdapp )
{
           char cmdi[PATH_MAX];
           strncpy( cmdi , "  " , PATH_MAX );
           strncat( cmdi , cmdapp , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi ,  filesource , PATH_MAX - strlen( cmdi ) -1 );
           strncat( cmdi , "\" " , PATH_MAX - strlen( cmdi ) -1 );
           nsystem( cmdi ); 
}





//////////////////////////
char *strcut( char *str , int myposstart, int myposend )
{  
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( ( str[i] != '\0' ) && ( str[i] != '\0') )
         if ( ( i >=  myposstart-1 ) && (  i <= myposend-1 ) )
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
char *strsplit(char *str , int mychar , int myitemfoo )
{  
      char ptr[strlen(str)+1];
      int myitem = myitemfoo +1;
      int i,j=0;
      int fooitem = 0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == mychar ) 
           fooitem++;
        else if ( str[i] != mychar &&  fooitem == myitem-2  ) 
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}

/// customed one
char *strdelimit(char *str , int mychar1, int mychar2,  int mycol )
{ 
      char ptr[strlen(str)+1];
      char ptq[strlen(str)+1];
      strncpy( ptr, strsplit( str, mychar1 , mycol+1 ), strlen(str)+1 );
      strncpy( ptq, strsplit( ptr, mychar2 , 1 ), strlen(str)+1 );
      size_t siz = sizeof ptq ; 
      char *r = malloc( sizeof ptq );
      return r ? memcpy(r, ptq, siz ) : NULL;
}
 //fputs( strdelimit( fetchline,  '{' ,'}' ,  1 ) , fp5 );












///////////////
char* scan_line( char* buffer, int buffer_size) 
{
   char* p = buffer;
   int count = 0;
   do {
       char c;
       scanf("%c", &c); // scan a single character
       // break on end of line, string terminating NUL, or end of file

       if (c == '\r' || c == '\n' || c == 0 || c == EOF) 
       {
           *p = 0;
           break;
       }

       *p++ = c; // add the valid character into the buffer
   } while (count < buffer_size - 1);  // don't overrun the buffer
   // ensure the string is null terminated
   buffer[buffer_size - 1] = 0;
   return buffer;
}



static struct termios oldt;

void restore_terminal_settings(void)
{
    tcsetattr(0, TCSANOW, &oldt);  /* Apply saved settings */
}

void enable_waiting_for_enter(void)
{
    tcsetattr(0, TCSANOW, &oldt);  /* Apply saved settings */
}

void disable_waiting_for_enter(void)
{
    struct termios newt;

    /* Make terminal read 1 char at a time */
    tcgetattr(0, &oldt);  /* Save terminal settings */
    newt = oldt;  /* Init new settings */
    newt.c_lflag &= ~(ICANON | ECHO);  /* Change settings */
    tcsetattr(0, TCSANOW, &newt);  /* Apply settings */
    atexit(restore_terminal_settings); /* Make sure settings will be restored when program ends  */
}












int file_linemax = 0;
///////////////////////////////////////////
void readfile( char *filesource )
{
   FILE *source; 
   int ch ; 
   file_linemax = 0;
   source = fopen( filesource , "r");
   while( ( ch = fgetc(source) ) != EOF )
   {
         if ( ch == '\n' )
           file_linemax++;
   }
   fclose(source);
}






///////////////////////////////////////////
///////////////////////////////////////////
void appendfileline( char *outputfile, char *filesource )
{
   int readsearchi;
   FILE *source; 
   int ch ; 
   char lline[PATH_MAX];
   int pcc = 0;
   int linecount = 0;
   int artcount = 0;
   int posy = 0;
   clrscr();
   home();
   gotoxy( 0, viewer_scrolly );

   FILE *fptt;
   //fptt = fopen( outputfile , "wb+" );
   //fclose( fptt );

   source = fopen( filesource , "r");
   int fileeof = 0;
   while(  fileeof == 0 )
   {
       ch = fgetc(source); 
       if ( ch == EOF ) fileeof = 1;
       else
       {
         if ( ch != '\n' )
            lline[pcc++]=ch;

         else if ( ch == '\n' ) 
         {
             linecount++;
             lline[pcc++]='\0';

             //if ( linecount >= linesel )
             //if ( posy <= rowmax -1 - viewer_scrolly )
             {

                if ( linecount  == user_line_sel )
                {
                   //printf("%s", KGRN);
                   //printf(">");
                }
                else if ( ( linecount  >= user_block_start )
                      &&  ( linecount  <= user_block_end ))
                {
                   //printf("%s", KCYN);
                }
                else
                {
                   //printf("%s", KYEL);
                   //printf(" ");
                }

               // if ( mode_show_linenb == 1 ) 
               //    printf( "%d: %s\n" , linecount, lline );   
               // else
               //    printf( "%s\n" , lline );   

                if ( ( linecount  >= user_block_start ) &&  ( linecount  <= user_block_end ))
                {
                   fptt = fopen( outputfile  , "ab+" );
                    fputs( lline, fptt );
                    fputs( "\n", fptt );
                   fclose( fptt );
                }

                posy++;
             }

             lline[0]='\0';
             pcc = 0;
         }
       }
   }
   fclose(source);
}



///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////
void copyfileline( char *outputfile, char *filesource )
{
   int readsearchi;
   FILE *source; 
   int ch ; 
   char lline[PATH_MAX];
   int pcc = 0;
   int linecount = 0;
   int artcount = 0;
   int posy = 0;
   clrscr();
   home();
   gotoxy( 0, viewer_scrolly );

   FILE *fptt;
   fptt = fopen( outputfile , "wb+" );
   fclose( fptt );

   source = fopen( filesource , "r");
   int fileeof = 0;
   while(  fileeof == 0 )
   {
       ch = fgetc(source); 
       if ( ch == EOF ) fileeof = 1;
       else
       {
         if ( ch != '\n' )
            lline[pcc++]=ch;

         else if ( ch == '\n' ) 
         {
             linecount++;
             lline[pcc++]='\0';

             //if ( linecount >= linesel )
             //if ( posy <= rowmax -1 - viewer_scrolly )
             {

                if ( linecount  == user_line_sel )
                {
                   //printf("%s", KGRN);
                   //printf(">");
                }
                else if ( ( linecount  >= user_block_start )
                      &&  ( linecount  <= user_block_end ))
                {
                   //printf("%s", KCYN);
                }
                else
                {
                   //printf("%s", KYEL);
                   //printf(" ");
                }

               // if ( mode_show_linenb == 1 ) 
               //    printf( "%d: %s\n" , linecount, lline );   
               // else
               //    printf( "%s\n" , lline );   

                if ( ( linecount  >= user_block_start ) &&  ( linecount  <= user_block_end ))
                {
                   fptt = fopen( outputfile  , "ab+" );
                    fputs( lline, fptt );
                    fputs( "\n", fptt );
                   fclose( fptt );
                }

                posy++;
             }

             lline[0]='\0';
             pcc = 0;
         }
       }
   }
   fclose(source);
}







///////////////////////////////////////////
void readfileline( char *filesource )
{
   int area_comment_on = 0;

   int readsearchi;
   FILE *source; 
   int ch ; 
   char lline[PATH_MAX];
   int pcc = 0;
   int linecount = 0;
   int artcount = 0;
   int posy = 0;
   int fskip = 0;
   clrscr();
   home();
   gotoxy( 0, viewer_scrolly );
   source = fopen( filesource , "r");
   int fileeof = 0;  int foox ; 
   while(  fileeof == 0 )
   {
       ch = fgetc(source); 
       if ( ch == EOF ) fileeof = 1;
       else
       {
         if ( ch != '\n' )
            lline[pcc++]=ch;

         else if ( ch == '\n' ) 
         {
             fskip = 0;
             printf("%s", KYEL);
             linecount++;
             lline[pcc++]='\0';

             if ( ( lline[0]=='/') && (lline[1]=='/') )  
             {
                if ( show_comment == 0 ) 
                    fskip = 1; 
             }

             if ( linecount >= linesel )
             if ( fskip == 0 )
             if ( posy <= rowmax -1 - viewer_scrolly )
             {
                if ( ( lline[0]=='/') && (lline[1]=='/') &&  ( show_comment == 2 ) )
                   area_comment_on = 1; 
                else
                   area_comment_on = 0; 

                if ( linecount  == user_line_sel )
                {
                   strncpy( user_line_linestr, lline , PATH_MAX );
                   printf("%s", KGRN);
                   printf(">");
                }
                else if ( ( linecount  >= user_block_start )
                      &&  ( linecount  <= user_block_end ))
                {
                   printf("%s", KCYN);
                }
                else if ( area_comment_on == 1 ) 
                {
                   printf("%s", KWHT);
                }
                else
                {
                   printf("%s", KYEL);
                   printf(" ");
                }

                if ( mode_show_wrap == 1 ) 
                {
                   if  ( mode_show_linenb == 1 ) printf( "%d: " , linecount );
                   for( foox = 0 ;  foox <= strlen( lline ) ; foox++)
                     if ( foox <= cols-2 ) 
                        printf( "%c" , lline[ foox ] );   

                   printf( "\n" );
                }
                else if ( ( mode_show_linenb == 1 ) && ( mode_show_wrap == 0 ) )
                   printf( "%d: %s\n" , linecount, lline );   
                else
                   printf( "%s\n" , lline );   

                posy++;
             }

             lline[0]='\0';
             pcc = 0;
         }
       }
   }
   fclose(source);
}










void clear_screen()
{
    int fooi;
    struct winsize w; // need ioctl and unistd 
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );
    for ( fooi = 1 ; fooi <= w.ws_row ; fooi++ ) 
       printf( "\n" );
    home();
}

void size_screen()
{
    struct winsize w; // need ioctl and unistd 
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );
    printf( "Size %d x %d \n" , w.ws_col , w.ws_row );
}














void open_file( )
{
    char ptr[PATH_MAX]; 
    char strmsg[PATH_MAX]; 
    int j, chr, ch ;  ch = 0; int fooi;
    int menu_usersel = 0; int gamev = 0;

    char strmenu[PATH_MAX];
    strncpy( strmenu , "" , PATH_MAX );
    DIR *dirp; 
    struct dirent *dp;
    int foocounter = 1;

          strncpy( strmsg , fichier, PATH_MAX );
          strncpy( strmenu, "" , PATH_MAX );
          fooi = 0;   
          while( gamev == 0 ) 
          {
            clrscr();
            home();
            printf( "LS:\n");

   //         nls( menu_usersel );
   foocounter = 1;
   dirp = opendir( "." );
   while  (( dp = readdir( dirp )) != NULL ) 
   {
         if (  strcmp( dp->d_name, "." ) != 0 )
         if (  strcmp( dp->d_name, ".." ) != 0 )
         {
           if ( foocounter == menu_usersel )  
           {
             printf( ">%s\n", dp->d_name );
             strncpy( strmenu , dp->d_name , PATH_MAX );
           }
           else
           {
             printf( " %s\n", dp->d_name );
           }
           foocounter++;
          }
         }
         closedir( dirp );

	    if ( fooi   ==  1 ) strncpy( strmsg, strmenu, PATH_MAX ); 
            fooi = 0;  
            printf( "\n");
            printf( "(Current File: %s)\n", fichier );
            printf( "File: " );
            printf( "|%s|", strmsg );
            ch = getchar(); 
            if       ( ch == 27 )  gamev = 1;
            else if  ( ch == 15 )  gamev = 1;
            else if  ( ch == 21 ) { menu_usersel--; fooi = 1; } 
            else if  ( ch == 4  ) { menu_usersel++; fooi = 1; } 

            else if  ( ch == 10 ) { gamev = 1; 
                if ( fexist( strmsg ) == 1 ) 
                  strncpy( fichier, strmsg, PATH_MAX ); }

	    else if ( ( ch == 8 )  || ( ch == 127 ) )  
            {
               if ( strlen( strmsg ) >= 1 ) 
               {
                 j = 0; strncpy(  ptr , "" ,  PATH_MAX );
                 for ( chr = 0 ;  chr <= strlen( strmsg )-2 ; chr++) 
                 {
                    ptr[j++] = strmsg[chr];
                 }
	         strncpy( strmsg, ptr ,  PATH_MAX );
               }
            }
	    else if (
			(( ch >= 'a' ) && ( ch <= 'z' ) ) 
		        || (( ch >= 'A' ) && ( ch <= 'Z' ) ) 
		        || (( ch >= '1' ) && ( ch <= '9' ) ) 
		        || (( ch == '0' ) ) 
		        || (( ch == '~' ) ) 
		        || (( ch == '!' ) ) 
		        || (( ch == '&' ) ) 
		        || (( ch == '=' ) ) 
		        || (( ch == ':' ) ) 
		        || (( ch == ';' ) ) 
		        || (( ch == '<' ) ) 
		        || (( ch == '>' ) ) 
		        || (( ch == ' ' ) ) 
		        || (( ch == '|' ) ) 
		        || (( ch == '#' ) ) 
		        || (( ch == '?' ) ) 
		        || (( ch == '+' ) ) 
		        || (( ch == '/' ) ) 
		        || (( ch == '\\' ) ) 
		        || (( ch == '.' ) ) 
		        || (( ch == '$' ) ) 
		        || (( ch == '%' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == ',' ) ) 
		        || (( ch == '{' ) ) 
		        || (( ch == '}' ) ) 
		        || (( ch == '(' ) ) 
		        || (( ch == ')' ) ) 
		        || (( ch == ']' ) ) 
		        || (( ch == '[' ) ) 
		        || (( ch == '*' ) ) 
		        || (( ch == '"' ) ) 
		        || (( ch == '@' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == '_' ) ) 
		        || (( ch == '^' ) ) 
		        || (( ch == '\'' ) ) 
	             ) 
		    {
                        snprintf( ptr, PATH_MAX , "%s%c",  strmsg, ch );
		        strncpy(  strmsg,  ptr ,  PATH_MAX );
		  }
            
          }
}
// end of strmenu






int main( int argc, char *argv[])
{

    if ( argc == 2)
    if ( strcmp( argv[1] , "time" ) ==  0 ) 
    {
       printf("%d\n", (int)time(NULL));
       return 0;
    }
     
    char cwd[PATH_MAX]; 
    char fichier_clipboard[PATH_MAX];
    strncpy( fichier_clipboard , getenv( "HOME" ) , PATH_MAX );
    strncat( fichier_clipboard , "/" , PATH_MAX - strlen( fichier_clipboard ) -1 );
    strncat( fichier_clipboard , ".clipboard" , PATH_MAX - strlen( fichier_clipboard ) -1 );



    if ( argc == 2)
    if ( strcmp( argv[1] , "-y" ) ==  0 ) 
    {
       printf("%syellow\n", KYEL);
       return 0;
    }

    char string[PATH_MAX];
    char pathbefore[PATH_MAX];
    strncpy( user_line_linestr, "" , PATH_MAX );
    strncpy( pathbefore , getcwd( string, PATH_MAX ) , PATH_MAX );

    int key = 0;  
    int fooi;

    struct winsize w; // need ioctl and unistd 
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );
    printf("Env HOME:  %s\n", getenv( "HOME" ));
    printf("Env PATH:  %s\n", getcwd( string, PATH_MAX ) );
    printf("Env TERM ROW:  %d\n", w.ws_row );
    printf("Env TERM COL:  %d\n", w.ws_col );

    cols = w.ws_col-1;
    rows = w.ws_row-1;


    ///////////////
    if ( argc == 1)
    {
       printf("Usage: please enter a file to use with tless." );
       printf("\n" );
       return 0;
    }


    ///////////////
    if ( argc == 2)
     strncpy( fichier, argv[ 1 ] , PATH_MAX );

    readfile( fichier );

    int ch;
    int gameover = 0;
    disable_waiting_for_enter();
    /* Key reading loop */
    while( gameover == 0  ) 
    {
        if ( linesel <= 0 ) linesel = 0;
        ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );
        rowmax = w.ws_row;
        colmax = w.ws_col;

        if ( user_line_sel <= 0 )  user_line_sel = 0;
        if ( user_line_sel <= linesel ) user_line_sel = linesel; 

        ///  main
        readfileline( fichier );

        gotoxy( 0, rowmax-2);
        printf("|L%s|", user_line_linestr ); 

        gotoxy( 0, rowmax-1);
        printf("|L%d/%d|[%d] ==>", linesel , file_linemax , user_line_sel );

        if ( mode_show_wrap == 1 )  printf( "|NoWarp| " ); 
        if ( show_comment != 1   )  printf( "|Com:%d| ", show_comment ); 
        printf(" Press Key:");

        ch = getchar();

        printf( "%c\n", ch );
        if ( ch == 'q' )          gameover = 1;
        else if ( ch == 'Q' )     gameover = 1;

        else if (ch == '"') 
           clip_slot_line = linesel ; 

        else if (ch == '\'') 
           linesel = clip_slot_line ; 


        else if ( ch == 18 ) 
        {
            gotoxy( 0, rowmax-1);
            printf("|^R| Press Key:");
            ch = getchar();
            if (ch == 'p') 
            {
                enable_waiting_for_enter();
                strncpy( string, "" , PATH_MAX );
                strncpy( string, user_line_linestr , PATH_MAX );
                printf("got: \"%s\"\n", strdelimit( string, '{', '}', 1 ) );
                nrunwith( " export DISPLAY=:0 ;   mupdf   ~/pool/figs/",  strdelimit( string, '{', '}', 1 ) );
                disable_waiting_for_enter();
            }
            else if (ch == 'f') 
            {
                enable_waiting_for_enter();
                strncpy( string, "" , PATH_MAX );
                strncpy( string, user_line_linestr , PATH_MAX );
                printf("got: \"%s\"\n", strdelimit( string, '{', '}', 1 ) );
                nrunwith( " export DISPLAY=:0 ;   feh   ~/pool/figs/",  strdelimit( string, '{', '}', 1 ) );
                disable_waiting_for_enter();
                //getchar();
            }
        }



        else if ( ch == 'g' ) 
        {
            gotoxy( 0, rowmax-1);
            printf("|g| Press Key:");
            ch = getchar();
            if          ( ch == '1' )  { linesel = user_block_start; }
            else if     ( ch == '2' )  { linesel = user_block_end;   }
            else if ( ch == 'g' )  { linesel = 0; user_line_sel = 1 ; }
        }

        else if ( ch == 'v' )  {  nrunwith( " vim " , fichier ); }

        else if ( ch == 'G' )     linesel = file_linemax - w.ws_row;
        else if ( ch == 'j' )    { linesel++; user_line_sel++; }
        else if ( ch == 'k' )    { linesel--; user_line_sel--; }






       else if ( ch == 'R' )
       {
          if ( mode_refresh == 0 ) mode_refresh = 1 ; else mode_refresh = 0 ; 
       }

        else if ( ch == 't' )     printf("%syellow\n", KYEL);
        else if ( ch == 'T' )     printf("%syellow\n", KYEL);

        else if ( ch == 32  )      linesel+= rowmax * 76 / 100;
        else if ( ch == 21  )      linesel-= rowmax * 76 / 100; //ctrlu

        else if ( ch == 'u' )    { linesel-= rowmax * 76 / 100; user_line_sel-= rowmax * 76 / 100; }
        else if ( ch == 'd' )    { linesel+=10; user_line_sel+=10;} //ctrld
        else if ( ch == 'n' )    { linesel+=10; user_line_sel+=10;} //ctrld
        else if ( ch == 4 )      { linesel+=50; user_line_sel+=50;} //ctrld

        else if ( ch == 's' )     viewer_scrolly++;
        else if ( ch == 'S' )     viewer_scrolly--;
        else if ( ch == 'e' ) user_line_sel++;
        else if ( ch == 'E' ) user_line_sel--;

        else if ( ch == '(' ) user_line_sel--;
        else if ( ch == ')' ) user_line_sel++;
        else if ( ch == '-' ) user_line_sel--;
        else if ( ch == '+' ) user_line_sel++;

        else if ( ch == '[' )  cols--;
        else if ( ch == ']' )  cols++;


        else if ( ch == '6' )  cols = 60;
        else if ( ch == '7' )  cols = 70;
        else if ( ch == '8' )  cols = 80;
        else if ( ch == '9' )  cols = 90;

        //else if ( ch == 'a' )   readfileline( fichier );

        else if ( ch == 'l' )
        {  
           if (  mode_show_linenb == 0 ) 
             mode_show_linenb = 1;
           else
             mode_show_linenb = 0;
        }

        else if ( ch == 'c' )
        {  
           if      (  show_comment == 0 ) show_comment = 1;
           else if (  show_comment == 1 ) show_comment = 2;
           else if (  show_comment == 2 ) show_comment = 0;
           else   show_comment = 0;
        }


        else if ( ch == 'w' )
        {  
           if (  mode_show_wrap == 0 ) 
             mode_show_wrap = 1;
           else
             mode_show_wrap = 0;
        }


        else if (ch == 'K') 
        {
            enable_waiting_for_enter();
            strncpy( string, "" , PATH_MAX );
            strncpy( string, user_line_linestr , PATH_MAX );
            printf("got: \"%s\"\n", strdelimit( string, '{', '}', 1 ) );
            nrunwith( "  export DISPLAY=:0 ; feh ~/pool/figs/",  strdelimit( string, '{', '}', 1 ) );
            disable_waiting_for_enter();
            getchar();
        }


        else if (ch == '#') 
        {
            enable_waiting_for_enter();
            strncpy( string, "" , PATH_MAX );
            scan_line( string , PATH_MAX);
            printf("got: \"%s\"\n", string );
            linesel = atoi( string );
            disable_waiting_for_enter();
        }


        else if (ch == '$') 
        {
            enable_waiting_for_enter();
            strncpy( string, "" , PATH_MAX );
            printf("Enter a sys application: ");
            scan_line( string , PATH_MAX);
            printf("got: \"%s\"\n", string );
            nsystem( string );
            disable_waiting_for_enter();
        }

        else if ( ch == '1' )
              user_block_start = user_line_sel;
        else if ( ch == '2' )
              user_block_end = user_line_sel;

        else if ((  ch == '?' ) || ( ch == 'i' ))
        {
            clrscr();
            ch = 1;  home();
            printf( "===========\n" );
            printf( "HELP LKVIEW\n" );
            printf( "===========\n" );
            printf( "?: Help" );
            printf( "\n" );
            printf( "1: Start selection" );
            printf( "\n" );
            printf( "2: End selection" );
            printf( "\n" );
            printf( "5: Copy selection to ~/.clipboard" );
            printf( "\n" );
            printf( "w: Mode Wrap" );
            printf( "\n" );
            printf( "l: Mode Line" ); printf( "\n" );
            printf( "file: |%s|", fichier  ); printf( "\n" );
            printf( "path: |%s|", getcwd( cwd, PATH_MAX) ); printf( "\n" );
            printf( "<Press Key>" );
            getchar();
            ch = 0;
        }


        else if  (ch == 'a') 
        {
           // copy a line to clipboard
           chdir( pathbefore );
           chdir( getenv( "HOME" ) );
           FILE *fptt; 
           fptt = fopen( ".clipboard", "ab+" );
            fputs( user_line_linestr , fptt );
            fputs( "\n" , fptt );
           fclose( fptt );
           printf( "Copying to clipboard: %s\n", user_line_linestr );
           chdir( pathbefore );
        }

        else if  (ch == 'y') 
        {
           // copy a line to clipboard
           chdir( pathbefore );
           chdir( getenv( "HOME" ) );
           FILE *fptt; 
           fptt = fopen( ".clipboard", "wb+" );
            fputs( user_line_linestr , fptt );
            fputs( "\n" , fptt );
           fclose( fptt );
           printf( "Copying to clipboard: %s\n", user_line_linestr );
           chdir( pathbefore );
        }

        else if  ( (ch == 'Y')  || ( ch == 'o' )  )
        {
           // copy a line to clipboard
           chdir( pathbefore );
           chdir( getenv( "HOME" ) );
           FILE *fptt; 
            fptt = fopen( ".wclipboard", "wb+" );
            fputs( user_line_linestr , fptt );
            fputs( "\n" , fptt );
            fclose( fptt );
           nsystem( " cp .wclipboard ~/workspace/.clipboard " );
           chdir( pathbefore );
           printf( "Copying to clipboard: %s\n", user_line_linestr );
        }

        else if ( ch == '5' )
           copyfileline( fichier_clipboard , fichier );

       // else if ( ch == 'Y' )
       //    appendfileline( fichier_clipboard , fichier );

        else if ( ch == '\'' )
        {
             linesel = clip_slot_line ;
        }

        else  if (ch == '\'') 
             clip_line_sel = linesel ; 

        else if ( ch == 'm') 
        {
           gotoxy( colmax-4, rowmax-1 );
           printf( "|m|" );
           ch = getchar();
           enable_waiting_for_enter();

          if (ch == '"') 
             clip_slot_line = linesel ; 

          else if (ch == 'n') clip_slot_line = linesel ; 

           else if ( ch == '1' )
              user_block_start = linesel;
           else if ( ch == '2' )
              user_block_end = linesel;

           ch = 0;
           disable_waiting_for_enter();
        }




        else if (ch == '!') 
        {
            enable_waiting_for_enter();
            strncpy( string, "" , PATH_MAX );
            printf("Enter a cmd application: ");
            scan_line( string , PATH_MAX);
            printf("got: \"%s\"\n", string );
            nruncmd( fichier , string );
            disable_waiting_for_enter();
        }

        else if (ch == ':') 
        {
            enable_waiting_for_enter();
            strncpy( string, "" , PATH_MAX );
            printf("Enter a string: ");
            scan_line( string , PATH_MAX);
            printf("got: \"%s\"\n", string );
            disable_waiting_for_enter();
        }


       else if ( ch == 15 )
            open_file( );


    }

    enable_waiting_for_enter();
    return 0;
}




