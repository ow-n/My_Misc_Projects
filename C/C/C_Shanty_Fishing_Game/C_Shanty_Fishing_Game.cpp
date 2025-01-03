/* OSRS "C" Shanty Fishing Game
 * I recommend using Macros Options to:
 * Fish All > Cook All > Eat > 
 * Fish All > Cook All > Eat > Sell All */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

class Fish {
public:
    const char* name;
    int fishing_exp;
    int cooking_exp;
    int energy_value_raw;
    int energy_value_cooked;
    int price_raw;
    int price_cooked;
    int count_raw;
    int count_cooked;

    Fish() {
        count_raw = 0;
        count_cooked = 0;
    }
};

class Shrimp : public Fish {
public:
    Shrimp() {
        name = "Shrimp";
        fishing_exp = 15;
        cooking_exp = 10;
        energy_value_raw = 5;
        energy_value_cooked = 15;
        price_raw = 5;
        price_cooked = 15;
    }
};

class Salmon : public Fish {
public:
    Salmon() {
        name = "Salmon";
        fishing_exp = 25;
        cooking_exp = 30;
        energy_value_raw = 8;
        energy_value_cooked = 26;
        price_raw = 8;
        price_cooked = 24;
    }
};

class SwordFish : public Fish {
public:
    SwordFish() {
        name = "SwordFish";
        fishing_exp = 40;
        cooking_exp = 80;
        energy_value_raw = 10;
        energy_value_cooked = 36;
        price_raw = 12;
        price_cooked = 36;
    }
};

class Fisher {
private:
    void check_level_up() {
        while (fishing_exp >= 100) {
            fishing_exp -= 100;
            fishing_lvl++;
            printf("\to< [Fishing level up: %d] >o\n\n", fishing_lvl);
        }
        
        while (cooking_exp >= 100) {
            cooking_exp -= 100;
            cooking_lvl++;
            printf("\t[Cooking level up: %d]\n\n", cooking_lvl);
        }
    }

public:
    int energy;
    int gold;
    int fishing_exp;
    int fishing_lvl;
    int cooking_exp;
    int cooking_lvl;
    Shrimp shrimps;
    Salmon salmons;
    SwordFish swordfishes;

    Fisher() {
        energy = 100;
        gold = 0;
        fishing_exp = 0;
        fishing_lvl = 1;
        cooking_exp = 0;
        cooking_lvl = 1;
    }

    void display_stats() {
        printf("Displaying Stats:\n");
        printf("Gold: %d\n", gold);
        printf("Energy: %d\n", energy);
        printf("Fishing: Lvl %d | %d exp\n", fishing_lvl, fishing_exp);
        printf("Cooking: Lvl %d | %d exp\n\n", cooking_lvl, cooking_exp);
    }

    void display_inventory() {
        printf("Displaying Inventory:\n");
        printf("Shrimps:  \tRaw %dx \t Cooked %dx\n", shrimps.count_raw, shrimps.count_cooked);
        printf("Salmon:   \tRaw %dx \t Cooked %dx\n", salmons.count_raw, salmons.count_cooked);
        printf("SwordFish:\tRaw %dx \t Cooked %dx\n\n", swordfishes.count_raw, swordfishes.count_cooked);
    }

    Fish* fish() {
        if (energy < 10) { // 10 energy to fish
            printf("You're too tired to fish! [Energy: %d]\n\n", energy);
            return nullptr;
        }

        int chance = rand() % 100 + 1;
        Fish* caught_fish;
        int bonus_chance = (fishing_lvl - 1) * 2; // 2% increased chance for each level
        if (chance <= (60 - bonus_chance)) {
            caught_fish = &shrimps;
        } else if (chance <= (90 - (0.5*bonus_chance))) { // salmon and sword increases
            caught_fish = &salmons;
        } else {
            caught_fish = &swordfishes;
        }
        caught_fish->count_raw += 1;
        fishing_exp += caught_fish->fishing_exp;
        check_level_up();

        energy -= 10;
        printf("Caught a [%s]! [Energy: %d]\n\n", caught_fish->name, energy);
        return caught_fish;
    }

