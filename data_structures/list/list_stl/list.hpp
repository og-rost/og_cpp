#include <memory>

#ifndef LIST_H
#define LIST_H 1

#if __cplusplus >= 201103L
#include <initializer_list>
#endif

namespace std {
	namespace detail  {
		struct node_base {
			node_base* next;
			node_base* prev;
			static void swap(node_base&, node_base&);
			void  transfer(node_base* const, node_base* const);
			void  reverse();
			void  hook(node_base* const);
			void  unhook();
		};
	} // namespace detail


	/// An actual node in the%list.
	template<typename Tp>
	struct node : public detail::node_base {
		Tp data;
#if __cplusplus >= 201103L
		template<typename... _Args>
		node(_Args&&... __args) : detail::node_base(), data(std::forward<_Args>(__args)...) {}
#endif
	};
	
	template<typename Tp>
	struct my_iterator  {
		typedef my_iterator<Tp>                    Self;
		typedef node<Tp>                           Node;
		typedef ptrdiff_t                          difference_type;
		typedef std::bidirectional_iterator_tag    iterator_category;
		typedef Tp                                 value_type;
		typedef Tp*                                pointer;
		typedef Tp&                                reference;
		my_iterator() : curr() {}
		
		
		explicit my_iterator(detail::node_base* x) : curr(x) {}
		
		// Must downcast from node_base to node to get to data.
		reference  operator*() const
		{ return static_cast<Node*>(curr)->data; }
		
		pointer   operator->() const
		{ return std::__addressof(static_cast<Node*>(curr)->data); }
		
		Self&  operator++() {
			curr = curr->next;
			return *this;
		}
		
		Self  operator++(int) {
			Self tmp = *this;
			curr = curr->next;
			return tmp;
		}
		
		Self&  operator--() {
			curr = curr->prev;
			return *this;
		}
		
		Self operator--(int) {
			Self tmp = *this;
			curr = curr->prev;
			return tmp;
		}
		
		bool  operator==(const Self& x) const
		{ return curr == x.curr; }
		
		bool  operator!=(const Self& x) const
		{ return curr != x.curr; }
		
		// The only member points to the list element.
		detail::node_base* curr;
	};
	

	template<typename Tp>
	struct my_const_iterator  {
		typedef my_const_iterator<Tp>              Self;
		typedef const node<Tp>                     Node;
		typedef ptrdiff_t                          difference_type;
		typedef std::bidirectional_iterator_tag    iterator_category;
		typedef Tp                                 value_type;
		typedef const Tp*                          pointer;
		typedef const Tp&                          reference;
		my_const_iterator() : curr() {}
		
		
		explicit my_const_iterator(detail::node_base* x) : curr(x) {}
		
		// Must downcast from node_base to node to get to data.
		reference  operator*() const
		{ return static_cast<Node*>(curr)->data; }
		
		pointer   operator->() const
		{ return std::__addressof(static_cast<Node*>(curr)->data); }
		
		Self&  operator++() {
			curr = curr->next;
			return *this;
		}
		
		Self  operator++(int) {
			Self tmp = *this;
			curr = curr->next;
			return tmp;
		}
		
		Self&  operator--() {
			curr = curr->prev;
			return *this;
		}
		
		Self operator--(int) {
			Self tmp = *this;
			curr = curr->prev;
			return tmp;
		}
		
		bool  operator==(const Self& x) const
		{ return curr == x.curr; }
		
		bool  operator!=(const Self& x) const
		{ return curr != x.curr; }
		
		// The only member points to the list element.
		detail::node_base* curr;
	};
	
	
	template<typename Val>
	inline bool  operator==(const my_iterator<Val>& x,  const my_const_iterator<Val>& y)
	{ return x.curr == y.curr; }
	
	template<typename Val>
	inline bool  operator!=(const my_iterator<Val>& x,  const my_const_iterator<Val>& y)
	{ return x.curr != y.curr; }
	
	
	template<typename Tp, typename Alloc>
	class List_base  {
	protected:
		typedef typename Alloc::template rebind<node<Tp> >::other Node_alloc_type;
		typedef typename Alloc::template rebind<Tp>::other Tp_alloc_type;
		
		struct impl : public Node_alloc_type {
			detail::node_base M_node;
			impl() : Node_alloc_type(), M_node() {}
			
			impl(const Node_alloc_type& a) : Node_alloc_type(a), M_node() {}
#if __cplusplus >= 201103L
			impl(Node_alloc_type&& a) : Node_alloc_type(std::move(a)), M_node() {}
#endif
		};
		impl M_impl;
		
