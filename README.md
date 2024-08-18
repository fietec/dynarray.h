# dynarray.h
A simple header-only c program for creating dynamic arrays of any specific type.

The header file consists of a singular macro which creates the data structure and corresponding functions for:
  - creating
  - pushing a value 
  - printing a reprensentation (customizable with function pointer for value printing)
  - freeing the allocated memory (customizable with function pointer for value freeing)
# How to use
``` c
  #include "dynarray.h" // include the header file

  DEFINE_DYNAMIC_ARRAY(Ints, int) // define the dats structure and its functions with a name (here 'Ints') and the type of the stored values (here <int>)

  int main(void)
  {
    Ints_t* ints = Ints_create(16); // create the dynamic array of type <Name>_t with a initial capacity of 16
    for (size_t i=0; i<18; ++i){
      Ints_push(ints, i); // push a value to the dynamic array
    }
    Ints_print(ints, NULL); // print a representation of the dynamic array with placeholders for the values
    Ints_print(ints, &print_my_type); // print a reprensentation of the dynamic array with a custom function printing the value

    Ints_free(ints, NULL); // free the memory allocated for the dynamic array and ignore the stored values
    Ints_free(ints, &free_my_type); // free the memory allocated for the dynamic array and use a custom function for freeing the memory of the stored values
    
    return 0; // heard that's a good idea..
  }
```