    void cook(Fish* fish_type) {
        if (fish_type->count_raw > 0) {
            int chance = rand() % 100 + 1;
            int bonus_chance = (cooking_lvl - 1) * 2; // 2% decreased chance to burn for each level
            if (chance <= (30 - bonus_chance)) {
                printf("You burnt the [%s] to a crisp!\n\n", fish_type->name);
                fish_type->count_raw -= 1;
                cooking_exp += fish_type->cooking_exp / 2;
            } else {
                printf("Successfully cooked the [%s]!\n\n", fish_type->name);
                cooking_exp += fish_type->cooking_exp;
                fish_type->count_raw -= 1;
                fish_type->count_cooked += 1;
            }
            check_level_up();
        } else {
            printf("You don't have any [%s] to cook!\n\n", fish_type->name);
        }
    }

    void eat(Fish* fish_type, int is_raw) {
        if (is_raw) {
            if (fish_type->count_raw > 0) {
                fish_type->count_raw -= 1;
                energy += fish_type->energy_value_raw;
                printf("Ate a raw %s. [Energy: %d]\n\n", fish_type->name, energy);
            } else {
                printf("You don't have any raw [%s] to eat!\n\n", fish_type->name);
            }
        } else {
            if (fish_type->count_cooked > 0) {
                fish_type->count_cooked -= 1;
                energy += fish_type->energy_value_cooked;
                printf("Ate a cooked %s. [Energy: %d]\n\n", fish_type->name, energy);
            } else {
                printf("You don't have any cooked [%s] to eat!\n\n", fish_type->name);
            }
        }
    }

    void sell(Fish* fish_type, int is_raw) {
        if (is_raw) {
            if (fish_type->count_raw > 0) {
                fish_type->count_raw -= 1;
                gold += fish_type->price_raw;
                printf("Sold a [Raw %s] for %d gp! [Gold: %d]\n\n", fish_type->name, fish_type->price_raw, gold);
            } else {
                printf("You don't have any [Raw %s] to sell!\n\n", fish_type->name);
            }
        } else {
            if (fish_type->count_cooked > 0) {
                fish_type->count_cooked -= 1;
                gold += fish_type->price_cooked;
                printf("Sold a [Cooked %s] for %d coins! [Gold: %d]\n\n", fish_type->name, fish_type->price_cooked, gold);
            } else {
                printf("You don't have any [Cooked %s] to sell!\n\n", fish_type->name);
            }
        }
    }

    void rest() {
        if (gold >= 40) {
            energy += 20;
            gold -= 40;
            printf("You take a break at Rusty Anchor Inn for 40 gp and gained 20 energy.\n\n");
        } else {
            printf("Not enough gold! The Rusty Anchor Inn requires 40 gp.\n\n");
        }
    }

    // Macros
    void fish_all() {
        while (energy >= 10) {
            fish();
        }
        printf("Finished fishing until energy was depleted. [Energy: %d]\n\n", energy);
    }

    void cook_all() {
        while (shrimps.count_raw > 0) {
            cook(&shrimps);
        }
        while (salmons.count_raw > 0) {
            cook(&salmons);
        }
        while (swordfishes.count_raw > 0) {
            cook(&swordfishes);
        }
    }

    void sell_all() {
        Fish* fish_types[] = {&shrimps, &shrimps, &salmons, &salmons, &swordfishes, &swordfishes};
        int is_raw[] = {1, 0, 1, 0, 1, 0};

        for (int i = 0; i < 6; i++) {
            while ((is_raw[i] == 1 && fish_types[i]->count_raw > 0) || 
                   (is_raw[i] == 0 && fish_types[i]->count_cooked > 0)) {
                sell(fish_types[i], is_raw[i]);
            }
        }
    }
};

// C Prototypes
void fisher_creation();

