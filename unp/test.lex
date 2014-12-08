/* scanner for a toy Pascal-like language */
     
%{
/* need this for the call to atof() below */
#include <math.h>
%}
%option noyywrap
DIGIT    [0-9]
ID       [a-z_][a-z0-9_]*
STRING   \"([^\"]|\\\")*\"
%%

{DIGIT}+    {
     printf( "An integer: %s (%d)\n", yytext,
             atoi( yytext ) );
     }

{DIGIT}+"."{DIGIT}*        {
     printf( "A float: %s (%g)\n", yytext,
             atof( yytext ) );
     }

if|else|while|do|goto|volatile|const|static        {
     printf( "A keyword: %s\n", yytext );
     }

{ID}        printf( "An identifier: %s\n", yytext );

{STRING}    {
            printf( "An string: %s\n", yytext );
}
"+"|"-"|"*"|"/"|"{"|"}"|"("|")"|"["|"]"|","|";"|"'"|"\""   printf( "An operator: %s\n", yytext );

"{"[\^{}}\n]*"}"     /* eat up one-line comments */

[ \t\n]+          /* eat up whitespace */

.           printf( "Unrecognized character: %s\n", yytext );

%%

int main( int argc, char **argv )
{
++argv, --argc;  /* skip over program name */
if ( argc > 0 )
     yyin = fopen( argv[0], "r" );
else
     yyin = stdin;

yylex();
}
