%{
#include <string.h>
#include "oas_parser.h"
%} 

%option noyywrap
DIGIT              [0-9]
%%
"scan"                   {return SCAN;}
"project"                {return PROJECT;}
"select"                 {return SELECT;}
"sort"                   {return SORT;}
ASC|DESC                 {yylval.ival=!strcmp(yytext,"ASC"); return SORT_ORDER;}
{DIGIT}+                 {yylval.str=strdup(yytext); return NUM;}
[a-zA-Z]+\.[a-zA-Z0-9]+  {yylval.str=strdup(yytext); return KEY;}
[a-zA-Z][0-9a-zA-Z]*     {yylval.str=strdup(yytext); return INPUT;}
[a-zA-Z][0-9a-zA-Z ]*    {yylval.str=strdup(yytext); return ATT;}
[\_a-zA-Z0-9\/.-]+       {yylval.str=strdup(yytext); return FP;}
\(		         {return '(';}
\)		         {return ')';}
"&"                      {yylval.str=strdup(yytext); return PRED;}
"|"                      {yylval.str=strdup(yytext); return PRED;}
","		         {return ',';}
";"		         {return ';';}
"["		         {return '[';}
"]"		         {return ']';}
"\n"                     {return '\n';}
"="                      {yylval.str=strdup(yytext); return OP;}
"<"		         {yylval.str=strdup(yytext); return OP;}
">"		         {yylval.str=strdup(yytext); return OP;}
":="                     {return EQ;}
%%
