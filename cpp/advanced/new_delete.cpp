#include <iostream>
#include <string>
#include <cstring>

void f1() {
   // What happens when following code is executed? 
   class Dog {};


   Dog* pd = new Dog();

   // Step 1. operator new is called to allocate memory.
   // Step 2. dog's constructor is called to create dog.
   // Step 3. if step 2 throws an exception, call operator delete to free the memory allocated in step 1.

   delete pd;

   // Step 1. dog's destructor is called.
   // Step 2. operator delete is called to free the memory.

}

// This is how the operator new may look like if you re-implement it:
// new handler is a function invoked when operator new failed to allocate memory.
// set_new_handler() installs a new handler and returns current new handler.

/*
void* operator new(std::size_t size) { // throw(std::bad_alloc) {
   while (true) {
      void* pMem = malloc(size);   // Allocate memory
      if (pMem) {
         return pMem;              // Return the memory if successful
      }

      std::new_handler handler = std::set_new_handler(0);  // Get new handler
      std::set_new_handler(handler);

      if (handler) {
         (*handler)();            // Invoke new handler
      }
      else {
         throw std::bad_alloc();       // If new handler is null, throw exception
      }
   }
}
*/


// Member operator new and delete

class Dog {
public:
   static void* operator new(std::size_t size) { //throw(std::bad_alloc) {
      if (size == sizeof(Dog)) {
         //return customNewForDog(size);
         // or malloc
      }
      return ::operator new(size);
   }

   static void operator delete(void* pMemory) throw() {
      // customDeleteForDog();
      free(pMemory);
   }
};


/*
Why do we want to customize new/delete

1. Usage error detection:
   a. Memory leak detection/garbage collection. 
   b. Array index overrun/underrun.
2. Improve efficiency:
   a. Clustering related objects to reduce page fault.
   b. Fixed size allocation (good for application with many small objects).
   c. Align similar size objects to same places to reduce fragmentation.
3. Perform additional tasks:
   a. Fill the deallocated memory with 0's - security.
   b. Collect usage statistics.
*/


/* 
So the new-handler must do one of following things:
   1). Make more memory available.
   2). Install a different new-handler.
   3). Uninstall the new-handler (passing a null pointer).
   4). Throw an exception bad_alloc or its descendent.
   5). Terminate the program.
*/


/*****************************************************************************/


/*

overloading new and delete

1) there are two types of overloading 
   a. local (class)
   b. global
2) both new and delete are static members (no need to use static keyword)
3) there can be multiple overloaded new and delete functions
4) don't forget to override also the array version

*/


/*

new vs malloc

Feature	                               new / delete	                                 malloc / free
Memory allocated from	                Free Store  	                                 Heap
Returns	                               Fully typed pointer                            void*
On failure	                            Throws (never returns NULL)	                  Returns NULL
Required size	                         Calculated by compiler	                        Must be specified in bytes
Handling arrays	                      Has an explicit version	                     Requires manual calculations
Reallocating	                         Not handled intuitively	                     Simple (no copy constructor)
Call of reverse	                      Implementation defined	                        No
Low memory cases	                      Can add a new memory allocator	               Not handled by user code
Overridable	                            Yes	                                          No
Use of constructor / destructor	       Yes	                                          No


Free-store:

The free store is one of the two dynamic memory areas, allocated/freed by new/delete.
Object lifetime can be less than the time the storage is allocated; that is,
free store objects can have memory allocated without being immediately initialized,
and can be destroyed without the memory being immediately deallocated.
During the period when the storage is allocated but outside the object's lifetime,
the storage may be accessed and manipulated through a void* but none of the proto-object's
nonstatic members or member functions may be accessed, have their addresses taken, or be otherwise manipulated.

Heap:

The heap is the other dynamic memory area, allocated/freed by malloc/free and their variants.
Note that while the default global new and delete might be implemented in terms of malloc and free by a particular compiler,
the heap is not the same as free store and memory allocated in one area cannot be safely deallocated in the other.
Memory allocated from the heap can be used for objects of class type by placement-new construction and explicit destruction.
If so used, the notes about free store object lifetime apply similarly here.


Free Store is a pool of un-allocated heap memory given to a program that is used by the program for dynamic allocation during the execution of program.

*/


void* operator new(std::size_t size) {
   std::cout << "new called" << std::endl;
   void* ptr = std::malloc(size); // Allocate memory using malloc
   if (!ptr) {
      throw std::bad_alloc(); // Throw exception if allocation fails
   }
   else {
      std::cout << "new is done" << std::endl;
      return ptr;
   }
}

void* operator new[](std::size_t size) {
   std::cout << "new [] called" << std::endl;
   void* ptr = std::malloc(size); // Allocate memory using malloc
   if (!ptr) {
      throw std::bad_alloc(); // Throw exception if allocation fails
   }
   else {
      std::cout << "new [] is done" << std::endl;
      return ptr;
   }
}

void operator delete(void* ptr) noexcept {
   std::cout << "delete called" << std::endl;
   if (ptr) {
      // Call the destructor for the object being deleted
      // Free the memory block using free
      std::free(ptr);
      std::cout << "delete is done" << std::endl;
   }
}

void operator delete[](void* ptr) noexcept {
   std::cout << "delete [] called" << std::endl;
   if (ptr) {
      std::free(ptr);
      std::cout << "delete [] is done" << std::endl;
   }
}


class MyClass {
public:
   MyClass() {
      std::cout << "Default constructor called" << std::endl;
   }
   MyClass(int a, std::string b) : _a(a), _b(b) {
      std::cout << "Param constructor called" << std::endl;
   }
   ~MyClass() {
      std::cout << "Destructor called" << std::endl;
   }   
   int _a;
   std::string _b;
};

int main() {
   MyClass* obj = new MyClass(42, "hello");
   std::cout << obj->_a << std::endl;
   std::cout << obj->_b << std::endl;

   MyClass* arr = new MyClass[5];

   delete obj;
   delete [] arr;

   return 0;
}

