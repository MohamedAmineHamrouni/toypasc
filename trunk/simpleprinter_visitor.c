#include <stdlib.h>
#include <stdio.h>
#include "base.h"
#include "simpleprinter_visitor.h"

Visitor *
simpleprinter_new()
{
    Visitor *sp_visitor = (Visitor *) malloc (sizeof(Visitor));

    sp_visitor->visit_program = &simpleprinter_visit;
    sp_visitor->visit_programdecl = &simpleprinter_visit;
    sp_visitor->visit_vardecl_list = &simpleprinter_visit;
    sp_visitor->visit_vardecl = &simpleprinter_visit;
    sp_visitor->visit_identifier_list = &simpleprinter_visit;
    sp_visitor->visit_procfunc_list = &simpleprinter_visit;
    sp_visitor->visit_procedure = &simpleprinter_visit;
    sp_visitor->visit_function = &simpleprinter_visit;
    sp_visitor->visit_param_list = &simpleprinter_visit;
    sp_visitor->visit_parameter = &simpleprinter_visit;
    sp_visitor->visit_statement_list = &simpleprinter_visit;
    sp_visitor->visit_print_stmt = &simpleprinter_visit;
    sp_visitor->visit_assignment_stmt = &simpleprinter_visit;
    sp_visitor->visit_if_stmt = &simpleprinter_visit;
    sp_visitor->visit_while_stmt = &simpleprinter_visit;
    sp_visitor->visit_for_stmt = &simpleprinter_visit;
    sp_visitor->visit_rel_expr = &simpleprinter_visit;
    sp_visitor->visit_add_expr = &simpleprinter_visit;
    sp_visitor->visit_mul_expr = &simpleprinter_visit;
    sp_visitor->visit_notfactor = &simpleprinter_visit;
    sp_visitor->visit_call = &simpleprinter_visit;
    sp_visitor->visit_callparam_list = &simpleprinter_visit;
    sp_visitor->visit_identifier = &simpleprinter_visit;
    sp_visitor->visit_literal = &simpleprinter_visit;
    sp_visitor->close_group = NULL;
}

void
simpleprinter_visit(struct AstNode *self)
{
    int i;
    struct AstNode *temp;

    if (self == NULL)
        return;

    printf("(AstNode) %x : %s\n", self, self->name);
    printf("kind: %d\n", self->kind);
    printf("type: %d\n", self->type);
    printf("value: ");
    value_print(&self->value, self->type);
    printf("\nlinenum: %d\n", self->linenum);
    if (self->symbol != NULL)
        printf("symbol: %x (\"%s\")\n", self->symbol, self->symbol->name);

    printf("Parent: (AstNode) %x\n", self->parent);

    if (self->children != NULL) {
        printf("Children\n");
        for (temp = self->children; temp != NULL; temp = temp->sibling) {
            printf("\t(AstNode) %x", temp);
            if (temp->name != NULL)
                printf(" : %s", temp->name);
            printf("\n");
        }
    }
    printf("\n");

    simpleprinter_visit(self->children);
    simpleprinter_visit(self->sibling);
}
