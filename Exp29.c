#include <stdio.h>

#define STATE_SIZE 5
#define CAPACITY_LANES (2 * STATE_SIZE)
#define MAX_ITERATIONS 1000000

typedef struct {
    int lanes[STATE_SIZE][STATE_SIZE];
} InternalState;

// Function to check if all lanes in the capacity portion have at least one nonzero bit
int allCapacityLanesNonzero(InternalState state) {
    for (int i = 0; i < STATE_SIZE; i++) {
        for (int j = 0; j < CAPACITY_LANES; j++) {
            if (state.lanes[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

// Perform one iteration of the SHA-3 algorithm (considering only theta and chi operations)
void performIteration(InternalState* state) {
    InternalState newState = *state;

    // Theta operation
    // (Update each lane based on the neighboring lanes)
    for (int i = 0; i < STATE_SIZE; i++) {
        for (int j = 0; j < STATE_SIZE; j++) {
            newState.lanes[i][j] ^= state->lanes[(i + 4) % STATE_SIZE][j] ^ state->lanes[(i + 1) % STATE_SIZE][j];
        }
    }

    // Chi operation
    // (Update each lane based on the combination of its original value and the values of two neighboring lanes)
    for (int i = 0; i < STATE_SIZE; i++) {
        for (int j = 0; j < CAPACITY_LANES; j++) {
            newState.lanes[i][j] ^= (~state->lanes[i][(j + 1) % CAPACITY_LANES]) & state->lanes[i][(j + 2) % CAPACITY_LANES];
        }
    }

    *state = newState;
}

int main() {
    InternalState state;

    // Initialize all lanes in the capacity portion with zeros
    for (int i = 0; i < STATE_SIZE; i++) {
        for (int j = 0; j < CAPACITY_LANES; j++) {
            state.lanes[i][j] = 0;
        }
    }

    int iterations = 0;

    while (!allCapacityLanesNonzero(state) && iterations < MAX_ITERATIONS) {
        performIteration(&state);
        iterations++;
    }

    if (allCapacityLanesNonzero(state)) {
        printf("All lanes in the capacity portion have at least one nonzero bit after %d iterations.\n", iterations);
    } else {
        printf("The maximum number of iterations (%d) reached. Not all lanes in the capacity portion have a nonzero bit.\n", MAX_ITERATIONS);
    }

    return 0;
}
