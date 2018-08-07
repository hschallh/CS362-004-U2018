/**
 * Test of the function getCost()
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int testsPassed = 1;

void testAssert(int calculated, int expected, char* msg, int val1, char* name1)
{
    if (expected != calculated) {
        printf("TEST FAILED: %s\t%s: %d\tExpected: %d\tCalculated: %d\n",
            msg, name1, val1, expected, calculated);
        testsPassed = 0;
    } else {
#ifdef DEBUG_TEST
        printf("TEST PASSED: %s\n", msg);
#endif
    }
}

int main()
{
    char* names[] = { "curse", "estate", "duchy", "province", "copper", "silver",
        "gold", "adventurer", "council_room", "feast", "gardens", "mine",
        "remodel", "smithy", "village", "baron", "great_hall", "minion",
        "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost",
        "salvager", "sea_hag", "treasure_map" };
    int costs[] = { 0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4 };
    int card_number;

    printf("Testing: getCost()\n");

    for (card_number = curse; card_number <= treasure_map; card_number++) {

        testAssert(getCost(card_number), costs[card_number], "Cost of card",
            card_number, names[card_number]);
    }

    printf("%s\n", testsPassed ? "All tests passed" : "1 or more tests failed");
    return 0;
}