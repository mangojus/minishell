#include "libmem.h"

bool	ft_grow_vec(t_arr *arr, size_t value_size)
{
	int		new_capacity;

	if (arr->data == NULL)
		new_capacity = 16 * value_size;
	else
		new_capacity = arr->capacity * value_size * 2;
	arr->data = ft_realloc(arr->data, new_capacity, arr->capacity * value_size);
	if (!arr->data)
		return (false);
	arr->capacity = new_capacity / value_size;
	return (true);
}

bool	ft_push_value(t_arr *arr, void *value, size_t value_size)
{
	if (arr->size == arr->capacity)
	{
		if (!ft_grow_vec(arr, value_size))
			return (false);
	}
	ft_memmove(arr->data + (arr->size * value_size), value, value_size);
	arr->size++;
	return (true);
}