		node<Tp>*  get_node()
		{ return M_impl.Node_alloc_type::allocate(1); }
		
		void put_node(node<Tp>* p)
		{ M_impl.Node_alloc_type::deallocate(p, 1); }
	public:
		typedef Alloc allocator_type;

		Node_alloc_type&   get_Node_allocator()
		{ return *static_cast<Node_alloc_type*>(&M_impl); }
		
		const Node_alloc_type& 	get_Node_allocator() const
		{ return *static_cast<const Node_alloc_type*>(&M_impl); }
		
		Tp_alloc_type get_Tp_allocator() const
		{ return Tp_alloc_type(get_Node_allocator()); }
		
		allocator_type  get_allocator() const
		{ return allocator_type(get_Node_allocator()); }
		
		List_base() : M_impl() 
		{ init(); }
		
		List_base(const Node_alloc_type& a)  : M_impl(a)
		{ init(); }

#if __cplusplus >= 201103L
		List_base(List_base&& x) : M_impl(std::move(x.get_Node_allocator())) {
			init();
			detail::node_base::swap(M_impl.M_node, x.M_impl.M_node);
		}
#endif
		// This is what actually destroys the list.
		~List_base()
		{ M_clear(); }

		void M_clear();
		
		void  init() {
			this->M_impl.M_node.next = &this->M_impl.M_node;
			this->M_impl.M_node.prev = &this->M_impl.M_node;
		}
	};
	


	template<typename Tp, typename Alloc = std::allocator<Tp>>
	class list : protected List_base<Tp, Alloc> {
		// concept requirements
		typedef typename Alloc::value_type                 Alloc_value_type; 
		typedef List_base<Tp, Alloc>                       Base;
		typedef typename  Base::Tp_alloc_type		       Tp_alloc_type;
		typedef typename  Base::Node_alloc_type		       Node_alloc_type;
	public:
		typedef Tp                                         value_type;
		typedef typename Tp_alloc_type::pointer            pointer;
		typedef typename Tp_alloc_type::const_pointer      const_pointer;
		typedef typename Tp_alloc_type::reference          reference;
		typedef typename Tp_alloc_type::const_reference    const_reference;
		typedef my_iterator<Tp>                            iterator;
		typedef my_const_iterator<Tp>                      const_iterator;
		typedef std::reverse_iterator<const_iterator>      const_reverse_iterator;
		typedef std::reverse_iterator<iterator>            reverse_iterator;
		typedef size_t                                     size_type;
		typedef ptrdiff_t                                  difference_type;
		typedef Alloc                                      allocator_type;
	
	protected:
		// Note that pointers-to-_Node's can be ctor-converted to
		// iterator types.
		typedef node<Tp>							       Node;
		using Base::M_impl;
		using Base::put_node;
		using Base::get_node;
		using Base::get_Tp_allocator;
		using Base::get_Node_allocator;

      
       //@param  __args  An instance of user data.
       // Allocates space for a new node and constructs a copy of
       // @a __args in it.
       
#if __cplusplus < 201103L
		Node* M_create_node(const value_type& x)  {
			Node* p = this->get_node();
			try {
				get_Tp_allocator().construct  (std::__addressof(p->M_data), x);
			}
			catch(...)  {
				put_node(p);
				throw;
			}
			return p;
		}
#else
      template<typename... _Args>
	  Node* create_node(_Args&&... __args) {
		  Node* p = this->get_node();
		  try  {
			  get_Node_allocator().construct(p, std::forward<_Args>(__args)...);
		  }
		  catch(...) {
			  put_node(p);
			  throw;
		  }
		  return p;
	  }
#endif
	public:
		// construct/copy/destroy
		// (assign() and get_allocator() are also listed in this section)
		// Default constructor creates no elements.
		list() : Base() {}
		
		explicit  list(const allocator_type& a) : Base(Node_alloc_type(a)) {}
#if __cplusplus >= 201103L
				
		explicit  list(size_type n) : Base()
		{ default_initialize(n); }
		
		list(size_type n, const value_type& value,  const allocator_type& a = allocator_type()) : Base(Node_alloc_type(a))
		{ fill_initialize(n, value); }
#else
		explicit  list(size_type n, const value_type& value = value_type(), const allocator_type& a = allocator_type()) : Base(Node_alloc_type(a))
		{ fill_initialize(n, value); }
#endif
		list(const list& x) : Base(x.get_Node_allocator())
		{ initialize_dispatch(x.begin(), x.end(), false_type()); }

#if __cplusplus >= 201103L
		list(list&& x) noexcept : Base(std::move(x)) {}
		
