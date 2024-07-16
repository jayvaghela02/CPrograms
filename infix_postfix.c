
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
 
#define MAX 50
 
     char output[MAX] ;
     char stack[MAX] ;
     char input[MAX] ;
     char *s, *t ; /*pointers to input and output strings*/
     char ch; /*choice*/
     int top; /*Stack top*/
     int l ; /*length of infix string*/
 
     /*Function Prototypes*/
     void Initialize (void);
     void SetExpression (char *);
     char PopFromStack (void );
     void PushOnStack (char);
     int priority (char);
     void ConvertToPrefix (void);
     void ConvertToPostfix (void);
 
void main( )
{
//     clrscr( ) ;
     Initialize (  ) ;
     printf ( "\nEnter an expression in infix form: " ) ;
     gets ( input ) ;
     printf ( "\nSpecify output expression type, 1)Prefix 2)Postfix " ) ;
     ch=getch();
     SetExpression (input) ;
     if(ch=='1') /*Infix->Prefix*/
      {
            strrev ( s );
            ConvertToPrefix ( ) ;
            strrev (  output ) ;
            printf ( "\nThe Prefix expression is: " ) ;
      }
     else
      {
       ConvertToPostfix ( ) ;
       printf ( "\nThe Postfix expression is: " ) ;
      }
 
     puts(output);
     getch( ) ;
}
 
void Initialize (void)
{
            top = -1 ;/*Make stack empty*/
            strcpy ( output, "" ) ;
            strcpy ( stack, "" ) ;
            l = 0 ;
}
 
void SetExpression ( char *str )
{
            s = str ;
            l = strlen ( s ) ;
            *( output + l ) = '\0' ;
            t = output;
}
 
/* adds operator to the stack */
void PushOnStack (  char c )
{
            if ( top == MAX - 1 )
             printf ( "\nStack is full.\n" ) ;
            else
            {
                        top++ ;
                        stack[top] = c ;
            }
}
 
/* pops an operator from the stack */
char PopFromStack (void )
{
            if ( top == -1 ) /* Stack is empty*/
              return -1 ;
            else
            {
                        char item = stack[top] ;
                        top-- ;
                        return item ;
            }
}
 
 
/* returns the priotity of the operator */
int priority ( char c )
{
            if ( c == '^' ) return 3 ;/*Exponential operator*/
            if ( c == '*' || c == '/' || c == '%' )     return 2 ;
            else if ( c == '+' || c == '-' ) return 1 ;
            else return 0 ;
}
 
/* converts the Infix expression to Prefix form */
void ConvertToPrefix (void)
{
            char opr ;
 
            while ( *(s))
            {
                        /*Skip white spaces, if any*/
                        if ( *( s )  == ' ' || *( s )  == '\t' )
                        {
                                    s++    ;
                                    continue ;
                        }
 
                        if ( isdigit ( *( s )  ) || isalpha ( *(s )  ) )/*operands*/
						{
                              while ( isdigit ( *( s )  ) || isalpha ( * ( s )  ) )
                                    {
                                                *( t ) = *( s )  ;
                                                s++   ;
                                                t++ ;
                                    }
                        }
                        if ( *( s )  == ')' )/*Closing Parenthesis*/
						{
                                   PushOnStack (  *( s ) ) ;
                                    s++    ;
                        }
               if ( *( s )  == '*' || *( s )  == '+' || *( s )== '/' || *( s )  == '%' || *( s )  == '-' || *( s )== '^' )
                        {
                                    if ( top != -1 )
                                    {
										opr = PopFromStack (  ) ;     
		                                   while ( priority ( opr ) > priority ( *( s )  ) )
                                                {
                                                            *( t ) = opr ;
                                                            t++ ;
                                                            opr = 
                                                    PopFromStack (  ) ;
                                                }
                                                PushOnStack (  opr ) ;
                                                PushOnStack (  *( s )  ) ;
                                    }
                                    else PushOnStack (  *( s ) ) ;
                                    s++    ;
                        }
                        if ( *( s )  == '(' )/*Opening Parenthesis*/
						{
                                    opr = PopFromStack (  ) ;
                                    while ( opr != ')' )
                                    {
                                                *( t ) = opr ;
                                                t++ ;
                                                opr =  PopFromStack (  ) ;
                                    }
                                    s++ ;
                        }
            }


            while ( top != -1 )    
            {
                        opr = PopFromStack (  ) ;
                        *( t ) = opr ;
                        t++ ;
            }
            t++ ;
}

/* converts the infix expr. to postfix form */
void ConvertToPostfix (void)
{
            char opr ;
 
            while ( *( s )  )
            {       /*Skip white spaces, if any*/
                        if ( *( s )  == ' ' || *( s )  == '\t' )
                        {
                                    s++    ;
                                    continue ;
                        }
 
      if ( isdigit ( *( s )  ) || isalpha (*(s )  ) )/*Operands*/
                        {
            while ( isdigit ( *( s )  ) || isalpha ( *( s )  ) )
                                    {
                                                *( t ) = *( s )  ;
                                                s++   ;
                                                t++ ;
                                    }
                        }
                        if ( *( s )  == '(' )/*Opening Parenthesis*/
                        {
                                    PushOnStack (  *( s ) ) ;
                                    s++    ;
                        }
if ( *( s )  == '*' || *( s )  == '+' || *( s )  
      == '/' || *( s )  == '%' || *( s )  == '-' || *( s )  
                  == '^' )
                        {
      if ( top != -1 )
          {
          opr = PopFromStack (  ) ;
        while ( priority ( *( s ))<=priority ( opr ))
         {
              *( t ) = opr ;
               t++ ;
              opr =PopFromStack (  ) ;
         }        
        
          PushOnStack (  opr ) ;
         PushOnStack (  *( s )  ) ;
                                    }
                                    else PushOnStack (  *( s ) ) ;
                                    s++    ;
                        }
                        if ( *( s )  == ')' )/*Closing Parenthesis*/
                        {
                                    opr = PopFromStack (  ) ;
                          while ( opr != '(' )
                          {
                              *( t ) = opr ;
                                t++ ;
                              opr =  PopFromStack (  ) ;
                            }
                             s++    ;
                        }
            }
            while ( top != -1 )/*While stack is not empty*/
            {
                        opr = PopFromStack (  ) ;
                        *( t ) = opr ;
                        t++ ;
            }
            t++ ;
}
 
