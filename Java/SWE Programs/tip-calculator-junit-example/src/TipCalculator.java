/*
 *   TEST SCENARIO 1
 *   INPUTS: $100.00 bill, 20% tip
 *   EXPECTED OUTPUT: $20.00
 *
 *   TEST SCENARIO 2
 *   Your choice!
 */

public class TipCalculator {

    /*  This method takes the bill amount as a double and a tip percentage as an
     *  integer and returns a rounded amount for what to tip. Use a tip calculator
     *  online to write test data to test this method.
     *
     *  For tests results that are off by 1 cent, consider it a rounding issue
     *  and adjust your test data.
     */
    public double calculateTip(double bill, int percentage) {
        float decimalPercent = ((float) percentage / 100); // Turns our integer percentage into a decimal
        // With the true decimal calculated, the below calculates the tip and rounds to two decimal places
        return (double) Math.round((decimalPercent * bill) * 100) / 100;
    }
}