		list(initializer_list<value_type> l, const allocator_type& a = allocator_type()) : Base(Node_alloc_type(a))
		{ initialize_dispatch(l.begin(), l.end(), false_type()); }
#endif
		// Builds a %list from a range.
#if __cplusplus >= 201103L
		template<typename InputIterator,   typename = std::_RequireInputIter<InputIterator>>
		list(InputIterator first, InputIterator last,  const allocator_type& a = allocator_type()) : Base(Node_alloc_type(a))
		{ initialize_dispatch(first, last, false_type()); }
#else
		template<typename InputIterator>
		list(InputIterator first, InputIterator last,  const allocator_type& a = allocator_type()) : Base(Node_alloc_type(a)) {
			// Check whether it's an integral type.  If so, it's not an iterator.
			typedef typename std::__is_integer<InputIterator>::__type Integral;
			initialize_dispatch(first, last, Integral());
		}
#endif		
     
        //No explicit dtor needed as the Base dtor takes care of  things. 		
		
		//All the elements of @a __x are copied, but unlike the copy
        //constructor, the allocator object is not copied.
		
		list& operator=(const list&);
#if __cplusplus >= 201103L
		list& operator=(list&& x) {			
			this->clear();
			this->swap(x);
			return *this;
		}
		list&  operator=(initializer_list<value_type> l) {
			this->assign(l.begin(), l.end());
			return *this;
		}
#endif

      void   assign(size_type n, const value_type& val)
	  { fill_assign(n, val); }

   
#if __cplusplus >= 201103L
      template<typename InputIterator,  typename = std::_RequireInputIter<InputIterator>>
	  void  assign(InputIterator first, InputIterator last)
	  { assign_dispatch(first, last, fale_type()); }
#else
	  template<typename InputIterator>
	  void assign(InputIterator first, InputIterator last) {
		  // Check whether it's an integral type.  If so, it's not an iterator.
		  typedef typename std::__is_integer<InputIterator>::__type Integral;
		  assign_dispatch(first, last, Integral());
	  }
#endif

#if __cplusplus >= 201103L
      void  assign(initializer_list<value_type> l)
      { this->assign(l.begin(), l.end()); }
#endif
	  allocator_type  get_allocator() const 
	  { return Base::get_allocator(); }
	  
	  iterator  begin()
      { return iterator(this->M_impl.M_node.next); }
	  
      const_iterator begin() const
      { return const_iterator(this->M_impl.M_node.next); }
      
      iterator  end()
      { return iterator(&this->M_impl.M_node); }
	  
	  const_iterator  end() const
      { return const_iterator(&this->M_impl.M_node); }
     
      reverse_iterator rbegin()
      { return reverse_iterator(end()); }

      const_reverse_iterator rbegin() const
      { return const_reverse_iterator(end()); }

      reverse_iterator  rend()
      { return reverse_iterator(begin()); }

      const_reverse_iterator  rend() const
      { return const_reverse_iterator(begin()); }

#if __cplusplus >= 201103L
      
      const_iterator  cbegin() const noexcept
      { return const_iterator(this->M_impl.M_node.next); }

      const_iterator  cend() const noexcept
      { return const_iterator(&this->M_impl.M_node); }

      const_reverse_iterator crbegin() const noexcept
      { return const_reverse_iterator(end()); }

      const_reverse_iterator crend() const noexcept
      { return const_reverse_iterator(begin()); }
#endif
	  /***********************************************************************************************************/
      // [23.2.2.2] capacity
      /**
       *  Returns true if the %list is empty.  (Thus begin() would equal
       *  end().)
       */
      bool
      empty() const
      { return this->_M_impl._M_node._M_next == &this->_M_impl._M_node; }

      /**  Returns the number of elements in the %list.  */
      size_type
      size() const
      { return std::distance(begin(), end()); }

      /**  Returns the size() of the largest possible %list.  */
      size_type
      max_size() const
      { return _M_get_Node_allocator().max_size(); }

#if __cplusplus >= 201103L
      /**
       *  @brief Resizes the %list to the specified number of elements.
       *  @param __new_size Number of elements the %list should contain.
       *
       *  This function will %resize the %list to the specified number
       *  of elements.  If the number is smaller than the %list's
       *  current size the %list is truncated, otherwise default
       *  constructed elements are appended.
       */
      void
      resize(size_type __new_size);

