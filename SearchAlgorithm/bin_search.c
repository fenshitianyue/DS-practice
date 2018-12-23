#include <stdio.h>

//ineration
int binary_search(int *array, size_t size, int target){
  if(NULL == array){
    return -1;
  }
  size_t low = 0, high = size;
  size_t mid = 0; 
  while(low <= high){
    mid = low + (high - low) / 2;
    if(target == array[mid]){
      return mid;
    } else if(target > array[mid]) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

//recursive
int binary_search_r(int* array, int target, size_t low, size_t high){
  if(NULL == array){
    return -1;
  }
  size_t mid = low + (high - low) / 2;
  if(target == array[mid]){
    return mid;
  } else if(target > array[mid]) {
    return binary_search_r(array, target, mid + 1, high);
  } else {
    return binary_search_r(array, target, low, mid - 1);
  }
}

//test
int main() {
  
  return 0;
}
