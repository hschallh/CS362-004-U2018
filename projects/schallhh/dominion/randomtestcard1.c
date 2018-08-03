/**
 * Test of the Smithy card
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

    int seed = rand();
    int numPlayer = 2;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    struct gameState G, prevG;
    int p, i;
    int coin_bonus = 0;

    memset(&G, 23, sizeof(struct gameState));

    printf("Testing: smithyEffect()\n");

    for (i = 0; i < TRIES; i++) {

        initializeGame(numPlayer, k, seed, &G);
        p = whoseTurn(&G);

        // Place a smithy in the current player's hand and set the end of the deck to 2, 1, 0
        G.hand[p][0] = smithy;

        memcpy(&prevG, &G, sizeof(struct gameState));

        // Play card
        cardEffect(smithy, 0, 0, 0, &G, 0, &coin_bonus);

        // Test states
        testAssert(coin_bonus == 0, "No bonus gained from play.");
        testAssert(G.numActions == prevG.numActions, "No actions gained from play");
        testAssert(G.handCount[p] == prevG.handCount[p] + 2, "Hand increased by 2 (+3 from deck -1 to discard)");
        testAssert(G.deckCount[p] == prevG.deckCount[p] - 3, "Deck decresed by 3");

        // Test cards in right place
        testAssert(prevG.deck[p][prevG.deckCount[p] - 3] == G.hand[p][0], "Third to last card in deck replaces simthy at front of hand");
        testAssert(prevG.deck[p][prevG.deckCount[p] - 2] == G.hand[p][G.handCount[p] - 1], "Second to last card in deck is last card in hand");
        testAssert(prevG.deck[p][prevG.deckCount[p] - 1] == G.hand[p][G.handCount[p] - 2], "Last card in deck is second to last card in hand");
    }
    printf("%s\n", testsPassed ? "All tests passed" : "1 or more tests failed");
    return 0;
}