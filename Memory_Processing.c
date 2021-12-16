#include "Header.h"

// Update space from a hole to an allocated block, and update the remainder of the hole, if any.
int request(int request_size, int *memory, int n, int *mem_index, int *last_allocated, int choice){

    // Used for holding the number of holes examined by an algorithm.
    int holes_examined = 0;
    
    // Initialize mem_index to a sentinel value, -1.
    *mem_index = -1;
    
//TODO: v
printf(YELLOW "\nRequesting block of size %d.\n", request_size);
printf(RESET);
//sleep(2);
    
    /* Algorithms here. Algorithm functions return the number of holes examined per request. */
    
    // FIRST FIT
    if(choice == 1) holes_examined = firstFit(request_size, memory, n, mem_index);
                                                                                      
    // BEST FIT
    else if(choice == 2) holes_examined += bestFit(request_size, memory, n, mem_index);
    
    // WORST FIT
    else if(choice == 3) holes_examined = worstFit(request_size, memory, n, mem_index);

//TODO: v
if(*mem_index == -1){
    printf(MAGENTA "\n(!) MEMORY UNAVAILABLE (!)\n");
    printf(RESET);
//    sleep(2);
    if(n == 50) printMemory(memory, n, "request");
}
    
    // If an appropriate hole was found, update space from hole to allocated block, and update
    // the remainder of the hole, if any.
    if(*mem_index >= 0){
        
        // Get the absolute value of the hole size.
        int hold_size = (memory[*mem_index] * -1);
        
        // Update the first size index of this space to reflect the request size.
        memory[*mem_index] = request_size;
        
        // Set the second size index of this space to the same value.
        // Second size index is located at the end of this newly allocated space.
        int set_last = (*mem_index + request_size + 1);
        memory[set_last] = request_size;
        
        // Zero out the inside of the allocated block to remove any possible previous or next links
        // that may have been left behind by the hole.
        for(int i = *mem_index+1; i < set_last; i++){
            memory[i] = 0;
        }
        
        // Check if the request size is less than or equal to the hole size. If so, update the hole.
        if(request_size <= hold_size){
            
            // Get the total blocks left behind when the hole was filled by the allocated space.
            int difference = (hold_size + 2) - (request_size + 2);
        
            // If the total blocks left are less than 4, the hole is not usable.
            // Set all indices of the unsable hole to the negative value of its total indices.
            // These holes will be skipped when updating hole links to next and previous.
            if(difference < 4){
                if(difference == 1){
                    memory[set_last+1] = -1;
                }
                
                if(difference == 2){
                    memory[set_last+1] = -2;
                    memory[set_last+2] = -2;
                }
                
                if(difference == 3){
                    memory[set_last+1] = -3;
                    memory[set_last+2] = -3;
                    memory[set_last+3] = -3;
                }
            }
            
            // If the difference is greater than or equal to 4, update the hole as normal.
            // A difference of 4 means the hole is not usable, but it will be treated as allocated
            // when advancing past it.
            if(difference >= 4){
                hold_size = (difference - 2);
                memory[set_last+1] = (hold_size * -1);
                memory[set_last+1+hold_size+1] = (hold_size * -1);
            }
            
// TODO: v
if(n == 50) printMemory(memory, n, "resulting");
            
            // Coalesce any unusable holes that were created.
            // coalesce() also updates the next and previous links for all holes.
            coalesce(memory, n);
        }
    }

    return holes_examined;
}

// Update space from allocated block to a hole.
void release(int release_block, int *memory, int n){

    // Once an allocated block has been specified for release, update the space from an allocated
    // block to a hole by redefining its size indices.
    
    // Get the value of the allocated block size.
    int hold_size = memory[release_block];
    
    // Get the last index of this block.
    int set_last = (release_block + hold_size + 1);
        
//TODO: v
printf(GREEN "Releasing: Block [%d] | Size: %d\n", release_block, hold_size);
printf(RESET);
//sleep(2);
    
    // Set the value of the size as negative.
    memory[release_block] = (hold_size * -1);
    
    // Set the last index as the same negative size value as the first.
    memory[set_last] = (hold_size * -1);

// TODO: v
if(n == 50) printMemory(memory, n, "release");
    
    // Coalesce any other possible neighboring holes.
    // coalesce() also updates the next and previous links for all holes.
    coalesce(memory, n);
}

