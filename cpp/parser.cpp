#include "parser.h"


void str2lower(std::string &s)
{
    transform(s.begin(), s.end(), s.begin(),
            [](char c){return tolower(c);}); // compile with -std=c++11
}

std::map<std::string, double> get_vars_as_map(std::string &fin_name)
{
    std::ifstream fin(fin_name.c_str());
    if (!fin) 
    {
        std::cerr << "\nError: cannot open " << fin_name << std::endl;
        exit(-1);
    }

    size_t var_num;
    std::string var_ident;
    fin >> var_num >> var_ident;
    
    std::map<std::string, double> vars;
    double tmp_val;
    std::string tmp_str, k;
    for(int i = 0; i < var_num; ++i)
    {
        fin >> tmp_val >> tmp_str;
        str2lower(tmp_str);
        vars[tmp_str] = tmp_val;
    }
    fin.close();

    return vars;
}

std::vector<double> get_vars_as_vec(std::string &fin_name)
{
    std::map<std::string, double> vars;
    std::vector<double> vals;
    vars = get_vars_as_map(fin_name);

    for(std::map<std::string, double>::iterator it = vars.begin();
            it != vars.end(); ++it)
    {
        vals.push_back(it->second);
    }

    return vals;
}

void debug_print_map(std::map<std::string, double> &vars)
{
    for(std::map<std::string, double>::iterator it = vars.begin();
            it != vars.end(); ++it)
        std::cout << std::setprecision(16) << it->first 
            << " : " << it->second << std::endl;
}

void debug_print_vec(std::vector<double> &vars)
{
    for(std::vector<double>::iterator it = vars.begin();
            it != vars.end(); ++it)
        std::cout << *it << std::endl;
}

void print_usage(int argc, char *argv[])
{
    std::cout << "Usage: " << argv[0] << " PARAMETERS (9)\n";
    std::cout << "\n";
    std::cout << "  Mandatory parameters:" << "latfile idx_bpms idx_xcors idx_ycors\n";
    std::cout << "                       " << "ref_x0 ref_y0 ref_flag filein fileout\n";
    std::cout << "  Parameters meanings:" << "\n";
    std::cout << "    " << "latfile : " << "lattice file name\n";
    std::cout << "    " << "idx_bpms: " << "indices array of BPMs\n";
    std::cout << "    " << "idx_xcor: " << "indices array of correctors in x-axis\n";
    std::cout << "    " << "idx_ycor: " << "indices array of correctors in y-axis\n";
    std::cout << "    " << "ref_x0  : " << "double array of reference orbit in x,\n";
    std::cout << "    " << "          " << "size should be equal to idx_bpms\n";
    std::cout << "    " << "ref_y0  : " << "double array of reference orbit in y,\n";
    std::cout << "    " << "          " << "size should be equal to idx_bpms\n";
    std::cout << "    " << "ref_flag: " << "string flag for objective function:\n";
    std::cout << "    " << "          " << "'x' : sum of (x-x0)^2;\n";
    std::cout << "    " << "          " << "'y' : sum of (y-y0)^2;\n";
    std::cout << "    " << "          " << "'xy': sum of (x-x0)^2 and (y-y0)^2;\n";
    std::cout << "    " << "filein  : " << "parameters input file for DAKOTA\n";
    std::cout << "    " << "fileout : " << "parameters output file for DAKOTA\n";
}
