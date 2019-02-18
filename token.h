#ifndef _RONG_TOKEN_H
#define _RONG_TOKEN_H
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
namespace Rong
{
namespace Token
{
enum
{
    // Punctuators
    LPAR = '(',
    RPAR = ')',
    LSQB = '[',
    RSQB = ']',
    COLON = ':',
    COMMA = ',',
    SEMI = ';',
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    OR = '|',
    AND = '&',
    XOR = '^',
    LESS = '<',
    GREATER = '>',
    EQUAL = '=',
    DOT = '.',
    MOD = '%',
    LBRACE = '{',
    RBRACE = '}',
    TILDE = '~',
    NOT = '!',
    COND = '?',
    SHARP = '#',
    NEW_LINE = '\n',
    DSHARP = 128, //'##'
    PTR,
    INC,          // '++'
    DEC,          // '--'
    LEFT,         // '<<'
    RIGHT,        // '>>'
    LE,           // '<='
    GE,           // '>='
    EQ,           // '=='
    NE,           // '!='
    LOGICAL_AND,  // '&&'
    LOGICAL_OR,   // '||'
    MUL_ASSIGN,   // '*='
    DIV_ASSIGN,   // '/='
    MOD_ASSIGN,   // '%='
    ADD_ASSIGN,   // '+='
    SUB_ASSIGN,   // '-='
    LEFT_ASSIGN,  // '<<='
    RIGHT_ASSIGN, // '>>='
    AND_ASSIGN,   // '&='
    XOR_ASSIGN,   // '^='
    OR_ASSIGN,    // '|='
    ELLIPSIS,
    // Punctuators end

    // KEYWORD BEGIN
    // TYPE QUALIFIER BEGIN
    CONST,    // 'const'
    RESTRICT, // 'restrict'
    VOLATILE, // 'volatile'
    ATOMIC,   // 'atomic'
    // TYPE QUALIFIER END

    // TYPE SPECIFIER BEGIN
    VOID,     // 'void'
    CHAR,     // 'char'
    SHORT,    // 'short'
    INT,      // 'int'
    LONG,     // 'long'
    FLOAT,    // 'float'
    DOUBLE,   // 'double'
    SIGNED,   // 'signed'
    UNSIGNED, // 'unsigned'
    BOOL,     //_Bool
    COMPLEX,  //_Complex
    STRUCT,   // 'struct'
    UNION,    // 'union'
    ENUM,     // 'enum'
    // TYPE SPECIFIER END

    BREAK,    // 'break'
    CASE,     // 'cast'
    CONTINUE, // 'continue'
    DEFAULT,  // 'default'
    DO,       // 'do'
    ELSE,     // 'else'
    FOR,      // 'for'
    GOTO,     // 'goto'
    IF,       // 'if'
    RETURN,   // 'return'
    SIZEOF,   // 'sizeof'
    SWITCH,   // 'switch'
    WHILE,    // 'while'
    // KEYWORD END
    NOKEYWORD,  // no a keyword
    IDENTIFIER, // identifier
    I_CONSTANT, // number
    C_CONSTANT, // char
    F_CONSTANT, // double
    LITERAL,    // string
    ERROR,      // error
    END,        // eof
};

bool isIdentifier(int tag);
bool isPunctuator(int tag);
int isKeyWord(const std::string &val);
std::string getTagLexe(int tag);
extern const std::unordered_map<std::string, int> kwTypeMap_;
extern const std::unordered_map<int, const char *> TagLexemeMap_;
} // namespace Token

struct source_location
{
    std::shared_ptr<std::string> filenamePtr;
    size_t row;
    size_t pos;
    source_location(std::shared_ptr<std::string> &fnp, size_t r, size_t p)
        : filenamePtr(fnp),
          row(r),
          pos(p)
    {
    }
};

class token
{
  public:
    token(int tag_, std::string val_, source_location &loc_)
        : tag(tag_),
          val(val_),
          loc(loc_) {}
    int tag;
    std::string val;
    source_location loc;
};

class token_list
{
  public:
    typedef std::shared_ptr<token> token_ptr;
    void Add(token_ptr tk) { list.emplace_back(tk); }
    token_ptr Get() { return list[index++]; }
    token_ptr Peek() { return list[index]; }
    bool Unget() { return index > 0 ? --index, true : false; }
    bool Try(int tag) { return list[index]->tag == tag ? ++index, true : false; }
    bool Test(int tag) { return list[index]->tag == tag; }
    bool Empty(){return index==list.size();}
    int index;
    std::vector<std::shared_ptr<token>> list;
};
} // namespace Rong
#endif