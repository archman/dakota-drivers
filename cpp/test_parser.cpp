#include "parser.h"


int main(int argc, char **argv)
{
    std::string fname(argv[1]);
    std::map<std::string, double> vars;
    vars = get_vars_as_map(fname);
    debug_print_map(vars);

    std::vector<double> vals;
    vals = get_vars_as_vec(fname);
    debug_print_vec(vals);


    return 0;
}

