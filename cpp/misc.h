/*************************************************************************\

 Header file to support user-defined executable, to serve as
 analysis driver of dakota optimization procedure.

\author Tong Zhang <zhangt@frib.msu.edu>
\since 2016-10-14 05:12:01 PM EDT

\*************************************************************************/

#ifndef MISC_H_
#define MISC_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "flame/config.h"
#include "flame/moment.h"

//!< type definitions
typedef std::vector<double> dvec;

//!< functions just for debug

/** \brief print out the basic information that could be got from machine state.
 *
 * @param s point of MomentState
 */
void debug_print_state(MomentState *s);

/** \brief print out all the configuration of lattice file,
 * i.e. lattice configurations
 *
 * @param conf reference to the Config point
 */
void debug_print_lconf(Config &conf);

/** \brief print out the configuration of an element
 *
 * @param e reference to ElementVoid point
 */
void debug_print_econf(ElementVoid &e);

/** \brief print out machine configuration
 *
 * @param m reference to Machine point
 */
void debug_print_mconf(Machine &m);

/** \brief iter print out a double vector
 *
 * @param x double vector
 */
void debug_print_dvec(dvec *x);

/** \brief test set_observer(),
 * affect the Observer::view() behavior when Machine::propagate() is issued.
 *
 * @param m reference to Machine
 * @param b integer vector of selected BPM indices
 * @param x double vector to store results, x envelope
 * @param y double vector to store results, y envelope
 */
void set_observer(Machine &m, std::vector<int> &b, dvec *x, dvec *y);

/** \brief user-defined struct to generate observer
 * to feed the requirement of Observer::view()
 */
struct ObserverFactory
{
    virtual ~ObserverFactory() {}
    virtual Observer *observe(Machine &m, ElementVoid *e) = 0;
};

struct MyObserver : public Observer
{
    MyObserver(dvec *x_array, dvec *y_array) : x_array(x_array), y_array(y_array) {}
    virtual ~MyObserver() {}

    // vector to store view-of-interest values
    dvec *x_array, *y_array;
    virtual void view(const ElementVoid *, const StateBase *);

    struct Factory : public ObserverFactory
    {
        dvec *x_array, *y_array;
        Factory(dvec *x_array, dvec *y_array) : x_array(x_array), y_array(y_array) {}
        virtual ~Factory() {}
        virtual Observer *observe(Machine &, ElementVoid *);
    };
};

/** \brief objective function definition
 *
 * @param x double vector contains BPM feedback data in x or horizontan direction
 * @param y double vector contains BPM feedback data in y or vertical direction
 * @param x0 double vector contains reference readings in x or horizontan direction
 * @param y0 double vector contains reference readings in y or vertical direction
 * @param type return type of values, "xy" return sum of dx^2 and dy^2, "x" return sum of dx^2,
 *             "y" return sum of dy^2, which dx is x-x0 and dy is y-y0
 * @return interested statistical results from input vector
 */
double obj_func(dvec *x, dvec *y, dvec &x0, dvec &y0, std::string type="xy");

/** \brief update machine
 *
 * @param m Machine to be updated
 * @param i element index
 * @param k configuration field name
 * @param v new value to be configured
 */
void update_machine(Machine &m, int i, std::string k, double v);

/** \brief write result of interest to file
 *
 * @param s filename string
 * @param v result of interest, one double variable
 */
void write_output(std::string &s, double v);

/** \brief convert string into vector
 *
 * @param s string
 * @return vector of int
 */
std::vector<int> str2intvec(std::string s);

/** \brief convert string into vector
 *
 * @param s string
 * @return vector of double
 */
std::vector<double> str2dblvec(std::string s);

// template here is not working, I don't know why.
template <typename T>
std::vector<T> str2vec(std::string s);

/** \brief get all element indices from machine
 *
 * @param m reference to Machine point
 * @return integer vector of element indices
 */
std::vector<int> get_all_elem(Machine &m);

#endif // MISC_H_
