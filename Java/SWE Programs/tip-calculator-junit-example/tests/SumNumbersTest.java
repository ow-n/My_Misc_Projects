import org.junit.Test;
import static org.junit.Assert.*;

public class SumNumbersTest {

    @Test
    public void testSumIsEvenTrue() {
        SumNumbers sumNumbers = new SumNumbers();
        int result = sumNumbers.sumIsEven(1, 1);
        assertEquals("Sum should be Even", 1, result);
    }

    @Test
    public void testSumIsEvenFalse(){
        SumNumbers sumNumbers = new SumNumbers();
        int result = sumNumbers.sumIsEven(1, 2);
        assertEquals("Sum should be Odd", 0, result);
    }
}