/*
 * Copyright (c) 2017, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef AMO_TYPE_TRAITS_HPP
#define AMO_TYPE_TRAITS_HPP
  

#ifdef BOOST_NO_CXX11_HDR_TYPE_TRAITS
#include <amo/config.hpp>
#else
#include <type_traits>
#endif

namespace amo {


#ifdef BOOST_NO_CXX11_HDR_TYPE_TRAITS
	using boost::aligned_storage;
	using boost::decay;
	using boost::enable_if;
	//using boost::add_const;
	//using boost::add_cv;
	//using boost::add_pointer;
	//using boost::add_lvalue_reference;
	//using boost::add_reference;	// retained
	//using boost::add_rvalue_reference;
	//using boost::add_volatile;
	//using boost::aligned_storage;
	//using boost::alignment_of;
	//using boost::conditional;
	//using boost::decay;
	//using boost::enable_if;
	//using boost::extent;
	//using boost::false_type;
	//using boost::has_nothrow_assign;
	//using boost::has_nothrow_constructor;	// retained
	//using boost::has_nothrow_copy;	// retained
	//using boost::has_nothrow_copy_constructor;
	//using boost::has_nothrow_default_constructor;
	//using boost::has_trivial_assign;
	//using boost::has_trivial_constructor;	// retained
	//using boost::has_trivial_copy;	// retained
	//using boost::has_trivial_copy_constructor;
	//using boost::has_trivial_default_constructor;
	//using boost::has_trivial_destructor;
	//using boost::has_virtual_destructor;
	//using boost::integral_constant;
	//using boost::is_abstract;
	//using boost::is_arithmetic;
	//using boost::is_array;
	//using boost::is_base_of;
	//using boost::is_class;
	//using boost::is_compound;
	//using boost::is_const;
	//using boost::is_convertible;
	//using boost::is_empty;
	//using boost::is_enum;
	//using boost::is_floating_point;
	//using boost::is_function;
	//using boost::is_fundamental;
	//using boost::is_integral;
	//using boost::is_lvalue_reference;
	//using boost::is_member_function_pointer;
	//using boost::is_member_object_pointer;
	//using boost::is_member_pointer;
	//using boost::is_object;
	//using boost::is_pod;
	//using boost::is_pointer;
	//using boost::is_polymorphic;
	//using boost::is_reference;
	//using boost::is_rvalue_reference;
	//using boost::is_same;
	//using boost::is_scalar;
	//using boost::is_signed;
	//using boost::is_standard_layout;
	//using boost::is_trivial;
	//using boost::is_union;
	//using boost::is_unsigned;
	//using boost::is_void;
	//using boost::is_volatile;
	//using boost::make_signed;
	//using boost::make_unsigned;
	//using boost::rank;
	//using boost::remove_all_extents;
	//using boost::remove_const;
	//using boost::remove_cv;
	//using boost::remove_extent;
	//using boost::remove_pointer;
	//using boost::remove_reference;
	//using boost::_Remove_rvalue_reference;
	//using boost::remove_volatile;
	//using boost::true_type;
	//namespace amo = boost;
#else
	using std::add_const;
	using std::add_cv;
	using std::add_pointer;
	using std::add_lvalue_reference;
	//using std::add_reference;	// retained
	using std::add_rvalue_reference;
	using std::add_volatile;
	using std::aligned_storage;
	using std::alignment_of;
	using std::conditional;
	using std::decay;
	using std::enable_if;
	using std::extent;
	using std::false_type;
	//using std::has_nothrow_assign;
	//using std::has_nothrow_constructor;	// retained
	//using std::has_nothrow_copy;	// retained
	//using std::has_nothrow_copy_constructor;
	//using std::has_nothrow_default_constructor;
	//using std::has_trivial_assign;
	//using std::has_trivial_constructor;	// retained
	//using std::has_trivial_copy;	// retained
	//using std::has_trivial_copy_constructor;
	//using std::has_trivial_default_constructor;
	//using std::has_trivial_destructor;
	using std::has_virtual_destructor;
	using std::integral_constant;
	using std::is_abstract;
	using std::is_arithmetic;
	using std::is_array;
	using std::is_base_of;
	using std::is_class;
	using std::is_compound;
	using std::is_const;
	using std::is_convertible;
	using std::is_empty;
	using std::is_enum;
	using std::is_floating_point;
	using std::is_function;
	using std::is_fundamental;
	using std::is_integral;
	using std::is_lvalue_reference;
	using std::is_member_function_pointer;
	using std::is_member_object_pointer;
	using std::is_member_pointer;
	using std::is_object;
	using std::is_pod;
	using std::is_pointer;
	using std::is_polymorphic;
	using std::is_reference;
	using std::is_rvalue_reference;
	using std::is_same;
	using std::is_scalar;
	using std::is_signed;
	using std::is_standard_layout;
	using std::is_trivial;
	using std::is_union;
	using std::is_unsigned;
	using std::is_void;
	using std::is_volatile;
	using std::make_signed;
	using std::make_unsigned;
	using std::rank;
	using std::remove_all_extents;
	using std::remove_const;
	using std::remove_cv;
	using std::remove_extent;
	using std::remove_pointer;
	using std::remove_reference;
	//using std::remove_rvalue_reference;
	using std::remove_volatile;
	using std::true_type;
#endif

	template<typename T> struct is_not_void{ static const bool value = true; };
	template<> struct is_not_void < void > { static const bool value = false; };

} // namespace amo

#endif // AMO_TYPE_TRAITS_HPP
