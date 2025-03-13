import org.junit.*;

public class InsertionSortTest{
    InsertionSort is;
    
    @Before
    public void setup(){
        is = new InsertionSort();
    }
    //testing path 5-6-End
    @Test
    public void testingEmptyArray(){
        int[] nums = new int[0];
        is.insertionSort(nums);
        Assert.assertArrayEquals(new int[]{},nums);
    }

    //testing path 5-6-7-8-9-13-6End
    @Test
    public void testingSortedArray(){
        int[] nums = new int[] {1,2,3,4,5};
        is.insertionSort(nums);
        Assert.assertArrayEquals(new int[]{1,2,3,4,5},nums);
    }

    //testing path 5-6-7-8-9-10-11-13-6-End
    @Test
    public void testingUnsortedArray(){
        int[] nums = new int[] {4,3,1,2,5};
        is.insertionSort(nums);
        Assert.assertArrayEquals(new int[]{1,2,3,4,5},nums);
    }
}