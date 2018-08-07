/**
 * Test of the Adventurer card
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

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

void adventureTest(int cardNo, int deckPos)
{
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    struct gameState G, prevG;
    int p, i;
    int coin_bonus = 0;

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);
    p = whoseTurn(&G);

    // Place an adventurer in the current player's hand and set the deck and
    // discard to all estates and 2 of the provided treasure cards
    G.hand[p][0] = adventurer;
    G.discardCount[p] = 10 - G.deckCount[p];
    for (i = 0; i < 10; i++) {
        if (i < G.deckCount[p]) {
            G.deck[p][i] = i == deckPos || i == deckPos + 1 ? cardNo : estate;
        } else {
            G.discard[p][i - G.deckCount[p]] = i == deckPos || i == deckPos + 1 ? cardNo : estate;
        }
    }

    // printf("Deck: ");
    // for (i = 0; i < G.deckCount[p]; i++) {
    //     printf("%d ", G.deck[p][i]);
    // }
    // printf("\nDiscard: ");
    // for (i = 0; i < G.discardCount[p]; i++) {
    //     printf("%d ", G.discard[p][i]);
    // }
    // printf("\n");

    memcpy(&prevG, &G, sizeof(struct gameState));

    // Play card
    cardEffect(adventurer, 0, 0, 0, &G, 0, &coin_bonus);

    // Test states
    testAssert(coin_bonus == 0, "No bonus gained from play.");
    testAssert(G.numActions == prevG.numActions, "No actions gained from play");
    testAssert(G.handCount[p] == prevG.handCount[p] + 1, "Hand increased by 1 (+2 cards drawn -1 adventurer discarded)");
    testAssert(G.deckCount[p] + G.discardCount[p] == prevG.deckCount[p] + prevG.discardCount[p] - 2, "Deck and discard decresed by 2");

    // Test cards in right place
    testAssert(G.hand[p][G.handCount[p] - 1] == cardNo, "Last card in hand is the drawn treasure card");
    testAssert(G.hand[p][0] == cardNo, "Drawn treasure card replaces adventurer at front of hand");

    // Test $$ increases
    updateCoins(p, &G, 0);
    updateCoins(p, &prevG, 0);
    // Note: (cardNo - 3) is the value of any treasure card
    testAssert(prevG.coins + (cardNo - 3) * 2 == G.coins, "Value of the player's hand has increased by 2x the cardNo value");
}

int main()
{
    printf("Testing: adventurerEffect()\n");

    int cardNo, deckPos;

    for (cardNo = copper; cardNo <= gold; cardNo++) {
        for (deckPos = 0; deckPos < 9; deckPos++) {
            adventureTest(cardNo, deckPos);
        }
    }

    printf("%s\n", testsPassed ? "All tests passed" : "1 or more tests failed");
    return 0;
}