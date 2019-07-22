/**
 *
 * DHeap
 *
 * An implementation of a D-ary heap
 */

public class DHeap
{
	
    private int size, max_size, d;
    private DHeap_Item[] array;
    /*
     * returns childIndex's child of array[nodeIndex]
     * array[nodeIndex] has an childIndex'th child
     * preconditions:
     * 0<=nodeIndex<size
     * 0<=childIndex<d
     * time: O(1)
     */
    private int getChild(int nodeIndex,int childIndex)
    {
    	return child(nodeIndex, childIndex, d);
    }
    
    /*
     * does array[nodeIndex] have a child
     * preconditions:
     * 0<=nodeIndex
     * time: O(1)
     */
    private boolean hasChild(int nodeIndex){
    	return nodeIndex * d + 1 < size; //the index where the first child should be
    }
    
    /*
    * @return[0]: the index of the child of array[nodeIndex] with the minimum key
    * @return[1]: the number of comparisons
    * preconditions:
    * 0<=nodeIndex && hasChild(nodeIndex)
    * time: O(d)
    */
    private int[] minKeyChild(int nodeIndex){
    	int lastChildIndex =  Math.min(size-1, getChild(nodeIndex, d));
    	int minChildIndex = getChild(nodeIndex, 0);
    	for(int i = getChild(nodeIndex, 0)+1; i <= lastChildIndex; ++i){
    		if(array[i].getKey() < array[minChildIndex].getKey()){
    			minChildIndex = i;
    		}
    	}
    	return new int[]{minChildIndex,lastChildIndex-getChild(nodeIndex, 0)};
    }
    
    /*
     * node[nodeIndex] isn't root
     * preconditions:
     * 0<=nodeIndex<sizes
     * time: O(1)
     */
    private int getParent(int nodeIndex)
    {
    	return parent(nodeIndex,d);
    }
    
    /*
     * swap nodes array[a] and array[b]
     * preconditions:
     * 0<=a,b<size
     * time: O(1)
     */
    private void swap(int a,int b){
    	DHeap_Item node = array[a];
		array[a] = array[b];
		array[a].setPos(a); 
		array[b] = node;
		node.setPos(b);
    }
    
    /*
     * perform heapfy-up from array[nodeIndex]
     * preconditions:
     * 0<=nodeIndex<size
     * time: O(log_d(n))=O(log(n))
     */
    private int heapifyUp(int nodeIndex){
    	if(nodeIndex == 0){ //there is no up
    		return 0;
    	}
    	int parentIndex =  getParent(nodeIndex);
    	if(array[nodeIndex].getKey() < array[parentIndex].getKey()){
    		//swap node with parent
    		swap(nodeIndex,parentIndex);
    		return heapifyUp(parentIndex) + 1; //we did 1 comparison and problem might move up 
    	}
    	return 1; //we did 1 comparison
    }
    
    /*
    * perform heapfy-down from array[nodeIndex]
    * 0<=nodeIndex<size
    * time: O(d*log_d(n))=O(d*log(n))
    */
    private int heapifyDown(int nodeIndex){
    	if(!hasChild(nodeIndex)){
    		return 0;
    	}
    	int[] minKeyChildReturnValue = minKeyChild(nodeIndex);
    	if(array[nodeIndex].getKey() > array[minKeyChildReturnValue[0]].getKey()){ //if there is a child with a lower key
    		swap(nodeIndex,minKeyChildReturnValue[0]);
    		return minKeyChildReturnValue[1] + heapifyDown(minKeyChildReturnValue[0]) + 1; //problem might be pushed down
    	}
    	return minKeyChildReturnValue[1] + 1;
    }
    
	// Constructor
	// m_d >= 2, m_size > 0
    // time: O(1)
    DHeap(int m_d, int m_size) {
    	max_size = m_size;
		d = m_d;
        array = new DHeap_Item[max_size];
        size = 0;
    }
	
	/**
	 * public int getSize()
	 * Returns the number of elements in the heap.
	 * time: O(1)
	 */
	public int getSize() {
		return size;
	}
	
  /**
     * public int arrayToHeap()
     *
     * The function builds a new heap from the given array.
     * Previous data of the heap should be erased.
     * preconidtion: array1.length() <= max_size
     * postcondition: isHeap()
     * 				  size = array.length()
     * Returns number of comparisons along the function run.
     * time: O(n) 
	 */
    public int arrayToHeap(DHeap_Item[] array1) 
    {
        size = array1.length;
        int comparisons = 0;
        for(int i = 0; i < size; ++i){
        	array[i] = array1[i];
        	array[i].setPos(i);
        }
        for(int i = size-1; i >= 0; --i){
        	comparisons += heapifyDown(i);
        }
        return comparisons;
    }

