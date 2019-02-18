#include "token.h"

using namespace std;
using namespace Rong;
bool Token::isIdentifier(int tag) { return tag >= Token::CONST && tag <= Token::WHILE; }
bool Token::isPunctuator(int tag) { return tag >= Token::LPAR && tag <= Token::ELLIPSIS; }

const std::unordered_map<std::string, int> Token::kwTypeMap_{
    //{ "auto", Token::AUTO },
    {"break", Token::BREAK},
    {"case", Token::CASE},
    {"char", Token::CHAR},
    {"const", Token::CONST},
    {"continue", Token::CONTINUE},
    {"default", Token::DEFAULT},
    {"do", Token::DO},
    {"double", Token::DOUBLE},
    {"else", Token::ELSE},
    {"enum", Token::ENUM},
    //{ "extern", Token::EXTERN },
    {"float", Token::FLOAT},
    {"for", Token::FOR},
    {"goto", Token::GOTO},
    {"if", Token::IF},
    //{ "inline", Token::INLINE },
    {"int", Token::INT},
    {"long", Token::LONG},
    {"signed", Token::SIGNED},
    {"unsigned", Token::UNSIGNED},
    //{ "register", Token::REGISTER },
    {"restrict", Token::RESTRICT},
    {"return", Token::RETURN},
    {"short", Token::SHORT},
    {"sizeof", Token::SIZEOF},
    //{ "static", Token::STATIC },
    {"struct", Token::STRUCT},
    {"switch", Token::SWITCH},
    //{ "typedef", Token::TYPEDEF },
    {"union", Token::UNION},
    {"void", Token::VOID},
    {"volatile", Token::VOLATILE},
    {"while", Token::WHILE},
    //{ "_Alignas", Token::ALIGNAS },
    // { "_Alignof", Token::ALIGNOF },
    {"_Atomic", Token::ATOMIC},
    // { "__attribute__", Token::ATTRIBUTE },
    {"_Bool", Token::BOOL},
    {"_Complex", Token::COMPLEX},
    //{ "_Generic", Token::GENERIC },
    //{ "_Imaginary", Token::IMAGINARY },
    // { "_Noreturn", Token::NORETURN },
    //{ "_Static_assert", Token::STATIC_ASSERT },
    //{ "_Thread_local", Token::THREAD },
};

const std::unordered_map<int, const char *> Token::TagLexemeMap_{
    {'(', "("},
    {')', ")"},
    {'[', "["},
    {']', "]"},
    {':', ":"},
    {',', ","},
    {';', ";"},
    {'+', "+"},
    {'-', "-"},
    {'*', "*"},
    {'/', "/"},
    {'|', "|"},
    {'&', "&"},
    {'<', "<"},
    {'>', ">"},
    {'=', "="},
    {'.', "."},
    {'%', "%"},
    {'{', "{"},
    {'}', "}"},
    {'^', "^"},
    {'~', "~"},
    {'!', "!"},
    {'?', "?"},
    {'#', "#"},
    {Token::DSHARP, "##"},
    {Token::PTR, "->"},
    {Token::INC, "++"},
    {Token::DEC, "--"},
    {Token::LEFT, "<<"},
    {Token::RIGHT, ">>"},
    {Token::LE, "<="},
    {Token::GE, ">="},
    {Token::EQ, "=="},
    {Token::NE, "!="},
    {Token::LOGICAL_AND, "&&"},
    {Token::LOGICAL_OR, "||"},
    {Token::MUL_ASSIGN, "*="},
    {Token::DIV_ASSIGN, "/="},
    {Token::MOD_ASSIGN, "%="},
    {Token::ADD_ASSIGN, "+="},
    {Token::SUB_ASSIGN, "-="},
    {Token::LEFT_ASSIGN, "<<="},
    {Token::RIGHT_ASSIGN, ">>="},
    {Token::AND_ASSIGN, "&="},
    {Token::XOR_ASSIGN, "^="},
    {Token::OR_ASSIGN, "|="},
    {Token::ELLIPSIS, "..."},

    //{ Token::AUTO, "auto" },
    {Token::BREAK, "break"},
    {Token::CASE, "case"},
    {Token::CHAR, "char"},
    {Token::CONST, "const"},
    {Token::CONTINUE, "continue"},
    {Token::DEFAULT, "default"},
    {Token::DO, "do"},
    {Token::DOUBLE, "double"},
    {Token::ELSE, "else"},
    {Token::ENUM, "enum"},
    //{ Token::EXTERN, "extern" },
    {Token::FLOAT, "float"},
    {Token::FOR, "for"},
    {Token::GOTO, "goto"},
    {Token::IF, "if"},
    //{ Token::INLINE, "inline" },
    {Token::INT, "int"},
    {Token::LONG, "long"},
    {Token::SIGNED, "signed"},
    {Token::UNSIGNED, "unsigned"},
    //{ Token::REGISTER, "register" },
    {Token::RESTRICT, "restrict"},
    {Token::RETURN, "return"},
    {Token::SHORT, "short"},
    {Token::SIZEOF, "sizeof"},
    //{ Token::STATIC, "static" },
    {Token::STRUCT, "struct"},
    {Token::SWITCH, "switch"},
    //{ Token::TYPEDEF, "typedef" },
    {Token::UNION, "union"},
    {Token::VOID, "void"},
    {Token::VOLATILE, "volatile"},
    {Token::WHILE, "while"},
    //{ Token::ALIGNAS, "_Alignas" },
    //{ Token::ALIGNOF, "_Alignof" },
    //{ Token::ATOMIC, "_Atomic" },
    //{ Token::ATTRIBUTE, "__attribute__" },
    //{ Token::BOOL, "_Bool" },
    //{ Token::COMPLEX, "_Complex" },
    //{ Token::GENERIC, "_Generic" },
    //{ Token::IMAGINARY, "_Imaginary" },
    //{ Token::NORETURN, "_Noreturn" },
    //{ Token::STATIC_ASSERT, "_Static_assert" },
    //{ Token::THREAD, "_Thread_local" },

    {Token::END, "(eof)"},
    {Token::IDENTIFIER, "(identifier)"},
    //{ Token::CONSTANT, "(constant)" },
    {Token::LITERAL, "(string literal)"},
};

string Token::getTagLexe(int tag)
{
    auto res = TagLexemeMap_.find(tag);
    if (res != TagLexemeMap_.end())
        return res->second;
    return "";
}
int Token::isKeyWord(const string &val)
{
    auto res = kwTypeMap_.find(val);
    if (res != kwTypeMap_.end())
        return res->second;
    return Token::NOKEYWORD;
}