/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "symble.y"

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "symble_handlers.h"
#include "symbol_table.h"
#include "symble.tab.h"

int yylex();
int yyerror(const char * msg);

extern FILE * yyin;
extern SymbolTable * symbol_table;
extern int line_no;
int label_no;
LabelNo * true_label_no_stack;
LabelNo * false_label_no_stack;


#line 94 "symble.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "symble.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROCEDURE = 3,                  /* PROCEDURE  */
  YYSYMBOL_FUNCTION = 4,                   /* FUNCTION  */
  YYSYMBOL_RUN = 5,                        /* RUN  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_FOR = 9,                        /* FOR  */
  YYSYMBOL_FROM = 10,                      /* FROM  */
  YYSYMBOL_TO = 11,                        /* TO  */
  YYSYMBOL_BY = 12,                        /* BY  */
  YYSYMBOL_RETURN = 13,                    /* RETURN  */
  YYSYMBOL_PERIOD = 14,                    /* PERIOD  */
  YYSYMBOL_COLON = 15,                     /* COLON  */
  YYSYMBOL_LPAREN = 16,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 17,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 18,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 19,                    /* RBRACE  */
  YYSYMBOL_LARROW = 20,                    /* LARROW  */
  YYSYMBOL_RARROW = 21,                    /* RARROW  */
  YYSYMBOL_COMMA = 22,                     /* COMMA  */
  YYSYMBOL_DEREFERENCE = 23,               /* DEREFERENCE  */
  YYSYMBOL_PLUS = 24,                      /* PLUS  */
  YYSYMBOL_TIMES = 25,                     /* TIMES  */
  YYSYMBOL_DIV = 26,                       /* DIV  */
  YYSYMBOL_MOD = 27,                       /* MOD  */
  YYSYMBOL_EQ = 28,                        /* EQ  */
  YYSYMBOL_NE = 29,                        /* NE  */
  YYSYMBOL_LT = 30,                        /* LT  */
  YYSYMBOL_LE = 31,                        /* LE  */
  YYSYMBOL_GE = 32,                        /* GE  */
  YYSYMBOL_GT = 33,                        /* GT  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_OR = 35,                        /* OR  */
  YYSYMBOL_NOT = 36,                       /* NOT  */
  YYSYMBOL_BOOLEAN_TYPE = 37,              /* BOOLEAN_TYPE  */
  YYSYMBOL_INT1_TYPE = 38,                 /* INT1_TYPE  */
  YYSYMBOL_UINT1_TYPE = 39,                /* UINT1_TYPE  */
  YYSYMBOL_INT2_TYPE = 40,                 /* INT2_TYPE  */
  YYSYMBOL_UINT2_TYPE = 41,                /* UINT2_TYPE  */
  YYSYMBOL_INT4_TYPE = 42,                 /* INT4_TYPE  */
  YYSYMBOL_UINT4_TYPE = 43,                /* UINT4_TYPE  */
  YYSYMBOL_INT8_TYPE = 44,                 /* INT8_TYPE  */
  YYSYMBOL_UINT8_TYPE = 45,                /* UINT8_TYPE  */
  YYSYMBOL_ADDRESS_TYPE = 46,              /* ADDRESS_TYPE  */
  YYSYMBOL_IDENTIFIER = 47,                /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 48,                    /* NUMBER  */
  YYSYMBOL_MINUS = 49,                     /* MINUS  */
  YYSYMBOL_UMINUS = 50,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_unit_definitions = 53,          /* unit_definitions  */
  YYSYMBOL_unit_definition = 54,           /* unit_definition  */
  YYSYMBOL_procedure_definition = 55,      /* procedure_definition  */
  YYSYMBOL_function_definition = 56,       /* function_definition  */
  YYSYMBOL_procedure_head = 57,            /* procedure_head  */
  YYSYMBOL_function_head = 58,             /* function_head  */
  YYSYMBOL_procedure_id = 59,              /* procedure_id  */
  YYSYMBOL_function_id = 60,               /* function_id  */
  YYSYMBOL_params_list = 61,               /* params_list  */
  YYSYMBOL_block = 62,                     /* block  */
  YYSYMBOL_block_start = 63,               /* block_start  */
  YYSYMBOL_block_rest = 64,                /* block_rest  */
  YYSYMBOL_params = 65,                    /* params  */
  YYSYMBOL_param = 66,                     /* param  */
  YYSYMBOL_type_expression = 67,           /* type_expression  */
  YYSYMBOL_statements = 68,                /* statements  */
  YYSYMBOL_statement = 69,                 /* statement  */
  YYSYMBOL_initialized_variable_declaration_statement = 70, /* initialized_variable_declaration_statement  */
  YYSYMBOL_variable_declaration_statement = 71, /* variable_declaration_statement  */
  YYSYMBOL_assignment_statement = 72,      /* assignment_statement  */
  YYSYMBOL_procedure_call_statement = 73,  /* procedure_call_statement  */
  YYSYMBOL_conditional_statement = 74,     /* conditional_statement  */
  YYSYMBOL_condition_head = 75,            /* condition_head  */
  YYSYMBOL_iteration_statement = 76,       /* iteration_statement  */
  YYSYMBOL_return_statement = 77,          /* return_statement  */
  YYSYMBOL_variable_declaration = 78,      /* variable_declaration  */
  YYSYMBOL_expression = 79,                /* expression  */
  YYSYMBOL_arithmetic_expression = 80,     /* arithmetic_expression  */
  YYSYMBOL_relational_expression = 81,     /* relational_expression  */
  YYSYMBOL_logical_expression = 82,        /* logical_expression  */
  YYSYMBOL_function_call_expression = 83,  /* function_call_expression  */
  YYSYMBOL_dereference_expression = 84,    /* dereference_expression  */
  YYSYMBOL_args = 85,                      /* args  */
  YYSYMBOL_arg = 86                        /* arg  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   491

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    55,    55,    57,    58,    61,    62,    65,    68,    71,
      74,    77,    80,    83,    86,    89,    98,   103,   104,   105,
     108,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     123,   124,   127,   128,   129,   130,   131,   132,   133,   134,
     137,   141,   144,   145,   148,   151,   152,   155,   158,   159,
     163,   165,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   179,   180,   181,   182,   183,   186,   187,   188,   189,
     190,   191,   194,   195,   196,   199,   205,   209,   214,   215,
     218
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROCEDURE",
  "FUNCTION", "RUN", "IF", "ELSE", "WHILE", "FOR", "FROM", "TO", "BY",
  "RETURN", "PERIOD", "COLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LARROW", "RARROW", "COMMA", "DEREFERENCE", "PLUS", "TIMES", "DIV",
  "MOD", "EQ", "NE", "LT", "LE", "GE", "GT", "AND", "OR", "NOT",
  "BOOLEAN_TYPE", "INT1_TYPE", "UINT1_TYPE", "INT2_TYPE", "UINT2_TYPE",
  "INT4_TYPE", "UINT4_TYPE", "INT8_TYPE", "UINT8_TYPE", "ADDRESS_TYPE",
  "IDENTIFIER", "NUMBER", "MINUS", "UMINUS", "$accept", "program",
  "unit_definitions", "unit_definition", "procedure_definition",
  "function_definition", "procedure_head", "function_head", "procedure_id",
  "function_id", "params_list", "block", "block_start", "block_rest",
  "params", "param", "type_expression", "statements", "statement",
  "initialized_variable_declaration_statement",
  "variable_declaration_statement", "assignment_statement",
  "procedure_call_statement", "conditional_statement", "condition_head",
  "iteration_statement", "return_statement", "variable_declaration",
  "expression", "arithmetic_expression", "relational_expression",
  "logical_expression", "function_call_expression",
  "dereference_expression", "args", "arg", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      43,   -31,   -29,    31,    43,   -61,   -61,   -61,    16,    16,
      53,    53,   -61,   -61,   -61,   -61,   -61,   -61,   130,   -61,
      23,   -61,    59,    36,    73,    83,    84,    48,    48,    -6,
      48,    20,   -61,    48,   -61,   -61,    69,   -61,   -61,   -61,
     -61,   -61,   -61,    16,   -61,   -61,    -3,   416,   -61,   -61,
     -61,   -61,   -61,    87,    28,   -61,   -61,   362,    90,    48,
      48,    23,    91,    -5,   260,    48,   -61,   -61,   362,    48,
      48,   -61,   -61,   -61,   103,   -61,    48,    66,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,   -61,    23,   -61,   -61,   -61,   -61,   -61,   -61,   -61,
     -61,    98,   -61,    48,   286,   312,   105,   -61,   -61,   338,
     -61,   428,    51,   -61,   208,    16,   234,   106,    40,   -61,
     -61,   -61,   125,   125,   -12,   -12,   -12,   -12,   171,   442,
      40,   -61,   362,    64,   -61,   104,    48,   -61,   -61,    48,
     -61,   -61,   -61,   -61,   109,   113,    48,   156,   428,   -61,
     -61,   390,    48,   -61,   182,    48,   364,   130,    85,   -61
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     2,     4,     5,     6,     0,     0,
       0,     0,    11,    12,     1,     3,    15,     7,     0,     8,
      19,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    58,     0,    39,    14,     0,    31,    32,    33,
      34,    35,    36,     0,    37,    38,     0,     0,    52,    53,
      54,    55,    56,     0,     0,    18,    20,     0,     0,     0,
       0,     0,    59,     0,     0,     0,    76,    74,     0,     0,
       0,    57,    16,    30,    46,    41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    13,     0,    21,    22,    23,    24,    25,    26,    27,
      28,     0,    10,     0,     0,     0,     0,    50,    60,     0,
      51,    80,     0,    79,     0,     0,     0,     0,    61,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      62,    17,     0,     0,    47,     0,     0,    77,    75,     0,
      42,    45,    40,    43,     0,     0,     0,     0,    78,    29,
      44,     0,     0,    48,     0,     0,     0,     0,     0,    49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -61,   -61,   -61,   119,   -61,   -61,   -61,   -61,   -61,   -61,
     118,    -4,   -61,   -61,   -61,    38,   -60,   -26,   -34,   -61,
     -61,   -61,   -61,   -61,   -61,   -61,   -61,   -13,   -27,   -61,
     -61,   -61,   -61,   -61,    34,   -61
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      21,    34,    18,    35,    54,    55,   102,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,   112,   113
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      63,    64,    73,    67,    17,    19,    71,    56,   110,   107,
      65,    75,    78,    79,    80,    81,    12,    76,    13,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    14,   104,   105,    16,    68,    69,    90,   109,    74,
      70,    66,   111,   114,    90,    91,     1,     2,   106,   116,
      92,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,    28,    79,    80,    81,   138,    20,
      53,    29,   144,   139,    23,    24,   111,    25,    26,    56,
      57,   145,    27,    58,    30,    28,   139,    16,    72,    59,
      23,    24,    29,    25,    26,    62,    32,    33,    27,    60,
      61,    28,    68,    16,   159,    30,   103,    69,    29,   147,
     115,   141,   148,   117,   132,   136,    31,    32,    33,   151,
     143,    30,   146,    15,    73,   154,   149,   150,   156,    22,
     131,   158,    31,    32,    33,    23,    24,   133,    25,    26,
       0,     0,     0,    27,     0,     0,    28,     0,    16,    78,
      79,    80,    81,    29,     0,    84,    85,    86,    87,     0,
       0,     0,     0,     0,     0,     0,    30,   152,     0,     0,
       0,     0,     0,     0,    90,     0,     0,    31,    32,    33,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,     0,     0,   155,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    90,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
      90,     0,   140,     0,     0,     0,     0,     0,     0,     0,
       0,    90,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     0,     0,     0,     0,   142,     0,
       0,     0,     0,     0,     0,     0,     0,    90,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
       0,     0,     0,     0,     0,     0,     0,   108,     0,     0,
       0,     0,     0,    90,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,     0,     0,     0,
       0,     0,     0,   134,     0,     0,     0,     0,     0,    90,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,     0,     0,     0,     0,     0,     0,     0,   135,
       0,     0,     0,     0,     0,    90,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
       0,     0,     0,     0,     0,   137,     0,     0,     0,     0,
       0,    90,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     0,     0,     0,     0,     0,     0,
       0,     0,   157,     0,     0,     0,     0,    90,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   153,
       0,     0,     0,    90,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    77,     0,    90,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     0,    90,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    90
};

static const yytype_int16 yycheck[] =
{
      27,    28,    36,    30,     8,     9,    33,    20,    68,    14,
      16,    14,    24,    25,    26,    27,    47,    20,    47,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,     0,    59,    60,    18,    15,    16,    49,    65,    43,
      20,    47,    69,    70,    49,    17,     3,     4,    61,    76,
      22,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    16,    25,    26,    27,    17,    16,
      47,    23,   132,    22,     5,     6,   103,     8,     9,    92,
      21,    17,    13,    47,    36,    16,    22,    18,    19,    16,
       5,     6,    23,     8,     9,    47,    48,    49,    13,    16,
      16,    16,    15,    18,    19,    36,    16,    16,    23,   136,
       7,   115,   139,    47,    16,    10,    47,    48,    49,   146,
      14,    36,    18,     4,   158,   152,    17,    14,   155,    11,
      92,   157,    47,    48,    49,     5,     6,   103,     8,     9,
      -1,    -1,    -1,    13,    -1,    -1,    16,    -1,    18,    24,
      25,    26,    27,    23,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    47,    48,    49,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    12,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    49,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      49,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,
      -1,    -1,    -1,    49,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,    49,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    -1,    -1,    -1,    -1,    49,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    49,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    49,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    19,
      -1,    -1,    -1,    49,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    49,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    49,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    47,    47,     0,    54,    18,    62,    63,    62,
      16,    61,    61,     5,     6,     8,     9,    13,    16,    23,
      36,    47,    48,    49,    62,    64,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    47,    65,    66,    78,    21,    47,    16,
      16,    16,    47,    79,    79,    16,    47,    79,    15,    16,
      20,    79,    19,    69,    62,    14,    20,    21,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      49,    17,    22,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    67,    16,    79,    79,    78,    14,    17,    79,
      67,    79,    85,    86,    79,     7,    79,    47,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    66,    16,    85,    17,    17,    10,    17,    17,    22,
      14,    62,    14,    14,    67,    17,    18,    79,    79,    17,
      14,    79,    11,    19,    79,    12,    79,    18,    68,    19
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    65,    65,
      66,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      68,    68,    69,    69,    69,    69,    69,    69,    69,    69,
      70,    71,    72,    72,    73,    74,    74,    75,    76,    76,
      77,    78,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    80,    80,    80,    80,    80,    81,    81,    81,    81,
      81,    81,    82,    82,    82,    83,    84,    84,    85,    85,
      86
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     2,     2,     2,
       4,     2,     2,     3,     2,     1,     2,     3,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     2,     4,     4,     6,     4,     2,     4,     7,    12,
       3,     3,     1,     1,     1,     1,     1,     2,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     4,     2,     4,     3,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: unit_definitions  */
