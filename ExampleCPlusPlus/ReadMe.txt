
Examples of popular object oriented problems coded in c++

Some key gotchas and things for new c++ coders to look for are listed below:


References, raw pointers and smart pointers.

In c++11 onwards, there are fewer reasons to use raw pointers. Raw pointers don't give us much information other than that this variable may or may not point to a variable of a certain type. The ownership is unknown and if this object is deleted elsewhere, we have no way of knowing this.
A general rule for when to use pointers or references is to always use references if possible. The only reason it may not be possible to use a reference is if the object could be null. Therefore, we can make assumptions about the usage of an object based on whether we are asked to pass by pointer or reference.
For example:

	void MyFunc(Object* obj);

The function signature implies that obj could be nullptr and that indeed nullptr is an acceptable parameter. If writing code like this, be aware of the message you're giving to clients of this code. In contrast the function declaration:

	void MyFunc(Object& obj);

Here it is implied that obj will never be nullptr (references can still point to a nullptr even if you cannot directly assign nullptr to it) and that no such test to ensure that it isn't null will take place. Users cannot even call this function with MyFunc(nullptr);

The same goes for return types. Be sure you're giving the right message to clients. For example:

	Object* GetObjectP();
	Object& GetObjectR();

If you have a function returning a pointer such as GetObjectP() you're implying that the result could well be nullptr and that clients should indeed check the return value before attempting to do something. In contrast, GetObjectR should always return a value.


On a similar note, the choice of whether we use pointers or references in storing variables also gives clue as to the usage, so be sure to make the correct choice. If storing a member variable of type Object, your choices are

class C
{
Object mObject;
Object* mObject;
Object& mObject;
}

If using the first option, the object's lifetime is directly attached to the lifetime of the object of C that mObject is a part of.  Use this way of storing the object if that is the desired behaviour remembering that if you open up access to mObject, that any references to it will become invalid when the instance of C is destroyed.
If using the second option, you should only do so if at some point mObject could be nullptr. Any usage of this variable should be made with caution given that there is a chance it could be null, so ensure it is checked as often as it needs to be for nullptr. Another reason why mObject might be nullptr is if the construction of mObject will happen at a later date than construction, this can lead to problems that are easily addressed by smart pointers
If using the third option, mObject needs to be assigned on construction and must always hold a reference to a valid object.


Smart pointers (weak, shared and unique/auto) are well documented on the web and so no further explanation of them will be used here. We can summarise though by saying that whenever you're newing an object, you should probably be assigning that object to a smart pointer so that its lifetime can be tracked.
Your choice of smart pointer will give good hints as to how the object should be used and who owns it. As a rough guide, use unique_ptr whenever it is possible to do so, shared_ptr whenever an object can be held by multiple objects but you don't know who will be last to use it and use weak_ptr if you are interested in an object, but only if it is still being kept alive somewhere else



Const correctness

The const keyword should be used as often as it can be used. As a general rule, if const can be entered somewhere, then it should be. Failure to mark a function as const is a failure to guarantee the client that no side effects will occur. Failure to mark a variable as const is a failure to inform your code readers as to your intentions for this variable.
If I ever see code such as

bool GetResult();

I'm left scratching my head as to what side effect the function could cause; mark it as const!




Constructor initialisor lists

c++ provides a means of constructing your data members as part of the construction process of an object.

class C
{
public:
	C(RefObject& rObj);
private:
    // data members
	int mIntVar;
	Object mObj;
	RefObject& mObjRef;
	PointerObject* mObjPtr;
}

C(RefObject& rObj)
: mIntVar(0)
, mObj()
, mObjRef(rObj)
, mObjPtr(nullptr)
{}

Not using initialiser lists means that your data members could simply contain unusable garbage, and any reads or writes to that variable will give undefined behaviour. Note that objects of classes with default constructors will be initialised via that default constructor during this time.
If users decide to assign data to their data members in the constructor body but not as part of the constructor initialiser list, be warned that you are constructing objects twice! Since they will be constructed anyway in the default constructor, with undefined arguments (unless an object with a default constructor) and then again when you do the assigning in the constructor body
Remember that data members are initialised in the order they are listed in the class header, not the order in which they appear in the constructor initialiser list!


Strings

Getting a good understanding on how c++ deals with raw string literals and how to use classes like std::string to avoid some of the pitfalls that can occur here, will give you a good grasp on some of the fundamentals of memory management in c++.
const char* can be used to store strings, but be aware of where the data is being stored, especially if you're going to start passing it around. I would strongly recommend using a string wrapper class such as std::string to assist your handling of string literals in code.



Casting

Be sure to know the difference between static_cast dynamic_cast const_cast and reinterperet_cast and never use the C style casts Object* o = (Object*)someObj;




Forward declarations

Always favour forward declaring classes in headers over including them where possible. Defer inclusion to cpp files to increase compile teams and reduce the risk of cyclic dependencies



Implementation in header or cpp?

All implementation should go in the cpp with the exception of
	Very simple one line getter and setter functions (be sure that your project lead agrees!)
	Templated functionality, which cannot be linked in if it is in the cpp file



asserts

Use asserts liberally throughout your code, the chances are that you will greatly reduce your debug time if you can catch errors that you say should never happen! If there is any scope for error, use an assert to check that things are running as they should be