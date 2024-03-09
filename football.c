#include <stdio.h>

void findCombinations(int score) {
    printf("\nPossible combinations of scoring plays for the score %d:\n", score);

    // Variables for the count of each type of scoring play
    int TD, TD_plus_1, TD_plus_2, FG, Safety;

    // Iterate over all possible combinations of scoring plays
    for (TD_plus_2 = 0; TD_plus_2 * 8 <= score; ++TD_plus_2) {
        for (TD_plus_1 = 0; TD_plus_1 * 7 + TD_plus_2 * 8 <= score; ++TD_plus_1) {
            for (TD = 0; TD * 6 + TD_plus_1 * 7 + TD_plus_2 * 8 <= score; ++TD) {
                for (FG = 0; FG * 3 + TD * 6 + TD_plus_1 * 7 + TD_plus_2 * 8 <= score; ++FG) {
                    for (Safety = 0; Safety * 2 + FG * 3 + TD * 6 + TD_plus_1 * 7 + TD_plus_2 * 8 <= score; ++Safety) {
                        // If the combination adds up to the score, print it
                        if (Safety * 2 + FG * 3 + TD * 6 + TD_plus_1 * 7 + TD_plus_2 * 8 == score) {
                            printf("%d TD + 2pt, %d TD + 1pt FG, %d TD, %d 3pt FG, %d Safety\n",
                                   TD_plus_2, TD_plus_1, TD, FG, Safety);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int score;

    // Prompt the user for scores until 0 or 1 is entered to stop
    do {
        printf("\nEnter 0 or 1 to STOP\n");
        printf("Enter the NFL score: ");
        scanf("%d", &score);

        if (score > 1) {
            findCombinations(score);
        }
    } while (score > 1);

    return 0;
}