#line 55 "symble.y"
                           { puts("Done."); }
#line 1348 "symble.tab.c"
    break;

  case 5: /* unit_definition: procedure_definition  */
#line 61 "symble.y"
                                       { printf("ret\n\n"); }
#line 1354 "symble.tab.c"
    break;

  case 6: /* unit_definition: function_definition  */
#line 62 "symble.y"
                             { putchar('\n'); }
#line 1360 "symble.tab.c"
    break;

  case 11: /* procedure_id: PROCEDURE IDENTIFIER  */
#line 77 "symble.y"
                                    { handle_unit_id(&(yyvsp[0].info)); }
#line 1366 "symble.tab.c"
    break;

  case 12: /* function_id: FUNCTION IDENTIFIER  */
#line 80 "symble.y"
                                  { handle_unit_id(&(yyvsp[0].info)); }
#line 1372 "symble.tab.c"
    break;

  case 15: /* block_start: LBRACE  */
#line 89 "symble.y"
                     {
    if (symbol_table->unit_started) {
        symbol_table->unit_started = 0;
    } else {
        push_symbol_table();
    }
}
#line 1384 "symble.tab.c"
    break;

  case 16: /* block_rest: statements RBRACE  */
#line 98 "symble.y"
                               { pop_symbol_table(); }