      /**
       *  @brief Resizes the %list to the specified number of elements.
       *  @param __new_size Number of elements the %list should contain.
       *  @param __x Data with which new elements should be populated.
       *
       *  This function will %resize the %list to the specified number
       *  of elements.  If the number is smaller than the %list's
       *  current size the %list is truncated, otherwise the %list is
       *  extended and new elements are populated with given data.
       */
      void
      resize(size_type __new_size, const value_type& __x);
#else
      /**
       *  @brief Resizes the %list to the specified number of elements.
       *  @param __new_size Number of elements the %list should contain.
       *  @param __x Data with which new elements should be populated.
       *
       *  This function will %resize the %list to the specified number
       *  of elements.  If the number is smaller than the %list's
       *  current size the %list is truncated, otherwise the %list is
       *  extended and new elements are populated with given data.
       */
      void
      resize(size_type __new_size, value_type __x = value_type());
#endif

      // element access
      /**
       *  Returns a read/write reference to the data at the first
       *  element of the %list.
       */
      reference
      front()
      { return *begin(); }

      /**
       *  Returns a read-only (constant) reference to the data at the first
       *  element of the %list.
       */
      const_reference
      front() const
      { return *begin(); }

      /**
       *  Returns a read/write reference to the data at the last element
       *  of the %list.
       */
      reference
      back()
      {
	iterator __tmp = end();
	--__tmp;
	return *__tmp;
      }

      /**
       *  Returns a read-only (constant) reference to the data at the last
       *  element of the %list.
       */
      const_reference
      back() const
      {
	const_iterator __tmp = end();
	--__tmp;
	return *__tmp;
      }

      // [23.2.2.3] modifiers
      /**
       *  @brief  Add data to the front of the %list.
       *  @param  __x  Data to be added.
       *
       *  This is a typical stack operation.  The function creates an
       *  element at the front of the %list and assigns the given data
       *  to it.  Due to the nature of a %list this operation can be
       *  done in constant time, and does not invalidate iterators and
       *  references.
       */
      void
      push_front(const value_type& __x)
      { this->_M_insert(begin(), __x); }

#if __cplusplus >= 201103L
      void
      push_front(value_type&& __x)
      { this->_M_insert(begin(), std::move(__x)); }

      template<typename... _Args>
        void
        emplace_front(_Args&&... __args)
        { this->_M_insert(begin(), std::forward<_Args>(__args)...); }
#endif

      /**
       *  @brief  Removes first element.
       *
       *  This is a typical stack operation.  It shrinks the %list by
       *  one.  Due to the nature of a %list this operation can be done
       *  in constant time, and only invalidates iterators/references to
       *  the element being removed.
       *
       *  Note that no data is returned, and if the first element's data
       *  is needed, it should be retrieved before pop_front() is
       *  called.
       */
      void
      pop_front()
      { this->_M_erase(begin()); }

      /**
       *  @brief  Add data to the end of the %list.
       *  @param  __x  Data to be added.
       *
       *  This is a typical stack operation.  The function creates an
       *  element at the end of the %list and assigns the given data to
       *  it.  Due to the nature of a %list this operation can be done
       *  in constant time, and does not invalidate iterators and
       *  references.
       */
      void
      push_back(const value_type& __x)
      { this->_M_insert(end(), __x); }

#if __cplusplus >= 201103L
      void
      push_back(value_type&& __x)
      { this->_M_insert(end(), std::move(__x)); }

      template<typename... _Args>
        void
        emplace_back(_Args&&... __args)
        { this->_M_insert(end(), std::forward<_Args>(__args)...); }
#endif

      /**
       *  @brief  Removes last element.
       *
       *  This is a typical stack operation.  It shrinks the %list by
       *  one.  Due to the nature of a %list this operation can be done
       *  in constant time, and only invalidates iterators/references to
       *  the element being removed.
       *
       *  Note that no data is returned, and if the last element's data
       *  is needed, it should be retrieved before pop_back() is called.
       */
      void
      pop_back()
      { this->_M_erase(iterator(this->_M_impl._M_node._M_prev)); }

#if __cplusplus >= 201103L
      /**
       *  @brief  Constructs object in %list before specified iterator.
       *  @param  __position  A const_iterator into the %list.
       *  @param  __args  Arguments.
       *  @return  An iterator that points to the inserted data.
       *
       *  This function will insert an object of type T constructed
       *  with T(std::forward<Args>(args)...) before the specified
       *  location.  Due to the nature of a %list this operation can
       *  be done in constant time, and does not invalidate iterators
       *  and references.
       */
      template<typename... _Args>
        iterator
        emplace(iterator __position, _Args&&... __args);
#endif

