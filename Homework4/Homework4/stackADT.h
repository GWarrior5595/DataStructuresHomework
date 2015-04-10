#ifndef H_StackADT
#define H_StackADT

template <class Type>
class stackADT
{
public:
	virtual void initializeStack() = 0;

	virtual bool empty() const = 0;

	virtual bool isFullStack() const = 0;

	virtual void push(const Type& newItem) = 0;

	virtual Type top() const = 0;

	virtual void pop() = 0;
};

#endif
