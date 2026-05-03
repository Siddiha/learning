// ─────────────────────────────────────────
//  ARRAYS
// ─────────────────────────────────────────

import java.util.Arrays;

public class Arrays {
    public static void main(String[] args) {

        // ── Declare & Initialize ──────────────────
        int[] nums = {3, 1, 4, 1, 5, 9, 2, 6};
        String[] fruits = new String[3];   // fixed size, all null
        fruits[0] = "apple";
        fruits[1] = "banana";
        fruits[2] = "cherry";

        int[] zeros = new int[5];          // all 0
        boolean[] flags = new boolean[3];  // all false

        // ── Access ────────────────────────────────
        System.out.println(nums[0]);          // 3
        System.out.println(nums[nums.length - 1]); // 6 (last element)
        System.out.println(nums.length);      // 8

        // ── Iterate ───────────────────────────────
        for (int n : nums)                        // enhanced for
            System.out.print(n + " ");
        System.out.println();

        for (int i = 0; i < nums.length; i++)     // classic for (when index needed)
            System.out.print("[" + i + "]=" + nums[i] + " ");
        System.out.println();

        // ── Sort ──────────────────────────────────
        int[] copy = nums.clone();
        java.util.Arrays.sort(copy);
        System.out.println(java.util.Arrays.toString(copy)); // [1, 1, 2, 3, 4, 5, 6, 9]

        // Sort descending — needs Integer[] not int[]
        Integer[] boxed = {3, 1, 4, 1, 5};
        java.util.Arrays.sort(boxed, java.util.Comparator.reverseOrder());
        System.out.println(java.util.Arrays.toString(boxed)); // [5, 4, 3, 1, 1]

        // ── Search ────────────────────────────────
        java.util.Arrays.sort(copy);
        int idx = java.util.Arrays.binarySearch(copy, 5);  // must be sorted first
        System.out.println(idx);  // index of 5

        // ── Fill & Copy ───────────────────────────
        int[] filled = new int[5];
        java.util.Arrays.fill(filled, 7);
        System.out.println(java.util.Arrays.toString(filled)); // [7, 7, 7, 7, 7]

        int[] dest = java.util.Arrays.copyOf(nums, 5);         // copy first 5
        int[] range = java.util.Arrays.copyOfRange(nums, 2, 6); // index 2 to 5
        System.out.println(java.util.Arrays.toString(dest));
        System.out.println(java.util.Arrays.toString(range));

        // ── Compare ───────────────────────────────
        int[] arr1 = {1, 2, 3};
        int[] arr2 = {1, 2, 3};
        System.out.println(arr1 == arr2);                     // false — different refs
        System.out.println(java.util.Arrays.equals(arr1, arr2)); // true — same content

        // ── Print array ───────────────────────────
        System.out.println(java.util.Arrays.toString(nums));  // [3, 1, 4, 1, 5, 9, 2, 6]

        // ── 2D Arrays ─────────────────────────────
        int[][] matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        System.out.println(matrix[1][2]);           // 6
        System.out.println(matrix.length);          // 3 rows
        System.out.println(matrix[0].length);       // 3 cols

        for (int[] row : matrix) {
            for (int val : row)
                System.out.print(val + " ");
            System.out.println();
        }

        System.out.println(java.util.Arrays.deepToString(matrix));
        // [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

        // ── Jagged array (rows of different lengths) ─
        int[][] jagged = new int[3][];
        jagged[0] = new int[]{1, 2};
        jagged[1] = new int[]{3, 4, 5};
        jagged[2] = new int[]{6};

        for (int[] row : jagged) {
            System.out.println(java.util.Arrays.toString(row));
        }

        // ── Convert array ↔ List ──────────────────
        String[] arr = {"a", "b", "c"};
        java.util.List<String> list = java.util.Arrays.asList(arr); // fixed size list
        System.out.println(list);

        java.util.List<String> mutableList = new java.util.ArrayList<>(list);
        mutableList.add("d");
        System.out.println(mutableList);
    }
}