// Coalesce all possible neighboring holes, if any.
void coalesce(int *memory, int n){
    
    // Hold the size of the space being evaluated.
    int hold_size = 0;
    
    // Hold the index of a space being evaluated.
    int hold_index = 0;
    
    // Booleans to help determine the usability of an evaluated neighboring hole.
    bool has_neighbor = false;
    bool neighbor_usable = false;
    bool neighbor_UNusable = false;
    
    // Iterate through 'memory'.
    for(int i = 0; i < n; i++){

        if(i >= (n-1)) break;
        
        // Advance to the end of allocated blocks.
        if(memory[i] > 0){
            i = advance(memory, n, i, true, false, false);
            continue;
        }
        
        // Else, if encountering a hole, search for neighboring holes, if any.
        else if(memory[i] < 0){
            
            // Reset neighbor-identifying booleans.
            has_neighbor = false;
            neighbor_usable = false;
            neighbor_UNusable = false;
            
            // Save the starting index of this hole.
            hold_index = i;
            
            // Get the absolute value of the hole size.
            hold_size = (memory[i] * -1);

            // Advance to the last index of an unusable hole.
            if(memory[i] == -1 || (memory[i] < 0 && memory[i+1] == memory[i])){
                i = advance(memory, n, i, false, false, true);
            }
            
            // Advance to the last index of a usable hole.
            else if(memory[i+1] >= 0){
                i = advance(memory, n, i, false, true, false);
            }

            // Check if the next space is also a hole. If so, has_neighbor = true, and advance i
            // to the start of the next hole.
            if(i < (n-1) && memory[i+1] < 0){
                
                has_neighbor = true;
                i += 1;

                // If neighbor is UNusable, set neighbor_UNusable to true.
                if(memory[i] == -1) neighbor_UNusable = true;
                
                else if(i < (n-1) && (memory[i] < 0 && memory[i+1] == memory[i])){
                    neighbor_UNusable = true;
                }
                
                // Else, if neighbor is usable, set neighbor_usable to true.
                else if(i < (n-1) && (memory[i] != -1 && memory[i] < 0 && memory[i+1] >= 0)){
                    neighbor_usable = true;
                }
            }

            // If the hole has as a neighbor, combine the neighboring holes.
            if(has_neighbor){
                
                // Start the following for-loop at the first index of the neighboring hole.
                int starting_point = i;
                 
                // Continue to combine other neighboring holes, if any.
                for(int y = starting_point; y < n; y++){
                    
//TODO: v
int this_size = memory[y] * -1;
printf(PURPLE "\nCoalesce: (Hole [%d] | Size: %d) + (Hole [%d] | Size: %d)\n", hold_index, hold_size, y, this_size);
printf(RESET);
     
                    /* Combine neighboring hole sizes. */
                    /* Process will be different depending on the usablility of the holes. */
                    
                    // Coalesce two unusable holes.
                    if(memory[hold_index] == -1){
                        if(neighbor_UNusable == true && (memory[y] == -1 || memory[y] == -2)){
                            hold_size += (memory[y] * -1);
                        }
                           
                        else if(neighbor_UNusable == true && memory[y] == -3){
                            hold_size += 1;
                        }
                    }
                    
                    else if(memory[hold_index] == -2 && memory[hold_index+1] == -2){
                        if(neighbor_UNusable == true && memory[y] == -1){
                            hold_size += (memory[y] * -1);
                        }
                          
                        else if(neighbor_UNusable == true && memory[y] == -2){
                            hold_size = 2;
                        }
                        
                        else if(neighbor_UNusable == true && memory[y] == -3){
                            hold_size += 1;
                        }
                    }

                    else if(memory[hold_index] == -3 && memory[hold_index+1] == -3){
                        if(neighbor_UNusable == true && memory[y] == -1){
                            hold_size = 2;
                        }
                          
                        else if(neighbor_UNusable == true && memory[y] == -2){
                            hold_size = 3;
                        }
                        
                        else if(neighbor_UNusable == true && memory[y] == -3){
                            hold_size = 4;
                        }
                    }

                    // Coalesce an unusable hole with a usable hole.
                    if(memory[hold_index] == -1 || (memory[hold_index] < 0 && memory[hold_index+1] == memory[hold_index])){
                        if(neighbor_usable == true) hold_size += (memory[y] * -1);
                    }

                    // Coalesce two usable holes, or a usable hole with an unusable hole.
                    if(memory[hold_index] != -1 && (memory[hold_index] < 0 && memory[hold_index+1] >= 0)){
                        
                        // Coalesce two usable holes.
                        if(neighbor_usable == true) hold_size += (memory[y] * -1) + 2;
                        
                        // Coalesce a usable hole with an unusable hole.
                        else if(neighbor_UNusable == true) hold_size += (memory[y] * -1);
                    }
        
                    // Update the first size index of this newly combined hole.
                    memory[hold_index] = (hold_size * -1);

                    if(neighbor_usable) y = advance(memory, n, y, false, true, false);
                    else if(neighbor_UNusable) y = advance(memory, n, y, false, false, true);

                    memory[y] = (hold_size * -1);

                    // If this hole is unusable and is consuming other unusable holes, and the resulting
                    // size is -3, set the inside of the hole to -3 as well.
                    if(memory[hold_index] == -3 && memory[y+2] == -3){
                        memory[hold_index+1] = -3;
                    }
                    
                    // Else, zero out all values inside the new hole except for the indices holding hole
                    // size. Next and previous links for the entire new hole will be reset.
                    else for(int j = (hold_index+1); j < y; j++) memory[j] = 0;
                    
                    // Reset neighbor-identifying booleans.
                    has_neighbor = false;
                    neighbor_usable = false;
                    neighbor_UNusable = false;
                    
                    if(y >= (n-1)) break;
                    
                    // If the next block is not a hole, this hole has no neighbor. Advance i
                    // appropriately, and break from this inner for-loop.
                    else if(y < (n-1) && memory[y+1] >= 0){
                        i = y;
                        break;
                    }

                    // Else, if there is another neighbor, coalesce again.
                    else if(y < (n-1) && memory[y+1] < 0){
                         
                        has_neighbor = true;
                        
                        // If neighbor is UNusable, set neighbor_UNusable to true.
                        if(y < (n-1) && memory[y+1] == -1){
                            neighbor_UNusable = true;
                            continue;
                        }
                         
                        else if(y < (n-2) && (memory[y+1] < 0 && memory[y+2] == memory[y+1])){
                            neighbor_UNusable = true;
                            continue;
                        }
                         
                        // Else, if neighbor is usable, set neighbor_usable to true.
                        else if(y < (n-2) && (memory[y] != -1 && memory[y+1] < 0 && memory[y+2] >= 0)){
                            neighbor_usable = true;
                            continue;
                        }
                    }
                }

// TODO: v
if(n == 50) printMemory(memory, n, "coalesce");
                
            }
        }
    }
    
    // After all coalescing of neighboring holes is complete, call getNextAndPrev() to update
    // all links to next and previous holes.
//    getNextAndPrev(memory, n);

// TODO: v
tempFunc(memory, n);
    
}