    /**
     * public boolean isHeap()
     *
     * The function returns true if and only if the D-ary tree rooted at array[0]
     * satisfies the heap property or has size == 0.
     * time: O(n)
     */
    public boolean isHeap() 
    {
        if(size == 0){
        	return true;
        }
        if(array[0] == null){
        	return false;
        }
        for(int i = 1; i < size; ++i){ //check for each node if the edge with it's parent isn't bad
        	if(array[i] == null || array[i].getKey() < array[getParent(i)].getKey()){
        		return false; //not heap
        	}
        }
        return true; //not not heap => heap
    }


    /**
     * public static int parent(i,d), child(i,k,d)
     * (2 methods)
     *
     * precondition: i >= 0, d >= 2, 1 <= k <= d
     *
     * The methods compute the index of the parent and the k-th child of 
     * vertex i in a complete D-ary tree stored in an array. 
     * Note that indices of arrays in Java start from 0.
     * time: O(1)
     */
    public static int parent(int i, int d) {
    	return Math.max(0, (i-1)/d);
    }
    
    public static int child (int i, int k, int d) {
    	return d * i + k+1;
    }

    /**
    * public int Insert(DHeap_Item item)
    *
	* Inserts the given item to the heap.
	* Returns number of comparisons during the insertion.
	*
    * precondition: item != null
    *               isHeap()
    *               size < max_size
    * 
    * postcondition: isHeap()
    * time: O(log_d(n))=O(log(n))
    */
    public int Insert(DHeap_Item item) 
    {        
    	size++;
    	array[size-1] = item;
    	item.setPos(size-1);
    	return heapifyUp(size-1);
    }

 /**
    * public int Delete_Min()
    *
	* Deletes the minimum item in the heap.
	* Returns the number of comparisons made during the deletion.
    * 
	* precondition: size > 0
    *               isHeap()
    * 
    * postcondition: isHeap()
    * time: O(d*log_d(n))=O(d*log(n))
    */
    public int Delete_Min()
    {
     	array[0] = array[size-1];
     	array[0].setPos(0);
     	size--;
     	return heapifyDown(0);
    }


    /**
     * public DHeap_Item Get_Min()
     *
	 * Returns the minimum item in the heap.
	 *
     * precondition: heapsize > 0
     *               isHeap()
     *		size > 0
     * 
     * postcondition: isHeap()
     * time: O(1)
     */
    public DHeap_Item Get_Min()
    {
		return array[0];
    }
	
  /**
     * public int Decrease_Key(DHeap_Item item, int delta)
     *
	 * Decerases the key of the given item by delta.
	 * Returns number of comparisons made as a result of the decrease.
	 *
     * precondition: item.pos < size;
     *               item != null
     *               isHeap()
     * 
     * postcondition: isHeap()
     * time: O(dlog_d(n))=O(dlog(n))
     */
    public int Decrease_Key(DHeap_Item item, int delta)
    {
		int nodeIndex = item.getPos();
		item.setKey(item.getKey()-delta);
		if(delta >= 0) {
			return heapifyUp(nodeIndex); //node might need to go up
		}else {
			int comparisons = Delete(item);
			return comparisons + Insert(item); //node might need to go down
		}
    }
	
	  /**
     * public int Delete(DHeap_Item item)
     *
	 * Deletes the given item from the heap.
	 * Returns number of comparisons during the deletion.
	 *
     * precondition: item.pos < size;
     *               item != null
     *               isHeap()
     * 
     * postcondition: isHeap()
     * time: O(d*log_d(n))=O(d*log(n))
     */
    public int Delete(DHeap_Item item)
    {
		int comparisons = 0;
    	comparisons += Decrease_Key(item, item.getKey() - Get_Min().getKey() + 1); //turn item to the minimum
		comparisons += Delete_Min();
		return comparisons;
    }
	
	/**
	* Sort the input array using heap-sort (build a heap, and 
	* perform n times: get-min, del-min).
	* Sorting should be done using the DHeap, name of the items is irrelevant.
	* 
	* Returns the number of comparisons performed.
	* 
	* postcondition: array1 is sorted 
	* time: O(d*n*log_d(n))=O(d*n*log(n))
	*/
	public static int DHeapSort(int[] array1, int d) {
		int comparisons = 0;
		DHeap heap = new DHeap(d,array1.length);
		DHeap_Item[] items = new DHeap_Item[array1.length];
		for(int i = 0; i < array1.length; ++i){
			items[i] = new DHeap_Item(null, array1[i]);
		}
		comparisons += heap.arrayToHeap(items);
		for(int i = 0; i < array1.length; ++i){
			array1[i] = heap.Get_Min().getKey();
			comparisons += heap.Delete_Min();
		}
		return comparisons;
	}
}
