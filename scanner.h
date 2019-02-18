#ifndef _RONG_SCANNER_H_
#define _RONG_SCANNER_
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "token.h"
namespace Rong
{
class scanner
{
  public:
    scanner(std::string filename)
        : filenamePtr(std::make_shared<std::string>(filename)),
          row(0),
          pos(0),
          loc(filenamePtr,0,0)
    {
       fin.open(filename);
       if(fin.fail()){
           std::cerr<<"can not open input file "<<filename<<std::endl;
           exit(-1);
       } 
    }

    //扫描

    void scan(); 
    //扫描一个token
    std::shared_ptr<token> scanToken();

    //创建一个token
    std::shared_ptr<token> make_token(int tag);
    //跳过空白
    void  skipBlank();
    //扫描一个identity
    std::shared_ptr<token> skipIdentifier();

    //扫描一个punctuator
    std::shared_ptr<token> skipPunctuator();

    //扫描一个number 
    std::shared_ptr<token> skipNumber();

    //扫描一个字符串
    std::shared_ptr<token> skipLiteral();
  
    //扫描一个字符
    std::shared_ptr<token> skipCharacter();
   
    //扫描注释
    void skipComment();

    void Mark();
    char Get();
    char Peek();
    bool Unget();
    bool Try(char);
    bool Test(char);
  //private:
    //文件名
    std::shared_ptr<std::string> filenamePtr;
    //行号
    size_t row;
    //列号
    size_t pos;
    //行缓存
    std::string linebuff;
    //行列表
    std::vector<std::string> lines;
    //地址标记
    source_location loc;
    //输入流
    std::ifstream fin;
};
} // namespace Rong

#endif