#ifndef PDERIVATIVE_H
#define PDERIVATIVE_H

#include "../project.h"
#include "network.h"

bool propogate_error(network *w, NODES_LENGTH parameter_length, NODES_LENGTH *parameters);

bool back_propogate(network *w, NODES_LENGTH parameter_length, NODES_LENGTH *parameters, node *curr, tensor *derv);

#endif