#line 1390 "symble.tab.c"
    break;

  case 20: /* param: variable_declaration  */
#line 108 "symble.y"
                             { handle_param(&(yyval.info), &(yyvsp[0].info)); }
#line 1396 "symble.tab.c"
    break;

  case 21: /* type_expression: INT1_TYPE  */
#line 112 "symble.y"
                            { (yyval.type_id) = (yyvsp[0].type_id); }
#line 1402 "symble.tab.c"
    break;

  case 22: /* type_expression: UINT1_TYPE  */
#line 113 "symble.y"
                             { (yyval.type_id) = (yyvsp[0].type_id); }
#line 1408 "symble.tab.c"
    break;

  case 23: /* type_expression: INT2_TYPE  */
#line 114 "symble.y"
                            { (yyval.type_id) = (yyvsp[0].type_id); }
#line 1414 "symble.tab.c"
    break;

  case 24: /* type_expression: UINT2_TYPE  */
#line 115 "symble.y"
                             { (yyval.type_id) = (yyvsp[0].type_id); }
#line 1420 "symble.tab.c"
    break;

  case 25: /* type_expression: INT4_TYPE  */
#line 116 "symble.y"
                            { (yyval.type_id) = (yyvsp[0].type_id); }
#line 1426 "symble.tab.c"
    break;

  case 26: /* type_expression: UINT4_TYPE  */
