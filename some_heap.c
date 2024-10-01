#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "some_heap.h"

#define KEY_NOT_PRESENT -1

heap_t *heap_create(int capacity) {
    heap_t *newHeap = (heap_t*)malloc(sizeof(heap_t));
    newHeap->data = (heap_node_t*)malloc(capacity * sizeof(heap_node_t));
    newHeap->size = 0;
    newHeap->capacity = capacity;
    return newHeap;
}

void heap_free(heap_t *heap) {
    if (heap == NULL) {return;}
    free(heap->data);
    free(heap);

}

unsigned int heap_size(heap_t *heap) { return heap->size; }

unsigned int heap_parent(unsigned int index) { return floor((index - 1) / 2); }

unsigned int heap_left_child(unsigned int index) { return (index * 2) + 1; }

unsigned int heap_right_child(unsigned int index) { return (index * 2) + 2; }

unsigned int heap_level(unsigned int index) { return floor(log2(index)); }

void heap_print(heap_t *heap, FILE* outputFile) {
    for (int ix = 0; ix < heap_size(heap); ix++) {
        fprintf(outputFile, "%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix,
               heap->data[ix].key);
    }
    fprintf(outputFile, "\n");
}

void heap_swap(heap_t *heap, int index1, int index2) {
    heap_node_t index_swap = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = index_swap;
}

void heap_bubble_up(heap_t *heap, int index) {
    while (index > 0) {
        if (heap->data[index].key >= heap->data[heap_parent(index)].key) {
            break;
        }
        heap_swap(heap, index, heap_parent(index));
        index = heap_parent(index);
    }
}

void heap_bubble_down(heap_t *heap, int index) {
    int smallest = index;
    if (heap_left_child(index) < heap->size &&
        heap->data[heap_left_child(index)].key  < heap->data[smallest].key) {
        smallest = heap_left_child(index);
    }
    if (heap_right_child(index) < heap->size &&
        heap->data[heap_right_child(index)].key  < heap->data[smallest].key) {
        smallest = heap_right_child(index);
    }
    if  (smallest != index) {
        heap_swap(heap,  index, smallest);
        heap_bubble_down(heap, smallest);
    }
}

void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data) {
    if (heap_size(heap) == heap->capacity) {
        return;
    }

    heap->data[heap_size(heap)].key = key;
    heap->data[heap_size(heap)].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}


heap_value_t heap_remove_min(heap_t *heap) {
    if (heap_size(heap) == 0) {
        return NULL;
    }

    heap_value_t min = heap->data[0].value;

    heap->size--;

    // move last element to the root
    heap->data[0] = heap->data[heap_size(heap)];

    // then bubble it down to its correct position
    heap_bubble_down(heap, 0);

    return min;
}