      /**
       *  @brief  Inserts given value into %list before specified iterator.
       *  @param  __position  An iterator into the %list.
       *  @param  __x  Data to be inserted.
       *  @return  An iterator that points to the inserted data.
       *
       *  This function will insert a copy of the given value before
       *  the specified location.  Due to the nature of a %list this
       *  operation can be done in constant time, and does not
       *  invalidate iterators and references.
       */
      iterator
      insert(iterator __position, const value_type& __x);

#if __cplusplus >= 201103L
      /**
       *  @brief  Inserts given rvalue into %list before specified iterator.
       *  @param  __position  An iterator into the %list.
       *  @param  __x  Data to be inserted.
       *  @return  An iterator that points to the inserted data.
       *
       *  This function will insert a copy of the given rvalue before
       *  the specified location.  Due to the nature of a %list this
       *  operation can be done in constant time, and does not
       *  invalidate iterators and references.
        */
      iterator
      insert(iterator __position, value_type&& __x)
      { return emplace(__position, std::move(__x)); }

      /**
       *  @brief  Inserts the contents of an initializer_list into %list
       *          before specified iterator.
       *  @param  __p  An iterator into the %list.
       *  @param  __l  An initializer_list of value_type.
       *
       *  This function will insert copies of the data in the
       *  initializer_list @a l into the %list before the location
       *  specified by @a p.
       *
       *  This operation is linear in the number of elements inserted and
       *  does not invalidate iterators and references.
       */
      void
      insert(iterator __p, initializer_list<value_type> __l)
      { this->insert(__p, __l.begin(), __l.end()); }
#endif

      /**
       *  @brief  Inserts a number of copies of given data into the %list.
       *  @param  __position  An iterator into the %list.
       *  @param  __n  Number of elements to be inserted.
       *  @param  __x  Data to be inserted.
       *
       *  This function will insert a specified number of copies of the
       *  given data before the location specified by @a position.
       *
       *  This operation is linear in the number of elements inserted and
       *  does not invalidate iterators and references.
       */
      void
      insert(iterator __position, size_type __n, const value_type& __x)
      {
	list __tmp(__n, __x, get_allocator());
	splice(__position, __tmp);
      }

      /**
       *  @brief  Inserts a range into the %list.
       *  @param  __position  An iterator into the %list.
       *  @param  __first  An input iterator.
       *  @param  __last   An input iterator.
       *
       *  This function will insert copies of the data in the range [@a
       *  first,@a last) into the %list before the location specified by
       *  @a position.
       *
       *  This operation is linear in the number of elements inserted and
       *  does not invalidate iterators and references.
       */
#if __cplusplus >= 201103L
      template<typename _InputIterator,
	       typename = std::_RequireInputIter<_InputIterator>>
#else
      template<typename _InputIterator>
#endif
        void
        insert(iterator __position, _InputIterator __first,
	       _InputIterator __last)
        {
	  list __tmp(__first, __last, get_allocator());
	  splice(__position, __tmp);
	}

      /**
       *  @brief  Remove element at given position.
       *  @param  __position  Iterator pointing to element to be erased.
       *  @return  An iterator pointing to the next element (or end()).
       *
       *  This function will erase the element at the given position and thus
       *  shorten the %list by one.
       *
       *  Due to the nature of a %list this operation can be done in
       *  constant time, and only invalidates iterators/references to
       *  the element being removed.  The user is also cautioned that
       *  this function only erases the element, and that if the element
       *  is itself a pointer, the pointed-to memory is not touched in
       *  any way.  Managing the pointer is the user's responsibility.
       */
      iterator
      erase(iterator __position);

      /**
       *  @brief  Remove a range of elements.
       *  @param  __first  Iterator pointing to the first element to be erased.
       *  @param  __last  Iterator pointing to one past the last element to be
       *                erased.
       *  @return  An iterator pointing to the element pointed to by @a last
       *           prior to erasing (or end()).
       *
       *  This function will erase the elements in the range @a
       *  [first,last) and shorten the %list accordingly.
       *
       *  This operation is linear time in the size of the range and only
       *  invalidates iterators/references to the element being removed.
       *  The user is also cautioned that this function only erases the
       *  elements, and that if the elements themselves are pointers, the
       *  pointed-to memory is not touched in any way.  Managing the pointer
       *  is the user's responsibility.
       */
      iterator
      erase(iterator __first, iterator __last)
      {
	while (__first != __last)
	  __first = erase(__first);
	return __last;
      }

