#define MESSAGE_SIZE 256

typedef struct Info {
    char string[256];
    int type_id;
} Info;

typedef struct LabelNo {
    int num;
    struct LabelNo * next;
} LabelNo;

LabelNo * new_label_no(int num);
int push_label_no(int true);
int pop_label_no(int true);
void get_new_register(char * buffer);
void get_new_mem(char * buffer);
void get_new_param(char * buffer);
void reset_params();
void handle_assignment(Info * lhs, Info * source, Info * destination);
void handle_arithmetic_expression(Info * lhs, int op, Info * a, Info * b);
void handle_unary_minus_expression(Info * lhs, Info * expr);
void handle_relational_expression(Info * lhs, int op, Info * a, Info * b);
void handle_logical_expression(Info * lhs, int op, Info * a, Info * b);
void handle_arg(Info * arg, Info * expression);
void handle_unit_id(Info * identifier);
void handle_param(Info * lhs, Info * var_decl);
void handle_variable_declaration(Info * lhs, Info * identifier, int decl_type);
void handle_initialization(Info * var_decl, Info * value);
void handle_condition(int true);
void handle_condition_head(Info * cond_expr);
void handle_else();
void handle_number(Info * lhs, Info * num);
void handle_identifier_lexeme(Info * val, char * text);
void handle_identifier(Info * lhs, Info * identifier);

