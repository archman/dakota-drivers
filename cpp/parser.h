/*************************************************************************\
 Header file to provide functions to parse parameter file of dakota,
 used in external analysis drivers.

\author Tong Zhang <zhangt@frib.msu.edu>
\since 2016-10-16 05:05:06 PM EDT

\*************************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

/** \brief convert string s to be lower cased
 *
 * @param s string
 */
void str2lower(std::string &s);

/** \brief get N variables' values, N is defined by the first line,
 * which is of the format like "N variables"
 * 
 * @param s filename to read
 * @return a map, key: string, val: double
 */
std::map<std::string, double> get_vars_as_map(std::string &s);

/** \brief get N variables' values, N is defined by the first line,
 * which is of the format like "N variables"
 * 
 * @param s filename to read
 * @return a vector of values, ascend sorted by key
 */
std::vector<double> get_vars_as_vec(std::string &s);

/** \brief print out a map variable
 *
 * @param vars "string, double" map variable
 */
void debug_print_map(std::map<std::string, double> &vars);

/** \brief print out a vector variable
 *
 * @param vars double vector
 */
void debug_print_vec(std::vector<double> &vars);

/** \brief print usage
 *
 */
void print_usage(int argc, char *argv[]);

#endif // PARSER_H_
