#ifndef PDERIVATIVE_H
#define PDERIVATIVE_H

#include "../project.h"
#include "network.h"

bool propogate_error(network *w);

bool back_propogate(network *w, node *curr, tensor *derv);

bool gradient_decent(network *w, double scale, double stochastic);

void randomize_parameters(network *w, double base, double scale);

#endif
