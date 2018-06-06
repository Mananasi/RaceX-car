bool arraysEqual(bool arr1[], bool arr2[]) {
  int size1 = sizeof(arr1)/sizeof(bool);
  int size2 = sizeof(arr2)/sizeof(bool);
  if(size1 != size2) return false;

  int equalCount = 0;
  for(int i = 0; i < size1; i++) {
    if(arr1[i] == arr2[i]) equalCount++;
  }

  return equalCount == size1;
}

void copyArray(bool arrFrom[], bool* arrTo) {
  int arrSize = sizeof(arrTo) / sizeof(bool);

  for(int i = 0; i < arrSize; i++) {
    arrTo[i] = arrFrom[i];
  }
  
}

