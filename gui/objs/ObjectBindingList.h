// ======================================================================== //
// ObjectBindingList                                                        //
//                                                                          //
// This is a generic derived from the generic BindingList<T>.  The only     //
// modification is to make the copy constructor -- which isn't quite        //
// correctly named since it accepts any object which implements the generic //
// interface IList<T> -- to make this "copy constructor" copy the list into //
// its own storage, rather than set it as its internal list, as well as     //
// copy construct the list items themselves.                                //
// =======================================================================  //
#pragma once

#include "NotifyValidateEditBase.h"



namespace gui {



generic <typename T>
public ref class ObjectBindingList : public System::ComponentModel::BindingList<T>,
                                     public System::ICloneable
{
#pragma region Constructors
public:
  ObjectBindingList(void);
  ObjectBindingList( System::Collections::Generic::IList<T> ^ rhs );
  virtual ~ObjectBindingList(void);
#pragma endregion

#pragma region ICloneable
  virtual System::Object ^ Clone(void);
#pragma endregion

};

};
