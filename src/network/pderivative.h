#ifndef PDERIVATIVE_H
#define PDERIVATIVE_H

#include "../project.h"
#include "network.h"

bool propogate_error(network *w, NODES_LENGTH parameter_length, NODES_LENGTH *parameters);

bool back_propogate(network *w, NODES_LENGTH parameter_length, NODES_LENGTH *parameters, node *curr, tensor *derv);

bool gradient_decent(network *w, double scale, double stochastic);

void randomize_parameters(network *w, NODES_LENGTH parameter_length, NODES_LENGTH *parameters, double base, double scale);

#endif