      /**
       *  @brief  Swaps data with another %list.
       *  @param  __x  A %list of the same element and allocator types.
       *
       *  This exchanges the elements between two lists in constant
       *  time.  Note that the global std::swap() function is
       *  specialized such that std::swap(l1,l2) will feed to this
       *  function.
       */
      void
      swap(list& __x)
      {
	__detail::_List_node_base::swap(this->_M_impl._M_node,
					__x._M_impl._M_node);

	// _GLIBCXX_RESOLVE_LIB_DEFECTS
	// 431. Swapping containers with unequal allocators.
	std::__alloc_swap<typename _Base::_Node_alloc_type>::
	  _S_do_it(_M_get_Node_allocator(), __x._M_get_Node_allocator());
      }

      /**
       *  Erases all the elements.  Note that this function only erases
       *  the elements, and that if the elements themselves are
       *  pointers, the pointed-to memory is not touched in any way.
       *  Managing the pointer is the user's responsibility.
       */
      void clear() {      
		  Base::M_clear();
		  Base::init();
	  }

      // [23.2.2.4] list operations
      /**
       *  @brief  Insert contents of another %list.
       *  @param  __position  Iterator referencing the element to insert before.
       *  @param  __x  Source list.
       *
       *  The elements of @a __x are inserted in constant time in front of
       *  the element referenced by @a __position.  @a __x becomes an empty
       *  list.
       *
       *  Requires this != @a __x.
       */
      void
#if __cplusplus >= 201103L
      splice(iterator __position, list&& __x)
#else
      splice(iterator __position, list& __x)
#endif
      {
	if (!__x.empty())
	  {
	    _M_check_equal_allocators(__x);

	    this->_M_transfer(__position, __x.begin(), __x.end());
	  }
      }

#if __cplusplus >= 201103L
      void
      splice(iterator __position, list& __x)
      { splice(__position, std::move(__x)); }
#endif

      /**
       *  @brief  Insert element from another %list.
       *  @param  __position  Iterator referencing the element to insert before.
       *  @param  __x  Source list.
       *  @param  __i  Iterator referencing the element to move.
       *
       *  Removes the element in list @a __x referenced by @a __i and
       *  inserts it into the current list before @a __position.
       */
      void
#if __cplusplus >= 201103L
      splice(iterator __position, list&& __x, iterator __i)
#else
      splice(iterator __position, list& __x, iterator __i)
#endif
      {
	iterator __j = __i;
	++__j;
	if (__position == __i || __position == __j)
	  return;

	if (this != &__x)
	  _M_check_equal_allocators(__x);

	this->_M_transfer(__position, __i, __j);
      }

#if __cplusplus >= 201103L
      void
      splice(iterator __position, list& __x, iterator __i)
      { splice(__position, std::move(__x), __i); }
#endif

      /**
       *  @brief  Insert range from another %list.
       *  @param  __position  Iterator referencing the element to insert before.
       *  @param  __x  Source list.
       *  @param  __first  Iterator referencing the start of range in x.
       *  @param  __last  Iterator referencing the end of range in x.
       *
       *  Removes elements in the range [__first,__last) and inserts them
       *  before @a __position in constant time.
       *
       *  Undefined if @a __position is in [__first,__last).
       */
      void
#if __cplusplus >= 201103L
      splice(iterator __position, list&& __x, iterator __first,
	     iterator __last)
#else
      splice(iterator __position, list& __x, iterator __first,
	     iterator __last)
#endif
      {
	if (__first != __last)
	  {
	    if (this != &__x)
	      _M_check_equal_allocators(__x);

	    this->_M_transfer(__position, __first, __last);
	  }
      }

#if __cplusplus >= 201103L
      void
      splice(iterator __position, list& __x, iterator __first, iterator __last)
      { splice(__position, std::move(__x), __first, __last); }
#endif

      /**
       *  @brief  Remove all elements equal to value.
       *  @param  __value  The value to remove.
       *
       *  Removes every element in the list equal to @a value.
       *  Remaining elements stay in list order.  Note that this
       *  function only erases the elements, and that if the elements
       *  themselves are pointers, the pointed-to memory is not
       *  touched in any way.  Managing the pointer is the user's
       *  responsibility.
       */
      void
      remove(const Tp& value);

