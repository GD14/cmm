#ifndef _RONG_SCOPE_H
#define _RONG_SCOPE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <shared_ptr>

namespace Rong
{
//Identifier node
class Identifier;
class Token;

enum ScopeType
{
    S_FILE,
    S_PROTO,
    S_BLOCK,
    S_FUNC,
};
class Scope
{
    typedef std::vector<std::shared_ptr<Identifier>> TagList;
    typedef std::map<std::string, std::shared_ptr<Identifier>> IdentMap;

  public:
    explicit Scope(std::shared_ptr<Scope> &parent_, enum ScopeType type_)
        : parent(parent_), type(type_) {}

    ~Scope() {}

    // get/set 父scope
    std::shared_ptr<Scope> getParent() { return parent; }
    void setParent(Std::shared_ptr<Scope> &parent_) { parent = parent_; }

    enum ScopeType getType() const { return type; }

    //插入
    void insert(std::shared_ptr<Identifier>& ident )
    //插入
    void insert(const std::string&name,std::shared_ptr<Identifier>& ident )

    //查找
    std::shared_ptr<Identifier> find(std::shared_ptr<Token>);
    //查找
    std::shared_ptr<Identifier> find(const string& name);

    Std::shared_ptr<Scope> parent;
    enum ScopeType type;
    //符号表
    IdentMap identMap;
};
} // namespace Rong
#endif