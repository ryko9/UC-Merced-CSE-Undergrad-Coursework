package arraylist;

import java.util.ArrayList;

// the symbol 'CLASS' will stand for the class of elements that
// the ArrayList was declared with
public class TrackedArrayList<CLASS> extends ArrayList<CLASS> {

    public int size = 0;
    public int bsize = 0;

    public int maxSizeSoFar() {
        return bsize;
        
    } 

    
    //This is how you would override the remove method
    @Override
    public boolean remove(Object element) {
        // inside, you can use 'element' as you need
        boolean ret = super.remove(element);
        if(ret)
        {
            size--;
        }
        return ret;
    }
    

    // This is how you override the add method.  We can use the 
    // symbol 'CLASS' because we used it above, when we defined
    // TrackedArrayList
    @Override
    public boolean add(CLASS element) {
        // inside, you can use 'element' as necessary
        boolean ret = super.add(element);
        if(ret)
        {
            size++;
        }
        if(size > bsize)
        {
            bsize = size;
        }
        return ret;
    } 
    
    

    

    
}