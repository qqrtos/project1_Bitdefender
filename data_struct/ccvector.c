#include "ccvector.h"
#include "common.h"
#include "string.h"

//Create vector.
int VecCreate(CC_VECTOR** Vector)
{
	CC_VECTOR* vec = NULL;

	if (NULL == Vector)
	{
		return -1;
	}

	vec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
	if (NULL == vec)
	{
		free(vec);
		return -1;
	}

	memset(vec, 0, sizeof(*vec));

	vec->Count = 0;
	vec->Size = INITIAL_VECTOR_SIZE;
	vec->Array = (int*)malloc(sizeof(int) * INITIAL_VECTOR_SIZE);
	if (NULL == vec->Array)
	{
		free(vec->Array);
		return -1;
	}

	*Vector = vec;

	return 0;
}

//Destroy vector.
int VecDestroy(CC_VECTOR** Vector)
{
	CC_VECTOR* vec = *Vector;

	if (NULL == Vector)
	{
		return -1;
	}

	free(vec->Array);
	free(vec);

	*Vector = NULL;

	return 0;
}

//Insert element after last position.
int VecInsertTail(CC_VECTOR* Vector, int Value)
{
	if (NULL == Vector)
	{
		return -1;
	}

	if (Vector->Count >= Vector->Size)
	{
		/// REALLOC
		int* Array = (int*)realloc(Vector->Array, (INITIAL_VECTOR_SIZE + Vector->Count) * sizeof(int));
		if (NULL == Array)
		{
			return -1;
		}
		Vector->Size = INITIAL_VECTOR_SIZE + Vector->Count;
		Vector->Array = Array;
	}

	Vector->Array[Vector->Count] = Value;
	Vector->Count++;

	return 0;
}

//Insert element at first position.
int VecInsertHead(CC_VECTOR* Vector, int Value)
{
	if (NULL == Vector)
	{
		return -1;
	}

	if (Vector->Count >= Vector->Size)
	{
		/// REALLOC
		int* Array = (int*)realloc(Vector->Array, (INITIAL_VECTOR_SIZE + Vector->Count) * sizeof(int));
		if (NULL == Array)
		{
			return -1;
		}
		Vector->Size = INITIAL_VECTOR_SIZE + Vector->Count;
		Vector->Array = Array;
	}

	for (int i = Vector->Count - 1; i >= 0; i--)
	{
		Vector->Array[i + 1] = Vector->Array[i];
	}
	Vector->Array[0] = Value;
	Vector->Count++;

	return 0;
}

//Insert Value after given index.
int VecInsertAfterIndex(CC_VECTOR* Vector, int Index, int Value)
{
	if (NULL == Vector)
	{
		return -1;
	}

	if (Index < 0)
	{
		return -1;
	}

	if (Vector->Count >= Vector->Size)
	{
		/// REALLOC
		int* Array = (int*)realloc(Vector->Array, (INITIAL_VECTOR_SIZE + Vector->Count) * sizeof(int));
		if (NULL == Array)
		{
			return -1;
		}

		Vector->Size = INITIAL_VECTOR_SIZE + Vector->Count;
		Vector->Array = Array;
	}

	for (int i = Vector->Count - 1; i > Index; --i)
	{
		Vector->Array[i + 1] = Vector->Array[i];
	}
	Vector->Array[Index + 1] = Value;
	Vector->Count++;

	return 0;
}

//Remove value from Index.
int VecRemoveByIndex(CC_VECTOR* Vector, int Index)
{
	if (NULL == Vector)
	{
		return -1;
	}
	if (Index >= Vector->Count || Index < 0)
	{
		return -1;
	}

	for (int i = Index + 1; i < Vector->Count; ++i)
	{
		Vector->Array[i - 1] = Vector->Array[i];
	}
	--Vector->Count;

	return 0;
}

//Save the value from Index into the parameter Value.
int VecGetValueByIndex(CC_VECTOR* Vector, int Index, int* Value)
{
	if (NULL == Vector)
	{
		return -1;
	}
	if (Index > Vector->Count || Index < 0)
	{
		return -1;
	}
	*Value = Vector->Array[Index];
	return 0;
}

int VecGetCount(CC_VECTOR* Vector)
{
	if (NULL == Vector)
	{
		return -1;
	}

	return Vector->Count;
}

int VecClear(CC_VECTOR* Vector)
{
	if (NULL == Vector)
	{
		return -1;
	}

	Vector->Count = 0;
	return 0;
}

int BinarySearch(int* Array, int Item, int Low, int High)
{
	///Search for Item in Array and return it's position.
	if (High <= Low)
		return (Item < Array[Low]) ? (Low + 1) : Low;

	int mid = (Low + High) / 2;
	if (Item == Array[mid])
		return mid + 1;

	if (Item > Array[mid])
		return BinarySearch(Array, Item, Low, mid - 1);
	return BinarySearch(Array, Item, mid + 1, High);
}

//Sort vector (ascending).
int VecSort(CC_VECTOR* Vector)
{
	///Binary insertion sort.
	if (NULL == Vector)
	{
		return -1;
	}

	for (int i = 0; i < Vector->Count; ++i)
	{
		int j = i - 1;
		int item = Vector->Array[i];

		int pos = BinarySearch(Vector->Array, item, 0, j);  ///The elements from 0 to i-1 are alreaady sorted.
		for (; j >= pos; --j)
		{
			Vector->Array[j + 1] = Vector->Array[j];
		}

		Vector->Array[pos] = item;  ///Insert the element in the corresponding position.
	}

	return 0;
}

int VecAppend(CC_VECTOR* DestVector, CC_VECTOR* SrcVector)
{
	if (NULL == DestVector || NULL == SrcVector)
	{
		return -1;
	}

	///Append SrcVector to the end of DestVector
	for (int i = 0; i < SrcVector->Count; ++i)
	{
		int Value = SrcVector->Array[i];
		VecInsertTail(DestVector, Value);
	}

	return 0;
}
