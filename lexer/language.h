type = [int|float|double|char]
type_extend = [*|[]]
identifier = [_a-zA-Z]+[_a-zA-Z0-9]*

//declaration
declare = [type]{1}[type_extend]{0,1}[space][identifier];
declare_init = [declare]{1}[=][type_check]
