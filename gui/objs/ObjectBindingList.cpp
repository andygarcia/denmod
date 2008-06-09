#include "StdAfx.h"
#include "ObjectBindingList.h"

using namespace gui;
using namespace System;
using namespace System::Reflection;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;



generic <typename T>
ObjectBindingList<T>::ObjectBindingList(void)
: BindingList<T>()
{}



generic <typename T>
ObjectBindingList<T>::ObjectBindingList( System::Collections::Generic::IList<T> ^ rhs )
: BindingList<T>()
{
  // BindingList<T> is derived from Collection<T>,, whose copy constructor uses the IList
  // parameter as its actual collection, not to initialize its collection, furthermore
  // even if List<T> and ArrayList copy elements from argument, these would still be just references

  // generics in .NET pose some problems in instantiating a generic type parameter... 
  // in this case this means difficulties in calling the copy constructor
  // so let's find it

  // find copy constructor
  Type ^ type = T::typeid;
  ConstructorInfo ^ ci = type->GetConstructor( gcnew array<Type^>(1){type} );
  if( ci == nullptr ) {
    throw gcnew InvalidOperationException( "ObjectBindingList<T> : T has no copy constructor" );
  }

  // copy each item
  for each( T item in rhs ) {
    T itemCopy = safe_cast<T>(ci->Invoke( gcnew array<Object^>(1){item} ));
    this->Add( itemCopy );
  }

  // alternatively we could use this in the for loop:
  //T itemCopy = System::Activator::CreateInstance( T::typeid, gcnew array<Type^>(1){type} );
  // but given reflection costs, why not just find the constructor ourselves and then invoke
  // each time
}



generic <typename T>
ObjectBindingList<T>::~ObjectBindingList(void)
{}


generic <typename T>
System::Object ^ ObjectBindingList<T>::Clone(void)
{
  return Activator::CreateInstance( T::typeid,  gcnew array<Object^>(1){this} );
}
