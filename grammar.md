//支持结构体
支持函数
//支持指针
支持数组




1. program->declaration_list EOF
2. declaration_list -> declaration_list declaration | declaration
3. declaration -> var_declaration | function_declaration
4. var_declaration->type_specifier ID | type_specifier ID [NUM]
5. type_specifier ->INT | VOID
6. fun_declaration -> type_specifier ID( params) compound_stmt
7. params -> param_list | VOID 
8. param_list-> param_list,param |param
9. param-> type_specifier ID | type_specifier ID[]
10. compound_stmt-> {local_declaration statement_list}
11. local_declaration->local_declaration var_declaration |empty
12. statement_list -> statement_list statement |empty
13. statement-> expression_stmt | compound_stmt |selection_stmt|iteration_stmt|return_stmt
14. expression_stmt->expression;|;
15. selection_stmt-> IF (expression) statement |IF(expression) statement ELSE statment
16. iteration_stmt -> WHILE(expression) statement
17. return_stmt->RETURN | RETURN expression
18. expression -> var=expression | simple_expression
19. var-> ID|ID[expression]
20. simple_expression->additive_expression relop additive_expression | additive_expression
21. relop -> LE | LT |GT | GE |EQ |NE
22. additive_expression-> additive_expression addop term | term 
23. addop -> + | -
24. term -> term mulop factor |factor
25. mulpp-> * | /
26. factor-> (expression) |var |call | NUM
27. call-> ID(args)
28. args->arg_list |empty
29. arg_list-> arg_list ,expression |expression