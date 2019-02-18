#include "scanner.h"
#include "token.h"
using namespace std;
using namespace Rong;

void scanner::scan()
{
    vector<shared_ptr<token>> vec;

    for (;;)
    {
        auto tk = scanToken();
        vec.emplace_back(tk);

        if (tk->tag == Token::END)
            break;
    }
    for (auto x : vec)
        if (x->tag != Token::END)
        {
            cout << (*filenamePtr) << ":" << x->loc.row << ":" << x->loc.pos << " " << x->val << endl;
            cout << lines[x->loc.row - 1] << endl;
        }
}

shared_ptr<token> scanner::scanToken()
{
    skipBlank();
    char c = Peek();
    //end
    if (c == EOF)
        return make_token(Token::END);
    //!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
    if (ispunct(c))
        return skipPunctuator();
    //identifier [a-zA-z_]([a-zA-z0-9_])*
    if (isalpha(c) || '_' == c)
        return skipIdentifier();
    //only 十进制数
    if (isdigit(c))
        return skipNumber();
}

shared_ptr<token> scanner::skipPunctuator()
{
    char ch = Get();
    Mark();
    switch (ch)
    {
    case '#':
        return make_token(Try('#') ? Token::DSHARP : ch);
    case ':':
        return make_token(ch);
    case '(':
    case ')':
    case '[':
    case ']':
    case '?':
    case ',':
    case '{':
    case '}':
    case '~':
    case ';':
        return make_token(ch);
    case '-':
        if (Try('>'))
            return make_token(Token::PTR);
        if (Try('-'))
            return make_token(Token::DEC);
        if (Try('='))
            return make_token(Token::SUB_ASSIGN);
        return make_token(ch);
    case '+':
        if (Try('+'))
            return make_token(Token::INC);
        if (Try('='))
            return make_token(Token::ADD_ASSIGN);
        return make_token(ch);
    case '<':
        if (Try('<'))
            return make_token(Try('=') ? Token::LEFT_ASSIGN : Token::LEFT);
        if (Try('='))
            return make_token(Token::LE);
        return make_token(ch);
    case '%':
        if (Try('='))
            return make_token(Token::MOD_ASSIGN);
        if (Try('>'))
            return make_token('}');
        return make_token(ch);
    case '>':
        if (Try('>'))
            return make_token(Try('=') ? Token::RIGHT_ASSIGN : Token::RIGHT);
        if (Try('='))
            return make_token(Token::GE);
        return make_token(ch);
    case '=':
        return make_token(Try('=') ? Token::EQ : ch);
    case '!':
        return make_token(Try('=') ? Token::NE : ch);
    case '&':
        if (Try('&'))
            return make_token(Token::LOGICAL_AND);
        if (Try('='))
            return make_token(Token::AND_ASSIGN);
        return make_token(ch);
    case '|':
        if (Try('|'))
            return make_token(Token::LOGICAL_OR);
        if (Try('='))
            return make_token(Token::OR_ASSIGN);
        return make_token(ch);
    case '*':
        return make_token(Try('=') ? Token::MUL_ASSIGN : ch);
    case '/':
        if (Test('*') || Test('/'))
        {
            skipComment();
            return scanToken();
        }
        return make_token(Try('=') ? Token::DIV_ASSIGN : ch);
    case '^':
        return make_token(Try('=') ? Token::XOR_ASSIGN : ch);
    case '.':
        /*if (isdigit(peek())) return SkipNumber();
         if (Try('.')) {
         if (Try('.')) return make_token(Token::ELLIPSIS);
                                                                  un();
                                                                  return make_token('.');
                                                          }*/
        return make_token(ch);
    case '\'':
        return skipCharacter();
    case '\"':
        return skipLiteral();
    }
}

shared_ptr<token> scanner::skipIdentifier()
{
    char ch = Get();
    Mark();
    while (isalnum(Peek()) || ('_' == Peek()))
        Get();
    return make_token(Token::IDENTIFIER);
}

shared_ptr<token> scanner::skipNumber()
{
    char ch = Get();
    Mark();
    int tag = Token::I_CONSTANT;
    while (isalnum(ch) || '.' == ch)
    {
        if ('.' == ch)
            tag = Token::F_CONSTANT;
        ch = Get();
    }
    Unget();
    return make_token(tag);
}

shared_ptr<token> scanner::skipCharacter()
{
    char ch = Get();
    while (ch != '\n' && ch != '\'' && ch != '\0')
    {
        if (ch == '\\')
            Get();
        ch = Get();
    }
    if ('\'' != ch)
    {
        cerr << "empty char!\n";
        exit(-1);
    }
    return make_token(Token::C_CONSTANT);
}

shared_ptr<token> scanner::skipLiteral()
{
    char ch = Get();
    while (ch != '\n' && ch != '\"' && ch != '\0')
    {
        if (ch == '\\')
            Get();
        ch = Get();
    }
    if (ch != '\"')
    {
        cerr << "error string!\n";
        exit(-1);
    }
    return make_token(Token::LITERAL);
}
void scanner::skipBlank()
{
    while (isspace(Peek()))
        Get();
}
void scanner::skipComment()
{
    if (Try('/'))
    {
        //行注释以EOF或\n结束
        while (EOF != Peek())
        {
            char ch = Get();
            if (ch == '\n')
                return;
        }
    }
    else if (Try('*'))
    {
        for (;;)
        {
            char ch = Get();
            if (ch == '*' && Try('/'))
                return;
            if (ch == EOF)
            {
                cerr << "unterminated block comment\n";
                exit(-1);
            }
        }
    }
}
shared_ptr<token> scanner::make_token(int tag)
{
    string val = "";
    if (loc.row > 0 && loc.pos > 0)
    {
        size_t i = loc.row - 1;
        size_t j = loc.pos - 1;
        while (i < row - 1)
        {
            val += lines[i][j++];
            if (j == lines[i].size())
                j = 0, i++;
        }
        while (j <= pos - 1)
            val += lines[i][j++];
    }
    return make_shared<token>(tag, val, loc);
}

void scanner::Mark()
{
    loc.row = row;
    loc.pos = pos;
}
char scanner::Get()
{
    if (pos == linebuff.size())
    {
        if (row < lines.size())
            linebuff = lines[row];
        else
        {
            getline(fin, linebuff);
            if (fin.fail())
                return EOF;
            linebuff += '\n';
            lines.emplace_back(linebuff);
        }
        ++row;
        pos = 0;
    }
    return linebuff[pos++];
}

char scanner::Peek()
{
    if (pos < linebuff.size())
        return linebuff[pos];
    if (row == lines.size())
        return fin.peek();
    return lines[row][0];
}

bool scanner::Unget()
{
    if (pos == 0)
    {
        if (row < 2)
            return false;
        --row;
        linebuff = lines[row - 1];
        pos = linebuff.size();
    }
    --pos;
    return true;
}
bool scanner::Try(char c)
{
    return Peek() == c ? Get(), true : false;
}
bool scanner::Test(char c)
{
    return Peek() == c;
}