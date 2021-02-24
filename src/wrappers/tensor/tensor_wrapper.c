#include "../../tensor/tensor.h"
#include "../../tensor/functions.h"
#include <string.h>

/*OPTIONS:

creating: -c <form length> <form>
  <form> is written as base ten integers seperated by non digits

*/

tensor *string_tensor_create( char *form_length, char *form);


int main(int argc, char **argv){
  
  
  for(int i = 0; i < argc; i++){
    if(argv[i][0] == ' '){
      if(argv[i][1] == 'c'){
        string_tensor_create( argv[i + 1], argv[i + 2]);
      }
     
    }
  }
  
  return 0;
}


tensor *string_tensor_create( char *form_length_str, char *form_str){
  
  FORM_LENGTH form_length = atoi(form_length_str);
  
  FORM_ELEMENT *form = (FORM_ELEMENT *)calloc(fl, sizeof(FORM_ELEMENT));
  
  bool in_number = false;
  FORM_LENGTH form_index = 0;
  
  for(char *i = form_str; i[0] != '\0'; i++){ //i passes through form_str
    
    if('0' <= i[0] && i[0] <= '9'){
      
      if(form_index == form_length){
        break;
      }
      
      if(!in_number){
        form[form_index] = atoi(i);
        form_index++;
        in_number = true;
      }
    
    }else{
      in_number = false;
    }
    
  }
  
  
  
  if(form_index < form_length){
    
    FORM_LENGTH given = form_index;
    
    for(; form_index < form_length; form_length++){
      form[form_index] = form[form_index % given];
    }
  }
  
  tensor *ans = tensor_create(form_length, form);
   
  return ans;
}
