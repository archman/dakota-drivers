#include <stdio.h>
#include <iostream>

#include "flame/config.h"
#include "flame/base.h"
#include "flame/moment.h"
#include "misc.h"
#include "parser.h"

// argv[1]: latfile, lattice file
// argv[2]: idx_bpms, indices of selected BPMs
// argv[3]: idx_xcor, indices of selected horizontal correctors
// argv[4]: idx_ycor, indices of selected vertival correctors
// argv[5]: ref_x0, double array, reference orbit in x, size should be equal to idx_bpms
// argv[6]: ref_y0, double array, reference orbit in y, size should be equal to idx_bpms
// argv[7]: ref_flag, string, could be "x" (sum of dx^2), "y" (sum of dy^2), "xy" (sum of dx^2 and dy^2)
// argv[8]: dakin, params.in
// argv[9]: dakout, results.out
int main(int argc, char *argv[])
{
    try {
        if(argc<10)
        {
            print_usage(argc, argv);
            return 10;
        }

        if(argv[1] == "--help" || argv[1] == "-h")
        {
            print_usage(argc, argv);
            return 10;
        }

        if(argc == 1)
        {
            print_usage(argc, argv);
            return 10;
        }

        // parse lattice file
        registerMoment();
        std::string latfile(argv[1]);
        std::auto_ptr<Config> conf;
        {
            GLPSParser parser;
            conf.reset(parser.parse_file(latfile.c_str()));
        }

        // debug_print_lconf(*conf);
        Machine mymachine(*conf);

        // setup monitors and correctors
        std::vector<int> idx_bpms;
        if(std::string(argv[2]) == "all") {
            idx_bpms = get_all_elem(mymachine);
        } else {
            idx_bpms = str2intvec(argv[2]);
        }

        std::vector<int> idx_xcors = str2intvec(argv[3]);
        std::vector<int> idx_ycors = str2intvec(argv[4]);

        // reference orbit
        std::vector<double> ref_x0 = str2dblvec(argv[5]);
        std::vector<double> ref_y0 = str2dblvec(argv[6]);

        //std::cout << ref_x0.size() << std::endl;
        //std::cout << idx_bpms.size() << std::endl;

        if ((ref_x0.size() != idx_bpms.size()) || ref_y0.size() != idx_bpms.size())
        {
            std::cout << "Reference orbit array must be the size of selected BPMs array." 
                      << std::endl;
            return 1;
        }

        std::string ref_flag = std::string(argv[7]);

        // parse dakota input
        std::string dakin(argv[8]);

        std::map<std::string, double> vars;
        vars = get_vars_as_map(dakin);
        // debug_print_map(vars);


        //std::vector<double> vars;
        //vars = get_vars_as_vec(dakin);

        // ElementVoid *e = mymachine.find("LS1_CA01:DCH_D1131");
        // std::cout << e->index << std::endl;
        // int e_idx_size = 1;
        // int e_idx[e_idx_size];
        // e_idx[0] = e->index;

        //!< before re-configure
        // debug_print_econf(*e);
        //
        //
        dvec *x_array = new dvec();
        dvec *y_array = new dvec();
        set_observer(mymachine, idx_bpms, x_array, y_array);
        
        typedef std::vector<int>::iterator ivecit;
        std::map<std::string, double>::iterator mit = vars.begin();
        for (ivecit it = idx_xcors.begin(); it != idx_xcors.end(); ++it)
        {
            // std::cout << "theta_x: " << *it << " " << mit->second << std::endl;
            update_machine(mymachine, *it, "theta_x", mit->second);
            ++mit;
        }
        for (ivecit it = idx_ycors.begin(); it != idx_ycors.end(); ++it)
        {
            // std::cout << "theta_y: " << *it << " " << mit->second << std::endl;
            update_machine(mymachine, *it, "theta_y", mit->second);
            ++mit;
        }


        //!< define a vector to store the data of interest from output
        //dvec *x_array = new dvec();
        //dvec *y_array = new dvec();

        //!< setup observers for data retrievement,
        //!< data should be stored into x_array
        // ElementVoid *e;
        //set_observer(mymachine, idx_bpms, x_array, y_array);

        //!> print out machine configuration (except lattice)
//        debug_print_mconf(mymachine);

        std::auto_ptr<StateBase> thestate(mymachine.allocState());

        mymachine.propagate(thestate.get());

        //! get data from thestate
        MomentState *m_state = dynamic_cast<MomentState*>(thestate.get());
        //!< print out information from state
//        debug_print_state(m_state);

        //!< print out the retrieved data
//        debug_print_dvec(x_array);

        double f = obj_func(x_array, y_array, ref_x0, ref_y0, ref_flag);
        std::string dakout(argv[9]);
        write_output(dakout, f);

        Machine::registeryCleanup();
        delete x_array, y_array;

        return 0;
    } catch(std::exception& e) {
        std::cerr<<"Error: "<<e.what()<<"\n";
        return 1;
    }
}
