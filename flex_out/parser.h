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

#ifndef YY_YY_FLEX_OUT_PARSER_H_INCLUDED
# define YY_YY_FLEX_OUT_PARSER_H_INCLUDED
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
    LBRACE = 258,                  /* LBRACE  */
    RBRACE = 259,                  /* RBRACE  */
    LPAREN = 260,                  /* LPAREN  */
    RPAREN = 261,                  /* RPAREN  */
    LSQB = 262,                    /* LSQB  */
    RSQB = 263,                    /* RSQB  */
    COMMA = 264,                   /* COMMA  */
    SEMICOLON = 265,               /* SEMICOLON  */
    DOT = 266,                     /* DOT  */
    BACKSLASH = 267,               /* BACKSLASH  */
    BACKTICK = 268,                /* BACKTICK  */
    ARROW = 269,                   /* ARROW  */
    PLUS_OP = 270,                 /* PLUS_OP  */
    MULT_OP = 271,                 /* MULT_OP  */
    AND_OP = 272,                  /* AND_OP  */
    OR_OP = 273,                   /* OR_OP  */
    NOT_OP = 274,                  /* NOT_OP  */
    XOR_OP = 275,                  /* XOR_OP  */
    RPLUS_OP = 276,                /* RPLUS_OP  */
    RMULT_OP = 277,                /* RMULT_OP  */
    RAND_OP = 278,                 /* RAND_OP  */
    ROR_OP = 279,                  /* ROR_OP  */
    RXOR_OP = 280,                 /* RXOR_OP  */
    AND = 281,                     /* AND  */
    NOT = 282,                     /* NOT  */
    OR = 283,                      /* OR  */
    XOR = 284,                     /* XOR  */
    ASSIGN_OP = 285,               /* ASSIGN_OP  */
    COMPARE_OP = 286,              /* COMPARE_OP  */
    FUN = 287,                     /* FUN  */
    IF = 288,                      /* IF  */
    ELIF = 289,                    /* ELIF  */
    ELSE = 290,                    /* ELSE  */
    FOR = 291,                     /* FOR  */
    WHILE = 292,                   /* WHILE  */
    IMPORT = 293,                  /* IMPORT  */
    CASE = 294,                    /* CASE  */
    SWITCH = 295,                  /* SWITCH  */
    TYPE = 296,                    /* TYPE  */
    INT_LIT = 297,                 /* INT_LIT  */
    STR_LIT = 298,                 /* STR_LIT  */
    ID = 299,                      /* ID  */
    THEN = 300,                    /* THEN  */
    UNARY = 301                    /* UNARY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);

/* "%code provides" blocks.  */
#line 17 "src/parser.y"

void yyerror(const char * s);

#line 124 "flex_out/parser.h"

#endif /* !YY_YY_FLEX_OUT_PARSER_H_INCLUDED  */
