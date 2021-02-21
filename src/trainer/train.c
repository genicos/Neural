#include "train.h"

bool train(network *w, double scale, double stochastic, INPUTS_COUNT sample_size, lx *x){
  if(!w || !x)
    return false;
  
  if(sample_size == 0 || scale == 0)
    return true;
  
  //Creating space to calculate gradients 
  tensor **parameter_gradient = (tensor **)calloc(w->parameters_length, sizeof(tensor *));
  if(!parameter_gradient)
    return false;
  
 
  FORM_ELEMENT scalar_form[1] = {1};
  tensor *scalar = tensor_create(1, scalar_form);
  if(!scalar){
    free(parameter_gradient);
    return false;
  }
  tensor_create_data(scalar);
   
  for(NODES_LENGTH i = 0; i < w->parameters_length; i++){
    parameter_gradient[i] = tensor_cartesian_product(scalar, w->nodes[w->parameters[i]]->t);
    if(!parameter_gradient[i])
      return false;
    
  }
  
  EXAMPLES_COUNT to_train = sample_size;
  
  for(EXAMPLES_COUNT i = 0; i < x->examples_count; i++){
     
    if( (((double)rand()) /RAND_MAX) < (to_train / (x->examples_count - i) )) { //Randomly selecting sample
      to_train--;
       
      for(NODES_LENGTH j = 0; j < x->inputs_count; j++){
        w->nodes[j]->t = lx_example_input(x, i, j);
      }
      
      w->nodes[w->truth]->t = lx_example_output(x, i);
      
      network_clean(w);
      node_solve(w, w->root);
      
      propogate_error(w);
      
      for(NODES_LENGTH j = 0; j < w->parameters_length; j++){
        tensor_add(
          parameter_gradient[j], 
          parameter_gradient[j],
          w->derivatives[w->parameters[j]]
        );
      }
      
    }
  }
  
  
  
  scalar->data[0] = 1.0/sample_size;
  
  for(NODES_LENGTH i = 0; i < w->parameters_length; i++){
    tensor_scale(
      parameter_gradient[i],
      parameter_gradient[i],
      scalar
    );
    
    tensor_perturb(parameter_gradient[i], scale, stochastic);
    
    tensor_add(
      w->nodes[w->parameters[i]]->t,
      w->nodes[w->parameters[i]]->t,
      parameter_gradient[i]
    );
  }
  
  
  return true;
}
