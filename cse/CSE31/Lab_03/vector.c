/* Include the system headers we need */
#include <stdlib.h>
#include <stdio.h>

/* Include our header */
#include "vector.h"

/* Define what our struct is */
struct _vector_t {
	size_t size;
	int *data;
};

/* Create a new vector */
vector_t *vector_new() {
	vector_t *retval;

	/* First, we need to allocate the memory for the struct */
	retval = (vector_t *)malloc(1 * sizeof(vector_t));

	/* Check our return value to make sure we got memory */
	if(retval == NULL)
		return NULL;

	/* Why does the above statement cast the malloc's return value to 'vector_t *'
	 * instead of 'struct _vector_t *'?  Does it matter?
	 */

	/* Now we need to initialize our data */
	retval->size = 1;
	retval->data = (int *)malloc(retval->size * sizeof(int));

	/* Check our return value to make sure we got memory */
	if(retval->data == NULL) {
		free(retval);
		return NULL;
	}

	retval->data[0] = 0;

	/* Note that 'retval->size' could be written '(*retval).size', but the ->
	 * convention is easier to read
	 */

	/* and return... */
	return retval;
}

/* Free up the memory allocated for the passed vector */
void vector_delete(vector_t *v) {
	/* Remember, you need to free up ALL the memory that is allocated */





	/* ADD CODE HERE */

	free(v->data);
	free(v);


}

/* Return the value in the vector */
int vector_get(vector_t *v, size_t loc) {

	/* If we are passed a NULL pointer for our vector, complain about it and
	 * return 0.
	 */
	if(v == NULL) {
		fprintf(stderr, "vector_get: passed a NULL vector.  Returning 0.\n");
		return 0;
	}

	/* If the requested location is higher than we have allocated, return 0.
	 * Otherwise, return what is in the passed location.
	 */
	if(loc < v->size) {
		return v->data[loc];
	} else {
		return 0;
	}
}

/* Set a value in the vector */
void vector_set(vector_t *v, size_t loc, int value) {
	/* What do you need to do if the location is greater than the size we have
	 * allocated?  Remember that unset locations should contain a value of 0.
	 */



	/* ADD CODE HERE */


	if (loc < v->size) //if location is fine
	{
		v->data[loc] = value;
	}
	else  //if location is greater, copy the values from old array into new one
	{
		int* temp = (int*)malloc((loc + 1) * sizeof(int));
		int i;

		//copying the old values into a new array, which also has an extra space for the new index
		for(int i = 0; i < v->size; i++)
		{
			temp[i] = v->data[i];
		}

		temp[loc] = value; //assigning value to newly added index.

		//free old data that v was pointing to

		free(v->data);

		v->data = temp; //points to beginning of temp.
		v->size = loc + 1; //increment size by 1.
	}


}
