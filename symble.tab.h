/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SYMBLE_TAB_H_INCLUDED
# define YY_YY_SYMBLE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROCEDURE = 258,               /* PROCEDURE  */
    FUNCTION = 259,                /* FUNCTION  */
    RUN = 260,                     /* RUN  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    WHILE = 263,                   /* WHILE  */
    FOR = 264,                     /* FOR  */
    FROM = 265,                    /* FROM  */
    TO = 266,                      /* TO  */
    BY = 267,                      /* BY  */
    RETURN = 268,                  /* RETURN  */
    PERIOD = 269,                  /* PERIOD  */
    COLON = 270,                   /* COLON  */
    LPAREN = 271,                  /* LPAREN  */
    RPAREN = 272,                  /* RPAREN  */
    LBRACE = 273,                  /* LBRACE  */
    RBRACE = 274,                  /* RBRACE  */
    LARROW = 275,                  /* LARROW  */
    RARROW = 276,                  /* RARROW  */
    COMMA = 277,                   /* COMMA  */
    DEREFERENCE = 278,             /* DEREFERENCE  */
    PLUS = 279,                    /* PLUS  */
    TIMES = 280,                   /* TIMES  */
    DIV = 281,                     /* DIV  */
    MOD = 282,                     /* MOD  */
    EQ = 283,                      /* EQ  */
    NE = 284,                      /* NE  */
    LT = 285,                      /* LT  */
    LE = 286,                      /* LE  */
    GE = 287,                      /* GE  */
    GT = 288,                      /* GT  */
    AND = 289,                     /* AND  */
    OR = 290,                      /* OR  */
    NOT = 291,                     /* NOT  */
    BOOLEAN_TYPE = 292,            /* BOOLEAN_TYPE  */
    INT1_TYPE = 293,               /* INT1_TYPE  */
    UINT1_TYPE = 294,              /* UINT1_TYPE  */
    INT2_TYPE = 295,               /* INT2_TYPE  */
    UINT2_TYPE = 296,              /* UINT2_TYPE  */
    INT4_TYPE = 297,               /* INT4_TYPE  */
    UINT4_TYPE = 298,              /* UINT4_TYPE  */
    INT8_TYPE = 299,               /* INT8_TYPE  */
    UINT8_TYPE = 300,              /* UINT8_TYPE  */
    ADDRESS_TYPE = 301,            /* ADDRESS_TYPE  */
    IDENTIFIER = 302,              /* IDENTIFIER  */
    NUMBER = 303,                  /* NUMBER  */
    MINUS = 304,                   /* MINUS  */
    UMINUS = 305                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "symble.y"

    Info info;
    char string[LEXEME_SIZE];
    int type_id;

#line 120 "symble.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);

/* "%code provides" blocks.  */
#line 30 "symble.y"

    int yylex();
    int yyerror(const char * msg);

#line 140 "symble.tab.h"

#endif /* !YY_YY_SYMBLE_TAB_H_INCLUDED  */
