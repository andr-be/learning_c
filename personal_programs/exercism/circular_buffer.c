// CIRCULAR BUFFER
// andr-be 08/2023
/*
    Exercism challenge to create a circular buffer with fixed capacity.
    Not well designed, had to steal all the function headers from a
    community solution because none are provided but many are expected.

    TODO: Need to rewrite new_circular_buffer to return a pointer 
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef int buffer_value_t;
typedef struct circular_buffer_t {
    int capacity;
    int count;
    int head;
    int tail;
    buffer_value_t buffer[];
} circular_buffer_t;

circular_buffer_t *new_circular_buffer(int capacity);
void clear_buffer(circular_buffer_t *buffer);
void delete_buffer(circular_buffer_t *buffer);
int write(circular_buffer_t *buffer, buffer_value_t value);
int overwrite(circular_buffer_t *buffer, buffer_value_t value);
int read(circular_buffer_t *buffer, buffer_value_t *value);

int main(void)
{
    circular_buffer_t *b = new_circular_buffer(3);

    // reading empty buffer
    int read_ret;
    read(b, &read_ret);
    printf("Read: %d\n", read_ret);

    // writing one value
    printf("Write 13: %s\n", (write(b, 13) == EXIT_SUCCESS) ? "SUCCESS" : "FAILURE");

    // clearing buffer
    printf("CLEARING BUFFER\n");
    clear_buffer(b);

    // reading cleared buffer
    read(b, &read_ret);
    printf("Read: %d\n", read_ret);

    return EXIT_SUCCESS;
}

circular_buffer_t *new_circular_buffer(int capacity)
{
    circular_buffer_t *new_buff = calloc(1, sizeof(circular_buffer_t) + ((size_t) capacity * sizeof(buffer_value_t)));
    
    new_buff->capacity = capacity;
    clear_buffer(new_buff);
    return new_buff;
}

void clear_buffer(circular_buffer_t *buffer)
{
    for (int i = 0; i < buffer->capacity; i++)
        buffer->buffer[i] = 0;

    buffer->count = buffer->head = buffer->tail = 0;
}

void delete_buffer(circular_buffer_t *buffer)
{
    free(buffer);
}

int write(circular_buffer_t *buffer, buffer_value_t value)
{
    if (buffer->count >= buffer->capacity) {
        errno = ENOBUFS;
        return EXIT_FAILURE;
    }

    buffer->buffer[buffer->head] = value;
    buffer->head = (buffer->head + 1) % (buffer->capacity);
    buffer->count++;
    return EXIT_SUCCESS;
}

int overwrite(circular_buffer_t *buffer, buffer_value_t value)
{
    if (buffer->count < buffer-> capacity) return write(buffer, value);
    
    buffer->buffer[buffer->tail] = value;
    buffer->tail = (buffer->tail + 1) % (buffer->capacity);
    return EXIT_SUCCESS;
}

int read(circular_buffer_t *buffer, buffer_value_t *value)
{
    if (buffer->count < 1) {
        errno = ENODATA;
        *value = EXIT_FAILURE;
        return EXIT_FAILURE;
    }
    
    *value = buffer->buffer[buffer->tail];
    buffer->tail = (buffer->tail + 1) % (buffer->capacity);
    buffer->count--;
    return EXIT_SUCCESS;
}
