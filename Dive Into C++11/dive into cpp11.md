### Stability & Compatibility Garuanteed
    
  - reserved macros from __C99__:
     * __STDC_HOSTED__
     * __STDC__
     * __STDC_VERSION__
     * __STDC_ISO_10646__

  - __func__

     * return the function name (string)
     * there some other greats akin the great like :
        __LINE__ , __FILE__

  - _Pragma
    
     * the same func with #pragma

  - __VA_ARGS__

  - newly-added integer *long long*   

  - greate : _cplusplus
      make it possible to be included both by .c or .cpp

  - assert() && static_assert()

  - extern template declaration

### Captalization on General Codes  

   - *Delegate Constructor*:
      
      * using try 
      
      ------------------------
         constructor() try : *delegate constructor* {
            // normal initilization
         }
         catch() {
            // handle the *exception*
         }

   - use *explicit* to avoid default type converting
   
   - *initializer_list* 

      * Faciliate the initialization work 
      * Prohibiate implicit type convertion
               
                int b = {1.2};                 // Valid
                unsigned int * b = new int(-1) // Valid
                int a = {1.2} ;                // Invalid
                unsigned int * a = new int(-1) // Invalid    

      * example :
         * constructor(std::initializer_list< type > li);
         * operator[] (std::initializer_list< type > li);
         * etc..

   - *POD* (trivial && standard layout)
      * *trivial* 
      * *standard Layout* :

         - [1]. the access permisssion of non-static members hold same.
         - [2]. non-static objects ought not to appear in both derive && base classes
                  if multi-herited, there are no non-static members in meanwhile both base classes.
         - [3]. the very first member of a derive class cannot be it's base cass.
         - [4]. no virtual members.
         - [5]. all the non-static members is the standard-layout type, so as the base classes.
      * *Adantage*  :

         - It is safe to make use of memset() & memcpy() to initialize and to assign a value typed POD by each bytes.
         - Can provide high compatibility with the C memory layout.  
         - Safety & vaildility of the static initialization guaranteed, which can improve the behaviour of the progrmme.

   - *Modification for union*      
   - *literal override* :

      * we can declare such a operator ""*literal*(const char* *literal*, std::size_t *n*) to meet our 
            desire to make some type convertion more agreeable. 
   - *inline namespace* 

      * while used, oper can specify some template vision in some namespace from it's father namespace.
      * It can make the interface between different lib visions more compatible.
   
   - *ADL*(Argument-dependent look up)

      * Not recommonded
   
   - *Template alias*

            // 1.
            typedef std::unordered_map<std::vector<std::string>, cv::Mat> UmVstrMat; // Valid
            using UmVstrMat = std::unordered_map<std::vector<std::string>, cv::Mat>; // Valid
            
            UmVstrMat convexed_matUnion;
            // 2.
            template<typename T> using UmVtMat<T> = std::unordered_map<std::vector<T>, cv::Mat> // Also valid
            UmVtMat<std::string> convexed_matUnion;
   
   - Normalize *SFINAE*

            // like template
            template <typename T>
            void value(typename T::value_type t;) { }
            // it is easy to type like this
            value<int>();              // Invalid, no type as int::value_type;
            // By using SFINEA , we can do the following things to avoid 
            template <typename T>
            void value() {};           // override the value<T>();
            value<int>();              // Valid, the second edition;
            value<std::vector<int> >   // Valid, the first edition;

### Simplified Interface 

   - modification on *Right angle brackles usage deducement*

   - *auto* && *decltype*

      + decltype([expression][identifier]) 
      + realize *return type deducement* by combinint auto with decltype like :
                  
                  template<class _FwdIt, class OutIt>
                     auto transfrom(_FwdIt F, _FwdIt L, OutIt X) ->decltype(Val_type(X))
### Persuing Better Type Safety
   
   - enum class 
   - constexpr and the meta-programming
   - template arguement pack and unpack

      + expand argue list with *var_list*, *var_start*, *var_arg*, and *var_end* or *__VA_ARGS__* while in great
      + reload *template< typeame...args>* with *template< typename H, typename...last>* and *template< typename L>* or
         template<>, *template<*specified type value*>* to expand the extendible template parameters
      + using *sizeof...()* to acquire length of the argue list
      + template parameter package used as template argue

                  template<typename I, template<typename> class...B> Constructor {};
                  template<typename I, template<typename> class A, template<typename> class...B> Constructor
                  {
                     A<I> cs;
                     Constructor<I, B...> cs2;
                  }

                  template<typename...T> Herit {};
                  template<typename T1, typename...T> Herit : public Herit<T...> {
                     T1 a;
                     Herit(T1 a, T...b) :
                        a(a), Herit<T...>(b...) {};
                  }

         * multi-parameter package and the template class with parameter package used as template parameter 

                  template<class A, class B> container {}
                  template<template<typename...> class A, typename...pk1,
                           template<typename...> class B, typename...pk2>
                  container {
                     container<A<pk1...>, B<pk2...>> contains;
                  }

   - atomic and the *Concurrency Programming*
      
      * *std::atomic< T >*
      * *spin lock*
         test_and_set(), clear()
   
   - memory model and memory order

      - problems potantially occur due to the command reorder
      - memory model
         +  [1] *sequencial consistance*  
            * *strong order* 
            * *weak order*
         +  [2] *TLS*(Thread Local Storage)
      - capitalize std::memory_order_* on atomic var to boost the effciency
   - use *quick_exit* && *at_quick_exit* for normal termination in thread

      -  in single-thread progmme
         + terminate(), abort() && exit()
            * exit() && atexit()
            * terminate()
            * abort()
   
### Turns in thought

   - nullptr && nullptr_t

      + nullptr_t && (void *)
      + nullptr && (voif *)0

   - default && delete

      - default func
      - in class :
            - delete && operator new, etc.
            - delete && <explicit>
            - delete && ~*Destructor*()
      - delete && overrided func 
   
   - lambda

      - lambda && the functor 
      - inplace lambda :

         + may like this : []{statement}();
      - suppose the lambda has empty capture list, it is allowed to convert to the function pointer
      - mutable && const 
      - restriction on lambda capture list

### About alignment

   - Alignment
      + alignof() && alignas()
      +  alignas() describe the attribute of a type that 
          only the address id is the integer multiply of the aligned size 
          can the type be stored in.
      + the alignas() can be declared for type, array, and struct.etc .
      + aligned_storge && aligned_union 

         * by taking advantage of the STL templates,
               we can make certain that the alignment mode and the size of 
               a type is strictly fixed by inplacement new.

      + Applying *memory alignment* can improve the progrmme's behaviours,
            and by using *aligned_storge()* or *aligned_union* can ensure the 
            compatibility of the code bewteen different platforms or compilers.
      - General attributes
         cpp11 has the following general attribute :
            [[noreturn]]、[[carry_dependency]]、[final]、[override]、[default] and [delete]
         
      - Supportment for unicode 

         + *char_16t* && *char_32t*
         + locale, codecvt, facet,
     