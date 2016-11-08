#include "misc.h"
#include <boost/foreach.hpp>

void MyObserver::view(const ElementVoid *elem, const StateBase *state)
{
    /*
    bool is_bpm = (std::string(elem->type_name()) == std::string("bpm"));
    std::cout << "Observed element: " << elem->index << " | "
              << elem->name << " | "
              << elem->type_name() << " | "
              << is_bpm
              << "\n";
    std::cout << state->pos << std::endl;
    */
    const MomentState *m_state = dynamic_cast<const MomentState *>(state);
    double x_env = m_state->moment0_env[0];
    double y_env = m_state->moment0_env[2];
    /*
    std::cout << "x_env = " << x_env << std::endl;
    std::cout << "y_env = " << y_env << std::endl;
    */
    x_array->push_back(x_env);
    y_array->push_back(y_env);
}

Observer *MyObserver::Factory::observe(Machine &m, ElementVoid *e)
{
    return new MyObserver(x_array, y_array);
}

void debug_print_state(MomentState *s) {
    std::cout << "\n-------------- State Info (BEGIN) --------------" << std::endl;
    std::cout << "pos            : " << s->pos << std::endl;
    std::cout << "ref_phis       : " << s->ref.phis << std::endl;
    std::cout << "ref_IonZ       : " << s->ref.IonZ << std::endl;
    std::cout << "ref_IonQ       : " << s->ref.IonQ << std::endl;
    std::cout << "ref_IonEs      : " << s->ref.IonEs << std::endl;
    std::cout << "ref_IonW       : " << s->ref.IonW << std::endl;
    std::cout << "ref_gamma      : " << s->ref.gamma << std::endl;
    std::cout << "ref_beta       : " << s->ref.beta << std::endl;
    std::cout << "ref_bg         : " << s->ref.bg << std::endl;
    std::cout << "ref_SampleIonK : " << s->ref.SampleIonK << std::endl;
    std::cout << "ref_IonEk      : " << s->ref.IonEk << std::endl;
    std::cout << "--------------  State Info (END) ---------------\n" << std::endl;
}

void debug_print_lconf(Config &conf) {
//        std::ostream here_out(std::cout.rdbuf());
//        conf.show(here_out);
    std::filebuf fb;
    fb.open("parse_out.conf", std::ios::out);
    std::ostream here_out(&fb);
    std::cout << "\n-------------- Lattice Conf (BEGIN) --------------" << std::endl;
    conf.show(here_out);
    std::cout << "--------------  Lattice Conf (END) ---------------\n" << std::endl;
}

void debug_print_econf(ElementVoid &e) {
    std::cout << "\n-------------- Element Conf (BEGIN) --------------" << std::endl;
    /*
    std::cout << "Length       : " << e.length << std::endl;
    std::cout << "Name         : " << e.name << std::endl;
    std::cout << "Index        : " << e.index << std::endl;
    std::cout << "Type         : " << e.type_name() << std::endl;
    std::cout << "Observe flag : " << e.observer() << std::endl;
     */
    e.conf().show(std::cout, 2);
    std::cout << "--------------  Element Conf (END) ---------------\n" << std::endl;
}

void debug_print_mconf(Machine &m) {
    std::cout << "\n-------------- Machine Conf (BEGIN) --------------" << std::endl;
    std::cout << "Size     : " << m.size() << std::endl;
    std::cout << "Sim type : " << m.simtype() << std::endl;
    std::cout << "--------------  Machine Conf (END) ---------------\n" << std::endl;
}

void set_observer(ElementVoid *e, Machine& m, dvec *x_array, dvec *y_array)
{
    std::auto_ptr <ObserverFactory> ofact;
    ofact.reset(new MyObserver::Factory(x_array, y_array));

    BOOST_FOREACH(e, m)
    {
        if (std::string(e->type_name()) == "bpm") {
            assert(e->observer() == NULL);
            e->set_observer(ofact->observe(m, e));
        }
    }
}

void debug_print_dvec(dvec *x) {
    std::cout << x->size() << std::endl;

    for (std::vector<double>::iterator it = x->begin();
         it != x->end(); ++it)
        std::cout << *it << std::endl;
}

double obj_func(dvec *x, dvec *y, dvec &x0, dvec &y0, std::string type) {
    double s_dx2 = 0;
    double tmp_x;
    for (int i=0; i<x->size(); i++) {
        tmp_x = (*x)[i] - x0[i];
        s_dx2 += tmp_x * tmp_x;
    }
    if (type == "x") return s_dx2;
    
    double s_dy2 = 0;
    double tmp_y;
    for (int i=0; i<y->size(); i++) {
        tmp_y = (*y)[i] - y0[i];
        s_dy2 += tmp_y * tmp_y;
    }
    if (type == "y") {
        return s_dy2;
    } else {
        return s_dx2 + s_dy2;
    }
}

void update_machine(Machine &m, int i, std::string k, double v)
{
    Config newconf = m[i]->conf();
    newconf.set<double>(k, v);
    m.reconfigure(i, newconf);
}

void write_output(std::string &s, double v)
{
    std::ofstream fout(s.c_str());
    fout.precision(15); // 16 total digits
    fout.setf(std::ios::scientific);
    fout.setf(std::ios::right);
    fout << "                     " << v << " f\n";
}

std::vector<int> str2intvec(std::string s)
{
    std::istringstream istr(s);

    int tmp;
    std::vector<int> vec;

    while (istr >> tmp)
    {
        vec.push_back(tmp);
    }

    return vec;
}

std::vector<double> str2dblvec(std::string s)
{
    std::istringstream istr(s);

    double tmp;
    std::vector<double> vec;

    while (istr >> tmp)
    {
        vec.push_back(tmp);
    }

    return vec;
}

template <typename T>
std::vector<T> str2vec(std::string s)
{
    std::istringstream istr(s);

    T tmp;
    std::vector<T> vec;

    while (istr >> tmp)
    {
        vec.push_back(tmp);
    }

    return vec;
}
