#include "Header.h"

// First fit algorithm starts search at the beginning of the list and allocates the first hole
// large enough to accommodate the request. Function returns the number of holes examined.
int firstFit(int request_size, int *memory, int n, int *mem_index){
    
    // Declare holes_examined and initialize to 0.
    int holes_examined = 0;
    
    // Hold the size of the space being evaluated.
    int hold_size = 0;
    
    // Iterate through 'memory' searching for the first hole available for the given request size.
    for(int i = 0; i < n; i++){
        
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
        
        // If the hole is usable, examine the hole size.
        else if(memory[i] < 0 && memory[i] != -1 && memory[i+1] >= 0){
            
            // Increment holes_examined on each hole evalutaion.
            holes_examined += 1;

            // Get the absolute value of the hole size.
            hold_size = (memory[i] * -1);
            
//TODO: v
printf(PINK "\tChecking: Block [%d] ", i);
printf(RESET);
if((i - 10) >= 0){
    printf(PINK " |  Size: %d\n", hold_size);
    printf(RESET);
}
            
else{
    printf(PINK "  |  Size: %d\n", hold_size);
    printf(RESET);
}
//sleep(2);
            
            // If the hole can fit the request, save the starting index of the hole and break.
            if(hold_size >= request_size){
                *mem_index = i;
                
//TODO: v
printf(YELLOW "Block [%d] chosen.\n", i);
printf(RESET);
//sleep(2);
                
                break;
            }
            
            // Else, advance i past this hole and continue the search.
            else{
                i = advance(memory, n, i, false, true, false);
                continue;
            }
        }
    }
    
    return holes_examined;
}

// Best fit algorithm searches the entire list and chooses the smallest hole large enough to
// accommodate the request. Function returns the number of holes examined.
int bestFit(int request_size, int *memory, int n, int *mem_index){

    // Declare holes_examined and initialize to 0.
    int holes_examined = 0;
    
    // Hold the size of the space being evaluated.
    int hold_size = 0;
    
    // Hold the index of a space being evaluated.
    int hold_index = -1;
    
    // Hold the current difference of the hole size evaluated minus the request size.
    // Initialize to a sentinel value, -1.
    int this_difference = -1;
    
    // Hold the smallest difference calculated between hole size and request size.
    // Initialize to a number larger than any n given.
    int saved_difference = 2000000000;
    
    // Iterate through 'memory' searching for the best hole available for the given request size.
    for(int i = 0; i < n; i++){
        
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
        
        // If the hole is usable, examine the hole size.
        else if(memory[i] < 0 && memory[i] != -1 && memory[i+1] >= 0){
            
            // Increment holes_examined on each hole size evalutaion.
            holes_examined += 1;

            // Get the absolute value of the hole size.
            hold_size = (memory[i] * -1);

//TODO: v
printf(PINK "\tChecking: Block [%d] ", i);
printf(RESET);
if((i - 10) >= 0){
    printf(PINK " |  Size: %d\n", hold_size);
    printf(RESET);
}
            
else{
    printf(PINK "  |  Size: %d\n", hold_size);
    printf(RESET);
}
//sleep(2);
            
            // If the hole can fit the request, get the difference between hole size and request size.
            if(hold_size >= request_size){
                this_difference = hold_size - request_size;

                // If this difference is less than the last saved difference, update this_difference
                // and advance past this hole to continue the search.
                if(this_difference < saved_difference && this_difference >= 0){
                    saved_difference = this_difference;
                    hold_index = i;
                    i = advance(memory, n, i, false, true, false);
                    continue;
                }
                
                // Else, if this difference is not less than the last saved difference, just advance
                // past this hole to continue the search.
                else{
                    i = advance(memory, n, i, false, true, false);
                    continue;
                }
            }
            
            // Else, if the hole size is less than the request size, advance i past this hole and
            // continue the search.
            else{
                i = advance(memory, n, i, false, true, false);
                continue;
            }
        }
    }

//TODO: v
if(hold_index >= 0){
    hold_size = (memory[hold_index] * -1);
    *mem_index = hold_index;
    
//TODO: v
printf(YELLOW "Block [%d] chosen.\n", hold_index);
printf(RESET);
//sleep(2);
    
}

    return holes_examined;
}

// Worst fit algorithm chooses the largest available hole for any request.
// Function returns the number of holes examined.
int worstFit(int request_size, int *memory, int n, int *mem_index){

    // Declare holes_examined and initialize to 0.
    int holes_examined = 0;
    
    // Hold the size of the space being evaluated.
    int hold_size = 0;
    
    // Hold the index of a space being evaluated.
    int hold_index = 0;
    
    // Hold the maximum size evaluated.
    int max_size = 0;
    
    // Iterate through 'memory' searching for the largest hole available for the given request size.
    for(int i = 0; i < n; i++){
        
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
        
        // If the hole is usable, examine the hole size.
        else if(memory[i] < 0 && memory[i] != -1 && memory[i+1] >= 0){
            
            // Increment holes_examined on each hole size evalutaion.
            holes_examined += 1;

            // Get the absolute value of the hole size.
            hold_size = (memory[i] * -1);
            
//TODO: v
printf(PINK "\tChecking: Block [%d] ", i);
printf(RESET);
if((i - 10) >= 0){
    printf(PINK " |  Size: %d\n", hold_size);
    printf(RESET);
}
            
else{
    printf(PINK "  |  Size: %d\n", hold_size);
    printf(RESET);
}
//sleep(2);
            
            // If the size of the hole is greater than the last size saved, max_size = hole size,
            // save the index of this hole, and advance past it to continue the search.
            if(hold_size > max_size){
                max_size = hold_size;
                hold_index = i;
                i = advance(memory, n, i, false, true, false);
                continue;
            }
            
            // Else if the size of the hole is less than the last size saved, just advance i past this
            // hole and continue the search.
            else{
                i = advance(memory, n, i, false, true, false);
                continue;
            }
        }
    }
    
    // If the maximum sized hole can fit the request, save the index of the hole and break.
    if(max_size >= request_size){
        *mem_index = hold_index;
    }
    
//TODO: v
if(*mem_index >= 0){
    printf(YELLOW "Block [%d] chosen.\n", hold_index);
    printf(RESET);
    //sleep(2);
}
        
    return holes_examined;
}
