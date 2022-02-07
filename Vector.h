#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>

using namespace std;
template <typename T> class vectorClass
{

	///**<   vArray is the generic pointer that stores the address of the vector */
	T* vArray;

	///**< capacity is the total storage capacity of the vector
	int Capacity;

	///**< current is the number of elements currently present in the vector
	int Current;

public:

    /** \brief Default construcutor
     * This is used to give a default capacity of the dynamic class array.
     * This allocation is done using dynamic allocation.
     *
     */

	vectorClass()
	{
		vArray = new T[1];
		Capacity = 1;
		Current = 0;
	}

    /** \brief Copy Constructor
     *This is the copy constructor of the vector class. This is used to set
     * the current vector equal to an existing vector by copying its capacity(max number of components)
     * current size and the contents of dynamic array.
     * \param vectorclass object v passed by reference
     *
     */


	vectorClass(vectorClass &v)
	{
		Capacity = v.Capacity;
		Current = v.Current;
		vArray = new T[Capacity];
		for (int i = 0; i < Capacity; i++) {
			vArray[i] = v.vArray[i];
		}
	}

    /** \brief Increase the size of Dynamic array
     * When the capacity(max number of elements) becomes equal to current(current number of elements)
     * then is function comes into play and thus increases the capacity 2 times the original capacity.
     * After that the copy constructor copies all the data from the old array into the new array.
     * Then after doing this, the function deletes the old array.
     *\param Tempelate typename T
     *\return void
     *
     */
	void push(T data)
	{
        /**<  Loop tp check whether the array has reached its maximum capacity */
		if (Current == Capacity) {
			T* temp = new T[2 * Capacity];

			/**<  copying old array elements to new array*/
			for (int i = 0; i < Capacity; i++) {
				temp[i] = vArray[i];
			}

			///* deleting previous array */
			delete[] vArray;
			Capacity *= 2;
			vArray = temp;
		}

		///* Inserting data*/
		vArray[Current] = data;
		Current++;
	}

    /** \brief Add element
     * This function is used to insert/add element at any index
     * \param int data
     * \param int index
     * \return void
     *
     */

	void push(int data, int index)
	{

		/**< First it checks if the index specified is equal to the capacity of the array
		 If Yes, then it calls the push function to increase capacity. Otherwise it just inputs data on the speicified location.*/

		if (index == Capacity)
			push(data);
		else
			vArray[index] = data;
	}

    /** \brief Get object
     * This function is responsible for getting/extracting the data
     * on the specified index. The function also checks if the asked value
     * lies within the capacity.
     * \param int index
     * \return Vector data on specified index
     *
     */

	T get(int index)
	{

		/**< checking if the index is in the defined range. */
		if (index < Current)
			return vArray[index];
	}


	// Overload operator [] to get and set the values
	T& operator [](int index) {

		// if index is within the range
		if (index < Current)
			return vArray[index];
	}

    /** \brief Deleting the last object.
     *  Function is responsible for deleting the last element of the array
     * Also this is a single line function that makes it more efficient.
     * \return void
     *
     */
	void pop() { Current--; }

    /** \brief Returns size of array
     *  This function returns the size of the array in a form of an integer that is the total number of entries that have
	 *  data inside them. Single line function for improved efficiency.
     * \return int
     */
	int size() { return Current; }

    /** \brief Get max capacity of dynamic array.
     *  function to get capacity of the vector. Single file function to improve efficiency
     * \return int
     */
	int getcapacity() { return Capacity; }

    /** \brief print all elements of array
     *  function to print all the contents/elements of the dynamic array.
     * \return void
     */
	void print()
	{
		for (int i = 0; i < Current; i++) {
			cout << vArray[i] << " ";
		}
		cout << endl;
	}
};

#endif // VECTOR_H
