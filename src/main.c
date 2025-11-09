#include <stdio.h>

enum token_type
{
  // Special characters
  LBRACE,
  RBRACE,
  DQUOTE,
  COMMA,

  // Value types
  STRING,
  NUMBER,
  BOOLEAN,
  NULL_TOKEN,

  // EOF
  EOF_TOKEN,

  // Error
  ERROR_TOKEN
};

typedef struct
{
  enum token_type type;
  char value[512];
  int line;
  int column;
} Token;

typedef struct
{
  const char* input;
  int pos;
  int line;
  int column;
  char current;
  Token tokens[2048];
} Lexer;

Lexer
init_lexer(const char* input)
{
  Lexer lexer;
  lexer.input = input;
  lexer.pos = 0;
  lexer.line = 1;
  lexer.column = 1;
  lexer.current = input[0];
  return lexer;
}

const char*
peek(Lexer* lexer)
{
  if (lexer->input[lexer->pos + 1] != '\0')
    return &lexer->input[lexer->pos + 1];
  return nullptr;
}

void
advance(Lexer* lexer)
{
  if (lexer->input[lexer->pos] == '\0')
    return;

  if (lexer->current == '\n')
  {
    lexer->line++;
    lexer->column = 1;
  }
  else
  {
    lexer->column++;
  }

  lexer->pos++;
  lexer->current = lexer->input[lexer->pos];
}

void
skip_whitespace(Lexer* lexer)
{
  while (lexer->current == ' ' || lexer->current == '\t' ||
         lexer->current == '\r' || lexer->current == '\n')
  {
    advance(lexer);
  }
}

void
skip_single_line_comment(Lexer* lexer)
{
  while (lexer->current != '\n' && lexer->current != '\0')
  {
    advance(lexer);
  }
}

void
skip_multiple_lines_comment(Lexer* lexer)
{
  while ((lexer->current != '*' || *peek(lexer) != '/') &&
         lexer->current != '\0')
  {
    advance(lexer);
  }
}

void
analyze_lexer(Lexer* lexer)
{
  char current_char = lexer->input[lexer->pos];
  while (current_char != '\0')
  {
    if (current_char == ' ' || current_char == '\t' || current_char == '\r' ||
        current_char == '\n')
    {
      skip_whitespace(lexer);
      current_char = lexer->input[lexer->pos];
      continue;
    }

    if (current_char == '/' && *peek(lexer) == '/')
    {
      skip_single_line_comment(lexer);
      current_char = lexer->input[lexer->pos];
      continue;
    }

    if (current_char == '/' && *peek(lexer) == '*')
    {
      skip_multiple_lines_comment(lexer);
      current_char = lexer->input[lexer->pos];
      continue;
    }
  }
}

int
main()
{
  printf("Hello, World!\n");
  return 0;
}