#line 117 "symble.y"
                             { (yyval.type_id) = (yyvsp[0].type_id); }
#line 1432 "symble.tab.c"
    break;

  case 27: /* type_expression: INT8_TYPE  */
#line 118 "symble.y"
                            { (yyval.type_id) = (yyvsp[0].type_id); }
#line 1438 "symble.tab.c"
    break;

  case 28: /* type_expression: UINT8_TYPE  */
#line 119 "symble.y"
                             { (yyval.type_id) = (yyvsp[0].type_id); }
#line 1444 "symble.tab.c"
    break;

  case 29: /* type_expression: ADDRESS_TYPE LPAREN type_expression RPAREN  */
#line 120 "symble.y"
                                                             { (yyval.type_id) = (yyvsp[-3].type_id); }
#line 1450 "symble.tab.c"
    break;

  case 40: /* initialized_variable_declaration_statement: variable_declaration LARROW expression PERIOD  */
#line 138 "symble.y"
    { handle_initialization(&(yyvsp[-3].info), &(yyvsp[-1].info)); }
#line 1456 "symble.tab.c"
    break;

  case 42: /* assignment_statement: IDENTIFIER LARROW expression PERIOD  */
#line 144 "symble.y"
                                                           { handle_assignment(NULL, &(yyvsp[-1].info), &(yyvsp[-3].info)); }