// TODO: DELETE
void tempFunc(int *memory, int n){
    
//TODO: v
printf(CYAN "\nSet next and previous links for each hole.\n");
printf(RESET);
    
    for(int i = 0; i < n; i++){
        
        if(i > (n-5)) break;
        
        // Advance past allocated blocks.
        if(memory[i] > 0){
            i = advance(memory, n, i, true, false, false);
            continue;
        }
        
        // Advance past unusable holes.
        else if(memory[i] == -1 || (memory[i] < 0 && memory[i+1] == memory[i])){
            i = advance(memory, n, i, false, false, true);
            continue;
        }
        
        // If the hole is usable...
        else if(memory[i] < -1 && memory[i+1] >= 0){
            memory[i+1] = 99;
            memory[i+2] = 99;
            i = advance(memory, n, i, false, true, false);
            continue;
        }
    }
    
// TODO: v
if(n == 50) printMemory(memory, n, "getNextAndPrev");
    
}

// Set the next and previous links for all holes.
void getNextAndPrev(int *memory, int n){

//TODO: v
printf(CYAN "\nSet next and previous links for each hole.\n");
printf(RESET);
    
    // Variables to keep track of the first, second, previous, and last holes.
    int first_hole = 0;
    int second_hole = 0;
    int previous_hole = 0;
    int last_hole = 0;
    
    // For specifying a starting point.
    int starting_point = 0;
    
    // Hold the index of a space being evaluated.
    int hold_index = 0;
    
    // Find the first hole.
    for(int i = 0; i < n; i++){
        
        // Advance past allocated blocks.
        if(memory[i] > 0){
            i = advance(memory, n, i, true, false, false);
            continue;
        }
        
        // Advance past unusable holes.
        else if(memory[i] == -1 || (memory[i] < 0 && memory[i+1] == memory[i])){
            i = advance(memory, n, i, false, false, true);
            continue;
        }

        // If this hole is usable, set it as the first hole and break.
        else if(memory[i] < -1 && memory[i+1] >= 0){
            first_hole = i;
            hold_index = first_hole + (memory[first_hole] * -1) + 1;
            break;
        }
    }
    
    // Find the second hole starting at the first index after the end of the first hole.
    for(int i = hold_index+1; i < n; i++){
        
        // Advance past allocated blocks.
        if(memory[i] > 0){
            i = advance(memory, n, i, true, false, false);
            continue;
        }
        
        // Advance past unusable holes.
        else if(memory[i] == -1 || (memory[i] < 0 && memory[i+1] == memory[i])){
            i = advance(memory, n, i, false, false, true);
            continue;
        }
        
        // If this hole is usable, set it as the second hole and break.
        else if(memory[i] < -1 && memory[i+1] >= 0){
            second_hole = i;
            break;
        }
    }
    
    // Set first hole's 'next' link = to second hole.
    memory[first_hole+2] = second_hole;
    
    // Initialize previous_hole to first_hole.
    previous_hole = first_hole;
    
    // Start the following for-loop at the second hole. If no second hole, start at the first hole.
    if(second_hole > 0) starting_point = second_hole;
    else starting_point = first_hole;
    
    // Iterate through 'memory' searching for usable holes.
    for(int i = starting_point; i < n; i++){
            
        // If i reaches past the minimum size of usable space, break from the for-loop.
        if(i > (n-5)) break;
        
        // Advance past allocated blocks.
        if(memory[i] > 0){
            i = advance(memory, n, i, true, false, false);
            continue;
        }
        
        // Advance past unusable holes.
        else if(memory[i] == -1 || (memory[i] < 0 && memory[i+1] == memory[i])){
            i = advance(memory, n, i, false, false, true);
            continue;
        }

        // If this hole is usable, set its next and previous links.
        else if(memory[i] <= -3 && memory[i+1] >= 0){

            // Set link to previous hole.
            memory[i+1] = previous_hole;
            
            // Save the index for this hole.
            int hold_index = i;
            
            // Advance i to the last index of this hole.
            i = advance(memory, n, i, false, true, false);

            // If there is room for another usable hole in 'memory', find the next hole.
            if((i+1) <= (n-5)){

                // Start the search at the next space after this hole.
                for(int j = (i+1); j < n; j++){

                    // Advance past allocated blocks.
                    if(memory[j] > 0){
                        j = advance(memory, n, j, true, false, false);
                        continue;
                    }
                    
                    // Advance past unusable holes.
                    else if(memory[j] == -1 || (memory[j] < 0 && memory[j+1] == memory[j])){
                        j = advance(memory, n, j, false, false, true);
                        continue;
                    }

                    // If the next hole found is usable, set this hole's next link and advance i.
                    else if(memory[j] <= -3 && memory[j+1] >= 0){
                        memory[hold_index+2] = j;
                        last_hole = j;
                        memory[last_hole+1] = previous_hole;
                        previous_hole = hold_index;
                        i = j;
                        break;
                    }
                }
            }
            
            // Else, if there is no room for another usable hole in 'memory', this is the last hole.
            else{
                last_hole = hold_index;
                break;
            }
        }
    }
    
    // Set previous link for the first hole, which equals the last hole.
    memory[first_hole+1] = last_hole;

    // Set next link for the last hole, which equals the first hole.
    memory[last_hole+2] = first_hole;
    
// TODO: v
if(n == 50) printMemory(memory, n, "getNextAndPrev");
    
}

