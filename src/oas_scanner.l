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
ASC|DESC                 {oas_lval.ival=!strcmp(yytext,"ASC"); return SORT_ORDER;}
{DIGIT}+                 {oas_lval.str=strdup(yytext); return NUM;}
[a-zA-Z]+\.[a-zA-Z0-9]+  {oas_lval.str=strdup(yytext); return KEY;}
[a-zA-Z][0-9a-zA-Z]*     {oas_lval.str=strdup(yytext); return INPUT;}
[a-zA-Z][0-9a-zA-Z ]*    {oas_lval.str=strdup(yytext); return ATT;}
[\_a-zA-Z0-9\/.-]+       {oas_lval.str=strdup(yytext); return FP;}
\(		         {return '(';}
\)		         {return ')';}
"&"                      {oas_lval.str=strdup(yytext); return PRED;}
"|"                      {oas_lval.str=strdup(yytext); return PRED;}
","		         {return ',';}
";"		         {return ';';}
"["		         {return '[';}
"]"		         {return ']';}
"\n"                     {return '\n';}
"="                      {oas_lval.str=strdup(yytext); return OP;}
"<"		         {oas_lval.str=strdup(yytext); return OP;}
">"		         {oas_lval.str=strdup(yytext); return OP;}
":="                     {return EQ;}
%%