#line 1462 "symble.tab.c"
    break;

  case 43: /* assignment_statement: expression RARROW IDENTIFIER PERIOD  */
#line 145 "symble.y"
                                                           { handle_assignment(NULL, &(yyvsp[-3].info), &(yyvsp[-1].info)); }
#line 1468 "symble.tab.c"
    break;

  case 45: /* conditional_statement: condition_head block ELSE block  */
#line 151 "symble.y"
                                                        { handle_condition(1); }
#line 1474 "symble.tab.c"
    break;

  case 46: /* conditional_statement: condition_head block  */
#line 152 "symble.y"
                                             { handle_condition(0); }
#line 1480 "symble.tab.c"
    break;

  case 47: /* condition_head: IF LPAREN expression RPAREN  */
#line 155 "symble.y"
                                             { handle_condition_head(&(yyvsp[-1].info)); }
#line 1486 "symble.tab.c"
    break;

  case 50: /* return_statement: RETURN expression PERIOD  */
#line 163 "symble.y"
                                            { printf("mov %s, $ret\n", (yyvsp[-1].info).string); printf("ret\n"); }
#line 1492 "symble.tab.c"
    break;

  case 51: /* variable_declaration: IDENTIFIER COLON type_expression  */
#line 165 "symble.y"
                                                        { handle_variable_declaration( &(yyval.info), &(yyvsp[-2].info), (yyvsp[0].type_id)); }
#line 1498 "symble.tab.c"
    break;

  case 57: /* expression: MINUS expression  */
#line 173 "symble.y"
                                           { handle_unary_minus_expression(&(yyval.info), &(yyvsp[0].info)); }
#line 1504 "symble.tab.c"
    break;

  case 58: /* expression: NUMBER  */
#line 174 "symble.y"
                    { handle_number(&(yyval.info), &(yyvsp[0].info)); }
#line 1510 "symble.tab.c"
    break;

  case 59: /* expression: IDENTIFIER  */
#line 175 "symble.y"
                        { handle_identifier(&(yyval.info), &(yyvsp[0].info)); }
#line 1516 "symble.tab.c"
    break;

  case 60: /* expression: LPAREN expression RPAREN  */
#line 176 "symble.y"
                                      { (yyval.info) = (yyvsp[-1].info); }
#line 1522 "symble.tab.c"
    break;

  case 61: /* arithmetic_expression: expression PLUS expression  */
