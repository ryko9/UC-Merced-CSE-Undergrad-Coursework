package arraylist;

import java.util.ArrayList;

public class ArrayListRunner {
    
    // Use this class to run your code

    public static void main(String[] args) {
        
        testArrayList();
        testTrackedArrayList();
    }

    
    
    public static void testArrayList() {
        
        ArrayList<String> words = new ArrayList<String>();
        words.add ("a");
        words.add ("b");
        words.add ("c");
        words.remove ("b");
        words.add ("d");
        words.remove ("a");
        words.add ("e");
        words.remove ("b");
        words.add ("d");
        words.remove ("c");
        words.remove ("d");
        
        System.out.println(words.toString());
    }
    
    public static void testTrackedArrayList()
    {
        TrackedArrayList<String> words = new TrackedArrayList<String>();
        words.add ("a");
        System.out.println(words.maxSizeSoFar());
        words.add ("b");
        System.out.println(words.maxSizeSoFar());
        words.add ("c");
        System.out.println(words.maxSizeSoFar());
        words.remove ("b");
        System.out.println(words.maxSizeSoFar());
        words.add ("d");
        System.out.println(words.maxSizeSoFar());
        words.remove ("a");
        System.out.println(words.maxSizeSoFar());
        words.add ("e");
        System.out.println(words.maxSizeSoFar());
        words.remove ("b");
        System.out.println(words.maxSizeSoFar());
        words.add ("d");
        System.out.println(words.maxSizeSoFar());
        words.remove ("c");
        System.out.println(words.maxSizeSoFar());
        words.remove ("d");
        System.out.println(words.maxSizeSoFar());
        
    }
}