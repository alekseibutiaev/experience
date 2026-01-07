#pragma once

#ifndef __WINDLL_STL_EXPORT_HPP__
#define __WINDLL_STL_EXPORT_HPP__

#if 0
http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
#endif

#include "windll_export.h"

#if defined( NDEBUG )
#define EXPORT_STL_CONTEINER_BASE_AUX_ALLOC_REAL( __export_impl__, __dllmacro__, ... ) \
  __export_impl__ class  __dllmacro__ std::_Container_base_aux; \
  __export_impl__ class  __dllmacro__ std::_Aux_cont; \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Aux_cont >; \
  __export_impl__ template class __dllmacro__ std::_Container_base_aux_alloc_real< __VA_ARGS__ >

#else
#define EXPORT_STL_CONTEINER_BASE_AUX_ALLOC_REAL( __export_impl__, __dllmacro__, ... )
#endif

#define EXPORT_STL_VECTOR( __export_impl__, __dllmacro__, __type__ ) \
  __export_impl__ template class __dllmacro__ std::allocator< __type__ >; \
  EXPORT_STL_CONTEINER_BASE_AUX_ALLOC_REAL( __export_impl__, __dllmacro__, std::allocator< __type__ > ); \
  __export_impl__ template class __dllmacro__ std::vector< __type__, std::allocator< __type__ > >



#define EXPORT_STL_DEQUE( __export_impl__, __dllmacro__, __type__ ) \
  __export_impl__ template class __dllmacro__ std::allocator< __type__ >; \
  EXPORT_STL_CONTEINER_BASE_AUX_ALLOC_REAL( __export_impl__, __dllmacro__, std::allocator< __type__ > ); \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Deque_map< __type__, std::allocator< __type__ > >::_Tptr > ; \
  __export_impl__ template class __dllmacro__ std::_Deque_map< __type__, std::allocator< __type__ > >; \
  __export_impl__ template class __dllmacro__ std::_Deque_val< __type__, std::allocator< __type__ > >; \
  __export_impl__ template class __dllmacro__ std::deque< __type__, std::allocator< __type__ > >

#define EXPORT_STL_LIST( __export_impl__, __dllmacro__, __type__ ) \
  __export_impl__ template class __dllmacro__ std::allocator< __type__ >; \
  EXPORT_STL_CONTEINER_BASE_AUX_ALLOC_REAL( __export_impl__, __dllmacro__, std::allocator< __type__ > ); \
  __export_impl__ template class __dllmacro__ std::allocator< std::_List_nod< __type__, std::allocator< __type__ > >::_Node >; \
  __export_impl__ template class __dllmacro__ std::allocator< std::_List_nod< __type__, std::allocator< __type__ > >::_Nodeptr >; \
  __export_impl__ template class __dllmacro__ std::list< __type__, std::allocator< __type__ > >

#define EXPORT_STL_SET( __export_impl__, __dllmacro__, __type__ ) \
  __export_impl__ template class __dllmacro__ std::allocator< __type__ >; \
  __export_impl__ template struct __dllmacro__ std::less< __type__ >; \
  EXPORT_STL_CONTEINER_BASE_AUX_ALLOC_REAL( __export_impl__, __dllmacro__, std::allocator< __type__ > ); \
  __export_impl__ template class __dllmacro__ std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, false >; \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_nod< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, false > >::_Node >;  \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_nod< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, false > >::_Nodeptr >;  \
  __export_impl__ template class __dllmacro__ std::_Tree_ptr< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, false > >; \
  __export_impl__ template class __dllmacro__ std::_Tree_nod< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, false > >; \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_ptr< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, false > > >; \
  __export_impl__ template class __dllmacro__ std::_Tree_val< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, false > >; \
  __export_impl__ template class __dllmacro__ std::set< __type__, std::less< __type__ >, std::allocator< __type__ > > 

#define EXPORT_STL_MULTISET( __export_impl__, __dllmacro__, __type__ ) \
  __export_impl__ template class __dllmacro__ std::allocator< __type__ >; \
  __export_impl__ template struct __dllmacro__ std::less< __type__ >; \
  EXPORT_STL_CONTEINER_BASE_AUX_ALLOC_REAL( __export_impl__, __dllmacro__, std::allocator< __type__ > ); \
  __export_impl__ template class __dllmacro__ std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, true >; \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_nod< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, true > >::_Node >;  \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_nod< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, true > >::_Nodeptr >;  \
  __export_impl__ template class __dllmacro__ std::_Tree_ptr< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, true > >; \
  __export_impl__ template class __dllmacro__ std::_Tree_nod< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, true > >; \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_ptr< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, true > > >; \
  __export_impl__ template class __dllmacro__ std::_Tree_val< std::_Tset_traits< __type__, std::less< __type__ >, std::allocator< __type__ >, true > >; \
  __export_impl__ template class __dllmacro__ std::multiset< __type__, std::less< __type__ >, std::allocator< __type__ > > 

#define EXPORT_STL_MAP( __export_impl__, __dllmacro__, __key__, __type__ ) \
  __export_impl__ template struct __dllmacro__ std::pair< __key__, __type__ >; \
  __export_impl__ template class __dllmacro__ std::allocator< std::pair< const __key__, __type__ > >; \
  __export_impl__ template struct __dllmacro__ std::less< __key__ >; \
  EXPORT_STL_CONTEINER_BASE_AUX_ALLOC_REAL( __export_impl__, __dllmacro__, std::allocator< std::pair< const __key__, __type__ > > ); \
  __export_impl__ template class __dllmacro__ std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, false >; \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_nod< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, false > >::_Node >;  \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_nod< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, false > >::_Nodeptr >;  \
  __export_impl__ template class __dllmacro__ std::_Tree_ptr< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, false > >; \
  __export_impl__ template class __dllmacro__ std::_Tree_nod< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, false > >; \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_ptr< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, false > > >; \
  __export_impl__ template class __dllmacro__ std::_Tree_val< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, false > >; \
  __export_impl__ template class __dllmacro__ std::map< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > > >

#define EXPORT_STL_MULTIMAP( __export_impl__, __dllmacro__, __key__, __type__ ) \
  __export_impl__ template struct __dllmacro__ std::pair< __key__, __type__ >; \
  __export_impl__ template class __dllmacro__ std::allocator< std::pair< const __key__, __type__ > >; \
  __export_impl__ template struct __dllmacro__ std::less< __key__ >; \
  EXPORT_STL_CONTEINER_BASE_AUX_ALLOC_REAL( __export_impl__, __dllmacro__, std::allocator< std::pair< const __key__, __type__ > > ); \
  __export_impl__ template class __dllmacro__ std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, true >; \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_nod< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, true > >::_Node >;  \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_nod< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, true > >::_Nodeptr >;  \
  __export_impl__ template class __dllmacro__ std::_Tree_ptr< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, true > >; \
  __export_impl__ template class __dllmacro__ std::_Tree_nod< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, true > >; \
  __export_impl__ template class __dllmacro__ std::allocator< std::_Tree_ptr< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, true > > >; \
  __export_impl__ template class __dllmacro__ std::_Tree_val< std::_Tmap_traits< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > >, true > >; \
  __export_impl__ template class __dllmacro__ std::multimap< __key__, __type__, std::less< __key__ >, std::allocator< std::pair< const __key__, __type__ > > >

#endif /* __WINDLL_STL_EXPORT_HPP__ */
