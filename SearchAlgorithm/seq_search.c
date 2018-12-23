#include <stdio.h>

int sequence_search(int *array, size_t size, int target){
  if(NULL == array){
    return -1;
  }
  for(size_t i = 0; i < size; ++i){
    if(target == array[i]){
      return (int)i;
    }
  }
  return -1;
}


int main() {
  
  return 0;
}
