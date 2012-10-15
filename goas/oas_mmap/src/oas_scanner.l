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
ASC|DESC                 {oas_lval.ival=!strcmp(oas_text,"ASC"); return SORT_ORDER;}
{DIGIT}+                 {oas_lval.str=strdup(oas_text); return NUM;}
[a-zA-Z]+\.[a-zA-Z0-9]+  {oas_lval.str=strdup(oas_text); return KEY;}
[a-zA-Z][0-9a-zA-Z]*     {oas_lval.str=strdup(oas_text); return INPUT;}
[a-zA-Z][0-9a-zA-Z ]*    {oas_lval.str=strdup(oas_text); return ATT;}
[\_a-zA-Z0-9\/.-]+       {oas_lval.str=strdup(oas_text); return FP;}
\(		         {return '(';}
\)		         {return ')';}
"&"                      {oas_lval.str=strdup(oas_text); return PRED;}
"|"                      {oas_lval.str=strdup(oas_text); return PRED;}
","		         {return ',';}
";"		         {return ';';}
"["		         {return '[';}
"]"		         {return ']';}
"\n"                     {return '\n';}
"="                      {oas_lval.str=strdup(oas_text); return OP;}
"<"		         {oas_lval.str=strdup(oas_text); return OP;}
">"		         {oas_lval.str=strdup(oas_text); return OP;}
":="                     {return EQ;}
%%
