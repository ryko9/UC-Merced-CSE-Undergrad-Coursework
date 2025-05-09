public class Lab21_5 
{

    public static void init(long[] arr) 
    {
        // Initialize all the entries of the array to 0
        for (int i = 0; i < arr.length; i++) {
            arr[i] = 0;
        }
    }

    public static long sumAll(int max) 
    {
        // sumAll basic version
        long subTotal = 0;
        for (int i = 1; i <= max; i++) {
            subTotal += i;
            System.out.println("sumAll " + i + " value " + subTotal);
        }
        return subTotal;
    }
    
    public static long sumAll(long[] arr, int max) 
    {
        // Use the array to store sub results
        for (int i = 1; i <= max ; i++) {
            if (arr[i] == 0) {
                arr[i] = arr[i-1] + i;    
                System.out.println("sumAll[" + i + "] value " + arr[i]);
            }
        }
        return arr[max];
    }
    
    public static long squareSum(int max)
    {
        long subTotal = 0;
        for(int i = 1; i <= max; i++)
        {
            subTotal += (i * i);
            System.out.println("squareSum " + i + " value " + subTotal);
        }
        return subTotal;        
    }
    
    public static long squareSum(long[] arr, int max)
    {
        for (int i = 1; i <= max; i++)
        {
                if (arr[i] == 0)
                {
                    arr[i] = arr[i - 1] + (i * i); //Old value + index squared to get squareSum of that index.
                    System.out.println("squareSum[" + i + "] value " + arr[i]);
                }
        }
        return arr[max];
    }

    public static long fib(int max)
    {
        long subTotal = 0; //Variable to store the fibonacci value at the current index.
        long index2 = 0; //Variable to store the value two indexes before the current index. We start at 2, so index of 0 is 0.
        long index1 = 1; //Variable to store the value one index before the current index. We start at 2, so index of 1 is 1.
        
        for (int i = 2; i <= max; i++)
        {
            
            
            subTotal = index2 + index1; //subTotal changes everytime so no +=
                        
            index2 = index1;    //index changes to 3 in next loop, so two indexes before 3 would be 1, so the value for index2 is just the index value at 1.
            index1 = subTotal; // One index before 3 is 2, and we just found the index value at 2 which is represented by subtotal. 
    
            System.out.println("Fibonnaci " + i + " value " + subTotal); //prints to check value
            //after printing out the value, loops again uses the new values of index2 and index1 which now represent index at (i - 2) and index at (i - 1) for the new value of i.
        }
        return subTotal;
    }
    
    public static long fib(long[] arr, int max)
    {        
        long subTotal = 0;
        long index2 = 0;
        long index1 = 1;
        
        for (int i = 2; i<= max; i++)
        {
            subTotal = index2 + index1;
            
            if (arr[i] == 0)
            {
                arr[i] = subTotal;
            }
            
            index2 = index1;
            index1 = subTotal;
            
            System.out.println("Fibonnaci[" + i + "] value " +  subTotal);        
        }                            
        return subTotal;
    }
    public static long factorial(int max)
    {
        long lastValue = 1; //Starting at 2, factorial of 1 was 1.
        for (int i = 2; i <= max; i++)
        {
            lastValue*= i;
            System.out.println("Factorial " + i + " value " + lastValue);
        }
        return lastValue;
    }
    
    public static long factorial(long[] arr, int max)
    {
        long lastValue = 1;
        for (int i =2; i <= max; i++)
        {
            
            lastValue*= i;
            
            if(arr[i] == 0)
            {
                arr[i] = lastValue;
            }
            
            System.out.println("Factorial[" + i + "] value " + lastValue);
        }
        return lastValue;
    }

   // Fill-in the appropriate methods to complete the lab

    public static void main(String[] args) {

        final int MAXSIZE = 100;
        long[] arr = new long[MAXSIZE];

        System.out.println("sumAll output for 5 is " + sumAll(5));
        System.out.println("sumAll output for 10 is " + sumAll(10));
        System.out.println("sumAll output for 20 is " + sumAll(20));
        System.out.println("sumAll output for 15 is " + sumAll(15));
        System.out.println();

        init(arr);
        System.out.println("sumAll output for 5 is " + sumAll(arr, 5));
        System.out.println("sumAll output for 10 is " + sumAll(arr, 10));
        System.out.println("sumAll output for 20 is " + sumAll(arr, 20));
        System.out.println("sumAll output for 15 is " + sumAll(arr, 15));
        System.out.println();

        
        System.out.println("squareSum output for 5 is " + squareSum(5));
        System.out.println("squareSum output for 10 is " + squareSum(10));
        System.out.println("squareSum output for 20 is " + squareSum(20));
        System.out.println("squareSum output for 15 is " + squareSum(15));
        System.out.println();

        init(arr);
        System.out.println("squareSum output for 5 is " + squareSum(arr, 5));
        System.out.println("squareSum output for 10 is " + squareSum(arr, 10));
        System.out.println("squareSum output for 20 is " + squareSum(arr, 20));
        System.out.println("squareSum output for 15 is " + squareSum(arr, 15));
        System.out.println();

        System.out.println("Fibonacci Number 5 is " + fib(5));
        System.out.println("Fibonacci Number 10 is " + fib(10));
        System.out.println("Fibonacci Number 20 is " + fib(20));
        System.out.println("Fibonacci Number 15 is " + fib(15));
        System.out.println();
    
        init(arr);
        System.out.println("Fibonacci Number 5 is " + fib(arr, 5));
        System.out.println("Fibonacci Number 10 is " + fib(arr, 10));
        System.out.println("Fibonacci Number 20 is " + fib(arr, 20));
        System.out.println("Fibonacci Number 15 is " + fib(arr, 15));
        System.out.println();

        System.out.println("Factorial of 5 is " + factorial(5));
        System.out.println("Factorial of 10 is " + factorial(10));
        System.out.println("Factorial of 20 is " + factorial(20));
        System.out.println("Factorial of 15 is " + factorial(15));
        System.out.println();

        init(arr);
        System.out.println("Factorial of 5 is " + factorial(arr, 5));
        System.out.println("Factorial of 10 is " + factorial(arr, 10));
        System.out.println("Factorial of 20 is " + factorial(arr, 20));
        System.out.println("Factorial of 15 is " + factorial(arr, 15));
        
    } 

}
