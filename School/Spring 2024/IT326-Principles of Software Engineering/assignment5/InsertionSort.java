
public class InsertionSort {

    void insertionSort(int array[]) {
        int size = array.length;
        for (int step = 1; step < size; step++) {
            int key = array[step];
            int j = step - 1;
            while (j >= 0 && key < array[j]) {
                array[j + 1] = array[j];
                --j;
            }
            array[j + 1] = key;
        }
    }

    void display(int[] array){
        for(int i:array)
            System.out.print(i+"  ");
        System.out.println();
    }

    public static void main(String args[]){
        InsertionSort is = new InsertionSort();
        int[] nums = {2,3,44,22,35,67,819,89,11,22,22,56,65};
        is.display(nums);
        is.insertionSort(nums);
        is.display(nums);
    }
}
