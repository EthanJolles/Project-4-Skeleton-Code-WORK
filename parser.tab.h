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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    IDENTIFIER = 258,              /* IDENTIFIER  */
    INT_LITERAL = 259,             /* INT_LITERAL  */
    CHAR_LITERAL = 260,            /* CHAR_LITERAL  */
    REAL_LITERAL = 261,            /* REAL_LITERAL  */
    HEX_INT_LITERAL = 262,         /* HEX_INT_LITERAL  */
    OROP = 263,                    /* OROP  */
    ANDOP = 264,                   /* ANDOP  */
    RELOP = 265,                   /* RELOP  */
    ADDOP = 266,                   /* ADDOP  */
    MULOP = 267,                   /* MULOP  */
    MODOP = 268,                   /* MODOP  */
    XOROP = 269,                   /* XOROP  */
    NEGOP = 270,                   /* NEGOP  */
    NOTOP = 271,                   /* NOTOP  */
    ARROW = 272,                   /* ARROW  */
    FOLD = 273,                    /* FOLD  */
    ENDFOLD = 274,                 /* ENDFOLD  */
    LEFT = 275,                    /* LEFT  */
    RIGHT = 276,                   /* RIGHT  */
    BEGIN_ = 277,                  /* BEGIN_  */
    CASE = 278,                    /* CASE  */
    CHARACTER = 279,               /* CHARACTER  */
    ELSE = 280,                    /* ELSE  */
    END = 281,                     /* END  */
    ENDSWITCH = 282,               /* ENDSWITCH  */
    FUNCTION = 283,                /* FUNCTION  */
    INTEGER = 284,                 /* INTEGER  */
    IS = 285,                      /* IS  */
    LIST = 286,                    /* LIST  */
    OF = 287,                      /* OF  */
    OTHERS = 288,                  /* OTHERS  */
    RETURNS = 289,                 /* RETURNS  */
    SWITCH = 290,                  /* SWITCH  */
    WHEN = 291,                    /* WHEN  */
    IF = 292,                      /* IF  */
    ELSIF = 293,                   /* ELSIF  */
    ENDIF = 294,                   /* ENDIF  */
    THEN = 295                     /* THEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 32 "parser.y"

	CharPtr iden;
	Types type;
	Operators oper;
	double value;
	vector<Types>* typesList;

#line 112 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
