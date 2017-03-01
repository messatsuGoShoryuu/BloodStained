#ifndef BS_ARRAY_OPERATIONS
#define BS_ARRAY_OPERATIONS

#include "bs_types.h"

namespace bs
{
	/*Copy an array into an existing one (should be preallocated).
	*@source: source array
	*@destination: destination array
	*@count: item count of the source array
	*/
	template <class T>
	void copyArray(T* source, T* destination, ui32 count)
	{
		for (ui32 i = 0; i < count; i++)
		{
			if (source + i)
				new(destination + i) T(source[i]);
		}
	}

	/*Call destructors of objects in array.
	*@source: source array
	*@count: item count of the source array
	*/
	template <class T>
	void clearArray(T* source, ui32 count)
	{
		for (ui32 i = 0; i < count; i++)
		{
			if (source + i)
			{
				source[i].~T();
			}
				
		}
	}


	/*Swap two elements.
	*@source: source array
	*@index1: index of first element in the source array
	*@index2: index of the second element in the source array
	*/
	template<class T>
	void swapArrayItem(T* source, ui32 index1, ui32 index2)
	{
		T temp;
		new (&temp) T(source[index1]);
		new(source + index1) T(source[index2]);
		new(source + index2) T(temp);
	}

	/*Returns the index of the first object which tests 
	* true to a "==" test. 
	* Returns BS_INVALID_INDEX if no object is found
	*@source: source array
	*@item:	item to be found
	*@count: item count of the source array
	*/
	template<class T>
	ui32 findIndexInArray(T* source, const T& item, ui32 count)
	{
		for (ui32 i = 0; i < count; i++)
		{
			if (item == source[i]) return i;
		}
		return BS_INVALID_INDEX;
	}

	/*Find all indexes of objects that test true to
	*"==" test. Stores indexes into indexes array.
	*Returns false if no item is found.
	*@source: source array
	*@item: item to be found
	*@sourceCount: item count of the source array
	*@indexes: index array
	*@indexCount: count of items found
	*@maxIndexCount: preallocated space in index array
	*/
	template<class T>
	bool findIndexesInArray(T* source, const T& item, ui32 sourceCount, 
							ui32* indexes, ui32& indexCount, ui32 maxIndexCount)
	{
		//reset index count to 0
		indexCount = 0;

		for (ui32 i = 0; i < sourceCount; i++)
		{
			//if our index array is full return
			if (indexCount >= maxIndexCount)
			{
				return indexCount == 0 ? false : true;
			}

			//else test equalities
			if (source[i] == item)
			{
				//store index
				indexes[indexCount++] = i;
			}
		}

		return indexCount == 0 ? false : true;
	}
}


#endif // !BS_ARRAY_OPERATIONS
