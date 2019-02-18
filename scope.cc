#include "scope.h"

    //插入
    void scope::insert(std::shared_ptr<Identifier>& ident ){
        insert(ident->name(),ident);
    }
    //插入
    void scope::insert(const std::string&name,std::shared_ptr<Identifier>& ident ){

    }