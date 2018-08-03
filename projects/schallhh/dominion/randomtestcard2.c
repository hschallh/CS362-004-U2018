/**
 * Test of the village card
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRIES 1000

int testsPassed = 1;

void testAssert(int test, char* msg)
{
    if (!test) {
        printf("TEST FAILED: %s\n", msg);
        testsPassed = 0;
    } else {
#ifdef DEBUG_TEST
        printf("TEST PASSED: %s\n", msg);
#endif
    }
}

int main()
{
    srand(time(NULL));

    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    struct gameState G, prevG;
    int p, i, j;
    int coin_bonus = 0, villagePos;

    memset(&G, 23, sizeof(struct gameState));

    printf("Testing: villageEffect()\n");

    for (j = 0; j < TRIES; j++) {
        int seed = rand();
        int numPlayer = 2;

        initializeGame(numPlayer, k, seed, &G);
        p = whoseTurn(&G);

        // Randomize the player's deck
        G.deckCount[p] = rand() % (MAX_DECK - 3) + 3;
        for (i = 0; i < G.deckCount[p]; G.deck[p][i++] = rand() % (treasure_map + 1))
            ;

        // Place a village in the current player's hand
        villagePos = rand() % G.handCount[p];
        G.hand[p][villagePos] = village;

        memcpy(&prevG, &G, sizeof(struct gameState));

        // Play card
        cardEffect(village, 0, 0, 0, &G, villagePos, &coin_bonus);

        // Test states
        testAssert(coin_bonus == 0, "No bonus gained from play.");
        testAssert(G.numActions == prevG.numActions + 2, "2 actions gained from play");
        testAssert(G.handCount[p] == prevG.handCount[p], "Hand increased by 0 (+1 for drawn card, -1 for discard village");
        testAssert(G.deckCount[p] == prevG.deckCount[p] - 1, "Deck decresed by 1");

        // Test cards in right place
        testAssert(prevG.deck[p][prevG.deckCount[p] - 1] == G.hand[p][0], "Last card in previous deck replaces village at front of hand");
    }

    printf("%s\n", testsPassed ? "All tests passed" : "1 or more tests failed");
    return 0;
}