// Get the value of total occupied space in the 'memory' array.
int getOccupiedSpace(int *memory, int n){
    
    // Keep count of all occupied indices in 'memory'.
    int occupied = 0;
    
    // Hold the size of the space being evaluated.
    int hold_size = 0;
    
    // Iterate through 'memory' to find occupied spaces.
    for(int i = 0; i < n; i++){
        
        // If i is greater than (n-4), there are no more allocated spaces to find.
        // Break from for-loop.
        if(i > (n-4)) break;
        
        // If this index represents an allocated block, add to 'occupied', and advance i to the
        // end of this allocated block to resume the search.
        if(memory[i] > 0){
            hold_size = memory[i];
            occupied += (hold_size + 2);
            i = advance(memory, n, i, true, false, false);
            continue;
        }
        
        // Else, if this index represents a hole, advance i past the hole.
        else if(memory[i] < 0){
            
            // Advance past a usable hole.
            if(memory[i] != -1 && memory[i+1] >= 0){
                i = advance(memory, n, i, false, true, false);
                continue;
            }
            
            // Advance past an unusable hole.
            else if(memory[i] == -1 || (memory[i] < 0 && memory[i+1] == memory[i])){
                i = advance(memory, n, i, false, false, true);
                continue;
            }
        }
    }
    
//TODO: v
printf(GREEN "\nOccupied Space: %d of %d\n", occupied, n);
printf(RESET);
//sleep(2);
    
    return occupied;
}

