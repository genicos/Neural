#include "pderivative.h"
#include <stdio.h>


//derv is derivative of error with respect to parent
bool node_propogate(network *w, NODES_LENGTH parameters_length, NODES_LENGTH *parameters, node *curr, node *parent, tensor *derv){
  
  for(NODES_LENGTH i = 0; i < parameters_length; i++){ //Checking if parent is a parameter
    if(parent == w->nodes[parameters[i]]){             //
      tensor_add(w->derivatives[parameters[i]], w->derivatives[parameters[i]], derv); //Adding to derivative
      tensor_delete(derv);
      return true;
    }
  }
    
  return back_propogate(w, parameters_length, parameters, parent, derv);
}


//derv is partial derivative of error with respect to curr
bool back_propogate(network *w, NODES_LENGTH parameter_length, NODES_LENGTH *parameters, node *curr, tensor *derv){
  
  node *parent_1 = w->nodes[curr->parent_1];
  node *parent_2 = w->nodes[curr->parent_2];
  
  if(parent_1 != curr){ //Checking if parent 1 exists
    
    tensor *given_derv = tensor_cartesian_product(curr->t, parent_1->t);
    if(!given_derv){
      tensor_delete(derv);
      return false;
    }
    
    //calculating partial derivative
    tensor_function_table[curr->function]->f_d_1(given_derv, parent_1->t, parent_2->t); 
    
    tensor *next_derv = tensor_chain_rule(derv, given_derv);
    tensor_delete(given_derv);
    if(!next_derv){
      tensor_delete(derv);
      return false;
    }
    
    if(!node_propogate(w, parameter_length, parameters, curr, parent_1, next_derv)){
      tensor_delete(next_derv);
      return false;
    } 
  }

  if(parent_2 != curr){
    
    tensor *given_derv = tensor_cartesian_product(curr->t, parent_2->t);
    if(!given_derv){
      tensor_delete(derv);
      return false;
    }
    
    //calculating partial derivative
    tensor_function_table[curr->function]->f_d_2(given_derv, parent_1->t, parent_2->t); 
    
    tensor *next_derv = tensor_chain_rule(derv, given_derv);
    tensor_delete(given_derv);
    if(!next_derv){
      tensor_delete(derv);
      return false;
    }
    
    if(!node_propogate(w, parameter_length, parameters, curr, parent_2, next_derv)){
      tensor_delete(next_derv);
      return false;
    }
  }
  
  tensor_delete(derv);
  return true;
}


bool propogate_error(network *w, NODES_LENGTH parameters_length, NODES_LENGTH *parameters){
  
  if(!w || !parameters){
    return false;
  }

  node *error;  
  if(w->error >= w->nodes_length || !(error = w->nodes[w->error])){ //Ensuring that error node exists
    return false;
  }
  

  for(NODES_LENGTH i = 0; i < parameters_length; i++){  //Clearing derivatives and replacing them with zero tensors
    tensor_delete( w->derivatives[ parameters[i] ] );
    //Creating empty matrix
    FORM_ELEMENT form[2] = {error->t->data_length, w->nodes[ parameters[i] ]->t->data_length}; 
    if( !(w->derivatives[ parameters[i] ] = tensor_zero(2, form)) ){
      return false;
    }
  }
  
  tensor *derv = tensor_identity(error->t->data_length); //Derivative of error with respect to itself
  
  return back_propogate(w, parameters_length, parameters, error, derv);
}