      /**
       *  @brief  Remove all elements satisfying a predicate.
       *  @tparam  _Predicate  Unary predicate function or object.
       *
       *  Removes every element in the list for which the predicate
       *  returns true.  Remaining elements stay in list order.  Note
       *  that this function only erases the elements, and that if the
       *  elements themselves are pointers, the pointed-to memory is
       *  not touched in any way.  Managing the pointer is the user's
       *  responsibility.
       */
      template<typename _Predicate>
        void
        remove_if(_Predicate);

      /**
       *  @brief  Remove consecutive duplicate elements.
       *
       *  For each consecutive set of elements with the same value,
       *  remove all but the first one.  Remaining elements stay in
       *  list order.  Note that this function only erases the
       *  elements, and that if the elements themselves are pointers,
       *  the pointed-to memory is not touched in any way.  Managing
       *  the pointer is the user's responsibility.
       */
      void
      unique();

      /**
       *  @brief  Remove consecutive elements satisfying a predicate.
       *  @tparam _BinaryPredicate  Binary predicate function or object.
       *
       *  For each consecutive set of elements [first,last) that
       *  satisfy predicate(first,i) where i is an iterator in
       *  [first,last), remove all but the first one.  Remaining
       *  elements stay in list order.  Note that this function only
       *  erases the elements, and that if the elements themselves are
       *  pointers, the pointed-to memory is not touched in any way.
       *  Managing the pointer is the user's responsibility.
       */
      template<typename _BinaryPredicate>
        void
        unique(_BinaryPredicate);

      /**
       *  @brief  Merge sorted lists.
       *  @param  __x  Sorted list to merge.
       *
       *  Assumes that both @a __x and this list are sorted according to
       *  operator<().  Merges elements of @a __x into this list in
       *  sorted order, leaving @a __x empty when complete.  Elements in
       *  this list precede elements in @a __x that are equal.
       */
#if __cplusplus >= 201103L
      void
      merge(list&& __x);

      void
      merge(list& __x)
      { merge(std::move(__x)); }
#else
      void
      merge(list& __x);
#endif

      /**
       *  @brief  Merge sorted lists according to comparison function.
       *  @tparam _StrictWeakOrdering Comparison function defining
       *  sort order.
       *  @param  __x  Sorted list to merge.
       *  @param  __comp  Comparison functor.
       *
       *  Assumes that both @a __x and this list are sorted according to
       *  StrictWeakOrdering.  Merges elements of @a __x into this list
       *  in sorted order, leaving @a __x empty when complete.  Elements
       *  in this list precede elements in @a __x that are equivalent
       *  according to StrictWeakOrdering().
       */
#if __cplusplus >= 201103L
      template<typename _StrictWeakOrdering>
        void
        merge(list&& __x, _StrictWeakOrdering __comp);

      template<typename _StrictWeakOrdering>
        void
        merge(list& __x, _StrictWeakOrdering __comp)
        { merge(std::move(__x), __comp); }
#else
      template<typename _StrictWeakOrdering>
        void
        merge(list& __x, _StrictWeakOrdering __comp);
#endif

      /**
       *  @brief  Reverse the elements in list.
       *
       *  Reverse the order of elements in the list in linear time.
       */
      void  reverse()
      { this->M_impl.M_node.M_reverse(); }

      /**
       *  @brief  Sort the elements.
       *
       *  Sorts the elements of this list in NlogN time.  Equivalent
       *  elements remain in list order.
       */
      void sort();

      /**
       *  @brief  Sort the elements according to comparison function.
       *
       *  Sorts the elements of this list in NlogN time.  Equivalent
       *  elements remain in list order.
       */
      template<typename _StrictWeakOrdering>
        void
        sort(_StrictWeakOrdering);

    protected:
      // Internal constructor functions follow.

      // Called by the range constructor to implement [23.1.1]/9

      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 438. Ambiguity in the "do the right thing" clause
      template<typename Integer>
	  void  initialize_dispatch(Integer n, Integer x, true_type)
	  { fill_initialize(static_cast<size_type>(n), x); }

      // Called by the range constructor to implement [23.1.1]/9
	  template<typename InputIterator>
	  void initialize_dispatch(InputIterator first, InputIterator last, false_type)  {
		  for (; first != last; ++first)
#if __cplusplus >= 201103L
			  emplace_back(*first);
#else
			  push_back(*first);
#endif
	  }

