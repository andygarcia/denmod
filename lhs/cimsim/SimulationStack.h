#pragma once

using namespace System;
using namespace System::Threading;



public ref class SimulationStack
{
public:
	SimulationStack()
  {
    _stack = gcnew Collections::Generic::Stack<String^>();
  }

public:
	void Push(String ^ s)
	{
		_stack->Push(s);
	}

	String ^ Pop(void)
	{
		System::Threading::Monitor::Enter(_stack);
		try {
			return _stack->Pop();
		}
		finally {
			System::Threading::Monitor::Exit(_stack);
		}
	}

public:
  property int Count {
    int get(void)
    {
		  System::Threading::Monitor::Enter(_stack);
		    try {
			    return _stack->Count;
		    }
		    finally {
			    System::Threading::Monitor::Exit(_stack);
		    }
    }
  }

private:
  Collections::Generic::Stack<String^> ^_stack;
};
