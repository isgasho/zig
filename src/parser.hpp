#ifndef ZIG_PARSER_HPP
#define ZIG_PARSER_HPP

#include "list.hpp"
#include "buffer.hpp"
#include "tokenizer.hpp"

struct AstNode;

enum NodeType {
    NodeTypeRoot,
    NodeTypeFnDecl,
    NodeTypeParamDecl,
    NodeTypeType,
    NodeTypePointerType,
    NodeTypeBlock,
    NodeTypeStatement,
    NodeTypeExpressionStatement,
    NodeTypeReturnStatement,
    NodeTypeExpression,
    NodeTypeFnCall,
};

struct AstNodeRoot {
    ZigList<AstNode *> fn_decls;
};

struct AstNodeFnDecl {
    Buf name;
    ZigList<AstNode *> params;
    AstNode *return_type;
    AstNode *body;
};

struct AstNodeParamDecl {
    Buf name;
    AstNode *type;
};

enum AstNodeTypeType {
    AstNodeTypeTypePrimitive,
    AstNodeTypeTypePointer,
};

struct AstNodeType {
    AstNodeTypeType type;
    AstNode *child;
};

struct AstNodePointerType {
    AstNode *const_or_mut;
    AstNode *type;
};

struct AstNodeBlock {
    ZigList<AstNode *> expressions;
};

struct AstNodeExpression {
    AstNode *child;
};

struct AstNodeFnCall {
    Buf name;
    ZigList<AstNode *> params;
};

struct AstNode {
    enum NodeType type;
    AstNode *parent;
    union {
        AstNodeRoot root;
        AstNodeFnDecl fn_decl;
        AstNodeType type;
        AstNodeParamDecl param_decl;
        AstNodeBlock block;
        AstNodeExpression expression;
        AstNodeFnCall fn_call;
    } data;
};

__attribute__ ((format (printf, 2, 3)))
void ast_error(Token *token, const char *format, ...);

AstNode * ast_parse(Buf *buf, ZigList<Token> *tokens);

#endif