// Return the last index of either an allocated block, a usable hole, or an unusable hole.
int advance(int *memory, int n, int i, bool allocated, bool usable_hole, bool UNusable_hole){
    
    // Hold the size of the space being evaluated.
    int hold_size = 0;
    
    // Hold the index of the space being evaluated.
    int hold_index = 0;
    
    // Advance to the end of an allocated block.
    if(allocated){
        hold_size = memory[i];
        hold_index = i;
        i = (hold_index + hold_size + 1);
    }
    
    // Advance to the end of a usable hole.
    else if(usable_hole){
        hold_size = (memory[i] * -1);
        hold_index = i;
        i = (hold_index + hold_size + 1);
    }
    
    // Advance to the end of an unusable hole.
    else if(UNusable_hole){
        if(memory[i] == -1) return i;
        else if(memory[i] == -2 && memory[i+1] == -2) i += 1;
        else if(memory[i] == -3 && memory[i+1] == -3) i += 2;
    }
    
    return i;
}

// Compare all indices of allocated blocks to release_block.
int findAllocated(int release_block, int *memory, int n){

    // Declare and initialize a variable to hold the starting index that matches release_block.
    int found = -1;
    
    // Hold the size of the space being evaluated.
    int hold_size = 0;
    
    // Get the first size index of a memory space.
    int first_index = 0;
    
    /*
     The following if-statement cuts down time significantly when waiting for rand() to happen upon a
     starting index for an allocated block. Instead, if it lands inside an allocated block, release
     that block. If it lands inside a hole, check if the next space is allocated and release that block.
     */
    
    // If release_block points to an index inside of a memory space, determine whether the space is
    // a hole or an allocated block by getting the size from the last size index.
    if(memory[release_block] == 0){
        for(int i = release_block; i <= (n-1); i++){
            
            // If this space is allocated, get this size of the space from the last size index.
            if(memory[i] > 0){
                hold_size = memory[i];
                
                // Get the size of the space from the first size index.
                first_index = (i - hold_size -1);
                
                // If the size indices are a match, send this block as the block for release.
                if(memory[first_index] == memory[i]){
                    found = first_index;
                    return found;
                }
            }
            
            // Else, if still inside a space, continue looking for the last size index of this space.
            else if(memory[i] == 0) continue;
            
            // If this space is a hole, and there is room for allocated space next to it, and the next
            // space is indeed allocated, send that allocated block as the block for release.
            else if(i <= (n-6) && memory[i] < 0 && memory[i+1] > 0){
                found = (i+1);
                return found;
            }
            
            // Else, return -1.
            else return found;
        }
    }
    
    // Iterate through 'memory' looking for allocated blocks.
    for(int i = 0; i < n; i++){
        
        // If i reaches past the minimum size of usable space, break from the for-loop.
        if(i > (n-5)) break;
        
        // Compare and allocated block to release_block.
        if(memory[i] > 0){
            
            // If the starting index for this allocated block = release_block, send it for release.
            if(i == release_block){
                found = i;
                break;
            }
            
            // Else, if this allocated block does not = release_block, advance past this block.
            else{
                i = advance(memory, n, i, true, false, false);
                continue;
            }
        }
        
        // Advance past usable holes.
        else if(memory[i] != -1 && memory[i] < 0 && memory[i+1] >= 0){
            i = advance(memory, n, i, false, true, false);
            continue;
        }
        
        // Advance past unusable holes.
        else if(memory[i] == -1 || (memory[i] < 0 && memory[i+1] == memory[i])){
            i = advance(memory, n, i, false, false, true);
            continue;
        }
    }
    
    return found;
}