      // Called by list(n,v,a), and the range constructor when it turns out
      // to be the same thing.
      void fill_initialize(size_type n, const value_type& x) {
		  for (; n; --n)
			  push_back(x);
	  }

#if __cplusplus >= 201103L
	  // Called by list(n).
	  void default_initialize(size_type n) {
		  for (; n; --n)
			  emplace_back();
	  }

      // Called by resize(sz).
      void default_append(size_type n);
#endif
	  // Internal assign functions follow.
	  // Called by the range assign to implement [23.1.1]/9
	  // _GLIBCXX_RESOLVE_LIB_DEFECTS
	  // 438. Ambiguity in the "do the right thing" clause
	  template<typename Integer>
	  void  assign_dispatch(Integer n, Integer val, true_type)
	  { fill_assign(n, val); }

      // Called by the range assign to implement [23.1.1]/9
      template<typename InputIterator>
	  void assign_dispatch(InputIterator first, InputIterator last, false_type);

      // Called by assign(n,t), and the range assign when it turns out
      // to be the same thing.
      void fill_assign(size_type n, const value_type& val);


      // Moves the elements from [first,last) before position.
      void _M_transfer(iterator __position, iterator __first, iterator __last)
      { __position._M_node->_M_transfer(__first._M_node, __last._M_node); }

      // Inserts new element at position given and with value given.
#if __cplusplus < 201103L
      void
      _M_insert(iterator __position, const value_type& __x)
      {
        _Node* __tmp = _M_create_node(__x);
        __tmp->_M_hook(__position._M_node);
      }
#else
     template<typename... _Args>
       void
       _M_insert(iterator __position, _Args&&... __args)
       {
	 _Node* __tmp = _M_create_node(std::forward<_Args>(__args)...);
	 __tmp->_M_hook(__position._M_node);
       }
#endif

      // Erases element at position given.
      void
      _M_erase(iterator __position)
      {
        __position._M_node->_M_unhook();
        _Node* __n = static_cast<_Node*>(__position._M_node);
#if __cplusplus >= 201103L
        _M_get_Node_allocator().destroy(__n);
#else
	_M_get_Tp_allocator().destroy(std::__addressof(__n->_M_data));
#endif
        _M_put_node(__n);
      }

      // To implement the splice (and merge) bits of N1599.
      void
      _M_check_equal_allocators(list& __x)
      {
	if (std::__alloc_neq<typename _Base::_Node_alloc_type>::
	    _S_do_it(_M_get_Node_allocator(), __x._M_get_Node_allocator()))
	  __throw_runtime_error(__N("list::_M_check_equal_allocators"));
      }
    };

  /**
   *  @brief  List equality comparison.
   *  @param  __x  A %list.
   *  @param  __y  A %list of the same type as @a __x.
   *  @return  True iff the size and elements of the lists are equal.
   *
   *  This is an equivalence relation.  It is linear in the size of
   *  the lists.  Lists are considered equivalent if their sizes are
   *  equal, and if corresponding elements compare equal.
  */
  template<typename _Tp, typename _Alloc>
    inline bool
    operator==(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    {
      typedef typename list<_Tp, _Alloc>::const_iterator const_iterator;
      const_iterator __end1 = __x.end();
      const_iterator __end2 = __y.end();

      const_iterator __i1 = __x.begin();
      const_iterator __i2 = __y.begin();
      while (__i1 != __end1 && __i2 != __end2 && *__i1 == *__i2)
	{
	  ++__i1;
	  ++__i2;
	}
      return __i1 == __end1 && __i2 == __end2;
    }

  /**
   *  @brief  List ordering relation.
   *  @param  __x  A %list.
   *  @param  __y  A %list of the same type as @a __x.
   *  @return  True iff @a __x is lexicographically less than @a __y.
   *
   *  This is a total ordering relation.  It is linear in the size of the
   *  lists.  The elements must be comparable with @c <.
   *
   *  See std::lexicographical_compare() for how the determination is made.
  */
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    { return std::lexicographical_compare(__x.begin(), __x.end(),
					  __y.begin(), __y.end()); }

  /// Based on operator==
  template<typename _Tp, typename _Alloc>
    inline bool
    operator!=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    { return !(__x == __y); }

  /// Based on operator<
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    { return __y < __x; }

  /// Based on operator<
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    { return !(__y < __x); }

  /// Based on operator<
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
    { return !(__x < __y); }

  /// See std::list::swap().
  template<typename _Tp, typename _Alloc>
    inline void
    swap(list<_Tp, _Alloc>& __x, list<_Tp, _Alloc>& __y)
    { __x.swap(__y); }

	

} // namespace std

#endif /* _STL_LIST_H */
