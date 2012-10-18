%{
  #include <stdio.h>
  #include <errno.h>
  #include <string.h>
  #include <stdlib.h>

  #include "oas_parser.h"
///  #include "oas_scanner.h" //doesnt need it 

  void add_keys(char *, char *, char *);
  void add_key(char *);
  void create_key_array();
  void create_select_array();

  /* Initially lets just say at most 100 keys. */
  unsigned int key_size = 100;
  char **key_list;
  unsigned int key_count = 0;  

  unsigned int key_array_count = 0;
  unsigned int sort_order_count = 0;
  FILE *fp;
%}

%union {
  int ival;
  char *str;
}

%token <str>      	NUM
%token <str>       	INPUT
%token <str>       	ATT
%token <str>       	FP
%token SCAN        	"scan"
%token SELECT      	"select"
%token PROJECT     	"project"
%token SORT        	"sort"
%token <str>       	OP
%token <str>       	PRED
%token <str>       	EQ
%token <ival>	   	SORT_ORDER		       
%token <str>	   	KEY

%type <str>	   	line
%type <str>	   	scan		
%type <str>	   	project
%type <str>	   	sort
%type <str>	   	select
			
%start program

%%
program:	line {
    int i;
    fprintf(fp, "\tprint_r_list(%s);\n",$1);
    fprintf(fp, "\treturn 0;\n}\n");
    } ;

line:
/* epsilon */ {}

/* SCAN */
| line INPUT EQ scan '\n' { 
    fprintf(fp, "\tr_list *%s = scan(\"%s\");\n",$2,$4);
    $$ = $2;
 }

/* SELECT */
| line INPUT EQ select '\n' {
    int i;
    create_select_array();
    fprintf(fp, "\tr_list *%s = select_oas(%s,keys%d);\n",$2,$4,key_array_count++);

    for (i=0;i<key_count; i++) free(key_list[i]);

    key_count = 0;
    $$ = $2;
    }

/* PROJECT */
| line INPUT EQ project '\n' {
    int i;

    create_key_array();
    fprintf(fp,"\tr_list *%s = project(%s,keys%d);\n",$2,$4,key_array_count++);

    for (i=0; i<key_count; i++) free(key_list[i]);
    key_count = 0;
    $$ = $2;
    }

/* SORT */
| line INPUT EQ sort '\n' {
    int i;
    create_key_array();
    fprintf(fp,"\tr_list *%s = sort(%s,keys%d,order%d);\n",$2,$4,
            key_array_count++, sort_order_count++);
    
    for (i=0; i<key_count; i++) free(key_list[i]);
    key_count = 0;
    $$ = $2;
    }

| error '\n' { $$ = "error"};

scan:
"scan" '(' FP ')' ';'                                   {$$ = $3;} ;

select:
"select" '(' INPUT ',' '[' selectOp ']' ')' ';'         {$$ = $3;} ;

project:
"project" '(' INPUT ',''[' keylist ']'')'';'           {$$ = $3;} ;

sort:
"sort" '(' INPUT ',''[' keylist ']'',' SORT_ORDER ')'';' {
    if ($9) {
	char order[]  = "ASC";
        fprintf(fp, "\ts_order order%d = %s;\n",sort_order_count,order);
    }
    else {
	char order[]  = "DESC";
        fprintf(fp, "\ts_order order%d = %s;\n",sort_order_count,order);
    }
    $$ = $3;
    } ;

keylist:
  /* epsilon */
| KEY                                     {add_key($1);}
| KEY ',' keylist                         {add_key($1);} 
| INPUT                                   {add_key($1);}
| INPUT ',' keylist                       {add_key($1);} ;

selectOp:
/* epsilon */
| PRED ',' selectOp                            {add_key($1);} ;
| '(' KEY ',' OP ',' KEY ')'                   {add_keys($2,$4,$6);} ;
| '(' KEY ',' OP ',' KEY ')' ',' selectOp      {add_keys($2,$4,$6);} ;
| '(' KEY ',' OP ',' NUM ')'                   {add_keys($2,$4,$6);} ;
| '(' KEY ',' OP ',' NUM ')' ',' selectOp      {add_keys($2,$4,$6);} ;
| '(' KEY ',' OP ',' ATT ')'                   {add_keys($2,$4,$6);} ;
| '(' KEY ',' OP ',' ATT ')' ',' selectOp      {add_keys($2,$4,$6);} ;
| '(' INPUT ',' OP ',' INPUT ')'               {add_keys($2,$4,$6);} ;
| '(' INPUT ',' OP ',' INPUT ')' ',' selectOp  {add_keys($2,$4,$6);} ;
| '(' INPUT ',' OP ',' NUM ')'                 {add_keys($2,$4,$6);} ;
| '(' INPUT ',' OP ',' NUM ')' ',' selectOp    {add_keys($2,$4,$6);} ;
| '(' INPUT ',' OP ',' ATT ')'                 {add_keys($2,$4,$6);} ;
| '(' INPUT ',' OP ',' ATT ')' ',' selectOp    {add_keys($2,$4,$6);} ;

%%

int yyerror(const char *s) {
    fprintf (stderr, "%s\n", s);

    exit(-1);
}

void create_select_array() {
    int i;
    fprintf(fp, "\tconst char *keys%d[%d] = {",key_array_count,key_count+1);

    for (i=key_count-1; i>=0; i-=4) {
	fprintf(fp, "\"%s\", ", key_list[i-2]);
	fprintf(fp, "\"%s\", ", key_list[i-1]);
	fprintf(fp, "\"%s\", ", key_list[i]);

	if (i-3 > 0)
	    fprintf(fp, "\"%s\", ", key_list[i-3]);
    }
    fprintf(fp, "NULL};\n");
}

void create_key_array() {
    int i;
    fprintf(fp, "\tconst char *keys%d[%d] = {",key_array_count,key_count+1);

    for (i=key_count-1; i>=0; i--) {
	fprintf(fp, "\"");
	fprintf(fp, "%s",key_list[i]);
	fprintf(fp, "\", ");
    }
    fprintf(fp, "NULL};\n");
}

void add_keys(char *key0, char *key1, char *key2) {
    add_key(key0);
    add_key(key1);
    add_key(key2);
}

void add_key(char *key) {
    if (key_count < key_size) {
	key_list[key_count] = malloc(strlen(key) * sizeof(char) + 1);
	strcpy(key_list[key_count], key);
	key_count++;
    }
    else {
	key_size *= 2;
	key_list = realloc(key_list, key_size * sizeof(char *));
	key_list[key_count] = malloc(strlen(key) * sizeof(char) + 1);
	strcpy(key_list[key_count], key);
	key_count++;
    }
}
int main() {
    key_list = malloc(key_size * sizeof(char *));

    fp = fopen("temp.c", "w");
    char *t = "#include <stdio.h>\n"
	"\n" 
	"#include \"record.h\"\n" 
	"#include \"scan.h\"\n"
	"#include \"select.h\"\n"
	"#include \"project.h\"\n"
	"#include \"sort.h\"\n"
	"\n"
	"int main() {\n";
    
    fprintf(fp,"%s",t);
    
    yyparse();

    free(key_list);
    fclose(fp);
    return 0;
}
