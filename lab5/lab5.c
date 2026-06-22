#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;

  while (current != NULL) {
    if (current->size >= size) {
      return current->id;
    }

    current = current->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  uint64_t best_fit_size = 0;

  struct header *current = free_list_ptr;

  while (current != NULL) {
    if (current->size >= size) {
      if (best_fit_id == -1 || current->size < best_fit_size) {
        best_fit_id = current->id;
        best_fit_size = current->size;
      }
    }
    current = current->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  uint64_t worst_fit_size = 0;

  struct header *current = free_list_ptr;

  while (current != NULL) {
    if (current->size >= size) {
      if (worst_fit_id == -1 || current->size > worst_fit_size) {
        worst_fit_id = current->id;
        worst_fit_size = current->size;
      }
    }
    current = current->next;
  }
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  free(free_block1);
  free(free_block2);
  free(free_block3);
  free(free_block4);
  free(free_block5);

  return 0;
}

//  Part 2: Coalescing Contiguous Free Blocks
//
//  Algorithm: When a block is freed, check if the blocks directly before or
//  after it in memory are also free.
//
//  1. Find the block right before the newly freed block in memory.
//
//  2. Find the block right after the newly freed block in memory.
//
//  3. Check the free list to see if those blocks are already free.
//
//  4. If both the previous and next blocks are free, merge the previous block,
//  newly freed block, and next block into one bigger block. Then update the
//  free list so it only keeps the new bigger block.
//
//  5. If only the previous block is free, merge the newly freed block into the
//  previous block.
//
//  6. If only the next block is free, merge the next block into the newly freed
//  block. Then update the free list so the newly freed block replaces the next block.
//
//  7. If neither block is free, add the newly freed block into the free list by itself.
//