int main() {
    bool fishing_master = false;
    srand(time(NULL)); // seed random number generator

    Fisher myFisher; // create our character
    fisher_creation();

    printf("Listen up! I'll be tellin' ye this just once, so ye best be payin attention!\n");
    printf("Here be ye options. Don't let me catch ye slackin', or ye'll be feedin' the fish!\n\n");
    
    do {
        printf("Main Menu:\n");
        printf("1. Macros\n");
        printf("2. Fish\n");
        printf("3. Cook\n");
        printf("4. Sell\n");
        printf("5. Eat\n");
        printf("6. Rest\n");
        printf("7. Info\n");
        printf("8. Quit Game\n");
        printf("Choose Action: ");

        int choice;
        scanf("%d", &choice);
        printf("\n");

        Fish* caught_fish;

        switch (choice) {
            case 1: // macros
                printf("Macros Menu:\n");
                printf("1. Fish All\n");
                printf("2. Cook All\n");
                printf("3. Sell All\n");
                printf("Choose Macro: ");
                int macro_choice;
                scanf("%d", &macro_choice);
                printf("\n");
                switch (macro_choice) {
                    case 1: myFisher.fish_all(); break;
                    case 2: myFisher.cook_all(); break;
                    case 3: myFisher.sell_all(); break;
                    default: printf("Invalid macro choice.\n");
                }
                break;
            case 2: // fish
                myFisher.fish();
                break;
            case 3: // cook
                printf("Which fish would you like to cook?\n1. Shrimp\n2. Salmon\n3. Swordfish\nFish Option: ");
                int cook_choice;
                scanf("%d", &cook_choice);
                printf("\n");
                if (cook_choice == 1) myFisher.cook(&myFisher.shrimps);
                else if (cook_choice == 2) myFisher.cook(&myFisher.salmons);
                else if (cook_choice == 3) myFisher.cook(&myFisher.swordfishes);
                else printf("Invalid choice.\n");
                break;
            case 4: // sell
                printf("Which fish would you like to sell?\n1. Raw Shrimp\n2. Cooked Shrimp\n3. Raw Salmon\n4. Cooked Salmon\n5. Raw Swordfish\n6. Cooked Swordfish\nFish Option: ");
                int sell_choice;
                scanf("%d", &sell_choice);
                printf("\n");
                switch(sell_choice) {
                    case 1: myFisher.sell(&myFisher.shrimps, 1); break;
                    case 2: myFisher.sell(&myFisher.shrimps, 0); break;
                    case 3: myFisher.sell(&myFisher.salmons, 1); break;
                    case 4: myFisher.sell(&myFisher.salmons, 0); break;
                    case 5: myFisher.sell(&myFisher.swordfishes, 1); break;
                    case 6: myFisher.sell(&myFisher.swordfishes, 0); break;
                    default: printf("Invalid choice.\n");
                }
                break;
            case 5: // eat
                printf("Which fish would you like to eat?\n1. Raw Shrimp\n2. Cooked Shrimp\n3. Raw Salmon\n4. Cooked Salmon\n5. Raw Swordfish\n6. Cooked Swordfish\nFish Option: ");
                int eat_choice;
                scanf("%d", &eat_choice);
                printf("\n");
                switch (eat_choice) {
                    case 1: myFisher.eat(&myFisher.shrimps, 1); break;
                    case 2: myFisher.eat(&myFisher.shrimps, 0); break;
                    case 3: myFisher.eat(&myFisher.salmons, 1); break;
                    case 4: myFisher.eat(&myFisher.salmons, 0); break;
                    case 5: myFisher.eat(&myFisher.swordfishes, 1); break;
                    case 6: myFisher.eat(&myFisher.swordfishes, 0); break;
                    default: printf("Invalid choice.\n");
                }
                break;
            case 6: // rest
                myFisher.rest();
                break;
            case 7: // info
                printf("Info Menu:\n");
                printf("1. Display Stats\n");
                printf("2. Display Inventory\n");
                printf("3. Display Both\n");
                printf("Choose Info Option: ");
                int info_choice;
                scanf("%d", &info_choice);
                printf("\n");
                switch (info_choice) {
                    case 1: myFisher.display_stats(); break;
                    case 2: myFisher.display_inventory(); break;
                    case 3: 
                        myFisher.display_stats();
                        myFisher.display_inventory();
                        break;
                    default: printf("Invalid info choice.\n");
                }
                break;
            case 8:
                if (myFisher.gold >= 100) {
                    fishing_master = true;
                }
                printf("Fishing Master Status: %s\n", fishing_master ? "True" : "False");
                if (fishing_master) {
                    printf("Thanks for playing! Didn't think it'd take this long to write...\n");
                    return 0;
                } else {
                    printf("Your work here is not done! You need 100 gold!\n\n");
                }
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (true);
    return 0;
}

// C Functions
void fisher_creation() {
    char title[50] = "Fisher ";
    char name[50];

    printf("Ye've made it to Port Sarim have ye?\n");
    printf("What be yer name? ");
    scanf("%s", name);
    strncat(title, name, sizeof(title) - strlen(title) - 1);
    printf("Avast, %s! Time for our \"C\" Shanty!\n\n", title);
}