#line 179 "symble.y"
                                                   { handle_arithmetic_expression(&(yyval.info), PLUS, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1528 "symble.tab.c"
    break;

  case 62: /* arithmetic_expression: expression MINUS expression  */
#line 180 "symble.y"
                                      { handle_arithmetic_expression(&(yyval.info), MINUS, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1534 "symble.tab.c"
    break;

  case 63: /* arithmetic_expression: expression TIMES expression  */
#line 181 "symble.y"
                                      { handle_arithmetic_expression(&(yyval.info), TIMES, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1540 "symble.tab.c"
    break;

  case 64: /* arithmetic_expression: expression DIV expression  */
#line 182 "symble.y"
                                    { handle_arithmetic_expression(&(yyval.info), DIV, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1546 "symble.tab.c"
    break;

  case 65: /* arithmetic_expression: expression MOD expression  */
#line 183 "symble.y"
                                    { handle_arithmetic_expression(&(yyval.info), MOD, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1552 "symble.tab.c"
    break;

  case 66: /* relational_expression: expression EQ expression  */
#line 186 "symble.y"
                                                 { handle_relational_expression(&(yyval.info), EQ, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1558 "symble.tab.c"
    break;

  case 67: /* relational_expression: expression NE expression  */
#line 187 "symble.y"
                                   { handle_relational_expression(&(yyval.info), NE, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1564 "symble.tab.c"
    break;

  case 68: /* relational_expression: expression LT expression  */
#line 188 "symble.y"
                                   { handle_relational_expression(&(yyval.info), LT, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1570 "symble.tab.c"
    break;

  case 69: /* relational_expression: expression LE expression  */
#line 189 "symble.y"
                                   { handle_relational_expression(&(yyval.info), LE, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1576 "symble.tab.c"
    break;

  case 70: /* relational_expression: expression GE expression  */
#line 190 "symble.y"
                                   { handle_relational_expression(&(yyval.info), GE, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1582 "symble.tab.c"
    break;

  case 71: /* relational_expression: expression GT expression  */
#line 191 "symble.y"
                                   { handle_relational_expression(&(yyval.info), GT, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1588 "symble.tab.c"
    break;

  case 72: /* logical_expression: expression AND expression  */
#line 194 "symble.y"
                                               { handle_logical_expression(&(yyval.info), AND, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1594 "symble.tab.c"
    break;

  case 73: /* logical_expression: expression OR expression  */
#line 195 "symble.y"
                                   { handle_logical_expression(&(yyval.info), OR, &(yyvsp[-2].info), &(yyvsp[0].info)); }
#line 1600 "symble.tab.c"
    break;

  case 74: /* logical_expression: NOT expression  */
#line 196 "symble.y"
                         { handle_logical_expression(&(yyval.info), NOT, &(yyvsp[0].info), NULL); }
#line 1606 "symble.tab.c"
    break;

  case 75: /* function_call_expression: IDENTIFIER LPAREN args RPAREN  */
#line 199 "symble.y"
                                                         {
    strcpy((yyval.info).string, "$ret");
    printf("call _%s\n", (yyvsp[-3].info).string);
}
#line 1615 "symble.tab.c"
    break;

  case 76: /* dereference_expression: DEREFERENCE IDENTIFIER  */
#line 205 "symble.y"
                                                {
    get_new_register((yyval.info).string);
    printf("%s = address %s\n", (yyval.info).string, (yyvsp[0].info).string);
}
#line 1624 "symble.tab.c"
    break;

  case 77: /* dereference_expression: DEREFERENCE LPAREN expression RPAREN  */
#line 210 "symble.y"
                           { get_new_register((yyval.info).string); printf("%s = address %s\n", (yyval.info).string, (yyvsp[-1].info).string); }
#line 1630 "symble.tab.c"
    break;

  case 80: /* arg: expression  */
#line 218 "symble.y"
                 { handle_arg(&(yyval.info), &(yyvsp[0].info)); }
#line 1636 "symble.tab.c"
    break;


#line 1640 "symble.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 221 "symble.y"


int yyerror(const char * msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

FILE * fopen_checked(const char * const file_name, const char * const mode) {
    FILE * fp = fopen(file_name, mode);
    if (!fp) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }
    return fp;
}

int main(int argc, char ** argv) {
    if (argc > 1) {
        yyin = fopen_checked(argv[1], "r");
    }
    push_symbol_table();
    yyparse();
    if (argc > 1) {
        fclose(yyin);
    }
    pop_symbol_table();
    return EXIT_SUCCESS;
}