// Print contents of memory.
void printMemory(int *memory, int n, char *flag){
    
    /* Print different headers depending on the function from which printMemory() was called. */
    
    // Print starting memory with grey background color.
    if(strcmp(flag, "starting") == 0){
        printf("\n\n\t -------");
        printf(BACKGREY " STARTING MEMORY ");
        printf(RESET);
        printf("-------------------------------------------");
    }
    
    // Print resulting memory with yellow background color after block allocation or end of program.
    else if(strcmp(flag, "resulting") == 0){
        printf("\n\t -------");
        printf(BACKYELLOW " RESULTING MEMORY ");
        printf(RESET);
        printf("------------------------------------------");
    }
    
    // Print current memory with magenta background color when no memory is available for a request.
    else if(strcmp(flag, "request") == 0){
        printf("\n\t -------- ");
        printf(BACKMAGENTA " CURRENT MEMORY ");
        printf(RESET);
        printf("-------------------------------------------");
    }
    
    // Print current memory with green background color when releasing a block.
    else if(strcmp(flag, "release") == 0){
        printf("\n\t -------- ");
        printf(BACKGREEN " CURRENT MEMORY ");
        printf(RESET);
        printf("-------------------------------------------");
    }
    
    // Print current memory with purple background color after coalescing neighboring holes.
    else if(strcmp(flag, "coalesce") == 0){
        printf("\n\t -------- ");
        printf(BACKPURPLE " CURRENT MEMORY ");
        printf(RESET);
        printf("-------------------------------------------");
    }
    
    // Print current memory with X background color after setting next / previous links for each hole.
    else if(strcmp(flag, "getNextAndPrev") == 0){
        printf("\n\t -------- ");
        printf(BACKCYAN " CURRENT MEMORY ");
        printf(RESET);
        printf("-------------------------------------------");
    }
    
    // Print the contents of memory, including indices, evenly spaced within an ASCII box.
    printf("\n\t|                                                                   |");
    int width = 10;
    int bar_width = 4;
    char bar = '|';
    for(int x = 0; x < 10; x++){
        printf("\n\t|   %d [%d]", x, memory[x]);
        if((memory[x] > 0 && memory[x] > 9) || (memory[x] < 0 && memory[x] > -10)){
            width = 9;
        }
        else if(memory[x] < 0 && memory[x] < -9) width = 8;
        else width = 10;
        
        printf("%*d [%d]", width, (x+10), memory[x+10]);
        if((memory[x+10] > 0 && memory[x+10] > 9) || (memory[x+10] < 0 && memory[x+10] > -10)){
            width = 9;
        }
        else if(memory[x+10] < 0 && memory[x+10] < -9) width = 8;
        else width = 10;
        
        printf("%*d [%d]", width, (x+20), memory[x+20]);
        if((memory[x+20] > 0 && memory[x+20] > 9) || (memory[x+20] < 0 && memory[x+20] > -10)){
            width = 9;
        }
        else if(memory[x+20] < 0 && memory[x+20] < -9) width = 8;
        else width = 10;
        
        printf("%*d [%d]", width, (x+30), memory[x+30]);
        if((memory[x+30] > 0 && memory[x+30] > 9) || (memory[x+30] < 0 && memory[x+30] > -10)){
            width = 9;
        }
        else if(memory[x+30] < 0 && memory[x+30] < -9) width = 8;
        else width = 10;
        
        printf("%*d [%d]", width, (x+40), memory[x+40]);
        if((memory[x+40] > 0 && memory[x+40] > 9) || (memory[x+40] < 0 && memory[x+40] > -10)){
            bar_width = 3;
        }
        else if(memory[x+40] < 0 && memory[x+40] < -9) bar_width = 2;
        else bar_width = 4;
        
        printf("%*c\n", bar_width, bar);
        printf("\t|                                                                   |");
    }
    printf("\n\t -------------------------------------------------------------------\n");
    //sleep(2);
}
