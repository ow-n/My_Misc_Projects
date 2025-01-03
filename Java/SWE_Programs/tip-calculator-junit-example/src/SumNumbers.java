/*
 *   TEST SCENARIO 1
 *   INPUTS: 1, 1
 *   EXPECTED OUTPUT: 1 (which represents "true" - meaning the sum of the two numbers is even)
 *
 *   TEST SCENARIO 2
 *   INPUTS: 1, 2
 *   EXPECTED OUTPUT: 0 (which represents "false" - meaning the sum of the two numbers is odd)
 */

public class SumNumbers {

    /*   Define a function called sumIsEven() which takes two integer inputs
     *   and returns 1 for “true” if the sum of the two values is an even number.
     *   If the sum is an odd number, then return 0 for “false.”
     */
    public int sumIsEven(int a, int b) {
        if((a+b) % 2 == 0) { // Modulus for even should be 0 instead of 2
            return 1;
        } else {
            return 0;
        }
    }
}
